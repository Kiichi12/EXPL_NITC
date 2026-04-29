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
    SELF_KW = 261,                 /* SELF_KW  */
    INT = 262,                     /* INT  */
    STR = 263,                     /* STR  */
    MAIN = 264,                    /* MAIN  */
    DECL = 265,                    /* DECL  */
    ENDDECL = 266,                 /* ENDDECL  */
    kBEGIN = 267,                  /* kBEGIN  */
    kEND = 268,                    /* kEND  */
    WRITE = 269,                   /* WRITE  */
    READ = 270,                    /* READ  */
    RETURN = 271,                  /* RETURN  */
    IF = 272,                      /* IF  */
    THEN = 273,                    /* THEN  */
    ELSE = 274,                    /* ELSE  */
    ENDIF = 275,                   /* ENDIF  */
    WHILE = 276,                   /* WHILE  */
    DO = 277,                      /* DO  */
    ENDWHILE = 278,                /* ENDWHILE  */
    BREAK = 279,                   /* BREAK  */
    CONTINUE = 280,                /* CONTINUE  */
    SEMICOLON = 281,               /* SEMICOLON  */
    COMMA = 282,                   /* COMMA  */
    LPAREN = 283,                  /* LPAREN  */
    RPAREN = 284,                  /* RPAREN  */
    LBRACE = 285,                  /* LBRACE  */
    RBRACE = 286,                  /* RBRACE  */
    LSQBR = 287,                   /* LSQBR  */
    RSQBR = 288,                   /* RSQBR  */
    ASSIGN = 289,                  /* ASSIGN  */
    ADDRESS_OF = 290,              /* ADDRESS_OF  */
    MUL = 291,                     /* MUL  */
    TYPE_KW = 292,                 /* TYPE_KW  */
    ENDTYPE = 293,                 /* ENDTYPE  */
    DOT = 294,                     /* DOT  */
    ALLOC = 295,                   /* ALLOC  */
    FREE_KW = 296,                 /* FREE_KW  */
    INITIALIZE = 297,              /* INITIALIZE  */
    NULLVAL = 298,                 /* NULLVAL  */
    CLASS = 299,                   /* CLASS  */
    ENDCLASS = 300,                /* ENDCLASS  */
    NEW_KW = 301,                  /* NEW_KW  */
    DELETE_KW = 302,               /* DELETE_KW  */
    EXTENDS = 303,                 /* EXTENDS  */
    OR = 304,                      /* OR  */
    AND = 305,                     /* AND  */
    NOT = 306,                     /* NOT  */
    PLUS = 307,                    /* PLUS  */
    MINUS = 308,                   /* MINUS  */
    DIV = 309,                     /* DIV  */
    LT = 310,                      /* LT  */
    LE = 311,                      /* LE  */
    GT = 312,                      /* GT  */
    GE = 313,                      /* GE  */
    EQ = 314,                      /* EQ  */
    NE = 315,                      /* NE  */
    UNARY = 316                    /* UNARY  */
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
#define SELF_KW 261
#define INT 262
#define STR 263
#define MAIN 264
#define DECL 265
#define ENDDECL 266
#define kBEGIN 267
#define kEND 268
#define WRITE 269
#define READ 270
#define RETURN 271
#define IF 272
#define THEN 273
#define ELSE 274
#define ENDIF 275
#define WHILE 276
#define DO 277
#define ENDWHILE 278
#define BREAK 279
#define CONTINUE 280
#define SEMICOLON 281
#define COMMA 282
#define LPAREN 283
#define RPAREN 284
#define LBRACE 285
#define RBRACE 286
#define LSQBR 287
#define RSQBR 288
#define ASSIGN 289
#define ADDRESS_OF 290
#define MUL 291
#define TYPE_KW 292
#define ENDTYPE 293
#define DOT 294
#define ALLOC 295
#define FREE_KW 296
#define INITIALIZE 297
#define NULLVAL 298
#define CLASS 299
#define ENDCLASS 300
#define NEW_KW 301
#define DELETE_KW 302
#define EXTENDS 303
#define OR 304
#define AND 305
#define NOT 306
#define PLUS 307
#define MINUS 308
#define DIV 309
#define LT 310
#define LE 311
#define GT 312
#define GE 313
#define EQ 314
#define NE 315
#define UNARY 316

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 37 "task1.y"

    struct tnode *node;
    struct Paramstruct *param;
    struct TypeInfo typeData;

#line 195 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
