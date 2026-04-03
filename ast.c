#include "ast.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_HISTORY 10

typedef struct {
    NebulaType type;
    int num;
    double dec;
    char ch;
    int boolean;
    char *str;
} RuntimeValue;

typedef struct RuntimeVar {
    char *name;
    RuntimeValue value;
    int scope;
    struct RuntimeVar *next;
} RuntimeVar;

typedef struct FunctionDef {
    char *name;
    ASTNode *params;
    ASTNode *body;
    NebulaType return_type;
    struct FunctionDef *next;
} FunctionDef;

typedef struct History {
    char *name;
    int values[MAX_HISTORY];
    int head;
    int count;
    struct History *next;
} History;

typedef struct {
    int has_return;
    int has_break;
    int has_continue;
    RuntimeValue return_value;
} ExecSignal;

static RuntimeVar *runtime_env = NULL;
static FunctionDef *function_table = NULL;
static History *history_table = NULL;
static int runtime_scope = 0;

static RuntimeValue make_default_value(NebulaType t);
static RuntimeValue runtime_copy_value(RuntimeValue v);
static RuntimeVar *runtime_lookup_var(const char *name);
static RuntimeVar *runtime_lookup_var_current_scope(const char *name);
static void runtime_enter_scope(void);
static void runtime_exit_scope(void);
static void runtime_declare_var(const char *name, RuntimeValue v);
static void runtime_set_var(const char *name, RuntimeValue v);
static RuntimeValue runtime_get_var(const char *name);
static int runtime_is_truthy(RuntimeValue v);
static RuntimeValue runtime_from_int(int n);
static RuntimeValue runtime_from_double(double d);
static RuntimeValue runtime_from_bool(int b);
static RuntimeValue runtime_cast_to(NebulaType t, RuntimeValue v);
static RuntimeValue runtime_eval_expr(ASTNode *node);
static ExecSignal runtime_exec_node(ASTNode *node);
static ExecSignal runtime_exec_list(ASTNode *node);
static void runtime_register_functions(ASTNode *root);
static FunctionDef *runtime_find_function(const char *name);
static RuntimeValue runtime_call_function(const char *name, ASTNode *args);
static int runtime_try_call_builtin(const char *name, ASTNode *args, RuntimeValue *out);
static int runtime_value_to_int(RuntimeValue v);
static double runtime_value_to_double(RuntimeValue v);
static History *get_history(const char *name);
static void add_value(History *history, int value);
static int nebula_observe(History *history, int steps_back, int *ok);
static const char *type_name(NebulaType t);
static const char *ast_kind_name(ASTNodeType kind);

ExprAttr make_expr(NebulaType type, ASTNode *node) {
    ExprAttr out;
    out.type = type;
    out.node = node;
    if (node) {
        node->inferred_type = type;
    }
    return out;
}

ASTNode *new_ast_node(ASTNodeType kind, const char *text) {
    ASTNode *node = (ASTNode *)calloc(1, sizeof(ASTNode));
    if (!node) {
        fprintf(stderr, "Fatal: out of memory while creating AST node.\n");
        exit(2);
    }
    node->kind = kind;
    node->inferred_type = TYPE_UNKNOWN;
    if (text) {
        node->text = strdup(text);
    }
    return node;
}

ASTNode *new_ast_unary(ASTNodeType kind, const char *op, ASTNode *child, NebulaType t) {
    ASTNode *node = new_ast_node(kind, op);
    node->left = child;
    node->inferred_type = t;
    return node;
}

ASTNode *new_ast_binary(ASTNodeType kind, const char *op, ASTNode *lhs, ASTNode *rhs, NebulaType t) {
    ASTNode *node = new_ast_node(kind, op);
    node->left = lhs;
    node->right = rhs;
    node->inferred_type = t;
    return node;
}

ASTNode *append_node(ASTNode *list, ASTNode *node) {
    ASTNode *curr;
    if (!list) {
        return node;
    }
    curr = list;
    while (curr->next) {
        curr = curr->next;
    }
    curr->next = node;
    return list;
}

static const char *type_name(NebulaType t) {
    switch (t) {
        case TYPE_NUM: return "num";
        case TYPE_DEC: return "dec";
        case TYPE_CHAR: return "char";
        case TYPE_BOOL: return "bool";
        case TYPE_VOID: return "void";
        default: return "unknown";
    }
}

