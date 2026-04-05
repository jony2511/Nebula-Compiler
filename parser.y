%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "codegen.h"
#include "semantic.h"

extern int yylex(void);
extern int line_no;
extern char *yytext;
extern FILE *yyin;
extern int nebula_lex_error;

int nebula_parse_error = 0;
static NebulaType current_decl_type = TYPE_UNKNOWN;
static ASTNode *ast_root = NULL;

void yyerror(const char *msg);
%}

%code requires {
    #include "ast.h"
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
%token WHEN OTHERWISE LOOP GIVE PRINT PRINT_INLINE INPUT
%token NEBULA
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
    : FUNCTION type_spec IDENTIFIER LPAREN
      {
          enter_scope();
      }
      parameter_list_opt RPAREN compound_stmt
      {
          ASTNode *fn = new_ast_node(AST_FUNC_CALL, $3);
          fn->inferred_type = (NebulaType)$2;
          fn->left = $6;
          fn->body = $8;
          $$ = fn;
          exit_scope();
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
                    declare_variable($2, (NebulaType)$1, line_no);
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
    : LOOP LPAREN expression RPAREN statement
      {
          ASTNode *node = new_ast_node(AST_WHILE, "loop-while");
          node->left = $3.node;
          node->body = $5;
          check_condition_type($3.type, line_no, "loop");
          $$ = node;
      }
    | LOOP LPAREN opt_expr SEMICOLON opt_expr SEMICOLON opt_expr RPAREN statement
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
    | PRINT_INLINE LPAREN print_arg_list_opt RPAREN SEMICOLON
      {
          ASTNode *node = new_ast_node(AST_PRINT, "print_inline");
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
    | NEBULA LPAREN IDENTIFIER COMMA expression RPAREN
      {
          ASTNode *id = new_ast_node(AST_IDENTIFIER, $3);
          ASTNode *call = new_ast_node(AST_FUNC_CALL, "nebula");
          id->inferred_type = resolve_identifier_type($3, line_no);
          call->left = append_node(id, $5.node);
          $$ = make_expr(TYPE_NUM, call);
          free($3);
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
    semantic_reset();

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
        generate_c_code(ast_root, (argc > 1) ? argv[1] : NULL);
            execute_program(ast_root);
        }
        return 0;
    }

    printf("Parse failure: Nebula source has syntax/semantic errors.\n");
    return 1;
}
