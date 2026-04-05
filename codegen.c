#include "codegen.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <direct.h>
#else
#include <sys/stat.h>
#include <sys/types.h>
#endif

typedef struct TrackedVar {
    char *name;
    NebulaType type;
    struct TrackedVar *next;
} TrackedVar;

static TrackedVar *tracked_vars = NULL;

static const char *c_type_name(NebulaType t) {
    switch (t) {
        case TYPE_NUM: return "int";
        case TYPE_DEC: return "double";
        case TYPE_CHAR: return "char";
        case TYPE_BOOL: return "int";
        case TYPE_VOID: return "void";
        default: return "int";
    }
}

static char *build_c_output_path(const char *input_path) {
    const char *slash;
    const char *dot;
    const char *base;
    size_t base_len;
    char *out;

    if (!input_path || input_path[0] == '\0') {
        out = (char *)malloc(22);
        if (!out) return NULL;
        strcpy(out, "output/nebula_generated.c");
        return out;
    }

    slash = strrchr(input_path, '/');
    if (!slash) slash = strrchr(input_path, '\\');
    base = slash ? (slash + 1) : input_path;
    dot = strrchr(base, '.');

    if (!dot) {
        base_len = strlen(base);
    } else {
        base_len = (size_t)(dot - base);
    }

    out = (char *)malloc(7 + base_len + 3);
    if (!out) return NULL;
    strcpy(out, "output/");
    memcpy(out + 7, base, base_len);
    out[7 + base_len] = '\0';
    strcat(out, ".c");
    return out;
}

static void ensure_output_dir_exists(void) {
#ifdef _WIN32
    (void)_mkdir("output");
#else
    (void)mkdir("output", 0755);
#endif
}

static void emit_indent(FILE *out, int indent) {
    int i;
    for (i = 0; i < indent; i++) {
        fputs("    ", out);
    }
}

static void clear_tracked_vars(void) {
    TrackedVar *curr = tracked_vars;
    while (curr) {
        TrackedVar *next = curr->next;
        free(curr->name);
        free(curr);
        curr = next;
    }
    tracked_vars = NULL;
}

static void track_var_type(const char *name, NebulaType type) {
    TrackedVar *curr;
    TrackedVar *entry;
    if (!name || !name[0]) return;
    curr = tracked_vars;
    while (curr) {
        if (strcmp(curr->name, name) == 0) {
            curr->type = type;
            return;
        }
        curr = curr->next;
    }
    entry = (TrackedVar *)calloc(1, sizeof(TrackedVar));
    if (!entry) {
        fprintf(stderr, "Code generation error: out of memory while tracking variable type.\n");
        return;
    }
    entry->name = strdup(name);
    if (!entry->name) {
        free(entry);
        fprintf(stderr, "Code generation error: out of memory while tracking variable name.\n");
        return;
    }
    entry->type = type;
    entry->next = tracked_vars;
    tracked_vars = entry;
}

static NebulaType tracked_var_type(const char *name) {
    TrackedVar *curr = tracked_vars;
    if (!name || !name[0]) return TYPE_UNKNOWN;
    while (curr) {
        if (strcmp(curr->name, name) == 0) {
            return curr->type;
        }
        curr = curr->next;
    }
    return TYPE_UNKNOWN;
}

static int is_num_identifier(ASTNode *id) {
    NebulaType t;
    if (!id || id->kind != AST_IDENTIFIER || !id->text) return 0;
    if (id->inferred_type == TYPE_NUM) return 1;
    t = tracked_var_type(id->text);
    return t == TYPE_NUM;
}

