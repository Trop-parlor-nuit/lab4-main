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

#ifndef YY_YY_INCLUDE_PARSER_H_INCLUDED
# define YY_YY_INCLUDE_PARSER_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 10 "src/parser.y"

    #include "Ast.h"
    #include "SymbolTable.h"
    #include "Type.h"

#line 55 "include/parser.h"

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    ID = 258,                      /* ID  */
    INTEGER = 259,                 /* INTEGER  */
    FLO = 260,                     /* FLO  */
    IF = 261,                      /* IF  */
    ELSE = 262,                    /* ELSE  */
    INT = 263,                     /* INT  */
    VOID = 264,                    /* VOID  */
    FLOAT = 265,                   /* FLOAT  */
    CHAR = 266,                    /* CHAR  */
    LPAREN = 267,                  /* LPAREN  */
    RPAREN = 268,                  /* RPAREN  */
    LBRACE = 269,                  /* LBRACE  */
    RBRACE = 270,                  /* RBRACE  */
    SEMICOLON = 271,               /* SEMICOLON  */
    ADD = 272,                     /* ADD  */
    SUB = 273,                     /* SUB  */
    ASSIGN = 274,                  /* ASSIGN  */
    RETURN = 275,                  /* RETURN  */
    ALIGNAS = 276,                 /* ALIGNAS  */
    ALIGNOF = 277,                 /* ALIGNOF  */
    AUTO = 278,                    /* AUTO  */
    BOOL = 279,                    /* BOOL  */
    BREAK = 280,                   /* BREAK  */
    CASE = 281,                    /* CASE  */
    CATCH = 282,                   /* CATCH  */
    CHAR8_T = 283,                 /* CHAR8_T  */
    CHAR16_T = 284,                /* CHAR16_T  */
    CHAR32_T = 285,                /* CHAR32_T  */
    CLASS = 286,                   /* CLASS  */
    CONST = 287,                   /* CONST  */
    CONSTEXPR = 288,               /* CONSTEXPR  */
    CONST_CAST = 289,              /* CONST_CAST  */
    CONTINUE = 290,                /* CONTINUE  */
    DECLTYPE = 291,                /* DECLTYPE  */
    DEFAULT = 292,                 /* DEFAULT  */
    DELETE = 293,                  /* DELETE  */
    DO = 294,                      /* DO  */
    DOUBLE = 295,                  /* DOUBLE  */
    DYNAMIC_CAST = 296,            /* DYNAMIC_CAST  */
    ENUM = 297,                    /* ENUM  */
    EXPLICIT = 298,                /* EXPLICIT  */
    EXPORT = 299,                  /* EXPORT  */
    EXTERN = 300,                  /* EXTERN  */
    FALSE = 301,                   /* FALSE  */
    FOR = 302,                     /* FOR  */
    FRIEND = 303,                  /* FRIEND  */
    GOTO = 304,                    /* GOTO  */
    INLINE = 305,                  /* INLINE  */
    LONG = 306,                    /* LONG  */
    MUTABLE = 307,                 /* MUTABLE  */
    NAMESPACE = 308,               /* NAMESPACE  */
    NEW = 309,                     /* NEW  */
    NOEXCEPT = 310,                /* NOEXCEPT  */
    NULLPTR = 311,                 /* NULLPTR  */
    OPERATOR = 312,                /* OPERATOR  */
    PRIVATE = 313,                 /* PRIVATE  */
    PROTECTED = 314,               /* PROTECTED  */
    PUBLIC = 315,                  /* PUBLIC  */
    REGISTER = 316,                /* REGISTER  */
    REINTERPRET_CAST = 317,        /* REINTERPRET_CAST  */
    REQUIRES = 318,                /* REQUIRES  */
    SHORT = 319,                   /* SHORT  */
    SIGNED = 320,                  /* SIGNED  */
    SIZEOF = 321,                  /* SIZEOF  */
    STATIC = 322,                  /* STATIC  */
    STATIC_ASSERT = 323,           /* STATIC_ASSERT  */
    STATIC_CAST = 324,             /* STATIC_CAST  */
    STRUCT = 325,                  /* STRUCT  */
    SWITCH = 326,                  /* SWITCH  */
    TEMPLATE = 327,                /* TEMPLATE  */
    THIS = 328,                    /* THIS  */
    THREAD_LOCAL = 329,            /* THREAD_LOCAL  */
    THROW = 330,                   /* THROW  */
    TRUE = 331,                    /* TRUE  */
    TRY = 332,                     /* TRY  */
    TYPEDEF = 333,                 /* TYPEDEF  */
    TYPEID = 334,                  /* TYPEID  */
    TYPENAME = 335,                /* TYPENAME  */
    UNION = 336,                   /* UNION  */
    UNSIGNED = 337,                /* UNSIGNED  */
    USING = 338,                   /* USING  */
    VIRTUAL = 339,                 /* VIRTUAL  */
    VOLATILE = 340,                /* VOLATILE  */
    WHILE = 341,                   /* WHILE  */
    MUL = 342,                     /* MUL  */
    DIV = 343,                     /* DIV  */
    MOD = 344,                     /* MOD  */
    EQ = 345,                      /* EQ  */
    LT = 346,                      /* LT  */
    NEQ = 347,                     /* NEQ  */
    LE = 348,                      /* LE  */
    GT = 349,                      /* GT  */
    GE = 350,                      /* GE  */
    NE = 351,                      /* NE  */
    PLUSASSIGN = 352,              /* PLUSASSIGN  */
    MINUSASSIGN = 353,             /* MINUSASSIGN  */
    MULTASSIGN = 354,              /* MULTASSIGN  */
    DIVASSIGN = 355,               /* DIVASSIGN  */
    MODASSIGN = 356,               /* MODASSIGN  */
    ANDASSIGN = 357,               /* ANDASSIGN  */
    ORASSIGN = 358,                /* ORASSIGN  */
    XORASSIGN = 359,               /* XORASSIGN  */
    LSHIFTASSIGN = 360,            /* LSHIFTASSIGN  */
    RSHIFTASSIGN = 361,            /* RSHIFTASSIGN  */
    INCREMENT = 362,               /* INCREMENT  */
    DECREMENT = 363,               /* DECREMENT  */
    BITAND = 364,                  /* BITAND  */
    BITOR = 365,                   /* BITOR  */
    BITXOR = 366,                  /* BITXOR  */
    BITNOT = 367,                  /* BITNOT  */
    MODULO = 368,                  /* MODULO  */
    LSHIFT = 369,                  /* LSHIFT  */
    RSHIFT = 370,                  /* RSHIFT  */
    LOGAND = 371,                  /* LOGAND  */
    LOGOR = 372,                   /* LOGOR  */
    NOT = 373,                     /* NOT  */
    THEN = 374                     /* THEN  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 16 "src/parser.y"

    int itype;
    float ftype;
    char* strtype;
    StmtNode* stmttype;
    ExprNode* exprtype;
    Type* type;

#line 200 "include/parser.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_INCLUDE_PARSER_H_INCLUDED  */
