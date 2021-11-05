/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
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
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 2

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 2 "yacc_sql.y"


#include "sql/parser/parse_defs.h"
#include "sql/parser/yacc_sql.tab.h"
#include "sql/parser/lex.yy.h"
// #include "common/log/log.h" // 包含C++中的头文件

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct ParserContext {
  Query * ssql;
  size_t select_length;
  size_t condition_length;
  size_t from_length;
  size_t value_length;
  size_t order_length;
  Value values[MAX_NUM];
  Condition conditions[MAX_NUM];
  Order orders[MAX_NUM];
  CompOp comp;
  OrderType order_type;
	char id[MAX_NUM];
} ParserContext;

//获取子串
char *substr(const char *s,int n1,int n2)/*从s中提取下标为n1~n2的字符组成一个新字符串，然后返回这个新串的首地址*/
{
  char *sp = malloc(sizeof(char) * (n2 - n1 + 2));
  int i, j = 0;
  for (i = n1; i <= n2; i++) {
    sp[j++] = s[i];
  }
  sp[j] = 0;
  return sp;
}

void yyerror(yyscan_t scanner, const char *str)
{
  ParserContext *context = (ParserContext *)(yyget_extra(scanner));
  query_reset(context->ssql);
  context->ssql->flag = SCF_ERROR;
  context->condition_length = 0;
  context->from_length = 0;
  context->select_length = 0;
  context->value_length = 0;
  context->order_length = 0;
  context->ssql->sstr.insertion.value_num = 0;
  context->ssql->sstr.errors = str;
  printf("parse sql failed. error=%s\n", str);
}

ParserContext *get_context(yyscan_t scanner)
{
  return (ParserContext *)yyget_extra(scanner);
}

#define CONTEXT get_context(scanner)


#line 132 "yacc_sql.tab.c"

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

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_YACC_SQL_TAB_H_INCLUDED
# define YY_YY_YACC_SQL_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    SEMICOLON = 258,
    CREATE = 259,
    DROP = 260,
    NULL_T = 261,
    NULLABLE_T = 262,
    TABLE = 263,
    TABLES = 264,
    INDEX = 265,
    SELECT = 266,
    MAX = 267,
    MIN = 268,
    COUNT = 269,
    AVG = 270,
    DESC = 271,
    SHOW = 272,
    SYNC = 273,
    INSERT = 274,
    DELETE = 275,
    UPDATE = 276,
    LBRACE = 277,
    RBRACE = 278,
    COMMA = 279,
    TRX_BEGIN = 280,
    TRX_COMMIT = 281,
    TRX_ROLLBACK = 282,
    INT_T = 283,
    STRING_T = 284,
    FLOAT_T = 285,
    TEXT_T = 286,
    DATE_T = 287,
    HELP = 288,
    EXIT = 289,
    DOT = 290,
    INTO = 291,
    VALUES = 292,
    FROM = 293,
    WHERE = 294,
    IN = 295,
    AND = 296,
    GROUP = 297,
    SET = 298,
    INNER = 299,
    JOIN = 300,
    ON = 301,
    IS = 302,
    LOAD = 303,
    DATA = 304,
    INFILE = 305,
    UNIQUE = 306,
    ASC = 307,
    ORDER = 308,
    BY = 309,
    EQ = 310,
    LT = 311,
    GT = 312,
    LE = 313,
    GE = 314,
    NE = 315,
    NOT = 316,
    NUMBER = 317,
    FLOAT = 318,
    ID = 319,
    PATH = 320,
    SSS = 321,
    STAR = 322,
    STRING_V = 323
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 130 "yacc_sql.y"

  struct _Attr *attr;
  struct _Condition *condition1;
  struct _Value *value1;
  char *string;
  void *ptr;
  int number;
  float floats;
	char *position;

#line 264 "yacc_sql.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif



int yyparse (void *scanner);

#endif /* !YY_YY_YACC_SQL_TAB_H_INCLUDED  */



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
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
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

#if ! defined yyoverflow || YYERROR_VERBOSE

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
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


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
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   248

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  69
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  45
/* YYNRULES -- Number of rules.  */
#define YYNRULES  120
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  264

