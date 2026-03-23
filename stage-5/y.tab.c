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
#line 1 "task2.y"

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "tree.h"
    #include "memory.h"
    #include "yacc-helper.h"
    #include "codegeneration.h"
    #include "register.h"
    #include "labels.h"

    void yyerror(char *s);
    int yylex();
    extern FILE *yyin;
    extern int lineNumber;
    tnode *root;
    FILE *interim_file;
    char *current_function_name;
    extern char * yytext;

    // Global variable to store the type of the current declaration line
    struct TypeInfo currentTypeData;

#line 95 "y.tab.c"

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
    PLUS = 291,                    /* PLUS  */
    MINUS = 292,                   /* MINUS  */
    DIV = 293,                     /* DIV  */
    LT = 294,                      /* LT  */
    LE = 295,                      /* LE  */
    GT = 296,                      /* GT  */
    GE = 297,                      /* GE  */
    EQ = 298,                      /* EQ  */
    NE = 299,                      /* NE  */
    UNARY = 300                    /* UNARY  */
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
#define PLUS 291
#define MINUS 292
#define DIV 293
#define LT 294
#define LE 295
#define GT 296
#define GE 297
#define EQ 298
#define NE 299
#define UNARY 300

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 26 "task2.y"

    struct tnode *node;
    struct Paramstruct *param;
    struct TypeInfo typeData;

#line 244 "y.tab.c"

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
  YYSYMBOL_PLUS = 36,                      /* PLUS  */
  YYSYMBOL_MINUS = 37,                     /* MINUS  */
  YYSYMBOL_DIV = 38,                       /* DIV  */
  YYSYMBOL_LT = 39,                        /* LT  */
  YYSYMBOL_LE = 40,                        /* LE  */
  YYSYMBOL_GT = 41,                        /* GT  */
  YYSYMBOL_GE = 42,                        /* GE  */
  YYSYMBOL_EQ = 43,                        /* EQ  */
  YYSYMBOL_NE = 44,                        /* NE  */
  YYSYMBOL_UNARY = 45,                     /* UNARY  */
  YYSYMBOL_YYACCEPT = 46,                  /* $accept  */
  YYSYMBOL_Program = 47,                   /* Program  */
  YYSYMBOL_GDeclarations = 48,             /* GDeclarations  */
  YYSYMBOL_GdeclList = 49,                 /* GdeclList  */
  YYSYMBOL_GDecl = 50,                     /* GDecl  */
  YYSYMBOL_GidList = 51,                   /* GidList  */
  YYSYMBOL_Gid = 52,                       /* Gid  */
  YYSYMBOL_Type = 53,                      /* Type  */
  YYSYMBOL_ParamList = 54,                 /* ParamList  */
  YYSYMBOL_Param = 55,                     /* Param  */
  YYSYMBOL_FdefBlock = 56,                 /* FdefBlock  */
  YYSYMBOL_Fdef = 57,                      /* Fdef  */
  YYSYMBOL_58_1 = 58,                      /* $@1  */
  YYSYMBOL_LdeclBlock = 59,                /* LdeclBlock  */
  YYSYMBOL_LdeclList = 60,                 /* LdeclList  */
  YYSYMBOL_LDecl = 61,                     /* LDecl  */
  YYSYMBOL_IdList = 62,                    /* IdList  */
  YYSYMBOL_MainBlock = 63,                 /* MainBlock  */
  YYSYMBOL_64_2 = 64,                      /* $@2  */
  YYSYMBOL_Body = 65,                      /* Body  */
  YYSYMBOL_Slist = 66,                     /* Slist  */
  YYSYMBOL_Stmt = 67,                      /* Stmt  */
  YYSYMBOL_InputStmt = 68,                 /* InputStmt  */
  YYSYMBOL_OutputStmt = 69,                /* OutputStmt  */
  YYSYMBOL_AssgStmt = 70,                  /* AssgStmt  */
  YYSYMBOL_IfStmt = 71,                    /* IfStmt  */
  YYSYMBOL_WhileStmt = 72,                 /* WhileStmt  */
  YYSYMBOL_BreakStmt = 73,                 /* BreakStmt  */
  YYSYMBOL_ContinueStmt = 74,              /* ContinueStmt  */
  YYSYMBOL_E = 75,                         /* E  */
  YYSYMBOL_ArgList = 76                    /* ArgList  */
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
#define YYFINAL  11
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   358

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  46
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  31
/* YYNRULES -- Number of rules.  */
#define YYNRULES  86
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  192

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   300


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
      45
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    49,    49,    50,    54,    58,    59,    63,    64,    68,
      72,    73,    77,    82,    86,    90,    94,   101,   105,   109,
     116,   117,   121,   125,   126,   131,   130,   156,   181,   182,
     183,   187,   188,   192,   196,   201,   209,   208,   239,   240,
     244,   245,   249,   250,   251,   252,   253,   254,   255,   256,
     257,   261,   262,   263,   264,   272,   276,   277,   278,   279,
     287,   288,   292,   296,   300,   304,   305,   306,   307,   308,
     309,   310,   311,   312,   313,   314,   315,   316,   317,   318,
     319,   320,   321,   322,   323,   327,   328
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
  "MUL", "PLUS", "MINUS", "DIV", "LT", "LE", "GT", "GE", "EQ", "NE",
  "UNARY", "$accept", "Program", "GDeclarations", "GdeclList", "GDecl",
  "GidList", "Gid", "Type", "ParamList", "Param", "FdefBlock", "Fdef",
  "$@1", "LdeclBlock", "LdeclList", "LDecl", "IdList", "MainBlock", "$@2",
  "Body", "Slist", "Stmt", "InputStmt", "OutputStmt", "AssgStmt", "IfStmt",
  "WhileStmt", "BreakStmt", "ContinueStmt", "E", "ArgList", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-165)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  ((Yyn) == YYTABLE_NINF)

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      -2,    64,    18,    73,  -165,  -165,  -165,   160,    94,  -165,
      59,  -165,    97,   115,    73,  -165,  -165,  -165,  -165,  -165,
      -4,   144,  -165,  -165,   109,  -165,  -165,   148,   139,  -165,
      59,   122,   156,  -165,   167,    21,  -165,   141,  -165,   157,
     159,    33,  -165,   160,  -165,   155,   163,   181,  -165,  -165,
     184,   181,   110,   183,   196,   192,   183,  -165,   222,   158,
    -165,    98,   197,   181,  -165,   198,  -165,   149,  -165,  -165,
      99,  -165,   202,   214,    49,   215,   216,  -165,  -165,   240,
     111,   220,  -165,  -165,  -165,  -165,  -165,  -165,  -165,  -165,
     183,  -165,  -165,   242,    49,    49,    49,    10,  -165,    -3,
    -165,    49,   254,    49,   300,    49,    49,   226,  -165,   246,
    -165,   255,  -165,   225,   300,   161,    54,   268,    16,    49,
     178,  -165,  -165,    49,    49,    49,    49,    49,    49,    49,
      49,    49,    49,   195,   212,    49,  -165,  -165,   125,  -165,
    -165,    49,   256,  -165,   300,    47,   238,  -165,   138,   310,
     310,   138,   168,   168,   168,   168,   168,   168,   280,   289,
     300,    49,    49,   251,  -165,    49,  -165,   267,   137,   137,
     264,   300,    75,   300,    49,    74,    42,   278,  -165,    49,
     277,   137,  -165,  -165,    49,   290,  -165,   124,   300,   295,
    -165,  -165
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       6,     0,     0,     0,    17,    18,     5,     0,     0,     8,
       0,     1,    17,     0,     0,    24,     3,    19,     4,     7,
      12,     0,    11,    36,     0,    23,     2,     0,     0,     9,
       0,     0,     0,    16,     0,     0,    21,     0,    10,     0,
       0,     0,    22,     0,    15,    13,     0,    30,    25,    20,
       0,    30,     0,     0,     0,     0,     0,    29,     0,     0,
      32,     0,     0,    30,    14,     0,    35,     0,    28,    31,
       0,    39,     0,     0,    50,     0,     0,    63,    64,     0,
       0,     0,    42,    43,    44,    45,    46,    47,    48,    27,
       0,    37,    33,     0,     0,     0,     0,     0,    75,    77,
      76,     0,     0,     0,    49,     0,     0,     0,    38,     0,
      41,     0,    34,     0,    56,     0,     0,     0,     0,     0,
       0,    81,    80,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    40,    26,     0,    55,
      51,     0,     0,    79,    86,     0,     0,    82,    67,    65,
      66,    68,    69,    72,    70,    73,    71,    74,     0,     0,
      59,     0,     0,     0,    54,     0,    78,    83,     0,     0,
       0,    57,     0,    85,     0,     0,     0,     0,    52,     0,
       0,     0,    61,    62,     0,     0,    84,     0,    58,     0,
      60,    53
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -165,  -165,  -165,  -165,   316,  -165,   317,     8,   314,   312,
    -165,   342,  -165,   -22,  -165,   298,  -165,   344,  -165,   -50,
    -164,   -80,  -165,  -165,  -165,  -165,  -165,  -165,  -165,   -93,
    -165
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     2,     3,     8,     9,    21,    22,    34,    35,    36,
      14,    15,    54,    53,    59,    60,    67,    16,    31,    62,
      80,    81,    82,    83,    84,    85,    86,    87,    88,   104,
     145
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     109,   113,   114,   115,   175,   176,    65,     1,   120,    10,
     122,    13,   133,   134,   116,    17,    10,   187,    11,    98,
      99,   100,    13,    27,   118,   144,   146,    28,   119,    56,
     148,   149,   150,   151,   152,   153,   154,   155,   156,   157,
     111,    90,   160,   101,   143,   117,    70,    43,   163,    44,
     102,   103,    98,    99,   100,    72,    73,    74,    75,    43,
      58,    48,    76,    20,   183,    77,    78,    58,   170,   171,
       4,     5,   173,   165,     6,   166,   101,    79,    70,    12,
       5,   180,   140,   102,   103,   141,   185,    72,    73,    74,
      75,   188,   181,   182,    76,   109,   109,    77,    78,     7,
       4,     5,    70,   178,    18,    23,   179,   109,     7,    79,
      71,    72,    73,    74,    75,    70,     4,     5,    76,    24,
      57,    77,    78,   108,    72,    73,    74,    75,    70,     7,
      94,    76,    95,    79,    77,    78,    32,    72,    73,    74,
      75,    70,    37,   190,    76,     7,    79,    77,    78,    39,
      72,    73,    74,    75,     4,     5,   161,    76,   162,    79,
      77,    78,     4,     5,     4,     5,     4,     5,    68,    29,
      30,    42,    79,    45,    92,    93,    33,   127,   128,   129,
     130,   131,   132,     7,    40,    46,    50,    55,    47,   139,
      52,     7,    51,     7,    61,     7,   123,   124,   125,   126,
     127,   128,   129,   130,   131,   132,   147,    -1,    -1,    -1,
      -1,    -1,    -1,   123,   124,   125,   126,   127,   128,   129,
     130,   131,   132,   158,    64,    63,    66,    89,    91,    96,
     123,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     159,    97,   105,   106,   107,   110,   112,   123,   124,   125,
     126,   127,   128,   129,   130,   131,   132,   138,   121,   135,
     123,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     167,   136,   142,   123,   124,   125,   126,   127,   128,   129,
     130,   131,   132,   172,   164,   137,   123,   124,   125,   126,
     127,   128,   129,   130,   131,   132,   177,   168,   174,   123,
     124,   125,   126,   127,   128,   129,   130,   131,   132,   186,
     169,   184,   123,   124,   125,   126,   127,   128,   129,   130,
     131,   132,   189,   191,    19,   123,   124,   125,   126,   127,
     128,   129,   130,   131,   132,   123,   124,   125,   126,   127,
     128,   129,   130,   131,   132,   123,    41,    38,   126,   127,
     128,   129,   130,   131,   132,    49,    25,    69,    26
};

static const yytype_uint8 yycheck[] =
{
      80,    94,    95,    96,   168,   169,    56,     9,   101,     1,
     103,     3,   105,   106,     4,     7,     8,   181,     0,     3,
       4,     5,    14,    27,    27,   118,   119,    31,    31,    51,
     123,   124,   125,   126,   127,   128,   129,   130,   131,   132,
      90,    63,   135,    27,    28,    35,     4,    26,   141,    28,
      34,    35,     3,     4,     5,    13,    14,    15,    16,    26,
      52,    28,    20,     4,    22,    23,    24,    59,   161,   162,
       6,     7,   165,    26,    10,    28,    27,    35,     4,     6,
       7,   174,    28,    34,    35,    31,   179,    13,    14,    15,
      16,   184,    18,    19,    20,   175,   176,    23,    24,    35,
       6,     7,     4,    28,    10,     8,    31,   187,    35,    35,
      12,    13,    14,    15,    16,     4,     6,     7,    20,     4,
      10,    23,    24,    12,    13,    14,    15,    16,     4,    35,
      31,    20,    33,    35,    23,    24,    27,    13,    14,    15,
      16,     4,     3,    19,    20,    35,    35,    23,    24,    27,
      13,    14,    15,    16,     6,     7,    31,    20,    33,    35,
      23,    24,     6,     7,     6,     7,     6,     7,    10,    25,
      26,     4,    35,    32,    25,    26,    28,    39,    40,    41,
      42,    43,    44,    35,    28,    28,    31,     3,    29,    28,
       9,    35,    29,    35,    11,    35,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    28,    39,    40,    41,
      42,    43,    44,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    28,    32,    29,     4,    30,    30,    27,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      28,    27,    27,    27,     4,    25,     4,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    32,     4,    33,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      32,    25,     4,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    32,    28,    30,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    32,    17,    31,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    32,
      21,    33,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    32,    28,     8,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    35,    32,    30,    38,    39,
      40,    41,    42,    43,    44,    43,    14,    59,    14
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     9,    47,    48,     6,     7,    10,    35,    49,    50,
      53,     0,     6,    53,    56,    57,    63,    53,    10,    50,
       4,    51,    52,     8,     4,    57,    63,    27,    31,    25,
      26,    64,    27,    28,    53,    54,    55,     3,    52,    27,
      28,    54,     4,    26,    28,    32,    28,    29,    28,    55,
      31,    29,     9,    59,    58,     3,    59,    10,    53,    60,
      61,    11,    65,    29,    32,    65,     4,    62,    10,    61,
       4,    12,    13,    14,    15,    16,    20,    23,    24,    35,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    30,
      59,    30,    25,    26,    31,    33,    27,    27,     3,     4,
       5,    27,    34,    35,    75,    27,    27,     4,    12,    67,
      25,    65,     4,    75,    75,    75,     4,    35,    27,    31,
      75,     4,    75,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    75,    75,    33,    25,    30,    32,    28,
      28,    31,     4,    28,    75,    76,    75,    28,    75,    75,
      75,    75,    75,    75,    75,    75,    75,    75,    28,    28,
      75,    31,    33,    75,    28,    26,    28,    32,    17,    21,
      75,    75,    32,    75,    31,    66,    66,    32,    28,    31,
      75,    18,    19,    22,    33,    75,    32,    66,    75,    32,
      19,    28
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    46,    47,    47,    48,    48,    48,    49,    49,    50,
      51,    51,    52,    52,    52,    52,    52,    53,    53,    53,
      54,    54,    55,    56,    56,    58,    57,    57,    59,    59,
      59,    60,    60,    61,    62,    62,    64,    63,    65,    65,
      66,    66,    67,    67,    67,    67,    67,    67,    67,    67,
      67,    68,    68,    68,    68,    69,    70,    70,    70,    70,
      71,    71,    72,    73,    74,    75,    75,    75,    75,    75,
      75,    75,    75,    75,    75,    75,    75,    75,    75,    75,
      75,    75,    75,    75,    75,    76,    76
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     3,     2,     3,     2,     0,     2,     1,     3,
       3,     1,     1,     4,     7,     4,     3,     1,     1,     2,
       3,     1,     2,     2,     1,     0,    10,     8,     3,     2,
       0,     2,     1,     3,     3,     1,     0,     9,     3,     2,
       3,     2,     1,     1,     1,     1,     1,     1,     1,     2,
       1,     4,     7,    10,     5,     4,     3,     6,     9,     4,
       9,     7,     7,     1,     1,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     1,     1,     1,     4,     3,
       2,     2,     3,     4,     7,     3,     1
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
  case 2: /* Program: GDeclarations FdefBlock MainBlock  */
#line 49 "task2.y"
                                      { root = (yyvsp[0].node); }
#line 1456 "y.tab.c"
    break;

  case 3: /* Program: GDeclarations MainBlock  */
#line 50 "task2.y"
                            { root = (yyvsp[0].node); }
#line 1462 "y.tab.c"
    break;

  case 4: /* GDeclarations: DECL GdeclList ENDDECL  */
#line 55 "task2.y"
    { 
      handleGdeclComplete(); 
    }
#line 1470 "y.tab.c"
    break;

  case 12: /* Gid: ID  */
#line 78 "task2.y"
  { 
    // Uses the global currentTypeData instead of stack reference
    handleGidScalar((yyvsp[0].node), &currentTypeData); 
  }
#line 1479 "y.tab.c"
    break;

  case 13: /* Gid: ID LSQBR NUM RSQBR  */
#line 83 "task2.y"
  { 
    handleGidArray1D((yyvsp[-3].node), &currentTypeData, (yyvsp[-1].node)->val); 
  }
#line 1487 "y.tab.c"
    break;

  case 14: /* Gid: ID LSQBR NUM RSQBR LSQBR NUM RSQBR  */
#line 87 "task2.y"
  { 
    handleGidArray2D((yyvsp[-6].node), &currentTypeData, (yyvsp[-4].node)->val, (yyvsp[-1].node)->val); 
  }
#line 1495 "y.tab.c"
    break;

  case 15: /* Gid: ID LPAREN ParamList RPAREN  */
#line 91 "task2.y"
  { 
    handleGidFunction((yyvsp[-3].node), &currentTypeData, (yyvsp[-1].param)); 
  }
#line 1503 "y.tab.c"
    break;

  case 16: /* Gid: ID LPAREN RPAREN  */
#line 95 "task2.y"
  { 
    handleGidFunction((yyvsp[-2].node), &currentTypeData, NULL); 
  }
#line 1511 "y.tab.c"
    break;

  case 17: /* Type: INT  */
#line 101 "task2.y"
      { 
      (yyval.typeData).type = TYPE_INT; (yyval.typeData).ptrLevel = 0; 
      currentTypeData = (yyval.typeData); 
  }
#line 1520 "y.tab.c"
    break;

  case 18: /* Type: STR  */
#line 105 "task2.y"
        { 
      (yyval.typeData).type = TYPE_STRING; (yyval.typeData).ptrLevel = 0; 
      currentTypeData = (yyval.typeData); 
  }
#line 1529 "y.tab.c"
    break;

  case 19: /* Type: MUL Type  */
#line 109 "task2.y"
             { 
      (yyval.typeData) = (yyvsp[0].typeData); (yyval.typeData).ptrLevel++; 
      currentTypeData = (yyval.typeData); 
  }
#line 1538 "y.tab.c"
    break;

  case 20: /* ParamList: ParamList COMMA Param  */
#line 116 "task2.y"
                        { (yyval.param) = AppendParam((yyvsp[-2].param), (yyvsp[0].param)); }
#line 1544 "y.tab.c"
    break;

  case 21: /* ParamList: Param  */
#line 117 "task2.y"
          { (yyval.param) = (yyvsp[0].param); }
#line 1550 "y.tab.c"
    break;

  case 22: /* Param: Type ID  */
#line 121 "task2.y"
          { (yyval.param) = CreateParam((yyvsp[0].node)->varname, (yyvsp[-1].typeData).type, (yyvsp[-1].typeData).ptrLevel); }
#line 1556 "y.tab.c"
    break;

  case 25: /* $@1: %empty  */
#line 131 "task2.y"
  {
    handleParamInstall((yyvsp[-1].param));
    
    current_function_name = (yyvsp[-3].node)->varname;
  }
#line 1566 "y.tab.c"
    break;

  case 26: /* Fdef: Type ID LPAREN ParamList RPAREN $@1 LBRACE LdeclBlock Body RBRACE  */
#line 137 "task2.y"
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

    current_function_name = NULL;

    // Now it is expected that all functions have a return statement(empty or not)
    resetLocalSymbolTable();
  }
