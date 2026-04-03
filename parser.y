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

typedef enum {
    AST_PROGRAM = 0,
    AST_STMT_LIST,
    AST_DECL,
    AST_ASSIGN,
    AST_EXPR_STMT,
    AST_IF,
    AST_LOOP,
    AST_WHILE,
    AST_DO_WHILE,
    AST_FOR,
    AST_PRINT,
    AST_INPUT,
    AST_BINOP,
    AST_UNARYOP,
    AST_LITERAL,
    AST_IDENTIFIER,
    AST_FUNC_CALL
} ASTNodeType;

typedef struct ASTNode {
    ASTNodeType kind;
    NebulaType inferred_type;
    char *text;
    struct ASTNode *left;
    struct ASTNode *right;
    struct ASTNode *third;
    struct ASTNode *body;
    struct ASTNode *next;
} ASTNode;

typedef struct ExprAttr ExprAttr;

typedef struct Symbol {
    char *name;
    NebulaType type;
    int scope;
    struct Symbol *next;
} Symbol;

static Symbol *symbol_table = NULL;
static int current_scope = 0;
static NebulaType current_decl_type = TYPE_UNKNOWN;
static ASTNode *ast_root = NULL;

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

static ExprAttr make_expr(NebulaType type, ASTNode *node);
static ASTNode *new_ast_node(ASTNodeType kind, const char *text);
static ASTNode *new_ast_unary(ASTNodeType kind, const char *op, ASTNode *child, NebulaType t);
static ASTNode *new_ast_binary(ASTNodeType kind, const char *op, ASTNode *lhs, ASTNode *rhs, NebulaType t);
static ASTNode *append_node(ASTNode *list, ASTNode *node);
static void print_ast(const ASTNode *node, int indent);
static const char *ast_kind_name(ASTNodeType kind);

void yyerror(const char *msg);
%}

%code requires {
    typedef struct ASTNode ASTNode;
    typedef struct ExprAttr {
        int type;
        ASTNode *node;
    } ExprAttr;
}

%define parse.error verbose

%union {
    int num_val;
    double dec_val;
    char char_val;
    char *str_val;
    int type_val;
    ASTNode *node;
    ExprAttr expr;
}

%token <num_val> NUM_LITERAL
%token <dec_val> DEC_LITERAL
%token <char_val> CHAR_LITERAL
%token <str_val> STRING_LITERAL IDENTIFIER

%token INT FLOAT DOUBLE NUM DEC CHAR BOOL VOID STRUCT ENUM
%token IF ELSE SWITCH CASE DEFAULT WHILE DO FOR
%token BREAK CONTINUE RETURN FUNCTION
%token WHEN OTHERWISE LOOP GIVE PRINT INPUT
%token TRUE FALSE

%token INC DECREMENT
%token EQ NEQ LE GE LT GT ASSIGN
%token AND OR
%token BIT_AND BIT_OR BIT_XOR BIT_NOT
%token LSHIFT RSHIFT
%token PLUS MINUS MUL DIV
%token NOT
%token QMARK COLON
%token ARROW_R ARROW_L

%token SEMICOLON COMMA
%token LPAREN RPAREN LBRACE RBRACE LBRACKET RBRACKET

%token INVALID

%type <type_val> type_spec

%type <node> program translation_unit external_decl
%type <node> function_def parameter_list_opt parameter_list parameter
%type <node> compound_stmt stmt_list_opt stmt_list statement
%type <node> declaration_stmt init_declarator_list init_declarator
%type <node> expression_stmt selection_stmt loop_stmt jump_stmt io_stmt
%type <node> case_clauses_opt case_clause default_clause_opt
%type <node> print_arg_list_opt print_arg_list print_arg
%type <node> function_call argument_list_opt argument_list

%type <expr> opt_expr expression assignment_expr conditional_expr
%type <expr> logical_or_expr logical_and_expr
%type <expr> bitwise_or_expr bitwise_xor_expr bitwise_and_expr
%type <expr> equality_expr relational_expr shift_expr
%type <expr> additive_expr multiplicative_expr unary_expr postfix_expr primary_expr

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
      {
          ast_root = new_ast_node(AST_PROGRAM, "program");
          ast_root->left = $1;
          $$ = ast_root;
      }
    ;

translation_unit
    : /* empty */
      {
          $$ = NULL;
      }
    | translation_unit external_decl
      {
          $$ = append_node($1, $2);
      }
    ;

