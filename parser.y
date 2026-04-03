%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

extern int yylex(void);
extern int line_no;
extern char *yytext;
extern FILE *yyin;
extern int nebula_lex_error;

int nebula_parse_error = 0;
int semantic_error_count = 0;

typedef enum {
    TYPE_UNKNOWN = 0,
    TYPE_NUM,
    TYPE_DEC,
    TYPE_CHAR,
    TYPE_BOOL,
    TYPE_VOID
} NebulaType;

typedef struct Symbol {
    char *name;
    NebulaType type;
    int scope;
    struct Symbol *next;
} Symbol;

static Symbol *symbol_table = NULL;
static int current_scope = 0;
static NebulaType current_decl_type = TYPE_UNKNOWN;

static const char *type_name(NebulaType t);
static int is_numeric(NebulaType t);
static int is_truthy_compatible(NebulaType t);
static void semantic_error(int line, const char *fmt, ...);
static void enter_scope(void);
static void exit_scope(void);
static Symbol *lookup_symbol(const char *name);
static Symbol *lookup_symbol_current_scope(const char *name);
static void declare_variable(const char *name, NebulaType type, int line);
static NebulaType resolve_identifier_type(const char *name, int line);
static int is_assignment_compatible(NebulaType lhs, NebulaType rhs);
static NebulaType arithmetic_result_type(NebulaType lhs, NebulaType rhs, const char *op, int line);
static NebulaType equality_result_type(NebulaType lhs, NebulaType rhs, const char *op, int line);
static NebulaType relational_result_type(NebulaType lhs, NebulaType rhs, const char *op, int line);
static NebulaType logical_result_type(NebulaType lhs, NebulaType rhs, const char *op, int line);
static NebulaType bitwise_result_type(NebulaType lhs, NebulaType rhs, const char *op, int line);
static NebulaType unary_plus_minus_type(NebulaType t, const char *op, int line);
static NebulaType unary_not_type(NebulaType t, int line);
static NebulaType unary_bitnot_type(NebulaType t, int line);
static NebulaType incdec_type(NebulaType t, const char *op, int line);
static void check_condition_type(NebulaType cond_type, int line, const char *kw);

void yyerror(const char *msg);
%}

%define parse.error verbose

%union {
    int num_val;
    double dec_val;
    char char_val;
    char *str_val;
    int type_val;
}

/* ---------- Typed literal/identifier tokens ---------- */
%token <num_val> NUM_LITERAL
%token <dec_val> DEC_LITERAL
%token <char_val> CHAR_LITERAL
%token <str_val> STRING_LITERAL IDENTIFIER

/* ---------- Keywords ---------- */
%token INT FLOAT DOUBLE NUM DEC CHAR BOOL VOID STRUCT ENUM
%token IF ELSE SWITCH CASE DEFAULT WHILE DO FOR
%token BREAK CONTINUE RETURN FUNCTION
%token WHEN OTHERWISE LOOP GIVE PRINT INPUT
%token TRUE FALSE

/* ---------- Operators ---------- */
%token INC DECREMENT
%token EQ NEQ LE GE LT GT ASSIGN
%token AND OR
%token BIT_AND BIT_OR BIT_XOR BIT_NOT
%token LSHIFT RSHIFT
%token PLUS MINUS MUL DIV
%token NOT
%token QMARK COLON
%token ARROW_R ARROW_L

/* ---------- Delimiters ---------- */
%token SEMICOLON COMMA
%token LPAREN RPAREN LBRACE RBRACE LBRACKET RBRACKET

/* ---------- Error token from lexer ---------- */
%token INVALID

%type <type_val> type_spec
%type <type_val> opt_expr expression assignment_expr conditional_expr
%type <type_val> logical_or_expr logical_and_expr
%type <type_val> bitwise_or_expr bitwise_xor_expr bitwise_and_expr
%type <type_val> equality_expr relational_expr shift_expr
%type <type_val> additive_expr multiplicative_expr unary_expr postfix_expr primary_expr

/* ---------- Precedence / associativity ---------- */
%nonassoc LOWER_THAN_OTHERWISE
%nonassoc OTHERWISE ELSE

