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
    #include "tree.h"
    #include "register.h"
    #include "labels.h"
    #include "memory.h"
    #include "codegeneration.h"

    void printAST(struct tnode* t, int level);

    int currentType;
    int ptrLevel = 0; 

    // #define DEBUG // for debugging(comment when not needed)

    tnode *root;   /* The root of the AST */

    FILE *target_file;
    extern FILE *yyin;

    int yylex();
    void yyerror(char *s);
    extern char * yytext;
    extern int lineNumber;


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
  YYSYMBOL_ADDRESS_OF = 8,                 /* ADDRESS_OF  */
  YYSYMBOL_PLUS = 9,                       /* PLUS  */
  YYSYMBOL_MINUS = 10,                     /* MINUS  */
  YYSYMBOL_MUL = 11,                       /* MUL  */
  YYSYMBOL_DIV = 12,                       /* DIV  */
  YYSYMBOL_LT = 13,                        /* LT  */
  YYSYMBOL_LE = 14,                        /* LE  */
  YYSYMBOL_GT = 15,                        /* GT  */
  YYSYMBOL_GE = 16,                        /* GE  */
  YYSYMBOL_EQ = 17,                        /* EQ  */
  YYSYMBOL_NE = 18,                        /* NE  */
  YYSYMBOL_LPAREN = 19,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 20,                    /* RPAREN  */
  YYSYMBOL_ASSIGN = 21,                    /* ASSIGN  */
  YYSYMBOL_SEMICOLON = 22,                 /* SEMICOLON  */
  YYSYMBOL_COMMA = 23,                     /* COMMA  */
  YYSYMBOL_RSQBR = 24,                     /* RSQBR  */
  YYSYMBOL_LSQBR = 25,                     /* LSQBR  */
  YYSYMBOL_kBEGIN = 26,                    /* kBEGIN  */
  YYSYMBOL_kEND = 27,                      /* kEND  */
  YYSYMBOL_WRITE = 28,                     /* WRITE  */
  YYSYMBOL_READ = 29,                      /* READ  */
  YYSYMBOL_IF = 30,                        /* IF  */
  YYSYMBOL_THEN = 31,                      /* THEN  */
  YYSYMBOL_ELSE = 32,                      /* ELSE  */
  YYSYMBOL_WHILE = 33,                     /* WHILE  */
  YYSYMBOL_ENDIF = 34,                     /* ENDIF  */
  YYSYMBOL_ENDWHILE = 35,                  /* ENDWHILE  */
  YYSYMBOL_DO = 36,                        /* DO  */
  YYSYMBOL_DECL = 37,                      /* DECL  */
  YYSYMBOL_ENDDECL = 38,                   /* ENDDECL  */
  YYSYMBOL_YYACCEPT = 39,                  /* $accept  */
  YYSYMBOL_Program = 40,                   /* Program  */
  YYSYMBOL_DeclList = 41,                  /* DeclList  */
  YYSYMBOL_Decl = 42,                      /* Decl  */
  YYSYMBOL_Type = 43,                      /* Type  */
  YYSYMBOL_VarList = 44,                   /* VarList  */
  YYSYMBOL_Slist = 45,                     /* Slist  */
  YYSYMBOL_Stmt = 46,                      /* Stmt  */
  YYSYMBOL_InputStmt = 47,                 /* InputStmt  */
  YYSYMBOL_OutputStmt = 48,                /* OutputStmt  */
  YYSYMBOL_AssgStmt = 49,                  /* AssgStmt  */
  YYSYMBOL_IfStmt = 50,                    /* IfStmt  */
  YYSYMBOL_WhileStmt = 51,                 /* WhileStmt  */
  YYSYMBOL_E = 52                          /* E  */
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
#define YYFINAL  24
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   348

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  39
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  14
/* YYNRULES -- Number of rules.  */
#define YYNRULES  58
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  148

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   293


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
      35,    36,    37,    38
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    49,    49,    53,    55,    57,    61,    62,    66,    70,
      75,    82,    90,    98,   106,   114,   122,   128,   134,   140,
     146,   159,   160,   164,   165,   166,   167,   168,   172,   173,
     174,   175,   183,   187,   201,   219,   236,   256,   265,   277,
     289,   297,   305,   313,   321,   323,   331,   339,   347,   355,
     363,   371,   372,   373,   385,   397,   413,   429,   439
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
  "INT", "STR", "ADDRESS_OF", "PLUS", "MINUS", "MUL", "DIV", "LT", "LE",
  "GT", "GE", "EQ", "NE", "LPAREN", "RPAREN", "ASSIGN", "SEMICOLON",
  "COMMA", "RSQBR", "LSQBR", "kBEGIN", "kEND", "WRITE", "READ", "IF",
  "THEN", "ELSE", "WHILE", "ENDIF", "ENDWHILE", "DO", "DECL", "ENDDECL",
  "$accept", "Program", "DeclList", "Decl", "Type", "VarList", "Slist",
  "Stmt", "InputStmt", "OutputStmt", "AssgStmt", "IfStmt", "WhileStmt",
  "E", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-33)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  ((Yyn) == YYTABLE_NINF)

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      -9,    10,    -5,    18,    45,    11,   -33,    13,    16,    56,
      63,   101,    66,   -33,   -33,   -33,   -33,   -33,   -33,   -33,
      53,     4,   -33,     9,   -33,    54,    54,    73,    54,    12,
      54,    54,   -33,    74,   -33,   129,    69,   -33,    75,    15,
      58,   -33,    76,   -33,    98,     3,    54,   310,   154,    54,
     250,    47,    99,   262,   274,   -33,   109,   129,   103,   -33,
     104,   -33,    52,    54,   -33,   -33,    54,   286,    54,    54,
      54,    54,    54,    54,    54,    54,    54,    54,    72,   310,
     -33,   -33,    54,    89,    84,    83,   -33,   121,   100,   -33,
     110,    60,   170,   298,   -33,   318,   318,   324,   324,   330,
     330,   330,   330,   330,   330,    54,    54,   186,   -33,   129,
     129,   -33,   116,   120,   -33,   122,   118,   -33,   310,   202,
      49,    57,     1,   141,   123,   -33,    54,   124,   -33,    54,
     129,   -33,   -33,   128,   130,   218,    54,   234,    88,   -33,
     143,   -33,   310,   133,   -33,   132,   -33,   -33
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     5,     0,     0,     0,
       0,     0,     0,    23,    24,    25,    26,    27,     9,    10,
       0,     0,     7,     0,     1,     0,     0,     0,     0,     0,
       0,     0,     4,     0,    22,     0,     0,     6,    20,     0,
       0,    51,    58,    52,     0,     0,     0,    33,     0,     0,
       0,     0,     0,     0,     0,    21,     0,     0,     0,    16,
       0,     8,     0,     0,    55,    56,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    36,
      32,    28,     0,     0,     0,     0,     3,     0,     0,    17,
      11,     0,     0,     0,    44,    40,    41,    42,    43,    45,
      46,    47,    48,    49,    50,     0,     0,     0,    31,     0,
       0,     2,    14,     0,    18,     0,    53,    57,    34,     0,
       0,     0,     0,     0,     0,    19,     0,     0,    29,     0,
       0,    38,    39,     0,    12,     0,     0,     0,     0,    15,
       0,    54,    35,     0,    37,     0,    30,    13
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -33,   -33,   -33,   139,   -33,   -33,   -32,   -11,   -33,   -33,
     -33,   -33,   -33,   -22
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     3,    21,    22,    23,    40,    11,    12,    13,    14,
      15,    16,    17,    47
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      33,    18,    19,    56,    48,     4,    50,    65,    53,    54,
      18,    19,     5,    38,     4,    27,    51,     1,    24,    59,
      39,     5,    66,    52,    67,    87,    60,    79,     2,     7,
       8,     9,    28,    20,    10,    29,   132,     6,     7,     8,
       9,    92,    36,    10,    93,    33,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   104,    90,    41,    42,    43,
     107,     4,    44,    91,   114,    45,    25,    81,     5,   128,
      26,   115,    82,    46,   129,    30,    33,   121,   122,    35,
      61,    62,    31,   118,   119,     7,     8,     9,    34,   130,
      10,   131,     4,   105,    49,    57,    55,   106,   138,     5,
      58,    63,    64,    83,   135,     4,    88,   137,    89,   108,
      33,    33,     5,     4,   142,   109,     7,     8,     9,   110,
       5,    10,   144,   124,   112,     4,   125,    33,    32,     7,
       8,     9,     5,     4,    10,   113,    86,     7,     8,     9,
       5,   123,    10,   126,   133,   136,   145,   134,   111,     7,
       8,     9,   139,   146,    10,   140,   147,     7,     8,     9,
      37,     0,    10,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,     0,     0,     0,     0,     0,    78,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,     0,
       0,     0,     0,     0,   116,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,     0,     0,     0,     0,     0,
     120,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,     0,     0,     0,     0,     0,   127,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,     0,     0,     0,
       0,     0,   141,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,     0,     0,     0,     0,     0,   143,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,     0,
      80,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,     0,    84,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,     0,    85,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,     0,    94,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,     0,   117,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    70,
      71,    72,    73,    74,    75,    76,    77,    72,    73,    74,
      75,    76,    77,    -1,    -1,    -1,    -1,    -1,    -1
};