#define YYUNDEFTOK  2
#define YYMAXUTOK   323


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

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
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   162,   162,   164,   168,   169,   170,   171,   172,   173,
     174,   175,   176,   177,   178,   179,   180,   181,   182,   183,
     184,   188,   193,   198,   204,   210,   216,   222,   228,   234,
     241,   246,   254,   257,   264,   271,   280,   282,   286,   294,
     311,   312,   313,   318,   322,   323,   324,   325,   326,   330,
     331,   332,   333,   337,   339,   344,   351,   353,   359,   368,
     370,   375,   379,   383,   388,   395,   406,   416,   440,   442,
     449,   455,   461,   467,   473,   479,   485,   493,   495,   502,
     509,   515,   521,   527,   535,   537,   542,   544,   549,   551,
     558,   561,   564,   569,   650,   652,   657,   664,   666,   671,
     679,   680,   681,   682,   683,   684,   685,   686,   687,   688,
     692,   699,   701,   707,   713,   719,   726,   728,   735,   741,
     747
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "SEMICOLON", "CREATE", "DROP", "NULL_T",
  "NULLABLE_T", "TABLE", "TABLES", "INDEX", "SELECT", "MAX", "MIN",
  "COUNT", "AVG", "DESC", "SHOW", "SYNC", "INSERT", "DELETE", "UPDATE",
  "LBRACE", "RBRACE", "COMMA", "TRX_BEGIN", "TRX_COMMIT", "TRX_ROLLBACK",
  "INT_T", "STRING_T", "FLOAT_T", "TEXT_T", "DATE_T", "HELP", "EXIT",
  "DOT", "INTO", "VALUES", "FROM", "WHERE", "IN", "AND", "GROUP", "SET",
  "INNER", "JOIN", "ON", "IS", "LOAD", "DATA", "INFILE", "UNIQUE", "ASC",
  "ORDER", "BY", "EQ", "LT", "GT", "LE", "GE", "NE", "NOT", "NUMBER",
  "FLOAT", "ID", "PATH", "SSS", "STAR", "STRING_V", "$accept", "commands",
  "command", "exit", "help", "sync", "begin", "commit", "rollback",
  "drop_table", "show_tables", "desc_table", "create_index", "ID_list",
  "drop_index", "create_table", "attr_def_list", "attr_def", "null_def",
  "number", "type", "agg_type", "order_type", "ID_get",
  "insert_value_list", "insert", "value_list", "value", "delete", "update",
  "select", "join_list", "select_attr", "attr_list", "rel_list", "where",
  "condition_list", "condition_field", "condition", "group_by",
  "group_by_attr_list", "comOp", "load_data", "order", "order_attrs", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323
};
# endif

#define YYPACT_NINF (-196)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -196,    23,  -196,    21,    25,     0,   -54,    27,    51,    -6,
      17,    14,    55,    83,    95,    96,    97,    52,  -196,  -196,
    -196,  -196,  -196,  -196,  -196,  -196,  -196,  -196,  -196,  -196,
    -196,  -196,  -196,  -196,  -196,  -196,    42,    43,    98,    54,
      67,  -196,  -196,  -196,  -196,     2,  -196,    94,    81,   126,
     133,  -196,    73,    82,    99,  -196,  -196,  -196,  -196,  -196,
     104,   122,   101,    91,   153,   154,     6,   100,  -196,    68,
     102,  -196,  -196,   123,   119,   103,    93,   105,   106,   115,
    -196,  -196,    78,   140,   139,  -196,    61,   142,   145,   127,
     150,    -3,   170,   120,   138,  -196,   152,   121,   155,   114,
     116,  -196,    76,  -196,   139,   117,   139,   139,   134,   158,
       3,  -196,  -196,  -196,   148,  -196,  -196,    65,   143,  -196,
       3,   177,   105,   163,  -196,  -196,  -196,  -196,  -196,     1,
     114,   164,   165,   139,    62,   166,   167,  -196,   168,  -196,
    -196,   128,   129,   119,   171,   130,  -196,   135,  -196,  -196,
    -196,  -196,  -196,  -196,   157,    -3,    -3,  -196,   119,   136,
     152,   195,  -196,   193,   179,   180,   114,   141,  -196,   139,
     144,   139,   139,   139,   156,   127,   162,     3,   183,  -196,
    -196,  -196,  -196,   143,   204,   206,  -196,  -196,  -196,   149,
     207,  -196,   189,  -196,   190,  -196,  -196,  -196,    -3,   158,
     160,   169,   171,   191,  -196,  -196,  -196,   194,  -196,   213,
     139,   143,  -196,   159,   172,   215,  -196,   197,   217,  -196,
    -196,  -196,   127,    79,   161,  -196,     3,  -196,  -196,   173,
     174,  -196,    58,   171,    80,   200,  -196,   175,   176,  -196,
     203,  -196,   198,   178,  -196,  -196,    59,    57,  -196,   191,
     200,   181,   203,  -196,   203,  -196,  -196,  -196,    57,  -196,
    -196,   203,  -196,  -196
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       2,     0,     1,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     3,    20,
      19,    14,    15,    16,    17,     9,    10,    11,    12,    13,
       8,     5,     7,     6,     4,    18,     0,     0,     0,     0,
       0,    49,    50,    51,    52,    77,    70,     0,     0,     0,
       0,    23,     0,     0,     0,    24,    25,    26,    22,    21,
       0,     0,     0,     0,     0,     0,     0,     0,    71,     0,
       0,    29,    28,     0,    86,     0,     0,     0,     0,     0,
      27,    34,    77,     0,    77,    43,     0,     0,     0,    68,
       0,     0,     0,     0,     0,    55,    36,     0,     0,     0,
       0,    78,     0,    72,    77,     0,    77,    77,     0,    84,
       0,    64,    61,    62,    91,    63,    90,     0,    88,    65,
       0,     0,     0,     0,    44,    45,    46,    48,    47,    40,
       0,    32,     0,    77,     0,     0,     0,    75,     0,    73,
      74,     0,     0,    86,    59,     0,   108,   106,   100,   101,
     102,   103,   104,   105,     0,     0,     0,    87,    86,     0,
      36,     0,    41,     0,    39,     0,     0,     0,    79,    77,
       0,    77,    77,    77,     0,    68,    94,     0,     0,    92,
     107,   109,    93,    88,     0,     0,    37,    35,    42,     0,
       0,    33,     0,    82,     0,    80,    81,    76,     0,    84,
       0,   111,    59,    56,    89,    66,   110,     0,    30,     0,
      77,    88,    85,     0,     0,     0,    60,     0,     0,    38,
      31,    83,    68,    97,     0,    67,     0,    58,    69,     0,
       0,    95,   116,    59,    97,    97,    54,     0,     0,    53,
     116,   113,     0,     0,    98,    96,   116,   116,   112,    56,
      97,     0,   116,   118,   116,   114,    57,    99,   116,   117,
     115,   116,   119,   120
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -196,  -196,  -196,  -196,  -196,  -196,  -196,  -196,  -196,  -196,
    -196,  -196,  -196,  -114,  -196,  -196,    69,   108,  -196,   -97,
    -196,   182,  -170,  -196,   -21,  -196,  -195,  -109,  -196,  -196,
    -196,  -169,  -196,   -82,    32,  -111,  -166,    77,  -152,  -196,
    -155,  -196,  -196,  -196,  -113
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,   132,    29,    30,   123,    96,   164,    88,
     129,    47,   240,    97,   218,    31,   178,   116,    32,    33,
      34,   109,    48,    68,   143,    92,   157,   117,   118,   201,
     231,   155,    35,   215,   241
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     101,   144,   103,   111,   183,   136,   199,   216,   162,   111,
      49,   158,    41,    42,    43,    44,   165,   204,    41,    42,
      43,    44,   137,     2,   139,   140,    66,     3,     4,    36,
      52,    37,   176,    39,     5,    40,    50,    67,   242,     6,
       7,     8,     9,    10,    11,   222,   211,   184,    12,    13,
      14,   168,   191,   228,    51,    53,    15,    16,    55,   112,
     113,   114,   163,   115,    45,   112,   113,    46,   202,   115,
      82,    17,    38,   236,   236,   236,   252,   254,    54,   244,
     245,   237,   237,   237,   104,   169,    56,   193,   261,   195,
     196,   197,   207,   238,   251,   257,   105,   170,    57,    58,
      59,    60,    66,   229,   229,   146,    61,    62,    63,   239,
     239,   239,   147,   100,   230,   243,    69,   233,    64,    70,
     148,   149,   150,   151,   152,   153,   154,   248,   221,    71,
      85,    65,    86,   253,   255,    87,    72,    73,    85,   259,
     134,   260,    75,   135,    77,   262,    74,    78,   263,   124,
     125,   126,   127,   128,    76,    79,    80,    81,    91,    94,
      90,    99,   102,    66,    84,   106,    89,    93,   107,    95,
      98,   108,   110,   119,   121,   120,   122,   130,   131,   141,
     133,   138,   142,   145,   156,   159,   161,   167,   166,   171,
     172,   173,   174,   175,   179,   177,   180,   181,   187,   188,
     185,   189,   198,   190,   200,   192,   203,   205,   194,   206,
     208,    85,   209,   210,   213,   217,   220,   219,   225,   226,
     227,   249,   214,   223,   229,   232,   224,   237,   256,   186,
     160,   212,   182,     0,     0,     0,     0,   234,   235,   246,
     247,     0,   250,     0,     0,   258,     0,     0,    83
};