static void emit_expr(FILE *out, ASTNode *node) {
    const char *name;
    if (!node) {
        fputs("0", out);
        return;
    }

    switch (node->kind) {
        case AST_LITERAL:
        case AST_IDENTIFIER:
            fputs(node->text ? node->text : "0", out);
            return;

        case AST_ASSIGN:
            fputc('(', out);
            emit_expr(out, node->left);
            fputs(" = ", out);
            emit_expr(out, node->right);
            fputc(')', out);
            return;

        case AST_UNARYOP:
            if (!node->text) {
                emit_expr(out, node->left);
                return;
            }
            if (strcmp(node->text, "post++") == 0) {
                fputc('(', out);
                emit_expr(out, node->left);
                fputs("++)", out);
                return;
            }
            if (strcmp(node->text, "post--") == 0) {
                fputc('(', out);
                emit_expr(out, node->left);
                fputs("--)", out);
                return;
            }
            fputc('(', out);
            fputs(node->text, out);
            emit_expr(out, node->left);
            fputc(')', out);
            return;

        case AST_BINOP:
            if (node->text && strcmp(node->text, "[]") == 0) {
                emit_expr(out, node->left);
                fputc('[', out);
                emit_expr(out, node->right);
                fputc(']', out);
                return;
            }
            fputc('(', out);
            emit_expr(out, node->left);
            fputc(' ', out);
            fputs(node->text ? node->text : "+", out);
            fputc(' ', out);
            emit_expr(out, node->right);
            fputc(')', out);
            return;

        case AST_IF:
            if (node->text && strcmp(node->text, "?:") == 0) {
                fputc('(', out);
                emit_expr(out, node->left);
                fputs(" ? ", out);
                emit_expr(out, node->right);
                fputs(" : ", out);
                emit_expr(out, node->third);
                fputc(')', out);
                return;
            }
            fputs("0", out);
            return;

        case AST_INPUT:
            if (node->text && strcmp(node->text, "input") != 0) {
                fputs(node->text, out);
            } else {
                fputs("0", out);
            }
            return;

        case AST_FUNC_CALL:
            name = node->text ? node->text : "";
            if (strcmp(name, "nebula") == 0 || strcmp(name, "Nebula") == 0) {
                ASTNode *id_node = node->left;
                ASTNode *step_node = id_node ? id_node->next : NULL;
                fputs("nebula_observe_current(", out);
                if (id_node && id_node->kind == AST_IDENTIFIER && id_node->text) {
                    fprintf(out, "\"%s\"", id_node->text);
                } else {
                    fputs("\"\"", out);
                }
                fputs(", ", out);
                if (step_node) {
                    emit_expr(out, step_node);
                } else {
                    fputs("0", out);
                }
                fputc(')', out);
                return;
            }
            if (strcmp(name, "sin") == 0) name = "neb_sin_deg";
            else if (strcmp(name, "cos") == 0) name = "neb_cos_deg";
            else if (strcmp(name, "tan") == 0) name = "neb_tan_deg";
            fputs(name, out);
            fputc('(', out);
            {
                ASTNode *arg = node->left;
                int first = 1;
                while (arg) {
                    if (!first) fputs(", ", out);
                    emit_expr(out, arg);
                    first = 0;
                    arg = arg->next;
                }
            }
            fputc(')', out);
            return;

        default:
            fputs("0", out);
            return;
    }
}

static void emit_stmt(FILE *out, ASTNode *node, int indent);

static int is_decimal_literal_text(const char *text) {
    const char *p;
    if (!text || !text[0]) return 0;
    p = text;
    if (*p == '+' || *p == '-') p++;
    while (*p) {
        if (*p == '.' || *p == 'e' || *p == 'E') return 1;
        p++;
    }
    return 0;
}

static int is_bool_function_name(const char *name) {
    return name && (
        strcmp(name, "even") == 0 ||
        strcmp(name, "odd") == 0 ||
        strcmp(name, "prime") == 0 ||
        strcmp(name, "palindrome") == 0 ||
        strcmp(name, "leap_year") == 0
    );
}

static int is_decimal_function_name(const char *name) {
    return name && (
        strcmp(name, "sin") == 0 ||
        strcmp(name, "cos") == 0 ||
        strcmp(name, "tan") == 0 ||
        strcmp(name, "neb_sin_deg") == 0 ||
        strcmp(name, "neb_cos_deg") == 0 ||
        strcmp(name, "neb_tan_deg") == 0 ||
        strcmp(name, "power") == 0
    );
}

static int is_bool_binop(const char *op) {
    return op && (
        strcmp(op, "==") == 0 || strcmp(op, "!=") == 0 ||
        strcmp(op, "<") == 0 || strcmp(op, "<=") == 0 ||
        strcmp(op, ">") == 0 || strcmp(op, ">=") == 0 ||
        strcmp(op, "&&") == 0 || strcmp(op, "||") == 0
    );
}