external_decl
    : function_def
      {
          $$ = $1;
      }
    | statement
      {
          $$ = $1;
      }
    ;

function_def
    : FUNCTION type_spec IDENTIFIER LPAREN parameter_list_opt RPAREN compound_stmt
      {
          ASTNode *fn = new_ast_node(AST_FUNC_CALL, $3);
          fn->inferred_type = (NebulaType)$2;
          fn->left = $5;
          fn->body = $7;
          $$ = fn;
          free($3);
      }
    ;

parameter_list_opt
    : /* empty */
      {
          $$ = NULL;
      }
    | parameter_list
      {
          $$ = $1;
      }
    ;

parameter_list
    : parameter
      {
          $$ = $1;
      }
    | parameter_list COMMA parameter
      {
          $$ = append_node($1, $3);
      }
    ;

parameter
    : type_spec IDENTIFIER
      {
          ASTNode *id = new_ast_node(AST_IDENTIFIER, $2);
          id->inferred_type = (NebulaType)$1;
          $$ = id;
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
          ASTNode *list = new_ast_node(AST_STMT_LIST, "block");
          list->left = $3;
          $$ = list;
          exit_scope();
      }
    ;

stmt_list_opt
    : /* empty */
      {
          $$ = NULL;
      }
    | stmt_list
      {
          $$ = $1;
      }
    ;

stmt_list
    : statement
      {
          $$ = $1;
      }
    | stmt_list statement
      {
          $$ = append_node($1, $2);
      }
    ;

statement
    : declaration_stmt
      {
          $$ = $1;
      }
    | expression_stmt
      {
          $$ = $1;
      }
    | selection_stmt
      {
          $$ = $1;
      }
    | loop_stmt
      {
          $$ = $1;
      }
    | jump_stmt
      {
          $$ = $1;
      }
    | io_stmt
      {
          $$ = $1;
      }
    | compound_stmt
      {
          $$ = $1;
      }
    | error SEMICOLON
      {
          fprintf(stderr, "Recovered from syntax error at line %d.\n", line_no);
          yyerrok;
          $$ = NULL;
      }
    ;

declaration_stmt
    : type_spec
      {
          current_decl_type = (NebulaType)$1;
      }
      init_declarator_list SEMICOLON
      {
          $$ = $3;
      }
    ;

init_declarator_list
    : init_declarator
      {
          $$ = $1;
      }
    | init_declarator_list COMMA init_declarator
      {
          $$ = append_node($1, $3);
      }
    ;

init_declarator
    : IDENTIFIER
      {
          ASTNode *decl = new_ast_node(AST_DECL, $1);
          decl->inferred_type = current_decl_type;
          declare_variable($1, current_decl_type, line_no);
          $$ = decl;
          free($1);
      }
    | IDENTIFIER ASSIGN expression
      {
          ASTNode *decl = new_ast_node(AST_DECL, $1);
          decl->inferred_type = current_decl_type;
          decl->left = $3.node;
          declare_variable($1, current_decl_type, line_no);
          if (!is_assignment_compatible(current_decl_type, $3.type)) {
              semantic_error(line_no, "Type mismatch in declaration assignment (%s = %s)", type_name(current_decl_type), type_name($3.type));
          }
          $$ = decl;
          free($1);
      }
    ;

expression_stmt
    : expression SEMICOLON
      {
          ASTNode *st = new_ast_node(AST_EXPR_STMT, "expr");
          st->left = $1.node;
          $$ = st;
      }
    | SEMICOLON
      {
          $$ = NULL;
      }
    ;

selection_stmt
    : WHEN LPAREN expression RPAREN statement %prec LOWER_THAN_OTHERWISE
      {
          ASTNode *node = new_ast_node(AST_IF, "when");
          node->left = $3.node;
          node->right = $5;
          check_condition_type($3.type, line_no, "when");
          $$ = node;
      }
    | WHEN LPAREN expression RPAREN statement OTHERWISE statement
      {
          ASTNode *node = new_ast_node(AST_IF, "when-otherwise");
          node->left = $3.node;
          node->right = $5;
          node->third = $7;
          check_condition_type($3.type, line_no, "when");
          $$ = node;
      }
    | IF LPAREN expression RPAREN statement %prec LOWER_THAN_OTHERWISE
      {
          ASTNode *node = new_ast_node(AST_IF, "if");
          node->left = $3.node;
          node->right = $5;
          check_condition_type($3.type, line_no, "if");
          $$ = node;
      }
    | IF LPAREN expression RPAREN statement ELSE statement
      {
          ASTNode *node = new_ast_node(AST_IF, "if-else");
          node->left = $3.node;
          node->right = $5;
          node->third = $7;
          check_condition_type($3.type, line_no, "if");
          $$ = node;
      }
    | SWITCH LPAREN expression RPAREN LBRACE case_clauses_opt default_clause_opt RBRACE
      {
          ASTNode *node = new_ast_node(AST_IF, "switch");
          node->left = $3.node;
          node->right = $6;
          node->third = $7;
          $$ = node;
      }
    ;