static const yytype_int16 yycheck[] =
{
      82,   110,    84,     6,   156,   102,   175,   202,     7,     6,
      64,   120,    12,    13,    14,    15,   130,   183,    12,    13,
      14,    15,   104,     0,   106,   107,    24,     4,     5,     8,
      36,    10,   143,     8,    11,    10,     9,    35,   233,    16,
      17,    18,    19,    20,    21,   211,   198,   158,    25,    26,
      27,   133,   166,   222,     3,    38,    33,    34,     3,    62,
      63,    64,    61,    66,    64,    62,    63,    67,   177,    66,
      64,    48,    51,    16,    16,    16,   246,   247,    64,   234,
     235,    24,    24,    24,    23,    23,     3,   169,   258,   171,
     172,   173,   189,    35,    35,   250,    35,    35,     3,     3,
       3,    49,    24,    24,    24,    40,    64,    64,    10,    52,
      52,    52,    47,    35,    35,    35,    22,   226,    64,    38,
      55,    56,    57,    58,    59,    60,    61,   240,   210,     3,
      62,    64,    64,   246,   247,    67,     3,    64,    62,   252,
      64,   254,    43,    67,    22,   258,    64,    46,   261,    28,
      29,    30,    31,    32,    50,    64,     3,     3,    39,    66,
      37,    46,    22,    24,    64,    23,    64,    64,    23,    64,
      64,    44,    22,     3,    36,    55,    24,    22,    64,    45,
      64,    64,    24,    35,    41,     8,    23,    22,    24,    23,
      23,    23,    64,    64,    64,    24,    61,    40,     3,     6,
      64,    22,    46,    23,    42,    64,    23,     3,    64,     3,
       3,    62,    23,    23,    54,    24,     3,    23,     3,    22,
       3,    23,    53,    64,    24,    64,    54,    24,   249,   160,
     122,   199,   155,    -1,    -1,    -1,    -1,    64,    64,    64,
      64,    -1,    64,    -1,    -1,    64,    -1,    -1,    66
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    70,     0,     4,     5,    11,    16,    17,    18,    19,
      20,    21,    25,    26,    27,    33,    34,    48,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    83,
      84,    94,    97,    98,    99,   111,     8,    10,    51,     8,
      10,    12,    13,    14,    15,    64,    67,    90,   101,    64,
       9,     3,    36,    38,    64,     3,     3,     3,     3,     3,
      49,    64,    64,    10,    64,    64,    24,    35,   102,    22,
      38,     3,     3,    64,    64,    43,    50,    22,    46,    64,
       3,     3,    64,    90,    64,    62,    64,    67,    88,    64,
      37,    39,   104,    64,    66,    64,    86,    92,    64,    46,
      35,   102,    22,   102,    23,    35,    23,    23,    44,   100,
      22,     6,    62,    63,    64,    66,    96,   106,   107,     3,
      55,    36,    24,    85,    28,    29,    30,    31,    32,    89,
      22,    64,    82,    64,    64,    67,    88,   102,    64,   102,
     102,    45,    24,   103,    96,    35,    40,    47,    55,    56,
      57,    58,    59,    60,    61,   110,    41,   105,    96,     8,
      86,    23,     7,    61,    87,    82,    24,    22,   102,    23,
      35,    23,    23,    23,    64,    64,   104,    24,    95,    64,
      61,    40,   106,   107,   104,    64,    85,     3,     6,    22,
      23,    82,    64,   102,    64,   102,   102,   102,    46,   100,
      42,   108,    96,    23,   105,     3,     3,    88,     3,    23,
      23,   107,   103,    54,    53,   112,    95,    24,    93,    23,
       3,   102,   105,    64,    54,     3,    22,     3,   100,    24,
      35,   109,    64,    96,    64,    64,    16,    24,    35,    52,
      91,   113,    95,    35,   109,   109,    64,    64,   113,    23,
      64,    35,    91,   113,    91,   113,    93,   109,    64,   113,
     113,    91,   113,   113
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    69,    70,    70,    71,    71,    71,    71,    71,    71,
      71,    71,    71,    71,    71,    71,    71,    71,    71,    71,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    81,    82,    82,    83,    84,    85,    85,    86,    86,
      87,    87,    87,    88,    89,    89,    89,    89,    89,    90,
      90,    90,    90,    91,    91,    92,    93,    93,    94,    95,
      95,    96,    96,    96,    96,    97,    98,    99,   100,   100,
     101,   101,   101,   101,   101,   101,   101,   102,   102,   102,
     102,   102,   102,   102,   103,   103,   104,   104,   105,   105,
     106,   106,   106,   107,   108,   108,   108,   109,   109,   109,
     110,   110,   110,   110,   110,   110,   110,   110,   110,   110,
     111,   112,   112,   112,   112,   112,   113,   113,   113,   113,
     113
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     2,     2,     2,     2,     2,     4,     3,     3,
       9,    10,     1,     3,     4,     8,     0,     3,     6,     3,
       0,     1,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     6,    10,     0,
       3,     1,     1,     1,     1,     5,     8,    10,     0,     7,
       1,     2,     4,     5,     5,     5,     7,     0,     3,     5,
       6,     6,     6,     8,     0,     4,     0,     3,     0,     3,
       1,     1,     3,     3,     0,     4,     6,     0,     3,     5,
       1,     1,     1,     1,     1,     1,     1,     2,     1,     2,
       8,     0,     5,     4,     6,     7,     0,     4,     3,     5,
       6
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


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
        yyerror (scanner, YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



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

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, scanner); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, void *scanner)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  YYUSE (scanner);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, void *scanner)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep, scanner);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule, void *scanner)
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
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                                              , scanner);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule, scanner); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, void *scanner)
{
  YYUSE (yyvaluep);
  YYUSE (scanner);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void *scanner)
{
/* The lookahead symbol.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

    /* Number of syntax errors so far.  */
    int yynerrs;

    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYPTRDIFF_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
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

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
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
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
# undef YYSTACK_RELOCATE
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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex (&yylval, scanner);
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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
  case 21:
#line 188 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_EXIT;//"exit";
    }