static const char *ast_kind_name(ASTNodeType kind) {
    switch (kind) {
        case AST_PROGRAM: return "PROGRAM";
        case AST_STMT_LIST: return "STMT_LIST";
        case AST_DECL: return "DECL";
        case AST_ASSIGN: return "ASSIGN";
        case AST_EXPR_STMT: return "EXPR_STMT";
        case AST_IF: return "IF";
        case AST_LOOP: return "LOOP";
        case AST_WHILE: return "WHILE";
        case AST_DO_WHILE: return "DO_WHILE";
        case AST_FOR: return "FOR";
        case AST_PRINT: return "PRINT";
        case AST_INPUT: return "INPUT";
        case AST_BINOP: return "BINOP";
        case AST_UNARYOP: return "UNARYOP";
        case AST_LITERAL: return "LITERAL";
        case AST_IDENTIFIER: return "IDENTIFIER";
        case AST_FUNC_CALL: return "FUNC_CALL";
        default: return "UNKNOWN";
    }
}

void print_ast(const ASTNode *node, int indent) {
    const ASTNode *curr = node;
    int i;
    while (curr) {
        for (i = 0; i < indent; i++) {
            printf("  ");
        }
        printf("%s", ast_kind_name(curr->kind));
        if (curr->text) {
            printf("(%s)", curr->text);
        }
        if (curr->inferred_type != TYPE_UNKNOWN) {
            printf(" : %s", type_name(curr->inferred_type));
        }
        printf("\n");

        if (curr->left) {
            print_ast(curr->left, indent + 1);
        }
        if (curr->right) {
            print_ast(curr->right, indent + 1);
        }
        if (curr->third) {
            print_ast(curr->third, indent + 1);
        }
        if (curr->body) {
            print_ast(curr->body, indent + 1);
        }

        curr = curr->next;
    }
}

static RuntimeValue make_default_value(NebulaType t) {
    RuntimeValue v;
    v.type = t;
    v.num = 0;
    v.dec = 0.0;
    v.ch = '\0';
    v.boolean = 0;
    v.str = NULL;
    return v;
}

static RuntimeValue runtime_copy_value(RuntimeValue v) {
    RuntimeValue out = v;
    if (v.str) {
        out.str = strdup(v.str);
    }
    return out;
}

static RuntimeValue runtime_from_int(int n) {
    RuntimeValue v = make_default_value(TYPE_NUM);
    v.num = n;
    v.dec = (double)n;
    v.boolean = (n != 0);
    return v;
}

static RuntimeValue runtime_from_double(double d) {
    RuntimeValue v = make_default_value(TYPE_DEC);
    v.dec = d;
    v.num = (int)d;
    v.boolean = (d != 0.0);
    return v;
}

static RuntimeValue runtime_from_bool(int b) {
    RuntimeValue v = make_default_value(TYPE_BOOL);
    v.boolean = b ? 1 : 0;
    v.num = v.boolean;
    v.dec = (double)v.boolean;
    return v;
}

static RuntimeValue runtime_cast_to(NebulaType t, RuntimeValue v) {
    RuntimeValue out = make_default_value(t);
    if (t == TYPE_NUM) {
        if (v.type == TYPE_DEC) out.num = (int)v.dec;
        else if (v.type == TYPE_BOOL) out.num = v.boolean;
        else if (v.type == TYPE_CHAR) out.num = (unsigned char)v.ch;
        else out.num = v.num;
        out.dec = (double)out.num;
        out.boolean = (out.num != 0);
        return out;
    }
    if (t == TYPE_DEC) {
        if (v.type == TYPE_NUM) out.dec = (double)v.num;
        else if (v.type == TYPE_BOOL) out.dec = (double)v.boolean;
        else if (v.type == TYPE_CHAR) out.dec = (double)(unsigned char)v.ch;
        else out.dec = v.dec;
        out.num = (int)out.dec;
        out.boolean = (out.dec != 0.0);
        return out;
    }
    if (t == TYPE_BOOL) {
        out.boolean = runtime_is_truthy(v);
        out.num = out.boolean;
        out.dec = (double)out.boolean;
        return out;
    }
    if (t == TYPE_CHAR) {
        if (v.type == TYPE_NUM) out.ch = (char)v.num;
        else if (v.type == TYPE_DEC) out.ch = (char)((int)v.dec);
        else if (v.type == TYPE_BOOL) out.ch = (char)v.boolean;
        else out.ch = v.ch;
        out.num = (unsigned char)out.ch;
        out.dec = (double)out.num;
        out.boolean = (out.ch != '\0');
        return out;
    }
    return runtime_copy_value(v);
}

static RuntimeVar *runtime_lookup_var_current_scope(const char *name) {
    RuntimeVar *curr = runtime_env;
    while (curr) {
        if (curr->scope == runtime_scope && strcmp(curr->name, name) == 0) {
            return curr;
        }
        curr = curr->next;
    }
    return NULL;
}

static RuntimeVar *runtime_lookup_var(const char *name) {
    RuntimeVar *curr = runtime_env;
    RuntimeVar *best = NULL;
    while (curr) {
        if (strcmp(curr->name, name) == 0) {
            if (!best || curr->scope > best->scope) {
                best = curr;
            }
        }
        curr = curr->next;
    }
    return best;
}