case_clauses_opt
    : /* empty */
      {
          $$ = NULL;
      }
    | case_clauses_opt case_clause
      {
          $$ = append_node($1, $2);
      }
    ;

case_clause
    : CASE expression COLON stmt_list_opt
      {
          ASTNode *node = new_ast_node(AST_IF, "case");
          node->left = $2.node;
          node->right = $4;
          $$ = node;
      }
    ;

default_clause_opt
    : /* empty */
      {
          $$ = NULL;
      }
    | DEFAULT COLON stmt_list_opt
      {
          ASTNode *node = new_ast_node(AST_IF, "default");
          node->right = $3;
          $$ = node;
      }
    ;

loop_stmt
    : LOOP LPAREN opt_expr SEMICOLON opt_expr SEMICOLON opt_expr RPAREN statement
      {
          ASTNode *node = new_ast_node(AST_LOOP, "loop");
          node->left = $3.node;
          node->right = $5.node;
          node->third = $7.node;
          node->body = $9;
          if ($5.type != TYPE_UNKNOWN) {
              check_condition_type($5.type, line_no, "loop");
          }
          $$ = node;
      }
    | WHILE LPAREN expression RPAREN statement
      {
          ASTNode *node = new_ast_node(AST_WHILE, "while");
          node->left = $3.node;
          node->body = $5;
          check_condition_type($3.type, line_no, "while");
          $$ = node;
      }
    | DO statement WHILE LPAREN expression RPAREN SEMICOLON
      {
          ASTNode *node = new_ast_node(AST_DO_WHILE, "do-while");
          node->left = $5.node;
          node->body = $2;
          check_condition_type($5.type, line_no, "do-while");
          $$ = node;
      }
    | FOR LPAREN opt_expr SEMICOLON opt_expr SEMICOLON opt_expr RPAREN statement
      {
          ASTNode *node = new_ast_node(AST_FOR, "for");
          node->left = $3.node;
          node->right = $5.node;
          node->third = $7.node;
          node->body = $9;
          if ($5.type != TYPE_UNKNOWN) {
              check_condition_type($5.type, line_no, "for");
          }
          $$ = node;
      }
    ;

opt_expr
    : /* empty */
      {
          $$ = make_expr(TYPE_UNKNOWN, NULL);
      }
    | expression
      {
          $$ = $1;
      }
    ;

jump_stmt
    : GIVE expression SEMICOLON
      {
          ASTNode *node = new_ast_node(AST_UNARYOP, "give");
          node->left = $2.node;
          $$ = node;
      }
    | RETURN expression SEMICOLON
      {
          ASTNode *node = new_ast_node(AST_UNARYOP, "return");
          node->left = $2.node;
          $$ = node;
      }
    | BREAK SEMICOLON
      {
          $$ = new_ast_node(AST_UNARYOP, "break");
      }
    | CONTINUE SEMICOLON
      {
          $$ = new_ast_node(AST_UNARYOP, "continue");
      }
    ;

io_stmt
    : PRINT LPAREN print_arg_list_opt RPAREN SEMICOLON
      {
          ASTNode *node = new_ast_node(AST_PRINT, "print");
          node->left = $3;
          $$ = node;
      }
    | INPUT LPAREN IDENTIFIER RPAREN SEMICOLON
      {
          ASTNode *node = new_ast_node(AST_INPUT, $3);
          (void)resolve_identifier_type($3, line_no);
          $$ = node;
          free($3);
      }
    ;

print_arg_list_opt
    : /* empty */
      {
          $$ = NULL;
      }
    | print_arg_list
      {
          $$ = $1;
      }
    ;

