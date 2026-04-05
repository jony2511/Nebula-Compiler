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

#line 92 "parser.tab.c"

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
  YYSYMBOL_PRINT_INLINE = 35,              /* PRINT_INLINE  */
  YYSYMBOL_INPUT = 36,                     /* INPUT  */
  YYSYMBOL_NEBULA = 37,                    /* NEBULA  */
  YYSYMBOL_TRUE = 38,                      /* TRUE  */
  YYSYMBOL_FALSE = 39,                     /* FALSE  */
  YYSYMBOL_INC = 40,                       /* INC  */
  YYSYMBOL_DECREMENT = 41,                 /* DECREMENT  */
  YYSYMBOL_EQ = 42,                        /* EQ  */
  YYSYMBOL_NEQ = 43,                       /* NEQ  */
  YYSYMBOL_LE = 44,                        /* LE  */
  YYSYMBOL_GE = 45,                        /* GE  */
  YYSYMBOL_LT = 46,                        /* LT  */
  YYSYMBOL_GT = 47,                        /* GT  */
  YYSYMBOL_ASSIGN = 48,                    /* ASSIGN  */
  YYSYMBOL_AND = 49,                       /* AND  */
  YYSYMBOL_OR = 50,                        /* OR  */
  YYSYMBOL_BIT_AND = 51,                   /* BIT_AND  */
  YYSYMBOL_BIT_OR = 52,                    /* BIT_OR  */
  YYSYMBOL_BIT_XOR = 53,                   /* BIT_XOR  */
  YYSYMBOL_BIT_NOT = 54,                   /* BIT_NOT  */
  YYSYMBOL_LSHIFT = 55,                    /* LSHIFT  */
  YYSYMBOL_RSHIFT = 56,                    /* RSHIFT  */
  YYSYMBOL_PLUS = 57,                      /* PLUS  */
  YYSYMBOL_MINUS = 58,                     /* MINUS  */
  YYSYMBOL_MUL = 59,                       /* MUL  */
  YYSYMBOL_DIV = 60,                       /* DIV  */
  YYSYMBOL_NOT = 61,                       /* NOT  */
  YYSYMBOL_QMARK = 62,                     /* QMARK  */
  YYSYMBOL_COLON = 63,                     /* COLON  */
  YYSYMBOL_ARROW_R = 64,                   /* ARROW_R  */
  YYSYMBOL_ARROW_L = 65,                   /* ARROW_L  */
  YYSYMBOL_SEMICOLON = 66,                 /* SEMICOLON  */
  YYSYMBOL_COMMA = 67,                     /* COMMA  */
  YYSYMBOL_LPAREN = 68,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 69,                    /* RPAREN  */
  YYSYMBOL_LBRACE = 70,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 71,                    /* RBRACE  */
  YYSYMBOL_LBRACKET = 72,                  /* LBRACKET  */
  YYSYMBOL_RBRACKET = 73,                  /* RBRACKET  */
  YYSYMBOL_INVALID = 74,                   /* INVALID  */
  YYSYMBOL_LOWER_THAN_OTHERWISE = 75,      /* LOWER_THAN_OTHERWISE  */
  YYSYMBOL_UMINUS = 76,                    /* UMINUS  */
  YYSYMBOL_UPLUS = 77,                     /* UPLUS  */
  YYSYMBOL_YYACCEPT = 78,                  /* $accept  */
  YYSYMBOL_program = 79,                   /* program  */
  YYSYMBOL_translation_unit = 80,          /* translation_unit  */
  YYSYMBOL_external_decl = 81,             /* external_decl  */
  YYSYMBOL_function_def = 82,              /* function_def  */
  YYSYMBOL_83_1 = 83,                      /* $@1  */
  YYSYMBOL_parameter_list_opt = 84,        /* parameter_list_opt  */
  YYSYMBOL_parameter_list = 85,            /* parameter_list  */
  YYSYMBOL_parameter = 86,                 /* parameter  */
  YYSYMBOL_type_spec = 87,                 /* type_spec  */
  YYSYMBOL_compound_stmt = 88,             /* compound_stmt  */
  YYSYMBOL_89_2 = 89,                      /* $@2  */
  YYSYMBOL_stmt_list_opt = 90,             /* stmt_list_opt  */
  YYSYMBOL_stmt_list = 91,                 /* stmt_list  */
  YYSYMBOL_statement = 92,                 /* statement  */
  YYSYMBOL_declaration_stmt = 93,          /* declaration_stmt  */
  YYSYMBOL_94_3 = 94,                      /* $@3  */
  YYSYMBOL_init_declarator_list = 95,      /* init_declarator_list  */
  YYSYMBOL_init_declarator = 96,           /* init_declarator  */
  YYSYMBOL_expression_stmt = 97,           /* expression_stmt  */
  YYSYMBOL_selection_stmt = 98,            /* selection_stmt  */
  YYSYMBOL_case_clauses_opt = 99,          /* case_clauses_opt  */
  YYSYMBOL_case_clause = 100,              /* case_clause  */
  YYSYMBOL_default_clause_opt = 101,       /* default_clause_opt  */
  YYSYMBOL_loop_stmt = 102,                /* loop_stmt  */
  YYSYMBOL_opt_expr = 103,                 /* opt_expr  */
  YYSYMBOL_jump_stmt = 104,                /* jump_stmt  */
  YYSYMBOL_io_stmt = 105,                  /* io_stmt  */
  YYSYMBOL_print_arg_list_opt = 106,       /* print_arg_list_opt  */
  YYSYMBOL_print_arg_list = 107,           /* print_arg_list  */
  YYSYMBOL_print_arg = 108,                /* print_arg  */
  YYSYMBOL_function_call = 109,            /* function_call  */
  YYSYMBOL_argument_list_opt = 110,        /* argument_list_opt  */
  YYSYMBOL_argument_list = 111,            /* argument_list  */
  YYSYMBOL_expression = 112,               /* expression  */
  YYSYMBOL_assignment_expr = 113,          /* assignment_expr  */
  YYSYMBOL_conditional_expr = 114,         /* conditional_expr  */
  YYSYMBOL_logical_or_expr = 115,          /* logical_or_expr  */
  YYSYMBOL_logical_and_expr = 116,         /* logical_and_expr  */
  YYSYMBOL_bitwise_or_expr = 117,          /* bitwise_or_expr  */
  YYSYMBOL_bitwise_xor_expr = 118,         /* bitwise_xor_expr  */
  YYSYMBOL_bitwise_and_expr = 119,         /* bitwise_and_expr  */
  YYSYMBOL_equality_expr = 120,            /* equality_expr  */
  YYSYMBOL_relational_expr = 121,          /* relational_expr  */
  YYSYMBOL_shift_expr = 122,               /* shift_expr  */
  YYSYMBOL_additive_expr = 123,            /* additive_expr  */
  YYSYMBOL_multiplicative_expr = 124,      /* multiplicative_expr  */
  YYSYMBOL_unary_expr = 125,               /* unary_expr  */
  YYSYMBOL_postfix_expr = 126,             /* postfix_expr  */
  YYSYMBOL_primary_expr = 127              /* primary_expr  */
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
#define YYLAST   577

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  78
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  50
/* YYNRULES -- Number of rules.  */
#define YYNRULES  131
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  252

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   332


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
      75,    76,    77
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   105,   105,   115,   118,   125,   129,   137,   136,   154,
     157,   164,   168,   175,   186,   187,   188,   189,   190,   191,
     192,   193,   198,   197,   212,   215,   222,   226,   233,   237,
     241,   245,   249,   253,   257,   261,   271,   270,   281,   285,
     292,   300,   315,   321,   328,   336,   345,   353,   362,   374,
     377,   384,   395,   398,   407,   415,   427,   435,   443,   459,
     462,   469,   475,   481,   485,   492,   498,   504,   515,   518,
     525,   529,   536,   543,   554,   557,   564,   568,   575,   582,
     586,   604,   608,   630,   634,   642,   646,   654,   658,   666,
     670,   678,   682,   690,   694,   699,   707,   711,   716,   721,
     726,   734,   738,   743,   751,   755,   760,   768,   772,   777,
     785,   789,   794,   799,   804,   809,   814,   822,   826,   831,
     836,   847,   855,   861,   867,   873,   878,   882,   886,   890,
     894,   903
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
  "GIVE", "PRINT", "PRINT_INLINE", "INPUT", "NEBULA", "TRUE", "FALSE",
  "INC", "DECREMENT", "EQ", "NEQ", "LE", "GE", "LT", "GT", "ASSIGN", "AND",
  "OR", "BIT_AND", "BIT_OR", "BIT_XOR", "BIT_NOT", "LSHIFT", "RSHIFT",
  "PLUS", "MINUS", "MUL", "DIV", "NOT", "QMARK", "COLON", "ARROW_R",
  "ARROW_L", "SEMICOLON", "COMMA", "LPAREN", "RPAREN", "LBRACE", "RBRACE",
  "LBRACKET", "RBRACKET", "INVALID", "LOWER_THAN_OTHERWISE", "UMINUS",
  "UPLUS", "$accept", "program", "translation_unit", "external_decl",
  "function_def", "$@1", "parameter_list_opt", "parameter_list",
  "parameter", "type_spec", "compound_stmt", "$@2", "stmt_list_opt",
  "stmt_list", "statement", "declaration_stmt", "$@3",
  "init_declarator_list", "init_declarator", "expression_stmt",
  "selection_stmt", "case_clauses_opt", "case_clause",
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