static NebulaType infer_expr_type_for_codegen(ASTNode *node) {
    NebulaType lt;
    NebulaType rt;

    if (!node) return TYPE_UNKNOWN;
    if (node->inferred_type != TYPE_UNKNOWN) return node->inferred_type;

    switch (node->kind) {
        case AST_LITERAL:
            if (node->text && node->text[0] == '"') return TYPE_CHAR;
            if (node->text && (strcmp(node->text, "true") == 0 || strcmp(node->text, "false") == 0)) return TYPE_BOOL;
            if (is_decimal_literal_text(node->text)) return TYPE_DEC;
            return TYPE_NUM;

        case AST_IDENTIFIER:
            return TYPE_UNKNOWN;

        case AST_FUNC_CALL:
            if (is_bool_function_name(node->text)) return TYPE_BOOL;
            if (is_decimal_function_name(node->text)) return TYPE_DEC;
            if (node->text && (strcmp(node->text, "nebula") == 0 || strcmp(node->text, "Nebula") == 0 || strcmp(node->text, "nebula_observe_current") == 0)) return TYPE_NUM;
            return TYPE_UNKNOWN;

        case AST_BINOP:
            if (is_bool_binop(node->text)) return TYPE_BOOL;
            lt = infer_expr_type_for_codegen(node->left);
            rt = infer_expr_type_for_codegen(node->right);
            if (lt == TYPE_DEC || rt == TYPE_DEC) return TYPE_DEC;
            return TYPE_NUM;

        case AST_UNARYOP:
            if (node->text && strcmp(node->text, "!") == 0) return TYPE_BOOL;
            return infer_expr_type_for_codegen(node->left);

        case AST_ASSIGN:
            return infer_expr_type_for_codegen(node->right);

        case AST_IF:
            if (node->text && strcmp(node->text, "?:") == 0) {
                lt = infer_expr_type_for_codegen(node->right);
                rt = infer_expr_type_for_codegen(node->third);
                if (lt == TYPE_DEC || rt == TYPE_DEC) return TYPE_DEC;
                if (lt == TYPE_BOOL || rt == TYPE_BOOL) return TYPE_BOOL;
                if (lt != TYPE_UNKNOWN) return lt;
                return rt;
            }
            return TYPE_UNKNOWN;

        default:
            return TYPE_UNKNOWN;
    }
}

static void emit_stmt_as_block(FILE *out, ASTNode *node, int indent) {
    if (node && node->kind == AST_STMT_LIST) {
        emit_stmt(out, node, indent);
        return;
    }
    fputs("{\n", out);
    if (node) {
        emit_stmt(out, node, indent + 1);
    }
    emit_indent(out, indent);
    fputs("}\n", out);
}

static void emit_stmt_list(FILE *out, ASTNode *node, int indent) {
    ASTNode *curr = node;
    while (curr) {
        emit_stmt(out, curr, indent);
        curr = curr->next;
    }
}

static void emit_print_stmt(FILE *out, ASTNode *node, int indent, int add_newline) {
    ASTNode *arg = node ? node->left : NULL;
    int first = 1;
    NebulaType t;

    while (arg) {
        emit_indent(out, indent);
        if (!first) {
            fputs("printf(\" \");\n", out);
            emit_indent(out, indent);
        }

        t = arg->inferred_type;
        if (t == TYPE_UNKNOWN) {
            t = infer_expr_type_for_codegen(arg);
        }

        if (arg->kind == AST_LITERAL && arg->text && arg->text[0] == '"') {
            fputs("printf(\"%s\", ", out);
            emit_expr(out, arg);
            fputs(");\n", out);
        } else if (t == TYPE_DEC) {
            fputs("printf(\"%g\", (double)", out);
            emit_expr(out, arg);
            fputs(");\n", out);
        } else if (t == TYPE_CHAR) {
            fputs("printf(\"%c\", (char)", out);
            emit_expr(out, arg);
            fputs(");\n", out);
        } else if (t == TYPE_BOOL) {
            fputs("printf(\"%s\", (", out);
            emit_expr(out, arg);
            fputs(") ? \"true\" : \"false\");\n", out);
        } else {
            fputs("printf(\"%d\", (int)", out);
            emit_expr(out, arg);
            fputs(");\n", out);
        }
        first = 0;
        arg = arg->next;
    }

    if (add_newline) {
        emit_indent(out, indent);
        fputs("printf(\"\\n\");\n", out);
    }
}

