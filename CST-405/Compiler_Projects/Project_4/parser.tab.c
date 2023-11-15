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
#line 2 "parser.y"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>

#include "symbolTable.h"
#include "AST.h"
#include "IRcode.h"
#include "CodeGen.h"
#include "Semantic.h"

BinTree AST;

extern int yylex();
extern int yyparse();
extern FILE* yyin;
extern FILE* IRfile;

void yyerror(const char* s);
char currentScope[50]; // global or the name of the function
int semanticCheckPassed;

#line 97 "parser.tab.c"

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
  YYSYMBOL_CHAR = 3,                       /* CHAR  */
  YYSYMBOL_INT = 4,                        /* INT  */
  YYSYMBOL_ID = 5,                         /* ID  */
  YYSYMBOL_SEMICOLON = 6,                  /* SEMICOLON  */
  YYSYMBOL_EQ = 7,                         /* EQ  */
  YYSYMBOL_NUMBER = 8,                     /* NUMBER  */
  YYSYMBOL_WRITE = 9,                      /* WRITE  */
  YYSYMBOL_READ = 10,                      /* READ  */
  YYSYMBOL_WRITELN = 11,                   /* WRITELN  */
  YYSYMBOL_RETURN = 12,                    /* RETURN  */
  YYSYMBOL_IF = 13,                        /* IF  */
  YYSYMBOL_ELSE = 14,                      /* ELSE  */
  YYSYMBOL_LPAR = 15,                      /* LPAR  */
  YYSYMBOL_LBRA = 16,                      /* LBRA  */
  YYSYMBOL_RCBRA = 17,                     /* RCBRA  */
  YYSYMBOL_LCBRA = 18,                     /* LCBRA  */
  YYSYMBOL_COMMA = 19,                     /* COMMA  */
  YYSYMBOL_PLUS = 20,                      /* PLUS  */
  YYSYMBOL_MINUS = 21,                     /* MINUS  */
  YYSYMBOL_MULT = 22,                      /* MULT  */
  YYSYMBOL_DIV = 23,                       /* DIV  */
  YYSYMBOL_RPAR = 24,                      /* RPAR  */
  YYSYMBOL_RBRA = 25,                      /* RBRA  */
  YYSYMBOL_UNARY = 26,                     /* UNARY  */
  YYSYMBOL_LESSTHN = 27,                   /* LESSTHN  */
  YYSYMBOL_GRTRTHN = 28,                   /* GRTRTHN  */
  YYSYMBOL_LESSTHNEQ = 29,                 /* LESSTHNEQ  */
  YYSYMBOL_GRTRTHNEQ = 30,                 /* GRTRTHNEQ  */
  YYSYMBOL_EQEQ = 31,                      /* EQEQ  */
  YYSYMBOL_NOTEQ = 32,                     /* NOTEQ  */
  YYSYMBOL_YYACCEPT = 33,                  /* $accept  */
  YYSYMBOL_Program = 34,                   /* Program  */
  YYSYMBOL_FuncDeclList = 35,              /* FuncDeclList  */
  YYSYMBOL_FuncDecl = 36,                  /* FuncDecl  */
  YYSYMBOL_ParamDeclList = 37,             /* ParamDeclList  */
  YYSYMBOL_Block = 38,                     /* Block  */
  YYSYMBOL_Condition = 39,                 /* Condition  */
  YYSYMBOL_BlockList = 40,                 /* BlockList  */
  YYSYMBOL_ParamDecl = 41,                 /* ParamDecl  */
  YYSYMBOL_VarDecl = 42,                   /* VarDecl  */
  YYSYMBOL_Type = 43,                      /* Type  */
  YYSYMBOL_StmtList = 44,                  /* StmtList  */
  YYSYMBOL_Stmt = 45,                      /* Stmt  */
  YYSYMBOL_Expr = 46,                      /* Expr  */
  YYSYMBOL_IfBlock = 47,                   /* IfBlock  */
  YYSYMBOL_Primary = 48,                   /* Primary  */
  YYSYMBOL_ExprList = 49                   /* ExprList  */
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
typedef yytype_int8 yy_state_t;

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
#define YYLAST   119

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  33
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  17
/* YYNRULES -- Number of rules.  */
#define YYNRULES  53
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  98

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   287


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
      25,    26,    27,    28,    29,    30,    31,    32
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    62,    62,    64,    66,    67,    70,    86,    87,    88,
     101,   104,   105,   106,   107,   108,   109,   112,   113,   116,
     121,   127,   150,   168,   182,   183,   189,   190,   193,   194,
     227,   228,   231,   234,   237,   240,   241,   244,   247,   251,
     254,   257,   260,   263,   266,   271,   272,   276,   279,   280,
     283,   291,   292,   293
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
  "\"end of file\"", "error", "\"invalid token\"", "CHAR", "INT", "ID",
  "SEMICOLON", "EQ", "NUMBER", "WRITE", "READ", "WRITELN", "RETURN", "IF",
  "ELSE", "LPAR", "LBRA", "RCBRA", "LCBRA", "COMMA", "PLUS", "MINUS",
  "MULT", "DIV", "RPAR", "RBRA", "UNARY", "LESSTHN", "GRTRTHN",
  "LESSTHNEQ", "GRTRTHNEQ", "EQEQ", "NOTEQ", "$accept", "Program",
  "FuncDeclList", "FuncDecl", "ParamDeclList", "Block", "Condition",
  "BlockList", "ParamDecl", "VarDecl", "Type", "StmtList", "Stmt", "Expr",
  "IfBlock", "Primary", "ExprList", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-74)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-48)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      16,   -74,   -74,     8,   -74,    16,    27,   -74,   -74,   -74,
      45,    16,    39,    49,    66,    54,    16,    57,   -74,   -74,
     -74,    77,    53,    68,    33,   -74,   -74,    38,    76,    38,
      81,   -74,   -74,    93,   -74,    75,    92,   -74,    38,    94,
      74,     3,    21,   -74,    18,    38,     1,   -74,    38,    72,
      79,    80,   -74,    38,    38,    38,    38,    38,   -74,    82,
      47,   -74,    96,    25,    38,   -74,   -74,    78,   -74,   -17,
      78,   -17,    78,   -17,   -74,   -17,    54,    38,    38,    38,
      38,    38,    38,    83,   -74,   -74,    87,   -74,    -7,    -7,
      -7,    -7,    -7,    -7,   101,    54,   -74,   -74
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,    25,    24,     0,     2,     4,     0,     1,     3,     5,
       0,     7,     0,     8,     0,     0,     7,    20,    17,     6,
       9,     0,     0,     0,    47,    28,    48,     0,     0,     0,
       0,    10,    19,     0,    18,    26,     0,    21,    51,     0,
      35,     0,    34,    32,     0,     0,     0,    27,     0,    52,
       0,     0,    30,     0,     0,     0,     0,     0,    31,     0,
       0,    22,     0,     0,    51,    49,    50,    38,    36,    34,
      39,    34,    43,    34,    41,    34,     0,     0,     0,     0,
       0,     0,     0,     0,    29,    53,    45,    33,    11,    12,
      13,    14,    15,    16,     0,     0,    23,    46
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -74,   -74,    34,   -74,    95,   -73,   -74,   -74,   -74,   -74,
      -6,    84,   -74,   -27,   -74,   -21,    46
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     3,     4,     5,    12,    19,    59,    22,    13,    32,
       6,    34,    35,    49,    87,    42,    50
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      41,    36,    44,    86,    56,    14,    57,    61,     7,    52,
      14,     1,     2,    53,    36,    54,    33,    62,    60,     1,
       2,    63,    97,    53,    58,    54,    67,    68,    70,    72,
      74,    84,    10,    69,    71,    73,    75,     8,    53,     9,
      54,    55,    56,    40,    57,    53,    26,    54,    38,    39,
      88,    89,    90,    91,    92,    93,     1,     2,    24,    25,
      11,    26,    27,    15,    28,    29,    30,    53,    16,    54,
      31,    17,    18,    21,    77,    78,    79,    80,    81,    82,
      24,    25,    43,    26,    27,    23,    28,    29,    30,    38,
      39,    64,    53,    37,    54,   -47,    45,   -47,    46,    48,
      54,    95,    51,    65,    83,    66,    76,    96,    94,     0,
      85,    20,     0,     0,     0,     0,     0,     0,     0,    47
};

static const yytype_int8 yycheck[] =
{
      27,    22,    29,    76,    21,    11,    23,     6,     0,     6,
      16,     3,     4,    20,    35,    22,    22,    16,    45,     3,
       4,    48,    95,    20,     6,    22,    53,    54,    55,    56,
      57,     6,     5,    54,    55,    56,    57,     3,    20,     5,
      22,    20,    21,     5,    23,    20,     8,    22,    15,    16,
      77,    78,    79,    80,    81,    82,     3,     4,     5,     6,
      15,     8,     9,    24,    11,    12,    13,    20,    19,    22,
      17,     5,    18,    16,    27,    28,    29,    30,    31,    32,
       5,     6,     6,     8,     9,     8,    11,    12,    13,    15,
      16,    19,    20,    25,    22,    21,    15,    23,     5,     7,
      22,    14,     8,    24,     8,    25,    24,     6,    25,    -1,
      64,    16,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    35
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     4,    34,    35,    36,    43,     0,    35,    35,
       5,    15,    37,    41,    43,    24,    19,     5,    18,    38,
      37,    16,    40,     8,     5,     6,     8,     9,    11,    12,
      13,    17,    42,    43,    44,    45,    48,    25,    15,    16,
       5,    46,    48,     6,    46,    15,     5,    44,     7,    46,
      49,     8,     6,    20,    22,    20,    21,    23,     6,    39,
      46,     6,    16,    46,    19,    24,    25,    46,    46,    48,
      46,    48,    46,    48,    46,    48,    24,    27,    28,    29,
      30,    31,    32,     8,     6,    49,    38,    47,    46,    46,
      46,    46,    46,    46,    25,    14,     6,    38
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    33,    34,    34,    35,    35,    36,    37,    37,    37,
      38,    39,    39,    39,    39,    39,    39,    40,    40,    40,
      41,    41,    42,    42,    43,    43,    44,    44,    45,    45,
      45,    45,    45,    45,    46,    46,    46,    46,    46,    46,
      46,    46,    46,    46,    46,    47,    47,    48,    48,    48,
      48,    49,    49,    49
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     2,     6,     0,     1,     3,
       3,     3,     3,     3,     3,     3,     3,     0,     2,     2,
       2,     5,     3,     6,     1,     1,     1,     2,     1,     4,
       3,     3,     2,     5,     1,     1,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     1,     3,     1,     1,     4,
       4,     0,     1,     3
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
  switch (yykind)
    {
    case YYSYMBOL_ID: /* ID  */
#line 52 "parser.y"
         { fprintf(yyoutput, "%s", ((*yyvaluep).string)); }
#line 814 "parser.tab.c"
        break;

    case YYSYMBOL_NUMBER: /* NUMBER  */
#line 53 "parser.y"
         { fprintf(yyoutput, "%d", ((*yyvaluep).number)); }
#line 820 "parser.tab.c"
        break;

      default:
        break;
    }
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
  case 2: /* Program: FuncDeclList  */
#line 62 "parser.y"
                        {AST.addNode("Program",(yyvsp[0].ast),NULL);
						printf("\n PARSER START? \n");}
#line 1211 "parser.tab.c"
    break;

  case 3: /* Program: Program FuncDeclList  */
#line 64 "parser.y"
                              {AST.addNode("Program",(yyvsp[-1].ast),(yyvsp[0].ast));}
#line 1217 "parser.tab.c"
    break;

  case 4: /* FuncDeclList: FuncDecl  */
#line 66 "parser.y"
                                    {(yyval.ast) = (yyvsp[0].ast);}
#line 1223 "parser.tab.c"
    break;

  case 5: /* FuncDeclList: FuncDecl FuncDeclList  */
#line 67 "parser.y"
                                    {(yyval.ast) = AST.addNode("FuncDeclList",(yyvsp[-1].ast),(yyvsp[0].ast));}
#line 1229 "parser.tab.c"
    break;

  case 6: /* FuncDecl: Type ID LPAR ParamDeclList RPAR Block  */
#line 70 "parser.y"
                                                 {printf("\n FUNCDECL \n");
												(yyval.ast) = AST.addNode("Func",AST.addNode((yyvsp[-4].string), NULL, NULL),AST.addNode("FuncInfo",(yyvsp[-2].ast),(yyvsp[0].ast)));
												cout << "SCOPE::" << cBS((yyvsp[-4].string)) << "\n";
												cout << "TEMP\n";
												showTempSymTable();
												cout << "\n SCOPE TABLE \n";
												moveTable();
												showAllSymTable();
												cout << "\n ADD NEW SCOPE \n";
												addFunc((yyvsp[-4].string), (yyvsp[-5].string));
												showFuncTable();

												//FINISH nodeType
}
#line 1248 "parser.tab.c"
    break;

  case 7: /* ParamDeclList: %empty  */
#line 86 "parser.y"
                                                {(yyval.ast) = NULL;}
#line 1254 "parser.tab.c"
    break;

  case 8: /* ParamDeclList: ParamDecl  */
#line 87 "parser.y"
                                                                {(yyval.ast) = (yyvsp[0].ast);}
#line 1260 "parser.tab.c"
    break;

  case 9: /* ParamDeclList: ParamDecl COMMA ParamDeclList  */
#line 88 "parser.y"
                                                        {(yyval.ast) = AST.addNode("ParamDeclList",(yyvsp[-2].ast),(yyvsp[0].ast));
											//FINISH nodeType
			}
#line 1268 "parser.tab.c"
    break;

  case 10: /* Block: LCBRA BlockList RCBRA  */
#line 101 "parser.y"
                             {(yyval.ast) = (yyvsp[-1].ast);}
#line 1274 "parser.tab.c"
    break;

  case 11: /* Condition: Expr LESSTHN Expr  */
#line 104 "parser.y"
                             {(yyval.ast) = AST.addNode("<",(yyvsp[-2].ast),(yyvsp[0].ast));}
#line 1280 "parser.tab.c"
    break;

  case 12: /* Condition: Expr GRTRTHN Expr  */
#line 105 "parser.y"
                                    {(yyval.ast) = AST.addNode(">",(yyvsp[-2].ast),(yyvsp[0].ast));}
#line 1286 "parser.tab.c"
    break;

  case 13: /* Condition: Expr LESSTHNEQ Expr  */
#line 106 "parser.y"
                                      {(yyval.ast) = AST.addNode("<=",(yyvsp[-2].ast),(yyvsp[0].ast));}
#line 1292 "parser.tab.c"
    break;

  case 14: /* Condition: Expr GRTRTHNEQ Expr  */
#line 107 "parser.y"
                                      {(yyval.ast) = AST.addNode(">=",(yyvsp[-2].ast),(yyvsp[0].ast));}
#line 1298 "parser.tab.c"
    break;

  case 15: /* Condition: Expr EQEQ Expr  */
#line 108 "parser.y"
                                 {(yyval.ast) = AST.addNode("==",(yyvsp[-2].ast),(yyvsp[0].ast));}
#line 1304 "parser.tab.c"
    break;

  case 16: /* Condition: Expr NOTEQ Expr  */
#line 109 "parser.y"
                                  {(yyval.ast) = AST.addNode("!=",(yyvsp[-2].ast),(yyvsp[0].ast));}
#line 1310 "parser.tab.c"
    break;

  case 17: /* BlockList: %empty  */
#line 112 "parser.y"
                                                        {(yyval.ast) = AST.addNode("BlockEnd",NULL,NULL);}
#line 1316 "parser.tab.c"
    break;

  case 18: /* BlockList: BlockList StmtList  */
#line 113 "parser.y"
                                                {(yyval.ast) = AST.addNode("BlockList",(yyvsp[0].ast),(yyvsp[-1].ast));
									//FINISH?
									}
#line 1324 "parser.tab.c"
    break;

  case 19: /* BlockList: BlockList VarDecl  */
#line 116 "parser.y"
                                                        {(yyval.ast) = AST.addNode("BlockList",(yyvsp[-1].ast),(yyvsp[0].ast));
									//FINISH?
									}
#line 1332 "parser.tab.c"
    break;

  case 20: /* ParamDecl: Type ID  */
#line 121 "parser.y"
                                                        {printf("\n ParamDecl \n");
									(yyval.ast) = AST.addNode((yyvsp[0].string), NULL, NULL);
									addParam((yyvsp[0].string), (yyvsp[-1].string), 1);
									showSymTable();
									//FINISH?
									}
#line 1343 "parser.tab.c"
    break;

  case 21: /* ParamDecl: Type ID LBRA NUMBER RBRA  */
#line 127 "parser.y"
                                           {(yyval.ast) = AST.addNode((yyvsp[-3].string), NULL, NULL);
									for (int x = 0; x < (yyvsp[-1].number); x++){
										string n = cBS((yyvsp[-3].string)) + "[" + to_string(x) + "]";
										cout << "Array: " << n <<"\n";
										addParam((char*)n.c_str(),(yyvsp[-4].string),1);
									}
									showSymTable();
		}
#line 1356 "parser.tab.c"
    break;

  case 22: /* VarDecl: Type ID SEMICOLON  */
#line 150 "parser.y"
                                        { printf("\n RECOGNIZED RULE: Variable declaration %s\n", (yyvsp[-1].string));
									// Symbol Table
									symTabAccess();
									int inSymTab = found((yyvsp[-1].string), 0);
									//printf("looking for %s in symtab - found: %d \n", $2, inSymTab);
									
									if (inSymTab == 1) {
										addItem((yyvsp[-1].string), "Var", (yyvsp[-2].string),0, currentScope);
										printf("\n Item Name: %s\n", (yyvsp[-1].string));
									}else
										printf("SEMANTIC ERROR: Var %s is already in the symbol table", (yyvsp[-1].string));
									showSymTable();
									
								  // ---- SEMANTIC ACTIONS by PARSER ----
								  (yyval.ast) = AST.addNode((yyvsp[-1].string),NULL, NULL);
								  printf("----------> %s", (yyval.ast)->Left);

								}
#line 1379 "parser.tab.c"
    break;

  case 23: /* VarDecl: Type ID LBRA NUMBER RBRA SEMICOLON  */
#line 168 "parser.y"
                                                     {
								printf("\n ARRAY NUMBER %d\n", (yyvsp[-2].number));
								printf("INPUT: %s\n", (yyvsp[-4].string));
								for (int x = 0; x < (yyvsp[-2].number); x++){
									string n = cBS((yyvsp[-4].string)) + "[" + to_string(x) + "]";
									cout << "Array: " << n <<"\n";
									addItem((char*)n.c_str(), "Var", (yyvsp[-5].string),0, currentScope);
								}
								showSymTable();
								(yyval.ast) = AST.addNode((yyvsp[-4].string),NULL, NULL);
								//Add array indicator
								}
#line 1396 "parser.tab.c"
    break;

  case 24: /* Type: INT  */
#line 182 "parser.y"
           {(yyval.string) = (yyvsp[0].string);}
#line 1402 "parser.tab.c"
    break;

  case 25: /* Type: CHAR  */
#line 183 "parser.y"
           {(yyval.string) = (yyvsp[0].string);}
#line 1408 "parser.tab.c"
    break;

  case 26: /* StmtList: Stmt  */
#line 189 "parser.y"
                              {(yyval.ast) = (yyvsp[0].ast);}
#line 1414 "parser.tab.c"
    break;

  case 27: /* StmtList: Stmt StmtList  */
#line 190 "parser.y"
                        {(yyval.ast) = AST.addNode("StmtList",(yyvsp[-1].ast),(yyvsp[0].ast));}
#line 1420 "parser.tab.c"
    break;

  case 28: /* Stmt: SEMICOLON  */
#line 193 "parser.y"
                        {}
#line 1426 "parser.tab.c"
    break;

  case 29: /* Stmt: Primary EQ Expr SEMICOLON  */
#line 194 "parser.y"
                                        { printf("\n RECOGNIZED RULE: prime=Expr statement\n"); 
					cout << "\n\nEquals\n" << (yyvsp[-1].ast) << "\n";
					// ---- SEMANTIC ACTIONS by PARSER ----
					  (yyval.ast) = AST.addNode("=",(yyvsp[-3].ast),(yyvsp[-1].ast));
					// Semantic ananysic
					/*if(found($1, 0) != 1){
						printf("Semantic error: Variable %s has not been declared in scope %s \n", $1, currentScope);
						semanticCheckPassed = 0;
					}*/

					if(found((yyvsp[-1].ast)->data, 0) != 1){
						printf("Semantic error: Variable %s has not been declared in scope %s \n", (yyvsp[-1].ast), currentScope);
						semanticCheckPassed = 0;
					}

					printf("\nChecking types: \n");
					/*int typeMatch = compareTypes ($1, $3->data, currentScope);
					if (typeMatch == 0){
						printf("Semantic error: Type mismatch for variables %s and %s \n", $1, $3);
						semanticCheckPassed = 0;
					}

					if (semanticCheckPassed == 1){
						printf("\n\n >IR code is emitted!<\n\n");
						//emitAssignment($1,$3->data);
					}
					
					if(testVarDeclaration($1) == 1)
						if(testVarDeclaration($3) == 1)
							if(checkType($1) == checkType($3))
								//emitIRcode(IRfile, IRAssignment($1,$3));
					*/
				}
#line 1464 "parser.tab.c"
    break;

  case 30: /* Stmt: WRITE Expr SEMICOLON  */
#line 227 "parser.y"
                              {(yyval.ast) = AST.addNode("WRITE",(yyvsp[-1].ast),(yyvsp[-1].ast));}
#line 1470 "parser.tab.c"
    break;

  case 31: /* Stmt: RETURN Expr SEMICOLON  */
#line 228 "parser.y"
                               {(yyval.ast) = AST.addNode("RETURN",(yyvsp[-1].ast),NULL);
							//FINISH node and return type
							}
#line 1478 "parser.tab.c"
    break;

  case 32: /* Stmt: WRITELN SEMICOLON  */
#line 231 "parser.y"
                            {(yyval.ast) = AST.addNode("WRITELN",NULL,NULL);
							//FINISH nodeType
							}
#line 1486 "parser.tab.c"
    break;

  case 33: /* Stmt: IF LPAR Condition RPAR IfBlock  */
#line 234 "parser.y"
                                         {(yyval.ast) = AST.addNode("IF", (yyvsp[-2].ast), (yyvsp[0].ast));}
#line 1492 "parser.tab.c"
    break;

  case 34: /* Expr: Primary  */
#line 237 "parser.y"
                        {(yyval.ast) = (yyvsp[0].ast);
					cout << "prine->expr\n";
					}
#line 1500 "parser.tab.c"
    break;

  case 35: /* Expr: ID  */
#line 240 "parser.y"
             {(yyval.ast) = AST.addNode((yyvsp[0].string), NULL, NULL); printf("\n RECOGNIZED RULE: Simplest expression: %s \n", (yyvsp[0].string)); }
#line 1506 "parser.tab.c"
    break;

  case 36: /* Expr: Expr MULT Expr  */
#line 241 "parser.y"
                                {printf("\n RECOGNIZED RULE: Expr*Expr statement\n");
				(yyval.ast) = AST.addNode("*",(yyvsp[0].ast),(yyvsp[-2].ast));
				}
#line 1514 "parser.tab.c"
    break;

  case 37: /* Expr: Expr MULT Primary  */
#line 244 "parser.y"
                                {printf("\n RECOGNIZED RULE: Expr*Prime statement\n");
				(yyval.ast) = AST.addNode("*",(yyvsp[-2].ast),(yyvsp[0].ast));
				}
#line 1522 "parser.tab.c"
    break;

  case 38: /* Expr: Expr PLUS Expr  */
#line 247 "parser.y"
                                {printf("\n RECOGNIZED RULE: MULT statement\n");
				cout << "\n\nPLUS\n";
				(yyval.ast) = AST.addNode("+",(yyvsp[0].ast),(yyvsp[-2].ast));
				}
#line 1531 "parser.tab.c"
    break;

  case 39: /* Expr: Primary PLUS Expr  */
#line 251 "parser.y"
                                {printf("\n RECOGNIZED RULE: MULT statement\n");
				(yyval.ast) = AST.addNode("+",(yyvsp[-2].ast),(yyvsp[0].ast));
				}
#line 1539 "parser.tab.c"
    break;

  case 40: /* Expr: Primary PLUS Primary  */
#line 254 "parser.y"
                                {printf("\n RECOGNIZED RULE: MULT statement\n");
				(yyval.ast) = AST.addNode("+",(yyvsp[-2].ast),(yyvsp[0].ast));
				}
#line 1547 "parser.tab.c"
    break;

  case 41: /* Expr: Primary DIV Expr  */
#line 257 "parser.y"
                                {printf("\n RECOGNIZED RULE: DIV statement\n");
				(yyval.ast) = AST.addNode("/",(yyvsp[-2].ast),(yyvsp[0].ast));
				}
#line 1555 "parser.tab.c"
    break;

  case 42: /* Expr: Primary DIV Primary  */
#line 260 "parser.y"
                                {printf("\n RECOGNIZED RULE: DIV statement\n");
				(yyval.ast) = AST.addNode("/",(yyvsp[-2].ast),(yyvsp[0].ast));
				}
#line 1563 "parser.tab.c"
    break;

  case 43: /* Expr: Primary MINUS Expr  */
#line 263 "parser.y"
                                {printf("\n RECOGNIZED RULE: MINUS statement\n");
				(yyval.ast) = AST.addNode("-",(yyvsp[-2].ast),(yyvsp[0].ast));
				}
#line 1571 "parser.tab.c"
    break;

  case 44: /* Expr: Primary MINUS Primary  */
#line 266 "parser.y"
                                {printf("\n RECOGNIZED RULE: MINUS statement\n");
				(yyval.ast) = AST.addNode("-",(yyvsp[-2].ast),(yyvsp[0].ast));
				}
#line 1579 "parser.tab.c"
    break;

  case 45: /* IfBlock: Block  */
#line 271 "parser.y"
               {(yyval.ast) = AST.addNode("Block", (yyvsp[0].ast),NULL);}
#line 1585 "parser.tab.c"
    break;

  case 46: /* IfBlock: Block ELSE Block  */
#line 272 "parser.y"
                                   {printf("\nELSE\n");
			(yyval.ast) = AST.addNode("Block", (yyvsp[-2].ast),AST.addNode("ELSE",AST.addNode("Block",(yyvsp[0].ast),NULL),NULL));}
#line 1592 "parser.tab.c"
    break;

  case 47: /* Primary: ID  */
#line 276 "parser.y"
                                                        {(yyval.ast) = AST.addNode((yyvsp[0].string), NULL, NULL);
								printf("\nPrimary BS \n");
								}
#line 1600 "parser.tab.c"
    break;

  case 48: /* Primary: NUMBER  */
#line 279 "parser.y"
                                                        {(yyval.ast) = AST.addNum((yyvsp[0].number));}
#line 1606 "parser.tab.c"
    break;

  case 49: /* Primary: ID LPAR ExprList RPAR  */
#line 280 "parser.y"
                                                {(yyval.ast) = AST.addNode("FuncCall",AST.addNode((yyvsp[-3].string), NULL, NULL),(yyvsp[-1].ast));
									//FINISH NodeType
									}
#line 1614 "parser.tab.c"
    break;

  case 50: /* Primary: ID LBRA NUMBER RBRA  */
#line 283 "parser.y"
                                        {
								cout << ">> ID[]\n";
								string idArray = cBS((yyvsp[-3].string)) + "[" + to_string((yyvsp[-1].number)) + "]";
								(yyval.ast) = AST.addNode(idArray, NULL, NULL);
								}
#line 1624 "parser.tab.c"
    break;

  case 51: /* ExprList: %empty  */
#line 291 "parser.y"
                                                {(yyval.ast) = NULL;}
#line 1630 "parser.tab.c"
    break;

  case 52: /* ExprList: Expr  */
#line 292 "parser.y"
                                                        {(yyval.ast) = (yyvsp[0].ast);}
#line 1636 "parser.tab.c"
    break;

  case 53: /* ExprList: Expr COMMA ExprList  */
#line 293 "parser.y"
                                              {(yyval.ast) = AST.addNode("ExprList",(yyvsp[-2].ast),(yyvsp[0].ast));
											//FINISH
			}
#line 1644 "parser.tab.c"
    break;


#line 1648 "parser.tab.c"

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

#line 297 "parser.y"


int main(int argc, char**argv)
{
/*
	#ifdef YYDEBUG
		yydebug = 1;
	#endif
*/
	printf("\n\n##### COMPILER STARTED #####\n\n");
	
	if (argc > 1){
	  if(!(yyin = fopen(argv[1], "r")))
          {
		perror(argv[1]);
		return(1);
	  }
	}
	yyparse();
	AST.printTree(AST.root,0);
	openIRFile();
	AST.genIR(AST.root);
	closeIRFile();
	openASMFile();
	ASMGen();
	closeASMFile();
}

void yyerror(const char* s) {
	fprintf(stderr, "Parse error: %s\n", s);
	exit(1);
}
