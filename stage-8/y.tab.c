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
#line 1 "task1.y"

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "tree.h"
    #include "memory.h"
    #include "yacc-helper.h"
    #include "codegeneration.h"
    #include "register.h"
    #include "labels.h"
    #include "typetable.h"
    #include "classtable.h"

    void yyerror(char *s);
    int yylex();
    extern FILE *yyin;
    extern int lineNumber;
    tnode *root;
    FILE *interim_file;
    char *current_function_name;
    extern char * yytext;

    // to store the type of the current declaration line
    struct TypeInfo currentTypeData;

    // to store the udeftype being defined
    static TypeTableEntry *currentUdefType = NULL;

    // to store the current class being defined
    static ClassTableEntry *currentClassEntry = NULL;

    // for usage of self in method definitions
    ClassTableEntry *selfClassEntry = NULL;

#line 106 "y.tab.c"

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

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
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

#line 287 "y.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_NUM = 3,                        /* NUM  */
  YYSYMBOL_ID = 4,                         /* ID  */
  YYSYMBOL_STRING = 5,                     /* STRING  */
  YYSYMBOL_SELF_KW = 6,                    /* SELF_KW  */
  YYSYMBOL_INT = 7,                        /* INT  */
  YYSYMBOL_STR = 8,                        /* STR  */
  YYSYMBOL_MAIN = 9,                       /* MAIN  */
  YYSYMBOL_DECL = 10,                      /* DECL  */
  YYSYMBOL_ENDDECL = 11,                   /* ENDDECL  */
  YYSYMBOL_kBEGIN = 12,                    /* kBEGIN  */
  YYSYMBOL_kEND = 13,                      /* kEND  */
  YYSYMBOL_WRITE = 14,                     /* WRITE  */
  YYSYMBOL_READ = 15,                      /* READ  */
  YYSYMBOL_RETURN = 16,                    /* RETURN  */
  YYSYMBOL_IF = 17,                        /* IF  */
  YYSYMBOL_THEN = 18,                      /* THEN  */
  YYSYMBOL_ELSE = 19,                      /* ELSE  */
  YYSYMBOL_ENDIF = 20,                     /* ENDIF  */
  YYSYMBOL_WHILE = 21,                     /* WHILE  */
  YYSYMBOL_DO = 22,                        /* DO  */
  YYSYMBOL_ENDWHILE = 23,                  /* ENDWHILE  */
  YYSYMBOL_BREAK = 24,                     /* BREAK  */
  YYSYMBOL_CONTINUE = 25,                  /* CONTINUE  */
  YYSYMBOL_SEMICOLON = 26,                 /* SEMICOLON  */
  YYSYMBOL_COMMA = 27,                     /* COMMA  */
  YYSYMBOL_LPAREN = 28,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 29,                    /* RPAREN  */
  YYSYMBOL_LBRACE = 30,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 31,                    /* RBRACE  */
  YYSYMBOL_LSQBR = 32,                     /* LSQBR  */
  YYSYMBOL_RSQBR = 33,                     /* RSQBR  */
  YYSYMBOL_ASSIGN = 34,                    /* ASSIGN  */
  YYSYMBOL_ADDRESS_OF = 35,                /* ADDRESS_OF  */
  YYSYMBOL_MUL = 36,                       /* MUL  */
  YYSYMBOL_TYPE_KW = 37,                   /* TYPE_KW  */
  YYSYMBOL_ENDTYPE = 38,                   /* ENDTYPE  */
  YYSYMBOL_DOT = 39,                       /* DOT  */
  YYSYMBOL_ALLOC = 40,                     /* ALLOC  */
  YYSYMBOL_FREE_KW = 41,                   /* FREE_KW  */
  YYSYMBOL_INITIALIZE = 42,                /* INITIALIZE  */
  YYSYMBOL_NULLVAL = 43,                   /* NULLVAL  */
  YYSYMBOL_CLASS = 44,                     /* CLASS  */
  YYSYMBOL_ENDCLASS = 45,                  /* ENDCLASS  */
  YYSYMBOL_NEW_KW = 46,                    /* NEW_KW  */
  YYSYMBOL_DELETE_KW = 47,                 /* DELETE_KW  */
  YYSYMBOL_EXTENDS = 48,                   /* EXTENDS  */
  YYSYMBOL_OR = 49,                        /* OR  */
  YYSYMBOL_AND = 50,                       /* AND  */
  YYSYMBOL_NOT = 51,                       /* NOT  */
  YYSYMBOL_PLUS = 52,                      /* PLUS  */
  YYSYMBOL_MINUS = 53,                     /* MINUS  */
  YYSYMBOL_DIV = 54,                       /* DIV  */
  YYSYMBOL_LT = 55,                        /* LT  */
  YYSYMBOL_LE = 56,                        /* LE  */
  YYSYMBOL_GT = 57,                        /* GT  */
  YYSYMBOL_GE = 58,                        /* GE  */
  YYSYMBOL_EQ = 59,                        /* EQ  */
  YYSYMBOL_NE = 60,                        /* NE  */
  YYSYMBOL_UNARY = 61,                     /* UNARY  */
  YYSYMBOL_YYACCEPT = 62,                  /* $accept  */
  YYSYMBOL_Program = 63,                   /* Program  */
  YYSYMBOL_64_1 = 64,                      /* $@1  */
  YYSYMBOL_ClassDefBlock = 65,             /* ClassDefBlock  */
  YYSYMBOL_ClassDeflist = 66,              /* ClassDeflist  */
  YYSYMBOL_ClassDef = 67,                  /* ClassDef  */
  YYSYMBOL_68_2 = 68,                      /* $@2  */
  YYSYMBOL_69_3 = 69,                      /* $@3  */
  YYSYMBOL_ClassMemberDecList = 70,        /* ClassMemberDecList  */
  YYSYMBOL_ClassMemberDec = 71,            /* ClassMemberDec  */
  YYSYMBOL_MethodDefList = 72,             /* MethodDefList  */
  YYSYMBOL_MethodDef = 73,                 /* MethodDef  */
  YYSYMBOL_74_4 = 74,                      /* $@4  */
  YYSYMBOL_75_5 = 75,                      /* $@5  */
  YYSYMBOL_TypeDefBlock = 76,              /* TypeDefBlock  */
  YYSYMBOL_TypeDefList = 77,               /* TypeDefList  */
  YYSYMBOL_TypeDef = 78,                   /* TypeDef  */
  YYSYMBOL_79_6 = 79,                      /* $@6  */
  YYSYMBOL_FieldDecList = 80,              /* FieldDecList  */
  YYSYMBOL_FieldDec = 81,                  /* FieldDec  */
  YYSYMBOL_GDeclarations = 82,             /* GDeclarations  */
  YYSYMBOL_GDecList = 83,                  /* GDecList  */
  YYSYMBOL_GDecl = 84,                     /* GDecl  */
  YYSYMBOL_GidList = 85,                   /* GidList  */
  YYSYMBOL_Gid = 86,                       /* Gid  */
  YYSYMBOL_Type = 87,                      /* Type  */
  YYSYMBOL_ParamList = 88,                 /* ParamList  */
  YYSYMBOL_Param = 89,                     /* Param  */
  YYSYMBOL_FdefBlock = 90,                 /* FdefBlock  */
  YYSYMBOL_Fdef = 91,                      /* Fdef  */
  YYSYMBOL_92_7 = 92,                      /* $@7  */
  YYSYMBOL_93_8 = 93,                      /* $@8  */
  YYSYMBOL_LdeclBlock = 94,                /* LdeclBlock  */
  YYSYMBOL_LDecList = 95,                  /* LDecList  */
  YYSYMBOL_LDecl = 96,                     /* LDecl  */
  YYSYMBOL_IdList = 97,                    /* IdList  */
  YYSYMBOL_MainBlock = 98,                 /* MainBlock  */
  YYSYMBOL_99_9 = 99,                      /* $@9  */
  YYSYMBOL_Body = 100,                     /* Body  */
  YYSYMBOL_Slist = 101,                    /* Slist  */
  YYSYMBOL_Stmt = 102,                     /* Stmt  */
  YYSYMBOL_InputStmt = 103,                /* InputStmt  */
  YYSYMBOL_OutputStmt = 104,               /* OutputStmt  */
  YYSYMBOL_FreeStmt = 105,                 /* FreeStmt  */
  YYSYMBOL_DeleteStmt = 106,               /* DeleteStmt  */
  YYSYMBOL_InitStmt = 107,                 /* InitStmt  */
  YYSYMBOL_AssgStmt = 108,                 /* AssgStmt  */
  YYSYMBOL_LValue = 109,                   /* LValue  */
  YYSYMBOL_FieldAccess = 110,              /* FieldAccess  */
  YYSYMBOL_IfStmt = 111,                   /* IfStmt  */
  YYSYMBOL_WhileStmt = 112,                /* WhileStmt  */
  YYSYMBOL_BreakStmt = 113,                /* BreakStmt  */
  YYSYMBOL_ContinueStmt = 114,             /* ContinueStmt  */
  YYSYMBOL_E = 115,                        /* E  */
  YYSYMBOL_ArgList = 116                   /* ArgList  */
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
typedef yytype_int16 yy_state_t;

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