print_arg_list
    : print_arg
      {
          $$ = $1;
      }
    | print_arg_list COMMA print_arg
      {
          $$ = append_node($1, $3);
      }
    ;

print_arg
    : expression
      {
          $$ = $1.node;
      }
    ;

function_call
    : IDENTIFIER LPAREN argument_list_opt RPAREN
      {
          ASTNode *call = new_ast_node(AST_FUNC_CALL, $1);
          call->left = $3;
          $$ = call;
          free($1);
      }
    ;

argument_list_opt
    : /* empty */
      {
          $$ = NULL;
      }
    | argument_list
      {
          $$ = $1;
      }
    ;

argument_list
    : expression
      {
          $$ = $1.node;
      }
    | argument_list COMMA expression
      {
          $$ = append_node($1, $3.node);
      }
    ;

expression
    : assignment_expr
      {
          $$ = $1;
      }
    ;

assignment_expr
    : conditional_expr
      {
          $$ = $1;
      }
    | IDENTIFIER ASSIGN assignment_expr
      {
          NebulaType lhs = resolve_identifier_type($1, line_no);
          NebulaType rhs = $3.type;
          ASTNode *id = new_ast_node(AST_IDENTIFIER, $1);
          ASTNode *as = new_ast_node(AST_ASSIGN, "=");
          as->left = id;
          as->right = $3.node;
          as->inferred_type = lhs;
          if (lhs != TYPE_UNKNOWN && rhs != TYPE_UNKNOWN && !is_assignment_compatible(lhs, rhs)) {
              semantic_error(line_no, "Type mismatch in assignment (%s = %s)", type_name(lhs), type_name(rhs));
          }
          $$ = make_expr(lhs, as);
          free($1);
      }
    ;

conditional_expr
    : logical_or_expr
      {
          $$ = $1;
      }
    | logical_or_expr QMARK expression COLON conditional_expr
      {
          NebulaType out_type;
          ASTNode *node = new_ast_node(AST_IF, "?:");
          node->left = $1.node;
          node->right = $3.node;
          node->third = $5.node;
          check_condition_type($1.type, line_no, "?:");
          if (is_assignment_compatible($3.type, $5.type)) {
              out_type = $3.type;
          } else if (is_assignment_compatible($5.type, $3.type)) {
              out_type = $5.type;
          } else {
              semantic_error(line_no, "Type mismatch in conditional expression (%s : %s)", type_name($3.type), type_name($5.type));
              out_type = TYPE_UNKNOWN;
          }
          node->inferred_type = out_type;
          $$ = make_expr(out_type, node);
      }
    ;

logical_or_expr
    : logical_and_expr
      {
          $$ = $1;
      }
    | logical_or_expr OR logical_and_expr
      {
          NebulaType t = logical_result_type($1.type, $3.type, "||", line_no);
          $$ = make_expr(t, new_ast_binary(AST_BINOP, "||", $1.node, $3.node, t));
      }
    ;

logical_and_expr
    : bitwise_or_expr
      {
          $$ = $1;
      }
    | logical_and_expr AND bitwise_or_expr
      {
          NebulaType t = logical_result_type($1.type, $3.type, "&&", line_no);
          $$ = make_expr(t, new_ast_binary(AST_BINOP, "&&", $1.node, $3.node, t));
      }
    ;

bitwise_or_expr
    : bitwise_xor_expr
      {
          $$ = $1;
      }
    | bitwise_or_expr BIT_OR bitwise_xor_expr
      {
          NebulaType t = bitwise_result_type($1.type, $3.type, "|", line_no);
          $$ = make_expr(t, new_ast_binary(AST_BINOP, "|", $1.node, $3.node, t));
      }
    ;

bitwise_xor_expr
    : bitwise_and_expr
      {
          $$ = $1;
      }
    | bitwise_xor_expr BIT_XOR bitwise_and_expr
      {
          NebulaType t = bitwise_result_type($1.type, $3.type, "^", line_no);
          $$ = make_expr(t, new_ast_binary(AST_BINOP, "^", $1.node, $3.node, t));
      }
    ;

bitwise_and_expr
    : equality_expr
      {
          $$ = $1;
      }
    | bitwise_and_expr BIT_AND equality_expr
      {
          NebulaType t = bitwise_result_type($1.type, $3.type, "&", line_no);
          $$ = make_expr(t, new_ast_binary(AST_BINOP, "&", $1.node, $3.node, t));
      }
    ;