static void runtime_enter_scope(void) {
    runtime_scope++;
}

static void runtime_exit_scope(void) {
    RuntimeVar *curr = runtime_env;
    RuntimeVar *prev = NULL;
    while (curr) {
        if (curr->scope == runtime_scope) {
            RuntimeVar *dead = curr;
            if (prev) prev->next = curr->next;
            else runtime_env = curr->next;
            curr = curr->next;
            if (dead->value.str) free(dead->value.str);
            free(dead->name);
            free(dead);
        } else {
            prev = curr;
            curr = curr->next;
        }
    }
    if (runtime_scope > 0) runtime_scope--;
}

static void runtime_declare_var(const char *name, RuntimeValue v) {
    RuntimeVar *var = runtime_lookup_var_current_scope(name);
    if (var) return;
    var = (RuntimeVar *)calloc(1, sizeof(RuntimeVar));
    if (!var) {
        fprintf(stderr, "Runtime fatal: out of memory.\n");
        exit(2);
    }
    var->name = strdup(name);
    var->value = runtime_copy_value(v);
    var->scope = runtime_scope;
    var->next = runtime_env;
    runtime_env = var;
}

static void runtime_set_var(const char *name, RuntimeValue v) {
    RuntimeVar *var = runtime_lookup_var(name);
    RuntimeValue casted;
    History *h;
    if (!var) {
        fprintf(stderr, "Runtime Error: assignment to undeclared variable '%s'\n", name);
        return;
    }
    casted = runtime_cast_to(var->value.type, v);
    if (var->value.str) free(var->value.str);
    var->value = casted;

    /* Track assignment history for nebula(variable, steps_back), num only. */
    if (var->value.type == TYPE_NUM) {
        h = get_history(name);
        add_value(h, var->value.num);
    }
}

static RuntimeValue runtime_get_var(const char *name) {
    RuntimeVar *var = runtime_lookup_var(name);
    if (!var) {
        fprintf(stderr, "Runtime Error: variable '%s' not found\n", name);
        return make_default_value(TYPE_UNKNOWN);
    }
    return runtime_copy_value(var->value);
}

static int runtime_is_truthy(RuntimeValue v) {
    if (v.type == TYPE_BOOL) return v.boolean != 0;
    if (v.type == TYPE_NUM) return v.num != 0;
    if (v.type == TYPE_DEC) return v.dec != 0.0;
    if (v.type == TYPE_CHAR) return v.ch != '\0';
    return 0;
}

static FunctionDef *runtime_find_function(const char *name) {
    FunctionDef *f = function_table;
    while (f) {
        if (strcmp(f->name, name) == 0) return f;
        f = f->next;
    }
    return NULL;
}

static void runtime_register_functions(ASTNode *root) {
    ASTNode *curr;
    function_table = NULL;
    if (!root || root->kind != AST_PROGRAM) return;
    curr = root->left;
    while (curr) {
        if (curr->kind == AST_FUNC_CALL && curr->body) {
            FunctionDef *f = (FunctionDef *)calloc(1, sizeof(FunctionDef));
            f->name = strdup(curr->text ? curr->text : "");
            f->params = curr->left;
            f->body = curr->body;
            f->return_type = curr->inferred_type;
            f->next = function_table;
            function_table = f;
        }
        curr = curr->next;
    }
}

static RuntimeValue runtime_call_function(const char *name, ASTNode *args) {
    FunctionDef *f = runtime_find_function(name);
    ASTNode *param;
    ASTNode *arg;
    ExecSignal sig;

    if (!f) {
        RuntimeValue out;
        if (runtime_try_call_builtin(name, args, &out)) {
            return out;
        }
    }

    if (!f) {
        fprintf(stderr, "Runtime Error: undefined function '%s'\n", name);
        return make_default_value(TYPE_UNKNOWN);
    }

    runtime_enter_scope();
    param = f->params;
    arg = args;
    while (param) {
        RuntimeValue av;
        RuntimeValue dv;
        if (!arg) {
            fprintf(stderr, "Runtime Error: too few arguments for function '%s'\n", name);
            break;
        }
        av = runtime_eval_expr(arg);
        dv = make_default_value(param->inferred_type);
        runtime_declare_var(param->text, dv);
        runtime_set_var(param->text, av);
        param = param->next;
        arg = arg->next;
    }
    if (arg) {
        fprintf(stderr, "Runtime Error: too many arguments for function '%s'\n", name);
    }

    sig = runtime_exec_node(f->body);
    runtime_exit_scope();
    if (sig.has_return) {
        return runtime_cast_to(f->return_type, sig.return_value);
    }
    return make_default_value(f->return_type);
}

