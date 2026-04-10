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

#line 99 "y.tab.c"

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

#line 268 "y.tab.c"

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
  YYSYMBOL_INT = 6,                        /* INT  */
  YYSYMBOL_STR = 7,                        /* STR  */
  YYSYMBOL_MAIN = 8,                       /* MAIN  */
  YYSYMBOL_DECL = 9,                       /* DECL  */
  YYSYMBOL_ENDDECL = 10,                   /* ENDDECL  */
  YYSYMBOL_kBEGIN = 11,                    /* kBEGIN  */
  YYSYMBOL_kEND = 12,                      /* kEND  */
  YYSYMBOL_WRITE = 13,                     /* WRITE  */
  YYSYMBOL_READ = 14,                      /* READ  */
  YYSYMBOL_RETURN = 15,                    /* RETURN  */
  YYSYMBOL_IF = 16,                        /* IF  */
  YYSYMBOL_THEN = 17,                      /* THEN  */
  YYSYMBOL_ELSE = 18,                      /* ELSE  */
  YYSYMBOL_ENDIF = 19,                     /* ENDIF  */
  YYSYMBOL_WHILE = 20,                     /* WHILE  */
  YYSYMBOL_DO = 21,                        /* DO  */
  YYSYMBOL_ENDWHILE = 22,                  /* ENDWHILE  */
  YYSYMBOL_BREAK = 23,                     /* BREAK  */
  YYSYMBOL_CONTINUE = 24,                  /* CONTINUE  */
  YYSYMBOL_SEMICOLON = 25,                 /* SEMICOLON  */
  YYSYMBOL_COMMA = 26,                     /* COMMA  */
  YYSYMBOL_LPAREN = 27,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 28,                    /* RPAREN  */
  YYSYMBOL_LBRACE = 29,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 30,                    /* RBRACE  */
  YYSYMBOL_LSQBR = 31,                     /* LSQBR  */
  YYSYMBOL_RSQBR = 32,                     /* RSQBR  */
  YYSYMBOL_ASSIGN = 33,                    /* ASSIGN  */
  YYSYMBOL_ADDRESS_OF = 34,                /* ADDRESS_OF  */
  YYSYMBOL_MUL = 35,                       /* MUL  */
  YYSYMBOL_TYPE_KW = 36,                   /* TYPE_KW  */
  YYSYMBOL_ENDTYPE = 37,                   /* ENDTYPE  */
  YYSYMBOL_DOT = 38,                       /* DOT  */
  YYSYMBOL_ALLOC = 39,                     /* ALLOC  */
  YYSYMBOL_FREE_KW = 40,                   /* FREE_KW  */
  YYSYMBOL_INITIALIZE = 41,                /* INITIALIZE  */
  YYSYMBOL_NULLVAL = 42,                   /* NULLVAL  */
  YYSYMBOL_OR = 43,                        /* OR  */
  YYSYMBOL_AND = 44,                       /* AND  */
  YYSYMBOL_NOT = 45,                       /* NOT  */
  YYSYMBOL_PLUS = 46,                      /* PLUS  */
  YYSYMBOL_MINUS = 47,                     /* MINUS  */
  YYSYMBOL_DIV = 48,                       /* DIV  */
  YYSYMBOL_LT = 49,                        /* LT  */
  YYSYMBOL_LE = 50,                        /* LE  */
  YYSYMBOL_GT = 51,                        /* GT  */
  YYSYMBOL_GE = 52,                        /* GE  */
  YYSYMBOL_EQ = 53,                        /* EQ  */
  YYSYMBOL_NE = 54,                        /* NE  */
  YYSYMBOL_UNARY = 55,                     /* UNARY  */
  YYSYMBOL_YYACCEPT = 56,                  /* $accept  */
  YYSYMBOL_Program = 57,                   /* Program  */
  YYSYMBOL_TypeDefBlock = 58,              /* TypeDefBlock  */
  YYSYMBOL_TypeDefList = 59,               /* TypeDefList  */
  YYSYMBOL_TypeDef = 60,                   /* TypeDef  */
  YYSYMBOL_61_1 = 61,                      /* $@1  */
  YYSYMBOL_FieldDecList = 62,              /* FieldDecList  */
  YYSYMBOL_FieldDec = 63,                  /* FieldDec  */
  YYSYMBOL_GDeclarations = 64,             /* GDeclarations  */
  YYSYMBOL_GDecList = 65,                  /* GDecList  */
  YYSYMBOL_GDecl = 66,                     /* GDecl  */
  YYSYMBOL_GidList = 67,                   /* GidList  */
  YYSYMBOL_Gid = 68,                       /* Gid  */
  YYSYMBOL_Type = 69,                      /* Type  */
  YYSYMBOL_ParamList = 70,                 /* ParamList  */
  YYSYMBOL_Param = 71,                     /* Param  */
  YYSYMBOL_FdefBlock = 72,                 /* FdefBlock  */
  YYSYMBOL_Fdef = 73,                      /* Fdef  */
  YYSYMBOL_74_2 = 74,                      /* $@2  */
  YYSYMBOL_LdeclBlock = 75,                /* LdeclBlock  */
  YYSYMBOL_LDecList = 76,                  /* LDecList  */
  YYSYMBOL_LDecl = 77,                     /* LDecl  */
  YYSYMBOL_IdList = 78,                    /* IdList  */
  YYSYMBOL_MainBlock = 79,                 /* MainBlock  */
  YYSYMBOL_80_3 = 80,                      /* $@3  */
  YYSYMBOL_Body = 81,                      /* Body  */
  YYSYMBOL_Slist = 82,                     /* Slist  */
  YYSYMBOL_Stmt = 83,                      /* Stmt  */
  YYSYMBOL_InputStmt = 84,                 /* InputStmt  */
  YYSYMBOL_OutputStmt = 85,                /* OutputStmt  */
  YYSYMBOL_FreeStmt = 86,                  /* FreeStmt  */
  YYSYMBOL_InitStmt = 87,                  /* InitStmt  */
  YYSYMBOL_AssgStmt = 88,                  /* AssgStmt  */
  YYSYMBOL_LValue = 89,                    /* LValue  */
  YYSYMBOL_FieldAccess = 90,               /* FieldAccess  */
  YYSYMBOL_IfStmt = 91,                    /* IfStmt  */
  YYSYMBOL_WhileStmt = 92,                 /* WhileStmt  */
  YYSYMBOL_BreakStmt = 93,                 /* BreakStmt  */
  YYSYMBOL_ContinueStmt = 94,              /* ContinueStmt  */
  YYSYMBOL_E = 95,                         /* E  */
  YYSYMBOL_ArgList = 96                    /* ArgList  */
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
#define YYFINAL  17
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   499

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  56
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  41
/* YYNRULES -- Number of rules.  */
#define YYNRULES  108
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  222

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   310


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
      55
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    60,    60,    61,    62,    63,    64,    68,    75,    76,
      81,    80,    91,    92,    96,   141,   145,   146,   150,   151,
     155,   159,   160,   164,   168,   172,   177,   184,   188,   192,
     196,   211,   212,   216,   220,   221,   226,   225,   254,   283,
     284,   285,   289,   290,   294,   298,   303,   311,   310,   340,
     341,   345,   346,   350,   351,   352,   353,   354,   355,   356,
     357,   358,   359,   360,   364,   365,   366,   374,   378,   385,
     391,   392,   397,   404,   408,   412,   416,   421,   428,   429,
     433,   437,   441,   445,   446,   447,   448,   449,   450,   451,
     452,   453,   454,   455,   456,   457,   458,   459,   460,   461,
     462,   463,   464,   465,   466,   467,   468,   472,   473
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
  "INT", "STR", "MAIN", "DECL", "ENDDECL", "kBEGIN", "kEND", "WRITE",
  "READ", "RETURN", "IF", "THEN", "ELSE", "ENDIF", "WHILE", "DO",
  "ENDWHILE", "BREAK", "CONTINUE", "SEMICOLON", "COMMA", "LPAREN",
  "RPAREN", "LBRACE", "RBRACE", "LSQBR", "RSQBR", "ASSIGN", "ADDRESS_OF",
  "MUL", "TYPE_KW", "ENDTYPE", "DOT", "ALLOC", "FREE_KW", "INITIALIZE",
  "NULLVAL", "OR", "AND", "NOT", "PLUS", "MINUS", "DIV", "LT", "LE", "GT",
  "GE", "EQ", "NE", "UNARY", "$accept", "Program", "TypeDefBlock",
  "TypeDefList", "TypeDef", "$@1", "FieldDecList", "FieldDec",
  "GDeclarations", "GDecList", "GDecl", "GidList", "Gid", "Type",
  "ParamList", "Param", "FdefBlock", "Fdef", "$@2", "LdeclBlock",
  "LDecList", "LDecl", "IdList", "MainBlock", "$@3", "Body", "Slist",
  "Stmt", "InputStmt", "OutputStmt", "FreeStmt", "InitStmt", "AssgStmt",
  "LValue", "FieldAccess", "IfStmt", "WhileStmt", "BreakStmt",
  "ContinueStmt", "E", "ArgList", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-117)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-3)

