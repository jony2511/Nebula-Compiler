#ifndef NEBULA_AST_H
#define NEBULA_AST_H

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

typedef struct ExprAttr {
    int type;
    ASTNode *node;
} ExprAttr;

ExprAttr make_expr(NebulaType type, ASTNode *node);
ASTNode *new_ast_node(ASTNodeType kind, const char *text);
ASTNode *new_ast_unary(ASTNodeType kind, const char *op, ASTNode *child, NebulaType t);
ASTNode *new_ast_binary(ASTNodeType kind, const char *op, ASTNode *lhs, ASTNode *rhs, NebulaType t);
ASTNode *append_node(ASTNode *list, ASTNode *node);
void print_ast(const ASTNode *node, int indent);
void execute_program(ASTNode *root);

#endif
