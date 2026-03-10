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
    ADDRESS_OF = 263,              /* ADDRESS_OF  */
    PLUS = 264,                    /* PLUS  */
    MINUS = 265,                   /* MINUS  */
    MUL = 266,                     /* MUL  */
    DIV = 267,                     /* DIV  */
    LT = 268,                      /* LT  */
    LE = 269,                      /* LE  */
    GT = 270,                      /* GT  */
    GE = 271,                      /* GE  */
    EQ = 272,                      /* EQ  */
    NE = 273,                      /* NE  */
    LPAREN = 274,                  /* LPAREN  */
    RPAREN = 275,                  /* RPAREN  */
    ASSIGN = 276,                  /* ASSIGN  */
    SEMICOLON = 277,               /* SEMICOLON  */
    COMMA = 278,                   /* COMMA  */
    RSQBR = 279,                   /* RSQBR  */
    LSQBR = 280,                   /* LSQBR  */
    kBEGIN = 281,                  /* kBEGIN  */
    kEND = 282,                    /* kEND  */
    WRITE = 283,                   /* WRITE  */
    READ = 284,                    /* READ  */
    IF = 285,                      /* IF  */
    THEN = 286,                    /* THEN  */
    ELSE = 287,                    /* ELSE  */
    WHILE = 288,                   /* WHILE  */
    ENDIF = 289,                   /* ENDIF  */
    ENDWHILE = 290,                /* ENDWHILE  */
    DO = 291,                      /* DO  */
    DECL = 292,                    /* DECL  */
    ENDDECL = 293                  /* ENDDECL  */
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
#define ADDRESS_OF 263
#define PLUS 264
#define MINUS 265
#define MUL 266
#define DIV 267
#define LT 268
#define LE 269
#define GT 270
#define GE 271
#define EQ 272
#define NE 273
#define LPAREN 274
#define RPAREN 275
#define ASSIGN 276
#define SEMICOLON 277
#define COMMA 278
#define RSQBR 279
#define LSQBR 280
#define kBEGIN 281
#define kEND 282
#define WRITE 283
#define READ 284
#define IF 285
#define THEN 286
#define ELSE 287
#define WHILE 288
#define ENDIF 289
#define ENDWHILE 290
#define DO 291
#define DECL 292
#define ENDDECL 293

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