static void emit_switch_stmt(FILE *out, ASTNode *node, int indent) {
    ASTNode *c;
    emit_indent(out, indent);
    fputs("switch (", out);
    emit_expr(out, node->left);
    fputs(") {\n", out);

    c = node->right;
    while (c) {
        if (c->kind == AST_IF && c->text && strcmp(c->text, "case") == 0) {
            emit_indent(out, indent + 1);
            fputs("case ", out);
            emit_expr(out, c->left);
            fputs(":\n", out);
            emit_stmt_list(out, c->right, indent + 2);
            emit_indent(out, indent + 2);
            fputs("break;\n", out);
        }
        c = c->next;
    }

    if (node->third && node->third->kind == AST_IF && node->third->text && strcmp(node->third->text, "default") == 0) {
        emit_indent(out, indent + 1);
        fputs("default:\n", out);
        emit_stmt_list(out, node->third->right, indent + 2);
        emit_indent(out, indent + 2);
        fputs("break;\n", out);
    }

    emit_indent(out, indent);
    fputs("}\n", out);
}

static void emit_stmt(FILE *out, ASTNode *node, int indent) {
    if (!node) return;

    switch (node->kind) {
        case AST_STMT_LIST:
            emit_indent(out, indent);
            fputs("{\n", out);
            emit_stmt_list(out, node->left, indent + 1);
            emit_indent(out, indent);
            fputs("}\n", out);
            return;

        case AST_DECL:
            if (node->text) {
                track_var_type(node->text, node->inferred_type);
            }
            emit_indent(out, indent);
            fprintf(out, "%s %s", c_type_name(node->inferred_type), node->text ? node->text : "v");
            if (node->left) {
                fputs(" = ", out);
                emit_expr(out, node->left);
            }
            fputs(";\n", out);
            if (node->left && node->inferred_type == TYPE_NUM && node->text) {
                emit_indent(out, indent);
                fprintf(out, "neb_add_value(\"%s\", %s);\n", node->text, node->text);
            }
            return;

        case AST_EXPR_STMT:
            emit_indent(out, indent);
            emit_expr(out, node->left);
            fputs(";\n", out);
            if (node->left && node->left->kind == AST_ASSIGN && node->left->left && is_num_identifier(node->left->left)) {
                emit_indent(out, indent);
                fprintf(out, "neb_add_value(\"%s\", %s);\n", node->left->left->text, node->left->left->text);
            } else if (node->left && node->left->kind == AST_UNARYOP && node->left->left && node->left->text &&
                       (strcmp(node->left->text, "++") == 0 || strcmp(node->left->text, "--") == 0 ||
                        strcmp(node->left->text, "post++") == 0 || strcmp(node->left->text, "post--") == 0) &&
                       is_num_identifier(node->left->left)) {
                emit_indent(out, indent);
                fprintf(out, "neb_add_value(\"%s\", %s);\n", node->left->left->text, node->left->left->text);
            }
            return;

        case AST_INPUT:
            if (node->text && strcmp(node->text, "input") != 0) {
                emit_indent(out, indent);
                fprintf(out, "scanf(\"%%d\", &%s);\n", node->text);
                if (tracked_var_type(node->text) == TYPE_NUM) {
                    emit_indent(out, indent);
                    fprintf(out, "neb_add_value(\"%s\", %s);\n", node->text, node->text);
                }
            }
            return;

        case AST_PRINT:
            emit_print_stmt(out, node, indent, !(node->text && strcmp(node->text, "print_inline") == 0));
            return;

        case AST_IF:
            if (node->text && strcmp(node->text, "switch") == 0) {
                emit_switch_stmt(out, node, indent);
                return;
            }
            emit_indent(out, indent);
            fputs("if (", out);
            emit_expr(out, node->left);
            fputs(") ", out);
            emit_stmt_as_block(out, node->right, indent);
            if (node->third) {
                emit_indent(out, indent);
                fputs("else ", out);
                emit_stmt_as_block(out, node->third, indent);
            }
            return;

        case AST_LOOP:
            emit_indent(out, indent);
            fputs("for (", out);
            if (node->left) emit_expr(out, node->left);
            fputs("; ", out);
            if (node->right) emit_expr(out, node->right);
            else fputs("1", out);
            fputs("; ", out);
            if (node->third) emit_expr(out, node->third);
            fputs(") ", out);
            emit_stmt_as_block(out, node->body, indent);
            return;

        case AST_WHILE:
            emit_indent(out, indent);
            fputs("while (", out);
            emit_expr(out, node->left);
            fputs(") ", out);
            emit_stmt_as_block(out, node->body, indent);
            return;

        case AST_DO_WHILE:
            emit_indent(out, indent);
            fputs("do ", out);
            emit_stmt_as_block(out, node->body, indent);
            emit_indent(out, indent);
            fputs("while (", out);
            emit_expr(out, node->left);
            fputs(");\n", out);
            return;

        case AST_FOR:
            emit_indent(out, indent);
            fputs("for (", out);
            if (node->left) emit_expr(out, node->left);
            fputs("; ", out);
            if (node->right) emit_expr(out, node->right);
            else fputs("1", out);
            fputs("; ", out);
            if (node->third) emit_expr(out, node->third);
            fputs(") ", out);
            emit_stmt_as_block(out, node->body, indent);
            return;

        case AST_UNARYOP:
            if (node->text && (strcmp(node->text, "give") == 0 || strcmp(node->text, "return") == 0)) {
                emit_indent(out, indent);
                fputs("return ", out);
                emit_expr(out, node->left);
                fputs(";\n", out);
                return;
            }
            if (node->text && strcmp(node->text, "break") == 0) {
                emit_indent(out, indent);
                fputs("break;\n", out);
                return;
            }
            if (node->text && strcmp(node->text, "continue") == 0) {
                emit_indent(out, indent);
                fputs("continue;\n", out);
                return;
            }
            emit_indent(out, indent);
            emit_expr(out, node);
            fputs(";\n", out);
            return;

        case AST_FUNC_CALL:
            if (node->body) return;
            emit_indent(out, indent);
            emit_expr(out, node);
            fputs(";\n", out);
            return;

        default:
            emit_indent(out, indent);
            emit_expr(out, node);
            fputs(";\n", out);
            return;
    }
}