equality_expr
    : relational_expr
      {
          $$ = $1;
      }
    | equality_expr EQ relational_expr
      {
          NebulaType t = equality_result_type($1.type, $3.type, "==", line_no);
          $$ = make_expr(t, new_ast_binary(AST_BINOP, "==", $1.node, $3.node, t));
      }
    | equality_expr NEQ relational_expr
      {
          NebulaType t = equality_result_type($1.type, $3.type, "!=", line_no);
          $$ = make_expr(t, new_ast_binary(AST_BINOP, "!=", $1.node, $3.node, t));
      }
    ;

relational_expr
    : shift_expr
      {
          $$ = $1;
      }
    | relational_expr LT shift_expr
      {
          NebulaType t = relational_result_type($1.type, $3.type, "<", line_no);
          $$ = make_expr(t, new_ast_binary(AST_BINOP, "<", $1.node, $3.node, t));
      }
    | relational_expr GT shift_expr
      {
          NebulaType t = relational_result_type($1.type, $3.type, ">", line_no);
          $$ = make_expr(t, new_ast_binary(AST_BINOP, ">", $1.node, $3.node, t));
      }
    | relational_expr LE shift_expr
      {
          NebulaType t = relational_result_type($1.type, $3.type, "<=", line_no);
          $$ = make_expr(t, new_ast_binary(AST_BINOP, "<=", $1.node, $3.node, t));
      }
    | relational_expr GE shift_expr
      {
          NebulaType t = relational_result_type($1.type, $3.type, ">=", line_no);
          $$ = make_expr(t, new_ast_binary(AST_BINOP, ">=", $1.node, $3.node, t));
      }
    ;

shift_expr
    : additive_expr
      {
          $$ = $1;
      }
    | shift_expr LSHIFT additive_expr
      {
          NebulaType t = bitwise_result_type($1.type, $3.type, "<<", line_no);
          $$ = make_expr(t, new_ast_binary(AST_BINOP, "<<", $1.node, $3.node, t));
      }
    | shift_expr RSHIFT additive_expr
      {
          NebulaType t = bitwise_result_type($1.type, $3.type, ">>", line_no);
          $$ = make_expr(t, new_ast_binary(AST_BINOP, ">>", $1.node, $3.node, t));
      }
    ;

additive_expr
    : multiplicative_expr
      {
          $$ = $1;
      }
    | additive_expr PLUS multiplicative_expr
      {
          NebulaType t = arithmetic_result_type($1.type, $3.type, "+", line_no);
          $$ = make_expr(t, new_ast_binary(AST_BINOP, "+", $1.node, $3.node, t));
      }
    | additive_expr MINUS multiplicative_expr
      {
          NebulaType t = arithmetic_result_type($1.type, $3.type, "-", line_no);
          $$ = make_expr(t, new_ast_binary(AST_BINOP, "-", $1.node, $3.node, t));
      }
    ;

multiplicative_expr
    : unary_expr
      {
          $$ = $1;
      }
    | multiplicative_expr MUL unary_expr
      {
          NebulaType t = arithmetic_result_type($1.type, $3.type, "*", line_no);
          $$ = make_expr(t, new_ast_binary(AST_BINOP, "*", $1.node, $3.node, t));
      }
    | multiplicative_expr DIV unary_expr
      {
          NebulaType t = arithmetic_result_type($1.type, $3.type, "/", line_no);
          $$ = make_expr(t, new_ast_binary(AST_BINOP, "/", $1.node, $3.node, t));
      }
    ;

unary_expr
    : postfix_expr
      {
          $$ = $1;
      }
    | PLUS unary_expr %prec UPLUS
      {
          NebulaType t = unary_plus_minus_type($2.type, "+", line_no);
          $$ = make_expr(t, new_ast_unary(AST_UNARYOP, "+", $2.node, t));
      }
    | MINUS unary_expr %prec UMINUS
      {
          NebulaType t = unary_plus_minus_type($2.type, "-", line_no);
          $$ = make_expr(t, new_ast_unary(AST_UNARYOP, "-", $2.node, t));
      }
    | NOT unary_expr
      {
          NebulaType t = unary_not_type($2.type, line_no);
          $$ = make_expr(t, new_ast_unary(AST_UNARYOP, "!", $2.node, t));
      }
    | BIT_NOT unary_expr
      {
          NebulaType t = unary_bitnot_type($2.type, line_no);
          $$ = make_expr(t, new_ast_unary(AST_UNARYOP, "~", $2.node, t));
      }
    | INC unary_expr
      {
          NebulaType t = incdec_type($2.type, "++", line_no);
          $$ = make_expr(t, new_ast_unary(AST_UNARYOP, "++", $2.node, t));
      }
    | DECREMENT unary_expr
      {
          NebulaType t = incdec_type($2.type, "--", line_no);
          $$ = make_expr(t, new_ast_unary(AST_UNARYOP, "--", $2.node, t));
      }
    ;