#line 1590 "y.tab.c"
    break;

  case 27: /* Fdef: Type ID LPAREN RPAREN LBRACE LdeclBlock Body RBRACE  */
#line 157 "task2.y"
  {
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

    current_function_name = NULL;

    // Now it is expected that all functions have a return statement(empty or not)
    resetLocalSymbolTable();
  }
#line 1616 "y.tab.c"
    break;

  case 34: /* IdList: IdList COMMA ID  */
#line 197 "task2.y"
  { 
    // Uses the global currentTypeData
    handleLidInstall((yyvsp[0].node)->varname, &currentTypeData); 
  }
#line 1625 "y.tab.c"
    break;

  case 35: /* IdList: ID  */
#line 202 "task2.y"
  { 
    handleLidInstall((yyvsp[0].node)->varname, &currentTypeData); 
  }
#line 1633 "y.tab.c"
    break;

  case 36: /* $@2: %empty  */
#line 209 "task2.y"
  {
    current_function_name = "MAIN";
  }
#line 1641 "y.tab.c"
    break;

  case 37: /* MainBlock: INT MAIN $@2 LPAREN RPAREN LBRACE LdeclBlock Body RBRACE  */
#line 213 "task2.y"
  { 
    // Set current function name for main
    
    
    handleMainPrint((yyvsp[-1].node)); 
    (yyval.node) = (yyvsp[-1].node); 

    fprintf(interim_file, "MAIN:\n");
    moveStackPointer(interim_file);
    fprintf(interim_file, "BRKP\n");
    fprintf(interim_file, "PUSH BP\n");
    fprintf(interim_file, "MOV BP, SP\n");
    
    locAlloc(interim_file);

    codeGen((yyval.node), interim_file);

    // Clear current function name
    current_function_name = NULL;

    // Now it is expected that all functions have a return statement(empty or not)
    resetLocalSymbolTable();
  }