static int runtime_value_to_int(RuntimeValue v) {
    if (v.type == TYPE_DEC) return (int)v.dec;
    if (v.type == TYPE_BOOL) return v.boolean;
    if (v.type == TYPE_CHAR) return (unsigned char)v.ch;
    return v.num;
}

static double runtime_value_to_double(RuntimeValue v) {
    if (v.type == TYPE_DEC) return v.dec;
    if (v.type == TYPE_BOOL) return (double)v.boolean;
    if (v.type == TYPE_CHAR) return (double)(unsigned char)v.ch;
    return (double)v.num;
}

static int runtime_try_call_builtin(const char *name, ASTNode *args, RuntimeValue *out) {
    RuntimeValue vals[4];
    int argc = 0;
    ASTNode *curr = args;
    int i;

    if (strcmp(name, "nebula") == 0 || strcmp(name, "Nebula") == 0) {
        ASTNode *id_node;
        ASTNode *step_node;
        RuntimeValue step_val;
        int k;
        History *h;
        int ok = 0;
        int observed = 0;

        if (!args || !args->next || args->next->next) {
            fprintf(stderr, "Runtime Error: nebula(variable, steps_back) expects exactly 2 arguments\n");
            *out = runtime_from_int(0);
            return 1;
        }

        id_node = args;
        step_node = args->next;
        if (id_node->kind != AST_IDENTIFIER || !id_node->text) {
            fprintf(stderr, "Runtime Error: nebula first argument must be a variable identifier\n");
            *out = runtime_from_int(0);
            return 1;
        }

        step_val = runtime_eval_expr(step_node);
        k = runtime_value_to_int(step_val);
        if (k < 0) {
            fprintf(stderr, "Runtime Error: nebula steps_back must be >= 0\n");
            *out = runtime_from_int(0);
            return 1;
        }

        h = get_history(id_node->text);
        observed = nebula_observe(h, k, &ok);
        if (!ok) {
            fprintf(stderr, "Runtime Warning: nebula(%s, %d) out of history range (available: %d)\n", id_node->text, k, h ? h->count-1 : 0);
            *out = runtime_from_int(0);
            return 1;
        }

        *out = runtime_from_int(observed);
        return 1;
    }

    while (curr && argc < 4) {
        vals[argc++] = runtime_eval_expr(curr);
        curr = curr->next;
    }
    if (curr) {
        fprintf(stderr, "Runtime Error: too many arguments for built-in '%s'\n", name);
        *out = make_default_value(TYPE_UNKNOWN);
        return 1;
    }

    if (strcmp(name, "even") == 0 || strcmp(name, "Even") == 0) {
        if (argc != 1) {
            fprintf(stderr, "Runtime Error: even(x) expects 1 argument\n");
            *out = make_default_value(TYPE_UNKNOWN);
            return 1;
        }
        *out = runtime_from_bool((runtime_value_to_int(vals[0]) % 2) == 0);
        return 1;
    }

    if (strcmp(name, "odd") == 0 || strcmp(name, "Odd") == 0) {
        if (argc != 1) {
            fprintf(stderr, "Runtime Error: odd(x) expects 1 argument\n");
            *out = make_default_value(TYPE_UNKNOWN);
            return 1;
        }
        *out = runtime_from_bool((runtime_value_to_int(vals[0]) % 2) != 0);
        return 1;
    }

    if (strcmp(name, "factorial") == 0 || strcmp(name, "Factorial") == 0) {
        int n;
        int fact;
        if (argc != 1) {
            fprintf(stderr, "Runtime Error: factorial(n) expects 1 argument\n");
            *out = make_default_value(TYPE_UNKNOWN);
            return 1;
        }
        n = runtime_value_to_int(vals[0]);
        if (n < 0) {
            fprintf(stderr, "Runtime Error: factorial undefined for negative numbers\n");
            *out = make_default_value(TYPE_UNKNOWN);
            return 1;
        }
        fact = 1;
        for (i = 2; i <= n; i++) {
            fact *= i;
        }
        *out = runtime_from_int(fact);
        return 1;
    }

    if (strcmp(name, "prime") == 0 || strcmp(name, "Prime") == 0) {
        int n;
        int is_prime = 1;
        if (argc != 1) {
            fprintf(stderr, "Runtime Error: prime(n) expects 1 argument\n");
            *out = make_default_value(TYPE_UNKNOWN);
            return 1;
        }
        n = runtime_value_to_int(vals[0]);
        if (n < 2) {
            *out = runtime_from_bool(0);
            return 1;
        }
        for (i = 2; i * i <= n; i++) {
            if (n % i == 0) {
                is_prime = 0;
                break;
            }
        }
        *out = runtime_from_bool(is_prime);
        return 1;
    }

    if (strcmp(name, "palindrome") == 0 || strcmp(name, "Palindrome") == 0) {
        int n;
        int x;
        int rev = 0;
        if (argc != 1) {
            fprintf(stderr, "Runtime Error: palindrome(x) expects 1 argument\n");
            *out = make_default_value(TYPE_UNKNOWN);
            return 1;
        }
        if (vals[0].str) {
            const char *s = vals[0].str;
            int left;
            int right;
            int ok = 1;
            int len = (int)strlen(s);
            if (len >= 2 && s[0] == '"' && s[len - 1] == '"') {
                s = s + 1;
                len -= 2;
            }
            left = 0;
            right = len - 1;
            while (left < right) {
                if (s[left] != s[right]) {
                    ok = 0;
                    break;
                }
                left++;
                right--;
            }
            *out = runtime_from_bool(ok);
            return 1;
        }
        n = runtime_value_to_int(vals[0]);
        if (n < 0) {
            *out = runtime_from_bool(0);
            return 1;
        }
        x = n;
        while (x > 0) {
            rev = rev * 10 + (x % 10);
            x /= 10;
        }
        *out = runtime_from_bool(n == rev);
        return 1;
    }

    if (strcmp(name, "leap_year") == 0 || strcmp(name, "leapyear") == 0 || strcmp(name, "LeapYear") == 0) {
        int y;
        int leap;
        if (argc != 1) {
            fprintf(stderr, "Runtime Error: leap_year(y) expects 1 argument\n");
            *out = make_default_value(TYPE_UNKNOWN);
            return 1;
        }
        y = runtime_value_to_int(vals[0]);
        leap = ((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0));
        *out = runtime_from_bool(leap);
        return 1;
    }

    if (strcmp(name, "power") == 0 || strcmp(name, "Power") == 0) {
        double base;
        double expv;
        if (argc != 2) {
            fprintf(stderr, "Runtime Error: power(base, exp) expects 2 arguments\n");
            *out = make_default_value(TYPE_UNKNOWN);
            return 1;
        }
        base = runtime_value_to_double(vals[0]);
        expv = runtime_value_to_double(vals[1]);
        *out = runtime_from_double(pow(base, expv));
        return 1;
    }

    if (strcmp(name, "sin") == 0 || strcmp(name, "cos") == 0 || strcmp(name, "tan") == 0) {
        double x;
        double rad;
        if (argc != 1) {
            fprintf(stderr, "Runtime Error: %s(x) expects 1 argument\n", name);
            *out = make_default_value(TYPE_UNKNOWN);
            return 1;
        }
        x = runtime_value_to_double(vals[0]);
        rad = x * 3.14159265358979323846 / 180.0;
        if (strcmp(name, "sin") == 0) {
            *out = runtime_from_double(sin(rad));
        } else if (strcmp(name, "cos") == 0) {
            *out = runtime_from_double(cos(rad));
        } else {
            *out = runtime_from_double(tan(rad));
        }
        return 1;
    }

    return 0;
}

