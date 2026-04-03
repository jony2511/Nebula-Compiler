%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int yylex(void);
extern int line_no;
extern char *yytext;
extern FILE *yyin;
extern int nebula_lex_error;

int nebula_parse_error = 0;

void yyerror(const char *msg);
%}

%define parse.error verbose

%union {
    int num_val;
    double dec_val;
    char char_val;
    char *str_val;
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
        { free($3); }
    | type_spec IDENTIFIER LPAREN parameter_list_opt RPAREN compound_stmt
        { free($2); }
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
        { free($2); }
    ;

type_spec
    : NUM
    | DEC
    | CHAR
    | BOOL
    | VOID
    | INT
    | FLOAT
    | DOUBLE
    ;

compound_stmt
    : LBRACE stmt_list_opt RBRACE
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
    : type_spec init_declarator_list SEMICOLON
    ;

init_declarator_list
    : init_declarator
    | init_declarator_list COMMA init_declarator
    ;

init_declarator
    : IDENTIFIER
        { free($1); }
    | IDENTIFIER ASSIGN expression
        { free($1); }
    ;

expression_stmt
    : expression SEMICOLON
    | SEMICOLON
    ;

selection_stmt
    : WHEN LPAREN expression RPAREN statement %prec LOWER_THAN_OTHERWISE
    | WHEN LPAREN expression RPAREN statement OTHERWISE statement
    | IF LPAREN expression RPAREN statement %prec LOWER_THAN_OTHERWISE
    | IF LPAREN expression RPAREN statement ELSE statement
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
    | WHILE LPAREN expression RPAREN statement
    | DO statement WHILE LPAREN expression RPAREN SEMICOLON
    | FOR LPAREN opt_expr SEMICOLON opt_expr SEMICOLON opt_expr RPAREN statement
    ;

opt_expr
    : /* empty */
    | expression
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
        { free($3); }
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
        { free($1); }
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
    ;

assignment_expr
    : conditional_expr
    | IDENTIFIER ASSIGN assignment_expr
        { free($1); }
    ;

conditional_expr
    : logical_or_expr
    | logical_or_expr QMARK expression COLON conditional_expr
    ;

logical_or_expr
    : logical_and_expr
    | logical_or_expr OR logical_and_expr
    ;

logical_and_expr
    : bitwise_or_expr
    | logical_and_expr AND bitwise_or_expr
    ;

bitwise_or_expr
    : bitwise_xor_expr
    | bitwise_or_expr BIT_OR bitwise_xor_expr
    ;

bitwise_xor_expr
    : bitwise_and_expr
    | bitwise_xor_expr BIT_XOR bitwise_and_expr
    ;

bitwise_and_expr
    : equality_expr
    | bitwise_and_expr BIT_AND equality_expr
    ;

equality_expr
    : relational_expr
    | equality_expr EQ relational_expr
    | equality_expr NEQ relational_expr
    ;

relational_expr
    : shift_expr
    | relational_expr LT shift_expr
    | relational_expr GT shift_expr
    | relational_expr LE shift_expr
    | relational_expr GE shift_expr
    ;

shift_expr
    : additive_expr
    | shift_expr LSHIFT additive_expr
    | shift_expr RSHIFT additive_expr
    ;

additive_expr
    : multiplicative_expr
    | additive_expr PLUS multiplicative_expr
    | additive_expr MINUS multiplicative_expr
    ;

multiplicative_expr
    : unary_expr
    | multiplicative_expr MUL unary_expr
    | multiplicative_expr DIV unary_expr
    ;

unary_expr
    : postfix_expr
    | PLUS unary_expr %prec UPLUS
    | MINUS unary_expr %prec UMINUS
    | NOT unary_expr
    | BIT_NOT unary_expr
    | INC unary_expr
    | DECREMENT unary_expr
    ;

postfix_expr
    : primary_expr
    | postfix_expr INC
    | postfix_expr DECREMENT
    | postfix_expr LBRACKET expression RBRACKET
    ;

primary_expr
    : IDENTIFIER
        { free($1); }
    | NUM_LITERAL
    | DEC_LITERAL
    | CHAR_LITERAL
    | STRING_LITERAL
        { free($1); }
    | TRUE
    | FALSE
    | function_call
    | INPUT LPAREN RPAREN
    | LPAREN expression RPAREN
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

    if (yyparse() == 0 && nebula_lex_error == 0 && nebula_parse_error == 0) {
        printf("Parse success: Nebula source is syntactically valid.\n");
        return 0;
    }

    printf("Parse failure: Nebula source has syntax errors.\n");
    return 1;
}