#line 1669 "y.tab.c"
    break;

  case 38: /* Body: kBEGIN Slist kEND  */
#line 239 "task2.y"
                    { (yyval.node) = (yyvsp[-1].node); }
#line 1675 "y.tab.c"
    break;

  case 39: /* Body: kBEGIN kEND  */
#line 240 "task2.y"
                { (yyval.node) = NULL; }
#line 1681 "y.tab.c"
    break;

  case 40: /* Slist: Slist Stmt SEMICOLON  */
#line 244 "task2.y"
                       { (yyval.node) = makeConnectorNode((yyvsp[-2].node), (yyvsp[-1].node)); }
#line 1687 "y.tab.c"
    break;

  case 41: /* Slist: Stmt SEMICOLON  */
#line 245 "task2.y"
                   { (yyval.node) = (yyvsp[-1].node); }
#line 1693 "y.tab.c"
    break;

  case 42: /* Stmt: InputStmt  */
#line 249 "task2.y"
            { (yyval.node) = (yyvsp[0].node); }
#line 1699 "y.tab.c"
    break;

  case 43: /* Stmt: OutputStmt  */
#line 250 "task2.y"
               { (yyval.node) = (yyvsp[0].node); }
#line 1705 "y.tab.c"
    break;

  case 44: /* Stmt: AssgStmt  */