static RuntimeValue runtime_eval_expr(ASTNode *node) {
    RuntimeValue l;
    RuntimeValue r;
    RuntimeValue out;
    const char *op;

    if (!node) return make_default_value(TYPE_UNKNOWN);

    switch (node->kind) {
        case AST_LITERAL:
            if (!node->text) return make_default_value(TYPE_UNKNOWN);
            if (strcmp(node->text, "true") == 0) return runtime_from_bool(1);
            if (strcmp(node->text, "false") == 0) return runtime_from_bool(0);
            if (node->text[0] == '\'' && strlen(node->text) >= 3) {
                out = make_default_value(TYPE_CHAR);
                out.ch = node->text[1];
                out.num = (unsigned char)out.ch;
                out.dec = (double)out.num;
                out.boolean = (out.ch != '\0');
                return out;
            }
            if (node->text[0] == '"') {
                out = make_default_value(TYPE_UNKNOWN);
                out.str = strdup(node->text);
                return out;
            }
            if (strchr(node->text, '.') || strchr(node->text, 'e') || strchr(node->text, 'E')) {
                return runtime_from_double(strtod(node->text, NULL));
            }
            return runtime_from_int((int)strtol(node->text, NULL, 10));

        case AST_IDENTIFIER:
            return runtime_get_var(node->text);

        case AST_ASSIGN:
            r = runtime_eval_expr(node->right);
            runtime_set_var(node->left->text, r);
            return runtime_get_var(node->left->text);

        case AST_INPUT:
            if (node->text && strcmp(node->text, "input") != 0) {
                RuntimeVar *var = runtime_lookup_var(node->text);
                if (!var) {
                    fprintf(stderr, "Runtime Error: input target '%s' undeclared\n", node->text);
                    return make_default_value(TYPE_UNKNOWN);
                }
                if (var->value.type == TYPE_DEC) {
                    double d = 0.0;
                    scanf("%lf", &d);
                    runtime_set_var(node->text, runtime_from_double(d));
                } else if (var->value.type == TYPE_CHAR) {
                    char c = '\0';
                    scanf(" %c", &c);
                    out = make_default_value(TYPE_CHAR);
                    out.ch = c;
                    out.num = (unsigned char)c;
                    out.dec = (double)out.num;
                    out.boolean = (c != '\0');
                    runtime_set_var(node->text, out);
                } else if (var->value.type == TYPE_BOOL) {
                    int b = 0;
                    scanf("%d", &b);
                    runtime_set_var(node->text, runtime_from_bool(b != 0));
                } else {
                    int n = 0;
                    scanf("%d", &n);
                    runtime_set_var(node->text, runtime_from_int(n));
                }
                return runtime_get_var(node->text);
            }
            {
                int n = 0;
                scanf("%d", &n);
                return runtime_from_int(n);
            }

        case AST_FUNC_CALL:
            if (node->body) {
                return make_default_value(TYPE_UNKNOWN);
            }
            return runtime_call_function(node->text ? node->text : "", node->left);

        case AST_UNARYOP:
            op = node->text ? node->text : "";
            if (strcmp(op, "+") == 0) return runtime_eval_expr(node->left);
            if (strcmp(op, "-") == 0) {
                l = runtime_eval_expr(node->left);
                if (l.type == TYPE_DEC) return runtime_from_double(-l.dec);
                return runtime_from_int(-l.num);
            }
            if (strcmp(op, "!") == 0) {
                l = runtime_eval_expr(node->left);
                return runtime_from_bool(!runtime_is_truthy(l));
            }
            if (strcmp(op, "~") == 0) {
                l = runtime_eval_expr(node->left);
                return runtime_from_int(~l.num);
            }
            if (strcmp(op, "++") == 0 || strcmp(op, "--") == 0 || strcmp(op, "post++") == 0 || strcmp(op, "post--") == 0) {
                ASTNode *id = node->left;
                RuntimeValue cur = runtime_eval_expr(id);
                RuntimeValue old = cur;
                int delta = (strstr(op, "--") != NULL) ? -1 : 1;
                if (cur.type == TYPE_DEC) cur.dec += delta;
                else cur.num += delta;
                runtime_set_var(id->text, cur);
                if (strncmp(op, "post", 4) == 0) return old;
                return runtime_get_var(id->text);
            }
            return make_default_value(TYPE_UNKNOWN);

        case AST_BINOP:
            op = node->text ? node->text : "";
            if (strcmp(op, "[]") == 0) return runtime_eval_expr(node->left);
            l = runtime_eval_expr(node->left);
            r = runtime_eval_expr(node->right);
            if (strcmp(op, "+") == 0) {
                if (l.type == TYPE_DEC || r.type == TYPE_DEC) {
                    return runtime_from_double((l.type == TYPE_DEC ? l.dec : l.num) + (r.type == TYPE_DEC ? r.dec : r.num));
                }
                return runtime_from_int(l.num + r.num);
            }
            if (strcmp(op, "-") == 0) {
                if (l.type == TYPE_DEC || r.type == TYPE_DEC) {
                    return runtime_from_double((l.type == TYPE_DEC ? l.dec : l.num) - (r.type == TYPE_DEC ? r.dec : r.num));
                }
                return runtime_from_int(l.num - r.num);
            }
            if (strcmp(op, "*") == 0) {
                if (l.type == TYPE_DEC || r.type == TYPE_DEC) {
                    return runtime_from_double((l.type == TYPE_DEC ? l.dec : l.num) * (r.type == TYPE_DEC ? r.dec : r.num));
                }
                return runtime_from_int(l.num * r.num);
            }
            if (strcmp(op, "/") == 0) {
                double rv = (r.type == TYPE_DEC ? r.dec : (double)r.num);
                if (rv == 0.0) {
                    fprintf(stderr, "Runtime Error: division by zero\n");
                    return make_default_value(TYPE_UNKNOWN);
                }
                if (l.type == TYPE_DEC || r.type == TYPE_DEC) {
                    return runtime_from_double((l.type == TYPE_DEC ? l.dec : l.num) / rv);
                }
                return runtime_from_int(l.num / r.num);
            }
            if (strcmp(op, "<") == 0) return runtime_from_bool((l.type == TYPE_DEC ? l.dec : l.num) < (r.type == TYPE_DEC ? r.dec : r.num));
            if (strcmp(op, ">") == 0) return runtime_from_bool((l.type == TYPE_DEC ? l.dec : l.num) > (r.type == TYPE_DEC ? r.dec : r.num));
            if (strcmp(op, "<=") == 0) return runtime_from_bool((l.type == TYPE_DEC ? l.dec : l.num) <= (r.type == TYPE_DEC ? r.dec : r.num));
            if (strcmp(op, ">=") == 0) return runtime_from_bool((l.type == TYPE_DEC ? l.dec : l.num) >= (r.type == TYPE_DEC ? r.dec : r.num));
            if (strcmp(op, "==") == 0) return runtime_from_bool((l.type == TYPE_DEC ? l.dec : l.num) == (r.type == TYPE_DEC ? r.dec : r.num));
            if (strcmp(op, "!=") == 0) return runtime_from_bool((l.type == TYPE_DEC ? l.dec : l.num) != (r.type == TYPE_DEC ? r.dec : r.num));
            if (strcmp(op, "&&") == 0) return runtime_from_bool(runtime_is_truthy(l) && runtime_is_truthy(r));
            if (strcmp(op, "||") == 0) return runtime_from_bool(runtime_is_truthy(l) || runtime_is_truthy(r));
            if (strcmp(op, "&") == 0) return runtime_from_int(l.num & r.num);
            if (strcmp(op, "|") == 0) return runtime_from_int(l.num | r.num);
            if (strcmp(op, "^") == 0) return runtime_from_int(l.num ^ r.num);
            if (strcmp(op, "<<") == 0) return runtime_from_int(l.num << r.num);
            if (strcmp(op, ">>") == 0) return runtime_from_int(l.num >> r.num);
            return make_default_value(TYPE_UNKNOWN);

        case AST_IF:
            if (node->text && strcmp(node->text, "?:") == 0) {
                return runtime_is_truthy(runtime_eval_expr(node->left)) ? runtime_eval_expr(node->right) : runtime_eval_expr(node->third);
            }
            return make_default_value(TYPE_UNKNOWN);

        default:
            return make_default_value(TYPE_UNKNOWN);
    }
}

