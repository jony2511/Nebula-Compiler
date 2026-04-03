/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "parser.y"

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

typedef struct {
    int has_return;
    int has_break;
    int has_continue;
    RuntimeValue return_value;
} ExecSignal;

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
static RuntimeVar *runtime_env = NULL;
static FunctionDef *function_table = NULL;
static int runtime_scope = 0;

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
static void execute_program(ASTNode *root);

void yyerror(const char *msg);

#line 228 "parser.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_NUM_LITERAL = 3,                /* NUM_LITERAL  */
  YYSYMBOL_DEC_LITERAL = 4,                /* DEC_LITERAL  */
  YYSYMBOL_CHAR_LITERAL = 5,               /* CHAR_LITERAL  */
  YYSYMBOL_STRING_LITERAL = 6,             /* STRING_LITERAL  */
  YYSYMBOL_IDENTIFIER = 7,                 /* IDENTIFIER  */
  YYSYMBOL_INT = 8,                        /* INT  */
  YYSYMBOL_FLOAT = 9,                      /* FLOAT  */
  YYSYMBOL_DOUBLE = 10,                    /* DOUBLE  */
  YYSYMBOL_NUM = 11,                       /* NUM  */
  YYSYMBOL_DEC = 12,                       /* DEC  */
  YYSYMBOL_CHAR = 13,                      /* CHAR  */
  YYSYMBOL_BOOL = 14,                      /* BOOL  */
  YYSYMBOL_VOID = 15,                      /* VOID  */
  YYSYMBOL_STRUCT = 16,                    /* STRUCT  */
  YYSYMBOL_ENUM = 17,                      /* ENUM  */
  YYSYMBOL_IF = 18,                        /* IF  */
  YYSYMBOL_ELSE = 19,                      /* ELSE  */
  YYSYMBOL_SWITCH = 20,                    /* SWITCH  */
  YYSYMBOL_CASE = 21,                      /* CASE  */
  YYSYMBOL_DEFAULT = 22,                   /* DEFAULT  */
  YYSYMBOL_WHILE = 23,                     /* WHILE  */
  YYSYMBOL_DO = 24,                        /* DO  */
  YYSYMBOL_FOR = 25,                       /* FOR  */
  YYSYMBOL_BREAK = 26,                     /* BREAK  */
  YYSYMBOL_CONTINUE = 27,                  /* CONTINUE  */
  YYSYMBOL_RETURN = 28,                    /* RETURN  */
  YYSYMBOL_FUNCTION = 29,                  /* FUNCTION  */
  YYSYMBOL_WHEN = 30,                      /* WHEN  */
  YYSYMBOL_OTHERWISE = 31,                 /* OTHERWISE  */
  YYSYMBOL_LOOP = 32,                      /* LOOP  */
  YYSYMBOL_GIVE = 33,                      /* GIVE  */
  YYSYMBOL_PRINT = 34,                     /* PRINT  */
  YYSYMBOL_INPUT = 35,                     /* INPUT  */
  YYSYMBOL_TRUE = 36,                      /* TRUE  */
  YYSYMBOL_FALSE = 37,                     /* FALSE  */
  YYSYMBOL_INC = 38,                       /* INC  */
  YYSYMBOL_DECREMENT = 39,                 /* DECREMENT  */
  YYSYMBOL_EQ = 40,                        /* EQ  */
  YYSYMBOL_NEQ = 41,                       /* NEQ  */
  YYSYMBOL_LE = 42,                        /* LE  */
  YYSYMBOL_GE = 43,                        /* GE  */
  YYSYMBOL_LT = 44,                        /* LT  */
  YYSYMBOL_GT = 45,                        /* GT  */
  YYSYMBOL_ASSIGN = 46,                    /* ASSIGN  */
  YYSYMBOL_AND = 47,                       /* AND  */
  YYSYMBOL_OR = 48,                        /* OR  */
  YYSYMBOL_BIT_AND = 49,                   /* BIT_AND  */
  YYSYMBOL_BIT_OR = 50,                    /* BIT_OR  */
  YYSYMBOL_BIT_XOR = 51,                   /* BIT_XOR  */
  YYSYMBOL_BIT_NOT = 52,                   /* BIT_NOT  */
  YYSYMBOL_LSHIFT = 53,                    /* LSHIFT  */
  YYSYMBOL_RSHIFT = 54,                    /* RSHIFT  */
  YYSYMBOL_PLUS = 55,                      /* PLUS  */
  YYSYMBOL_MINUS = 56,                     /* MINUS  */
  YYSYMBOL_MUL = 57,                       /* MUL  */
  YYSYMBOL_DIV = 58,                       /* DIV  */
  YYSYMBOL_NOT = 59,                       /* NOT  */
  YYSYMBOL_QMARK = 60,                     /* QMARK  */
  YYSYMBOL_COLON = 61,                     /* COLON  */
  YYSYMBOL_ARROW_R = 62,                   /* ARROW_R  */
  YYSYMBOL_ARROW_L = 63,                   /* ARROW_L  */
  YYSYMBOL_SEMICOLON = 64,                 /* SEMICOLON  */
  YYSYMBOL_COMMA = 65,                     /* COMMA  */
  YYSYMBOL_LPAREN = 66,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 67,                    /* RPAREN  */
  YYSYMBOL_LBRACE = 68,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 69,                    /* RBRACE  */
  YYSYMBOL_LBRACKET = 70,                  /* LBRACKET  */
  YYSYMBOL_RBRACKET = 71,                  /* RBRACKET  */
  YYSYMBOL_INVALID = 72,                   /* INVALID  */
  YYSYMBOL_LOWER_THAN_OTHERWISE = 73,      /* LOWER_THAN_OTHERWISE  */
  YYSYMBOL_UMINUS = 74,                    /* UMINUS  */
  YYSYMBOL_UPLUS = 75,                     /* UPLUS  */
  YYSYMBOL_YYACCEPT = 76,                  /* $accept  */
  YYSYMBOL_program = 77,                   /* program  */
  YYSYMBOL_translation_unit = 78,          /* translation_unit  */
  YYSYMBOL_external_decl = 79,             /* external_decl  */
  YYSYMBOL_function_def = 80,              /* function_def  */
  YYSYMBOL_81_1 = 81,                      /* $@1  */
  YYSYMBOL_parameter_list_opt = 82,        /* parameter_list_opt  */
  YYSYMBOL_parameter_list = 83,            /* parameter_list  */
  YYSYMBOL_parameter = 84,                 /* parameter  */
  YYSYMBOL_type_spec = 85,                 /* type_spec  */
  YYSYMBOL_compound_stmt = 86,             /* compound_stmt  */
  YYSYMBOL_87_2 = 87,                      /* $@2  */
  YYSYMBOL_stmt_list_opt = 88,             /* stmt_list_opt  */
  YYSYMBOL_stmt_list = 89,                 /* stmt_list  */
  YYSYMBOL_statement = 90,                 /* statement  */
  YYSYMBOL_declaration_stmt = 91,          /* declaration_stmt  */
  YYSYMBOL_92_3 = 92,                      /* $@3  */
  YYSYMBOL_init_declarator_list = 93,      /* init_declarator_list  */
  YYSYMBOL_init_declarator = 94,           /* init_declarator  */
  YYSYMBOL_expression_stmt = 95,           /* expression_stmt  */
  YYSYMBOL_selection_stmt = 96,            /* selection_stmt  */
  YYSYMBOL_case_clauses_opt = 97,          /* case_clauses_opt  */
  YYSYMBOL_case_clause = 98,               /* case_clause  */
  YYSYMBOL_default_clause_opt = 99,        /* default_clause_opt  */
  YYSYMBOL_loop_stmt = 100,                /* loop_stmt  */
  YYSYMBOL_opt_expr = 101,                 /* opt_expr  */
  YYSYMBOL_jump_stmt = 102,                /* jump_stmt  */
  YYSYMBOL_io_stmt = 103,                  /* io_stmt  */
  YYSYMBOL_print_arg_list_opt = 104,       /* print_arg_list_opt  */
  YYSYMBOL_print_arg_list = 105,           /* print_arg_list  */
  YYSYMBOL_print_arg = 106,                /* print_arg  */
  YYSYMBOL_function_call = 107,            /* function_call  */
  YYSYMBOL_argument_list_opt = 108,        /* argument_list_opt  */
  YYSYMBOL_argument_list = 109,            /* argument_list  */
  YYSYMBOL_expression = 110,               /* expression  */
  YYSYMBOL_assignment_expr = 111,          /* assignment_expr  */
  YYSYMBOL_conditional_expr = 112,         /* conditional_expr  */
  YYSYMBOL_logical_or_expr = 113,          /* logical_or_expr  */
  YYSYMBOL_logical_and_expr = 114,         /* logical_and_expr  */
  YYSYMBOL_bitwise_or_expr = 115,          /* bitwise_or_expr  */
  YYSYMBOL_bitwise_xor_expr = 116,         /* bitwise_xor_expr  */
  YYSYMBOL_bitwise_and_expr = 117,         /* bitwise_and_expr  */
  YYSYMBOL_equality_expr = 118,            /* equality_expr  */
  YYSYMBOL_relational_expr = 119,          /* relational_expr  */
  YYSYMBOL_shift_expr = 120,               /* shift_expr  */
  YYSYMBOL_additive_expr = 121,            /* additive_expr  */
  YYSYMBOL_multiplicative_expr = 122,      /* multiplicative_expr  */
  YYSYMBOL_unary_expr = 123,               /* unary_expr  */
  YYSYMBOL_postfix_expr = 124,             /* postfix_expr  */
  YYSYMBOL_primary_expr = 125              /* primary_expr  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if 1

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* 1 */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   556

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  76
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  50
/* YYNRULES -- Number of rules.  */
#define YYNRULES  129
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  241

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   330


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   244,   244,   254,   257,   264,   268,   276,   275,   293,
     296,   303,   307,   314,   325,   326,   327,   328,   329,   330,
     331,   332,   337,   336,   351,   354,   361,   365,   372,   376,
     380,   384,   388,   392,   396,   400,   410,   409,   420,   424,
     431,   439,   454,   460,   467,   475,   484,   492,   501,   513,
     516,   523,   534,   537,   546,   554,   566,   574,   582,   598,
     601,   608,   614,   620,   624,   631,   637,   648,   651,   658,
     662,   669,   676,   687,   690,   697,   701,   708,   715,   719,
     737,   741,   763,   767,   775,   779,   787,   791,   799,   803,
     811,   815,   823,   827,   832,   840,   844,   849,   854,   859,
     867,   871,   876,   884,   888,   893,   901,   905,   910,   918,
     922,   927,   932,   937,   942,   947,   955,   959,   964,   969,
     980,   988,   994,  1000,  1006,  1011,  1015,  1019,  1023,  1027
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "NUM_LITERAL",
  "DEC_LITERAL", "CHAR_LITERAL", "STRING_LITERAL", "IDENTIFIER", "INT",
  "FLOAT", "DOUBLE", "NUM", "DEC", "CHAR", "BOOL", "VOID", "STRUCT",
  "ENUM", "IF", "ELSE", "SWITCH", "CASE", "DEFAULT", "WHILE", "DO", "FOR",
  "BREAK", "CONTINUE", "RETURN", "FUNCTION", "WHEN", "OTHERWISE", "LOOP",
  "GIVE", "PRINT", "INPUT", "TRUE", "FALSE", "INC", "DECREMENT", "EQ",
  "NEQ", "LE", "GE", "LT", "GT", "ASSIGN", "AND", "OR", "BIT_AND",
  "BIT_OR", "BIT_XOR", "BIT_NOT", "LSHIFT", "RSHIFT", "PLUS", "MINUS",
  "MUL", "DIV", "NOT", "QMARK", "COLON", "ARROW_R", "ARROW_L", "SEMICOLON",
  "COMMA", "LPAREN", "RPAREN", "LBRACE", "RBRACE", "LBRACKET", "RBRACKET",
  "INVALID", "LOWER_THAN_OTHERWISE", "UMINUS", "UPLUS", "$accept",
  "program", "translation_unit", "external_decl", "function_def", "$@1",
  "parameter_list_opt", "parameter_list", "parameter", "type_spec",
  "compound_stmt", "$@2", "stmt_list_opt", "stmt_list", "statement",
  "declaration_stmt", "$@3", "init_declarator_list", "init_declarator",
  "expression_stmt", "selection_stmt", "case_clauses_opt", "case_clause",
  "default_clause_opt", "loop_stmt", "opt_expr", "jump_stmt", "io_stmt",
  "print_arg_list_opt", "print_arg_list", "print_arg", "function_call",
  "argument_list_opt", "argument_list", "expression", "assignment_expr",
  "conditional_expr", "logical_or_expr", "logical_and_expr",
  "bitwise_or_expr", "bitwise_xor_expr", "bitwise_and_expr",
  "equality_expr", "relational_expr", "shift_expr", "additive_expr",
  "multiplicative_expr", "unary_expr", "postfix_expr", "primary_expr", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-206)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-26)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -206,     5,   353,  -206,   -57,  -206,  -206,  -206,  -206,   -43,
    -206,  -206,  -206,  -206,  -206,  -206,  -206,  -206,   -34,   -26,
     -10,   488,     8,   -40,     1,    23,    34,    17,    24,    23,
      44,    47,  -206,  -206,    32,    32,    32,    32,    32,    32,
    -206,    23,  -206,  -206,  -206,  -206,  -206,  -206,  -206,  -206,
    -206,  -206,  -206,  -206,  -206,    12,  -206,  -206,   -42,    69,
      31,    66,    70,   -19,    58,   -20,    -5,    15,  -206,   -29,
    -206,  -206,    23,    23,    23,    23,    23,    95,    23,  -206,
    -206,    54,    57,   115,    23,    23,    59,    23,    10,    61,
    -206,  -206,  -206,  -206,  -206,  -206,    62,   419,   117,  -206,
      32,    23,    32,    32,    32,    32,    32,    32,    32,    32,
      32,    32,    32,    32,    32,    32,    32,    32,  -206,  -206,
      23,  -206,    63,    60,  -206,    64,    67,    68,    71,    72,
    -206,    73,  -206,    76,    74,    79,    78,  -206,    80,    81,
    -206,  -206,    82,  -206,  -206,    83,   214,  -206,    87,    21,
    -206,    69,    77,    31,    66,    70,   -19,    58,    58,   -20,
     -20,   -20,   -20,    -5,    -5,    15,    15,  -206,  -206,    85,
    -206,    23,   488,    89,   488,    23,    23,  -206,   488,    23,
     488,    84,    23,    96,  -206,  -206,    23,  -206,   117,    32,
    -206,  -206,   109,  -206,  -206,    86,    98,    34,   108,    99,
    -206,  -206,  -206,  -206,  -206,  -206,  -206,   488,    75,   100,
      23,    92,   101,  -206,   144,   488,    23,  -206,    23,   106,
    -206,   102,  -206,   107,   111,    34,  -206,  -206,   110,   114,
     419,  -206,   488,  -206,  -206,   488,   283,  -206,  -206,  -206,
    -206
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     0,     1,     0,   121,   122,   123,   124,   120,
      19,    20,    21,    14,    15,    16,    17,    18,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   125,   126,     0,     0,     0,     0,     0,     0,
      43,     0,    22,     4,     5,    36,    34,     6,    28,    29,
      30,    31,    32,    33,   127,     0,    77,    78,    80,    82,
      84,    86,    88,    90,    92,    95,   100,   103,   106,   109,
     116,    35,     0,    73,     0,     0,     0,     0,    59,    63,
      64,     0,     0,     0,     0,    59,     0,    67,     0,   120,
     114,   115,   113,   110,   111,   112,     0,     0,     0,    42,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   117,   118,
       0,    79,     0,    74,    75,     0,     0,     0,     0,     0,
      60,     0,    62,     0,     0,     0,    60,    61,     0,    68,
      69,    71,     0,   128,   129,     0,     0,    26,    40,     0,
      38,    83,     0,    85,    87,    89,    91,    93,    94,    98,
      99,    96,    97,   101,   102,   104,   105,   107,   108,     0,
      72,     0,     0,     0,     0,     0,    59,     7,     0,    59,
       0,     0,     0,     0,    23,    27,     0,    37,     0,     0,
     119,    76,    46,    49,    56,     0,     0,     9,    44,     0,
      54,    65,    70,    66,    41,    39,    81,     0,    52,     0,
      59,     0,    10,    11,     0,     0,    59,    47,     0,     0,
      50,     0,    57,     0,     0,     0,    13,    45,     0,     0,
       0,    48,     0,     8,    12,     0,     0,    53,    58,    55,
      51
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -206,  -206,  -206,  -206,  -206,  -206,  -206,  -206,   -56,   -24,
     -44,  -206,  -205,  -206,    -2,  -206,  -206,  -206,    -7,  -206,
    -206,  -206,  -206,  -206,  -206,   -84,  -206,  -206,  -206,  -206,
     -14,  -206,  -206,  -206,   -21,   112,    -6,  -206,    88,    90,
      91,    94,    97,     2,    -4,    -1,     0,   -23,  -206,  -206
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     1,     2,    43,    44,   197,   211,   212,   213,    45,
      46,    97,   145,   146,   147,    48,    98,   149,   150,    49,
      50,   208,   220,   221,    51,   129,    52,    53,   138,   139,
     140,    54,   122,   123,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      47,   135,    83,    72,    82,     3,   100,    71,    86,   118,
     119,    90,    91,    92,    93,    94,    95,   142,   101,    77,
      96,   106,   107,    73,    79,   237,     5,     6,     7,     8,
       9,   240,    74,   112,   113,     5,     6,     7,     8,    89,
      75,   120,    10,    11,    12,    13,    14,    15,    16,    17,
     114,   115,   124,   125,   126,   127,    76,   130,    81,    32,
      33,    34,    35,   134,   136,    80,   141,    81,    32,    33,
      34,    35,   116,   117,    78,    36,    99,   143,    37,    38,
     152,   103,    39,    84,    36,   187,   188,    37,    38,    41,
      85,    39,   196,   167,   168,   199,   218,   219,    41,   169,
     108,   109,   110,   111,   159,   160,   161,   162,   157,   158,
      87,   163,   164,    88,   165,   166,   102,   104,   128,   105,
     131,   132,   133,   137,   148,   171,   223,    73,   207,   144,
     170,   172,   228,   186,   173,   174,   176,   175,   189,   215,
     143,   178,   177,   179,   185,   180,   182,   181,   201,   183,
     191,   226,   184,   209,   195,   130,   190,   193,   130,   224,
     203,   141,   210,   216,   222,   204,   225,   230,   202,   234,
     192,   231,   194,   214,   232,   236,   198,   235,   200,    42,
     233,   205,     0,   206,   121,     0,     0,     0,   151,   130,
       0,     0,   153,     0,   154,   130,     0,   229,   155,     0,
       0,   214,   156,     0,     0,   217,     0,     0,     0,     0,
       0,     0,     0,   227,     0,     4,     0,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
     238,     0,    18,   239,    19,   -25,   -25,    20,    21,    22,
      23,    24,    25,     0,    27,     0,    28,    29,    30,    31,
      32,    33,    34,    35,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    36,     0,     0,    37,
      38,     0,     0,    39,     0,     0,     0,     0,    40,     0,
      41,     0,    42,   -25,     4,     0,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,     0,
       0,    18,     0,    19,   -24,   -24,    20,    21,    22,    23,
      24,    25,     0,    27,     0,    28,    29,    30,    31,    32,
      33,    34,    35,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    36,     0,     0,    37,    38,
       0,     0,    39,     0,     0,     0,     0,    40,     0,    41,
       0,    42,   -24,    -2,     4,     0,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,     0,
       0,    18,     0,    19,     0,     0,    20,    21,    22,    23,
      24,    25,    26,    27,     0,    28,    29,    30,    31,    32,
      33,    34,    35,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    36,     0,     0,    37,    38,
       0,     0,    39,     0,     0,     0,     0,    40,     0,    41,
       4,    42,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,     0,     0,    18,     0,    19,
       0,     0,    20,    21,    22,    23,    24,    25,     0,    27,
       0,    28,    29,    30,    31,    32,    33,    34,    35,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    36,     0,     0,    37,    38,     0,     0,    39,     0,
       0,     0,     0,    40,     0,    41,     0,    42,   -24,     4,
       0,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,     0,     0,    18,     0,    19,     0,
       0,    20,    21,    22,    23,    24,    25,     0,    27,     0,
      28,    29,    30,    31,    32,    33,    34,    35,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      36,     0,     0,    37,    38,     0,     0,    39,     0,     0,
       0,     0,    40,     0,    41,     0,    42
};