#line 251 "task2.y"
             { (yyval.node) = (yyvsp[0].node); }
#line 1711 "y.tab.c"
    break;

  case 45: /* Stmt: IfStmt  */
#line 252 "task2.y"
           { (yyval.node) = (yyvsp[0].node); }
#line 1717 "y.tab.c"
    break;

  case 46: /* Stmt: WhileStmt  */
#line 253 "task2.y"
              { (yyval.node) = (yyvsp[0].node); }
#line 1723 "y.tab.c"
    break;

  case 47: /* Stmt: BreakStmt  */
#line 254 "task2.y"
              { (yyval.node) = (yyvsp[0].node); }
#line 1729 "y.tab.c"
    break;

  case 48: /* Stmt: ContinueStmt  */
#line 255 "task2.y"
                 { (yyval.node) = (yyvsp[0].node); }
#line 1735 "y.tab.c"
    break;

  case 49: /* Stmt: RETURN E  */
#line 256 "task2.y"
             { (yyval.node) = makeReturnNode((yyvsp[0].node), current_function_name); }
#line 1741 "y.tab.c"
    break;

  case 50: /* Stmt: RETURN  */
#line 257 "task2.y"
           { (yyval.node) = makeReturnNode(NULL, current_function_name); }
#line 1747 "y.tab.c"
    break;

  case 51: /* InputStmt: READ LPAREN ID RPAREN  */
#line 261 "task2.y"
                        { (yyval.node) = makeReadNode(makeVarNode((yyvsp[-1].node)->varname)); }