static ExecSignal runtime_exec_list(ASTNode *node) {
    ExecSignal sig;
    ASTNode *curr = node;
    sig.has_return = 0;
    sig.has_break = 0;
    sig.has_continue = 0;
    sig.return_value = make_default_value(TYPE_VOID);
    while (curr) {
        sig = runtime_exec_node(curr);
        if (sig.has_return || sig.has_break || sig.has_continue) {
            return sig;
        }
        curr = curr->next;
    }
    return sig;
}

static ExecSignal runtime_exec_node(ASTNode *node) {
    ExecSignal sig;
    sig.has_return = 0;
    sig.has_break = 0;
    sig.has_continue = 0;
    sig.return_value = make_default_value(TYPE_VOID);

    if (!node) return sig;

    switch (node->kind) {
        case AST_PROGRAM:
            return runtime_exec_list(node->left);

        case AST_STMT_LIST:
            runtime_enter_scope();
            sig = runtime_exec_list(node->left);
            runtime_exit_scope();
            return sig;

        case AST_DECL: {
            RuntimeValue v = make_default_value(node->inferred_type);
            runtime_declare_var(node->text, v);
            if (node->left) {
                RuntimeValue init = runtime_eval_expr(node->left);
                runtime_set_var(node->text, init);
            }
            return sig;
        }

        case AST_EXPR_STMT:
            (void)runtime_eval_expr(node->left);
            return sig;

        case AST_INPUT:
            (void)runtime_eval_expr(node);
            return sig;

        case AST_PRINT: {
            ASTNode *arg = node->left;
            int first = 1;
            while (arg) {
                RuntimeValue v = runtime_eval_expr(arg);
                if (!first) printf(" ");
                if (v.str) {
                    size_t len = strlen(v.str);
                    if (len >= 2 && v.str[0] == '"' && v.str[len - 1] == '"') {
                        printf("%.*s", (int)(len - 2), v.str + 1);
                    } else {
                        printf("%s", v.str);
                    }
                } else if (v.type == TYPE_DEC) {
                    printf("%g", v.dec);
                } else if (v.type == TYPE_CHAR) {
                    printf("%c", v.ch);
                } else if (v.type == TYPE_BOOL) {
                    printf("%s", v.boolean ? "true" : "false");
                } else {
                    printf("%d", v.num);
                }
                first = 0;
                arg = arg->next;
            }
            printf("\n");
            return sig;
        }

        case AST_IF:
            if (node->text && strcmp(node->text, "switch") == 0) {
                RuntimeValue target = runtime_eval_expr(node->left);
                ASTNode *c = node->right;
                int matched = 0;
                while (c) {
                    if (c->kind == AST_IF && c->text && strcmp(c->text, "case") == 0) {
                        RuntimeValue cv = runtime_eval_expr(c->left);
                        int eq = (target.type == TYPE_DEC || cv.type == TYPE_DEC)
                            ? ((target.type == TYPE_DEC ? target.dec : target.num) == (cv.type == TYPE_DEC ? cv.dec : cv.num))
                            : (target.num == cv.num);
                        if (eq) {
                            matched = 1;
                            sig = runtime_exec_list(c->right);
                            if (sig.has_return || sig.has_break || sig.has_continue) return sig;
                            break;
                        }
                    }
                    c = c->next;
                }
                if (!matched && node->third) {
                    sig = runtime_exec_list(node->third->right);
                }
                return sig;
            }
            if (runtime_is_truthy(runtime_eval_expr(node->left))) {
                return runtime_exec_node(node->right);
            }
            if (node->third) {
                return runtime_exec_node(node->third);
            }
            return sig;

        case AST_LOOP:
            if (node->left) (void)runtime_eval_expr(node->left);
            while (1) {
                if (node->right && !runtime_is_truthy(runtime_eval_expr(node->right))) break;
                sig = runtime_exec_node(node->body);
                if (sig.has_return) return sig;
                if (sig.has_break) { sig.has_break = 0; break; }
                if (node->third) (void)runtime_eval_expr(node->third);
                if (sig.has_continue) sig.has_continue = 0;
            }
            return sig;

        case AST_WHILE:
            while (runtime_is_truthy(runtime_eval_expr(node->left))) {
                sig = runtime_exec_node(node->body);
                if (sig.has_return) return sig;
                if (sig.has_break) { sig.has_break = 0; break; }
                if (sig.has_continue) sig.has_continue = 0;
            }
            return sig;

        case AST_DO_WHILE:
            do {
                sig = runtime_exec_node(node->body);
                if (sig.has_return) return sig;
                if (sig.has_break) { sig.has_break = 0; break; }
                if (sig.has_continue) sig.has_continue = 0;
            } while (runtime_is_truthy(runtime_eval_expr(node->left)));
            return sig;

        case AST_FOR:
            if (node->left) (void)runtime_eval_expr(node->left);
            while (1) {
                if (node->right && !runtime_is_truthy(runtime_eval_expr(node->right))) break;
                sig = runtime_exec_node(node->body);
                if (sig.has_return) return sig;
                if (sig.has_break) { sig.has_break = 0; break; }
                if (node->third) (void)runtime_eval_expr(node->third);
                if (sig.has_continue) sig.has_continue = 0;
            }
            return sig;

        case AST_UNARYOP:
            if (node->text && (strcmp(node->text, "give") == 0 || strcmp(node->text, "return") == 0)) {
                sig.has_return = 1;
                sig.return_value = runtime_eval_expr(node->left);
                return sig;
            }
            if (node->text && strcmp(node->text, "break") == 0) {
                sig.has_break = 1;
                return sig;
            }
            if (node->text && strcmp(node->text, "continue") == 0) {
                sig.has_continue = 1;
                return sig;
            }
            (void)runtime_eval_expr(node);
            return sig;

        case AST_FUNC_CALL:
            if (node->body) return sig;
            (void)runtime_eval_expr(node);
            return sig;

        default:
            (void)runtime_eval_expr(node);
            return sig;
    }
}