#line 1631 "yacc_sql.tab.c"
    break;

  case 22:
#line 193 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_HELP;//"help";
    }
#line 1639 "yacc_sql.tab.c"
    break;

  case 23:
#line 198 "yacc_sql.y"
                   {
      CONTEXT->ssql->flag = SCF_SYNC;
    }
#line 1647 "yacc_sql.tab.c"
    break;

  case 24:
#line 204 "yacc_sql.y"
                        {
      CONTEXT->ssql->flag = SCF_BEGIN;
    }
#line 1655 "yacc_sql.tab.c"
    break;

  case 25:
#line 210 "yacc_sql.y"
                         {
      CONTEXT->ssql->flag = SCF_COMMIT;
    }
#line 1663 "yacc_sql.tab.c"
    break;

  case 26:
#line 216 "yacc_sql.y"
                           {
      CONTEXT->ssql->flag = SCF_ROLLBACK;
    }
#line 1671 "yacc_sql.tab.c"
    break;

  case 27:
#line 222 "yacc_sql.y"
                            {
        CONTEXT->ssql->flag = SCF_DROP_TABLE;//"drop_table";
        drop_table_init(&CONTEXT->ssql->sstr.drop_table, (yyvsp[-1].string));
    }
#line 1680 "yacc_sql.tab.c"
    break;

  case 28:
#line 228 "yacc_sql.y"
                          {
      CONTEXT->ssql->flag = SCF_SHOW_TABLES;
    }
#line 1688 "yacc_sql.tab.c"
    break;

  case 29:
#line 234 "yacc_sql.y"
                      {
      CONTEXT->ssql->flag = SCF_DESC_TABLE;
      desc_table_init(&CONTEXT->ssql->sstr.desc_table, (yyvsp[-1].string));
    }
#line 1697 "yacc_sql.tab.c"
    break;

  case 30:
#line 242 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
			create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-6].string), (yyvsp[-4].string), (yyvsp[-2].string));
		}
#line 1706 "yacc_sql.tab.c"
    break;

  case 31:
#line 247 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_CREATE_UNIQUE_INDEX;// "create_unique_index";
			create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-6].string), (yyvsp[-4].string), (yyvsp[-2].string));
    		}
#line 1715 "yacc_sql.tab.c"
    break;

  case 32:
#line 254 "yacc_sql.y"
                {
    			(yyval.string) = (yyvsp[0].string);
    		}
#line 1723 "yacc_sql.tab.c"
    break;

  case 33:
#line 258 "yacc_sql.y"
                {
			(yyval.string) = (yyvsp[-2].string);
    		}
#line 1731 "yacc_sql.tab.c"
    break;

  case 34:
#line 265 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_DROP_INDEX;//"drop_index";
			drop_index_init(&CONTEXT->ssql->sstr.drop_index, (yyvsp[-1].string));
		}
#line 1740 "yacc_sql.tab.c"
    break;

  case 35:
#line 272 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_CREATE_TABLE;//"create_table";
			// CONTEXT->ssql->sstr.create_table.attribute_count = CONTEXT->value_length;
			create_table_init_name(&CONTEXT->ssql->sstr.create_table, (yyvsp[-5].string));
			//临时变量清零	
			CONTEXT->value_length = 0;
		}
#line 1752 "yacc_sql.tab.c"
    break;

  case 37:
#line 282 "yacc_sql.y"
                                   {    }
#line 1758 "yacc_sql.tab.c"
    break;

  case 38:
#line 287 "yacc_sql.y"
                {
			AttrInfo attribute;
			// 我们让nullable的列增加4个字节
			attr_info_init(&attribute, CONTEXT->id, (yyvsp[-4].number), (yyvsp[-1].number) + (yyvsp[-3].number) * 4, (yyvsp[-3].number));
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			CONTEXT->value_length++;
		}
#line 1770 "yacc_sql.tab.c"
    break;

  case 39:
#line 295 "yacc_sql.y"
                {
			AttrInfo attribute;
			// 这里我们可以让nullable的属性列长度增加4个字节
			if ((yyvsp[-1].number) == TEXTS) {
				// TEXTS默认为4096字节
				attr_info_init(&attribute, CONTEXT->id, CHARS, 4096 + (yyvsp[0].number) * 4, (yyvsp[0].number));
			} else {
				attr_info_init(&attribute, CONTEXT->id, (yyvsp[-1].number), 4 + (yyvsp[0].number) * 4, (yyvsp[0].number));
			}
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			CONTEXT->value_length++;
		}
#line 1787 "yacc_sql.tab.c"
    break;

  case 40:
#line 311 "yacc_sql.y"
          { (yyval.number) = 0; }
#line 1793 "yacc_sql.tab.c"
    break;

  case 41:
#line 312 "yacc_sql.y"
                     { (yyval.number) = 1; }
#line 1799 "yacc_sql.tab.c"
    break;

  case 42:
#line 313 "yacc_sql.y"
                     { (yyval.number) = 0; }
#line 1805 "yacc_sql.tab.c"
    break;

  case 43:
#line 318 "yacc_sql.y"
                       {(yyval.number) = (yyvsp[0].number);}
#line 1811 "yacc_sql.tab.c"
    break;

  case 44:
#line 322 "yacc_sql.y"
              { (yyval.number)=INTS; }
#line 1817 "yacc_sql.tab.c"
    break;

  case 45:
#line 323 "yacc_sql.y"
                  { (yyval.number)=CHARS; }
#line 1823 "yacc_sql.tab.c"
    break;

  case 46:
#line 324 "yacc_sql.y"
                 { (yyval.number)=FLOATS; }
#line 1829 "yacc_sql.tab.c"
    break;

  case 47:
#line 325 "yacc_sql.y"
                { (yyval.number)=DATE; }
#line 1835 "yacc_sql.tab.c"
    break;

  case 48:
#line 326 "yacc_sql.y"
                { (yyval.number) = TEXTS; }
#line 1841 "yacc_sql.tab.c"
    break;

  case 49:
#line 330 "yacc_sql.y"
            { (yyval.number) = AGG_MAX; }
#line 1847 "yacc_sql.tab.c"
    break;

  case 50:
#line 331 "yacc_sql.y"
              { (yyval.number) = AGG_MIN; }
#line 1853 "yacc_sql.tab.c"
    break;

  case 51:
