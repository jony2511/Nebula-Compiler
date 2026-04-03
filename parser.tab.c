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

#line 131 "parser.tab.c"

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
  YYSYMBOL_parameter_list_opt = 81,        /* parameter_list_opt  */
  YYSYMBOL_parameter_list = 82,            /* parameter_list  */
  YYSYMBOL_parameter = 83,                 /* parameter  */
  YYSYMBOL_type_spec = 84,                 /* type_spec  */
  YYSYMBOL_compound_stmt = 85,             /* compound_stmt  */
  YYSYMBOL_86_1 = 86,                      /* $@1  */
  YYSYMBOL_stmt_list_opt = 87,             /* stmt_list_opt  */
  YYSYMBOL_stmt_list = 88,                 /* stmt_list  */
  YYSYMBOL_statement = 89,                 /* statement  */
  YYSYMBOL_declaration_stmt = 90,          /* declaration_stmt  */
  YYSYMBOL_91_2 = 91,                      /* $@2  */
  YYSYMBOL_init_declarator_list = 92,      /* init_declarator_list  */
  YYSYMBOL_init_declarator = 93,           /* init_declarator  */
  YYSYMBOL_expression_stmt = 94,           /* expression_stmt  */
  YYSYMBOL_selection_stmt = 95,            /* selection_stmt  */
  YYSYMBOL_case_clauses_opt = 96,          /* case_clauses_opt  */
  YYSYMBOL_case_clause = 97,               /* case_clause  */
  YYSYMBOL_default_clause_opt = 98,        /* default_clause_opt  */
  YYSYMBOL_loop_stmt = 99,                 /* loop_stmt  */
  YYSYMBOL_opt_expr = 100,                 /* opt_expr  */
  YYSYMBOL_jump_stmt = 101,                /* jump_stmt  */
  YYSYMBOL_io_stmt = 102,                  /* io_stmt  */
  YYSYMBOL_print_arg_list_opt = 103,       /* print_arg_list_opt  */
  YYSYMBOL_print_arg_list = 104,           /* print_arg_list  */
  YYSYMBOL_print_arg = 105,                /* print_arg  */
  YYSYMBOL_function_call = 106,            /* function_call  */
  YYSYMBOL_argument_list_opt = 107,        /* argument_list_opt  */
  YYSYMBOL_argument_list = 108,            /* argument_list  */
  YYSYMBOL_expression = 109,               /* expression  */
  YYSYMBOL_assignment_expr = 110,          /* assignment_expr  */
  YYSYMBOL_conditional_expr = 111,         /* conditional_expr  */
  YYSYMBOL_logical_or_expr = 112,          /* logical_or_expr  */
  YYSYMBOL_logical_and_expr = 113,         /* logical_and_expr  */
  YYSYMBOL_bitwise_or_expr = 114,          /* bitwise_or_expr  */
  YYSYMBOL_bitwise_xor_expr = 115,         /* bitwise_xor_expr  */
  YYSYMBOL_bitwise_and_expr = 116,         /* bitwise_and_expr  */
  YYSYMBOL_equality_expr = 117,            /* equality_expr  */
  YYSYMBOL_relational_expr = 118,          /* relational_expr  */
  YYSYMBOL_shift_expr = 119,               /* shift_expr  */
  YYSYMBOL_additive_expr = 120,            /* additive_expr  */
  YYSYMBOL_multiplicative_expr = 121,      /* multiplicative_expr  */
  YYSYMBOL_unary_expr = 122,               /* unary_expr  */
  YYSYMBOL_postfix_expr = 123,             /* postfix_expr  */
  YYSYMBOL_primary_expr = 124              /* primary_expr  */
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
#define YYLAST   554

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  76
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  49
/* YYNRULES -- Number of rules.  */
#define YYNRULES  127
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  237

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
       0,   133,   133,   137,   138,   142,   143,   147,   154,   155,
     159,   160,   164,   171,   172,   173,   174,   175,   176,   177,
     178,   183,   182,   193,   194,   198,   199,   203,   204,   205,
     206,   207,   208,   209,   210,   219,   218,   226,   227,   231,
     236,   247,   248,   252,   256,   260,   264,   268,   272,   273,
     277,   281,   282,   286,   292,   296,   300,   309,   310,   314,
     315,   316,   317,   321,   322,   330,   331,   335,   336,   340,
     344,   352,   353,   357,   358,   362,   367,   369,   382,   384,
     399,   401,   406,   408,   413,   415,   420,   422,   427,   429,
     434,   436,   438,   443,   445,   447,   449,   451,   456,   458,
     460,   465,   467,   469,   474,   476,   478,   483,   485,   487,
     489,   491,   493,   495,   500,   502,   504,   506,   516,   521,
     523,   525,   527,   532,   534,   536,   538,   540
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
  "program", "translation_unit", "external_decl", "function_def",
  "parameter_list_opt", "parameter_list", "parameter", "type_spec",
  "compound_stmt", "$@1", "stmt_list_opt", "stmt_list", "statement",
  "declaration_stmt", "$@2", "init_declarator_list", "init_declarator",
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