%right ASSIGN
%right QMARK COLON
%left OR
%left AND
%left BIT_OR
%left BIT_XOR
%left BIT_AND
%left EQ NEQ
%left LT GT LE GE
%left LSHIFT RSHIFT
%left PLUS MINUS
%left MUL DIV
%right NOT BIT_NOT UMINUS UPLUS
%left INC DECREMENT

%start program

%%

program
    : translation_unit
    ;

translation_unit
    : /* empty */
    | translation_unit external_decl
    ;

external_decl
    : function_def
    | statement
    ;

function_def
    : FUNCTION type_spec IDENTIFIER LPAREN parameter_list_opt RPAREN compound_stmt
      {
          free($3);
      }
    ;

parameter_list_opt
    : /* empty */
    | parameter_list
    ;

parameter_list
    : parameter
    | parameter_list COMMA parameter
    ;

parameter
    : type_spec IDENTIFIER
        {
            free($2);
        }
    ;

type_spec
    : NUM        { $$ = TYPE_NUM; }
    | DEC        { $$ = TYPE_DEC; }
    | CHAR       { $$ = TYPE_CHAR; }
    | BOOL       { $$ = TYPE_BOOL; }
    | VOID       { $$ = TYPE_VOID; }
    | INT        { $$ = TYPE_NUM; }
    | FLOAT      { $$ = TYPE_DEC; }
    | DOUBLE     { $$ = TYPE_DEC; }
    ;

compound_stmt
    : LBRACE
      {
          enter_scope();
      }
      stmt_list_opt RBRACE
      {
          exit_scope();
      }
    ;

stmt_list_opt
    : /* empty */
    | stmt_list
    ;

stmt_list
    : statement
    | stmt_list statement
    ;

statement
    : declaration_stmt
    | expression_stmt
    | selection_stmt
    | loop_stmt
    | jump_stmt
    | io_stmt
    | compound_stmt
    | error SEMICOLON
        {
            fprintf(stderr, "Recovered from syntax error at line %d.\n", line_no);
            yyerrok;
        }
    ;

declaration_stmt
    : type_spec
      {
          current_decl_type = (NebulaType)$1;
      }
      init_declarator_list SEMICOLON
    ;

init_declarator_list
    : init_declarator
    | init_declarator_list COMMA init_declarator
    ;

init_declarator
    : IDENTIFIER
        {
            declare_variable($1, current_decl_type, line_no);
            free($1);
        }
    | IDENTIFIER ASSIGN expression
        {
            declare_variable($1, current_decl_type, line_no);
            if (!is_assignment_compatible(current_decl_type, (NebulaType)$3)) {
                semantic_error(line_no, "Type mismatch in declaration assignment (%s = %s)", type_name(current_decl_type), type_name((NebulaType)$3));
            }
            free($1);
        }
    ;

expression_stmt
    : expression SEMICOLON
    | SEMICOLON
    ;

selection_stmt
        : WHEN LPAREN expression RPAREN statement %prec LOWER_THAN_OTHERWISE
            {
                    check_condition_type((NebulaType)$3, line_no, "when");
            }
        | WHEN LPAREN expression RPAREN statement OTHERWISE statement
            {
                    check_condition_type((NebulaType)$3, line_no, "when");
            }
        | IF LPAREN expression RPAREN statement %prec LOWER_THAN_OTHERWISE
            {
                    check_condition_type((NebulaType)$3, line_no, "if");
            }
        | IF LPAREN expression RPAREN statement ELSE statement
            {
                    check_condition_type((NebulaType)$3, line_no, "if");
            }
    | SWITCH LPAREN expression RPAREN LBRACE case_clauses_opt default_clause_opt RBRACE
    ;

case_clauses_opt
    : /* empty */
    | case_clauses_opt case_clause
    ;

case_clause
    : CASE expression COLON stmt_list_opt
    ;

default_clause_opt
    : /* empty */
    | DEFAULT COLON stmt_list_opt
    ;