#line 332 "yacc_sql.y"
                { (yyval.number) = AGG_COUNT; }
#line 1859 "yacc_sql.tab.c"
    break;

  case 52:
#line 333 "yacc_sql.y"
              { (yyval.number) = AGG_AVG; }
#line 1865 "yacc_sql.tab.c"
    break;

  case 53:
#line 337 "yacc_sql.y"
            {
	(yyval.number) = ORDER_ASC; printf("I am ASC\n");}
#line 1872 "yacc_sql.tab.c"
    break;

  case 54:
#line 339 "yacc_sql.y"
               {
	(yyval.number) = ORDER_DESC; printf("I am DESC\n");}
#line 1879 "yacc_sql.tab.c"
    break;

  case 55:
#line 345 "yacc_sql.y"
        {
		char *temp=(yyvsp[0].string); 
		snprintf(CONTEXT->id, sizeof(CONTEXT->id), "%s", temp);
	}
#line 1888 "yacc_sql.tab.c"
    break;

  case 57:
#line 354 "yacc_sql.y"
                {

    		}
#line 1896 "yacc_sql.tab.c"
    break;

  case 58:
#line 360 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_INSERT;//"insert";
			inserts_init(&CONTEXT->ssql->sstr.insertion, (yyvsp[-7].string), CONTEXT->values, CONTEXT->value_length);

      			//临时变量清零
      			CONTEXT->value_length=0;
    		}
#line 1908 "yacc_sql.tab.c"
    break;

  case 60:
#line 370 "yacc_sql.y"
                              { 
  		// CONTEXT->values[CONTEXT->value_length++] = *$2;
	  }
#line 1916 "yacc_sql.tab.c"
    break;

  case 61:
#line 376 "yacc_sql.y"
                {
  			value_init_integer(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].number));
		}
#line 1924 "yacc_sql.tab.c"
    break;

  case 62:
#line 380 "yacc_sql.y"
                {
  			value_init_float(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].floats));
		}
#line 1932 "yacc_sql.tab.c"
    break;

  case 63:
#line 384 "yacc_sql.y"
                {
			(yyvsp[0].string) = substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
  			value_init_string(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].string));
		}
#line 1941 "yacc_sql.tab.c"
    break;

  case 64:
#line 389 "yacc_sql.y"
                {
    			value_init_null(&CONTEXT->values[CONTEXT->value_length++]);
    		}
#line 1949 "yacc_sql.tab.c"
    break;

  case 65:
#line 396 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_DELETE;//"delete";
			deletes_init_relation(&CONTEXT->ssql->sstr.deletion, (yyvsp[-2].string));
			deletes_set_conditions(&CONTEXT->ssql->sstr.deletion, 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;	
    }
#line 1961 "yacc_sql.tab.c"
    break;

  case 66:
#line 407 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_UPDATE;//"update";
			Value *value = &CONTEXT->values[0];
			updates_init(&CONTEXT->ssql->sstr.update, (yyvsp[-6].string), (yyvsp[-4].string), value, 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;
		}
#line 1973 "yacc_sql.tab.c"
    break;

  case 67:
#line 417 "yacc_sql.y"
                {
			// CONTEXT->ssql->sstr.selection.relations[CONTEXT->from_length++]=$4;
			selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-6].string));
			selects_append_conditions(&CONTEXT->ssql->sstr.selection, CONTEXT->conditions, CONTEXT->condition_length);

			CONTEXT->ssql->flag=SCF_SELECT;//"select";
			// CONTEXT->ssql->sstr.selection.attr_num = CONTEXT->select_length;

			//临时变量清零
			CONTEXT->condition_length=0;
			CONTEXT->from_length=0;
			CONTEXT->select_length=0;
			CONTEXT->value_length = 0;
	}
#line 1992 "yacc_sql.tab.c"
    break;

  case 69:
#line 443 "yacc_sql.y"
                {
			selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-4].string));
		}
#line 2000 "yacc_sql.tab.c"
    break;

  case 70:
#line 450 "yacc_sql.y"
                {
			RelAttr attr;
			relation_attr_init(&attr, NULL, "*");
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 2010 "yacc_sql.tab.c"
    break;

  case 71:
#line 456 "yacc_sql.y"
                {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 2020 "yacc_sql.tab.c"
    break;

  case 72:
#line 462 "yacc_sql.y"
                {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 2030 "yacc_sql.tab.c"
    break;

  case 73:
#line 468 "yacc_sql.y"
                {
			AggDesc agg_desc;
			agg_desc_init_string(&agg_desc, (yyvsp[-4].number), AGG_STAR, NULL, "*");
			selects_append_agg(&CONTEXT->ssql->sstr.selection, &agg_desc);
		}
#line 2040 "yacc_sql.tab.c"
    break;

  case 74:
#line 474 "yacc_sql.y"
                {
			AggDesc agg_desc;
			agg_desc_init_number(&agg_desc, (yyvsp[-4].number), AGG_NUMBER, (yyvsp[-2].number));
			selects_append_agg(&CONTEXT->ssql->sstr.selection, &agg_desc);
		}
#line 2050 "yacc_sql.tab.c"
    break;

  case 75:
#line 480 "yacc_sql.y"
                {
			AggDesc agg_desc;
			agg_desc_init_string(&agg_desc, (yyvsp[-4].number), AGG_FIELD, NULL, (yyvsp[-2].string));
			selects_append_agg(&CONTEXT->ssql->sstr.selection, &agg_desc);
		}
#line 2060 "yacc_sql.tab.c"
    break;

  case 76:
#line 486 "yacc_sql.y"
                {
			AggDesc agg_desc;
			agg_desc_init_string(&agg_desc, (yyvsp[-6].number), AGG_FIELD, (yyvsp[-4].string), (yyvsp[-2].string));
			selects_append_agg(&CONTEXT->ssql->sstr.selection, &agg_desc);
		}
#line 2070 "yacc_sql.tab.c"
    break;

  case 78:
#line 495 "yacc_sql.y"
                         {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
     	  // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length].relation_name = NULL;
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length++].attribute_name=$2;
      }
#line 2082 "yacc_sql.tab.c"
    break;

  case 79:
#line 502 "yacc_sql.y"
                                {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length].attribute_name=$4;
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length++].relation_name=$2;
  	  }