#define YYPACT_NINF (-226)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-26)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -226,    21,   368,  -226,   -40,  -226,  -226,  -226,  -226,   -43,
    -226,  -226,  -226,  -226,  -226,  -226,  -226,  -226,   -36,   -12,
      -6,   507,    13,   -22,    17,    32,   105,    16,    19,    32,
      20,    26,    27,    28,  -226,  -226,    71,    71,    71,    71,
      71,    71,  -226,    32,  -226,  -226,  -226,  -226,  -226,  -226,
    -226,  -226,  -226,  -226,  -226,  -226,  -226,    31,  -226,  -226,
     -35,    36,    46,    50,    53,   -19,   -16,   -38,   -24,   -13,
    -226,   -27,  -226,  -226,    32,    32,    32,    32,    32,    82,
      32,  -226,  -226,    38,    55,   115,    32,    32,    57,    32,
      32,    -4,   117,    58,  -226,  -226,  -226,  -226,  -226,  -226,
      61,   436,   120,  -226,    71,    32,    71,    71,    71,    71,
      71,    71,    71,    71,    71,    71,    71,    71,    71,    71,
      71,    71,  -226,  -226,    32,  -226,    62,    66,  -226,    65,
      67,    69,    72,    75,  -226,    73,  -226,    76,    77,    79,
      78,  -226,    80,    68,  -226,  -226,    83,    84,  -226,    81,
    -226,    85,   225,  -226,   103,   -18,  -226,    36,    92,    46,
      50,    53,   -19,   -16,   -16,   -38,   -38,   -38,   -38,   -24,
     -24,   -13,   -13,  -226,  -226,    87,  -226,    32,   507,    91,
     507,    32,    32,  -226,   507,    32,   507,    97,    32,    98,
     100,    32,  -226,  -226,    32,  -226,   120,    71,  -226,  -226,
     138,  -226,  -226,   101,   106,   105,   136,   107,  -226,  -226,
    -226,  -226,  -226,   108,  -226,  -226,  -226,   507,    29,   109,
      32,   110,   102,  -226,   167,   507,    32,  -226,  -226,    32,
     118,  -226,   112,  -226,   116,   119,   105,  -226,  -226,   121,
     123,   436,  -226,   507,  -226,  -226,   507,   296,  -226,  -226,
    -226,  -226
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     0,     1,     0,   122,   123,   124,   125,   121,
      19,    20,    21,    14,    15,    16,    17,    18,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   126,   127,     0,     0,     0,     0,
       0,     0,    43,     0,    22,     4,     5,    36,    34,     6,
      28,    29,    30,    31,    32,    33,   128,     0,    78,    79,
      81,    83,    85,    87,    89,    91,    93,    96,   101,   104,
     107,   110,   117,    35,     0,    74,     0,     0,     0,     0,
      59,    63,    64,     0,     0,     0,     0,    59,     0,    68,
      68,     0,     0,   121,   115,   116,   114,   111,   112,   113,
       0,     0,     0,    42,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   118,   119,     0,    80,     0,    75,    76,     0,
       0,     0,     0,     0,    60,     0,    62,     0,     0,     0,
      60,    61,     0,    69,    70,    72,     0,     0,   129,     0,
     131,     0,     0,    26,    40,     0,    38,    84,     0,    86,
      88,    90,    92,    94,    95,    99,   100,    97,    98,   102,
     103,   105,   106,   108,   109,     0,    73,     0,     0,     0,
       0,     0,    59,     7,     0,    59,     0,     0,     0,     0,
       0,     0,    23,    27,     0,    37,     0,     0,   120,    77,
      46,    49,    56,     0,     0,     9,    44,     0,    54,    65,
      71,    66,    67,     0,    41,    39,    82,     0,    52,     0,
      59,     0,    10,    11,     0,     0,    59,   130,    47,     0,
       0,    50,     0,    57,     0,     0,     0,    13,    45,     0,
       0,     0,    48,     0,     8,    12,     0,     0,    53,    58,
      55,    51
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -226,  -226,  -226,  -226,  -226,  -226,  -226,  -226,   -49,   -25,
     -47,  -226,  -225,  -226,    -2,  -226,  -226,  -226,    -5,  -226,
    -226,  -226,  -226,  -226,  -226,   -83,  -226,  -226,   104,  -226,
       4,  -226,  -226,  -226,   -23,   122,     1,  -226,    89,    93,
      88,    94,    95,   -52,   -72,   -56,   -39,   -29,  -226,  -226
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     1,     2,    45,    46,   205,   221,   222,   223,    47,
      48,   101,   151,   152,   153,    50,   102,   155,   156,    51,
      52,   218,   231,   232,    53,   133,    54,    55,   142,   143,
     144,    56,   126,   127,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      49,    85,    84,   147,   139,    74,    88,    94,    95,    96,
      97,    98,    99,   122,   123,   104,   248,   116,   117,    79,
     100,     3,   251,   110,   111,    75,    73,   105,   112,   113,
     114,   115,    76,   118,   119,     5,     6,     7,     8,     9,
     165,   166,   167,   168,    81,   124,   120,   121,   195,   196,
     229,   230,   128,   129,   130,   131,    77,   134,   163,   164,
     169,   170,    78,   138,   140,   148,   145,   145,    83,    33,
      34,    35,    36,    37,     5,     6,     7,     8,    93,   171,
     172,    80,   158,    82,    86,   106,    38,    87,    89,    39,
      40,   173,   174,    41,    90,    91,    92,   103,   107,   204,
      43,   175,   207,   108,   109,   132,   135,    83,    33,    34,
      35,    36,    37,    10,    11,    12,    13,    14,    15,    16,
      17,   136,   137,   141,   149,    38,    75,   154,    39,    40,
     150,   176,    41,   177,   178,   188,   179,   234,   180,    43,
     181,   182,   148,   239,   183,   185,   184,   186,   191,   187,
     193,   194,   189,   190,   199,   197,   192,   217,   203,   134,
     198,   201,   134,   209,   211,   145,   212,   225,   213,   236,
     219,   214,   220,   226,   237,   233,   200,   227,   202,   235,
     224,   241,   206,   242,   208,   243,   247,   245,   244,    44,
     246,   215,   210,   157,   146,   160,   125,   134,   216,   159,
       0,     0,   161,   134,   162,     0,   240,     0,     0,     0,
       0,   224,     0,     0,     0,   228,     0,     0,     0,     0,
       0,     0,     0,   238,     0,     0,     4,     0,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,   249,     0,    18,   250,    19,   -25,   -25,    20,    21,
      22,    23,    24,    25,     0,    27,     0,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    38,
       0,     0,    39,    40,     0,     0,    41,     0,     0,     0,
       0,    42,     0,    43,     0,    44,   -25,     4,     0,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,     0,     0,    18,     0,    19,   -24,   -24,    20,
      21,    22,    23,    24,    25,     0,    27,     0,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      38,     0,     0,    39,    40,     0,     0,    41,     0,     0,
       0,     0,    42,     0,    43,     0,    44,   -24,    -2,     4,
       0,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,     0,     0,    18,     0,    19,     0,
       0,    20,    21,    22,    23,    24,    25,    26,    27,     0,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    38,     0,     0,    39,    40,     0,     0,    41,
       0,     0,     0,     0,    42,     0,    43,     4,    44,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,     0,     0,    18,     0,    19,     0,     0,    20,
      21,    22,    23,    24,    25,     0,    27,     0,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      38,     0,     0,    39,    40,     0,     0,    41,     0,     0,
       0,     0,    42,     0,    43,     0,    44,   -24,     4,     0,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,     0,     0,    18,     0,    19,     0,     0,
      20,    21,    22,    23,    24,    25,     0,    27,     0,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    38,     0,     0,    39,    40,     0,     0,    41,     0,
       0,     0,     0,    42,     0,    43,     0,    44
};