loop_stmt
        : LOOP LPAREN opt_expr SEMICOLON opt_expr SEMICOLON opt_expr RPAREN statement
            {
                    if ((NebulaType)$5 != TYPE_UNKNOWN) {
                            check_condition_type((NebulaType)$5, line_no, "loop");
                    }
            }
        | WHILE LPAREN expression RPAREN statement
            {
                    check_condition_type((NebulaType)$3, line_no, "while");
            }
    | DO statement WHILE LPAREN expression RPAREN SEMICOLON
      {
          check_condition_type((NebulaType)$5, line_no, "do-while");
      }
        | FOR LPAREN opt_expr SEMICOLON opt_expr SEMICOLON opt_expr RPAREN statement
            {
                    if ((NebulaType)$5 != TYPE_UNKNOWN) {
                            check_condition_type((NebulaType)$5, line_no, "for");
                    }
            }
    ;

opt_expr
    : /* empty */     { $$ = TYPE_UNKNOWN; }
    | expression      { $$ = $1; }
    ;

jump_stmt
    : GIVE expression SEMICOLON
    | RETURN expression SEMICOLON
    | BREAK SEMICOLON
    | CONTINUE SEMICOLON
    ;

io_stmt
    : PRINT LPAREN print_arg_list_opt RPAREN SEMICOLON
    | INPUT LPAREN IDENTIFIER RPAREN SEMICOLON
        {
            (void)resolve_identifier_type($3, line_no);
            free($3);
        }
    ;

print_arg_list_opt
    : /* empty */
    | print_arg_list
    ;

print_arg_list
    : print_arg
    | print_arg_list COMMA print_arg
    ;

print_arg
    : expression
    ;

function_call
    : IDENTIFIER LPAREN argument_list_opt RPAREN
        {
            /* Function symbols will be handled in later phases; keep type unknown for now. */
            free($1);
        }
    ;

argument_list_opt
    : /* empty */
    | argument_list
    ;

argument_list
    : expression
    | argument_list COMMA expression
    ;

expression
    : assignment_expr
        { $$ = $1; }
    ;

assignment_expr
    : conditional_expr
        { $$ = $1; }
    | IDENTIFIER ASSIGN assignment_expr
        {
            NebulaType lhs = resolve_identifier_type($1, line_no);
            NebulaType rhs = (NebulaType)$3;
            if (lhs != TYPE_UNKNOWN && rhs != TYPE_UNKNOWN && !is_assignment_compatible(lhs, rhs)) {
                semantic_error(line_no, "Type mismatch in assignment (%s = %s)", type_name(lhs), type_name(rhs));
            }
            $$ = lhs;
            free($1);
        }
    ;

conditional_expr
    : logical_or_expr
        { $$ = $1; }
    | logical_or_expr QMARK expression COLON conditional_expr
        {
            check_condition_type((NebulaType)$1, line_no, "?:");
            if (is_assignment_compatible((NebulaType)$3, (NebulaType)$5)) {
                $$ = $3;
            } else if (is_assignment_compatible((NebulaType)$5, (NebulaType)$3)) {
                $$ = $5;
            } else {
                semantic_error(line_no, "Type mismatch in conditional expression (%s : %s)", type_name((NebulaType)$3), type_name((NebulaType)$5));
                $$ = TYPE_UNKNOWN;
            }
        }
    ;

logical_or_expr
    : logical_and_expr
        { $$ = $1; }
    | logical_or_expr OR logical_and_expr
        { $$ = logical_result_type((NebulaType)$1, (NebulaType)$3, "||", line_no); }
    ;

logical_and_expr
    : bitwise_or_expr
        { $$ = $1; }
    | logical_and_expr AND bitwise_or_expr
        { $$ = logical_result_type((NebulaType)$1, (NebulaType)$3, "&&", line_no); }
    ;

bitwise_or_expr
    : bitwise_xor_expr
        { $$ = $1; }
    | bitwise_or_expr BIT_OR bitwise_xor_expr
        { $$ = bitwise_result_type((NebulaType)$1, (NebulaType)$3, "|", line_no); }
    ;

bitwise_xor_expr
    : bitwise_and_expr
        { $$ = $1; }
    | bitwise_xor_expr BIT_XOR bitwise_and_expr
        { $$ = bitwise_result_type((NebulaType)$1, (NebulaType)$3, "^", line_no); }
    ;