void execute_program(ASTNode *root) {
    ASTNode *curr;
    runtime_register_functions(root);
    runtime_scope = 0;
    runtime_env = NULL;
    history_table = NULL;

    curr = root ? root->left : NULL;
    while (curr) {
        if (!(curr->kind == AST_FUNC_CALL && curr->body)) {
            ExecSignal sig = runtime_exec_node(curr);
            if (sig.has_return) {
                break;
            }
        }
        curr = curr->next;
    }
}

static History *get_history(const char *name) {
    History *curr = history_table;
    while (curr) {
        if (strcmp(curr->name, name) == 0) {
            return curr;
        }
        curr = curr->next;
    }

    curr = (History *)calloc(1, sizeof(History));
    if (!curr) {
        fprintf(stderr, "Runtime fatal: out of memory while creating history.\n");
        exit(2);
    }
    curr->name = strdup(name);
    curr->head = -1;
    curr->count = 0;
    curr->next = history_table;
    history_table = curr;
    return curr;
}

static void add_value(History *history, int value) {
    if (!history) {
        return;
    }
    history->head = (history->head + 1) % MAX_HISTORY;
    history->values[history->head] = value;
    if (history->count < MAX_HISTORY) {
        history->count++;
    }
}

static int nebula_observe(History *history, int steps_back, int *ok) {
    int idx;
    if (ok) {
        *ok = 0;
    }
    if (!history || history->count == 0 || steps_back < 0 || steps_back >= history->count) {
        return 0;
    }
    idx = (history->head - steps_back + MAX_HISTORY) % MAX_HISTORY;
    if (ok) {
        *ok = 1;
    }
    return history->values[idx];
}