#line 1753 "y.tab.c"
    break;

  case 52: /* InputStmt: READ LPAREN ID LSQBR E RSQBR RPAREN  */
#line 262 "task2.y"
                                        { (yyval.node) = makeReadNode(makeArrayNode((yyvsp[-4].node), (yyvsp[-2].node))); }
#line 1759 "y.tab.c"
    break;

  case 53: /* InputStmt: READ LPAREN ID LSQBR E RSQBR LSQBR E RSQBR RPAREN  */
#line 263 "task2.y"
                                                      { (yyval.node) = makeReadNode(make2dArrayNode((yyvsp[-7].node), (yyvsp[-5].node), (yyvsp[-2].node))); }
#line 1765 "y.tab.c"
    break;

  case 54: /* InputStmt: READ LPAREN MUL ID RPAREN  */
#line 265 "task2.y"
  { 
    tnode* ptr_node = makeVarNode((yyvsp[-1].node)->varname);
    (yyval.node) = makeReadNode(makeDerefNode(ptr_node)); 
  }
#line 1774 "y.tab.c"
    break;

  case 55: /* OutputStmt: WRITE LPAREN E RPAREN  */
#line 272 "task2.y"
                        { (yyval.node) = makeWriteNode((yyvsp[-1].node)); }
#line 1780 "y.tab.c"
    break;

  case 56: /* AssgStmt: ID ASSIGN E  */
#line 276 "task2.y"
              { (yyval.node) = makeAssignNode(makeVarNode((yyvsp[-2].node)->varname), (yyvsp[0].node)); }
#line 1786 "y.tab.c"
    break;

  case 57: /* AssgStmt: ID LSQBR E RSQBR ASSIGN E  */
#line 277 "task2.y"
                              { (yyval.node) = makeArrayAssignNode(makeArrayNode((yyvsp[-5].node), (yyvsp[-3].node)), (yyvsp[0].node)); }
#line 1792 "y.tab.c"
    break;

  case 58: /* AssgStmt: ID LSQBR E RSQBR LSQBR E RSQBR ASSIGN E  */
#line 278 "task2.y"
                                            { (yyval.node) = makeArray2DAssignNode(make2dArrayNode((yyvsp[-8].node), (yyvsp[-6].node), (yyvsp[-3].node)), (yyvsp[0].node)); }
#line 1798 "y.tab.c"
    break;

  case 59: /* AssgStmt: MUL ID ASSIGN E  */
#line 280 "task2.y"
  { 
    tnode* deref = makeDerefNode(makeVarNode((yyvsp[-2].node)->varname));
    (yyval.node) = makeAssignNode(deref, (yyvsp[0].node)); 
  }
#line 1807 "y.tab.c"
    break;

  case 60: /* IfStmt: IF LPAREN E RPAREN THEN Slist ELSE Slist ENDIF  */
#line 287 "task2.y"
                                                 { (yyval.node) = makeIfElseNode((yyvsp[-6].node), (yyvsp[-3].node), (yyvsp[-1].node)); }
#line 1813 "y.tab.c"
    break;

  case 61: /* IfStmt: IF LPAREN E RPAREN THEN Slist ENDIF  */
#line 288 "task2.y"
                                        { (yyval.node) = makeIfNode((yyvsp[-4].node), (yyvsp[-1].node)); }
#line 1819 "y.tab.c"
    break;

  case 62: /* WhileStmt: WHILE LPAREN E RPAREN DO Slist ENDWHILE  */
#line 292 "task2.y"
                                          { (yyval.node) = makeWhileNode((yyvsp[-4].node), (yyvsp[-1].node)); }
#line 1825 "y.tab.c"
    break;

  case 63: /* BreakStmt: BREAK  */
#line 296 "task2.y"
        { (yyval.node) = makeBreakNode(); }
#line 1831 "y.tab.c"
    break;

  case 64: /* ContinueStmt: CONTINUE  */
#line 300 "task2.y"
           { (yyval.node) = makeContinueNode(); }
#line 1837 "y.tab.c"
    break;

  case 65: /* E: E PLUS E  */