postfix_expr
    : primary_expr
      {
          $$ = $1;
      }
    | postfix_expr INC
      {
          NebulaType t = incdec_type($1.type, "++", line_no);
          $$ = make_expr(t, new_ast_unary(AST_UNARYOP, "post++", $1.node, t));
      }
    | postfix_expr DECREMENT
      {
          NebulaType t = incdec_type($1.type, "--", line_no);
          $$ = make_expr(t, new_ast_unary(AST_UNARYOP, "post--", $1.node, t));
      }
    | postfix_expr LBRACKET expression RBRACKET
      {
          ASTNode *idx = new_ast_binary(AST_BINOP, "[]", $1.node, $3.node, $1.type);
          if ($3.type != TYPE_NUM) {
              semantic_error(line_no, "Array index must be num, found %s", type_name($3.type));
          }
          $$ = make_expr($1.type, idx);
      }
    ;

primary_expr
    : IDENTIFIER
      {
          NebulaType t = resolve_identifier_type($1, line_no);
          ASTNode *id = new_ast_node(AST_IDENTIFIER, $1);
          id->inferred_type = t;
          $$ = make_expr(t, id);
          free($1);
      }
    | NUM_LITERAL
      {
          char buf[64];
          snprintf(buf, sizeof(buf), "%d", $1);
          $$ = make_expr(TYPE_NUM, new_ast_node(AST_LITERAL, buf));
      }
    | DEC_LITERAL
      {
          char buf[64];
          snprintf(buf, sizeof(buf), "%g", $1);
          $$ = make_expr(TYPE_DEC, new_ast_node(AST_LITERAL, buf));
      }
    | CHAR_LITERAL
      {
          char buf[8];
          snprintf(buf, sizeof(buf), "'%c'", $1);
          $$ = make_expr(TYPE_CHAR, new_ast_node(AST_LITERAL, buf));
      }
    | STRING_LITERAL
      {
          $$ = make_expr(TYPE_UNKNOWN, new_ast_node(AST_LITERAL, $1));
          free($1);
      }
    | TRUE
      {
          $$ = make_expr(TYPE_BOOL, new_ast_node(AST_LITERAL, "true"));
      }
    | FALSE
      {
          $$ = make_expr(TYPE_BOOL, new_ast_node(AST_LITERAL, "false"));
      }
    | function_call
      {
          $$ = make_expr(TYPE_UNKNOWN, $1);
      }
    | INPUT LPAREN RPAREN
      {
          $$ = make_expr(TYPE_UNKNOWN, new_ast_node(AST_INPUT, "input"));
      }
    | LPAREN expression RPAREN
      {
          $$ = $2;
      }
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
        if (ast_root) {
            printf("AST generated successfully.\n");
            print_ast(ast_root, 0);
        }
        return 0;
    }

    printf("Parse failure: Nebula source has syntax/semantic errors.\n");
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

static ExprAttr make_expr(NebulaType type, ASTNode *node) {
    ExprAttr out;
    out.type = type;
    out.node = node;
    if (node) {
        node->inferred_type = type;
    }
    return out;
}

static ASTNode *new_ast_node(ASTNodeType kind, const char *text) {
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

static ASTNode *new_ast_unary(ASTNodeType kind, const char *op, ASTNode *child, NebulaType t) {
    ASTNode *node = new_ast_node(kind, op);
    node->left = child;
    node->inferred_type = t;
    return node;
}

static ASTNode *new_ast_binary(ASTNodeType kind, const char *op, ASTNode *lhs, ASTNode *rhs, NebulaType t) {
    ASTNode *node = new_ast_node(kind, op);
    node->left = lhs;
    node->right = rhs;
    node->inferred_type = t;
    return node;
}

static ASTNode *append_node(ASTNode *list, ASTNode *node) {
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

static void print_ast(const ASTNode *node, int indent) {
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