static const yytype_int16 yycheck[] =
{
       2,    26,    25,     7,    87,    48,    29,    36,    37,    38,
      39,    40,    41,    40,    41,    50,   241,    55,    56,    21,
      43,     0,   247,    42,    43,    68,    66,    62,    44,    45,
      46,    47,    68,    57,    58,     3,     4,     5,     6,     7,
     112,   113,   114,   115,    66,    72,    59,    60,    66,    67,
      21,    22,    75,    76,    77,    78,    68,    80,   110,   111,
     116,   117,    68,    86,    87,    69,    89,    90,    36,    37,
      38,    39,    40,    41,     3,     4,     5,     6,     7,   118,
     119,    68,   105,    66,    68,    49,    54,    68,    68,    57,
      58,   120,   121,    61,    68,    68,    68,    66,    52,   182,
      68,   124,   185,    53,    51,    23,    68,    36,    37,    38,
      39,    40,    41,     8,     9,    10,    11,    12,    13,    14,
      15,    66,     7,    66,     7,    54,    68,     7,    57,    58,
      69,    69,    61,    67,    69,    67,    69,   220,    69,    68,
      68,    66,    69,   226,    68,    66,    69,    69,    67,    69,
     152,    48,    69,    69,   177,    63,    71,    19,   181,   182,
      73,    70,   185,    66,    66,   188,    66,    31,   191,    67,
      69,   194,    66,    66,     7,    66,   178,    69,   180,    69,
     205,    63,   184,    71,   186,    69,    63,   236,   235,    70,
      69,   196,   188,   104,    90,   107,    74,   220,   197,   106,
      -1,    -1,   108,   226,   109,    -1,   229,    -1,    -1,    -1,
      -1,   236,    -1,    -1,    -1,   217,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   225,    -1,    -1,     1,    -1,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,   243,    -1,    18,   246,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    -1,    30,    -1,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    54,
      -1,    -1,    57,    58,    -1,    -1,    61,    -1,    -1,    -1,
      -1,    66,    -1,    68,    -1,    70,    71,     1,    -1,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    -1,    -1,    18,    -1,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    -1,    30,    -1,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      54,    -1,    -1,    57,    58,    -1,    -1,    61,    -1,    -1,
      -1,    -1,    66,    -1,    68,    -1,    70,    71,     0,     1,
      -1,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    -1,    -1,    18,    -1,    20,    -1,
      -1,    23,    24,    25,    26,    27,    28,    29,    30,    -1,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    54,    -1,    -1,    57,    58,    -1,    -1,    61,
      -1,    -1,    -1,    -1,    66,    -1,    68,     1,    70,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    -1,    -1,    18,    -1,    20,    -1,    -1,    23,
      24,    25,    26,    27,    28,    -1,    30,    -1,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      54,    -1,    -1,    57,    58,    -1,    -1,    61,    -1,    -1,
      -1,    -1,    66,    -1,    68,    -1,    70,    71,     1,    -1,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    -1,    -1,    18,    -1,    20,    -1,    -1,
      23,    24,    25,    26,    27,    28,    -1,    30,    -1,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    54,    -1,    -1,    57,    58,    -1,    -1,    61,    -1,
      -1,    -1,    -1,    66,    -1,    68,    -1,    70
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    79,    80,     0,     1,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    18,    20,
      23,    24,    25,    26,    27,    28,    29,    30,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    54,    57,
      58,    61,    66,    68,    70,    81,    82,    87,    88,    92,
      93,    97,    98,   102,   104,   105,   109,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,    66,    48,    68,    68,    68,    68,    92,
      68,    66,    66,    36,   112,    87,    68,    68,   112,    68,
      68,    68,    68,     7,   125,   125,   125,   125,   125,   125,
     112,    89,    94,    66,    50,    62,    49,    52,    53,    51,
      42,    43,    44,    45,    46,    47,    55,    56,    57,    58,
      59,    60,    40,    41,    72,   113,   110,   111,   112,   112,
     112,   112,    23,   103,   112,    68,    66,     7,   112,   103,
     112,    66,   106,   107,   108,   112,   106,     7,    69,     7,
      69,    90,    91,    92,     7,    95,    96,   116,   112,   117,
     118,   119,   120,   121,   121,   122,   122,   122,   122,   123,
     123,   124,   124,   125,   125,   112,    69,    67,    69,    69,
      69,    68,    66,    68,    69,    66,    69,    69,    67,    69,
      69,    67,    71,    92,    48,    66,    67,    63,    73,   112,
      92,    70,    92,   112,   103,    83,    92,   103,    92,    66,
     108,    66,    66,   112,   112,    96,   114,    19,    99,    69,
      66,    84,    85,    86,    87,    31,    66,    69,    92,    21,
      22,   100,   101,    66,   103,    69,    67,     7,    92,   103,
     112,    63,    71,    69,    88,    86,    69,    63,    90,    92,
      92,    90
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    78,    79,    80,    80,    81,    81,    83,    82,    84,
      84,    85,    85,    86,    87,    87,    87,    87,    87,    87,
      87,    87,    89,    88,    90,    90,    91,    91,    92,    92,
      92,    92,    92,    92,    92,    92,    94,    93,    95,    95,
      96,    96,    97,    97,    98,    98,    98,    98,    98,    99,
      99,   100,   101,   101,   102,   102,   102,   102,   102,   103,
     103,   104,   104,   104,   104,   105,   105,   105,   106,   106,
     107,   107,   108,   109,   110,   110,   111,   111,   112,   113,
     113,   114,   114,   115,   115,   116,   116,   117,   117,   118,
     118,   119,   119,   120,   120,   120,   121,   121,   121,   121,
     121,   122,   122,   122,   123,   123,   123,   124,   124,   124,
     125,   125,   125,   125,   125,   125,   125,   126,   126,   126,
     126,   127,   127,   127,   127,   127,   127,   127,   127,   127,
     127,   127
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
       1,     3,     3,     2,     2,     5,     5,     5,     0,     1,
       1,     3,     1,     4,     0,     1,     1,     3,     1,     1,
       3,     1,     5,     1,     3,     1,     3,     1,     3,     1,
       3,     1,     3,     1,     3,     3,     1,     3,     3,     3,
       3,     1,     3,     3,     1,     3,     3,     1,     3,     3,
       1,     2,     2,     2,     2,     2,     2,     1,     2,     2,
       4,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       6,     3
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
#line 106 "parser.y"
      {
          ast_root = new_ast_node(AST_PROGRAM, "program");
          ast_root->left = (yyvsp[0].node);
          (yyval.node) = ast_root;
      }
#line 1732 "parser.tab.c"
    break;

  case 3: /* translation_unit: %empty  */
#line 115 "parser.y"
      {
          (yyval.node) = NULL;
      }
#line 1740 "parser.tab.c"
    break;

  case 4: /* translation_unit: translation_unit external_decl  */
#line 119 "parser.y"
      {
          (yyval.node) = append_node((yyvsp[-1].node), (yyvsp[0].node));
      }
#line 1748 "parser.tab.c"
    break;

  case 5: /* external_decl: function_def  */
#line 126 "parser.y"
      {
          (yyval.node) = (yyvsp[0].node);
      }
#line 1756 "parser.tab.c"
    break;

  case 6: /* external_decl: statement  */
#line 130 "parser.y"
      {
          (yyval.node) = (yyvsp[0].node);
      }
#line 1764 "parser.tab.c"
    break;

  case 7: /* $@1: %empty  */
#line 137 "parser.y"
      {
          enter_scope();
      }
#line 1772 "parser.tab.c"
    break;

  case 8: /* function_def: FUNCTION type_spec IDENTIFIER LPAREN $@1 parameter_list_opt RPAREN compound_stmt  */
#line 141 "parser.y"
      {
          ASTNode *fn = new_ast_node(AST_FUNC_CALL, (yyvsp[-5].str_val));
          fn->inferred_type = (NebulaType)(yyvsp[-6].type_val);
          fn->left = (yyvsp[-2].node);
          fn->body = (yyvsp[0].node);
          (yyval.node) = fn;
          exit_scope();
          free((yyvsp[-5].str_val));
      }
#line 1786 "parser.tab.c"
    break;

  case 9: /* parameter_list_opt: %empty  */
#line 154 "parser.y"
      {
          (yyval.node) = NULL;
      }
#line 1794 "parser.tab.c"
    break;

  case 10: /* parameter_list_opt: parameter_list  */
#line 158 "parser.y"
      {
          (yyval.node) = (yyvsp[0].node);
      }
#line 1802 "parser.tab.c"
    break;

  case 11: /* parameter_list: parameter  */
#line 165 "parser.y"
      {
          (yyval.node) = (yyvsp[0].node);
      }
#line 1810 "parser.tab.c"
    break;

  case 12: /* parameter_list: parameter_list COMMA parameter  */
#line 169 "parser.y"
      {
          (yyval.node) = append_node((yyvsp[-2].node), (yyvsp[0].node));
      }
#line 1818 "parser.tab.c"
    break;

  case 13: /* parameter: type_spec IDENTIFIER  */
#line 176 "parser.y"
      {
          ASTNode *id = new_ast_node(AST_IDENTIFIER, (yyvsp[0].str_val));
          id->inferred_type = (NebulaType)(yyvsp[-1].type_val);
                    declare_variable((yyvsp[0].str_val), (NebulaType)(yyvsp[-1].type_val), line_no);
          (yyval.node) = id;
          free((yyvsp[0].str_val));
      }
#line 1830 "parser.tab.c"
    break;

  case 14: /* type_spec: NUM  */
#line 186 "parser.y"
                 { (yyval.type_val) = TYPE_NUM; }
#line 1836 "parser.tab.c"
    break;

  case 15: /* type_spec: DEC  */
#line 187 "parser.y"
                 { (yyval.type_val) = TYPE_DEC; }
#line 1842 "parser.tab.c"
    break;

  case 16: /* type_spec: CHAR  */
#line 188 "parser.y"
                 { (yyval.type_val) = TYPE_CHAR; }
#line 1848 "parser.tab.c"
    break;

  case 17: /* type_spec: BOOL  */
#line 189 "parser.y"
                 { (yyval.type_val) = TYPE_BOOL; }
#line 1854 "parser.tab.c"
    break;

  case 18: /* type_spec: VOID  */
#line 190 "parser.y"
                 { (yyval.type_val) = TYPE_VOID; }
#line 1860 "parser.tab.c"
    break;

  case 19: /* type_spec: INT  */
#line 191 "parser.y"
                 { (yyval.type_val) = TYPE_NUM; }
#line 1866 "parser.tab.c"
    break;

  case 20: /* type_spec: FLOAT  */
#line 192 "parser.y"
                 { (yyval.type_val) = TYPE_DEC; }
#line 1872 "parser.tab.c"
    break;

  case 21: /* type_spec: DOUBLE  */
#line 193 "parser.y"
                 { (yyval.type_val) = TYPE_DEC; }
#line 1878 "parser.tab.c"
    break;

  case 22: /* $@2: %empty  */
#line 198 "parser.y"
      {
          enter_scope();
      }
#line 1886 "parser.tab.c"
    break;

  case 23: /* compound_stmt: LBRACE $@2 stmt_list_opt RBRACE  */
#line 202 "parser.y"
      {
          ASTNode *list = new_ast_node(AST_STMT_LIST, "block");
          list->left = (yyvsp[-1].node);
          (yyval.node) = list;
          exit_scope();
      }
#line 1897 "parser.tab.c"
    break;

  case 24: /* stmt_list_opt: %empty  */
#line 212 "parser.y"
      {
          (yyval.node) = NULL;
      }
#line 1905 "parser.tab.c"
    break;

  case 25: /* stmt_list_opt: stmt_list  */
#line 216 "parser.y"
      {
          (yyval.node) = (yyvsp[0].node);
      }
#line 1913 "parser.tab.c"
    break;

  case 26: /* stmt_list: statement  */
#line 223 "parser.y"
      {
          (yyval.node) = (yyvsp[0].node);
      }
#line 1921 "parser.tab.c"
    break;

  case 27: /* stmt_list: stmt_list statement  */
#line 227 "parser.y"
      {
          (yyval.node) = append_node((yyvsp[-1].node), (yyvsp[0].node));
      }
#line 1929 "parser.tab.c"
    break;

  case 28: /* statement: declaration_stmt  */
#line 234 "parser.y"
      {
          (yyval.node) = (yyvsp[0].node);
      }
#line 1937 "parser.tab.c"
    break;

  case 29: /* statement: expression_stmt  */
#line 238 "parser.y"
      {
          (yyval.node) = (yyvsp[0].node);
      }
#line 1945 "parser.tab.c"
    break;

  case 30: /* statement: selection_stmt  */
#line 242 "parser.y"
      {
          (yyval.node) = (yyvsp[0].node);
      }
#line 1953 "parser.tab.c"
    break;

  case 31: /* statement: loop_stmt  */
#line 246 "parser.y"
      {
          (yyval.node) = (yyvsp[0].node);
      }
#line 1961 "parser.tab.c"
    break;

  case 32: /* statement: jump_stmt  */
#line 250 "parser.y"
      {
          (yyval.node) = (yyvsp[0].node);
      }
#line 1969 "parser.tab.c"
    break;

  case 33: /* statement: io_stmt  */
#line 254 "parser.y"
      {
          (yyval.node) = (yyvsp[0].node);
      }
#line 1977 "parser.tab.c"
    break;

  case 34: /* statement: compound_stmt  */
#line 258 "parser.y"
      {
          (yyval.node) = (yyvsp[0].node);
      }
#line 1985 "parser.tab.c"
    break;

  case 35: /* statement: error SEMICOLON  */
#line 262 "parser.y"
      {
          fprintf(stderr, "Recovered from syntax error at line %d.\n", line_no);
          yyerrok;
          (yyval.node) = NULL;
      }
#line 1995 "parser.tab.c"
    break;

  case 36: /* $@3: %empty  */
#line 271 "parser.y"
      {
          current_decl_type = (NebulaType)(yyvsp[0].type_val);
      }
#line 2003 "parser.tab.c"
    break;

  case 37: /* declaration_stmt: type_spec $@3 init_declarator_list SEMICOLON  */
#line 275 "parser.y"
      {
          (yyval.node) = (yyvsp[-1].node);
      }
#line 2011 "parser.tab.c"
    break;

  case 38: /* init_declarator_list: init_declarator  */
#line 282 "parser.y"
      {
          (yyval.node) = (yyvsp[0].node);
      }
#line 2019 "parser.tab.c"
    break;

  case 39: /* init_declarator_list: init_declarator_list COMMA init_declarator  */
#line 286 "parser.y"
      {
          (yyval.node) = append_node((yyvsp[-2].node), (yyvsp[0].node));
      }
#line 2027 "parser.tab.c"
    break;

  case 40: /* init_declarator: IDENTIFIER  */
#line 293 "parser.y"
      {
          ASTNode *decl = new_ast_node(AST_DECL, (yyvsp[0].str_val));
          decl->inferred_type = current_decl_type;
          declare_variable((yyvsp[0].str_val), current_decl_type, line_no);
          (yyval.node) = decl;
          free((yyvsp[0].str_val));
      }
#line 2039 "parser.tab.c"
    break;

  case 41: /* init_declarator: IDENTIFIER ASSIGN expression  */
#line 301 "parser.y"
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
#line 2055 "parser.tab.c"
    break;

  case 42: /* expression_stmt: expression SEMICOLON  */
#line 316 "parser.y"
      {
          ASTNode *st = new_ast_node(AST_EXPR_STMT, "expr");
          st->left = (yyvsp[-1].expr).node;
          (yyval.node) = st;
      }
#line 2065 "parser.tab.c"
    break;

  case 43: /* expression_stmt: SEMICOLON  */
#line 322 "parser.y"
      {
          (yyval.node) = NULL;
      }
#line 2073 "parser.tab.c"
    break;

  case 44: /* selection_stmt: WHEN LPAREN expression RPAREN statement  */
#line 329 "parser.y"
      {
          ASTNode *node = new_ast_node(AST_IF, "when");
          node->left = (yyvsp[-2].expr).node;
          node->right = (yyvsp[0].node);
          check_condition_type((yyvsp[-2].expr).type, line_no, "when");
          (yyval.node) = node;
      }
#line 2085 "parser.tab.c"
    break;

  case 45: /* selection_stmt: WHEN LPAREN expression RPAREN statement OTHERWISE statement  */
#line 337 "parser.y"
      {
          ASTNode *node = new_ast_node(AST_IF, "when-otherwise");
          node->left = (yyvsp[-4].expr).node;
          node->right = (yyvsp[-2].node);
          node->third = (yyvsp[0].node);
          check_condition_type((yyvsp[-4].expr).type, line_no, "when");
          (yyval.node) = node;
      }
#line 2098 "parser.tab.c"
    break;

  case 46: /* selection_stmt: IF LPAREN expression RPAREN statement  */
#line 346 "parser.y"
      {
          ASTNode *node = new_ast_node(AST_IF, "if");
          node->left = (yyvsp[-2].expr).node;
          node->right = (yyvsp[0].node);
          check_condition_type((yyvsp[-2].expr).type, line_no, "if");
          (yyval.node) = node;
      }
#line 2110 "parser.tab.c"
    break;

  case 47: /* selection_stmt: IF LPAREN expression RPAREN statement ELSE statement  */
#line 354 "parser.y"
      {
          ASTNode *node = new_ast_node(AST_IF, "if-else");
          node->left = (yyvsp[-4].expr).node;
          node->right = (yyvsp[-2].node);
          node->third = (yyvsp[0].node);
          check_condition_type((yyvsp[-4].expr).type, line_no, "if");
          (yyval.node) = node;
      }
#line 2123 "parser.tab.c"
    break;

  case 48: /* selection_stmt: SWITCH LPAREN expression RPAREN LBRACE case_clauses_opt default_clause_opt RBRACE  */
#line 363 "parser.y"
      {
          ASTNode *node = new_ast_node(AST_IF, "switch");
          node->left = (yyvsp[-5].expr).node;
          node->right = (yyvsp[-2].node);
          node->third = (yyvsp[-1].node);
          (yyval.node) = node;
      }
#line 2135 "parser.tab.c"
    break;

  case 49: /* case_clauses_opt: %empty  */
#line 374 "parser.y"
      {
          (yyval.node) = NULL;
      }
#line 2143 "parser.tab.c"
    break;

  case 50: /* case_clauses_opt: case_clauses_opt case_clause  */
#line 378 "parser.y"
      {
          (yyval.node) = append_node((yyvsp[-1].node), (yyvsp[0].node));
      }
#line 2151 "parser.tab.c"
    break;

  case 51: /* case_clause: CASE expression COLON stmt_list_opt  */
#line 385 "parser.y"
      {
          ASTNode *node = new_ast_node(AST_IF, "case");
          node->left = (yyvsp[-2].expr).node;
          node->right = (yyvsp[0].node);
          (yyval.node) = node;
      }
#line 2162 "parser.tab.c"
    break;

  case 52: /* default_clause_opt: %empty  */
#line 395 "parser.y"
      {
          (yyval.node) = NULL;
      }
#line 2170 "parser.tab.c"
    break;

  case 53: /* default_clause_opt: DEFAULT COLON stmt_list_opt  */
#line 399 "parser.y"
      {
          ASTNode *node = new_ast_node(AST_IF, "default");
          node->right = (yyvsp[0].node);
          (yyval.node) = node;
      }
#line 2180 "parser.tab.c"
    break;

  case 54: /* loop_stmt: LOOP LPAREN expression RPAREN statement  */
#line 408 "parser.y"
      {
          ASTNode *node = new_ast_node(AST_WHILE, "loop-while");
          node->left = (yyvsp[-2].expr).node;
          node->body = (yyvsp[0].node);
          check_condition_type((yyvsp[-2].expr).type, line_no, "loop");
          (yyval.node) = node;
      }
#line 2192 "parser.tab.c"
    break;

  case 55: /* loop_stmt: LOOP LPAREN opt_expr SEMICOLON opt_expr SEMICOLON opt_expr RPAREN statement  */
#line 416 "parser.y"
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
#line 2208 "parser.tab.c"
    break;

  case 56: /* loop_stmt: WHILE LPAREN expression RPAREN statement  */
#line 428 "parser.y"
      {
          ASTNode *node = new_ast_node(AST_WHILE, "while");
          node->left = (yyvsp[-2].expr).node;
          node->body = (yyvsp[0].node);
          check_condition_type((yyvsp[-2].expr).type, line_no, "while");
          (yyval.node) = node;
      }
#line 2220 "parser.tab.c"
    break;

  case 57: /* loop_stmt: DO statement WHILE LPAREN expression RPAREN SEMICOLON  */
#line 436 "parser.y"
      {
          ASTNode *node = new_ast_node(AST_DO_WHILE, "do-while");
          node->left = (yyvsp[-2].expr).node;
          node->body = (yyvsp[-5].node);
          check_condition_type((yyvsp[-2].expr).type, line_no, "do-while");
          (yyval.node) = node;
      }
#line 2232 "parser.tab.c"
    break;

  case 58: /* loop_stmt: FOR LPAREN opt_expr SEMICOLON opt_expr SEMICOLON opt_expr RPAREN statement  */
#line 444 "parser.y"
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
#line 2248 "parser.tab.c"
    break;

  case 59: /* opt_expr: %empty  */
#line 459 "parser.y"
      {
          (yyval.expr) = make_expr(TYPE_UNKNOWN, NULL);
      }
#line 2256 "parser.tab.c"
    break;

  case 60: /* opt_expr: expression  */
#line 463 "parser.y"
      {
          (yyval.expr) = (yyvsp[0].expr);
      }
#line 2264 "parser.tab.c"
    break;

  case 61: /* jump_stmt: GIVE expression SEMICOLON  */
#line 470 "parser.y"
      {
          ASTNode *node = new_ast_node(AST_UNARYOP, "give");
          node->left = (yyvsp[-1].expr).node;
          (yyval.node) = node;
      }
#line 2274 "parser.tab.c"
    break;

  case 62: /* jump_stmt: RETURN expression SEMICOLON  */
#line 476 "parser.y"
      {
          ASTNode *node = new_ast_node(AST_UNARYOP, "return");
          node->left = (yyvsp[-1].expr).node;
          (yyval.node) = node;
      }
#line 2284 "parser.tab.c"
    break;

  case 63: /* jump_stmt: BREAK SEMICOLON  */
#line 482 "parser.y"
      {
          (yyval.node) = new_ast_node(AST_UNARYOP, "break");
      }
#line 2292 "parser.tab.c"
    break;

  case 64: /* jump_stmt: CONTINUE SEMICOLON  */
#line 486 "parser.y"
      {
          (yyval.node) = new_ast_node(AST_UNARYOP, "continue");
      }
#line 2300 "parser.tab.c"
    break;

  case 65: /* io_stmt: PRINT LPAREN print_arg_list_opt RPAREN SEMICOLON  */
#line 493 "parser.y"
      {
          ASTNode *node = new_ast_node(AST_PRINT, "print");
          node->left = (yyvsp[-2].node);
          (yyval.node) = node;
      }
#line 2310 "parser.tab.c"
    break;

  case 66: /* io_stmt: PRINT_INLINE LPAREN print_arg_list_opt RPAREN SEMICOLON  */
#line 499 "parser.y"
      {
          ASTNode *node = new_ast_node(AST_PRINT, "print_inline");
          node->left = (yyvsp[-2].node);
          (yyval.node) = node;
      }
#line 2320 "parser.tab.c"
    break;

  case 67: /* io_stmt: INPUT LPAREN IDENTIFIER RPAREN SEMICOLON  */
#line 505 "parser.y"
      {
          ASTNode *node = new_ast_node(AST_INPUT, (yyvsp[-2].str_val));
          (void)resolve_identifier_type((yyvsp[-2].str_val), line_no);
          (yyval.node) = node;
          free((yyvsp[-2].str_val));
      }
#line 2331 "parser.tab.c"
    break;

  case 68: /* print_arg_list_opt: %empty  */
#line 515 "parser.y"
      {
          (yyval.node) = NULL;
      }
#line 2339 "parser.tab.c"
    break;

  case 69: /* print_arg_list_opt: print_arg_list  */
#line 519 "parser.y"
      {
          (yyval.node) = (yyvsp[0].node);
      }
#line 2347 "parser.tab.c"
    break;

  case 70: /* print_arg_list: print_arg  */
#line 526 "parser.y"
      {
          (yyval.node) = (yyvsp[0].node);
      }
#line 2355 "parser.tab.c"
    break;

  case 71: /* print_arg_list: print_arg_list COMMA print_arg  */
#line 530 "parser.y"
      {
          (yyval.node) = append_node((yyvsp[-2].node), (yyvsp[0].node));
      }
#line 2363 "parser.tab.c"
    break;

  case 72: /* print_arg: expression  */
#line 537 "parser.y"
      {
          (yyval.node) = (yyvsp[0].expr).node;
      }
#line 2371 "parser.tab.c"
    break;

  case 73: /* function_call: IDENTIFIER LPAREN argument_list_opt RPAREN  */
#line 544 "parser.y"
      {
          ASTNode *call = new_ast_node(AST_FUNC_CALL, (yyvsp[-3].str_val));
          call->left = (yyvsp[-1].node);
          (yyval.node) = call;
          free((yyvsp[-3].str_val));
      }
#line 2382 "parser.tab.c"
    break;

  case 74: /* argument_list_opt: %empty  */
#line 554 "parser.y"
      {
          (yyval.node) = NULL;
      }
#line 2390 "parser.tab.c"
    break;

  case 75: /* argument_list_opt: argument_list  */
#line 558 "parser.y"
      {
          (yyval.node) = (yyvsp[0].node);
      }
#line 2398 "parser.tab.c"
    break;

  case 76: /* argument_list: expression  */
#line 565 "parser.y"
      {
          (yyval.node) = (yyvsp[0].expr).node;
      }
#line 2406 "parser.tab.c"
    break;

  case 77: /* argument_list: argument_list COMMA expression  */
#line 569 "parser.y"
      {
          (yyval.node) = append_node((yyvsp[-2].node), (yyvsp[0].expr).node);
      }
#line 2414 "parser.tab.c"
    break;

  case 78: /* expression: assignment_expr  */
#line 576 "parser.y"
      {
          (yyval.expr) = (yyvsp[0].expr);
      }
#line 2422 "parser.tab.c"
    break;

  case 79: /* assignment_expr: conditional_expr  */
#line 583 "parser.y"
      {
          (yyval.expr) = (yyvsp[0].expr);
      }
#line 2430 "parser.tab.c"
    break;

  case 80: /* assignment_expr: IDENTIFIER ASSIGN assignment_expr  */
#line 587 "parser.y"
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
#line 2449 "parser.tab.c"
    break;

  case 81: /* conditional_expr: logical_or_expr  */
#line 605 "parser.y"
      {
          (yyval.expr) = (yyvsp[0].expr);
      }
#line 2457 "parser.tab.c"
    break;

  case 82: /* conditional_expr: logical_or_expr QMARK expression COLON conditional_expr  */
#line 609 "parser.y"
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
#line 2480 "parser.tab.c"
    break;

  case 83: /* logical_or_expr: logical_and_expr  */
#line 631 "parser.y"
      {
          (yyval.expr) = (yyvsp[0].expr);
      }
#line 2488 "parser.tab.c"
    break;

  case 84: /* logical_or_expr: logical_or_expr OR logical_and_expr  */
#line 635 "parser.y"
      {
          NebulaType t = logical_result_type((yyvsp[-2].expr).type, (yyvsp[0].expr).type, "||", line_no);
          (yyval.expr) = make_expr(t, new_ast_binary(AST_BINOP, "||", (yyvsp[-2].expr).node, (yyvsp[0].expr).node, t));
      }
#line 2497 "parser.tab.c"
    break;

  case 85: /* logical_and_expr: bitwise_or_expr  */
#line 643 "parser.y"
      {
          (yyval.expr) = (yyvsp[0].expr);
      }
#line 2505 "parser.tab.c"
    break;

  case 86: /* logical_and_expr: logical_and_expr AND bitwise_or_expr  */
#line 647 "parser.y"
      {
          NebulaType t = logical_result_type((yyvsp[-2].expr).type, (yyvsp[0].expr).type, "&&", line_no);
          (yyval.expr) = make_expr(t, new_ast_binary(AST_BINOP, "&&", (yyvsp[-2].expr).node, (yyvsp[0].expr).node, t));
      }
#line 2514 "parser.tab.c"
    break;

  case 87: /* bitwise_or_expr: bitwise_xor_expr  */
#line 655 "parser.y"
      {
          (yyval.expr) = (yyvsp[0].expr);
      }
#line 2522 "parser.tab.c"
    break;

  case 88: /* bitwise_or_expr: bitwise_or_expr BIT_OR bitwise_xor_expr  */
#line 659 "parser.y"
      {
          NebulaType t = bitwise_result_type((yyvsp[-2].expr).type, (yyvsp[0].expr).type, "|", line_no);
          (yyval.expr) = make_expr(t, new_ast_binary(AST_BINOP, "|", (yyvsp[-2].expr).node, (yyvsp[0].expr).node, t));
      }
#line 2531 "parser.tab.c"
    break;

  case 89: /* bitwise_xor_expr: bitwise_and_expr  */
#line 667 "parser.y"
      {
          (yyval.expr) = (yyvsp[0].expr);
      }
#line 2539 "parser.tab.c"
    break;

  case 90: /* bitwise_xor_expr: bitwise_xor_expr BIT_XOR bitwise_and_expr  */
#line 671 "parser.y"
      {
          NebulaType t = bitwise_result_type((yyvsp[-2].expr).type, (yyvsp[0].expr).type, "^", line_no);
          (yyval.expr) = make_expr(t, new_ast_binary(AST_BINOP, "^", (yyvsp[-2].expr).node, (yyvsp[0].expr).node, t));
      }
#line 2548 "parser.tab.c"
    break;

  case 91: /* bitwise_and_expr: equality_expr  */
#line 679 "parser.y"
      {
          (yyval.expr) = (yyvsp[0].expr);
      }
#line 2556 "parser.tab.c"
    break;

  case 92: /* bitwise_and_expr: bitwise_and_expr BIT_AND equality_expr  */
#line 683 "parser.y"
      {
          NebulaType t = bitwise_result_type((yyvsp[-2].expr).type, (yyvsp[0].expr).type, "&", line_no);
          (yyval.expr) = make_expr(t, new_ast_binary(AST_BINOP, "&", (yyvsp[-2].expr).node, (yyvsp[0].expr).node, t));
      }
#line 2565 "parser.tab.c"
    break;

  case 93: /* equality_expr: relational_expr  */
#line 691 "parser.y"
      {
          (yyval.expr) = (yyvsp[0].expr);
      }
#line 2573 "parser.tab.c"
    break;

  case 94: /* equality_expr: equality_expr EQ relational_expr  */
#line 695 "parser.y"
      {
          NebulaType t = equality_result_type((yyvsp[-2].expr).type, (yyvsp[0].expr).type, "==", line_no);
          (yyval.expr) = make_expr(t, new_ast_binary(AST_BINOP, "==", (yyvsp[-2].expr).node, (yyvsp[0].expr).node, t));
      }
#line 2582 "parser.tab.c"
    break;

  case 95: /* equality_expr: equality_expr NEQ relational_expr  */
#line 700 "parser.y"
      {
          NebulaType t = equality_result_type((yyvsp[-2].expr).type, (yyvsp[0].expr).type, "!=", line_no);
          (yyval.expr) = make_expr(t, new_ast_binary(AST_BINOP, "!=", (yyvsp[-2].expr).node, (yyvsp[0].expr).node, t));
      }
#line 2591 "parser.tab.c"
    break;

  case 96: /* relational_expr: shift_expr  */
#line 708 "parser.y"
      {
          (yyval.expr) = (yyvsp[0].expr);
      }
#line 2599 "parser.tab.c"
    break;

  case 97: /* relational_expr: relational_expr LT shift_expr  */
#line 712 "parser.y"
      {
          NebulaType t = relational_result_type((yyvsp[-2].expr).type, (yyvsp[0].expr).type, "<", line_no);
          (yyval.expr) = make_expr(t, new_ast_binary(AST_BINOP, "<", (yyvsp[-2].expr).node, (yyvsp[0].expr).node, t));
      }
#line 2608 "parser.tab.c"
    break;

  case 98: /* relational_expr: relational_expr GT shift_expr  */
#line 717 "parser.y"
      {
          NebulaType t = relational_result_type((yyvsp[-2].expr).type, (yyvsp[0].expr).type, ">", line_no);
          (yyval.expr) = make_expr(t, new_ast_binary(AST_BINOP, ">", (yyvsp[-2].expr).node, (yyvsp[0].expr).node, t));
      }
#line 2617 "parser.tab.c"
    break;

  case 99: /* relational_expr: relational_expr LE shift_expr  */
#line 722 "parser.y"
      {
          NebulaType t = relational_result_type((yyvsp[-2].expr).type, (yyvsp[0].expr).type, "<=", line_no);
          (yyval.expr) = make_expr(t, new_ast_binary(AST_BINOP, "<=", (yyvsp[-2].expr).node, (yyvsp[0].expr).node, t));
      }
#line 2626 "parser.tab.c"
    break;

  case 100: /* relational_expr: relational_expr GE shift_expr  */
#line 727 "parser.y"
      {
          NebulaType t = relational_result_type((yyvsp[-2].expr).type, (yyvsp[0].expr).type, ">=", line_no);
          (yyval.expr) = make_expr(t, new_ast_binary(AST_BINOP, ">=", (yyvsp[-2].expr).node, (yyvsp[0].expr).node, t));
      }
#line 2635 "parser.tab.c"
    break;

  case 101: /* shift_expr: additive_expr  */
#line 735 "parser.y"
      {
          (yyval.expr) = (yyvsp[0].expr);
      }
#line 2643 "parser.tab.c"
    break;

  case 102: /* shift_expr: shift_expr LSHIFT additive_expr  */
#line 739 "parser.y"
      {
          NebulaType t = bitwise_result_type((yyvsp[-2].expr).type, (yyvsp[0].expr).type, "<<", line_no);
          (yyval.expr) = make_expr(t, new_ast_binary(AST_BINOP, "<<", (yyvsp[-2].expr).node, (yyvsp[0].expr).node, t));
      }
#line 2652 "parser.tab.c"
    break;

  case 103: /* shift_expr: shift_expr RSHIFT additive_expr  */
#line 744 "parser.y"
      {
          NebulaType t = bitwise_result_type((yyvsp[-2].expr).type, (yyvsp[0].expr).type, ">>", line_no);
          (yyval.expr) = make_expr(t, new_ast_binary(AST_BINOP, ">>", (yyvsp[-2].expr).node, (yyvsp[0].expr).node, t));
      }
#line 2661 "parser.tab.c"
    break;

  case 104: /* additive_expr: multiplicative_expr  */
#line 752 "parser.y"
      {
          (yyval.expr) = (yyvsp[0].expr);
      }
#line 2669 "parser.tab.c"
    break;

  case 105: /* additive_expr: additive_expr PLUS multiplicative_expr  */
#line 756 "parser.y"
      {
          NebulaType t = arithmetic_result_type((yyvsp[-2].expr).type, (yyvsp[0].expr).type, "+", line_no);
          (yyval.expr) = make_expr(t, new_ast_binary(AST_BINOP, "+", (yyvsp[-2].expr).node, (yyvsp[0].expr).node, t));
      }
#line 2678 "parser.tab.c"
    break;

  case 106: /* additive_expr: additive_expr MINUS multiplicative_expr  */
#line 761 "parser.y"
      {
          NebulaType t = arithmetic_result_type((yyvsp[-2].expr).type, (yyvsp[0].expr).type, "-", line_no);
          (yyval.expr) = make_expr(t, new_ast_binary(AST_BINOP, "-", (yyvsp[-2].expr).node, (yyvsp[0].expr).node, t));
      }
#line 2687 "parser.tab.c"
    break;

  case 107: /* multiplicative_expr: unary_expr  */
#line 769 "parser.y"
      {
          (yyval.expr) = (yyvsp[0].expr);
      }
#line 2695 "parser.tab.c"
    break;

  case 108: /* multiplicative_expr: multiplicative_expr MUL unary_expr  */
#line 773 "parser.y"
      {
          NebulaType t = arithmetic_result_type((yyvsp[-2].expr).type, (yyvsp[0].expr).type, "*", line_no);
          (yyval.expr) = make_expr(t, new_ast_binary(AST_BINOP, "*", (yyvsp[-2].expr).node, (yyvsp[0].expr).node, t));
      }
#line 2704 "parser.tab.c"
    break;

  case 109: /* multiplicative_expr: multiplicative_expr DIV unary_expr  */
#line 778 "parser.y"
      {
          NebulaType t = arithmetic_result_type((yyvsp[-2].expr).type, (yyvsp[0].expr).type, "/", line_no);
          (yyval.expr) = make_expr(t, new_ast_binary(AST_BINOP, "/", (yyvsp[-2].expr).node, (yyvsp[0].expr).node, t));
      }
#line 2713 "parser.tab.c"
    break;

  case 110: /* unary_expr: postfix_expr  */
#line 786 "parser.y"
      {
          (yyval.expr) = (yyvsp[0].expr);
      }
#line 2721 "parser.tab.c"
    break;

  case 111: /* unary_expr: PLUS unary_expr  */
#line 790 "parser.y"
      {
          NebulaType t = unary_plus_minus_type((yyvsp[0].expr).type, "+", line_no);
          (yyval.expr) = make_expr(t, new_ast_unary(AST_UNARYOP, "+", (yyvsp[0].expr).node, t));
      }
#line 2730 "parser.tab.c"
    break;

  case 112: /* unary_expr: MINUS unary_expr  */
#line 795 "parser.y"
      {
          NebulaType t = unary_plus_minus_type((yyvsp[0].expr).type, "-", line_no);
          (yyval.expr) = make_expr(t, new_ast_unary(AST_UNARYOP, "-", (yyvsp[0].expr).node, t));
      }
#line 2739 "parser.tab.c"
    break;

  case 113: /* unary_expr: NOT unary_expr  */
#line 800 "parser.y"
      {
          NebulaType t = unary_not_type((yyvsp[0].expr).type, line_no);
          (yyval.expr) = make_expr(t, new_ast_unary(AST_UNARYOP, "!", (yyvsp[0].expr).node, t));
      }
#line 2748 "parser.tab.c"
    break;

  case 114: /* unary_expr: BIT_NOT unary_expr  */
#line 805 "parser.y"
      {
          NebulaType t = unary_bitnot_type((yyvsp[0].expr).type, line_no);
          (yyval.expr) = make_expr(t, new_ast_unary(AST_UNARYOP, "~", (yyvsp[0].expr).node, t));
      }
#line 2757 "parser.tab.c"
    break;

  case 115: /* unary_expr: INC unary_expr  */
#line 810 "parser.y"
      {
          NebulaType t = incdec_type((yyvsp[0].expr).type, "++", line_no);
          (yyval.expr) = make_expr(t, new_ast_unary(AST_UNARYOP, "++", (yyvsp[0].expr).node, t));
      }
#line 2766 "parser.tab.c"
    break;

  case 116: /* unary_expr: DECREMENT unary_expr  */
#line 815 "parser.y"
      {
          NebulaType t = incdec_type((yyvsp[0].expr).type, "--", line_no);
          (yyval.expr) = make_expr(t, new_ast_unary(AST_UNARYOP, "--", (yyvsp[0].expr).node, t));
      }
#line 2775 "parser.tab.c"
    break;

  case 117: /* postfix_expr: primary_expr  */
#line 823 "parser.y"
      {
          (yyval.expr) = (yyvsp[0].expr);
      }
#line 2783 "parser.tab.c"
    break;

  case 118: /* postfix_expr: postfix_expr INC  */
#line 827 "parser.y"
      {
          NebulaType t = incdec_type((yyvsp[-1].expr).type, "++", line_no);
          (yyval.expr) = make_expr(t, new_ast_unary(AST_UNARYOP, "post++", (yyvsp[-1].expr).node, t));
      }
#line 2792 "parser.tab.c"
    break;

  case 119: /* postfix_expr: postfix_expr DECREMENT  */
#line 832 "parser.y"
      {
          NebulaType t = incdec_type((yyvsp[-1].expr).type, "--", line_no);
          (yyval.expr) = make_expr(t, new_ast_unary(AST_UNARYOP, "post--", (yyvsp[-1].expr).node, t));
      }
#line 2801 "parser.tab.c"
    break;

  case 120: /* postfix_expr: postfix_expr LBRACKET expression RBRACKET  */
#line 837 "parser.y"
      {
          ASTNode *idx = new_ast_binary(AST_BINOP, "[]", (yyvsp[-3].expr).node, (yyvsp[-1].expr).node, (yyvsp[-3].expr).type);
          if ((yyvsp[-1].expr).type != TYPE_NUM) {
              semantic_error(line_no, "Array index must be num, found %s", type_name((yyvsp[-1].expr).type));
          }
          (yyval.expr) = make_expr((yyvsp[-3].expr).type, idx);
      }
#line 2813 "parser.tab.c"
    break;

  case 121: /* primary_expr: IDENTIFIER  */
#line 848 "parser.y"
      {
          NebulaType t = resolve_identifier_type((yyvsp[0].str_val), line_no);
          ASTNode *id = new_ast_node(AST_IDENTIFIER, (yyvsp[0].str_val));
          id->inferred_type = t;
          (yyval.expr) = make_expr(t, id);
          free((yyvsp[0].str_val));
      }
#line 2825 "parser.tab.c"
    break;

  case 122: /* primary_expr: NUM_LITERAL  */
#line 856 "parser.y"
      {
          char buf[64];
          snprintf(buf, sizeof(buf), "%d", (yyvsp[0].num_val));
          (yyval.expr) = make_expr(TYPE_NUM, new_ast_node(AST_LITERAL, buf));
      }
#line 2835 "parser.tab.c"
    break;

  case 123: /* primary_expr: DEC_LITERAL  */
#line 862 "parser.y"
      {
          char buf[64];
          snprintf(buf, sizeof(buf), "%g", (yyvsp[0].dec_val));
          (yyval.expr) = make_expr(TYPE_DEC, new_ast_node(AST_LITERAL, buf));
      }
#line 2845 "parser.tab.c"
    break;

  case 124: /* primary_expr: CHAR_LITERAL  */
#line 868 "parser.y"
      {
          char buf[8];
          snprintf(buf, sizeof(buf), "'%c'", (yyvsp[0].char_val));
          (yyval.expr) = make_expr(TYPE_CHAR, new_ast_node(AST_LITERAL, buf));
      }
#line 2855 "parser.tab.c"
    break;

  case 125: /* primary_expr: STRING_LITERAL  */
#line 874 "parser.y"
      {
          (yyval.expr) = make_expr(TYPE_UNKNOWN, new_ast_node(AST_LITERAL, (yyvsp[0].str_val)));
          free((yyvsp[0].str_val));
      }
#line 2864 "parser.tab.c"
    break;

  case 126: /* primary_expr: TRUE  */
#line 879 "parser.y"
      {
          (yyval.expr) = make_expr(TYPE_BOOL, new_ast_node(AST_LITERAL, "true"));
      }
#line 2872 "parser.tab.c"
    break;

  case 127: /* primary_expr: FALSE  */
#line 883 "parser.y"
      {
          (yyval.expr) = make_expr(TYPE_BOOL, new_ast_node(AST_LITERAL, "false"));
      }
#line 2880 "parser.tab.c"
    break;

  case 128: /* primary_expr: function_call  */
#line 887 "parser.y"
      {
          (yyval.expr) = make_expr(TYPE_UNKNOWN, (yyvsp[0].node));
      }
#line 2888 "parser.tab.c"
    break;

  case 129: /* primary_expr: INPUT LPAREN RPAREN  */
#line 891 "parser.y"
      {
          (yyval.expr) = make_expr(TYPE_UNKNOWN, new_ast_node(AST_INPUT, "input"));
      }
#line 2896 "parser.tab.c"
    break;

  case 130: /* primary_expr: NEBULA LPAREN IDENTIFIER COMMA expression RPAREN  */
#line 895 "parser.y"
      {
          ASTNode *id = new_ast_node(AST_IDENTIFIER, (yyvsp[-3].str_val));
          ASTNode *call = new_ast_node(AST_FUNC_CALL, "nebula");
          id->inferred_type = resolve_identifier_type((yyvsp[-3].str_val), line_no);
          call->left = append_node(id, (yyvsp[-1].expr).node);
          (yyval.expr) = make_expr(TYPE_NUM, call);
          free((yyvsp[-3].str_val));
      }
#line 2909 "parser.tab.c"
    break;

  case 131: /* primary_expr: LPAREN expression RPAREN  */
#line 904 "parser.y"
      {
          (yyval.expr) = (yyvsp[-1].expr);
      }
#line 2917 "parser.tab.c"
    break;


#line 2921 "parser.tab.c"

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

#line 909 "parser.y"


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