static const yytype_int16 yycheck[] =
{
       2,    85,    26,    46,    25,     0,    48,    64,    29,    38,
      39,    34,    35,    36,    37,    38,    39,     7,    60,    21,
      41,    40,    41,    66,    64,   230,     3,     4,     5,     6,
       7,   236,    66,    53,    54,     3,     4,     5,     6,     7,
      66,    70,     8,     9,    10,    11,    12,    13,    14,    15,
      55,    56,    73,    74,    75,    76,    66,    78,    35,    36,
      37,    38,    39,    84,    85,    64,    87,    35,    36,    37,
      38,    39,    57,    58,    66,    52,    64,    67,    55,    56,
     101,    50,    59,    66,    52,    64,    65,    55,    56,    66,
      66,    59,   176,   116,   117,   179,    21,    22,    66,   120,
      42,    43,    44,    45,   108,   109,   110,   111,   106,   107,
      66,   112,   113,    66,   114,   115,    47,    51,    23,    49,
      66,    64,     7,    64,     7,    65,   210,    66,    19,    67,
      67,    67,   216,    46,    67,    67,    64,    66,    61,    31,
      67,    67,    66,    64,   146,    67,    65,    67,    64,    67,
     171,     7,    69,    67,   175,   176,    71,    68,   179,    67,
      64,   182,    64,    64,    64,   186,    65,    61,   182,   225,
     172,    69,   174,   197,    67,    61,   178,    67,   180,    68,
     224,   188,    -1,   189,    72,    -1,    -1,    -1,   100,   210,
      -1,    -1,   102,    -1,   103,   216,    -1,   218,   104,    -1,
      -1,   225,   105,    -1,    -1,   207,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   215,    -1,     1,    -1,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
     232,    -1,    18,   235,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    -1,    30,    -1,    32,    33,    34,    35,
      36,    37,    38,    39,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    52,    -1,    -1,    55,
      56,    -1,    -1,    59,    -1,    -1,    -1,    -1,    64,    -1,
      66,    -1,    68,    69,     1,    -1,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    -1,
      -1,    18,    -1,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    -1,    30,    -1,    32,    33,    34,    35,    36,
      37,    38,    39,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    52,    -1,    -1,    55,    56,
      -1,    -1,    59,    -1,    -1,    -1,    -1,    64,    -1,    66,
      -1,    68,    69,     0,     1,    -1,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    -1,
      -1,    18,    -1,    20,    -1,    -1,    23,    24,    25,    26,
      27,    28,    29,    30,    -1,    32,    33,    34,    35,    36,
      37,    38,    39,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    52,    -1,    -1,    55,    56,
      -1,    -1,    59,    -1,    -1,    -1,    -1,    64,    -1,    66,
       1,    68,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    -1,    -1,    18,    -1,    20,
      -1,    -1,    23,    24,    25,    26,    27,    28,    -1,    30,
      -1,    32,    33,    34,    35,    36,    37,    38,    39,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    52,    -1,    -1,    55,    56,    -1,    -1,    59,    -1,
      -1,    -1,    -1,    64,    -1,    66,    -1,    68,    69,     1,
      -1,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    -1,    -1,    18,    -1,    20,    -1,
      -1,    23,    24,    25,    26,    27,    28,    -1,    30,    -1,
      32,    33,    34,    35,    36,    37,    38,    39,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      52,    -1,    -1,    55,    56,    -1,    -1,    59,    -1,    -1,
      -1,    -1,    64,    -1,    66,    -1,    68
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    77,    78,     0,     1,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    18,    20,
      23,    24,    25,    26,    27,    28,    29,    30,    32,    33,
      34,    35,    36,    37,    38,    39,    52,    55,    56,    59,
      64,    66,    68,    79,    80,    85,    86,    90,    91,    95,
      96,   100,   102,   103,   107,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,    64,    46,    66,    66,    66,    66,    90,    66,    64,
      64,    35,   110,    85,    66,    66,   110,    66,    66,     7,
     123,   123,   123,   123,   123,   123,   110,    87,    92,    64,
      48,    60,    47,    50,    51,    49,    40,    41,    42,    43,
      44,    45,    53,    54,    55,    56,    57,    58,    38,    39,
      70,   111,   108,   109,   110,   110,   110,   110,    23,   101,
     110,    66,    64,     7,   110,   101,   110,    64,   104,   105,
     106,   110,     7,    67,    67,    88,    89,    90,     7,    93,
      94,   114,   110,   115,   116,   117,   118,   119,   119,   120,
     120,   120,   120,   121,   121,   122,   122,   123,   123,   110,
      67,    65,    67,    67,    67,    66,    64,    66,    67,    64,
      67,    67,    65,    67,    69,    90,    46,    64,    65,    61,
      71,   110,    90,    68,    90,   110,   101,    81,    90,   101,
      90,    64,   106,    64,   110,    94,   112,    19,    97,    67,
      64,    82,    83,    84,    85,    31,    64,    90,    21,    22,
      98,    99,    64,   101,    67,    65,     7,    90,   101,   110,
      61,    69,    67,    86,    84,    67,    61,    88,    90,    90,
      88
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    76,    77,    78,    78,    79,    79,    81,    80,    82,
      82,    83,    83,    84,    85,    85,    85,    85,    85,    85,
      85,    85,    87,    86,    88,    88,    89,    89,    90,    90,
      90,    90,    90,    90,    90,    90,    92,    91,    93,    93,
      94,    94,    95,    95,    96,    96,    96,    96,    96,    97,
      97,    98,    99,    99,   100,   100,   100,   100,   100,   101,
     101,   102,   102,   102,   102,   103,   103,   104,   104,   105,
     105,   106,   107,   108,   108,   109,   109,   110,   111,   111,
     112,   112,   113,   113,   114,   114,   115,   115,   116,   116,
     117,   117,   118,   118,   118,   119,   119,   119,   119,   119,
     120,   120,   120,   121,   121,   121,   122,   122,   122,   123,
     123,   123,   123,   123,   123,   123,   124,   124,   124,   124,
     125,   125,   125,   125,   125,   125,   125,   125,   125,   125
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     0,     2,     1,     1,     0,     8,     0,
       1,     1,     3,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     0,     1,     1,     2,     1,     1,
       1,     1,     1,     1,     1,     2,     0,     4,     1,     3,
       1,     3,     2,     1,     5,     7,     5,     7,     8,     0,
       2,     4,     0,     3,     5,     9,     5,     7,     9,     0,
       1,     3,     3,     2,     2,     5,     5,     0,     1,     1,
       3,     1,     4,     0,     1,     1,     3,     1,     1,     3,
       1,     5,     1,     3,     1,     3,     1,     3,     1,     3,
       1,     3,     1,     3,     3,     1,     3,     3,     3,     3,
       1,     3,     3,     1,     3,     3,     1,     3,     3,     1,
       2,     2,     2,     2,     2,     2,     1,     2,     2,     4,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     3
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
  if (!yypact_value_is_default (yyn))
    {
      /* Start YYX at -YYN if negative to avoid negative indexes in
         YYCHECK.  In other words, skip the first -YYN actions for
         this state because they are default actions.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;
      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yyx;
      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
# endif
#endif

#ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;
      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
#endif


static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
      case N:                               \
        yyformat = S;                       \
        break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* program: translation_unit  */
#line 245 "parser.y"
      {
          ast_root = new_ast_node(AST_PROGRAM, "program");
          ast_root->left = (yyvsp[0].node);
          (yyval.node) = ast_root;
      }
#line 1855 "parser.tab.c"
    break;

  case 3: /* translation_unit: %empty  */
#line 254 "parser.y"
      {
          (yyval.node) = NULL;
      }
#line 1863 "parser.tab.c"
    break;

  case 4: /* translation_unit: translation_unit external_decl  */
#line 258 "parser.y"
      {
          (yyval.node) = append_node((yyvsp[-1].node), (yyvsp[0].node));
      }
#line 1871 "parser.tab.c"
    break;

  case 5: /* external_decl: function_def  */
#line 265 "parser.y"
      {
          (yyval.node) = (yyvsp[0].node);
      }
#line 1879 "parser.tab.c"
    break;

  case 6: /* external_decl: statement  */
#line 269 "parser.y"
      {
          (yyval.node) = (yyvsp[0].node);
      }
#line 1887 "parser.tab.c"
    break;

  case 7: /* $@1: %empty  */
#line 276 "parser.y"
      {
          enter_scope();
      }
#line 1895 "parser.tab.c"
    break;

  case 8: /* function_def: FUNCTION type_spec IDENTIFIER LPAREN $@1 parameter_list_opt RPAREN compound_stmt  */
#line 280 "parser.y"
      {
          ASTNode *fn = new_ast_node(AST_FUNC_CALL, (yyvsp[-5].str_val));
          fn->inferred_type = (NebulaType)(yyvsp[-6].type_val);
          fn->left = (yyvsp[-2].node);
          fn->body = (yyvsp[0].node);
          (yyval.node) = fn;
          exit_scope();
          free((yyvsp[-5].str_val));
      }
#line 1909 "parser.tab.c"
    break;

  case 9: /* parameter_list_opt: %empty  */
#line 293 "parser.y"
      {
          (yyval.node) = NULL;
      }
#line 1917 "parser.tab.c"
    break;

  case 10: /* parameter_list_opt: parameter_list  */
#line 297 "parser.y"
      {
          (yyval.node) = (yyvsp[0].node);
      }
#line 1925 "parser.tab.c"
    break;

  case 11: /* parameter_list: parameter  */
#line 304 "parser.y"
      {
          (yyval.node) = (yyvsp[0].node);
      }
#line 1933 "parser.tab.c"
    break;

  case 12: /* parameter_list: parameter_list COMMA parameter  */
#line 308 "parser.y"
      {
          (yyval.node) = append_node((yyvsp[-2].node), (yyvsp[0].node));
      }
#line 1941 "parser.tab.c"
    break;

  case 13: /* parameter: type_spec IDENTIFIER  */
#line 315 "parser.y"
      {
          ASTNode *id = new_ast_node(AST_IDENTIFIER, (yyvsp[0].str_val));
          id->inferred_type = (NebulaType)(yyvsp[-1].type_val);
                    declare_variable((yyvsp[0].str_val), (NebulaType)(yyvsp[-1].type_val), line_no);
          (yyval.node) = id;
          free((yyvsp[0].str_val));
      }
#line 1953 "parser.tab.c"
    break;

  case 14: /* type_spec: NUM  */
#line 325 "parser.y"
                 { (yyval.type_val) = TYPE_NUM; }
#line 1959 "parser.tab.c"
    break;

  case 15: /* type_spec: DEC  */
#line 326 "parser.y"
                 { (yyval.type_val) = TYPE_DEC; }
#line 1965 "parser.tab.c"
    break;

  case 16: /* type_spec: CHAR  */
#line 327 "parser.y"
                 { (yyval.type_val) = TYPE_CHAR; }
#line 1971 "parser.tab.c"
    break;

  case 17: /* type_spec: BOOL  */
#line 328 "parser.y"
                 { (yyval.type_val) = TYPE_BOOL; }
#line 1977 "parser.tab.c"
    break;

  case 18: /* type_spec: VOID  */
#line 329 "parser.y"
                 { (yyval.type_val) = TYPE_VOID; }
#line 1983 "parser.tab.c"
    break;

  case 19: /* type_spec: INT  */
#line 330 "parser.y"
                 { (yyval.type_val) = TYPE_NUM; }
#line 1989 "parser.tab.c"
    break;

  case 20: /* type_spec: FLOAT  */
#line 331 "parser.y"
                 { (yyval.type_val) = TYPE_DEC; }
#line 1995 "parser.tab.c"
    break;

  case 21: /* type_spec: DOUBLE  */
#line 332 "parser.y"
                 { (yyval.type_val) = TYPE_DEC; }
#line 2001 "parser.tab.c"
    break;

  case 22: /* $@2: %empty  */
#line 337 "parser.y"
      {
          enter_scope();
      }
#line 2009 "parser.tab.c"
    break;

  case 23: /* compound_stmt: LBRACE $@2 stmt_list_opt RBRACE  */
#line 341 "parser.y"
      {
          ASTNode *list = new_ast_node(AST_STMT_LIST, "block");
          list->left = (yyvsp[-1].node);
          (yyval.node) = list;
          exit_scope();
      }
#line 2020 "parser.tab.c"
    break;

  case 24: /* stmt_list_opt: %empty  */
#line 351 "parser.y"
      {
          (yyval.node) = NULL;
      }
#line 2028 "parser.tab.c"
    break;

  case 25: /* stmt_list_opt: stmt_list  */
#line 355 "parser.y"
      {
          (yyval.node) = (yyvsp[0].node);
      }
#line 2036 "parser.tab.c"
    break;

  case 26: /* stmt_list: statement  */
#line 362 "parser.y"
      {
          (yyval.node) = (yyvsp[0].node);
      }
#line 2044 "parser.tab.c"
    break;

  case 27: /* stmt_list: stmt_list statement  */
#line 366 "parser.y"
      {
          (yyval.node) = append_node((yyvsp[-1].node), (yyvsp[0].node));
      }
#line 2052 "parser.tab.c"
    break;

  case 28: /* statement: declaration_stmt  */
#line 373 "parser.y"
      {
          (yyval.node) = (yyvsp[0].node);
      }
#line 2060 "parser.tab.c"
    break;

  case 29: /* statement: expression_stmt  */
#line 377 "parser.y"
      {
          (yyval.node) = (yyvsp[0].node);
      }
#line 2068 "parser.tab.c"
    break;

  case 30: /* statement: selection_stmt  */
#line 381 "parser.y"
      {
          (yyval.node) = (yyvsp[0].node);
      }
#line 2076 "parser.tab.c"
    break;

  case 31: /* statement: loop_stmt  */
#line 385 "parser.y"
      {
          (yyval.node) = (yyvsp[0].node);
      }
#line 2084 "parser.tab.c"
    break;

  case 32: /* statement: jump_stmt  */
#line 389 "parser.y"
      {
          (yyval.node) = (yyvsp[0].node);
      }
#line 2092 "parser.tab.c"
    break;

  case 33: /* statement: io_stmt  */
#line 393 "parser.y"
      {
          (yyval.node) = (yyvsp[0].node);
      }
#line 2100 "parser.tab.c"
    break;

  case 34: /* statement: compound_stmt  */
#line 397 "parser.y"
      {
          (yyval.node) = (yyvsp[0].node);
      }
#line 2108 "parser.tab.c"
    break;

  case 35: /* statement: error SEMICOLON  */
#line 401 "parser.y"
      {
          fprintf(stderr, "Recovered from syntax error at line %d.\n", line_no);
          yyerrok;
          (yyval.node) = NULL;
      }
#line 2118 "parser.tab.c"
    break;

  case 36: /* $@3: %empty  */
#line 410 "parser.y"
      {
          current_decl_type = (NebulaType)(yyvsp[0].type_val);
      }
#line 2126 "parser.tab.c"
    break;

  case 37: /* declaration_stmt: type_spec $@3 init_declarator_list SEMICOLON  */
#line 414 "parser.y"
      {
          (yyval.node) = (yyvsp[-1].node);
      }
#line 2134 "parser.tab.c"
    break;

  case 38: /* init_declarator_list: init_declarator  */
#line 421 "parser.y"
      {
          (yyval.node) = (yyvsp[0].node);
      }
#line 2142 "parser.tab.c"
    break;

  case 39: /* init_declarator_list: init_declarator_list COMMA init_declarator  */
#line 425 "parser.y"
      {
          (yyval.node) = append_node((yyvsp[-2].node), (yyvsp[0].node));
      }
#line 2150 "parser.tab.c"
    break;

  case 40: /* init_declarator: IDENTIFIER  */
#line 432 "parser.y"
      {
          ASTNode *decl = new_ast_node(AST_DECL, (yyvsp[0].str_val));
          decl->inferred_type = current_decl_type;
          declare_variable((yyvsp[0].str_val), current_decl_type, line_no);
          (yyval.node) = decl;
          free((yyvsp[0].str_val));
      }
#line 2162 "parser.tab.c"
    break;

  case 41: /* init_declarator: IDENTIFIER ASSIGN expression  */
#line 440 "parser.y"
      {
          ASTNode *decl = new_ast_node(AST_DECL, (yyvsp[-2].str_val));
          decl->inferred_type = current_decl_type;
          decl->left = (yyvsp[0].expr).node;
          declare_variable((yyvsp[-2].str_val), current_decl_type, line_no);
          if (!is_assignment_compatible(current_decl_type, (yyvsp[0].expr).type)) {
              semantic_error(line_no, "Type mismatch in declaration assignment (%s = %s)", type_name(current_decl_type), type_name((yyvsp[0].expr).type));
          }
          (yyval.node) = decl;
          free((yyvsp[-2].str_val));
      }
#line 2178 "parser.tab.c"
    break;

  case 42: /* expression_stmt: expression SEMICOLON  */
#line 455 "parser.y"
      {
          ASTNode *st = new_ast_node(AST_EXPR_STMT, "expr");
          st->left = (yyvsp[-1].expr).node;
          (yyval.node) = st;
      }
#line 2188 "parser.tab.c"
    break;

  case 43: /* expression_stmt: SEMICOLON  */
#line 461 "parser.y"
      {
          (yyval.node) = NULL;
      }
#line 2196 "parser.tab.c"
    break;

  case 44: /* selection_stmt: WHEN LPAREN expression RPAREN statement  */
#line 468 "parser.y"
      {
          ASTNode *node = new_ast_node(AST_IF, "when");
          node->left = (yyvsp[-2].expr).node;
          node->right = (yyvsp[0].node);
          check_condition_type((yyvsp[-2].expr).type, line_no, "when");
          (yyval.node) = node;
      }
#line 2208 "parser.tab.c"
    break;

  case 45: /* selection_stmt: WHEN LPAREN expression RPAREN statement OTHERWISE statement  */
#line 476 "parser.y"
      {
          ASTNode *node = new_ast_node(AST_IF, "when-otherwise");
          node->left = (yyvsp[-4].expr).node;
          node->right = (yyvsp[-2].node);
          node->third = (yyvsp[0].node);
          check_condition_type((yyvsp[-4].expr).type, line_no, "when");
          (yyval.node) = node;
      }
#line 2221 "parser.tab.c"
    break;

  case 46: /* selection_stmt: IF LPAREN expression RPAREN statement  */
#line 485 "parser.y"
      {
          ASTNode *node = new_ast_node(AST_IF, "if");
          node->left = (yyvsp[-2].expr).node;
          node->right = (yyvsp[0].node);
          check_condition_type((yyvsp[-2].expr).type, line_no, "if");
          (yyval.node) = node;
      }
#line 2233 "parser.tab.c"
    break;

  case 47: /* selection_stmt: IF LPAREN expression RPAREN statement ELSE statement  */
#line 493 "parser.y"
      {
          ASTNode *node = new_ast_node(AST_IF, "if-else");
          node->left = (yyvsp[-4].expr).node;
          node->right = (yyvsp[-2].node);
          node->third = (yyvsp[0].node);
          check_condition_type((yyvsp[-4].expr).type, line_no, "if");
          (yyval.node) = node;
      }
#line 2246 "parser.tab.c"
    break;

  case 48: /* selection_stmt: SWITCH LPAREN expression RPAREN LBRACE case_clauses_opt default_clause_opt RBRACE  */
#line 502 "parser.y"
      {
          ASTNode *node = new_ast_node(AST_IF, "switch");
          node->left = (yyvsp[-5].expr).node;
          node->right = (yyvsp[-2].node);
          node->third = (yyvsp[-1].node);
          (yyval.node) = node;
      }
#line 2258 "parser.tab.c"
    break;

  case 49: /* case_clauses_opt: %empty  */
#line 513 "parser.y"
      {
          (yyval.node) = NULL;
      }
#line 2266 "parser.tab.c"
    break;

  case 50: /* case_clauses_opt: case_clauses_opt case_clause  */
#line 517 "parser.y"
      {
          (yyval.node) = append_node((yyvsp[-1].node), (yyvsp[0].node));
      }
#line 2274 "parser.tab.c"
    break;

  case 51: /* case_clause: CASE expression COLON stmt_list_opt  */
#line 524 "parser.y"
      {
          ASTNode *node = new_ast_node(AST_IF, "case");
          node->left = (yyvsp[-2].expr).node;
          node->right = (yyvsp[0].node);
          (yyval.node) = node;
      }
#line 2285 "parser.tab.c"
    break;

  case 52: /* default_clause_opt: %empty  */
#line 534 "parser.y"
      {
          (yyval.node) = NULL;
      }
#line 2293 "parser.tab.c"
    break;

  case 53: /* default_clause_opt: DEFAULT COLON stmt_list_opt  */
#line 538 "parser.y"
      {
          ASTNode *node = new_ast_node(AST_IF, "default");
          node->right = (yyvsp[0].node);
          (yyval.node) = node;
      }
#line 2303 "parser.tab.c"
    break;

  case 54: /* loop_stmt: LOOP LPAREN expression RPAREN statement  */
#line 547 "parser.y"
      {
          ASTNode *node = new_ast_node(AST_WHILE, "loop-while");
          node->left = (yyvsp[-2].expr).node;
          node->body = (yyvsp[0].node);
          check_condition_type((yyvsp[-2].expr).type, line_no, "loop");
          (yyval.node) = node;
      }
#line 2315 "parser.tab.c"
    break;

  case 55: /* loop_stmt: LOOP LPAREN opt_expr SEMICOLON opt_expr SEMICOLON opt_expr RPAREN statement  */
#line 555 "parser.y"
      {
          ASTNode *node = new_ast_node(AST_LOOP, "loop");
          node->left = (yyvsp[-6].expr).node;
          node->right = (yyvsp[-4].expr).node;
          node->third = (yyvsp[-2].expr).node;
          node->body = (yyvsp[0].node);
          if ((yyvsp[-4].expr).type != TYPE_UNKNOWN) {
              check_condition_type((yyvsp[-4].expr).type, line_no, "loop");
          }
          (yyval.node) = node;
      }
#line 2331 "parser.tab.c"
    break;

  case 56: /* loop_stmt: WHILE LPAREN expression RPAREN statement  */
#line 567 "parser.y"
      {
          ASTNode *node = new_ast_node(AST_WHILE, "while");
          node->left = (yyvsp[-2].expr).node;
          node->body = (yyvsp[0].node);
          check_condition_type((yyvsp[-2].expr).type, line_no, "while");
          (yyval.node) = node;
      }
#line 2343 "parser.tab.c"
    break;

  case 57: /* loop_stmt: DO statement WHILE LPAREN expression RPAREN SEMICOLON  */
#line 575 "parser.y"
      {
          ASTNode *node = new_ast_node(AST_DO_WHILE, "do-while");
          node->left = (yyvsp[-2].expr).node;
          node->body = (yyvsp[-5].node);
          check_condition_type((yyvsp[-2].expr).type, line_no, "do-while");
          (yyval.node) = node;
      }
#line 2355 "parser.tab.c"
    break;

  case 58: /* loop_stmt: FOR LPAREN opt_expr SEMICOLON opt_expr SEMICOLON opt_expr RPAREN statement  */
#line 583 "parser.y"
      {
          ASTNode *node = new_ast_node(AST_FOR, "for");
          node->left = (yyvsp[-6].expr).node;
          node->right = (yyvsp[-4].expr).node;
          node->third = (yyvsp[-2].expr).node;
          node->body = (yyvsp[0].node);
          if ((yyvsp[-4].expr).type != TYPE_UNKNOWN) {
              check_condition_type((yyvsp[-4].expr).type, line_no, "for");
          }
          (yyval.node) = node;
      }
#line 2371 "parser.tab.c"
    break;

  case 59: /* opt_expr: %empty  */
#line 598 "parser.y"
      {
          (yyval.expr) = make_expr(TYPE_UNKNOWN, NULL);
      }
#line 2379 "parser.tab.c"
    break;

  case 60: /* opt_expr: expression  */
#line 602 "parser.y"
      {
          (yyval.expr) = (yyvsp[0].expr);
      }
#line 2387 "parser.tab.c"
    break;

  case 61: /* jump_stmt: GIVE expression SEMICOLON  */
#line 609 "parser.y"
      {
          ASTNode *node = new_ast_node(AST_UNARYOP, "give");
          node->left = (yyvsp[-1].expr).node;
          (yyval.node) = node;
      }
#line 2397 "parser.tab.c"
    break;

  case 62: /* jump_stmt: RETURN expression SEMICOLON  */
#line 615 "parser.y"
      {
          ASTNode *node = new_ast_node(AST_UNARYOP, "return");
          node->left = (yyvsp[-1].expr).node;
          (yyval.node) = node;
      }
#line 2407 "parser.tab.c"
    break;

  case 63: /* jump_stmt: BREAK SEMICOLON  */
#line 621 "parser.y"
      {
          (yyval.node) = new_ast_node(AST_UNARYOP, "break");
      }
#line 2415 "parser.tab.c"
    break;

  case 64: /* jump_stmt: CONTINUE SEMICOLON  */
#line 625 "parser.y"
      {
          (yyval.node) = new_ast_node(AST_UNARYOP, "continue");
      }
#line 2423 "parser.tab.c"
    break;

  case 65: /* io_stmt: PRINT LPAREN print_arg_list_opt RPAREN SEMICOLON  */
#line 632 "parser.y"
      {
          ASTNode *node = new_ast_node(AST_PRINT, "print");
          node->left = (yyvsp[-2].node);
          (yyval.node) = node;
      }
#line 2433 "parser.tab.c"
    break;

  case 66: /* io_stmt: INPUT LPAREN IDENTIFIER RPAREN SEMICOLON  */
#line 638 "parser.y"
      {
          ASTNode *node = new_ast_node(AST_INPUT, (yyvsp[-2].str_val));
          (void)resolve_identifier_type((yyvsp[-2].str_val), line_no);
          (yyval.node) = node;
          free((yyvsp[-2].str_val));
      }
#line 2444 "parser.tab.c"
    break;

  case 67: /* print_arg_list_opt: %empty  */
#line 648 "parser.y"
      {
          (yyval.node) = NULL;
      }
#line 2452 "parser.tab.c"
    break;

  case 68: /* print_arg_list_opt: print_arg_list  */
#line 652 "parser.y"
      {
          (yyval.node) = (yyvsp[0].node);
      }
#line 2460 "parser.tab.c"
    break;

  case 69: /* print_arg_list: print_arg  */
#line 659 "parser.y"
      {
          (yyval.node) = (yyvsp[0].node);
      }
#line 2468 "parser.tab.c"
    break;

  case 70: /* print_arg_list: print_arg_list COMMA print_arg  */
#line 663 "parser.y"
      {
          (yyval.node) = append_node((yyvsp[-2].node), (yyvsp[0].node));
      }
#line 2476 "parser.tab.c"
    break;

  case 71: /* print_arg: expression  */
#line 670 "parser.y"
      {
          (yyval.node) = (yyvsp[0].expr).node;
      }
#line 2484 "parser.tab.c"
    break;

  case 72: /* function_call: IDENTIFIER LPAREN argument_list_opt RPAREN  */
#line 677 "parser.y"
      {
          ASTNode *call = new_ast_node(AST_FUNC_CALL, (yyvsp[-3].str_val));
          call->left = (yyvsp[-1].node);
          (yyval.node) = call;
          free((yyvsp[-3].str_val));
      }
#line 2495 "parser.tab.c"
    break;

  case 73: /* argument_list_opt: %empty  */
#line 687 "parser.y"
      {
          (yyval.node) = NULL;
      }
#line 2503 "parser.tab.c"
    break;

  case 74: /* argument_list_opt: argument_list  */
#line 691 "parser.y"
      {
          (yyval.node) = (yyvsp[0].node);
      }
#line 2511 "parser.tab.c"
    break;

  case 75: /* argument_list: expression  */
#line 698 "parser.y"
      {
          (yyval.node) = (yyvsp[0].expr).node;
      }
#line 2519 "parser.tab.c"
    break;

  case 76: /* argument_list: argument_list COMMA expression  */
#line 702 "parser.y"
      {
          (yyval.node) = append_node((yyvsp[-2].node), (yyvsp[0].expr).node);
      }
#line 2527 "parser.tab.c"
    break;

  case 77: /* expression: assignment_expr  */
#line 709 "parser.y"
      {
          (yyval.expr) = (yyvsp[0].expr);
      }
#line 2535 "parser.tab.c"
    break;

  case 78: /* assignment_expr: conditional_expr  */
#line 716 "parser.y"
      {
          (yyval.expr) = (yyvsp[0].expr);
      }
#line 2543 "parser.tab.c"
    break;

  case 79: /* assignment_expr: IDENTIFIER ASSIGN assignment_expr  */
#line 720 "parser.y"
      {
          NebulaType lhs = resolve_identifier_type((yyvsp[-2].str_val), line_no);
          NebulaType rhs = (yyvsp[0].expr).type;
          ASTNode *id = new_ast_node(AST_IDENTIFIER, (yyvsp[-2].str_val));
          ASTNode *as = new_ast_node(AST_ASSIGN, "=");
          as->left = id;
          as->right = (yyvsp[0].expr).node;
          as->inferred_type = lhs;
          if (lhs != TYPE_UNKNOWN && rhs != TYPE_UNKNOWN && !is_assignment_compatible(lhs, rhs)) {
              semantic_error(line_no, "Type mismatch in assignment (%s = %s)", type_name(lhs), type_name(rhs));
          }
          (yyval.expr) = make_expr(lhs, as);
          free((yyvsp[-2].str_val));
      }
#line 2562 "parser.tab.c"
    break;

  case 80: /* conditional_expr: logical_or_expr  */
#line 738 "parser.y"
      {
          (yyval.expr) = (yyvsp[0].expr);
      }
#line 2570 "parser.tab.c"
    break;

  case 81: /* conditional_expr: logical_or_expr QMARK expression COLON conditional_expr  */
#line 742 "parser.y"
      {
          NebulaType out_type;
          ASTNode *node = new_ast_node(AST_IF, "?:");
          node->left = (yyvsp[-4].expr).node;
          node->right = (yyvsp[-2].expr).node;
          node->third = (yyvsp[0].expr).node;
          check_condition_type((yyvsp[-4].expr).type, line_no, "?:");
          if (is_assignment_compatible((yyvsp[-2].expr).type, (yyvsp[0].expr).type)) {
              out_type = (yyvsp[-2].expr).type;
          } else if (is_assignment_compatible((yyvsp[0].expr).type, (yyvsp[-2].expr).type)) {
              out_type = (yyvsp[0].expr).type;
          } else {
              semantic_error(line_no, "Type mismatch in conditional expression (%s : %s)", type_name((yyvsp[-2].expr).type), type_name((yyvsp[0].expr).type));
              out_type = TYPE_UNKNOWN;
          }
          node->inferred_type = out_type;
          (yyval.expr) = make_expr(out_type, node);
      }
#line 2593 "parser.tab.c"
    break;

  case 82: /* logical_or_expr: logical_and_expr  */
#line 764 "parser.y"
      {
          (yyval.expr) = (yyvsp[0].expr);
      }
#line 2601 "parser.tab.c"
    break;

  case 83: /* logical_or_expr: logical_or_expr OR logical_and_expr  */
#line 768 "parser.y"
      {
          NebulaType t = logical_result_type((yyvsp[-2].expr).type, (yyvsp[0].expr).type, "||", line_no);
          (yyval.expr) = make_expr(t, new_ast_binary(AST_BINOP, "||", (yyvsp[-2].expr).node, (yyvsp[0].expr).node, t));
      }
#line 2610 "parser.tab.c"
    break;

  case 84: /* logical_and_expr: bitwise_or_expr  */
#line 776 "parser.y"
      {
          (yyval.expr) = (yyvsp[0].expr);
      }
#line 2618 "parser.tab.c"
    break;

  case 85: /* logical_and_expr: logical_and_expr AND bitwise_or_expr  */
#line 780 "parser.y"
      {
          NebulaType t = logical_result_type((yyvsp[-2].expr).type, (yyvsp[0].expr).type, "&&", line_no);
          (yyval.expr) = make_expr(t, new_ast_binary(AST_BINOP, "&&", (yyvsp[-2].expr).node, (yyvsp[0].expr).node, t));
      }
#line 2627 "parser.tab.c"
    break;

  case 86: /* bitwise_or_expr: bitwise_xor_expr  */
#line 788 "parser.y"
      {
          (yyval.expr) = (yyvsp[0].expr);
      }
#line 2635 "parser.tab.c"
    break;

  case 87: /* bitwise_or_expr: bitwise_or_expr BIT_OR bitwise_xor_expr  */
#line 792 "parser.y"
      {
          NebulaType t = bitwise_result_type((yyvsp[-2].expr).type, (yyvsp[0].expr).type, "|", line_no);
          (yyval.expr) = make_expr(t, new_ast_binary(AST_BINOP, "|", (yyvsp[-2].expr).node, (yyvsp[0].expr).node, t));
      }
#line 2644 "parser.tab.c"
    break;

  case 88: /* bitwise_xor_expr: bitwise_and_expr  */
#line 800 "parser.y"
      {
          (yyval.expr) = (yyvsp[0].expr);
      }
#line 2652 "parser.tab.c"
    break;

  case 89: /* bitwise_xor_expr: bitwise_xor_expr BIT_XOR bitwise_and_expr  */
#line 804 "parser.y"
      {
          NebulaType t = bitwise_result_type((yyvsp[-2].expr).type, (yyvsp[0].expr).type, "^", line_no);
          (yyval.expr) = make_expr(t, new_ast_binary(AST_BINOP, "^", (yyvsp[-2].expr).node, (yyvsp[0].expr).node, t));
      }
#line 2661 "parser.tab.c"
    break;

  case 90: /* bitwise_and_expr: equality_expr  */
#line 812 "parser.y"
      {
          (yyval.expr) = (yyvsp[0].expr);
      }
#line 2669 "parser.tab.c"
    break;

  case 91: /* bitwise_and_expr: bitwise_and_expr BIT_AND equality_expr  */
#line 816 "parser.y"
      {
          NebulaType t = bitwise_result_type((yyvsp[-2].expr).type, (yyvsp[0].expr).type, "&", line_no);
          (yyval.expr) = make_expr(t, new_ast_binary(AST_BINOP, "&", (yyvsp[-2].expr).node, (yyvsp[0].expr).node, t));
      }
#line 2678 "parser.tab.c"
    break;

  case 92: /* equality_expr: relational_expr  */
#line 824 "parser.y"
      {
          (yyval.expr) = (yyvsp[0].expr);
      }
#line 2686 "parser.tab.c"
    break;

  case 93: /* equality_expr: equality_expr EQ relational_expr  */
#line 828 "parser.y"
      {
          NebulaType t = equality_result_type((yyvsp[-2].expr).type, (yyvsp[0].expr).type, "==", line_no);
          (yyval.expr) = make_expr(t, new_ast_binary(AST_BINOP, "==", (yyvsp[-2].expr).node, (yyvsp[0].expr).node, t));
      }
#line 2695 "parser.tab.c"
    break;

  case 94: /* equality_expr: equality_expr NEQ relational_expr  */
#line 833 "parser.y"
      {
          NebulaType t = equality_result_type((yyvsp[-2].expr).type, (yyvsp[0].expr).type, "!=", line_no);
          (yyval.expr) = make_expr(t, new_ast_binary(AST_BINOP, "!=", (yyvsp[-2].expr).node, (yyvsp[0].expr).node, t));
      }
#line 2704 "parser.tab.c"
    break;

  case 95: /* relational_expr: shift_expr  */
#line 841 "parser.y"
      {
          (yyval.expr) = (yyvsp[0].expr);
      }
#line 2712 "parser.tab.c"
    break;

  case 96: /* relational_expr: relational_expr LT shift_expr  */
#line 845 "parser.y"
      {
          NebulaType t = relational_result_type((yyvsp[-2].expr).type, (yyvsp[0].expr).type, "<", line_no);
          (yyval.expr) = make_expr(t, new_ast_binary(AST_BINOP, "<", (yyvsp[-2].expr).node, (yyvsp[0].expr).node, t));
      }
#line 2721 "parser.tab.c"
    break;

  case 97: /* relational_expr: relational_expr GT shift_expr  */
#line 850 "parser.y"
      {
          NebulaType t = relational_result_type((yyvsp[-2].expr).type, (yyvsp[0].expr).type, ">", line_no);
          (yyval.expr) = make_expr(t, new_ast_binary(AST_BINOP, ">", (yyvsp[-2].expr).node, (yyvsp[0].expr).node, t));
      }
#line 2730 "parser.tab.c"
    break;

  case 98: /* relational_expr: relational_expr LE shift_expr  */
#line 855 "parser.y"
      {
          NebulaType t = relational_result_type((yyvsp[-2].expr).type, (yyvsp[0].expr).type, "<=", line_no);
          (yyval.expr) = make_expr(t, new_ast_binary(AST_BINOP, "<=", (yyvsp[-2].expr).node, (yyvsp[0].expr).node, t));
      }
#line 2739 "parser.tab.c"
    break;

  case 99: /* relational_expr: relational_expr GE shift_expr  */
#line 860 "parser.y"
      {
          NebulaType t = relational_result_type((yyvsp[-2].expr).type, (yyvsp[0].expr).type, ">=", line_no);
          (yyval.expr) = make_expr(t, new_ast_binary(AST_BINOP, ">=", (yyvsp[-2].expr).node, (yyvsp[0].expr).node, t));
      }
#line 2748 "parser.tab.c"
    break;

  case 100: /* shift_expr: additive_expr  */
#line 868 "parser.y"
      {
          (yyval.expr) = (yyvsp[0].expr);
      }
#line 2756 "parser.tab.c"
    break;

  case 101: /* shift_expr: shift_expr LSHIFT additive_expr  */
#line 872 "parser.y"
      {
          NebulaType t = bitwise_result_type((yyvsp[-2].expr).type, (yyvsp[0].expr).type, "<<", line_no);
          (yyval.expr) = make_expr(t, new_ast_binary(AST_BINOP, "<<", (yyvsp[-2].expr).node, (yyvsp[0].expr).node, t));
      }
#line 2765 "parser.tab.c"
    break;

  case 102: /* shift_expr: shift_expr RSHIFT additive_expr  */
#line 877 "parser.y"
      {
          NebulaType t = bitwise_result_type((yyvsp[-2].expr).type, (yyvsp[0].expr).type, ">>", line_no);
          (yyval.expr) = make_expr(t, new_ast_binary(AST_BINOP, ">>", (yyvsp[-2].expr).node, (yyvsp[0].expr).node, t));
      }
#line 2774 "parser.tab.c"
    break;

  case 103: /* additive_expr: multiplicative_expr  */
#line 885 "parser.y"
      {
          (yyval.expr) = (yyvsp[0].expr);
      }
#line 2782 "parser.tab.c"
    break;

  case 104: /* additive_expr: additive_expr PLUS multiplicative_expr  */
#line 889 "parser.y"
      {
          NebulaType t = arithmetic_result_type((yyvsp[-2].expr).type, (yyvsp[0].expr).type, "+", line_no);
          (yyval.expr) = make_expr(t, new_ast_binary(AST_BINOP, "+", (yyvsp[-2].expr).node, (yyvsp[0].expr).node, t));
      }
#line 2791 "parser.tab.c"
    break;

  case 105: /* additive_expr: additive_expr MINUS multiplicative_expr  */
#line 894 "parser.y"
      {
          NebulaType t = arithmetic_result_type((yyvsp[-2].expr).type, (yyvsp[0].expr).type, "-", line_no);
          (yyval.expr) = make_expr(t, new_ast_binary(AST_BINOP, "-", (yyvsp[-2].expr).node, (yyvsp[0].expr).node, t));
      }
#line 2800 "parser.tab.c"
    break;

  case 106: /* multiplicative_expr: unary_expr  */
#line 902 "parser.y"
      {
          (yyval.expr) = (yyvsp[0].expr);
      }
#line 2808 "parser.tab.c"
    break;

  case 107: /* multiplicative_expr: multiplicative_expr MUL unary_expr  */
#line 906 "parser.y"
      {
          NebulaType t = arithmetic_result_type((yyvsp[-2].expr).type, (yyvsp[0].expr).type, "*", line_no);
          (yyval.expr) = make_expr(t, new_ast_binary(AST_BINOP, "*", (yyvsp[-2].expr).node, (yyvsp[0].expr).node, t));
      }
#line 2817 "parser.tab.c"
    break;

  case 108: /* multiplicative_expr: multiplicative_expr DIV unary_expr  */
#line 911 "parser.y"
      {
          NebulaType t = arithmetic_result_type((yyvsp[-2].expr).type, (yyvsp[0].expr).type, "/", line_no);
          (yyval.expr) = make_expr(t, new_ast_binary(AST_BINOP, "/", (yyvsp[-2].expr).node, (yyvsp[0].expr).node, t));
      }
#line 2826 "parser.tab.c"
    break;

  case 109: /* unary_expr: postfix_expr  */
#line 919 "parser.y"
      {
          (yyval.expr) = (yyvsp[0].expr);
      }
#line 2834 "parser.tab.c"
    break;

  case 110: /* unary_expr: PLUS unary_expr  */
#line 923 "parser.y"
      {
          NebulaType t = unary_plus_minus_type((yyvsp[0].expr).type, "+", line_no);
          (yyval.expr) = make_expr(t, new_ast_unary(AST_UNARYOP, "+", (yyvsp[0].expr).node, t));
      }
#line 2843 "parser.tab.c"
    break;

  case 111: /* unary_expr: MINUS unary_expr  */
#line 928 "parser.y"
      {
          NebulaType t = unary_plus_minus_type((yyvsp[0].expr).type, "-", line_no);
          (yyval.expr) = make_expr(t, new_ast_unary(AST_UNARYOP, "-", (yyvsp[0].expr).node, t));
      }
#line 2852 "parser.tab.c"
    break;

  case 112: /* unary_expr: NOT unary_expr  */
#line 933 "parser.y"
      {
          NebulaType t = unary_not_type((yyvsp[0].expr).type, line_no);
          (yyval.expr) = make_expr(t, new_ast_unary(AST_UNARYOP, "!", (yyvsp[0].expr).node, t));
      }
#line 2861 "parser.tab.c"
    break;

  case 113: /* unary_expr: BIT_NOT unary_expr  */
#line 938 "parser.y"
      {
          NebulaType t = unary_bitnot_type((yyvsp[0].expr).type, line_no);
          (yyval.expr) = make_expr(t, new_ast_unary(AST_UNARYOP, "~", (yyvsp[0].expr).node, t));
      }
#line 2870 "parser.tab.c"
    break;

  case 114: /* unary_expr: INC unary_expr  */
#line 943 "parser.y"
      {
          NebulaType t = incdec_type((yyvsp[0].expr).type, "++", line_no);
          (yyval.expr) = make_expr(t, new_ast_unary(AST_UNARYOP, "++", (yyvsp[0].expr).node, t));
      }
#line 2879 "parser.tab.c"
    break;

  case 115: /* unary_expr: DECREMENT unary_expr  */
#line 948 "parser.y"
      {
          NebulaType t = incdec_type((yyvsp[0].expr).type, "--", line_no);
          (yyval.expr) = make_expr(t, new_ast_unary(AST_UNARYOP, "--", (yyvsp[0].expr).node, t));
      }
#line 2888 "parser.tab.c"
    break;

  case 116: /* postfix_expr: primary_expr  */
#line 956 "parser.y"
      {
          (yyval.expr) = (yyvsp[0].expr);
      }
#line 2896 "parser.tab.c"
    break;

  case 117: /* postfix_expr: postfix_expr INC  */
#line 960 "parser.y"
      {
          NebulaType t = incdec_type((yyvsp[-1].expr).type, "++", line_no);
          (yyval.expr) = make_expr(t, new_ast_unary(AST_UNARYOP, "post++", (yyvsp[-1].expr).node, t));
      }
#line 2905 "parser.tab.c"
    break;

  case 118: /* postfix_expr: postfix_expr DECREMENT  */
#line 965 "parser.y"
      {
          NebulaType t = incdec_type((yyvsp[-1].expr).type, "--", line_no);
          (yyval.expr) = make_expr(t, new_ast_unary(AST_UNARYOP, "post--", (yyvsp[-1].expr).node, t));
      }
#line 2914 "parser.tab.c"
    break;

  case 119: /* postfix_expr: postfix_expr LBRACKET expression RBRACKET  */
#line 970 "parser.y"
      {
          ASTNode *idx = new_ast_binary(AST_BINOP, "[]", (yyvsp[-3].expr).node, (yyvsp[-1].expr).node, (yyvsp[-3].expr).type);
          if ((yyvsp[-1].expr).type != TYPE_NUM) {
              semantic_error(line_no, "Array index must be num, found %s", type_name((yyvsp[-1].expr).type));
          }
          (yyval.expr) = make_expr((yyvsp[-3].expr).type, idx);
      }
#line 2926 "parser.tab.c"
    break;

  case 120: /* primary_expr: IDENTIFIER  */
#line 981 "parser.y"
      {
          NebulaType t = resolve_identifier_type((yyvsp[0].str_val), line_no);
          ASTNode *id = new_ast_node(AST_IDENTIFIER, (yyvsp[0].str_val));
          id->inferred_type = t;
          (yyval.expr) = make_expr(t, id);
          free((yyvsp[0].str_val));
      }
#line 2938 "parser.tab.c"
    break;

  case 121: /* primary_expr: NUM_LITERAL  */
#line 989 "parser.y"
      {
          char buf[64];
          snprintf(buf, sizeof(buf), "%d", (yyvsp[0].num_val));
          (yyval.expr) = make_expr(TYPE_NUM, new_ast_node(AST_LITERAL, buf));
      }
#line 2948 "parser.tab.c"
    break;

  case 122: /* primary_expr: DEC_LITERAL  */
#line 995 "parser.y"
      {
          char buf[64];
          snprintf(buf, sizeof(buf), "%g", (yyvsp[0].dec_val));
          (yyval.expr) = make_expr(TYPE_DEC, new_ast_node(AST_LITERAL, buf));
      }
#line 2958 "parser.tab.c"
    break;

  case 123: /* primary_expr: CHAR_LITERAL  */
#line 1001 "parser.y"
      {
          char buf[8];
          snprintf(buf, sizeof(buf), "'%c'", (yyvsp[0].char_val));
          (yyval.expr) = make_expr(TYPE_CHAR, new_ast_node(AST_LITERAL, buf));
      }
#line 2968 "parser.tab.c"
    break;

  case 124: /* primary_expr: STRING_LITERAL  */
#line 1007 "parser.y"
      {
          (yyval.expr) = make_expr(TYPE_UNKNOWN, new_ast_node(AST_LITERAL, (yyvsp[0].str_val)));
          free((yyvsp[0].str_val));
      }
#line 2977 "parser.tab.c"
    break;

  case 125: /* primary_expr: TRUE  */
#line 1012 "parser.y"
      {
          (yyval.expr) = make_expr(TYPE_BOOL, new_ast_node(AST_LITERAL, "true"));
      }
#line 2985 "parser.tab.c"
    break;

  case 126: /* primary_expr: FALSE  */
#line 1016 "parser.y"
      {
          (yyval.expr) = make_expr(TYPE_BOOL, new_ast_node(AST_LITERAL, "false"));
      }
#line 2993 "parser.tab.c"
    break;

  case 127: /* primary_expr: function_call  */
#line 1020 "parser.y"
      {
          (yyval.expr) = make_expr(TYPE_UNKNOWN, (yyvsp[0].node));
      }
#line 3001 "parser.tab.c"
    break;

  case 128: /* primary_expr: INPUT LPAREN RPAREN  */
#line 1024 "parser.y"
      {
          (yyval.expr) = make_expr(TYPE_UNKNOWN, new_ast_node(AST_INPUT, "input"));
      }
#line 3009 "parser.tab.c"
    break;

  case 129: /* primary_expr: LPAREN expression RPAREN  */
#line 1028 "parser.y"
      {
          (yyval.expr) = (yyvsp[-1].expr);
      }
#line 3017 "parser.tab.c"
    break;


#line 3021 "parser.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      {
        yypcontext_t yyctx
          = {yyssp, yytoken};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          YYNOMEM;
      }
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 1033 "parser.y"


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
            execute_program(ast_root);
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
        if (v.type == TYPE_DEC) {
            out.num = (int)v.dec;
        } else if (v.type == TYPE_BOOL) {
            out.num = v.boolean;
        } else if (v.type == TYPE_CHAR) {
            out.num = (unsigned char)v.ch;
        } else {
            out.num = v.num;
        }
        out.dec = (double)out.num;
        out.boolean = (out.num != 0);
        return out;
    }
    if (t == TYPE_DEC) {
        if (v.type == TYPE_NUM) {
            out.dec = (double)v.num;
        } else if (v.type == TYPE_BOOL) {
            out.dec = (double)v.boolean;
        } else if (v.type == TYPE_CHAR) {
            out.dec = (double)(unsigned char)v.ch;
        } else {
            out.dec = v.dec;
        }
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
        if (v.type == TYPE_NUM) {
            out.ch = (char)v.num;
        } else if (v.type == TYPE_DEC) {
            out.ch = (char)((int)v.dec);
        } else if (v.type == TYPE_BOOL) {
            out.ch = (char)v.boolean;
        } else {
            out.ch = v.ch;
        }
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
            if (prev) {
                prev->next = curr->next;
            } else {
                runtime_env = curr->next;
            }
            curr = curr->next;
            if (dead->value.str) {
                free(dead->value.str);
            }
            free(dead->name);
            free(dead);
        } else {
            prev = curr;
            curr = curr->next;
        }
    }
    if (runtime_scope > 0) {
        runtime_scope--;
    }
}