#line 304 "task2.y"
           { (yyval.node) = makeArithNode(NODE_PLUS, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1843 "y.tab.c"
    break;

  case 66: /* E: E MINUS E  */
#line 305 "task2.y"
              { (yyval.node) = makeArithNode(NODE_MINUS, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1849 "y.tab.c"
    break;

  case 67: /* E: E MUL E  */
#line 306 "task2.y"
            { (yyval.node) = makeArithNode(NODE_MUL, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1855 "y.tab.c"
    break;

  case 68: /* E: E DIV E  */
#line 307 "task2.y"
            { (yyval.node) = makeArithNode(NODE_DIV, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1861 "y.tab.c"
    break;

  case 69: /* E: E LT E  */
#line 308 "task2.y"
           { (yyval.node) = makeBoolNode(NODE_LT, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1867 "y.tab.c"
    break;

  case 70: /* E: E GT E  */
#line 309 "task2.y"
           { (yyval.node) = makeBoolNode(NODE_GT, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1873 "y.tab.c"
    break;

  case 71: /* E: E EQ E  */
#line 310 "task2.y"
           { (yyval.node) = makeBoolNode(NODE_EQ, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1879 "y.tab.c"
    break;

  case 72: /* E: E LE E  */
#line 311 "task2.y"
           { (yyval.node) = makeBoolNode(NODE_LE, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1885 "y.tab.c"
    break;

  case 73: /* E: E GE E  */
#line 312 "task2.y"
           { (yyval.node) = makeBoolNode(NODE_GE, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1891 "y.tab.c"
    break;

  case 74: /* E: E NE E  */
#line 313 "task2.y"
           { (yyval.node) = makeBoolNode(NODE_NE, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1897 "y.tab.c"
    break;

  case 75: /* E: NUM  */
#line 314 "task2.y"
        { (yyval.node) = (yyvsp[0].node); }
#line 1903 "y.tab.c"
    break;

  case 76: /* E: STRING  */
#line 315 "task2.y"
           { (yyval.node) = (yyvsp[0].node); }
#line 1909 "y.tab.c"
    break;

  case 77: /* E: ID  */
#line 316 "task2.y"
       { (yyval.node) = makeVarNode((yyvsp[0].node)->varname); }
#line 1915 "y.tab.c"
    break;

  case 78: /* E: ID LPAREN ArgList RPAREN  */
#line 317 "task2.y"
                             { (yyval.node) = makeFuncallNode((yyvsp[-3].node)->varname, (yyvsp[-1].node)); }
#line 1921 "y.tab.c"
    break;

  case 79: /* E: ID LPAREN RPAREN  */
#line 318 "task2.y"
                     { (yyval.node) = makeFuncallNode((yyvsp[-2].node)->varname, NULL); }
#line 1927 "y.tab.c"
    break;

  case 80: /* E: MUL E  */
#line 319 "task2.y"
                      { (yyval.node) = makeDerefNode((yyvsp[0].node)); }
#line 1933 "y.tab.c"
    break;

  case 81: /* E: ADDRESS_OF ID  */
#line 320 "task2.y"
                              { (yyval.node) = makePointerNode(makeVarNode((yyvsp[0].node)->varname)); }
#line 1939 "y.tab.c"
    break;

  case 82: /* E: LPAREN E RPAREN  */
#line 321 "task2.y"
                    { (yyval.node) = (yyvsp[-1].node); }
#line 1945 "y.tab.c"
    break;

  case 83: /* E: ID LSQBR E RSQBR  */
#line 322 "task2.y"
                     { (yyval.node) = makeArrayNode((yyvsp[-3].node), (yyvsp[-1].node)); }
#line 1951 "y.tab.c"
    break;

  case 84: /* E: ID LSQBR E RSQBR LSQBR E RSQBR  */
#line 323 "task2.y"
                                   { (yyval.node) = make2dArrayNode((yyvsp[-6].node), (yyvsp[-4].node), (yyvsp[-1].node)); }
#line 1957 "y.tab.c"
    break;

  case 85: /* ArgList: ArgList COMMA E  */
#line 327 "task2.y"
                  { (yyval.node) = makeConnectorNode((yyvsp[-2].node), (yyvsp[0].node)); }
#line 1963 "y.tab.c"
    break;

  case 86: /* ArgList: E  */
#line 328 "task2.y"
      { (yyval.node) = (yyvsp[0].node); }
#line 1969 "y.tab.c"
    break;


#line 1973 "y.tab.c"

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

#line 331 "task2.y"


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

  initReg();
  fileinit(interim_file);
  
  // Initialize current function name
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