bitwise_and_expr
    : equality_expr
        { $$ = $1; }
    | bitwise_and_expr BIT_AND equality_expr
        { $$ = bitwise_result_type((NebulaType)$1, (NebulaType)$3, "&", line_no); }
    ;

equality_expr
    : relational_expr
        { $$ = $1; }
    | equality_expr EQ relational_expr
        { $$ = equality_result_type((NebulaType)$1, (NebulaType)$3, "==", line_no); }
    | equality_expr NEQ relational_expr
        { $$ = equality_result_type((NebulaType)$1, (NebulaType)$3, "!=", line_no); }
    ;

relational_expr
    : shift_expr
        { $$ = $1; }
    | relational_expr LT shift_expr
        { $$ = relational_result_type((NebulaType)$1, (NebulaType)$3, "<", line_no); }
    | relational_expr GT shift_expr
        { $$ = relational_result_type((NebulaType)$1, (NebulaType)$3, ">", line_no); }
    | relational_expr LE shift_expr
        { $$ = relational_result_type((NebulaType)$1, (NebulaType)$3, "<=", line_no); }
    | relational_expr GE shift_expr
        { $$ = relational_result_type((NebulaType)$1, (NebulaType)$3, ">=", line_no); }
    ;

shift_expr
    : additive_expr
        { $$ = $1; }
    | shift_expr LSHIFT additive_expr
        { $$ = bitwise_result_type((NebulaType)$1, (NebulaType)$3, "<<", line_no); }
    | shift_expr RSHIFT additive_expr
        { $$ = bitwise_result_type((NebulaType)$1, (NebulaType)$3, ">>", line_no); }
    ;

additive_expr
    : multiplicative_expr
        { $$ = $1; }
    | additive_expr PLUS multiplicative_expr
        { $$ = arithmetic_result_type((NebulaType)$1, (NebulaType)$3, "+", line_no); }
    | additive_expr MINUS multiplicative_expr
        { $$ = arithmetic_result_type((NebulaType)$1, (NebulaType)$3, "-", line_no); }
    ;

multiplicative_expr
    : unary_expr
        { $$ = $1; }
    | multiplicative_expr MUL unary_expr
        { $$ = arithmetic_result_type((NebulaType)$1, (NebulaType)$3, "*", line_no); }
    | multiplicative_expr DIV unary_expr
        { $$ = arithmetic_result_type((NebulaType)$1, (NebulaType)$3, "/", line_no); }
    ;

unary_expr
    : postfix_expr
        { $$ = $1; }
    | PLUS unary_expr %prec UPLUS
        { $$ = unary_plus_minus_type((NebulaType)$2, "+", line_no); }
    | MINUS unary_expr %prec UMINUS
        { $$ = unary_plus_minus_type((NebulaType)$2, "-", line_no); }
    | NOT unary_expr
        { $$ = unary_not_type((NebulaType)$2, line_no); }
    | BIT_NOT unary_expr
        { $$ = unary_bitnot_type((NebulaType)$2, line_no); }
    | INC unary_expr
        { $$ = incdec_type((NebulaType)$2, "++", line_no); }
    | DECREMENT unary_expr
        { $$ = incdec_type((NebulaType)$2, "--", line_no); }
    ;

postfix_expr
    : primary_expr
        { $$ = $1; }
    | postfix_expr INC
        { $$ = incdec_type((NebulaType)$1, "++", line_no); }
    | postfix_expr DECREMENT
        { $$ = incdec_type((NebulaType)$1, "--", line_no); }
    | postfix_expr LBRACKET expression RBRACKET
        {
            if ((NebulaType)$3 != TYPE_NUM) {
                semantic_error(line_no, "Array index must be num, found %s", type_name((NebulaType)$3));
            }
            $$ = $1;
        }
    ;

primary_expr
    : IDENTIFIER
        {
            $$ = resolve_identifier_type($1, line_no);
            free($1);
        }
    | NUM_LITERAL
        { $$ = TYPE_NUM; }
    | DEC_LITERAL
        { $$ = TYPE_DEC; }
    | CHAR_LITERAL
        { $$ = TYPE_CHAR; }
    | STRING_LITERAL
        {
            $$ = TYPE_UNKNOWN;
            free($1);
        }
    | TRUE
        { $$ = TYPE_BOOL; }
    | FALSE
        { $$ = TYPE_BOOL; }
    | function_call
        { $$ = TYPE_UNKNOWN; }
    | INPUT LPAREN RPAREN
        { $$ = TYPE_UNKNOWN; }
    | LPAREN expression RPAREN
        { $$ = $2; }
    ;