#if !defined yyoverflow

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
#endif /* !defined yyoverflow */

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
#define YYFINAL  7
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   606

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  62
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  55
/* YYNRULES -- Number of rules.  */
#define YYNRULES  140
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  304

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   316


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
      55,    56,    57,    58,    59,    60,    61
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    72,    72,    71,    87,    88,    89,    92,    93,    98,
      97,   113,   112,   130,   131,   135,   166,   175,   254,   255,
     256,   261,   260,   302,   301,   347,   351,   355,   356,   361,
     360,   371,   372,   376,   421,   425,   426,   430,   431,   435,
     439,   440,   444,   449,   453,   458,   465,   469,   473,   477,
     504,   505,   509,   513,   514,   519,   518,   566,   565,   619,
     620,   621,   625,   626,   630,   634,   639,   647,   646,   679,
     680,   684,   685,   689,   690,   691,   692,   693,   694,   695,
     696,   697,   698,   699,   700,   704,   705,   706,   711,   718,
     722,   729,   736,   742,   743,   748,   752,   759,   763,   767,
     771,   776,   780,   798,   799,   803,   807,   811,   815,   816,
     817,   818,   819,   820,   821,   822,   823,   824,   825,   826,
     827,   828,   829,   830,   831,   832,   833,   834,   835,   836,
     837,   838,   839,   854,   869,   884,   885,   886,   891,   900,
     901
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "NUM", "ID", "STRING",
  "SELF_KW", "INT", "STR", "MAIN", "DECL", "ENDDECL", "kBEGIN", "kEND",
  "WRITE", "READ", "RETURN", "IF", "THEN", "ELSE", "ENDIF", "WHILE", "DO",
  "ENDWHILE", "BREAK", "CONTINUE", "SEMICOLON", "COMMA", "LPAREN",
  "RPAREN", "LBRACE", "RBRACE", "LSQBR", "RSQBR", "ASSIGN", "ADDRESS_OF",
  "MUL", "TYPE_KW", "ENDTYPE", "DOT", "ALLOC", "FREE_KW", "INITIALIZE",
  "NULLVAL", "CLASS", "ENDCLASS", "NEW_KW", "DELETE_KW", "EXTENDS", "OR",
  "AND", "NOT", "PLUS", "MINUS", "DIV", "LT", "LE", "GT", "GE", "EQ", "NE",
  "UNARY", "$accept", "Program", "$@1", "ClassDefBlock", "ClassDeflist",
  "ClassDef", "$@2", "$@3", "ClassMemberDecList", "ClassMemberDec",
  "MethodDefList", "MethodDef", "$@4", "$@5", "TypeDefBlock",
  "TypeDefList", "TypeDef", "$@6", "FieldDecList", "FieldDec",
  "GDeclarations", "GDecList", "GDecl", "GidList", "Gid", "Type",
  "ParamList", "Param", "FdefBlock", "Fdef", "$@7", "$@8", "LdeclBlock",
  "LDecList", "LDecl", "IdList", "MainBlock", "$@9", "Body", "Slist",
  "Stmt", "InputStmt", "OutputStmt", "FreeStmt", "DeleteStmt", "InitStmt",
  "AssgStmt", "LValue", "FieldAccess", "IfStmt", "WhileStmt", "BreakStmt",
  "ContinueStmt", "E", "ArgList", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-145)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  ((Yyn) == YYTABLE_NINF)

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -32,    24,    36,     9,  -145,    14,  -145,  -145,    -1,  -145,
      26,  -145,  -145,    32,  -145,    10,  -145,    86,   108,   101,
      72,  -145,  -145,    22,  -145,  -145,  -145,  -145,   108,    93,
    -145,   104,  -145,   111,  -145,   119,  -145,   121,   400,  -145,
    -145,  -145,   117,   177,   108,  -145,  -145,   100,   130,  -145,
     125,   173,  -145,  -145,  -145,   213,   143,  -145,   220,    12,
     214,  -145,   121,  -145,   182,   108,   108,  -145,    42,  -145,
     222,    91,  -145,   198,  -145,   219,   201,   159,   207,  -145,
     230,  -145,   238,  -145,   108,  -145,  -145,   224,  -145,   106,
     108,  -145,  -145,   229,   232,   153,  -145,   239,   242,  -145,
     289,   363,  -145,   258,   276,   276,   270,  -145,  -145,   156,
    -145,   389,   294,   294,   276,   277,  -145,  -145,   304,   394,
    -145,   274,   280,   283,   294,   276,   287,  -145,   147,  -145,
    -145,   -22,   279,  -145,   291,   295,   197,   299,   303,  -145,
    -145,   318,   305,   306,   313,   288,   323,  -145,  -145,  -145,
    -145,  -145,  -145,   298,   309,  -145,  -145,  -145,  -145,  -145,
    -145,   324,   294,   276,  -145,   340,   197,   350,   355,   197,
      21,  -145,    39,  -145,   326,   197,   358,   197,  -145,   197,
     327,   521,   197,   197,   334,   200,   344,   200,  -145,   349,
    -145,    71,   375,  -145,   351,   294,  -145,   469,  -145,  -145,
     385,    33,   376,    40,     3,   197,   377,   384,   397,  -145,
    -145,   536,   386,   197,   197,   197,   197,   197,   197,   197,
     197,   197,   197,   197,   197,   429,   441,   197,   360,  -145,
     374,  -145,   381,   382,   521,  -145,  -145,   387,  -145,  -145,
    -145,   197,   390,  -145,  -145,   521,   189,   481,   388,   392,
    -145,   395,   206,   496,   536,   546,   546,   206,   404,   404,
     404,   404,   404,   404,   406,   391,   521,  -145,  -145,   393,
     411,  -145,   509,  -145,   197,  -145,  -145,   133,   184,   193,
     370,   370,  -145,   398,   399,   521,  -145,   241,  -145,   246,
    -145,   252,   235,   322,  -145,  -145,  -145,  -145,  -145,   370,
    -145,  -145,   336,  -145
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
      26,     0,     0,     6,    29,     0,    28,     1,     0,     2,
       0,    25,    27,     9,     5,     0,     8,    36,     0,     0,
       0,     4,     7,     0,    54,    49,    46,    47,     0,     0,
      32,     0,    11,     0,    35,     0,    38,     0,     0,    48,
      30,    31,     0,     0,     0,    34,    37,    42,     0,    41,
      46,     0,    53,     3,    33,     0,     0,    14,     0,     0,
       0,    39,     0,    67,     0,     0,    20,    13,     0,    45,
       0,     0,    51,     0,    40,     0,     0,     0,     0,    19,
       0,    15,     0,    52,     0,    44,    43,     0,    57,     0,
      20,    10,    18,     0,     0,     0,    50,     0,     0,    55,
       0,     0,    17,     0,    61,    61,     0,    12,    23,     0,
      16,     0,     0,     0,    61,     0,    21,    60,     0,     0,
      63,     0,     0,     0,     0,    61,     0,    66,     0,    59,
      62,    97,     0,    70,     0,     0,    81,     0,     0,   106,
     107,     0,     0,     0,     0,     0,     0,    73,    74,    82,
      84,    83,    75,     0,    99,    76,    77,    78,    79,    68,
      58,     0,     0,    61,    64,     0,     0,     0,     0,     0,
       0,   121,   124,   122,   132,     0,     0,     0,   123,     0,
     131,    80,     0,     0,     0,     0,     0,     0,    69,     0,
      72,     0,     0,    56,     0,     0,    65,     0,   100,   102,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   128,
     127,   120,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    92,
       0,    71,     0,     0,    93,   101,    24,     0,    98,    89,
      85,     0,     0,    88,   126,   140,     0,     0,   100,   102,
     129,   101,   110,   119,   118,   108,   109,   111,   112,   115,
     113,   116,   114,   117,     0,     0,    94,    90,    91,     0,
       0,    22,     0,    87,     0,   125,   130,     0,     0,     0,
       0,     0,    95,     0,     0,   139,   136,     0,   134,     0,
     138,     0,     0,     0,    96,    86,   135,   133,   137,     0,
     104,   105,     0,   103
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -145,  -145,  -145,  -145,  -145,   414,  -145,  -145,   366,   -14,
     342,   -65,  -145,  -145,  -145,  -145,   443,  -145,  -145,   437,
    -145,  -145,   432,  -145,   407,    75,   -61,   396,  -145,  -145,
    -145,  -145,  -103,  -145,   352,  -145,  -145,  -145,  -101,  -135,
    -144,  -145,  -145,  -145,  -145,  -145,  -145,    98,  -121,  -145,
    -145,  -145,  -145,  -132,   -86
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     2,    17,     9,    15,    16,    20,    43,    56,    57,
      78,    79,   126,   115,     3,     5,     6,    10,    29,    30,
      24,    35,    36,    48,    49,    70,    71,    72,    38,    52,
     106,    98,   112,   119,   120,   128,    53,    75,   122,   145,
     146,   147,   148,   149,   150,   151,   152,   153,   180,   155,
     156,   157,   158,   245,   246
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     154,   189,   113,    13,   181,     1,   171,   172,   173,   174,
     166,   124,   123,    92,    13,    89,    25,   167,     4,    26,
      27,    95,   162,   161,   154,   201,    25,   132,     4,    26,
      27,   175,   244,    34,   197,    92,     7,   200,   176,   177,
     109,    69,    67,   208,    14,   210,   178,   211,    28,   203,
     225,   226,    11,     8,   179,    21,    18,   202,    28,   234,
     195,   194,   240,    67,   154,   241,   154,   204,    81,   243,
      82,   205,   167,   247,   171,   172,   173,   174,   206,   192,
      19,   252,   253,   254,   255,   256,   257,   258,   259,   260,
     261,   262,   263,    31,   237,   266,    23,    25,    37,   175,
      26,    27,    33,    39,    31,    32,   176,   177,    42,   272,
      37,   232,    25,    51,   178,    26,    27,   233,    84,    58,
      85,    44,   179,    25,    40,    47,    26,    27,    59,    28,
      45,    58,    60,    84,    63,    99,   171,   172,   173,   174,
      58,    80,   285,    54,    28,   292,   293,    25,   189,   189,
      26,    27,    58,    80,    66,    28,    61,    62,   189,   154,
     154,   175,   286,    25,   302,    80,    26,    27,   176,   177,
      90,   154,   154,   164,   165,    80,   178,    64,   154,    28,
      84,   154,   103,    84,   179,   116,   118,   171,   172,   173,
     174,   287,   289,   291,   118,    28,   171,   172,   173,   174,
     171,   172,   173,   174,   131,    25,   132,    55,    26,    27,
      76,    25,   175,   288,    26,    27,   274,    73,   275,   176,
     177,   175,   290,    65,    68,   175,    83,   178,   176,   177,
      88,    86,   176,   177,    93,   179,   178,    28,    91,   131,
     178,   132,    25,    28,   179,    26,    27,    87,   179,   134,
     135,   136,   137,    97,   299,   300,   138,   101,   102,   139,
     140,   219,   220,   221,   222,   223,   224,    94,   274,   104,
     296,   141,   105,   274,    28,   297,   142,   143,   131,   274,
     132,   298,   144,   228,   110,   230,   111,   133,   134,   135,
     136,   137,   131,    25,   132,   138,    26,    27,   139,   140,
     114,   188,   134,   135,   136,   137,   121,   125,   127,   138,
     141,   159,   139,   140,   160,   142,   143,   163,   168,   169,
     107,   144,   184,   170,   141,    28,   131,   182,   132,   142,
     143,   183,   191,   185,   186,   144,   134,   135,   136,   137,
     131,   187,   132,   138,   196,   301,   139,   140,   192,   190,
     134,   135,   136,   137,   198,   193,   303,   138,   141,   199,
     139,   140,   209,   142,   143,   207,   212,    25,   227,   144,
      26,    27,   141,   229,   131,   231,   132,   142,   143,   235,
     242,   248,   236,   144,   134,   135,   136,   137,   249,   267,
     251,   138,   108,    25,   139,   140,    26,    27,    25,    28,
     117,    26,    27,   268,    25,   129,   141,    50,    27,   269,
     270,   142,   143,   281,   239,   283,   277,   144,   271,   273,
     278,   213,   282,   279,   280,    28,   250,   294,   295,    22,
      28,    77,   100,   213,   214,   215,    28,   216,   217,   218,
     219,   220,   221,   222,   223,   224,   214,   215,    12,   216,
     217,   218,   219,   220,   221,   222,   223,   224,   264,    -1,
      -1,    -1,    -1,    -1,    -1,   213,    41,    46,     0,    74,
     265,   130,     0,     0,     0,     0,     0,   213,   214,   215,
      96,   216,   217,   218,   219,   220,   221,   222,   223,   224,
     214,   215,     0,   216,   217,   218,   219,   220,   221,   222,
     223,   224,   238,     0,     0,   213,     0,     0,     0,     0,
       0,     0,     0,     0,   276,     0,     0,   213,   214,   215,
       0,   216,   217,   218,   219,   220,   221,   222,   223,   224,
     214,   215,   213,   216,   217,   218,   219,   220,   221,   222,
     223,   224,   284,     0,     0,   213,   215,     0,   216,   217,
     218,   219,   220,   221,   222,   223,   224,   213,   214,   215,
       0,   216,   217,   218,   219,   220,   221,   222,   223,   224,
     214,   215,   213,   216,   217,   218,   219,   220,   221,   222,
     223,   224,   213,     0,     0,     0,     0,     0,   216,   217,
     218,   219,   220,   221,   222,   223,   224,     0,     0,     0,
     218,   219,   220,   221,   222,   223,   224
};