#line 2094 "yacc_sql.tab.c"
    break;

  case 80:
#line 510 "yacc_sql.y"
                {
			AggDesc agg_desc;
			agg_desc_init_string(&agg_desc, (yyvsp[-4].number), AGG_STAR, NULL, "*");
			selects_append_agg(&CONTEXT->ssql->sstr.selection, &agg_desc);
		}
#line 2104 "yacc_sql.tab.c"
    break;

  case 81:
#line 516 "yacc_sql.y"
                {
			AggDesc agg_desc;
			agg_desc_init_number(&agg_desc, (yyvsp[-4].number), AGG_NUMBER, (yyvsp[-2].number));
			selects_append_agg(&CONTEXT->ssql->sstr.selection, &agg_desc);
		}
#line 2114 "yacc_sql.tab.c"
    break;

  case 82:
#line 522 "yacc_sql.y"
                {
			AggDesc agg_desc;
			agg_desc_init_string(&agg_desc, (yyvsp[-4].number), AGG_FIELD, NULL, (yyvsp[-2].string));
			selects_append_agg(&CONTEXT->ssql->sstr.selection, &agg_desc);
		}
#line 2124 "yacc_sql.tab.c"
    break;

  case 83:
#line 528 "yacc_sql.y"
                {
			AggDesc agg_desc;
			agg_desc_init_string(&agg_desc, (yyvsp[-6].number), AGG_FIELD, (yyvsp[-4].string), (yyvsp[-2].string));
			selects_append_agg(&CONTEXT->ssql->sstr.selection, &agg_desc);
		}
#line 2134 "yacc_sql.tab.c"
    break;

  case 85:
#line 538 "yacc_sql.y"
                {
			selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-2].string));
		}
#line 2142 "yacc_sql.tab.c"
    break;

  case 87:
#line 545 "yacc_sql.y"
                {
			// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
		}
#line 2150 "yacc_sql.tab.c"
    break;

  case 89:
#line 552 "yacc_sql.y"
                {
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
		}
#line 2158 "yacc_sql.tab.c"
    break;

  case 90:
#line 558 "yacc_sql.y"
              {
		(yyval.ptr) = condition_field_init_value(&CONTEXT->values[CONTEXT->value_length - 1]);
	}
#line 2166 "yacc_sql.tab.c"
    break;

  case 91:
#line 561 "yacc_sql.y"
             {
		(yyval.ptr) = condition_field_init_attr(NULL, (yyvsp[0].string));
	}
#line 2174 "yacc_sql.tab.c"
    break;

  case 92:
#line 564 "yacc_sql.y"
                    {
		(yyval.ptr) = condition_field_init_attr((yyvsp[-2].string), (yyvsp[0].string));
	}
#line 2182 "yacc_sql.tab.c"
    break;

  case 93:
#line 569 "yacc_sql.y"
                                              {
		Condition condition;
		condition_init(&condition, (yyvsp[-2].ptr), (yyvsp[0].ptr), CONTEXT->comp);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
	}
#line 2192 "yacc_sql.tab.c"
    break;

  case 95:
#line 652 "yacc_sql.y"
                                         {
		RelAttr attr;
		relation_attr_init(&attr, NULL, (yyvsp[-1].string));
		selects_append_group_by_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 2202 "yacc_sql.tab.c"
    break;

  case 96:
#line 657 "yacc_sql.y"
                                                {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
		selects_append_group_by_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 2212 "yacc_sql.tab.c"
    break;

  case 98:
#line 666 "yacc_sql.y"
                                      {
		RelAttr attr;
		relation_attr_init(&attr, NULL, (yyvsp[-1].string));
		selects_append_group_by_attribute(&CONTEXT->ssql->sstr.selection, &attr);
    }
#line 2222 "yacc_sql.tab.c"
    break;

  case 99:
#line 671 "yacc_sql.y"
                                         {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
		selects_append_group_by_attribute(&CONTEXT->ssql->sstr.selection, &attr);
  	}
#line 2232 "yacc_sql.tab.c"
    break;

  case 100:
#line 679 "yacc_sql.y"
       { CONTEXT->comp = EQUAL_TO; }
#line 2238 "yacc_sql.tab.c"
    break;

  case 101:
#line 680 "yacc_sql.y"
         { CONTEXT->comp = LESS_THAN; }
#line 2244 "yacc_sql.tab.c"
    break;

  case 102:
#line 681 "yacc_sql.y"
         { CONTEXT->comp = GREAT_THAN; }
#line 2250 "yacc_sql.tab.c"
    break;

  case 103:
#line 682 "yacc_sql.y"
         { CONTEXT->comp = LESS_EQUAL; }
#line 2256 "yacc_sql.tab.c"
    break;

  case 104:
#line 683 "yacc_sql.y"
         { CONTEXT->comp = GREAT_EQUAL; }
#line 2262 "yacc_sql.tab.c"
    break;

  case 105:
#line 684 "yacc_sql.y"
         { CONTEXT->comp = NOT_EQUAL; }
#line 2268 "yacc_sql.tab.c"
    break;

  case 106:
#line 685 "yacc_sql.y"
         { CONTEXT->comp = IS_OP;}
#line 2274 "yacc_sql.tab.c"
    break;

  case 107:
#line 686 "yacc_sql.y"
             { CONTEXT->comp = IS_NOT_OP;}
#line 2280 "yacc_sql.tab.c"
    break;

  case 108:
#line 687 "yacc_sql.y"
         { CONTEXT->comp = COND_IN; }
#line 2286 "yacc_sql.tab.c"
    break;

  case 109:
#line 688 "yacc_sql.y"
             { CONTEXT->comp = NOT_IN; }
#line 2292 "yacc_sql.tab.c"
    break;

  case 110:
#line 693 "yacc_sql.y"
                {
		  	CONTEXT->ssql->flag = SCF_LOAD_DATA;
			load_data_init(&CONTEXT->ssql->sstr.load_data, (yyvsp[-1].string), (yyvsp[-4].string));
		}
#line 2301 "yacc_sql.tab.c"
    break;

  case 112:
#line 702 "yacc_sql.y"
                {
			Order order;
			order_info_init(&order, (yyvsp[-1].number), NULL,(yyvsp[-2].string));
			selects_append_order(&CONTEXT->ssql->sstr.selection, &order);
		}
#line 2311 "yacc_sql.tab.c"
    break;

  case 113:
#line 708 "yacc_sql.y"
                {
			Order order;
			order_info_init(&order, ASC, NULL, (yyvsp[-1].string));
			selects_append_order(&CONTEXT->ssql->sstr.selection, &order);
		}
#line 2321 "yacc_sql.tab.c"
    break;

  case 114:
#line 714 "yacc_sql.y"
                {
			Order order;
			order_info_init(&order, ASC, (yyvsp[-3].string), (yyvsp[-1].string));
			selects_append_order(&CONTEXT->ssql->sstr.selection, &order);
		}
#line 2331 "yacc_sql.tab.c"
    break;

  case 115:
#line 720 "yacc_sql.y"
                {
			Order order;
			order_info_init(&order, (yyvsp[-1].number), (yyvsp[-4].string), (yyvsp[-2].string));
			selects_append_order(&CONTEXT->ssql->sstr.selection, &order);
		}
#line 2341 "yacc_sql.tab.c"
    break;

  case 117:
#line 729 "yacc_sql.y"
                {
			Order order;
			printf("odered_type : %d\n", CONTEXT->order_type);
			order_info_init(&order, (yyvsp[-1].number), NULL,(yyvsp[-2].string));
			selects_append_order(&CONTEXT->ssql->sstr.selection, &order);
		}
#line 2352 "yacc_sql.tab.c"
    break;

  case 118:
#line 736 "yacc_sql.y"
                {
			Order order;
			order_info_init(&order, ASC, NULL, (yyvsp[-1].string));
			selects_append_order(&CONTEXT->ssql->sstr.selection, &order);
		}
#line 2362 "yacc_sql.tab.c"
    break;

  case 119:
#line 742 "yacc_sql.y"
                {
			Order order;
			order_info_init(&order, ASC, (yyvsp[-3].string), (yyvsp[-1].string));
			selects_append_order(&CONTEXT->ssql->sstr.selection, &order);
		}
#line 2372 "yacc_sql.tab.c"
    break;

  case 120:
#line 747 "yacc_sql.y"
                                                {
			Order order;
			order_info_init(&order, (yyvsp[-1].number), (yyvsp[-4].string),(yyvsp[-2].string));
			selects_append_order(&CONTEXT->ssql->sstr.selection, &order);
		}
#line 2382 "yacc_sql.tab.c"
    break;


#line 2386 "yacc_sql.tab.c"

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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

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
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (scanner, YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (scanner, yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
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
                      yytoken, &yylval, scanner);
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

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
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
                  yystos[yystate], yyvsp, scanner);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (scanner, YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, scanner);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[+*yyssp], yyvsp, scanner);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 754 "yacc_sql.y"

//_____________________________________________________________________
extern void scan_string(const char *str, yyscan_t scanner);

int sql_parse(const char *s, Query *sqls){
	ParserContext context;
	memset(&context, 0, sizeof(context));

	yyscan_t scanner;
	yylex_init_extra(&context, &scanner);
	context.ssql = sqls;
	scan_string(s, scanner);
	int result = yyparse(scanner);
	yylex_destroy(scanner);
	return result;
}