#define YYPACT_NINF (-213)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-25)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -213,    33,   351,  -213,   -49,  -213,  -213,  -213,  -213,   -32,
    -213,  -213,  -213,  -213,  -213,  -213,  -213,  -213,    -4,    12,
      14,   486,    19,   -21,   -11,    20,    27,    21,    38,    20,
      41,    42,  -213,  -213,    62,    62,    62,    62,    62,    62,
    -213,    20,  -213,  -213,  -213,  -213,  -213,  -213,  -213,  -213,
    -213,  -213,  -213,  -213,  -213,    45,  -213,  -213,   -30,    63,
      61,    64,    67,   -19,     3,   -25,    15,    16,  -213,   -26,
    -213,  -213,    20,    20,    20,    20,    20,    89,    20,  -213,
    -213,    47,    55,   113,    20,    20,    58,    20,    -3,    57,
    -213,  -213,  -213,  -213,  -213,  -213,    59,   417,   117,  -213,
      62,    20,    62,    62,    62,    62,    62,    62,    62,    62,
      62,    62,    62,    62,    62,    62,    62,    62,  -213,  -213,
      20,  -213,    66,    60,  -213,    68,    70,    71,    65,    72,
    -213,    73,  -213,    75,    77,    78,  -213,    80,    74,  -213,
    -213,    81,  -213,  -213,    76,   212,  -213,    83,   -33,  -213,
      63,    88,    61,    64,    67,   -19,     3,     3,   -25,   -25,
     -25,   -25,    15,    15,    16,    16,  -213,  -213,    84,  -213,
      20,   486,    90,   486,    20,    20,    27,   486,    20,    93,
      20,    95,  -213,  -213,    20,  -213,   117,    62,  -213,  -213,
     111,  -213,  -213,    85,    97,    96,    99,  -213,   127,   131,
     101,  -213,  -213,  -213,  -213,  -213,  -213,   486,    69,   102,
      20,   100,    27,  -213,   486,    20,  -213,    20,   106,  -213,
     103,  -213,   107,  -213,  -213,  -213,   109,   112,   417,  -213,
     486,   486,   281,  -213,  -213,  -213,  -213
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       3,     0,     0,     1,     0,   119,   120,   121,   122,   118,
      18,    19,    20,    13,    14,    15,    16,    17,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   123,   124,     0,     0,     0,     0,     0,     0,
      42,     0,    21,     4,     5,    35,    33,     6,    27,    28,
      29,    30,    31,    32,   125,     0,    75,    76,    78,    80,
      82,    84,    86,    88,    90,    93,    98,   101,   104,   107,
     114,    34,     0,    71,     0,     0,     0,     0,    57,    61,
      62,     0,     0,     0,     0,    57,     0,    65,     0,   118,
     112,   113,   111,   108,   109,   110,     0,     0,     0,    41,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   115,   116,
       0,    77,     0,    72,    73,     0,     0,     0,     0,     0,
      58,     0,    60,     0,     0,     0,    59,     0,    66,    67,
      69,     0,   126,   127,     0,     0,    25,    39,     0,    37,
      81,     0,    83,    85,    87,    89,    91,    92,    96,    97,
      94,    95,    99,   100,   102,   103,   105,   106,     0,    70,
       0,     0,     0,     0,     0,    57,     8,     0,    57,     0,
       0,     0,    22,    26,     0,    36,     0,     0,   117,    74,
      45,    48,    54,     0,     0,     0,     9,    10,     0,    43,
       0,    63,    68,    64,    40,    38,    79,     0,    51,     0,
      57,     0,     0,    12,     0,    57,    46,     0,     0,    49,
       0,    55,     0,     7,    11,    44,     0,     0,     0,    47,
       0,     0,     0,    52,    56,    53,    50
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -213,  -213,  -213,  -213,  -213,  -213,  -213,   -42,   -23,   -34,
    -213,  -212,  -213,    -2,  -213,  -213,  -213,    -8,  -213,  -213,
    -213,  -213,  -213,  -213,   -83,  -213,  -213,  -213,  -213,    -1,
    -213,  -213,  -213,   -24,   108,    -6,  -213,    82,    86,    87,
      79,    91,   -13,   -27,   -10,    -9,   -28,  -213,  -213
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     1,     2,    43,    44,   195,   196,   197,    45,    46,
      97,   144,   145,   146,    48,    98,   148,   149,    49,    50,
     208,   219,   220,    51,   129,    52,    53,   137,   138,   139,
      54,   122,   123,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      47,    82,   135,    83,   141,    86,    90,    91,    92,    93,
      94,    95,   118,   119,    72,    71,   233,    96,   100,    77,
     236,   106,   107,     5,     6,     7,     8,     9,   112,   113,
     101,   185,   186,     3,    73,    10,    11,    12,    13,    14,
      15,    16,    17,    79,   120,   108,   109,   110,   111,   124,
     125,   126,   127,    80,   130,    81,    32,    33,    34,    35,
     134,   130,    74,   140,   142,     5,     6,     7,     8,    89,
     114,   115,    36,   116,   117,    37,    38,   151,    75,    39,
      76,   158,   159,   160,   161,    78,    41,    84,   166,   167,
     217,   218,   194,   156,   157,   200,   168,    81,    32,    33,
      34,    35,   162,   163,    85,   164,   165,    87,    88,    99,
     102,   103,   128,   131,    36,   104,   105,    37,    38,   132,
     133,    39,   136,    73,   147,   170,   143,   222,    41,   184,
     207,   174,   226,   169,   213,   171,   175,   172,   173,   180,
     142,   176,   178,   183,   177,   182,   189,   179,   181,   187,
     193,   130,   209,   198,   130,   188,   140,   201,   191,   203,
     204,   210,   214,   211,   212,   215,   221,   228,    42,   190,
     224,   192,   229,   232,   230,   199,   231,   223,   205,   202,
     121,   206,   150,   154,     0,     0,   130,     0,   152,   198,
     153,   130,     0,   227,     0,     0,   155,     0,     0,     0,
       0,     0,     0,     0,     0,   216,     0,     0,     0,     0,
       0,     0,   225,     4,     0,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,   234,   235,
      18,     0,    19,   -24,   -24,    20,    21,    22,    23,    24,
      25,     0,    27,     0,    28,    29,    30,    31,    32,    33,
      34,    35,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    36,     0,     0,    37,    38,     0,
       0,    39,     0,     0,     0,     0,    40,     0,    41,     0,
      42,   -24,     4,     0,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,     0,     0,    18,
       0,    19,   -23,   -23,    20,    21,    22,    23,    24,    25,
       0,    27,     0,    28,    29,    30,    31,    32,    33,    34,
      35,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    36,     0,     0,    37,    38,     0,     0,
      39,     0,     0,     0,     0,    40,     0,    41,     0,    42,
     -23,    -2,     4,     0,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,     0,     0,    18,
       0,    19,     0,     0,    20,    21,    22,    23,    24,    25,
      26,    27,     0,    28,    29,    30,    31,    32,    33,    34,
      35,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    36,     0,     0,    37,    38,     0,     0,
      39,     0,     0,     0,     0,    40,     0,    41,     4,    42,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,     0,     0,    18,     0,    19,     0,     0,
      20,    21,    22,    23,    24,    25,     0,    27,     0,    28,
      29,    30,    31,    32,    33,    34,    35,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    36,
       0,     0,    37,    38,     0,     0,    39,     0,     0,     0,
       0,    40,     0,    41,     0,    42,   -23,     4,     0,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,     0,     0,    18,     0,    19,     0,     0,    20,
      21,    22,    23,    24,    25,     0,    27,     0,    28,    29,
      30,    31,    32,    33,    34,    35,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    36,     0,
       0,    37,    38,     0,     0,    39,     0,     0,     0,     0,
      40,     0,    41,     0,    42
};