#define yytable_value_is_error(Yyn) \
  ((Yyn) == YYTABLE_NINF)

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      29,   241,     1,    21,    16,    87,  -117,  -117,  -117,  -117,
     141,   248,  -117,    48,  -117,    -1,  -117,  -117,    87,    50,
      63,    87,  -117,  -117,  -117,  -117,  -117,    -8,    80,  -117,
       6,  -117,  -117,    87,  -117,  -117,    49,  -117,  -117,   146,
      89,  -117,    48,   141,  -117,    74,   187,  -117,   114,    31,
    -117,    79,  -117,   227,  -117,   119,    98,   134,    47,  -117,
     141,  -117,  -117,  -117,  -117,   139,   143,   164,  -117,  -117,
    -117,   164,   264,   169,   156,   169,  -117,   183,   271,  -117,
      84,   159,   164,   162,  -117,   107,  -117,  -117,   -23,  -117,
     175,   176,   109,   178,   182,  -117,  -117,   210,   191,   196,
     155,   201,  -117,  -117,  -117,  -117,  -117,   194,   190,  -117,
    -117,  -117,  -117,  -117,   169,  -117,  -117,   225,   109,   231,
     109,     2,  -117,   100,  -117,   109,   232,   109,  -117,   109,
     190,   415,   109,   109,   211,   239,   228,  -117,   234,  -117,
      27,   249,   230,  -117,   349,  -117,   244,    43,   260,    75,
     109,   272,  -117,  -117,   445,   109,   109,   109,   109,   109,
     109,   109,   109,   109,   109,   109,   109,   299,   326,   109,
     235,  -117,  -117,   238,   415,  -117,  -117,  -117,  -117,  -117,
     109,   245,  -117,   415,   158,   372,  -117,   259,   435,   445,
      33,    33,   259,   279,   279,   279,   279,   279,   279,   252,
     261,   415,  -117,   256,   395,  -117,   109,  -117,  -117,   226,
     226,  -117,   257,   415,   142,   184,  -117,   226,  -117,  -117,
     197,  -117
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
      17,     0,     0,     0,    17,     0,    30,    27,    28,    16,
       0,     0,    19,     0,    10,     0,     9,     1,     0,    27,
       0,     0,    35,     6,    29,    15,    18,    23,     0,    22,
       0,     7,     8,     0,     4,    47,     0,    34,     5,     0,
       0,    20,     0,     0,     3,     0,     0,    26,     0,     0,
      32,     0,    21,     0,    13,     0,     0,     0,     0,    33,
       0,    25,    24,    11,    12,     0,     0,    41,    36,    31,
      14,    41,     0,     0,     0,     0,    40,     0,     0,    43,
       0,     0,    41,     0,    46,     0,    39,    42,    73,    50,
       0,     0,    61,     0,     0,    81,    82,     0,     0,     0,
       0,     0,    53,    54,    62,    63,    55,     0,    75,    56,
      57,    58,    59,    38,     0,    48,    44,     0,     0,     0,
       0,     0,    96,    99,    97,     0,     0,     0,    98,     0,
     106,    60,     0,     0,     0,     0,     0,    49,     0,    52,
       0,     0,     0,    45,     0,    76,     0,     0,     0,     0,
       0,     0,   103,   102,    95,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    69,    51,     0,    70,    77,    37,    74,    67,    64,
       0,     0,   101,   108,     0,     0,   104,    85,    94,    93,
      83,    84,    86,    87,    90,    88,    91,    89,    92,     0,
       0,    71,    68,     0,     0,    66,     0,   100,   105,     0,
       0,    72,     0,   107,     0,     0,    65,     0,    79,    80,
       0,    78
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -117,  -117,  -117,  -117,   265,  -117,  -117,   233,   285,  -117,
     290,  -117,   262,    17,   268,   242,   287,    -7,  -117,    57,
    -117,   258,  -117,   -11,  -117,   -63,   -68,   -99,  -117,  -117,
    -117,  -117,  -117,   168,   -80,  -117,  -117,  -117,  -117,  -116,
    -117
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     3,     4,    15,    16,    30,    53,    54,     5,    11,
      12,    28,    29,    20,    49,    50,    21,    22,    74,    73,
      78,    79,    85,    23,    45,    81,   100,   101,   102,   103,
     104,   105,   106,   107,   130,   109,   110,   111,   112,   131,
     184
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     108,   138,   144,    14,   146,    14,   147,    34,   118,   151,
      38,   153,    83,   154,    37,   119,   167,   168,    13,    39,
     108,    17,    44,    40,   174,     1,    37,    24,    13,    -2,
     122,   123,   124,   183,   185,    43,    31,   148,     1,   187,
     188,   189,   190,   191,   192,   193,   194,   195,   196,   197,
     198,   142,    27,   201,   125,   108,    48,    60,    35,    61,
      55,   126,   127,    48,   204,     2,   173,    36,   155,   128,
      55,   179,   129,    60,   180,    68,    46,    48,   122,   123,
     124,   160,   161,   162,   163,   164,   165,   166,    88,    77,
     213,     6,    51,    19,     8,    77,    89,    90,    91,    92,
      93,    56,   125,   182,    94,    41,    42,    95,    96,   126,
     127,    62,   122,   123,   124,   138,   138,   128,    59,    97,
     129,   138,    10,    65,    98,    99,    66,   149,    75,   108,
     108,   150,   116,   117,   108,   108,   125,   108,   119,   114,
     108,   214,   215,   126,   127,     6,    88,     7,     8,   220,
       6,   128,     7,     8,   129,    90,    91,    92,    93,    88,
     217,   218,    94,    67,    70,    95,    96,   137,    90,    91,
      92,    93,    71,    72,    47,    94,    10,    97,    95,    96,
      80,    10,    98,    99,   206,    82,   207,    84,    88,   113,
      97,     6,   115,     7,     8,    98,    99,    90,    91,    92,
      93,    88,   120,   121,    94,   132,   219,    95,    96,   133,
      90,    91,    92,    93,   134,    57,   221,    94,   135,    97,
      95,    96,    10,   136,    98,    99,   139,   140,   141,   143,
      88,     6,    97,     7,     8,   145,   152,    98,    99,    90,
      91,    92,    93,    88,   169,     6,    94,     7,     8,    95,
      96,     9,     6,   175,     7,     8,   171,    63,    25,   172,
     176,    97,    10,   202,   181,   203,    98,    99,     6,   209,
       7,     8,   178,   205,    76,     6,    10,     7,     8,   155,
      32,    86,   210,    10,   211,   216,    64,   156,   157,    18,
     158,   159,   160,   161,   162,   163,   164,   165,   166,    10,
     186,    26,    69,   170,    52,    33,    10,   155,   161,   162,
     163,   164,   165,   166,    58,   156,   157,     0,   158,   159,
     160,   161,   162,   163,   164,   165,   166,   199,    -3,    -3,
      -3,    -3,    -3,    -3,   155,     0,    87,     0,     0,     0,
       0,     0,   156,   157,     0,   158,   159,   160,   161,   162,
     163,   164,   165,   166,   200,     0,     0,     0,     0,     0,
       0,   155,     0,     0,     0,     0,     0,     0,     0,   156,
     157,     0,   158,   159,   160,   161,   162,   163,   164,   165,
     166,   177,     0,     0,   155,     0,     0,     0,     0,     0,
       0,     0,   156,   157,     0,   158,   159,   160,   161,   162,
     163,   164,   165,   166,   208,     0,     0,   155,     0,     0,
       0,     0,     0,     0,     0,   156,   157,     0,   158,   159,
     160,   161,   162,   163,   164,   165,   166,   212,     0,     0,
     155,     0,     0,     0,     0,     0,     0,     0,   156,   157,
       0,   158,   159,   160,   161,   162,   163,   164,   165,   166,
     155,     0,     0,     0,     0,     0,     0,     0,   156,   157,
       0,   158,   159,   160,   161,   162,   163,   164,   165,   166,
     155,     0,     0,     0,     0,     0,     0,     0,     0,   157,
     155,   158,   159,   160,   161,   162,   163,   164,   165,   166,
       0,   158,   159,   160,   161,   162,   163,   164,   165,   166
};