static void emit_function_def(FILE *out, ASTNode *fn) {
    ASTNode *param;
    int first = 1;

    fprintf(out, "%s %s(", c_type_name(fn->inferred_type), fn->text ? fn->text : "fn");
    clear_tracked_vars();
    param = fn->left;
    while (param) {
        if (!first) fputs(", ", out);
        fprintf(out, "%s %s", c_type_name(param->inferred_type), param->text ? param->text : "p");
        if (param->text) {
            track_var_type(param->text, param->inferred_type);
        }
        first = 0;
        param = param->next;
    }
    if (first) {
        fputs("void", out);
    }
    fputs(") ", out);
    emit_stmt_as_block(out, fn->body, 0);
    fputc('\n', out);
    clear_tracked_vars();
}

int generate_c_code(ASTNode *root, const char *input_path) {
    FILE *out;
    char *path;
    ASTNode *curr;

    if (!root || root->kind != AST_PROGRAM) {
        return -1;
    }

    ensure_output_dir_exists();
    path = build_c_output_path(input_path);
    if (!path) {
        fprintf(stderr, "Code generation error: out of memory while building output path.\n");
        return -1;
    }

    out = fopen(path, "w");
    if (!out) {
        fprintf(stderr, "Code generation error: failed to open output file '%s'.\n", path);
        free(path);
        return -1;
    }

    fputs("#include <stdio.h>\n", out);
    fputs("#include <stdlib.h>\n", out);
    fputs("#include <string.h>\n", out);
    fputs("#include <math.h>\n", out);
    fputs("#include <stdbool.h>\n\n", out);
    fputs("#define MAX_HISTORY 10\n", out);
    fputs("typedef struct NebHistory {\n", out);
    fputs("    const char *name;\n", out);
    fputs("    int values[MAX_HISTORY];\n", out);
    fputs("    int head;\n", out);
    fputs("    int count;\n", out);
    fputs("    struct NebHistory *next;\n", out);
    fputs("} NebHistory;\n", out);
    fputs("static NebHistory *neb_history_table = NULL;\n", out);
    fputs("static NebHistory *neb_get_history(const char *name) {\n", out);
    fputs("    NebHistory *curr = neb_history_table;\n", out);
    fputs("    if (!name || !name[0]) return NULL;\n", out);
    fputs("    while (curr) {\n", out);
    fputs("        if (strcmp(curr->name, name) == 0) return curr;\n", out);
    fputs("        curr = curr->next;\n", out);
    fputs("    }\n", out);
    fputs("    curr = (NebHistory *)calloc(1, sizeof(NebHistory));\n", out);
    fputs("    if (!curr) return NULL;\n", out);
    fputs("    curr->name = name;\n", out);
    fputs("    curr->head = -1;\n", out);
    fputs("    curr->count = 0;\n", out);
    fputs("    curr->next = neb_history_table;\n", out);
    fputs("    neb_history_table = curr;\n", out);
    fputs("    return curr;\n", out);
    fputs("}\n", out);
    fputs("static void neb_add_value(const char *name, int value) {\n", out);
    fputs("    NebHistory *h = neb_get_history(name);\n", out);
    fputs("    if (!h) return;\n", out);
    fputs("    h->head = (h->head + 1) % MAX_HISTORY;\n", out);
    fputs("    h->values[h->head] = value;\n", out);
    fputs("    if (h->count < MAX_HISTORY) h->count++;\n", out);
    fputs("}\n", out);
    fputs("static int nebula_observe_current(const char *name, int steps_back) {\n", out);
    fputs("    int idx;\n", out);
    fputs("    NebHistory *h = neb_get_history(name);\n", out);
    fputs("    if (!h || h->count == 0 || steps_back < 0 || steps_back >= h->count) return 0;\n", out);
    fputs("    idx = (h->head - steps_back + MAX_HISTORY) % MAX_HISTORY;\n", out);
    fputs("    return h->values[idx];\n", out);
    fputs("}\n", out);
    fputs("static double neb_sin_deg(double x) { return sin(x * 3.14159265358979323846 / 180.0); }\n", out);
    fputs("static double neb_cos_deg(double x) { return cos(x * 3.14159265358979323846 / 180.0); }\n", out);
    fputs("static double neb_tan_deg(double x) { return tan(x * 3.14159265358979323846 / 180.0); }\n", out);
    fputs("static int even(int x) { return (x % 2) == 0; }\n", out);
    fputs("static int odd(int x) { return (x % 2) != 0; }\n", out);
    fputs("static int factorial(int n) { int i, f = 1; if (n < 0) return 0; for (i = 2; i <= n; i++) f *= i; return f; }\n", out);
    fputs("static int prime(int n) { int i; if (n < 2) return 0; for (i = 2; i * i <= n; i++) if (n % i == 0) return 0; return 1; }\n", out);
    fputs("static int palindrome_int(int n) { int x = n, rev = 0; if (n < 0) return 0; while (x > 0) { rev = rev * 10 + (x % 10); x /= 10; } return n == rev; }\n", out);
    fputs("static int palindrome_str(const char *s) { int l = 0; int r = (int)strlen(s) - 1; while (l < r) { if (s[l] != s[r]) return 0; l++; r--; } return 1; }\n", out);
    fputs("#define palindrome(x) _Generic((x), char*: palindrome_str, const char*: palindrome_str, default: palindrome_int)(x)\n", out);
    fputs("static int leap_year(int y) { return ((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0)); }\n", out);
    fputs("static double power(double base, double expv) { return pow(base, expv); }\n\n", out);

    curr = root->left;
    while (curr) {
        if (curr->kind == AST_FUNC_CALL && curr->body) {
            emit_function_def(out, curr);
        }
        curr = curr->next;
    }

    fputs("int main(void) {\n", out);
    curr = root->left;
    clear_tracked_vars();
    while (curr) {
        if (!(curr->kind == AST_FUNC_CALL && curr->body)) {
            emit_stmt(out, curr, 1);
        }
        curr = curr->next;
    }
    clear_tracked_vars();
    fputs("    return 0;\n", out);
    fputs("}\n", out);

    fclose(out);
    printf("Code generation: C output written to %s\n", path);
    free(path);
    return 0;
}