static const yytype_int16 yycheck[] =
{
     121,   145,   105,     4,   136,    37,     3,     4,     5,     6,
      32,   114,   113,    78,     4,    76,     4,    39,     4,     7,
       8,    82,   125,   124,   145,     4,     4,     6,     4,     7,
       8,    28,    29,    11,   166,   100,     0,   169,    35,    36,
     101,    29,    56,   175,    45,   177,    43,   179,    36,   170,
     182,   183,    38,    44,    51,    45,    30,    36,    36,   191,
     163,   162,    29,    77,   185,    32,   187,    28,    26,    29,
      28,    32,    39,   205,     3,     4,     5,     6,    39,    39,
      48,   213,   214,   215,   216,   217,   218,   219,   220,   221,
     222,   223,   224,    18,   195,   227,    10,     4,    23,    28,
       7,     8,    30,    28,    29,     4,    35,    36,     4,   241,
      35,    40,     4,    38,    43,     7,     8,    46,    27,    44,
      29,    10,    51,     4,    31,     4,     7,     8,    28,    36,
      11,    56,    32,    27,     9,    29,     3,     4,     5,     6,
      65,    66,   274,    26,    36,   280,   281,     4,   292,   293,
       7,     8,    77,    78,    11,    36,    26,    27,   302,   280,
     281,    28,    29,     4,   299,    90,     7,     8,    35,    36,
      11,   292,   293,    26,    27,   100,    43,     4,   299,    36,
      27,   302,    29,    27,    51,    29,   111,     3,     4,     5,
       6,   277,   278,   279,   119,    36,     3,     4,     5,     6,
       3,     4,     5,     6,     4,     4,     6,    30,     7,     8,
      28,     4,    28,    29,     7,     8,    27,     3,    29,    35,
      36,    28,    29,    10,     4,    28,     4,    43,    35,    36,
      29,    33,    35,    36,     4,    51,    43,    36,    31,     4,
      43,     6,     4,    36,    51,     7,     8,    28,    51,    14,
      15,    16,    17,    29,    19,    20,    21,    28,    26,    24,
      25,    55,    56,    57,    58,    59,    60,    29,    27,    30,
      29,    36,    30,    27,    36,    29,    41,    42,     4,    27,
       6,    29,    47,   185,    26,   187,    10,    13,    14,    15,
      16,    17,     4,     4,     6,    21,     7,     8,    24,    25,
      30,    13,    14,    15,    16,    17,    12,    30,     4,    21,
      36,    31,    24,    25,    31,    41,    42,    30,    39,    28,
      31,    47,     4,    28,    36,    36,     4,    28,     6,    41,
      42,    28,    34,    28,    28,    47,    14,    15,    16,    17,
       4,    28,     6,    21,     4,    23,    24,    25,    39,    26,
      14,    15,    16,    17,     4,    31,    20,    21,    36,     4,
      24,    25,     4,    41,    42,    39,    39,     4,    34,    47,
       7,     8,    36,    29,     4,    26,     6,    41,    42,     4,
       4,     4,    31,    47,    14,    15,    16,    17,     4,    29,
       4,    21,    29,     4,    24,    25,     7,     8,     4,    36,
      11,     7,     8,    29,     4,    11,    36,     7,     8,    28,
      28,    41,    42,    22,    29,     4,    28,    47,    31,    29,
      28,    36,    29,    28,    18,    36,    29,    29,    29,    15,
      36,    65,    90,    36,    49,    50,    36,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    49,    50,     5,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    29,    55,
      56,    57,    58,    59,    60,    36,    29,    35,    -1,    62,
      29,   119,    -1,    -1,    -1,    -1,    -1,    36,    49,    50,
      84,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      49,    50,    -1,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    33,    -1,    -1,    36,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    33,    -1,    -1,    36,    49,    50,
      -1,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      49,    50,    36,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    33,    -1,    -1,    36,    50,    -1,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    36,    49,    50,
      -1,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      49,    50,    36,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    36,    -1,    -1,    -1,    -1,    -1,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    -1,    -1,    -1,
      54,    55,    56,    57,    58,    59,    60
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    37,    63,    76,     4,    77,    78,     0,    44,    65,
      79,    38,    78,     4,    45,    66,    67,    64,    30,    48,
      68,    45,    67,    10,    82,     4,     7,     8,    36,    80,
      81,    87,     4,    30,    11,    83,    84,    87,    90,    87,
      31,    81,     4,    69,    10,    11,    84,     4,    85,    86,
       7,    87,    91,    98,    26,    30,    70,    71,    87,    28,
      32,    26,    27,     9,     4,    10,    11,    71,     4,    29,
      87,    88,    89,     3,    86,    99,    28,    70,    72,    73,
      87,    26,    28,     4,    27,    29,    33,    28,    29,    88,
      11,    31,    73,     4,    29,    88,    89,    29,    93,    29,
      72,    28,    26,    29,    30,    30,    92,    31,    29,    88,
      26,    10,    94,    94,    30,    75,    29,    11,    87,    95,
      96,    12,   100,   100,    94,    30,    74,     4,    97,    11,
      96,     4,     6,    13,    14,    15,    16,    17,    21,    24,
      25,    36,    41,    42,    47,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,    31,
      31,   100,    94,    30,    26,    27,    32,    39,    39,    28,
      28,     3,     4,     5,     6,    28,    35,    36,    43,    51,
     110,   115,    28,    28,     4,    28,    28,    28,    13,   102,
      26,    34,    39,    31,   100,    94,     4,   115,     4,     4,
     115,     4,    36,   110,    28,    32,    39,    39,   115,     4,
     115,   115,    39,    36,    49,    50,    52,    53,    54,    55,
      56,    57,    58,    59,    60,   115,   115,    34,   109,    29,
     109,    26,    40,    46,   115,     4,    31,   100,    33,    29,
      29,    32,     4,    29,    29,   115,   116,   115,     4,     4,
      29,     4,   115,   115,   115,   115,   115,   115,   115,   115,
     115,   115,   115,   115,    29,    29,   115,    29,    29,    28,
      28,    31,   115,    29,    27,    29,    33,    28,    28,    28,
      18,    22,    29,     4,    33,   115,    29,   116,    29,   116,
      29,   116,   101,   101,    29,    29,    29,    29,    29,    19,
      20,    23,   101,    20
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    62,    64,    63,    65,    65,    65,    66,    66,    68,
      67,    69,    67,    70,    70,    71,    71,    71,    72,    72,
      72,    74,    73,    75,    73,    76,    76,    77,    77,    79,
      78,    80,    80,    81,    82,    82,    82,    83,    83,    84,
      85,    85,    86,    86,    86,    86,    87,    87,    87,    87,
      88,    88,    89,    90,    90,    92,    91,    93,    91,    94,
      94,    94,    95,    95,    96,    97,    97,    99,    98,   100,
     100,   101,   101,   102,   102,   102,   102,   102,   102,   102,
     102,   102,   102,   102,   102,   103,   103,   103,   103,   104,
     105,   106,   107,   108,   108,   108,   108,   109,   109,   109,
     110,   110,   110,   111,   111,   112,   113,   114,   115,   115,
     115,   115,   115,   115,   115,   115,   115,   115,   115,   115,
     115,   115,   115,   115,   115,   115,   115,   115,   115,   115,
     115,   115,   115,   115,   115,   115,   115,   115,   115,   116,
     116
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     6,     3,     2,     0,     2,     1,     0,
       8,     0,    10,     2,     1,     3,     6,     5,     2,     1,
       0,     0,    10,     0,     9,     3,     0,     2,     1,     0,
       5,     2,     1,     3,     3,     2,     0,     2,     1,     3,
       3,     1,     1,     4,     4,     3,     1,     1,     2,     1,
       3,     1,     2,     2,     0,     0,    10,     0,     9,     3,
       2,     0,     2,     1,     3,     3,     1,     0,     9,     3,
       2,     3,     2,     1,     1,     1,     1,     1,     1,     1,
       2,     1,     1,     1,     1,     4,     7,     5,     4,     4,
       4,     4,     3,     3,     4,     5,     6,     1,     4,     1,
       3,     3,     3,     9,     7,     7,     1,     1,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       2,     1,     1,     1,     1,     4,     3,     2,     2,     3,
       4,     1,     1,     6,     5,     6,     5,     6,     5,     3,
       1
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
  case 2: /* $@1: %empty  */
#line 72 "task1.y"
  {
    int numClasses = 0;
    ClassTableEntry *cc = classTableHead;
    while (cc) 
    { 
      numClasses++; 
      cc = cc->next; 
    }
    if (numClasses > 0)
      advanceNextBinding(numClasses * 8);
  }
#line 1662 "y.tab.c"
    break;

  case 3: /* Program: TypeDefBlock ClassDefBlock $@1 GDeclarations FdefBlock MainBlock  */
#line 83 "task1.y"
                                    { root = (yyvsp[0].node); }
#line 1668 "y.tab.c"
    break;

  case 4: /* ClassDefBlock: CLASS ClassDeflist ENDCLASS  */
#line 87 "task1.y"
                              { printClassTable(); }
#line 1674 "y.tab.c"
    break;

  case 9: /* $@2: %empty  */
#line 98 "task1.y"
  {
    currentClassEntry = installClass((yyvsp[0].node)->varname, NULL);
    currentUdefType = currentClassEntry->type;
  }
#line 1683 "y.tab.c"
    break;

  case 10: /* ClassDef: ID $@2 LBRACE DECL ClassMemberDecList ENDDECL MethodDefList RBRACE  */
#line 103 "task1.y"
  {
    if (currentClassEntry)
    {
      printf("\n--- Class '%s' definition complete ---\n", currentClassEntry->name);
      // printClassTable();
    }
    currentClassEntry = NULL;
    currentUdefType = NULL;
  }
#line 1697 "y.tab.c"
    break;

  case 11: /* $@3: %empty  */
#line 113 "task1.y"
  {
    currentClassEntry = installClass((yyvsp[-2].node)->varname, (yyvsp[0].node)->varname);
    currentUdefType = currentClassEntry->type;
  }
#line 1706 "y.tab.c"
    break;

  case 12: /* ClassDef: ID EXTENDS ID $@3 LBRACE DECL ClassMemberDecList ENDDECL MethodDefList RBRACE  */
#line 118 "task1.y"
  {
    if (currentClassEntry)
    {
      printf("\n--- Class '%s' definition complete ---\n", currentClassEntry->name);
      // printClassTable();
    }
    currentClassEntry = NULL;
    currentUdefType = NULL;
  }
#line 1720 "y.tab.c"
    break;

  case 15: /* ClassMemberDec: Type ID SEMICOLON  */
#line 136 "task1.y"
  {
    if(!currentClassEntry)
    {
      fprintf(stderr, "Error: handleClassFieldDec called outside a class definition\n");
      exit(1);  
    }

    TypeTableEntry *t;
    if((yyvsp[-2].typeData).type == TYPE_USERDEF)
    {
      t = (yyvsp[-2].typeData).typeEntry;
    }
    else
    {
      if((yyvsp[-2].typeData).type == TYPE_INT)
      {
        t = lookupType("int");
      }
      if((yyvsp[-2].typeData).type == TYPE_STRING)
      {
        t = lookupType("string");
      }
      if((yyvsp[-2].typeData).type == TYPE_BOOL)
      {
        t = lookupType("bool");
      }
    }
    
    addField(currentClassEntry->type, (yyvsp[-1].node)->varname, t);
  }
#line 1755 "y.tab.c"
    break;

  case 16: /* ClassMemberDec: Type ID LPAREN ParamList RPAREN SEMICOLON  */
#line 167 "task1.y"
  {
    if(!currentClassEntry)
    {
      fprintf(stderr, "Error: handleMethodDec called outside a class definition\n");
      exit(1);
    }
    addMethod(currentClassEntry, (yyvsp[-4].node)->varname, (yyvsp[-5].typeData).type, (yyvsp[-5].typeData).typeEntry, (yyvsp[-2].param));
  }
#line 1768 "y.tab.c"
    break;

  case 17: /* ClassMemberDec: Type ID LPAREN RPAREN SEMICOLON  */
#line 176 "task1.y"
  {
    if(!currentClassEntry)
    {
      fprintf(stderr, "Error: handleMethodDec called outside a class definition\n");
      exit(1);
    }
    addMethod(currentClassEntry, (yyvsp[-3].node)->varname, (yyvsp[-4].typeData).type, (yyvsp[-4].typeData).typeEntry, NULL);
  }
#line 1781 "y.tab.c"
    break;

  case 21: /* $@4: %empty  */
#line 261 "task1.y"
  {
    // set current function name
    current_function_name = (yyvsp[-3].node)->varname;

    if(currentClassEntry)
    {
      InstallParamsToLSTMethod((yyvsp[-1].param), currentClassEntry->type);
    }
  }
#line 1795 "y.tab.c"
    break;

  case 22: /* MethodDef: Type ID LPAREN ParamList RPAREN $@4 LBRACE LdeclBlock Body RBRACE  */
#line 271 "task1.y"
  { 
    struct TypeInfo retType = (yyvsp[-9].typeData);
    
    verifyMethodSignature(currentClassEntry, (yyvsp[-8].node)->varname, &retType, (yyvsp[-6].param));

    handleFdefPrint((yyvsp[-8].node)->varname, (yyvsp[-1].node));
    
    Gsymbol *method = malloc(sizeof(Gsymbol));
    method->name = strdup((yyvsp[-8].node)->varname);
    MethodEntry *MethodEntry = lookupMethod(currentClassEntry, method->name);
    method->flabel = MethodEntry->flabel;
    
    /*
    fprintf(interim_file, "F%d:\n", g->flabel);
    fprintf(interim_file, "PUSH BP\n");
    fprintf(interim_file, "MOV BP, SP\n");

    locAlloc(interim_file);
    */

    codeGen((yyvsp[-1].node), interim_file, method);

    // clear current function name
    current_function_name = NULL;

    selfClassEntry = NULL;

    // now it is expected that all functions have a return statement(empty or not)
    resetLocalSymbolTable();
  }
#line 1830 "y.tab.c"
    break;

  case 23: /* $@5: %empty  */
#line 302 "task1.y"
  {
    // set current function name
    current_function_name = (yyvsp[-2].node)->varname;
    
    if(currentClassEntry)
    {
      InstallParamsToLSTMethod(NULL, currentClassEntry->type); // to install self in LST
    }
  }
#line 1844 "y.tab.c"
    break;

  case 24: /* MethodDef: Type ID LPAREN RPAREN $@5 LBRACE LdeclBlock Body RBRACE  */
#line 312 "task1.y"
  {
    struct TypeInfo retType = (yyvsp[-8].typeData);
    Paramstruct *p = malloc(sizeof(Paramstruct));
    p->next = NULL;
    p->type = TYPE_NULL;
    verifyMethodSignature(currentClassEntry, (yyvsp[-7].node)->varname, &retType, p);

    handleFdefPrint((yyvsp[-7].node)->varname, (yyvsp[-1].node));

    Gsymbol *method = malloc(sizeof(Gsymbol));
    method->name = strdup((yyvsp[-7].node)->varname);
    MethodEntry *MethodEntry = lookupMethod(currentClassEntry, method->name);
    method->flabel = MethodEntry->flabel;
    /*
    fprintf(interim_file, "F%d:\n", g->flabel);
    fprintf(interim_file, "PUSH BP\n");
    fprintf(interim_file, "MOV BP, SP\n");

    locAlloc(interim_file);
    */

    codeGen((yyvsp[-1].node), interim_file, method);

    // clear current function name
    current_function_name = NULL;

    selfClassEntry = NULL;

    // now it is expected that all functions have a return statement(empty or not)
    resetLocalSymbolTable();
  }
#line 1880 "y.tab.c"
    break;

  case 25: /* TypeDefBlock: TYPE_KW TypeDefList ENDTYPE  */
#line 348 "task1.y"
  {
    printTypeTable();
  }
#line 1888 "y.tab.c"
    break;

  case 29: /* $@6: %empty  */
#line 361 "task1.y"
  {
    currentUdefType = installType((yyvsp[0].node)->varname);
  }
#line 1896 "y.tab.c"
    break;

  case 30: /* TypeDef: ID $@6 LBRACE FieldDecList RBRACE  */
#line 365 "task1.y"
  {
    currentUdefType = NULL; // end of type definition
  }
#line 1904 "y.tab.c"
    break;

  case 33: /* FieldDec: Type ID SEMICOLON  */
#line 377 "task1.y"
  {
    TypeTableEntry *t;
    if((yyvsp[-2].typeData).type == TYPE_USERDEF)
    {
      t = (yyvsp[-2].typeData).typeEntry;
    }
    else
    {
      if((yyvsp[-2].typeData).type == TYPE_INT)
      {
        t = lookupType("int");
      }
      if((yyvsp[-2].typeData).type == TYPE_STRING)
      {
        t = lookupType("string");
      }
      if((yyvsp[-2].typeData).type == TYPE_BOOL)
      {
        t = lookupType("bool");
      }
    }
    if(!t)
    {
      yyerror("Unknown field type");
      exit(1);
    }
    if(currentUdefType->fieldCount >= MAX_FIELDS_IN_USER_TYPE)
    {
      yyerror("Maximum fields in user type exceeded");
      exit(1);
    }

    addField(currentUdefType, (yyvsp[-1].node)->varname, t);
  }
#line 1943 "y.tab.c"
    break;

  case 34: /* GDeclarations: DECL GDecList ENDDECL  */
#line 422 "task1.y"
  { 
    handleGdecComplete(); 
  }
#line 1951 "y.tab.c"
    break;

  case 42: /* Gid: ID  */
#line 445 "task1.y"
  { 
    // printf("current type: %d\ncurrent var:%s\n", currentTypeData.type, $1->varname);
    handleGidScalar((yyvsp[0].node), &currentTypeData); 
  }
#line 1960 "y.tab.c"
    break;

  case 43: /* Gid: ID LSQBR NUM RSQBR  */
#line 450 "task1.y"
  { 
    handleGidArray1D((yyvsp[-3].node), &currentTypeData, (yyvsp[-1].node)->val); 
  }
#line 1968 "y.tab.c"
    break;

  case 44: /* Gid: ID LPAREN ParamList RPAREN  */
#line 454 "task1.y"
  { 
    struct TypeInfo funcType = (yyvsp[-4].typeData);
    handleGidFunction((yyvsp[-3].node), &funcType, (yyvsp[-1].param)); 
  }
#line 1977 "y.tab.c"
    break;

  case 45: /* Gid: ID LPAREN RPAREN  */
#line 459 "task1.y"
  { 
    handleGidFunction((yyvsp[-2].node), &currentTypeData, NULL); 
  }
#line 1985 "y.tab.c"
    break;

  case 46: /* Type: INT  */
#line 465 "task1.y"
      { 
      (yyval.typeData).type = TYPE_INT; (yyval.typeData).ptrLevel = 0; 
      currentTypeData = (yyval.typeData); 
  }
#line 1994 "y.tab.c"
    break;

  case 47: /* Type: STR  */
#line 469 "task1.y"
        { 
      (yyval.typeData).type = TYPE_STRING; (yyval.typeData).ptrLevel = 0; 
      currentTypeData = (yyval.typeData); 
  }
#line 2003 "y.tab.c"
    break;

  case 48: /* Type: MUL Type  */
#line 473 "task1.y"
             { 
      (yyval.typeData) = (yyvsp[0].typeData); (yyval.typeData).ptrLevel++; 
      currentTypeData = (yyval.typeData); 
  }
#line 2012 "y.tab.c"
    break;

  case 49: /* Type: ID  */
#line 477 "task1.y"
       {
      TypeTableEntry *t = lookupType((yyvsp[0].node)->varname);
      if(!t || t->typeId < TYPE_USERDEF || lookupClass((yyvsp[0].node)->varname))
      {
        ClassTableEntry *c = lookupClass((yyvsp[0].node)->varname);
        if(!c)
        {
          yyerror("Undefined type name");
          exit(1);
        }
        t = c->type;
        (yyval.typeData).type = TYPE_CLASS;
        (yyval.typeData).typeEntry = t;
        (yyval.typeData).ptrLevel = 0;
        currentTypeData = (yyval.typeData);
      }
      else
      {
        (yyval.typeData).type = TYPE_USERDEF;
        (yyval.typeData).typeEntry = t;
        (yyval.typeData).ptrLevel = 0;
        currentTypeData = (yyval.typeData);
      }
  }
#line 2041 "y.tab.c"
    break;

  case 50: /* ParamList: ParamList COMMA Param  */
#line 504 "task1.y"
                        { (yyval.param) = AppendParam((yyvsp[-2].param), (yyvsp[0].param)); }
#line 2047 "y.tab.c"
    break;

  case 51: /* ParamList: Param  */
#line 505 "task1.y"
          { (yyval.param) = (yyvsp[0].param); }
#line 2053 "y.tab.c"
    break;

  case 52: /* Param: Type ID  */
#line 509 "task1.y"
          { (yyval.param) = CreateParam((yyvsp[0].node)->varname, (yyvsp[-1].typeData).type, (yyvsp[-1].typeData).typeEntry, (yyvsp[-1].typeData).ptrLevel); }
#line 2059 "y.tab.c"
    break;

  case 55: /* $@7: %empty  */
#line 519 "task1.y"
  {
    // set current function name
    current_function_name = (yyvsp[-3].node)->varname;

    if(lookupMethod(currentClassEntry, current_function_name))
    {
      selfClassEntry = currentClassEntry;
    }
    else
    {
      selfClassEntry = findClassForMethod((yyvsp[-3].node)->varname);
    }
    if(selfClassEntry)
    {
      InstallParamsToLSTMethod((yyvsp[-1].param), selfClassEntry->type);
    }
    else
    {
      InstallParamsToLST((yyvsp[-1].param));
    }
  }
#line 2085 "y.tab.c"
    break;

  case 56: /* Fdef: Type ID LPAREN ParamList RPAREN $@7 LBRACE LdeclBlock Body RBRACE  */
#line 541 "task1.y"
  { 
    struct TypeInfo retType = (yyvsp[-9].typeData);
    verifyFunctionSignature(Lookup((yyvsp[-8].node)->varname), &retType, (yyvsp[-6].param));
    handleFdefPrint((yyvsp[-8].node)->varname, (yyvsp[-1].node));

    struct Gsymbol* g = Lookup((yyvsp[-8].node)->varname);
    /*
    fprintf(interim_file, "F%d:\n", g->flabel);
    fprintf(interim_file, "PUSH BP\n");
    fprintf(interim_file, "MOV BP, SP\n");

    locAlloc(interim_file);
    */

    codeGen((yyvsp[-1].node), interim_file, g);

    // clear current function name
    current_function_name = NULL;

    selfClassEntry = NULL;

    // now it is expected that all functions have a return statement(empty or not)
    resetLocalSymbolTable();
  }
#line 2114 "y.tab.c"
    break;

  case 57: /* $@8: %empty  */
#line 566 "task1.y"
  {
    // set current function name
    current_function_name = (yyvsp[-2].node)->varname;
    if(lookupMethod(currentClassEntry, current_function_name))
    {
      selfClassEntry = currentClassEntry;
    }
    else
    {
      selfClassEntry = findClassForMethod((yyvsp[-2].node)->varname);
    }
    if(selfClassEntry)
    {
      InstallParamsToLSTMethod(NULL, selfClassEntry->type); // to install self in LST
    }
    else
    {
      printf("Function %s is not a method\n", (yyvsp[-2].node)->varname);
      exit(1);
    }
    printf("code reached here\n");
  }
#line 2141 "y.tab.c"
    break;

  case 58: /* Fdef: Type ID LPAREN RPAREN $@8 LBRACE LdeclBlock Body RBRACE  */
#line 589 "task1.y"
  {
    struct TypeInfo retType = (yyvsp[-8].typeData);
    Paramstruct *p = malloc(sizeof(Paramstruct));
    p->next = NULL;
    p->type = TYPE_NULL;
    verifyFunctionSignature(Lookup((yyvsp[-7].node)->varname), &retType, p);
    handleFdefNoArgsPrint((yyvsp[-7].node)->varname, (yyvsp[-1].node)); 

    struct Gsymbol* g = Lookup((yyvsp[-7].node)->varname);
    /*
    fprintf(interim_file, "F%d:\n", g->flabel);
    fprintf(interim_file, "PUSH BP\n");
    fprintf(interim_file, "MOV BP, SP\n");

    locAlloc(interim_file);
    */

    codeGen((yyvsp[-1].node), interim_file, g);

    // clear current function name
    current_function_name = NULL;

    selfClassEntry = NULL;

    // now it is expected that all functions have a return statement(empty or not)
    resetLocalSymbolTable();
  }
#line 2173 "y.tab.c"
    break;

  case 65: /* IdList: IdList COMMA ID  */
#line 635 "task1.y"
  { 
    // Uses the global currentTypeData
    handleLidInstall((yyvsp[0].node)->varname, &currentTypeData); 
  }
#line 2182 "y.tab.c"
    break;

  case 66: /* IdList: ID  */
#line 640 "task1.y"
  { 
    handleLidInstall((yyvsp[0].node)->varname, &currentTypeData); 
  }
#line 2190 "y.tab.c"
    break;

  case 67: /* $@9: %empty  */
#line 647 "task1.y"
  {
    current_function_name = "MAIN";
  }
#line 2198 "y.tab.c"
    break;

  case 68: /* MainBlock: INT MAIN $@9 LPAREN RPAREN LBRACE LdeclBlock Body RBRACE  */
#line 651 "task1.y"
  { 
    handleMainPrint((yyvsp[-1].node)); 
    (yyval.node) = (yyvsp[-1].node); 

    /*
    fprintf(interim_file, "MAIN:\n");
    moveStackPointer(interim_file);
    fprintf(interim_file, "BRKP\n");
    fprintf(interim_file, "PUSH BP\n");
    fprintf(interim_file, "MOV BP, SP\n");
    
    locAlloc(interim_file);
    */

    struct Gsymbol* main_func = malloc(sizeof(struct Gsymbol));
    main_func->name = "MAIN";
    
    codeGen((yyval.node), interim_file, main_func);

    // clear current function name
    current_function_name = NULL;

    // now it is expected that all functions have a return statement(empty or not)
    resetLocalSymbolTable();
  }
#line 2228 "y.tab.c"
    break;

  case 69: /* Body: kBEGIN Slist kEND  */
#line 679 "task1.y"
                    { (yyval.node) = (yyvsp[-1].node); }
#line 2234 "y.tab.c"
    break;

  case 70: /* Body: kBEGIN kEND  */
#line 680 "task1.y"
                { (yyval.node) = NULL; }
#line 2240 "y.tab.c"
    break;

  case 71: /* Slist: Slist Stmt SEMICOLON  */
#line 684 "task1.y"
                       { (yyval.node) = makeConnectorNode((yyvsp[-2].node), (yyvsp[-1].node)); }
#line 2246 "y.tab.c"
    break;

  case 72: /* Slist: Stmt SEMICOLON  */
#line 685 "task1.y"
                   { (yyval.node) = (yyvsp[-1].node); }
#line 2252 "y.tab.c"
    break;

  case 73: /* Stmt: InputStmt  */
#line 689 "task1.y"
            { (yyval.node) = (yyvsp[0].node); }
#line 2258 "y.tab.c"
    break;

  case 74: /* Stmt: OutputStmt  */
#line 690 "task1.y"
               { (yyval.node) = (yyvsp[0].node); }
#line 2264 "y.tab.c"
    break;

  case 75: /* Stmt: AssgStmt  */
#line 691 "task1.y"
             { (yyval.node) = (yyvsp[0].node); }
#line 2270 "y.tab.c"
    break;

  case 76: /* Stmt: IfStmt  */
#line 692 "task1.y"
           { (yyval.node) = (yyvsp[0].node); }
#line 2276 "y.tab.c"
    break;

  case 77: /* Stmt: WhileStmt  */
#line 693 "task1.y"
              { (yyval.node) = (yyvsp[0].node); }
#line 2282 "y.tab.c"
    break;

  case 78: /* Stmt: BreakStmt  */
#line 694 "task1.y"
              { (yyval.node) = (yyvsp[0].node); }
#line 2288 "y.tab.c"
    break;

  case 79: /* Stmt: ContinueStmt  */
#line 695 "task1.y"
                 { (yyval.node) = (yyvsp[0].node); }
#line 2294 "y.tab.c"
    break;

  case 80: /* Stmt: RETURN E  */
#line 696 "task1.y"
             { (yyval.node) = makeReturnNode((yyvsp[0].node), current_function_name); }
#line 2300 "y.tab.c"
    break;

  case 81: /* Stmt: RETURN  */
#line 697 "task1.y"
           { (yyval.node) = makeReturnNode(NULL, current_function_name); }
#line 2306 "y.tab.c"
    break;

  case 82: /* Stmt: FreeStmt  */
#line 698 "task1.y"
             { (yyval.node) = (yyvsp[0].node); }
#line 2312 "y.tab.c"
    break;

  case 83: /* Stmt: InitStmt  */
#line 699 "task1.y"
             { (yyval.node) = (yyvsp[0].node); }
#line 2318 "y.tab.c"
    break;

  case 84: /* Stmt: DeleteStmt  */
#line 700 "task1.y"
               { (yyval.node) = (yyvsp[0].node); }
#line 2324 "y.tab.c"
    break;

  case 85: /* InputStmt: READ LPAREN ID RPAREN  */
#line 704 "task1.y"
                        { (yyval.node) = makeReadNode(makeVarNode((yyvsp[-1].node)->varname)); }
#line 2330 "y.tab.c"
    break;

  case 86: /* InputStmt: READ LPAREN ID LSQBR E RSQBR RPAREN  */
#line 705 "task1.y"
                                        { (yyval.node) = makeReadNode(makeArrayNode((yyvsp[-4].node), (yyvsp[-2].node))); }
#line 2336 "y.tab.c"
    break;

  case 87: /* InputStmt: READ LPAREN MUL ID RPAREN  */
#line 707 "task1.y"
  { 
    tnode* ptr_node = makeVarNode((yyvsp[-1].node)->varname);
    (yyval.node) = makeReadNode(makeDerefNode(ptr_node)); 
  }
#line 2345 "y.tab.c"
    break;

  case 88: /* InputStmt: READ LPAREN FieldAccess RPAREN  */
#line 712 "task1.y"
  {
    (yyval.node) = makeReadNode((yyvsp[-1].node));
  }
#line 2353 "y.tab.c"
    break;

  case 89: /* OutputStmt: WRITE LPAREN E RPAREN  */
#line 718 "task1.y"
                        { (yyval.node) = makeWriteNode((yyvsp[-1].node)); }
#line 2359 "y.tab.c"
    break;

  case 90: /* FreeStmt: FREE_KW LPAREN LValue RPAREN  */
#line 723 "task1.y"
  {
    (yyval.node) = makeFreeNode((yyvsp[-1].node));
  }
#line 2367 "y.tab.c"
    break;

  case 91: /* DeleteStmt: DELETE_KW LPAREN LValue RPAREN  */
#line 730 "task1.y"
  {
    (yyval.node) = makeDeleteNode((yyvsp[-1].node));
  }
#line 2375 "y.tab.c"
    break;

  case 92: /* InitStmt: INITIALIZE LPAREN RPAREN  */
#line 737 "task1.y"
  {
    (yyval.node) = makeInitializeNode();
  }
#line 2383 "y.tab.c"
    break;

  case 93: /* AssgStmt: LValue ASSIGN E  */
#line 742 "task1.y"
                  { (yyval.node) = makeAssignNode((yyvsp[-2].node), (yyvsp[0].node)); }
#line 2389 "y.tab.c"
    break;

  case 94: /* AssgStmt: MUL ID ASSIGN E  */
#line 744 "task1.y"
  { 
    tnode* deref = makeDerefNode(makeVarNode((yyvsp[-2].node)->varname));
    (yyval.node) = makeAssignNode(deref, (yyvsp[0].node)); 
  }
#line 2398 "y.tab.c"
    break;

  case 95: /* AssgStmt: LValue ASSIGN ALLOC LPAREN RPAREN  */
#line 749 "task1.y"
  {
    (yyval.node) = makeAssignNode((yyvsp[-4].node), makeAllocNode((yyvsp[-4].node)));
  }
#line 2406 "y.tab.c"
    break;

  case 96: /* AssgStmt: LValue ASSIGN NEW_KW LPAREN ID RPAREN  */
#line 753 "task1.y"
  {
    (yyval.node) = makeAssignNode((yyvsp[-5].node), makeNewNode((yyvsp[-1].node)->varname));
  }
#line 2414 "y.tab.c"
    break;

  case 97: /* LValue: ID  */
#line 760 "task1.y"
  {
    (yyval.node) = makeVarNode((yyvsp[0].node)->varname);
  }
#line 2422 "y.tab.c"
    break;

  case 98: /* LValue: ID LSQBR E RSQBR  */
#line 764 "task1.y"
  {
    (yyval.node) = makeArrayNode((yyvsp[-3].node), (yyvsp[-1].node));
  }
#line 2430 "y.tab.c"
    break;

  case 100: /* FieldAccess: ID DOT ID  */
#line 772 "task1.y"
  {
    tnode *base = makeVarNode((yyvsp[-2].node)->varname);
    (yyval.node) = makeFieldNode(base, (yyvsp[0].node)->varname);
  }
#line 2439 "y.tab.c"
    break;

  case 101: /* FieldAccess: FieldAccess DOT ID  */
#line 777 "task1.y"
  {
    (yyval.node) = makeFieldNode((yyvsp[-2].node), (yyvsp[0].node)->varname);
  }
#line 2447 "y.tab.c"
    break;

  case 102: /* FieldAccess: SELF_KW DOT ID  */
#line 781 "task1.y"
  {
    if(lookupMethod(currentClassEntry, current_function_name))
    {
      selfClassEntry = currentClassEntry;
    }
    else
    {
      selfClassEntry = findClassForMethod(current_function_name);
    }
    if(!selfClassEntry) {
      printf("expr:lineNumber:%d\n", lineNumber); 
    }
    (yyval.node) = makeFieldNode(makeSelfNode(), (yyvsp[0].node)->varname);
  }
#line 2466 "y.tab.c"
    break;

  case 103: /* IfStmt: IF LPAREN E RPAREN THEN Slist ELSE Slist ENDIF  */
#line 798 "task1.y"
                                                 { (yyval.node) = makeIfElseNode((yyvsp[-6].node), (yyvsp[-3].node), (yyvsp[-1].node)); }
#line 2472 "y.tab.c"
    break;

  case 104: /* IfStmt: IF LPAREN E RPAREN THEN Slist ENDIF  */
#line 799 "task1.y"
                                        { (yyval.node) = makeIfNode((yyvsp[-4].node), (yyvsp[-1].node)); }
#line 2478 "y.tab.c"
    break;

  case 105: /* WhileStmt: WHILE LPAREN E RPAREN DO Slist ENDWHILE  */
#line 803 "task1.y"
                                          { (yyval.node) = makeWhileNode((yyvsp[-4].node), (yyvsp[-1].node)); }
#line 2484 "y.tab.c"
    break;

  case 106: /* BreakStmt: BREAK  */
#line 807 "task1.y"
        { (yyval.node) = makeBreakNode(); }
#line 2490 "y.tab.c"
    break;

  case 107: /* ContinueStmt: CONTINUE  */
#line 811 "task1.y"
           { (yyval.node) = makeContinueNode(); }
#line 2496 "y.tab.c"
    break;

  case 108: /* E: E PLUS E  */
#line 815 "task1.y"
           { (yyval.node) = makeArithNode(NODE_PLUS, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2502 "y.tab.c"
    break;

  case 109: /* E: E MINUS E  */
#line 816 "task1.y"
              { (yyval.node) = makeArithNode(NODE_MINUS, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2508 "y.tab.c"
    break;

  case 110: /* E: E MUL E  */
#line 817 "task1.y"
            { (yyval.node) = makeArithNode(NODE_MUL, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2514 "y.tab.c"
    break;

  case 111: /* E: E DIV E  */
#line 818 "task1.y"
            { (yyval.node) = makeArithNode(NODE_DIV, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2520 "y.tab.c"
    break;

  case 112: /* E: E LT E  */
#line 819 "task1.y"
           { (yyval.node) = makeBoolNode(NODE_LT, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2526 "y.tab.c"
    break;

  case 113: /* E: E GT E  */
#line 820 "task1.y"
           { (yyval.node) = makeBoolNode(NODE_GT, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2532 "y.tab.c"
    break;

  case 114: /* E: E EQ E  */
#line 821 "task1.y"
           { (yyval.node) = makeBoolNode(NODE_EQ, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2538 "y.tab.c"
    break;

  case 115: /* E: E LE E  */
#line 822 "task1.y"
           { (yyval.node) = makeBoolNode(NODE_LE, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2544 "y.tab.c"
    break;

  case 116: /* E: E GE E  */
#line 823 "task1.y"
           { (yyval.node) = makeBoolNode(NODE_GE, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2550 "y.tab.c"
    break;

  case 117: /* E: E NE E  */
#line 824 "task1.y"
           { (yyval.node) = makeBoolNode(NODE_NE, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2556 "y.tab.c"
    break;

  case 118: /* E: E AND E  */
#line 825 "task1.y"
            { (yyval.node) = makeBoolNode(NODE_AND, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2562 "y.tab.c"
    break;

  case 119: /* E: E OR E  */
#line 826 "task1.y"
            { (yyval.node) = makeBoolNode(NODE_OR, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2568 "y.tab.c"
    break;

  case 120: /* E: NOT E  */
#line 827 "task1.y"
            { (yyval.node) = makeNotNode((yyvsp[0].node)); }
#line 2574 "y.tab.c"
    break;

  case 121: /* E: NUM  */
#line 828 "task1.y"
        { (yyval.node) = (yyvsp[0].node); }
#line 2580 "y.tab.c"
    break;

  case 122: /* E: STRING  */
#line 829 "task1.y"
           { (yyval.node) = (yyvsp[0].node); }
#line 2586 "y.tab.c"
    break;

  case 123: /* E: NULLVAL  */
#line 830 "task1.y"
               { (yyval.node) = makeNullNode(); }
#line 2592 "y.tab.c"
    break;

  case 124: /* E: ID  */
#line 831 "task1.y"
       { (yyval.node) = makeVarNode((yyvsp[0].node)->varname); }
#line 2598 "y.tab.c"
    break;

  case 125: /* E: ID LPAREN ArgList RPAREN  */
#line 832 "task1.y"
                             { (yyval.node) = makeFuncallNode((yyvsp[-3].node)->varname, (yyvsp[-1].node)); }
#line 2604 "y.tab.c"
    break;

  case 126: /* E: ID LPAREN RPAREN  */
#line 833 "task1.y"
                     { (yyval.node) = makeFuncallNode((yyvsp[-2].node)->varname, NULL); }
#line 2610 "y.tab.c"
    break;

  case 127: /* E: MUL E  */
#line 834 "task1.y"
                      { (yyval.node) = makeDerefNode((yyvsp[0].node)); }
#line 2616 "y.tab.c"
    break;

  case 128: /* E: ADDRESS_OF ID  */
#line 835 "task1.y"
                              { (yyval.node) = makePointerNode(makeVarNode((yyvsp[0].node)->varname)); }
#line 2622 "y.tab.c"
    break;

  case 129: /* E: LPAREN E RPAREN  */
#line 836 "task1.y"
                    { (yyval.node) = (yyvsp[-1].node); }
#line 2628 "y.tab.c"
    break;

  case 130: /* E: ID LSQBR E RSQBR  */
#line 837 "task1.y"
                     { (yyval.node) = makeArrayNode((yyvsp[-3].node), (yyvsp[-1].node)); }
#line 2634 "y.tab.c"
    break;

  case 132: /* E: SELF_KW  */
#line 840 "task1.y"
  {
    if(lookupMethod(currentClassEntry, current_function_name))
    {
      selfClassEntry = currentClassEntry;
    }
    else
    {
      selfClassEntry = findClassForMethod(current_function_name);
    }
    if(!selfClassEntry) {
      printf("expr:lineNumber:%d\n", lineNumber); 
    }
    (yyval.node) = makeSelfNode(); 
  }
#line 2653 "y.tab.c"
    break;

  case 133: /* E: SELF_KW DOT ID LPAREN ArgList RPAREN  */
#line 855 "task1.y"
  {
    if(lookupMethod(currentClassEntry, current_function_name))
    {
      selfClassEntry = currentClassEntry;
    }
    else
    {
      selfClassEntry = findClassForMethod(current_function_name);
    }
    if(!selfClassEntry) {
      printf("expr:lineNumber:%d\n", lineNumber); 
    } 
    (yyval.node) = makeMethodCallNode(makeSelfNode(), (yyvsp[-3].node)->varname, (yyvsp[-1].node)); 
  }
#line 2672 "y.tab.c"
    break;

  case 134: /* E: SELF_KW DOT ID LPAREN RPAREN  */
#line 870 "task1.y"
  { 
    if(lookupMethod(currentClassEntry, current_function_name))
    {
      selfClassEntry = currentClassEntry;
    }
    else
    {
      selfClassEntry = findClassForMethod(current_function_name);
    }
    if(!selfClassEntry) {
      printf("expr:lineNumber:%d\n", lineNumber); 
    }
    (yyval.node) = makeMethodCallNode(makeSelfNode(), (yyvsp[-2].node)->varname, NULL); 
  }
#line 2691 "y.tab.c"
    break;

  case 135: /* E: ID DOT ID LPAREN ArgList RPAREN  */
#line 884 "task1.y"
                                    { (yyval.node) = makeMethodCallNode(makeVarNode((yyvsp[-5].node)->varname), (yyvsp[-3].node)->varname, (yyvsp[-1].node)); }
#line 2697 "y.tab.c"
    break;

  case 136: /* E: ID DOT ID LPAREN RPAREN  */
#line 885 "task1.y"
                            { (yyval.node) = makeMethodCallNode(makeVarNode((yyvsp[-4].node)->varname), (yyvsp[-2].node)->varname, NULL); }
#line 2703 "y.tab.c"
    break;

  case 137: /* E: FieldAccess DOT ID LPAREN ArgList RPAREN  */
#line 887 "task1.y"
  { 
    tnode *t = makeFieldNode((yyvsp[-5].node)->left, (yyvsp[-5].node)->varname);
    (yyval.node) = makeMethodCallNode(t, (yyvsp[-3].node)->varname, (yyvsp[-1].node)); 
  }
#line 2712 "y.tab.c"
    break;

  case 138: /* E: FieldAccess DOT ID LPAREN RPAREN  */
#line 892 "task1.y"
  { 
    tnode *t = makeFieldNode((yyvsp[-4].node)->left, (yyvsp[-4].node)->varname);
    (yyval.node) = makeMethodCallNode(t, (yyvsp[-2].node)->varname, NULL); 
  }
#line 2721 "y.tab.c"
    break;

  case 139: /* ArgList: ArgList COMMA E  */
#line 900 "task1.y"
                  { (yyval.node) = makeConnectorNode((yyvsp[-2].node), (yyvsp[0].node)); }
#line 2727 "y.tab.c"
    break;

  case 140: /* ArgList: E  */
#line 901 "task1.y"
      { (yyval.node) = (yyvsp[0].node); }
#line 2733 "y.tab.c"
    break;


#line 2737 "y.tab.c"

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
      yyerror (YY_("syntax error"));
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

  return yyresult;
}

#line 904 "task1.y"


void yyerror(char *s) 
{
  fprintf(stderr, "Error at line %d: %s: %s\n", lineNumber, s, yytext);
}

int main(int argc, char **argv) 
{
  if (argc < 3)   
  {
    fprintf(stderr, "Usage: %s <input_file> <output_file>\n", argv[0]);
    return 1;
  }
  
  FILE *fp = fopen(argv[1], "r");
  if (fp) yyin = fp;
  else {
    fprintf(stderr, "Error: Cannot open input file %s\n", argv[1]);
    return 1;
  }

  FILE * target_file = fopen(argv[2], "w");
  if (!target_file) {
    fprintf(stderr, "Error: Cannot open output file %s\n", argv[2]);
    return 1;
  }

  interim_file = fopen("interim_file.xsm", "w");
  if (!interim_file) {
    fprintf(stderr, "Error: Cannot open interim file\n");
    return 1;
  }

  initTypeTable();
  initClassTable();
  initReg();
  fileinit(interim_file);
  
  current_function_name = NULL;
  
  yyparse();
  emitExit(interim_file);

  fclose(interim_file);

  interim_file = fopen("interim_file.xsm", "r");
  rewind(interim_file);
  buildLabelTable(interim_file);

  translateLabels(interim_file, target_file);

  fclose(interim_file);
  fclose(target_file);
  

  return 0;
}