static const yytype_int16 yycheck[] =
{
      11,     6,     7,    35,    26,     4,    28,     4,    30,    31,
       6,     7,    11,     4,     4,     4,     4,    26,     0,     4,
      11,    11,    19,    11,    46,    57,    11,    49,    37,    28,
      29,    30,    19,    38,    33,    19,    35,    27,    28,    29,
      30,    63,    38,    33,    66,    56,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,     4,     3,     4,     5,
      82,     4,     8,    11,     4,    11,    21,    20,    11,    20,
      25,    11,    25,    19,    25,    19,    87,   109,   110,    26,
      22,    23,    19,   105,   106,    28,    29,    30,    22,    32,
      33,    34,     4,    21,    21,    26,    22,    25,   130,    11,
      25,    25,     4,     4,   126,     4,     3,   129,     4,    20,
     121,   122,    11,     4,   136,    31,    28,    29,    30,    36,
      11,    33,    34,     3,    24,     4,     4,   138,    27,    28,
      29,    30,    11,     4,    33,    25,    27,    28,    29,    30,
      11,    25,    33,    25,     3,    21,     3,    24,    27,    28,
      29,    30,    24,    20,    33,    25,    24,    28,    29,    30,
      21,    -1,    33,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    -1,    -1,    -1,    -1,    -1,    24,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    -1,
      -1,    -1,    -1,    -1,    24,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    -1,    -1,    -1,    -1,    -1,
      24,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    -1,    -1,    -1,    -1,    -1,    24,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    -1,    -1,    -1,
      -1,    -1,    24,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    -1,    -1,    -1,    -1,    -1,    24,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    -1,
      20,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    -1,    20,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    -1,    20,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    -1,    20,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    -1,    20,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    11,
      12,    13,    14,    15,    16,    17,    18,    13,    14,    15,
      16,    17,    18,    13,    14,    15,    16,    17,    18
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    26,    37,    40,     4,    11,    27,    28,    29,    30,
      33,    45,    46,    47,    48,    49,    50,    51,     6,     7,
      38,    41,    42,    43,     0,    21,    25,     4,    19,    19,
      19,    19,    27,    46,    22,    26,    38,    42,     4,    11,
      44,     3,     4,     5,     8,    11,    19,    52,    52,    21,
      52,     4,    11,    52,    52,    22,    45,    26,    25,     4,
      11,    22,    23,    25,     4,     4,    19,    52,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    24,    52,
      20,    20,    25,     4,    20,    20,    27,    45,     3,     4,
       4,    11,    52,    52,    20,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    21,    25,    52,    20,    31,
      36,    27,    24,    25,     4,    11,    24,    20,    52,    52,
      24,    45,    45,    25,     3,     4,    25,    24,    20,    25,
      32,    34,    35,     3,    24,    52,    21,    52,    45,    24,
      25,    24,    52,    24,    34,     3,    20,    24
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    39,    40,    40,    40,    40,    41,    41,    42,    43,
      43,    44,    44,    44,    44,    44,    44,    44,    44,    44,
      44,    45,    45,    46,    46,    46,    46,    46,    47,    47,
      47,    47,    48,    49,    49,    49,    49,    50,    50,    51,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     6,     5,     3,     2,     2,     1,     3,     1,
       1,     3,     6,     9,     4,     7,     2,     3,     4,     5,
       1,     3,     2,     1,     1,     1,     1,     1,     4,     7,
      10,     5,     4,     3,     6,     9,     4,     9,     7,     7,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     1,     1,     4,     7,     2,     2,     4,     1
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
  case 2: /* Program: DECL DeclList ENDDECL kBEGIN Slist kEND  */
#line 50 "task2.y"
        {
            root = yyvsp[-1]; 
        }
#line 1379 "y.tab.c"
    break;

  case 3: /* Program: DECL ENDDECL kBEGIN Slist kEND  */
#line 54 "task2.y"
        { root = yyvsp[-1]; }
#line 1385 "y.tab.c"
    break;

  case 4: /* Program: kBEGIN Slist kEND  */
#line 56 "task2.y"
        { root = yyvsp[-1]; }
#line 1391 "y.tab.c"
    break;

  case 5: /* Program: kBEGIN kEND  */
#line 57 "task2.y"
                          { yyval = NULL; }
#line 1397 "y.tab.c"
    break;

  case 9: /* Type: INT  */
#line 71 "task2.y"
    { 
        currentType = TYPE_INT; 
        ptrLevel = PTR_LEVEL_0;
    }
#line 1406 "y.tab.c"
    break;

  case 10: /* Type: STR  */
#line 76 "task2.y"
    { 
        currentType = TYPE_STRING; 
        ptrLevel = PTR_LEVEL_0;
    }
#line 1415 "y.tab.c"
    break;

  case 11: /* VarList: VarList COMMA ID  */
#line 83 "task2.y"
    { 
        if (ptrLevel > 0) {
            InstallPointer(yyvsp[0]->varname, currentType, ptrLevel);
        } else {
            Install(yyvsp[0]->varname, currentType, 1); 
        }
    }
#line 1427 "y.tab.c"
    break;

  case 12: /* VarList: VarList COMMA ID LSQBR NUM RSQBR  */
#line 91 "task2.y"
    { 
        if (ptrLevel > 0) {
            fprintf(stderr, "Parse error: line number:%d\nArrays cannot be pointers\nyytext:%s\n", lineNumber, yytext);
            exit(1);
        }
        Install1DArray(yyvsp[-3]->varname, currentType, yyvsp[-1]->val); 
    }
#line 1439 "y.tab.c"
    break;

  case 13: /* VarList: VarList COMMA ID LSQBR NUM RSQBR LSQBR NUM RSQBR  */
#line 99 "task2.y"
    { 
        if (ptrLevel > 0) {
            fprintf(stderr, "Parse error: line number:%d\nArrays cannot be pointers\nyytext:%s\n", lineNumber, yytext);
            exit(1);
        }
        Install2DArray(yyvsp[-6]->varname, currentType, yyvsp[-4]->val, yyvsp[-1]->val); 
    }
#line 1451 "y.tab.c"
    break;

  case 14: /* VarList: ID LSQBR NUM RSQBR  */
#line 107 "task2.y"
    { 
        if (ptrLevel > 0) {
            fprintf(stderr, "Parse error: line number:%d\nArrays cannot be pointers\nyytext:%s\n", lineNumber, yytext);
            exit(1);
        }
        Install1DArray(yyvsp[-3]->varname, currentType, yyvsp[-1]->val); 
    }
#line 1463 "y.tab.c"
    break;

  case 15: /* VarList: ID LSQBR NUM RSQBR LSQBR NUM RSQBR  */
#line 115 "task2.y"
    { 
        if (ptrLevel > 0) {
            fprintf(stderr, "Parse error: line number:%d\nArrays cannot be pointers\nyytext:%s\n", lineNumber, yytext);
            exit(1);
        }
        Install2DArray(yyvsp[-6]->varname, currentType, yyvsp[-4]->val, yyvsp[-1]->val); 
    }
#line 1475 "y.tab.c"
    break;

  case 16: /* VarList: MUL ID  */
#line 123 "task2.y"
    {  
        ptrLevel = PTR_LEVEL_1;
        InstallPointer(yyvsp[0]->varname, TYPE_POINTER, ptrLevel);
        ptrLevel = PTR_LEVEL_0;
    }
#line 1485 "y.tab.c"
    break;

  case 17: /* VarList: MUL MUL ID  */
#line 129 "task2.y"
    { 
        ptrLevel = PTR_LEVEL_2;
        InstallPointer(yyvsp[0]->varname, TYPE_POINTER, ptrLevel);
        ptrLevel = PTR_LEVEL_0;
    }
#line 1495 "y.tab.c"
    break;

  case 18: /* VarList: VarList COMMA MUL ID  */
#line 135 "task2.y"
    {  
        ptrLevel = PTR_LEVEL_1;
        InstallPointer(yyvsp[0]->varname, TYPE_POINTER, ptrLevel);
        ptrLevel = PTR_LEVEL_0;
    }
#line 1505 "y.tab.c"
    break;

  case 19: /* VarList: VarList COMMA MUL MUL ID  */
#line 141 "task2.y"
    { 
        ptrLevel = PTR_LEVEL_2;
        InstallPointer(yyvsp[0]->varname, TYPE_POINTER, ptrLevel);
        ptrLevel = PTR_LEVEL_0;
    }
#line 1515 "y.tab.c"
    break;

  case 20: /* VarList: ID  */
#line 147 "task2.y"
    { 
        if (ptrLevel > 0) {
            InstallPointer(yyvsp[0]->varname, currentType, ptrLevel);
        } else {
            Install(yyvsp[0]->varname, currentType, 1);
        }
    }
#line 1527 "y.tab.c"
    break;

  case 21: /* Slist: Slist Stmt SEMICOLON  */
#line 159 "task2.y"
                         { yyval = makeConnectorNode(yyvsp[-2], yyvsp[-1]); }
#line 1533 "y.tab.c"
    break;

  case 22: /* Slist: Stmt SEMICOLON  */
#line 160 "task2.y"
                         { yyval = yyvsp[-1]; }
#line 1539 "y.tab.c"
    break;

  case 23: /* Stmt: InputStmt  */
#line 164 "task2.y"
                          { yyval = yyvsp[0]; }
#line 1545 "y.tab.c"
    break;

  case 24: /* Stmt: OutputStmt  */
#line 165 "task2.y"
                          { yyval = yyvsp[0]; }
#line 1551 "y.tab.c"
    break;

  case 25: /* Stmt: AssgStmt  */
#line 166 "task2.y"
                          { yyval = yyvsp[0]; }
#line 1557 "y.tab.c"
    break;

  case 26: /* Stmt: IfStmt  */
#line 167 "task2.y"
                          { yyval = yyvsp[0]; }
#line 1563 "y.tab.c"
    break;

  case 27: /* Stmt: WhileStmt  */
#line 168 "task2.y"
                          { yyval = yyvsp[0]; }
#line 1569 "y.tab.c"
    break;

  case 28: /* InputStmt: READ LPAREN ID RPAREN  */
#line 172 "task2.y"
                                                      { yyval = makeReadNode(makeVarNode(yyvsp[-1]->varname)); }
#line 1575 "y.tab.c"
    break;

  case 29: /* InputStmt: READ LPAREN ID LSQBR E RSQBR RPAREN  */
#line 173 "task2.y"
                                                        { yyval = makeReadNode(makeArrayNode(yyvsp[-4], yyvsp[-2])); }
#line 1581 "y.tab.c"
    break;

  case 30: /* InputStmt: READ LPAREN ID LSQBR E RSQBR LSQBR E RSQBR RPAREN  */
#line 174 "task2.y"
                                                        { yyval = makeReadNode(make2dArrayNode(yyvsp[-7], yyvsp[-5], yyvsp[-2])); }
#line 1587 "y.tab.c"
    break;

  case 31: /* InputStmt: READ LPAREN MUL ID RPAREN  */
#line 176 "task2.y"
    { 
        tnode* ptr_node = makeVarNode(yyvsp[-1]->varname);
        yyval = makeReadNode(makeDerefNode(ptr_node)); 
    }
#line 1596 "y.tab.c"
    break;

  case 32: /* OutputStmt: WRITE LPAREN E RPAREN  */
#line 183 "task2.y"
                          { yyval = makeWriteNode(yyvsp[-1]); }
#line 1602 "y.tab.c"
    break;

  case 33: /* AssgStmt: ID ASSIGN E  */
#line 188 "task2.y"
    {
        struct Gsymbol *g = Lookup(yyvsp[-2]->varname);
        if (!g) {
            fprintf(stderr, "Parse error: line number:%d\nUndeclared variable: %s\nyytext:%s\n", lineNumber, yyvsp[-2]->varname, yytext);
            exit(1);
        }
        if (g->type != yyvsp[0]->type) {
            fprintf(stderr, "Parse error: line number:%d\nType mismatch in assignment to %s\nyytext:%s\n", lineNumber, yyvsp[-2]->varname, yytext);
            exit(1);
        }
        yyval = makeAssignNode(makeVarNode(yyvsp[-2]->varname), yyvsp[0]);
    }
#line 1619 "y.tab.c"
    break;

  case 34: /* AssgStmt: ID LSQBR E RSQBR ASSIGN E  */
#line 202 "task2.y"
    {
        struct Gsymbol *g = Lookup(yyvsp[-5]->varname);
        if (!g) {
            fprintf(stderr, "Parse error: line number:%d\nUndeclared variable: %s\nyytext:%s\n", lineNumber, yyvsp[-5]->varname, yytext);
            exit(1);
        }
        if (g->type != yyvsp[0]->type) {
            fprintf(stderr, "Parse error: line number:%d\nType mismatch in assignment to %s\nyytext:%s\n", lineNumber, yyvsp[-5]->varname, yytext);
            exit(1);
        }
        if (yyvsp[-3]->type != TYPE_INT) {
            fprintf(stderr, "Parse error: line number:%d\nArray index should be TYPE_INT (array:%s)\nyytext:%s\n", lineNumber, yyvsp[-5]->varname, yytext);
            exit(1);
        }
        yyval = makeArrayAssignNode(makeArrayNode(yyvsp[-5], yyvsp[-3]), yyvsp[0]);
    }
#line 1640 "y.tab.c"
    break;

  case 35: /* AssgStmt: ID LSQBR E RSQBR LSQBR E RSQBR ASSIGN E  */
#line 220 "task2.y"
    {
        struct Gsymbol *g = Lookup(yyvsp[-8]->varname);
        if (!g) {
            fprintf(stderr, "Parse error: line number:%d\nUndeclared variable: %s\nyytext:%s\n", lineNumber, yyvsp[-8]->varname, yytext);
            exit(1);
        }
        if (g->type != yyvsp[0]->type) {
            fprintf(stderr, "Parse error: line number:%d\nType mismatch in assignment to %s\nyytext:%s\n", lineNumber, yyvsp[-8]->varname, yytext);
            exit(1);
        }
        if (yyvsp[-6]->type != TYPE_INT || yyvsp[-3]->type != TYPE_INT) {
            fprintf(stderr, "Parse error: line number:%d\nArray index should be TYPE_INT (array:%s)\nyytext:%s\n", lineNumber, yyvsp[-8]->varname, yytext);
            exit(1);
        }
        yyval = makeArray2DAssignNode(make2dArrayNode(yyvsp[-8], yyvsp[-6], yyvsp[-3]), yyvsp[0]);
    }
#line 1661 "y.tab.c"
    break;

  case 36: /* AssgStmt: MUL ID ASSIGN E  */
#line 237 "task2.y"
    {
        struct Gsymbol *g = Lookup(yyvsp[-2]->varname);
        if (!g) {
            fprintf(stderr, "Parse error: line number:%d\nUndeclared variable: %s\nyytext:%s\n", lineNumber, yyvsp[-2]->varname, yytext);
            exit(1);
        }
        if (g->ptrLevel == 0) {
            fprintf(stderr, "Parse error: line number:%d\nCannot dereference non-pointer: %s\nyytext:%s\n", lineNumber, yyvsp[-2]->varname, yytext);
            exit(1);
        }
        tnode* ptr_node = makeVarNode(yyvsp[-2]->varname);
        tnode* deref_node = makeDerefNode(ptr_node);
        yyval = makeAssignNode(deref_node, yyvsp[0]);
        
    }
#line 1681 "y.tab.c"
    break;

  case 37: /* IfStmt: IF LPAREN E RPAREN THEN Slist ELSE Slist ENDIF  */
#line 257 "task2.y"
        { 
            if(yyvsp[-6]->type != TYPE_BOOL)
            {
                fprintf(stderr, "Parse error: line number:%d\nIF statement expects BOOL expression\nyytext:%s\n", lineNumber, yytext);
                exit(1);
            }
            yyval = makeIfElseNode(yyvsp[-6], yyvsp[-3], yyvsp[-1]); 
        }
#line 1694 "y.tab.c"
    break;

  case 38: /* IfStmt: IF LPAREN E RPAREN THEN Slist ENDIF  */
#line 266 "task2.y"
        { 
            if(yyvsp[-4]->type != TYPE_BOOL)
            {
                fprintf(stderr, "Parse error: line number:%d\nIF statement expects BOOL expression\nyytext:%s\n", lineNumber, yytext);
                exit(1);
            }
            yyval = makeIfNode(yyvsp[-4], yyvsp[-1]); 
        }
#line 1707 "y.tab.c"
    break;

  case 39: /* WhileStmt: WHILE LPAREN E RPAREN DO Slist ENDWHILE  */
#line 278 "task2.y"
        {
            if(yyvsp[-4]->type != TYPE_BOOL)
            {
                fprintf(stderr, "Parse error: line number:%d\nWHILE statement expects BOOL expression\nyytext:%s\n", lineNumber, yytext);
                exit(1);
            }
            yyval = makeWhileNode(yyvsp[-4], yyvsp[-1]); 
        }
#line 1720 "y.tab.c"
    break;

  case 40: /* E: E PLUS E  */
#line 289 "task2.y"
             {
        if ((yyvsp[-2]->type != TYPE_INT) || (yyvsp[0]->type != TYPE_INT)) {
            fprintf(stderr, "Parse error: line number:%d\ntype mismatch\nyytext:%s\n", lineNumber, yytext);
            exit(1);
        } else {
            yyval = makeArithNode(NODE_PLUS, yyvsp[-2], yyvsp[0]);
        }
    }
#line 1733 "y.tab.c"
    break;

  case 41: /* E: E MINUS E  */
#line 297 "task2.y"
                {
        if ((yyvsp[-2]->type != TYPE_INT) || (yyvsp[0]->type != TYPE_INT)) {
            fprintf(stderr, "Parse error: line number:%d\ntype mismatch\nyytext:%s\n", lineNumber, yytext);
            exit(1);
        } else {
            yyval = makeArithNode(NODE_MINUS, yyvsp[-2], yyvsp[0]);
        }
    }
#line 1746 "y.tab.c"
    break;

  case 42: /* E: E MUL E  */
#line 305 "task2.y"
              {
        if ((yyvsp[-2]->type != TYPE_INT) || (yyvsp[0]->type != TYPE_INT)) {
            fprintf(stderr, "Parse error: line number:%d\ntype mismatch\nyytext:%s\n", lineNumber, yytext);
            exit(1);
        } else {
            yyval = makeArithNode(NODE_MUL, yyvsp[-2], yyvsp[0]);
        }
    }
#line 1759 "y.tab.c"
    break;

  case 43: /* E: E DIV E  */
#line 313 "task2.y"
              {
        if ((yyvsp[-2]->type != TYPE_INT) || (yyvsp[0]->type != TYPE_INT)) {
            fprintf(stderr, "Parse error: line number:%d\nERROR: type mismatch\nyytext:%s\n", lineNumber, yytext);
            exit(1);
        } else {
            yyval = makeArithNode(NODE_DIV, yyvsp[-2], yyvsp[0]);
        }
    }
#line 1772 "y.tab.c"
    break;

  case 44: /* E: LPAREN E RPAREN  */
#line 321 "task2.y"
                      { yyval = yyvsp[-1]; }
#line 1778 "y.tab.c"
    break;

  case 45: /* E: E LT E  */
#line 323 "task2.y"
             {
        if ((yyvsp[-2]->type != TYPE_INT) || (yyvsp[0]->type != TYPE_INT)) {
            fprintf(stderr, "Parse error: line number:%d\nERROR: type mismatch\nyytext:%s\n", lineNumber, yytext);
            exit(1);
        } else {
            yyval = makeBoolNode(NODE_LT, yyvsp[-2], yyvsp[0]);
        }
    }
#line 1791 "y.tab.c"
    break;

  case 46: /* E: E LE E  */
#line 331 "task2.y"
             {
        if ((yyvsp[-2]->type != TYPE_INT) || (yyvsp[0]->type != TYPE_INT)) {
            fprintf(stderr, "Parse error: line number:%d\nERROR: type mismatch\nyytext:%s\n", lineNumber, yytext);
            exit(1);
        } else {
            yyval = makeBoolNode(NODE_LE, yyvsp[-2], yyvsp[0]);
        }
    }
#line 1804 "y.tab.c"
    break;

  case 47: /* E: E GT E  */
#line 339 "task2.y"
             {
        if ((yyvsp[-2]->type != TYPE_INT) || (yyvsp[0]->type != TYPE_INT)) {
            fprintf(stderr, "Parse error: line number:%d\nERROR: type mismatch\nyytext:%s\n", lineNumber, yytext);
            exit(1);
        } else {
            yyval = makeBoolNode(NODE_GT, yyvsp[-2], yyvsp[0]);
        }
    }
#line 1817 "y.tab.c"
    break;

  case 48: /* E: E GE E  */
#line 347 "task2.y"
             {
        if ((yyvsp[-2]->type != TYPE_INT) || (yyvsp[0]->type != TYPE_INT)) {
            fprintf(stderr, "Parse error: line number:%d\nERROR: type mismatch\nyytext:%s\n", lineNumber, yytext);
            exit(1);
        } else {
            yyval = makeBoolNode(NODE_GE, yyvsp[-2], yyvsp[0]);
        }
    }
#line 1830 "y.tab.c"
    break;

  case 49: /* E: E EQ E  */
#line 355 "task2.y"
             {
        if ((yyvsp[-2]->type != TYPE_INT) || (yyvsp[0]->type != TYPE_INT)) {
            fprintf(stderr, "Parse error: line number:%d\nERROR: type mismatch\nyytext:%s\n", lineNumber, yytext);
            exit(1);
        } else {
            yyval = makeBoolNode(NODE_EQ, yyvsp[-2], yyvsp[0]);
        }
    }
#line 1843 "y.tab.c"
    break;

  case 50: /* E: E NE E  */
#line 363 "task2.y"
             {
        if ((yyvsp[-2]->type != TYPE_INT) || (yyvsp[0]->type != TYPE_INT)) {
            fprintf(stderr, "Parse error: line number:%d\nERROR: type mismatch\nyytext:%s\n", lineNumber, yytext);
            exit(1);
        } else {
            yyval = makeBoolNode(NODE_NE, yyvsp[-2], yyvsp[0]);
        }
    }
#line 1856 "y.tab.c"
    break;

  case 51: /* E: NUM  */
#line 371 "task2.y"
                { yyval = yyvsp[0]; }
#line 1862 "y.tab.c"
    break;

  case 52: /* E: STRING  */
#line 372 "task2.y"
                { yyval = yyvsp[0]; }
#line 1868 "y.tab.c"
    break;

  case 53: /* E: ID LSQBR E RSQBR  */
#line 373 "task2.y"
                       { 
                            struct Gsymbol *g = Lookup(yyvsp[-3]->varname);
                            if (!g) {
                                fprintf(stderr, "Parse error: line number:%d\nUndeclared variable: %s\nyytext:%s\n", lineNumber, yyvsp[-3]->varname, yytext);
                                exit(1);
                            }
                            if (yyvsp[-1]->type != TYPE_INT) {
                                fprintf(stderr, "Parse error: line number:%d\nArray index should be TYPE_INT (array:%s)\nyytext:%s\n", lineNumber, yyvsp[-3]->varname, yytext);
                                exit(1);
                            }
                            yyval = makeArrayNode(yyvsp[-3], yyvsp[-1]);
                        }
#line 1885 "y.tab.c"
    break;

  case 54: /* E: ID LSQBR E RSQBR LSQBR E RSQBR  */
#line 385 "task2.y"
                                     {
                                        struct Gsymbol *g = Lookup(yyvsp[-6]->varname);
                                        if (!g) {
                                            fprintf(stderr, "Parse error: line number:%d\nUndeclared variable: %s\nyytext:%s\n", lineNumber, yyvsp[-6]->varname, yytext);
                                            exit(1);
                                        }
                                        if (yyvsp[-4]->type != TYPE_INT || yyvsp[-1]->type != TYPE_INT) {
                                            fprintf(stderr, "Parse error: line number:%d\nArray index should be TYPE_INT (array:%s)\nyytext:%s\n", lineNumber, yyvsp[-6]->varname, yytext);
                                            exit(1);
                                        }
                                        yyval = make2dArrayNode(yyvsp[-6], yyvsp[-4], yyvsp[-1]);
                                     }
#line 1902 "y.tab.c"
    break;

  case 55: /* E: ADDRESS_OF ID  */
#line 398 "task2.y"
        {
            struct Gsymbol *g = Lookup(yyvsp[0]->varname);
            if (!g) {
                fprintf(stderr, "Parse error: line number:%d\nUndeclared variable: %s\nyytext:%s\n", lineNumber, yyvsp[0]->varname, yytext);
                exit(1);
            }
            if (g->ptrLevel > 0) {
                fprintf(stderr, "Parse error: line number:%d\nCannot take address of pointer: %s\nyytext:%s\n", lineNumber, yyvsp[0]->varname, yytext);
                exit(1);
            }
            tnode* t = makeVarNode(yyvsp[0]->varname);
            yyval = makePointerNode(t);
            yyval->type = TYPE_POINTER;
        }
#line 1921 "y.tab.c"
    break;

  case 56: /* E: MUL ID  */
#line 414 "task2.y"
        {
            struct Gsymbol *g = Lookup(yyvsp[0]->varname);
            if (!g) {
                fprintf(stderr, "Parse error: line number:%d\nUndeclared variable: %s\nyytext:%s\n", lineNumber, yyvsp[0]->varname, yytext);
                exit(1);
            }
            if (g->ptrLevel == 0) {
                fprintf(stderr, "Parse error: line number:%d\nCannot dereference non-pointer: %s\nyytext:%s\n", lineNumber, yyvsp[0]->varname, yytext);
                exit(1);
            }
            tnode* t = makeVarNode(yyvsp[0]->varname);
            yyval = makeDerefNode(t);
            yyval->type = g->type;
        }
#line 1940 "y.tab.c"
    break;

  case 57: /* E: MUL LPAREN E RPAREN  */
#line 430 "task2.y"
        {
            if (yyvsp[-1]->type != TYPE_POINTER) {
                fprintf(stderr, "Parse error: line number:%d\nCannot dereference non-pointer expression\nyytext:%s\n", lineNumber, yytext);
                exit(1);
            }
            yyval = makeDerefNode(yyvsp[-1]);
            /* Type depends on what's being pointed to */
        }
#line 1953 "y.tab.c"
    break;

  case 58: /* E: ID  */
#line 440 "task2.y"
        {
            struct Gsymbol *g = Lookup(yyvsp[0]->varname);
            if (!g) {
                fprintf(stderr, "Parse error: line number:%d\nUndeclared variable: %s\nyytext:%s\n", lineNumber, yyvsp[0]->varname, yytext);
                exit(1);
            }
            yyval = makeVarNode(yyvsp[0]->varname);
        }
#line 1966 "y.tab.c"
    break;


#line 1970 "y.tab.c"

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

#line 452 "task2.y"


int main(int argc, char **argv)
{
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input.expl> <output.xsm>\n", argv[0]);
        return 1;
    }

    FILE *source_file = fopen(argv[1], "r");
    if (!source_file) {
        fprintf(stderr, "Parse error: line number:%d\nfopen input\nyytext:%s\n", lineNumber, yytext);
        return 1;
    }

    yyin = source_file;

    if (yyparse() != 0) {
        fprintf(stderr, "Parsing failed\n");
        fclose(source_file);
        return 1;
    }

    fclose(source_file);

    if (!root) {
        fprintf(stderr, "Empty or invalid program\n");
        return 1;
    }

#ifdef DEBUG
    printSymbolTable();
    printAST(root, 0);
#endif

    FILE *temp = tmpfile();
    if (!temp) {
        fprintf(stderr, "Parse error: line number:%d\ntmpfile\nyytext:%s\n", lineNumber, yytext);
        return 1;
    }

    initReg();
    fileinit(temp);
    moveStackPointer(temp);
    codeGen(root, temp);
    emitExit(temp);

    rewind(temp);

    buildLabelTable(temp);

    FILE *out = fopen(argv[2], "w");
    if (!out) {
        fprintf(stderr, "Parse error: line number:%d\nfopen output\nyytext:%s\n", lineNumber, yytext);
        fclose(temp);
        return 1;
    }

    translateLabels(temp, out);

    fclose(out);
    fclose(temp);   

    return 0;
}

void yyerror(char *s)
{
    fprintf(stderr, "Parse error: currentType:%d\nline number:%d\n%s\nyytext:%s\n",currentType, lineNumber, s, yytext);
}