static const yytype_int16 yycheck[] =
{
       2,    25,    85,    26,     7,    29,    34,    35,    36,    37,
      38,    39,    38,    39,    46,    64,   228,    41,    48,    21,
     232,    40,    41,     3,     4,     5,     6,     7,    53,    54,
      60,    64,    65,     0,    66,     8,     9,    10,    11,    12,
      13,    14,    15,    64,    70,    42,    43,    44,    45,    73,
      74,    75,    76,    64,    78,    35,    36,    37,    38,    39,
      84,    85,    66,    87,    67,     3,     4,     5,     6,     7,
      55,    56,    52,    57,    58,    55,    56,   101,    66,    59,
      66,   108,   109,   110,   111,    66,    66,    66,   116,   117,
      21,    22,   175,   106,   107,   178,   120,    35,    36,    37,
      38,    39,   112,   113,    66,   114,   115,    66,    66,    64,
      47,    50,    23,    66,    52,    51,    49,    55,    56,    64,
       7,    59,    64,    66,     7,    65,    67,   210,    66,    46,
      19,    66,   215,    67,     7,    67,    64,    67,    67,    65,
      67,    66,    64,   145,    67,    69,   170,    67,    67,    61,
     174,   175,    67,   176,   178,    71,   180,    64,    68,    64,
     184,    64,    31,    67,    65,    64,    64,    61,    68,   171,
     212,   173,    69,    61,    67,   177,    67,   211,   186,   180,
      72,   187,   100,   104,    -1,    -1,   210,    -1,   102,   212,
     103,   215,    -1,   217,    -1,    -1,   105,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   207,    -1,    -1,    -1,    -1,
      -1,    -1,   214,     1,    -1,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,   230,   231,
      18,    -1,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    -1,    30,    -1,    32,    33,    34,    35,    36,    37,
      38,    39,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    52,    -1,    -1,    55,    56,    -1,
      -1,    59,    -1,    -1,    -1,    -1,    64,    -1,    66,    -1,
      68,    69,     1,    -1,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    -1,    -1,    18,
      -1,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      -1,    30,    -1,    32,    33,    34,    35,    36,    37,    38,
      39,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    52,    -1,    -1,    55,    56,    -1,    -1,
      59,    -1,    -1,    -1,    -1,    64,    -1,    66,    -1,    68,
      69,     0,     1,    -1,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    -1,    -1,    18,
      -1,    20,    -1,    -1,    23,    24,    25,    26,    27,    28,
      29,    30,    -1,    32,    33,    34,    35,    36,    37,    38,
      39,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    52,    -1,    -1,    55,    56,    -1,    -1,
      59,    -1,    -1,    -1,    -1,    64,    -1,    66,     1,    68,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    -1,    -1,    18,    -1,    20,    -1,    -1,
      23,    24,    25,    26,    27,    28,    -1,    30,    -1,    32,
      33,    34,    35,    36,    37,    38,    39,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    52,
      -1,    -1,    55,    56,    -1,    -1,    59,    -1,    -1,    -1,
      -1,    64,    -1,    66,    -1,    68,    69,     1,    -1,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    -1,    -1,    18,    -1,    20,    -1,    -1,    23,
      24,    25,    26,    27,    28,    -1,    30,    -1,    32,    33,
      34,    35,    36,    37,    38,    39,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    52,    -1,
      -1,    55,    56,    -1,    -1,    59,    -1,    -1,    -1,    -1,
      64,    -1,    66,    -1,    68
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    77,    78,     0,     1,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    18,    20,
      23,    24,    25,    26,    27,    28,    29,    30,    32,    33,
      34,    35,    36,    37,    38,    39,    52,    55,    56,    59,
      64,    66,    68,    79,    80,    84,    85,    89,    90,    94,
      95,    99,   101,   102,   106,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     124,    64,    46,    66,    66,    66,    66,    89,    66,    64,
      64,    35,   109,    84,    66,    66,   109,    66,    66,     7,
     122,   122,   122,   122,   122,   122,   109,    86,    91,    64,
      48,    60,    47,    50,    51,    49,    40,    41,    42,    43,
      44,    45,    53,    54,    55,    56,    57,    58,    38,    39,
      70,   110,   107,   108,   109,   109,   109,   109,    23,   100,
     109,    66,    64,     7,   109,   100,    64,   103,   104,   105,
     109,     7,    67,    67,    87,    88,    89,     7,    92,    93,
     113,   109,   114,   115,   116,   117,   118,   118,   119,   119,
     119,   119,   120,   120,   121,   121,   122,   122,   109,    67,
      65,    67,    67,    67,    66,    64,    66,    67,    64,    67,
      65,    67,    69,    89,    46,    64,    65,    61,    71,   109,
      89,    68,    89,   109,   100,    81,    82,    83,    84,    89,
     100,    64,   105,    64,   109,    93,   111,    19,    96,    67,
      64,    67,    65,     7,    31,    64,    89,    21,    22,    97,
      98,    64,   100,    85,    83,    89,   100,   109,    61,    69,
      67,    67,    61,    87,    89,    89,    87
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    76,    77,    78,    78,    79,    79,    80,    81,    81,
      82,    82,    83,    84,    84,    84,    84,    84,    84,    84,
      84,    86,    85,    87,    87,    88,    88,    89,    89,    89,
      89,    89,    89,    89,    89,    91,    90,    92,    92,    93,
      93,    94,    94,    95,    95,    95,    95,    95,    96,    96,
      97,    98,    98,    99,    99,    99,    99,   100,   100,   101,
     101,   101,   101,   102,   102,   103,   103,   104,   104,   105,
     106,   107,   107,   108,   108,   109,   110,   110,   111,   111,
     112,   112,   113,   113,   114,   114,   115,   115,   116,   116,
     117,   117,   117,   118,   118,   118,   118,   118,   119,   119,
     119,   120,   120,   120,   121,   121,   121,   122,   122,   122,
     122,   122,   122,   122,   123,   123,   123,   123,   124,   124,
     124,   124,   124,   124,   124,   124,   124,   124
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     0,     2,     1,     1,     7,     0,     1,
       1,     3,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     0,     1,     1,     2,     1,     1,     1,
       1,     1,     1,     1,     2,     0,     4,     1,     3,     1,
       3,     2,     1,     5,     7,     5,     7,     8,     0,     2,
       4,     0,     3,     9,     5,     7,     9,     0,     1,     3,
       3,     2,     2,     5,     5,     0,     1,     1,     3,     1,
       4,     0,     1,     1,     3,     1,     1,     3,     1,     5,
       1,     3,     1,     3,     1,     3,     1,     3,     1,     3,
       1,     3,     3,     1,     3,     3,     3,     3,     1,     3,
       3,     1,     3,     3,     1,     3,     3,     1,     2,     2,
       2,     2,     2,     2,     1,     2,     2,     4,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     3
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
  case 7: /* function_def: FUNCTION type_spec IDENTIFIER LPAREN parameter_list_opt RPAREN compound_stmt  */
#line 148 "parser.y"
      {
          free((yyvsp[-4].str_val));
      }
#line 1752 "parser.tab.c"
    break;

  case 12: /* parameter: type_spec IDENTIFIER  */
#line 165 "parser.y"
        {
            free((yyvsp[0].str_val));
        }
#line 1760 "parser.tab.c"
    break;

  case 13: /* type_spec: NUM  */
#line 171 "parser.y"
                 { (yyval.type_val) = TYPE_NUM; }
#line 1766 "parser.tab.c"
    break;

  case 14: /* type_spec: DEC  */
#line 172 "parser.y"
                 { (yyval.type_val) = TYPE_DEC; }
#line 1772 "parser.tab.c"
    break;

  case 15: /* type_spec: CHAR  */
#line 173 "parser.y"
                 { (yyval.type_val) = TYPE_CHAR; }
#line 1778 "parser.tab.c"
    break;

  case 16: /* type_spec: BOOL  */
#line 174 "parser.y"
                 { (yyval.type_val) = TYPE_BOOL; }
#line 1784 "parser.tab.c"
    break;

  case 17: /* type_spec: VOID  */
#line 175 "parser.y"
                 { (yyval.type_val) = TYPE_VOID; }
#line 1790 "parser.tab.c"
    break;

  case 18: /* type_spec: INT  */
#line 176 "parser.y"
                 { (yyval.type_val) = TYPE_NUM; }
#line 1796 "parser.tab.c"
    break;

  case 19: /* type_spec: FLOAT  */
#line 177 "parser.y"
                 { (yyval.type_val) = TYPE_DEC; }
#line 1802 "parser.tab.c"
    break;

  case 20: /* type_spec: DOUBLE  */
#line 178 "parser.y"
                 { (yyval.type_val) = TYPE_DEC; }
#line 1808 "parser.tab.c"
    break;

  case 21: /* $@1: %empty  */
#line 183 "parser.y"
      {
          enter_scope();
      }
#line 1816 "parser.tab.c"
    break;

  case 22: /* compound_stmt: LBRACE $@1 stmt_list_opt RBRACE  */
#line 187 "parser.y"
      {
          exit_scope();
      }
#line 1824 "parser.tab.c"
    break;

  case 34: /* statement: error SEMICOLON  */
#line 211 "parser.y"
        {
            fprintf(stderr, "Recovered from syntax error at line %d.\n", line_no);
            yyerrok;
        }
#line 1833 "parser.tab.c"
    break;

  case 35: /* $@2: %empty  */
#line 219 "parser.y"
      {
          current_decl_type = (NebulaType)(yyvsp[0].type_val);
      }
#line 1841 "parser.tab.c"
    break;

  case 39: /* init_declarator: IDENTIFIER  */
#line 232 "parser.y"
        {
            declare_variable((yyvsp[0].str_val), current_decl_type, line_no);
            free((yyvsp[0].str_val));
        }
#line 1850 "parser.tab.c"
    break;

  case 40: /* init_declarator: IDENTIFIER ASSIGN expression  */
#line 237 "parser.y"
        {
            declare_variable((yyvsp[-2].str_val), current_decl_type, line_no);
            if (!is_assignment_compatible(current_decl_type, (NebulaType)(yyvsp[0].type_val))) {
                semantic_error(line_no, "Type mismatch in declaration assignment (%s = %s)", type_name(current_decl_type), type_name((NebulaType)(yyvsp[0].type_val)));
            }
            free((yyvsp[-2].str_val));
        }
#line 1862 "parser.tab.c"
    break;

  case 43: /* selection_stmt: WHEN LPAREN expression RPAREN statement  */
#line 253 "parser.y"
            {
                    check_condition_type((NebulaType)(yyvsp[-2].type_val), line_no, "when");
            }
#line 1870 "parser.tab.c"
    break;

  case 44: /* selection_stmt: WHEN LPAREN expression RPAREN statement OTHERWISE statement  */
#line 257 "parser.y"
            {
                    check_condition_type((NebulaType)(yyvsp[-4].type_val), line_no, "when");
            }
#line 1878 "parser.tab.c"
    break;

  case 45: /* selection_stmt: IF LPAREN expression RPAREN statement  */
#line 261 "parser.y"
            {
                    check_condition_type((NebulaType)(yyvsp[-2].type_val), line_no, "if");
            }
#line 1886 "parser.tab.c"
    break;

  case 46: /* selection_stmt: IF LPAREN expression RPAREN statement ELSE statement  */
#line 265 "parser.y"
            {
                    check_condition_type((NebulaType)(yyvsp[-4].type_val), line_no, "if");
            }
#line 1894 "parser.tab.c"
    break;

  case 53: /* loop_stmt: LOOP LPAREN opt_expr SEMICOLON opt_expr SEMICOLON opt_expr RPAREN statement  */
#line 287 "parser.y"
            {
                    if ((NebulaType)(yyvsp[-4].type_val) != TYPE_UNKNOWN) {
                            check_condition_type((NebulaType)(yyvsp[-4].type_val), line_no, "loop");
                    }
            }
#line 1904 "parser.tab.c"
    break;

  case 54: /* loop_stmt: WHILE LPAREN expression RPAREN statement  */
#line 293 "parser.y"
            {
                    check_condition_type((NebulaType)(yyvsp[-2].type_val), line_no, "while");
            }
#line 1912 "parser.tab.c"
    break;

  case 55: /* loop_stmt: DO statement WHILE LPAREN expression RPAREN SEMICOLON  */
#line 297 "parser.y"
      {
          check_condition_type((NebulaType)(yyvsp[-2].type_val), line_no, "do-while");
      }
#line 1920 "parser.tab.c"
    break;

  case 56: /* loop_stmt: FOR LPAREN opt_expr SEMICOLON opt_expr SEMICOLON opt_expr RPAREN statement  */
#line 301 "parser.y"
            {
                    if ((NebulaType)(yyvsp[-4].type_val) != TYPE_UNKNOWN) {
                            check_condition_type((NebulaType)(yyvsp[-4].type_val), line_no, "for");
                    }
            }
#line 1930 "parser.tab.c"
    break;

  case 57: /* opt_expr: %empty  */
#line 309 "parser.y"
                      { (yyval.type_val) = TYPE_UNKNOWN; }
#line 1936 "parser.tab.c"
    break;

  case 58: /* opt_expr: expression  */
#line 310 "parser.y"
                      { (yyval.type_val) = (yyvsp[0].type_val); }
#line 1942 "parser.tab.c"
    break;

  case 64: /* io_stmt: INPUT LPAREN IDENTIFIER RPAREN SEMICOLON  */
#line 323 "parser.y"
        {
            (void)resolve_identifier_type((yyvsp[-2].str_val), line_no);
            free((yyvsp[-2].str_val));
        }
#line 1951 "parser.tab.c"
    break;

  case 70: /* function_call: IDENTIFIER LPAREN argument_list_opt RPAREN  */
#line 345 "parser.y"
        {
            /* Function symbols will be handled in later phases; keep type unknown for now. */
            free((yyvsp[-3].str_val));
        }
#line 1960 "parser.tab.c"
    break;

  case 75: /* expression: assignment_expr  */
#line 363 "parser.y"
        { (yyval.type_val) = (yyvsp[0].type_val); }
#line 1966 "parser.tab.c"
    break;

  case 76: /* assignment_expr: conditional_expr  */
#line 368 "parser.y"
        { (yyval.type_val) = (yyvsp[0].type_val); }
#line 1972 "parser.tab.c"
    break;

  case 77: /* assignment_expr: IDENTIFIER ASSIGN assignment_expr  */
#line 370 "parser.y"
        {
            NebulaType lhs = resolve_identifier_type((yyvsp[-2].str_val), line_no);
            NebulaType rhs = (NebulaType)(yyvsp[0].type_val);
            if (lhs != TYPE_UNKNOWN && rhs != TYPE_UNKNOWN && !is_assignment_compatible(lhs, rhs)) {
                semantic_error(line_no, "Type mismatch in assignment (%s = %s)", type_name(lhs), type_name(rhs));
            }
            (yyval.type_val) = lhs;
            free((yyvsp[-2].str_val));
        }
#line 1986 "parser.tab.c"
    break;

  case 78: /* conditional_expr: logical_or_expr  */
#line 383 "parser.y"
        { (yyval.type_val) = (yyvsp[0].type_val); }
#line 1992 "parser.tab.c"
    break;

  case 79: /* conditional_expr: logical_or_expr QMARK expression COLON conditional_expr  */
#line 385 "parser.y"
        {
            check_condition_type((NebulaType)(yyvsp[-4].type_val), line_no, "?:");
            if (is_assignment_compatible((NebulaType)(yyvsp[-2].type_val), (NebulaType)(yyvsp[0].type_val))) {
                (yyval.type_val) = (yyvsp[-2].type_val);
            } else if (is_assignment_compatible((NebulaType)(yyvsp[0].type_val), (NebulaType)(yyvsp[-2].type_val))) {
                (yyval.type_val) = (yyvsp[0].type_val);
            } else {
                semantic_error(line_no, "Type mismatch in conditional expression (%s : %s)", type_name((NebulaType)(yyvsp[-2].type_val)), type_name((NebulaType)(yyvsp[0].type_val)));
                (yyval.type_val) = TYPE_UNKNOWN;
            }
        }
#line 2008 "parser.tab.c"
    break;

  case 80: /* logical_or_expr: logical_and_expr  */
#line 400 "parser.y"
        { (yyval.type_val) = (yyvsp[0].type_val); }
#line 2014 "parser.tab.c"
    break;

  case 81: /* logical_or_expr: logical_or_expr OR logical_and_expr  */
#line 402 "parser.y"
        { (yyval.type_val) = logical_result_type((NebulaType)(yyvsp[-2].type_val), (NebulaType)(yyvsp[0].type_val), "||", line_no); }
#line 2020 "parser.tab.c"
    break;

  case 82: /* logical_and_expr: bitwise_or_expr  */
#line 407 "parser.y"
        { (yyval.type_val) = (yyvsp[0].type_val); }
#line 2026 "parser.tab.c"
    break;

  case 83: /* logical_and_expr: logical_and_expr AND bitwise_or_expr  */
#line 409 "parser.y"
        { (yyval.type_val) = logical_result_type((NebulaType)(yyvsp[-2].type_val), (NebulaType)(yyvsp[0].type_val), "&&", line_no); }
#line 2032 "parser.tab.c"
    break;

  case 84: /* bitwise_or_expr: bitwise_xor_expr  */
#line 414 "parser.y"
        { (yyval.type_val) = (yyvsp[0].type_val); }
#line 2038 "parser.tab.c"
    break;

  case 85: /* bitwise_or_expr: bitwise_or_expr BIT_OR bitwise_xor_expr  */
#line 416 "parser.y"
        { (yyval.type_val) = bitwise_result_type((NebulaType)(yyvsp[-2].type_val), (NebulaType)(yyvsp[0].type_val), "|", line_no); }
#line 2044 "parser.tab.c"
    break;

  case 86: /* bitwise_xor_expr: bitwise_and_expr  */
#line 421 "parser.y"
        { (yyval.type_val) = (yyvsp[0].type_val); }
#line 2050 "parser.tab.c"
    break;

  case 87: /* bitwise_xor_expr: bitwise_xor_expr BIT_XOR bitwise_and_expr  */
#line 423 "parser.y"
        { (yyval.type_val) = bitwise_result_type((NebulaType)(yyvsp[-2].type_val), (NebulaType)(yyvsp[0].type_val), "^", line_no); }
#line 2056 "parser.tab.c"
    break;

  case 88: /* bitwise_and_expr: equality_expr  */
#line 428 "parser.y"
        { (yyval.type_val) = (yyvsp[0].type_val); }
#line 2062 "parser.tab.c"
    break;

  case 89: /* bitwise_and_expr: bitwise_and_expr BIT_AND equality_expr  */
#line 430 "parser.y"
        { (yyval.type_val) = bitwise_result_type((NebulaType)(yyvsp[-2].type_val), (NebulaType)(yyvsp[0].type_val), "&", line_no); }
#line 2068 "parser.tab.c"
    break;

  case 90: /* equality_expr: relational_expr  */
#line 435 "parser.y"
        { (yyval.type_val) = (yyvsp[0].type_val); }
#line 2074 "parser.tab.c"
    break;

  case 91: /* equality_expr: equality_expr EQ relational_expr  */
#line 437 "parser.y"
        { (yyval.type_val) = equality_result_type((NebulaType)(yyvsp[-2].type_val), (NebulaType)(yyvsp[0].type_val), "==", line_no); }
#line 2080 "parser.tab.c"
    break;

  case 92: /* equality_expr: equality_expr NEQ relational_expr  */
#line 439 "parser.y"
        { (yyval.type_val) = equality_result_type((NebulaType)(yyvsp[-2].type_val), (NebulaType)(yyvsp[0].type_val), "!=", line_no); }
#line 2086 "parser.tab.c"
    break;

  case 93: /* relational_expr: shift_expr  */
#line 444 "parser.y"
        { (yyval.type_val) = (yyvsp[0].type_val); }
#line 2092 "parser.tab.c"
    break;

  case 94: /* relational_expr: relational_expr LT shift_expr  */
#line 446 "parser.y"
        { (yyval.type_val) = relational_result_type((NebulaType)(yyvsp[-2].type_val), (NebulaType)(yyvsp[0].type_val), "<", line_no); }
#line 2098 "parser.tab.c"
    break;

  case 95: /* relational_expr: relational_expr GT shift_expr  */
#line 448 "parser.y"
        { (yyval.type_val) = relational_result_type((NebulaType)(yyvsp[-2].type_val), (NebulaType)(yyvsp[0].type_val), ">", line_no); }
#line 2104 "parser.tab.c"
    break;

  case 96: /* relational_expr: relational_expr LE shift_expr  */
#line 450 "parser.y"
        { (yyval.type_val) = relational_result_type((NebulaType)(yyvsp[-2].type_val), (NebulaType)(yyvsp[0].type_val), "<=", line_no); }
#line 2110 "parser.tab.c"
    break;

  case 97: /* relational_expr: relational_expr GE shift_expr  */
#line 452 "parser.y"
        { (yyval.type_val) = relational_result_type((NebulaType)(yyvsp[-2].type_val), (NebulaType)(yyvsp[0].type_val), ">=", line_no); }
#line 2116 "parser.tab.c"
    break;

  case 98: /* shift_expr: additive_expr  */
#line 457 "parser.y"
        { (yyval.type_val) = (yyvsp[0].type_val); }
#line 2122 "parser.tab.c"
    break;

  case 99: /* shift_expr: shift_expr LSHIFT additive_expr  */
#line 459 "parser.y"
        { (yyval.type_val) = bitwise_result_type((NebulaType)(yyvsp[-2].type_val), (NebulaType)(yyvsp[0].type_val), "<<", line_no); }
#line 2128 "parser.tab.c"
    break;

  case 100: /* shift_expr: shift_expr RSHIFT additive_expr  */
#line 461 "parser.y"
        { (yyval.type_val) = bitwise_result_type((NebulaType)(yyvsp[-2].type_val), (NebulaType)(yyvsp[0].type_val), ">>", line_no); }
#line 2134 "parser.tab.c"
    break;

  case 101: /* additive_expr: multiplicative_expr  */
#line 466 "parser.y"
        { (yyval.type_val) = (yyvsp[0].type_val); }
#line 2140 "parser.tab.c"
    break;

  case 102: /* additive_expr: additive_expr PLUS multiplicative_expr  */
#line 468 "parser.y"
        { (yyval.type_val) = arithmetic_result_type((NebulaType)(yyvsp[-2].type_val), (NebulaType)(yyvsp[0].type_val), "+", line_no); }
#line 2146 "parser.tab.c"
    break;

  case 103: /* additive_expr: additive_expr MINUS multiplicative_expr  */
#line 470 "parser.y"
        { (yyval.type_val) = arithmetic_result_type((NebulaType)(yyvsp[-2].type_val), (NebulaType)(yyvsp[0].type_val), "-", line_no); }
#line 2152 "parser.tab.c"
    break;

  case 104: /* multiplicative_expr: unary_expr  */
#line 475 "parser.y"
        { (yyval.type_val) = (yyvsp[0].type_val); }
#line 2158 "parser.tab.c"
    break;

  case 105: /* multiplicative_expr: multiplicative_expr MUL unary_expr  */
#line 477 "parser.y"
        { (yyval.type_val) = arithmetic_result_type((NebulaType)(yyvsp[-2].type_val), (NebulaType)(yyvsp[0].type_val), "*", line_no); }
#line 2164 "parser.tab.c"
    break;

  case 106: /* multiplicative_expr: multiplicative_expr DIV unary_expr  */
#line 479 "parser.y"
        { (yyval.type_val) = arithmetic_result_type((NebulaType)(yyvsp[-2].type_val), (NebulaType)(yyvsp[0].type_val), "/", line_no); }
#line 2170 "parser.tab.c"
    break;

  case 107: /* unary_expr: postfix_expr  */
#line 484 "parser.y"
        { (yyval.type_val) = (yyvsp[0].type_val); }
#line 2176 "parser.tab.c"
    break;

  case 108: /* unary_expr: PLUS unary_expr  */
#line 486 "parser.y"
        { (yyval.type_val) = unary_plus_minus_type((NebulaType)(yyvsp[0].type_val), "+", line_no); }
#line 2182 "parser.tab.c"
    break;

  case 109: /* unary_expr: MINUS unary_expr  */
#line 488 "parser.y"
        { (yyval.type_val) = unary_plus_minus_type((NebulaType)(yyvsp[0].type_val), "-", line_no); }
#line 2188 "parser.tab.c"
    break;

  case 110: /* unary_expr: NOT unary_expr  */
#line 490 "parser.y"
        { (yyval.type_val) = unary_not_type((NebulaType)(yyvsp[0].type_val), line_no); }
#line 2194 "parser.tab.c"
    break;

  case 111: /* unary_expr: BIT_NOT unary_expr  */
#line 492 "parser.y"
        { (yyval.type_val) = unary_bitnot_type((NebulaType)(yyvsp[0].type_val), line_no); }
#line 2200 "parser.tab.c"
    break;

  case 112: /* unary_expr: INC unary_expr  */
#line 494 "parser.y"
        { (yyval.type_val) = incdec_type((NebulaType)(yyvsp[0].type_val), "++", line_no); }
#line 2206 "parser.tab.c"
    break;

  case 113: /* unary_expr: DECREMENT unary_expr  */
#line 496 "parser.y"
        { (yyval.type_val) = incdec_type((NebulaType)(yyvsp[0].type_val), "--", line_no); }
#line 2212 "parser.tab.c"
    break;

  case 114: /* postfix_expr: primary_expr  */
#line 501 "parser.y"
        { (yyval.type_val) = (yyvsp[0].type_val); }
#line 2218 "parser.tab.c"
    break;

  case 115: /* postfix_expr: postfix_expr INC  */
#line 503 "parser.y"
        { (yyval.type_val) = incdec_type((NebulaType)(yyvsp[-1].type_val), "++", line_no); }
#line 2224 "parser.tab.c"
    break;

  case 116: /* postfix_expr: postfix_expr DECREMENT  */
#line 505 "parser.y"
        { (yyval.type_val) = incdec_type((NebulaType)(yyvsp[-1].type_val), "--", line_no); }
#line 2230 "parser.tab.c"
    break;

  case 117: /* postfix_expr: postfix_expr LBRACKET expression RBRACKET  */
#line 507 "parser.y"
        {
            if ((NebulaType)(yyvsp[-1].type_val) != TYPE_NUM) {
                semantic_error(line_no, "Array index must be num, found %s", type_name((NebulaType)(yyvsp[-1].type_val)));
            }
            (yyval.type_val) = (yyvsp[-3].type_val);
        }
#line 2241 "parser.tab.c"
    break;

  case 118: /* primary_expr: IDENTIFIER  */
#line 517 "parser.y"
        {
            (yyval.type_val) = resolve_identifier_type((yyvsp[0].str_val), line_no);
            free((yyvsp[0].str_val));
        }
#line 2250 "parser.tab.c"
    break;

  case 119: /* primary_expr: NUM_LITERAL  */
#line 522 "parser.y"
        { (yyval.type_val) = TYPE_NUM; }
#line 2256 "parser.tab.c"
    break;

  case 120: /* primary_expr: DEC_LITERAL  */
#line 524 "parser.y"
        { (yyval.type_val) = TYPE_DEC; }
#line 2262 "parser.tab.c"
    break;

  case 121: /* primary_expr: CHAR_LITERAL  */
#line 526 "parser.y"
        { (yyval.type_val) = TYPE_CHAR; }
#line 2268 "parser.tab.c"
    break;

  case 122: /* primary_expr: STRING_LITERAL  */
#line 528 "parser.y"
        {
            (yyval.type_val) = TYPE_UNKNOWN;
            free((yyvsp[0].str_val));
        }
#line 2277 "parser.tab.c"
    break;

  case 123: /* primary_expr: TRUE  */
#line 533 "parser.y"
        { (yyval.type_val) = TYPE_BOOL; }
#line 2283 "parser.tab.c"
    break;

  case 124: /* primary_expr: FALSE  */
#line 535 "parser.y"
        { (yyval.type_val) = TYPE_BOOL; }
#line 2289 "parser.tab.c"
    break;

  case 125: /* primary_expr: function_call  */
#line 537 "parser.y"
        { (yyval.type_val) = TYPE_UNKNOWN; }
#line 2295 "parser.tab.c"
    break;

  case 126: /* primary_expr: INPUT LPAREN RPAREN  */
#line 539 "parser.y"
        { (yyval.type_val) = TYPE_UNKNOWN; }
#line 2301 "parser.tab.c"
    break;

  case 127: /* primary_expr: LPAREN expression RPAREN  */
#line 541 "parser.y"
        { (yyval.type_val) = (yyvsp[-1].type_val); }
#line 2307 "parser.tab.c"
    break;


#line 2311 "parser.tab.c"

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

#line 544 "parser.y"


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