%%

void yyerror(const char *msg) {
    nebula_parse_error = 1;
    if (yytext && yytext[0] != '\0') {
        fprintf(stderr, "Syntax Error at line %d: %s near '%s'\n", line_no, msg, yytext);
    } else {
        fprintf(stderr, "Syntax Error at line %d: %s\n", line_no, msg);
    }
}

int main(int argc, char **argv) {
    if (argc > 1) {
        yyin = fopen(argv[1], "r");
        if (!yyin) {
            perror("Failed to open input file");
            return 1;
        }
    }

    if (yyparse() == 0 && nebula_lex_error == 0 && nebula_parse_error == 0 && semantic_error_count == 0) {
        printf("Parse success: Nebula source is syntactically valid.\n");
        return 0;
    }

    printf("Parse failure: Nebula source has syntax errors.\n");
    return 1;
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

static int is_numeric(NebulaType t) {
    return t == TYPE_NUM || t == TYPE_DEC;
}

static int is_truthy_compatible(NebulaType t) {
    return t == TYPE_BOOL || is_numeric(t);
}

static void semantic_error(int line, const char *fmt, ...) {
    va_list args;
    semantic_error_count++;
    fprintf(stderr, "Semantic Error at line %d: ", line);
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
    fprintf(stderr, "\n");
}

static void enter_scope(void) {
    current_scope++;
}

static void exit_scope(void) {
    Symbol *curr = symbol_table;
    Symbol *prev = NULL;
    while (curr) {
        if (curr->scope == current_scope) {
            Symbol *to_delete = curr;
            if (prev) {
                prev->next = curr->next;
            } else {
                symbol_table = curr->next;
            }
            curr = curr->next;
            free(to_delete->name);
            free(to_delete);
        } else {
            prev = curr;
            curr = curr->next;
        }
    }
    if (current_scope > 0) {
        current_scope--;
    }
}

static Symbol *lookup_symbol_current_scope(const char *name) {
    Symbol *curr = symbol_table;
    while (curr) {
        if (curr->scope == current_scope && strcmp(curr->name, name) == 0) {
            return curr;
        }
        curr = curr->next;
    }
    return NULL;
}

static Symbol *lookup_symbol(const char *name) {
    Symbol *curr = symbol_table;
    Symbol *best = NULL;
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

static void declare_variable(const char *name, NebulaType type, int line) {
    Symbol *exists = lookup_symbol_current_scope(name);
    Symbol *sym;
    if (exists) {
        semantic_error(line, "Duplicate declaration of variable '%s'", name);
        return;
    }
    sym = (Symbol *)malloc(sizeof(Symbol));
    if (!sym) {
        fprintf(stderr, "Fatal: out of memory while declaring symbol.\n");
        exit(2);
    }
    sym->name = strdup(name);
    sym->type = type;
    sym->scope = current_scope;
    sym->next = symbol_table;
    symbol_table = sym;
}

static NebulaType resolve_identifier_type(const char *name, int line) {
    Symbol *sym = lookup_symbol(name);
    if (!sym) {
        semantic_error(line, "Variable %s used before declaration", name);
        return TYPE_UNKNOWN;
    }
    return sym->type;
}

static int is_assignment_compatible(NebulaType lhs, NebulaType rhs) {
    if (lhs == TYPE_UNKNOWN || rhs == TYPE_UNKNOWN) {
        return 1;
    }
    if (lhs == rhs) {
        return 1;
    }
    if (lhs == TYPE_DEC && rhs == TYPE_NUM) {
        return 1;
    }
    return 0;
}

static NebulaType arithmetic_result_type(NebulaType lhs, NebulaType rhs, const char *op, int line) {
    if (lhs == TYPE_UNKNOWN || rhs == TYPE_UNKNOWN) {
        return TYPE_UNKNOWN;
    }
    if (is_numeric(lhs) && is_numeric(rhs)) {
        if (lhs == TYPE_DEC || rhs == TYPE_DEC) {
            return TYPE_DEC;
        }
        return TYPE_NUM;
    }
    semantic_error(line, "Type mismatch (%s %s %s)", type_name(lhs), op, type_name(rhs));
    return TYPE_UNKNOWN;
}

static NebulaType equality_result_type(NebulaType lhs, NebulaType rhs, const char *op, int line) {
    if (lhs == TYPE_UNKNOWN || rhs == TYPE_UNKNOWN) {
        return TYPE_BOOL;
    }
    if (lhs == rhs || (is_numeric(lhs) && is_numeric(rhs))) {
        return TYPE_BOOL;
    }
    semantic_error(line, "Type mismatch (%s %s %s)", type_name(lhs), op, type_name(rhs));
    return TYPE_BOOL;
}

static NebulaType relational_result_type(NebulaType lhs, NebulaType rhs, const char *op, int line) {
    if (lhs == TYPE_UNKNOWN || rhs == TYPE_UNKNOWN) {
        return TYPE_BOOL;
    }
    if (is_numeric(lhs) && is_numeric(rhs)) {
        return TYPE_BOOL;
    }
    semantic_error(line, "Type mismatch (%s %s %s)", type_name(lhs), op, type_name(rhs));
    return TYPE_BOOL;
}

static NebulaType logical_result_type(NebulaType lhs, NebulaType rhs, const char *op, int line) {
    if (lhs == TYPE_UNKNOWN || rhs == TYPE_UNKNOWN) {
        return TYPE_BOOL;
    }
    if (lhs == TYPE_BOOL && rhs == TYPE_BOOL) {
        return TYPE_BOOL;
    }
    semantic_error(line, "Logical operator %s requires bool operands, found %s and %s", op, type_name(lhs), type_name(rhs));
    return TYPE_BOOL;
}

static NebulaType bitwise_result_type(NebulaType lhs, NebulaType rhs, const char *op, int line) {
    if (lhs == TYPE_UNKNOWN || rhs == TYPE_UNKNOWN) {
        return TYPE_UNKNOWN;
    }
    if (lhs == TYPE_NUM && rhs == TYPE_NUM) {
        return TYPE_NUM;
    }
    semantic_error(line, "Bitwise operator %s requires num operands, found %s and %s", op, type_name(lhs), type_name(rhs));
    return TYPE_UNKNOWN;
}

static NebulaType unary_plus_minus_type(NebulaType t, const char *op, int line) {
    if (t == TYPE_UNKNOWN) {
        return TYPE_UNKNOWN;
    }
    if (is_numeric(t)) {
        return t;
    }
    semantic_error(line, "Unary %s requires numeric operand, found %s", op, type_name(t));
    return TYPE_UNKNOWN;
}

static NebulaType unary_not_type(NebulaType t, int line) {
    if (t == TYPE_UNKNOWN) {
        return TYPE_BOOL;
    }
    if (t == TYPE_BOOL) {
        return TYPE_BOOL;
    }
    semantic_error(line, "Logical not requires bool operand, found %s", type_name(t));
    return TYPE_BOOL;
}

static NebulaType unary_bitnot_type(NebulaType t, int line) {
    if (t == TYPE_UNKNOWN) {
        return TYPE_UNKNOWN;
    }
    if (t == TYPE_NUM) {
        return TYPE_NUM;
    }
    semantic_error(line, "Bitwise not requires num operand, found %s", type_name(t));
    return TYPE_UNKNOWN;
}

static NebulaType incdec_type(NebulaType t, const char *op, int line) {
    if (t == TYPE_UNKNOWN) {
        return TYPE_UNKNOWN;
    }
    if (is_numeric(t)) {
        return t;
    }
    semantic_error(line, "%s requires numeric operand, found %s", op, type_name(t));
    return TYPE_UNKNOWN;
}

static void check_condition_type(NebulaType cond_type, int line, const char *kw) {
    if (cond_type == TYPE_UNKNOWN) {
        return;
    }
    if (!is_truthy_compatible(cond_type)) {
        semantic_error(line, "Condition in %s must be bool/num/dec, found %s", kw, type_name(cond_type));
    }
}