static const yytype_int16 yycheck[] =
{
      80,   100,   118,     4,   120,     4,     4,    18,    31,   125,
      21,   127,    75,   129,    21,    38,   132,   133,     1,    27,
     100,     0,    33,    31,   140,     9,    33,    10,    11,     0,
       3,     4,     5,   149,   150,    29,    37,    35,     9,   155,
     156,   157,   158,   159,   160,   161,   162,   163,   164,   165,
     166,   114,     4,   169,    27,   135,    39,    26,     8,    28,
      43,    34,    35,    46,   180,    36,    39,     4,    35,    42,
      53,    28,    45,    26,    31,    28,    27,    60,     3,     4,
       5,    48,    49,    50,    51,    52,    53,    54,     4,    72,
     206,     4,     3,     6,     7,    78,    12,    13,    14,    15,
      16,    27,    27,    28,    20,    25,    26,    23,    24,    34,
      35,    32,     3,     4,     5,   214,   215,    42,     4,    35,
      45,   220,    35,     4,    40,    41,    28,    27,    71,   209,
     210,    31,    25,    26,   214,   215,    27,   217,    38,    82,
     220,   209,   210,    34,    35,     4,     4,     6,     7,   217,
       4,    42,     6,     7,    45,    13,    14,    15,    16,     4,
      18,    19,    20,    29,    25,    23,    24,    12,    13,    14,
      15,    16,    29,     9,    28,    20,    35,    35,    23,    24,
      11,    35,    40,    41,    26,    29,    28,     4,     4,    30,
      35,     4,    30,     6,     7,    40,    41,    13,    14,    15,
      16,     4,    27,    27,    20,    27,    22,    23,    24,    27,
      13,    14,    15,    16,     4,    28,    19,    20,    27,    35,
      23,    24,    35,    27,    40,    41,    25,    33,    38,     4,
       4,     4,    35,     6,     7,     4,     4,    40,    41,    13,
      14,    15,    16,     4,    33,     4,    20,     6,     7,    23,
      24,    10,     4,     4,     6,     7,    28,    30,    10,    25,
      30,    35,    35,    28,     4,    27,    40,    41,     4,    17,
       6,     7,    28,    28,    10,     4,    35,     6,     7,    35,
      15,    10,    21,    35,    28,    28,    53,    43,    44,     4,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    35,
      28,    11,    60,   135,    42,    18,    35,    35,    49,    50,
      51,    52,    53,    54,    46,    43,    44,    -1,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    28,    49,    50,
      51,    52,    53,    54,    35,    -1,    78,    -1,    -1,    -1,
      -1,    -1,    43,    44,    -1,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    28,    -1,    -1,    -1,    -1,    -1,
      -1,    35,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    43,
      44,    -1,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    32,    -1,    -1,    35,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    43,    44,    -1,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    32,    -1,    -1,    35,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    43,    44,    -1,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    32,    -1,    -1,
      35,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    43,    44,
      -1,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      35,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    43,    44,
      -1,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      35,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    44,
      35,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      -1,    46,    47,    48,    49,    50,    51,    52,    53,    54
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     9,    36,    57,    58,    64,     4,     6,     7,    10,
      35,    65,    66,    69,     4,    59,    60,     0,    64,     6,
      69,    72,    73,    79,    69,    10,    66,     4,    67,    68,
      61,    37,    60,    72,    79,     8,     4,    73,    79,    27,
      31,    25,    26,    29,    79,    80,    27,    28,    69,    70,
      71,     3,    68,    62,    63,    69,    27,    28,    70,     4,
      26,    28,    32,    30,    63,     4,    28,    29,    28,    71,
      25,    29,     9,    75,    74,    75,    10,    69,    76,    77,
      11,    81,    29,    81,     4,    78,    10,    77,     4,    12,
      13,    14,    15,    16,    20,    23,    24,    35,    40,    41,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    30,    75,    30,    25,    26,    31,    38,
      27,    27,     3,     4,     5,    27,    34,    35,    42,    45,
      90,    95,    27,    27,     4,    27,    27,    12,    83,    25,
      33,    38,    81,     4,    95,     4,    95,     4,    35,    27,
      31,    95,     4,    95,    95,    35,    43,    44,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    95,    95,    33,
      89,    28,    25,    39,    95,     4,    30,    32,    28,    28,
      31,     4,    28,    95,    96,    95,    28,    95,    95,    95,
      95,    95,    95,    95,    95,    95,    95,    95,    95,    28,
      28,    95,    28,    27,    95,    28,    26,    28,    32,    17,
      21,    28,    32,    95,    82,    82,    28,    18,    19,    22,
      82,    19
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    56,    57,    57,    57,    57,    57,    58,    59,    59,
      61,    60,    62,    62,    63,    64,    64,    64,    65,    65,
      66,    67,    67,    68,    68,    68,    68,    69,    69,    69,
      69,    70,    70,    71,    72,    72,    74,    73,    73,    75,
      75,    75,    76,    76,    77,    78,    78,    80,    79,    81,
      81,    82,    82,    83,    83,    83,    83,    83,    83,    83,
      83,    83,    83,    83,    84,    84,    84,    85,    86,    87,
      88,    88,    88,    89,    89,    89,    90,    90,    91,    91,
      92,    93,    94,    95,    95,    95,    95,    95,    95,    95,
      95,    95,    95,    95,    95,    95,    95,    95,    95,    95,
      95,    95,    95,    95,    95,    95,    95,    96,    96
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     4,     3,     3,     2,     3,     2,     1,
       0,     5,     2,     1,     3,     3,     2,     0,     2,     1,
       3,     3,     1,     1,     4,     4,     3,     1,     1,     2,
       1,     3,     1,     2,     2,     1,     0,    10,     8,     3,
       2,     0,     2,     1,     3,     3,     1,     0,     9,     3,
       2,     3,     2,     1,     1,     1,     1,     1,     1,     1,
       2,     1,     1,     1,     4,     7,     5,     4,     4,     3,
       3,     4,     5,     1,     4,     1,     3,     3,     9,     7,
       7,     1,     1,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     2,     1,     1,     1,     1,
       4,     3,     2,     2,     3,     4,     1,     3,     1
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
  case 3: /* Program: TypeDefBlock GDeclarations FdefBlock MainBlock  */
#line 61 "task1.y"
                                                   { root = (yyvsp[0].node); }
#line 1550 "y.tab.c"
    break;

  case 4: /* Program: TypeDefBlock GDeclarations MainBlock  */
#line 62 "task1.y"
                                         { root = (yyvsp[0].node); }
#line 1556 "y.tab.c"
    break;

  case 5: /* Program: GDeclarations FdefBlock MainBlock  */
#line 63 "task1.y"
                                      { root = (yyvsp[0].node); }
#line 1562 "y.tab.c"
    break;

  case 6: /* Program: GDeclarations MainBlock  */
#line 64 "task1.y"
                            { root = (yyvsp[0].node); }
#line 1568 "y.tab.c"
    break;

  case 7: /* TypeDefBlock: TYPE_KW TypeDefList ENDTYPE  */
#line 69 "task1.y"
  {
    printTypeTable();
  }
#line 1576 "y.tab.c"
    break;

  case 10: /* $@1: %empty  */
#line 81 "task1.y"
  {
    currentUdefType = installType((yyvsp[0].node)->varname);
  }
#line 1584 "y.tab.c"
    break;

  case 11: /* TypeDef: ID $@1 LBRACE FieldDecList RBRACE  */
#line 85 "task1.y"
  {
    currentUdefType = NULL; // end of type definition
  }
#line 1592 "y.tab.c"
    break;

  case 14: /* FieldDec: Type ID SEMICOLON  */
#line 97 "task1.y"
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
#line 1631 "y.tab.c"
    break;

  case 15: /* GDeclarations: DECL GDecList ENDDECL  */
#line 142 "task1.y"
    { 
      handleGdecComplete(); 
    }
#line 1639 "y.tab.c"
    break;

  case 23: /* Gid: ID  */
#line 165 "task1.y"
  { 
    handleGidScalar((yyvsp[0].node), &currentTypeData); 
  }
#line 1647 "y.tab.c"
    break;

  case 24: /* Gid: ID LSQBR NUM RSQBR  */
#line 169 "task1.y"
  { 
    handleGidArray1D((yyvsp[-3].node), &currentTypeData, (yyvsp[-1].node)->val); 
  }
#line 1655 "y.tab.c"
    break;

  case 25: /* Gid: ID LPAREN ParamList RPAREN  */
#line 173 "task1.y"
  { 
    struct TypeInfo funcType = (yyvsp[-4].typeData);
    handleGidFunction((yyvsp[-3].node), &funcType, (yyvsp[-1].param)); 
  }
#line 1664 "y.tab.c"
    break;

  case 26: /* Gid: ID LPAREN RPAREN  */
#line 178 "task1.y"
  { 
    handleGidFunction((yyvsp[-2].node), &currentTypeData, NULL); 
  }
#line 1672 "y.tab.c"
    break;

  case 27: /* Type: INT  */
#line 184 "task1.y"
      { 
      (yyval.typeData).type = TYPE_INT; (yyval.typeData).ptrLevel = 0; 
      currentTypeData = (yyval.typeData); 
  }
#line 1681 "y.tab.c"
    break;

  case 28: /* Type: STR  */
#line 188 "task1.y"
        { 
      (yyval.typeData).type = TYPE_STRING; (yyval.typeData).ptrLevel = 0; 
      currentTypeData = (yyval.typeData); 
  }
#line 1690 "y.tab.c"
    break;

  case 29: /* Type: MUL Type  */
#line 192 "task1.y"
             { 
      (yyval.typeData) = (yyvsp[0].typeData); (yyval.typeData).ptrLevel++; 
      currentTypeData = (yyval.typeData); 
  }
#line 1699 "y.tab.c"
    break;

  case 30: /* Type: ID  */
#line 196 "task1.y"
       {
      TypeTableEntry *t = lookupType((yyvsp[0].node)->varname);
      if(!t || t->typeId < TYPE_USERDEF)
      {
        yyerror("Undefined type name");
        exit(1);
      }
      (yyval.typeData).type = TYPE_USERDEF;
      (yyval.typeData).typeEntry = t;
      (yyval.typeData).ptrLevel = 0;
      currentTypeData = (yyval.typeData);
  }
#line 1716 "y.tab.c"
    break;

  case 31: /* ParamList: ParamList COMMA Param  */
#line 211 "task1.y"
                        { (yyval.param) = AppendParam((yyvsp[-2].param), (yyvsp[0].param)); }
#line 1722 "y.tab.c"
    break;

  case 32: /* ParamList: Param  */
#line 212 "task1.y"
          { (yyval.param) = (yyvsp[0].param); }
#line 1728 "y.tab.c"
    break;

  case 33: /* Param: Type ID  */
#line 216 "task1.y"
          { (yyval.param) = CreateParam((yyvsp[0].node)->varname, (yyvsp[-1].typeData).type, (yyvsp[-1].typeData).typeEntry, (yyvsp[-1].typeData).ptrLevel); }
#line 1734 "y.tab.c"
    break;

  case 36: /* $@2: %empty  */
#line 226 "task1.y"
  {
    handleParamInstall((yyvsp[-1].param));
    // set current function name
    current_function_name = (yyvsp[-3].node)->varname;
  }
#line 1744 "y.tab.c"
    break;

  case 37: /* Fdef: Type ID LPAREN ParamList RPAREN $@2 LBRACE LdeclBlock Body RBRACE  */
#line 232 "task1.y"
  { 
    struct TypeInfo retType = (yyvsp[-9].typeData);
    verifyFunctionSignature(Lookup((yyvsp[-8].node)->varname), &retType, (yyvsp[-6].param));
    handleFdefPrint((yyvsp[-8].node)->varname, (yyvsp[-1].node));

    struct Gsymbol* g = Lookup((yyvsp[-8].node)->varname);
    
    fprintf(interim_file, "F%d:\n", g->flabel);
    fprintf(interim_file, "PUSH BP\n");
    fprintf(interim_file, "MOV BP, SP\n");

    locAlloc(interim_file);
    

    codeGen((yyvsp[-1].node), interim_file);

    // Clear current function name
    current_function_name = NULL;

    // Now it is expected that all functions have a return statement(empty or not)
    resetLocalSymbolTable();
  }
#line 1771 "y.tab.c"
    break;

  case 38: /* Fdef: Type ID LPAREN RPAREN LBRACE LdeclBlock Body RBRACE  */
#line 255 "task1.y"
  {
    // Set current function name
    current_function_name = (yyvsp[-6].node)->varname;
    
    struct TypeInfo retType = (yyvsp[-7].typeData);
    verifyFunctionSignature(Lookup((yyvsp[-6].node)->varname), &retType, NULL);
    handleFdefNoArgsPrint((yyvsp[-6].node)->varname, (yyvsp[-1].node)); 

    struct Gsymbol* g = Lookup((yyvsp[-6].node)->varname);
    
    fprintf(interim_file, "F%d:\n", g->flabel);
    fprintf(interim_file, "PUSH BP\n");
    fprintf(interim_file, "MOV BP, SP\n");

    locAlloc(interim_file);
    

    codeGen((yyvsp[-1].node), interim_file);

    // Clear current function name
    current_function_name = NULL;

    // Now it is expected that all functions have a return statement(empty or not)
    resetLocalSymbolTable();
  }
#line 1801 "y.tab.c"
    break;

  case 45: /* IdList: IdList COMMA ID  */
#line 299 "task1.y"
  { 
    // Uses the global currentTypeData
    handleLidInstall((yyvsp[0].node)->varname, &currentTypeData); 
  }
#line 1810 "y.tab.c"
    break;

  case 46: /* IdList: ID  */
#line 304 "task1.y"
  { 
    handleLidInstall((yyvsp[0].node)->varname, &currentTypeData); 
  }
#line 1818 "y.tab.c"
    break;

  case 47: /* $@3: %empty  */
#line 311 "task1.y"
  {
    current_function_name = "MAIN";
  }
#line 1826 "y.tab.c"
    break;

  case 48: /* MainBlock: INT MAIN $@3 LPAREN RPAREN LBRACE LdeclBlock Body RBRACE  */
#line 315 "task1.y"
  { 
    handleMainPrint((yyvsp[-1].node)); 
    (yyval.node) = (yyvsp[-1].node); 

    
    fprintf(interim_file, "MAIN:\n");
    moveStackPointer(interim_file);
    fprintf(interim_file, "BRKP\n");
    fprintf(interim_file, "PUSH BP\n");
    fprintf(interim_file, "MOV BP, SP\n");
    
    locAlloc(interim_file);
    

    codeGen((yyval.node), interim_file);

    // clear current function name
    current_function_name = NULL;

    // now it is expected that all functions have a return statement(empty or not)
    resetLocalSymbolTable();
  }
#line 1853 "y.tab.c"
    break;

  case 49: /* Body: kBEGIN Slist kEND  */
#line 340 "task1.y"
                    { (yyval.node) = (yyvsp[-1].node); }
#line 1859 "y.tab.c"
    break;

  case 50: /* Body: kBEGIN kEND  */
#line 341 "task1.y"
                { (yyval.node) = NULL; }
#line 1865 "y.tab.c"
    break;

  case 51: /* Slist: Slist Stmt SEMICOLON  */
#line 345 "task1.y"
                       { (yyval.node) = makeConnectorNode((yyvsp[-2].node), (yyvsp[-1].node)); }
#line 1871 "y.tab.c"
    break;

  case 52: /* Slist: Stmt SEMICOLON  */
#line 346 "task1.y"
                   { (yyval.node) = (yyvsp[-1].node); }
#line 1877 "y.tab.c"
    break;

  case 53: /* Stmt: InputStmt  */
#line 350 "task1.y"
            { (yyval.node) = (yyvsp[0].node); }
#line 1883 "y.tab.c"
    break;

  case 54: /* Stmt: OutputStmt  */
#line 351 "task1.y"
               { (yyval.node) = (yyvsp[0].node); }
#line 1889 "y.tab.c"
    break;

  case 55: /* Stmt: AssgStmt  */
#line 352 "task1.y"
             { (yyval.node) = (yyvsp[0].node); }
#line 1895 "y.tab.c"
    break;

  case 56: /* Stmt: IfStmt  */
#line 353 "task1.y"
           { (yyval.node) = (yyvsp[0].node); }
#line 1901 "y.tab.c"
    break;

  case 57: /* Stmt: WhileStmt  */
#line 354 "task1.y"
              { (yyval.node) = (yyvsp[0].node); }
#line 1907 "y.tab.c"
    break;

  case 58: /* Stmt: BreakStmt  */
#line 355 "task1.y"
              { (yyval.node) = (yyvsp[0].node); }
#line 1913 "y.tab.c"
    break;

  case 59: /* Stmt: ContinueStmt  */
#line 356 "task1.y"
                 { (yyval.node) = (yyvsp[0].node); }
#line 1919 "y.tab.c"
    break;

  case 60: /* Stmt: RETURN E  */
#line 357 "task1.y"
             { (yyval.node) = makeReturnNode((yyvsp[0].node), current_function_name); }
#line 1925 "y.tab.c"
    break;

  case 61: /* Stmt: RETURN  */
#line 358 "task1.y"
           { (yyval.node) = makeReturnNode(NULL, current_function_name); }
#line 1931 "y.tab.c"
    break;

  case 62: /* Stmt: FreeStmt  */
#line 359 "task1.y"
             { (yyval.node) = (yyvsp[0].node); }
#line 1937 "y.tab.c"
    break;

  case 63: /* Stmt: InitStmt  */
#line 360 "task1.y"
             { (yyval.node) = (yyvsp[0].node); }
#line 1943 "y.tab.c"
    break;

  case 64: /* InputStmt: READ LPAREN ID RPAREN  */
#line 364 "task1.y"
                        { (yyval.node) = makeReadNode(makeVarNode((yyvsp[-1].node)->varname)); }
#line 1949 "y.tab.c"
    break;

  case 65: /* InputStmt: READ LPAREN ID LSQBR E RSQBR RPAREN  */
#line 365 "task1.y"
                                        { (yyval.node) = makeReadNode(makeArrayNode((yyvsp[-4].node), (yyvsp[-2].node))); }
#line 1955 "y.tab.c"
    break;

  case 66: /* InputStmt: READ LPAREN MUL ID RPAREN  */
#line 367 "task1.y"
  { 
    tnode* ptr_node = makeVarNode((yyvsp[-1].node)->varname);
    (yyval.node) = makeReadNode(makeDerefNode(ptr_node)); 
  }
#line 1964 "y.tab.c"
    break;

  case 67: /* OutputStmt: WRITE LPAREN E RPAREN  */
#line 374 "task1.y"
                        { (yyval.node) = makeWriteNode((yyvsp[-1].node)); }
#line 1970 "y.tab.c"
    break;

  case 68: /* FreeStmt: FREE_KW LPAREN LValue RPAREN  */
#line 379 "task1.y"
  {
      (yyval.node) = makeFreeNode((yyvsp[-1].node));
  }
#line 1978 "y.tab.c"
    break;

  case 69: /* InitStmt: INITIALIZE LPAREN RPAREN  */
#line 386 "task1.y"
  {
      (yyval.node) = makeInitializeNode();
  }
#line 1986 "y.tab.c"
    break;

  case 70: /* AssgStmt: LValue ASSIGN E  */
#line 391 "task1.y"
                  { (yyval.node) = makeAssignNode((yyvsp[-2].node), (yyvsp[0].node)); }
#line 1992 "y.tab.c"
    break;

  case 71: /* AssgStmt: MUL ID ASSIGN E  */
#line 393 "task1.y"
  { 
    tnode* deref = makeDerefNode(makeVarNode((yyvsp[-2].node)->varname));
    (yyval.node) = makeAssignNode(deref, (yyvsp[0].node)); 
  }
#line 2001 "y.tab.c"
    break;

  case 72: /* AssgStmt: LValue ASSIGN ALLOC LPAREN RPAREN  */
#line 398 "task1.y"
  {
    (yyval.node) = makeAssignNode((yyvsp[-4].node), makeAllocNode((yyvsp[-4].node)));
  }
#line 2009 "y.tab.c"
    break;

  case 73: /* LValue: ID  */
#line 405 "task1.y"
  {
    (yyval.node) = makeVarNode((yyvsp[0].node)->varname);
  }
#line 2017 "y.tab.c"
    break;

  case 74: /* LValue: ID LSQBR E RSQBR  */
#line 409 "task1.y"
  {
    (yyval.node) = makeArrayNode((yyvsp[-3].node), (yyvsp[-1].node));
  }
#line 2025 "y.tab.c"
    break;

  case 76: /* FieldAccess: ID DOT ID  */
#line 417 "task1.y"
  {
    tnode *base = makeVarNode((yyvsp[-2].node)->varname);
    (yyval.node) = makeFieldNode(base, (yyvsp[0].node)->varname);
  }
#line 2034 "y.tab.c"
    break;

  case 77: /* FieldAccess: FieldAccess DOT ID  */
#line 422 "task1.y"
  {
    (yyval.node) = makeFieldNode((yyvsp[-2].node), (yyvsp[0].node)->varname);
  }
#line 2042 "y.tab.c"
    break;

  case 78: /* IfStmt: IF LPAREN E RPAREN THEN Slist ELSE Slist ENDIF  */
#line 428 "task1.y"
                                                 { (yyval.node) = makeIfElseNode((yyvsp[-6].node), (yyvsp[-3].node), (yyvsp[-1].node)); }
#line 2048 "y.tab.c"
    break;

  case 79: /* IfStmt: IF LPAREN E RPAREN THEN Slist ENDIF  */
#line 429 "task1.y"
                                        { (yyval.node) = makeIfNode((yyvsp[-4].node), (yyvsp[-1].node)); }
#line 2054 "y.tab.c"
    break;

  case 80: /* WhileStmt: WHILE LPAREN E RPAREN DO Slist ENDWHILE  */
#line 433 "task1.y"
                                          { (yyval.node) = makeWhileNode((yyvsp[-4].node), (yyvsp[-1].node)); }
#line 2060 "y.tab.c"
    break;

  case 81: /* BreakStmt: BREAK  */
#line 437 "task1.y"
        { (yyval.node) = makeBreakNode(); }
#line 2066 "y.tab.c"
    break;

  case 82: /* ContinueStmt: CONTINUE  */
#line 441 "task1.y"
           { (yyval.node) = makeContinueNode(); }
#line 2072 "y.tab.c"
    break;

  case 83: /* E: E PLUS E  */
#line 445 "task1.y"
           { (yyval.node) = makeArithNode(NODE_PLUS, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2078 "y.tab.c"
    break;

  case 84: /* E: E MINUS E  */
#line 446 "task1.y"
              { (yyval.node) = makeArithNode(NODE_MINUS, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2084 "y.tab.c"
    break;

  case 85: /* E: E MUL E  */
#line 447 "task1.y"
            { (yyval.node) = makeArithNode(NODE_MUL, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2090 "y.tab.c"
    break;

  case 86: /* E: E DIV E  */
#line 448 "task1.y"
            { (yyval.node) = makeArithNode(NODE_DIV, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2096 "y.tab.c"
    break;

  case 87: /* E: E LT E  */
#line 449 "task1.y"
           { (yyval.node) = makeBoolNode(NODE_LT, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2102 "y.tab.c"
    break;

  case 88: /* E: E GT E  */
#line 450 "task1.y"
           { (yyval.node) = makeBoolNode(NODE_GT, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2108 "y.tab.c"
    break;

  case 89: /* E: E EQ E  */
#line 451 "task1.y"
           { (yyval.node) = makeBoolNode(NODE_EQ, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2114 "y.tab.c"
    break;

  case 90: /* E: E LE E  */
#line 452 "task1.y"
           { (yyval.node) = makeBoolNode(NODE_LE, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2120 "y.tab.c"
    break;

  case 91: /* E: E GE E  */
#line 453 "task1.y"
           { (yyval.node) = makeBoolNode(NODE_GE, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2126 "y.tab.c"
    break;

  case 92: /* E: E NE E  */
#line 454 "task1.y"
           { (yyval.node) = makeBoolNode(NODE_NE, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2132 "y.tab.c"
    break;

  case 93: /* E: E AND E  */
#line 455 "task1.y"
            { (yyval.node) = makeBoolNode(NODE_AND, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2138 "y.tab.c"
    break;

  case 94: /* E: E OR E  */
#line 456 "task1.y"
            { (yyval.node) = makeBoolNode(NODE_OR, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2144 "y.tab.c"
    break;

  case 95: /* E: NOT E  */
#line 457 "task1.y"
            { (yyval.node) = makeNotNode((yyvsp[0].node)); }
#line 2150 "y.tab.c"
    break;

  case 96: /* E: NUM  */
#line 458 "task1.y"
        { (yyval.node) = (yyvsp[0].node); }
#line 2156 "y.tab.c"
    break;

  case 97: /* E: STRING  */
#line 459 "task1.y"
           { (yyval.node) = (yyvsp[0].node); }
#line 2162 "y.tab.c"
    break;

  case 98: /* E: NULLVAL  */
#line 460 "task1.y"
               { (yyval.node) = makeNullNode(); }
#line 2168 "y.tab.c"
    break;

  case 99: /* E: ID  */
#line 461 "task1.y"
       { (yyval.node) = makeVarNode((yyvsp[0].node)->varname); }
#line 2174 "y.tab.c"
    break;

  case 100: /* E: ID LPAREN ArgList RPAREN  */
#line 462 "task1.y"
                             { (yyval.node) = makeFuncallNode((yyvsp[-3].node)->varname, (yyvsp[-1].node)); }
#line 2180 "y.tab.c"
    break;

  case 101: /* E: ID LPAREN RPAREN  */
#line 463 "task1.y"
                     { (yyval.node) = makeFuncallNode((yyvsp[-2].node)->varname, NULL); }
#line 2186 "y.tab.c"
    break;

  case 102: /* E: MUL E  */
#line 464 "task1.y"
                      { (yyval.node) = makeDerefNode((yyvsp[0].node)); }
#line 2192 "y.tab.c"
    break;

  case 103: /* E: ADDRESS_OF ID  */
#line 465 "task1.y"
                              { (yyval.node) = makePointerNode(makeVarNode((yyvsp[0].node)->varname)); }
#line 2198 "y.tab.c"
    break;

  case 104: /* E: LPAREN E RPAREN  */
#line 466 "task1.y"
                    { (yyval.node) = (yyvsp[-1].node); }
#line 2204 "y.tab.c"
    break;

  case 105: /* E: ID LSQBR E RSQBR  */
#line 467 "task1.y"
                     { (yyval.node) = makeArrayNode((yyvsp[-3].node), (yyvsp[-1].node)); }
#line 2210 "y.tab.c"
    break;

  case 107: /* ArgList: ArgList COMMA E  */
#line 472 "task1.y"
                  { (yyval.node) = makeConnectorNode((yyvsp[-2].node), (yyvsp[0].node)); }
#line 2216 "y.tab.c"
    break;

  case 108: /* ArgList: E  */
#line 473 "task1.y"
      { (yyval.node) = (yyvsp[0].node); }
#line 2222 "y.tab.c"
    break;


#line 2226 "y.tab.c"

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

#line 476 "task1.y"


void yyerror(char *s) 
{
  fprintf(stderr, "Error at line %d: %s\n", lineNumber, s);
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