static void runtime_declare_var(const char *name, RuntimeValue v) {
    RuntimeVar *var = runtime_lookup_var_current_scope(name);
    if (var) {
        return;
    }
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
    if (!var) {
        fprintf(stderr, "Runtime Error: assignment to undeclared variable '%s'\n", name);
        return;
    }
    casted = runtime_cast_to(var->value.type, v);
    if (var->value.str) {
        free(var->value.str);
    }
    var->value = casted;
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
    if (v.type == TYPE_BOOL) {
        return v.boolean != 0;
    }
    if (v.type == TYPE_NUM) {
        return v.num != 0;
    }
    if (v.type == TYPE_DEC) {
        return v.dec != 0.0;
    }
    if (v.type == TYPE_CHAR) {
        return v.ch != '\0';
    }
    return 0;
}

static FunctionDef *runtime_find_function(const char *name) {
    FunctionDef *f = function_table;
    while (f) {
        if (strcmp(f->name, name) == 0) {
            return f;
        }
        f = f->next;
    }
    return NULL;
}

static void runtime_register_functions(ASTNode *root) {
    ASTNode *curr;
    function_table = NULL;
    if (!root || root->kind != AST_PROGRAM) {
        return;
    }
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

static RuntimeValue runtime_eval_expr(ASTNode *node) {
    RuntimeValue l;
    RuntimeValue r;
    RuntimeValue out;
    const char *op;
    if (!node) {
        return make_default_value(TYPE_UNKNOWN);
    }

    switch (node->kind) {
        case AST_LITERAL:
            if (!node->text) {
                return make_default_value(TYPE_UNKNOWN);
            }
            if (strcmp(node->text, "true") == 0) {
                return runtime_from_bool(1);
            }
            if (strcmp(node->text, "false") == 0) {
                return runtime_from_bool(0);
            }
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
            if (strcmp(op, "+") == 0) {
                return runtime_eval_expr(node->left);
            }
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
                if (strncmp(op, "post", 4) == 0) {
                    return old;
                }
                return runtime_get_var(id->text);
            }
            return make_default_value(TYPE_UNKNOWN);

        case AST_BINOP:
            op = node->text ? node->text : "";
            if (strcmp(op, "[]") == 0) {
                return runtime_eval_expr(node->left);
            }
            l = runtime_eval_expr(node->left);
            r = runtime_eval_expr(node->right);
            if (strcmp(op, "+") == 0) {
                if (l.type == TYPE_DEC || r.type == TYPE_DEC) return runtime_from_double((l.type == TYPE_DEC ? l.dec : l.num) + (r.type == TYPE_DEC ? r.dec : r.num));
                return runtime_from_int(l.num + r.num);
            }
            if (strcmp(op, "-") == 0) {
                if (l.type == TYPE_DEC || r.type == TYPE_DEC) return runtime_from_double((l.type == TYPE_DEC ? l.dec : l.num) - (r.type == TYPE_DEC ? r.dec : r.num));
                return runtime_from_int(l.num - r.num);
            }
            if (strcmp(op, "*") == 0) {
                if (l.type == TYPE_DEC || r.type == TYPE_DEC) return runtime_from_double((l.type == TYPE_DEC ? l.dec : l.num) * (r.type == TYPE_DEC ? r.dec : r.num));
                return runtime_from_int(l.num * r.num);
            }
            if (strcmp(op, "/") == 0) {
                double rv = (r.type == TYPE_DEC ? r.dec : (double)r.num);
                if (rv == 0.0) {
                    fprintf(stderr, "Runtime Error: division by zero\n");
                    return make_default_value(TYPE_UNKNOWN);
                }
                if (l.type == TYPE_DEC || r.type == TYPE_DEC) return runtime_from_double((l.type == TYPE_DEC ? l.dec : l.num) / rv);
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

    if (!node) {
        return sig;
    }

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
                if (!first) {
                    printf(" ");
                }
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
                if (node->right && !runtime_is_truthy(runtime_eval_expr(node->right))) {
                    break;
                }
                sig = runtime_exec_node(node->body);
                if (sig.has_return) return sig;
                if (sig.has_break) {
                    sig.has_break = 0;
                    break;
                }
                if (node->third) (void)runtime_eval_expr(node->third);
                if (sig.has_continue) {
                    sig.has_continue = 0;
                }
            }
            return sig;

        case AST_WHILE:
            while (runtime_is_truthy(runtime_eval_expr(node->left))) {
                sig = runtime_exec_node(node->body);
                if (sig.has_return) return sig;
                if (sig.has_break) {
                    sig.has_break = 0;
                    break;
                }
                if (sig.has_continue) {
                    sig.has_continue = 0;
                }
            }
            return sig;

        case AST_DO_WHILE:
            do {
                sig = runtime_exec_node(node->body);
                if (sig.has_return) return sig;
                if (sig.has_break) {
                    sig.has_break = 0;
                    break;
                }
                if (sig.has_continue) {
                    sig.has_continue = 0;
                }
            } while (runtime_is_truthy(runtime_eval_expr(node->left)));
            return sig;

        case AST_FOR:
            if (node->left) (void)runtime_eval_expr(node->left);
            while (1) {
                if (node->right && !runtime_is_truthy(runtime_eval_expr(node->right))) {
                    break;
                }
                sig = runtime_exec_node(node->body);
                if (sig.has_return) return sig;
                if (sig.has_break) {
                    sig.has_break = 0;
                    break;
                }
                if (node->third) (void)runtime_eval_expr(node->third);
                if (sig.has_continue) {
                    sig.has_continue = 0;
                }
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
            if (node->body) {
                return sig;
            }
            (void)runtime_eval_expr(node);
            return sig;

        default:
            (void)runtime_eval_expr(node);
            return sig;
    }
}

static void execute_program(ASTNode *root) {
    ASTNode *curr;
    runtime_register_functions(root);
    runtime_scope = 0;
    runtime_env = NULL;

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
