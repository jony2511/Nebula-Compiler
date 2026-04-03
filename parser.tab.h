/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    NUM_LITERAL = 258,             /* NUM_LITERAL  */
    DEC_LITERAL = 259,             /* DEC_LITERAL  */
    CHAR_LITERAL = 260,            /* CHAR_LITERAL  */
    STRING_LITERAL = 261,          /* STRING_LITERAL  */
    IDENTIFIER = 262,              /* IDENTIFIER  */
    INT = 263,                     /* INT  */
    FLOAT = 264,                   /* FLOAT  */
    DOUBLE = 265,                  /* DOUBLE  */
    NUM = 266,                     /* NUM  */
    DEC = 267,                     /* DEC  */
    CHAR = 268,                    /* CHAR  */
    BOOL = 269,                    /* BOOL  */
    VOID = 270,                    /* VOID  */
    STRUCT = 271,                  /* STRUCT  */
    ENUM = 272,                    /* ENUM  */
    IF = 273,                      /* IF  */
    ELSE = 274,                    /* ELSE  */
    SWITCH = 275,                  /* SWITCH  */
    CASE = 276,                    /* CASE  */
    DEFAULT = 277,                 /* DEFAULT  */
    WHILE = 278,                   /* WHILE  */
    DO = 279,                      /* DO  */
    FOR = 280,                     /* FOR  */
    BREAK = 281,                   /* BREAK  */
    CONTINUE = 282,                /* CONTINUE  */
    RETURN = 283,                  /* RETURN  */
    FUNCTION = 284,                /* FUNCTION  */
    WHEN = 285,                    /* WHEN  */
    OTHERWISE = 286,               /* OTHERWISE  */
    LOOP = 287,                    /* LOOP  */
    GIVE = 288,                    /* GIVE  */
    PRINT = 289,                   /* PRINT  */
    INPUT = 290,                   /* INPUT  */
    TRUE = 291,                    /* TRUE  */
    FALSE = 292,                   /* FALSE  */
    INC = 293,                     /* INC  */
    DECREMENT = 294,               /* DECREMENT  */
    EQ = 295,                      /* EQ  */
    NEQ = 296,                     /* NEQ  */
    LE = 297,                      /* LE  */
    GE = 298,                      /* GE  */
    LT = 299,                      /* LT  */
    GT = 300,                      /* GT  */
    ASSIGN = 301,                  /* ASSIGN  */
    AND = 302,                     /* AND  */
    OR = 303,                      /* OR  */
    BIT_AND = 304,                 /* BIT_AND  */
    BIT_OR = 305,                  /* BIT_OR  */
    BIT_XOR = 306,                 /* BIT_XOR  */
    BIT_NOT = 307,                 /* BIT_NOT  */
    LSHIFT = 308,                  /* LSHIFT  */
    RSHIFT = 309,                  /* RSHIFT  */
    PLUS = 310,                    /* PLUS  */
    MINUS = 311,                   /* MINUS  */
    MUL = 312,                     /* MUL  */
    DIV = 313,                     /* DIV  */
    NOT = 314,                     /* NOT  */
    QMARK = 315,                   /* QMARK  */
    COLON = 316,                   /* COLON  */
    ARROW_R = 317,                 /* ARROW_R  */
    ARROW_L = 318,                 /* ARROW_L  */
    SEMICOLON = 319,               /* SEMICOLON  */
    COMMA = 320,                   /* COMMA  */
    LPAREN = 321,                  /* LPAREN  */
    RPAREN = 322,                  /* RPAREN  */
    LBRACE = 323,                  /* LBRACE  */
    RBRACE = 324,                  /* RBRACE  */
    LBRACKET = 325,                /* LBRACKET  */
    RBRACKET = 326,                /* RBRACKET  */
    INVALID = 327,                 /* INVALID  */
    LOWER_THAN_OTHERWISE = 328,    /* LOWER_THAN_OTHERWISE  */
    UMINUS = 329,                  /* UMINUS  */
    UPLUS = 330                    /* UPLUS  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 19 "parser.y"

    int num_val;
    double dec_val;
    char char_val;
    char *str_val;

#line 146 "parser.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */
