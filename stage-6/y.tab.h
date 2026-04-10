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

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
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
    NUM = 258,                     /* NUM  */
    ID = 259,                      /* ID  */
    STRING = 260,                  /* STRING  */
    INT = 261,                     /* INT  */
    STR = 262,                     /* STR  */
    MAIN = 263,                    /* MAIN  */
    DECL = 264,                    /* DECL  */
    ENDDECL = 265,                 /* ENDDECL  */
    kBEGIN = 266,                  /* kBEGIN  */
    kEND = 267,                    /* kEND  */
    WRITE = 268,                   /* WRITE  */
    READ = 269,                    /* READ  */
    RETURN = 270,                  /* RETURN  */
    IF = 271,                      /* IF  */
    THEN = 272,                    /* THEN  */
    ELSE = 273,                    /* ELSE  */
    ENDIF = 274,                   /* ENDIF  */
    WHILE = 275,                   /* WHILE  */
    DO = 276,                      /* DO  */
    ENDWHILE = 277,                /* ENDWHILE  */
    BREAK = 278,                   /* BREAK  */
    CONTINUE = 279,                /* CONTINUE  */
    SEMICOLON = 280,               /* SEMICOLON  */
    COMMA = 281,                   /* COMMA  */
    LPAREN = 282,                  /* LPAREN  */
    RPAREN = 283,                  /* RPAREN  */
    LBRACE = 284,                  /* LBRACE  */
    RBRACE = 285,                  /* RBRACE  */
    LSQBR = 286,                   /* LSQBR  */
    RSQBR = 287,                   /* RSQBR  */
    ASSIGN = 288,                  /* ASSIGN  */
    ADDRESS_OF = 289,              /* ADDRESS_OF  */
    MUL = 290,                     /* MUL  */
    TYPE_KW = 291,                 /* TYPE_KW  */
    ENDTYPE = 292,                 /* ENDTYPE  */
    DOT = 293,                     /* DOT  */
    ALLOC = 294,                   /* ALLOC  */
    FREE_KW = 295,                 /* FREE_KW  */
    INITIALIZE = 296,              /* INITIALIZE  */
    NULLVAL = 297,                 /* NULLVAL  */
    OR = 298,                      /* OR  */
    AND = 299,                     /* AND  */
    NOT = 300,                     /* NOT  */
    PLUS = 301,                    /* PLUS  */
    MINUS = 302,                   /* MINUS  */
    DIV = 303,                     /* DIV  */
    LT = 304,                      /* LT  */
    LE = 305,                      /* LE  */
    GT = 306,                      /* GT  */
    GE = 307,                      /* GE  */
    EQ = 308,                      /* EQ  */
    NE = 309,                      /* NE  */
    UNARY = 310                    /* UNARY  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define NUM 258
#define ID 259
#define STRING 260
#define INT 261
#define STR 262
#define MAIN 263
#define DECL 264
#define ENDDECL 265
#define kBEGIN 266
#define kEND 267
#define WRITE 268
#define READ 269
#define RETURN 270
#define IF 271
#define THEN 272
#define ELSE 273
#define ENDIF 274
#define WHILE 275
#define DO 276
#define ENDWHILE 277
#define BREAK 278
#define CONTINUE 279
#define SEMICOLON 280
#define COMMA 281
#define LPAREN 282
#define RPAREN 283
#define LBRACE 284
#define RBRACE 285
#define LSQBR 286
#define RSQBR 287
#define ASSIGN 288
#define ADDRESS_OF 289
#define MUL 290
#define TYPE_KW 291
#define ENDTYPE 292
#define DOT 293
#define ALLOC 294
#define FREE_KW 295
#define INITIALIZE 296
#define NULLVAL 297
#define OR 298
#define AND 299
#define NOT 300
#define PLUS 301
#define MINUS 302
#define DIV 303
#define LT 304
#define LE 305
#define GT 306
#define GE 307
#define EQ 308
#define NE 309
#define UNARY 310

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 30 "task1.y"

    struct tnode *node;
    struct Paramstruct *param;
    struct TypeInfo typeData;

#line 183 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
