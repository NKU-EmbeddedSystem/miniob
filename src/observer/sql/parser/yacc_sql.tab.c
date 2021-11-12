/* A Bison parser, made by GNU Bison 3.8.1.  */

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
#define YYBISON 30801

/* Bison version string.  */
#define YYBISON_VERSION "3.8.1"

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


#line 133 "yacc_sql.tab.c"

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

#include "yacc_sql.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_SEMICOLON = 3,                  /* SEMICOLON  */
  YYSYMBOL_CREATE = 4,                     /* CREATE  */
  YYSYMBOL_DROP = 5,                       /* DROP  */
  YYSYMBOL_NULL_T = 6,                     /* NULL_T  */
  YYSYMBOL_NULLABLE_T = 7,                 /* NULLABLE_T  */
  YYSYMBOL_TABLE = 8,                      /* TABLE  */
  YYSYMBOL_TABLES = 9,                     /* TABLES  */
  YYSYMBOL_INDEX = 10,                     /* INDEX  */
  YYSYMBOL_SELECT = 11,                    /* SELECT  */
  YYSYMBOL_MAX = 12,                       /* MAX  */
  YYSYMBOL_MIN = 13,                       /* MIN  */
  YYSYMBOL_COUNT = 14,                     /* COUNT  */
  YYSYMBOL_AVG = 15,                       /* AVG  */
  YYSYMBOL_DESC = 16,                      /* DESC  */
  YYSYMBOL_SHOW = 17,                      /* SHOW  */
  YYSYMBOL_SYNC = 18,                      /* SYNC  */
  YYSYMBOL_INSERT = 19,                    /* INSERT  */
  YYSYMBOL_DELETE = 20,                    /* DELETE  */
  YYSYMBOL_UPDATE = 21,                    /* UPDATE  */
  YYSYMBOL_LBRACE = 22,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 23,                    /* RBRACE  */
  YYSYMBOL_COMMA = 24,                     /* COMMA  */
  YYSYMBOL_TRX_BEGIN = 25,                 /* TRX_BEGIN  */
  YYSYMBOL_TRX_COMMIT = 26,                /* TRX_COMMIT  */
  YYSYMBOL_TRX_ROLLBACK = 27,              /* TRX_ROLLBACK  */
  YYSYMBOL_INT_T = 28,                     /* INT_T  */
  YYSYMBOL_STRING_T = 29,                  /* STRING_T  */
  YYSYMBOL_FLOAT_T = 30,                   /* FLOAT_T  */
  YYSYMBOL_TEXT_T = 31,                    /* TEXT_T  */
  YYSYMBOL_DATE_T = 32,                    /* DATE_T  */
  YYSYMBOL_HELP = 33,                      /* HELP  */
  YYSYMBOL_EXIT = 34,                      /* EXIT  */
  YYSYMBOL_DOT = 35,                       /* DOT  */
  YYSYMBOL_INTO = 36,                      /* INTO  */
  YYSYMBOL_VALUES = 37,                    /* VALUES  */
  YYSYMBOL_FROM = 38,                      /* FROM  */
  YYSYMBOL_WHERE = 39,                     /* WHERE  */
  YYSYMBOL_AND = 40,                       /* AND  */
  YYSYMBOL_SET = 41,                       /* SET  */
  YYSYMBOL_ON = 42,                        /* ON  */
  YYSYMBOL_IS = 43,                        /* IS  */
  YYSYMBOL_LOAD = 44,                      /* LOAD  */
  YYSYMBOL_DATA = 45,                      /* DATA  */
  YYSYMBOL_INFILE = 46,                    /* INFILE  */
  YYSYMBOL_UNIQUE = 47,                    /* UNIQUE  */
  YYSYMBOL_ASC = 48,                       /* ASC  */
  YYSYMBOL_ORDER = 49,                     /* ORDER  */
  YYSYMBOL_BY = 50,                        /* BY  */
  YYSYMBOL_EQ = 51,                        /* EQ  */
  YYSYMBOL_LT = 52,                        /* LT  */
  YYSYMBOL_GT = 53,                        /* GT  */
  YYSYMBOL_LE = 54,                        /* LE  */
  YYSYMBOL_GE = 55,                        /* GE  */
  YYSYMBOL_NE = 56,                        /* NE  */
  YYSYMBOL_NOT = 57,                       /* NOT  */
  YYSYMBOL_NUMBER = 58,                    /* NUMBER  */
  YYSYMBOL_FLOAT = 59,                     /* FLOAT  */
  YYSYMBOL_ID = 60,                        /* ID  */
  YYSYMBOL_PATH = 61,                      /* PATH  */
  YYSYMBOL_SSS = 62,                       /* SSS  */
  YYSYMBOL_STAR = 63,                      /* STAR  */
  YYSYMBOL_STRING_V = 64,                  /* STRING_V  */
  YYSYMBOL_YYACCEPT = 65,                  /* $accept  */
  YYSYMBOL_commands = 66,                  /* commands  */
  YYSYMBOL_command = 67,                   /* command  */
  YYSYMBOL_exit = 68,                      /* exit  */
  YYSYMBOL_help = 69,                      /* help  */
  YYSYMBOL_sync = 70,                      /* sync  */
  YYSYMBOL_begin = 71,                     /* begin  */
  YYSYMBOL_commit = 72,                    /* commit  */
  YYSYMBOL_rollback = 73,                  /* rollback  */
  YYSYMBOL_drop_table = 74,                /* drop_table  */
  YYSYMBOL_show_tables = 75,               /* show_tables  */
  YYSYMBOL_desc_table = 76,                /* desc_table  */
  YYSYMBOL_create_index = 77,              /* create_index  */
  YYSYMBOL_ID_list = 78,                   /* ID_list  */
  YYSYMBOL_drop_index = 79,                /* drop_index  */
  YYSYMBOL_create_table = 80,              /* create_table  */
  YYSYMBOL_attr_def_list = 81,             /* attr_def_list  */
  YYSYMBOL_attr_def = 82,                  /* attr_def  */
  YYSYMBOL_null_def = 83,                  /* null_def  */
  YYSYMBOL_number = 84,                    /* number  */
  YYSYMBOL_type = 85,                      /* type  */
  YYSYMBOL_agg_type = 86,                  /* agg_type  */
  YYSYMBOL_order_type = 87,                /* order_type  */
  YYSYMBOL_ID_get = 88,                    /* ID_get  */
  YYSYMBOL_insert_value_list = 89,         /* insert_value_list  */
  YYSYMBOL_insert = 90,                    /* insert  */
  YYSYMBOL_value_list = 91,                /* value_list  */
  YYSYMBOL_value = 92,                     /* value  */
  YYSYMBOL_delete = 93,                    /* delete  */
  YYSYMBOL_update = 94,                    /* update  */
  YYSYMBOL_select = 95,                    /* select  */
  YYSYMBOL_select_attr = 96,               /* select_attr  */
  YYSYMBOL_attr_list = 97,                 /* attr_list  */
  YYSYMBOL_agg_list = 98,                  /* agg_list  */
  YYSYMBOL_rel_list = 99,                  /* rel_list  */
  YYSYMBOL_where = 100,                    /* where  */
  YYSYMBOL_condition_list = 101,           /* condition_list  */
  YYSYMBOL_condition = 102,                /* condition  */
  YYSYMBOL_comOp = 103,                    /* comOp  */
  YYSYMBOL_load_data = 104,                /* load_data  */
  YYSYMBOL_order = 105,                    /* order  */
  YYSYMBOL_order_attrs = 106               /* order_attrs  */
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
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   246

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  65
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  42
/* YYNRULES -- Number of rules.  */
#define YYNRULES  110
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  245

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   319


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
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   156,   156,   158,   162,   163,   164,   165,   166,   167,
     168,   169,   170,   171,   172,   173,   174,   175,   176,   177,
     178,   182,   187,   192,   198,   204,   210,   216,   222,   228,
     235,   240,   248,   251,   258,   265,   274,   276,   280,   288,
     305,   306,   307,   312,   316,   317,   318,   319,   320,   324,
     325,   326,   327,   331,   332,   336,   343,   345,   351,   360,
     362,   367,   371,   375,   380,   387,   397,   407,   426,   432,
     438,   444,   450,   456,   462,   469,   471,   478,   487,   489,
     495,   501,   507,   515,   517,   522,   524,   529,   531,   537,
     558,   578,   598,   620,   641,   662,   684,   685,   686,   687,
     688,   689,   690,   691,   695,   702,   704,   709,   715,   717,
     722
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
  "\"end of file\"", "error", "\"invalid token\"", "SEMICOLON", "CREATE",
  "DROP", "NULL_T", "NULLABLE_T", "TABLE", "TABLES", "INDEX", "SELECT",
  "MAX", "MIN", "COUNT", "AVG", "DESC", "SHOW", "SYNC", "INSERT", "DELETE",
  "UPDATE", "LBRACE", "RBRACE", "COMMA", "TRX_BEGIN", "TRX_COMMIT",
  "TRX_ROLLBACK", "INT_T", "STRING_T", "FLOAT_T", "TEXT_T", "DATE_T",
  "HELP", "EXIT", "DOT", "INTO", "VALUES", "FROM", "WHERE", "AND", "SET",
  "ON", "IS", "LOAD", "DATA", "INFILE", "UNIQUE", "ASC", "ORDER", "BY",
  "EQ", "LT", "GT", "LE", "GE", "NE", "NOT", "NUMBER", "FLOAT", "ID",
  "PATH", "SSS", "STAR", "STRING_V", "$accept", "commands", "command",
  "exit", "help", "sync", "begin", "commit", "rollback", "drop_table",
  "show_tables", "desc_table", "create_index", "ID_list", "drop_index",
  "create_table", "attr_def_list", "attr_def", "null_def", "number",
  "type", "agg_type", "order_type", "ID_get", "insert_value_list",
  "insert", "value_list", "value", "delete", "update", "select",
  "select_attr", "attr_list", "agg_list", "rel_list", "where",
  "condition_list", "condition", "comOp", "load_data", "order",
  "order_attrs", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-213)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -213,   112,  -213,     8,    96,    20,   -51,    13,    27,    -5,
       1,   -17,    43,    67,    72,   102,   108,     5,  -213,  -213,
    -213,  -213,  -213,  -213,  -213,  -213,  -213,  -213,  -213,  -213,
    -213,  -213,  -213,  -213,  -213,  -213,    55,    58,   110,    61,
      62,  -213,  -213,  -213,  -213,     2,  -213,   103,    86,   123,
     131,  -213,    75,    76,   100,  -213,  -213,  -213,  -213,  -213,
      98,   120,   101,    87,   151,   152,   104,   105,  -213,    28,
     106,  -213,  -213,   125,   124,   107,   109,   113,   114,   126,
    -213,  -213,    12,   145,  -213,    -6,   147,   149,   153,   154,
      -2,   172,   127,   143,  -213,   156,   129,   159,   122,   128,
    -213,  -213,   160,   130,   160,   160,   132,   124,    19,  -213,
    -213,  -213,    47,  -213,    97,   146,  -213,    19,   175,   113,
     162,  -213,  -213,  -213,  -213,  -213,    -4,   122,   163,   167,
     145,    81,  -213,   168,  -213,  -213,   153,   144,   170,   135,
     139,  -213,  -213,  -213,  -213,  -213,  -213,     4,     9,    -2,
    -213,   124,   137,   156,   195,  -213,   193,   178,   179,   122,
     141,  -213,   181,   160,  -213,   155,   201,    19,   183,    97,
    -213,  -213,  -213,   173,  -213,   146,   204,   206,  -213,  -213,
    -213,   157,   207,  -213,   188,    29,  -213,   158,  -213,   170,
     189,    14,   161,  -213,  -213,  -213,   191,  -213,   209,    17,
     194,   196,     3,  -213,   198,   213,   187,  -213,  -213,  -213,
    -213,   160,   164,   160,   160,  -213,   165,  -213,   199,    19,
    -213,   166,  -213,   205,  -213,  -213,    -3,   169,  -213,   170,
    -213,   160,   199,    49,   208,  -213,  -213,   174,   199,   189,
      -3,  -213,  -213,   199,  -213
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
       0,    49,    50,    51,    52,    75,    68,     0,     0,     0,
       0,    23,     0,     0,     0,    24,    25,    26,    22,    21,
       0,     0,     0,     0,     0,     0,     0,     0,    69,     0,
       0,    29,    28,     0,    85,     0,     0,     0,     0,     0,
      27,    34,    75,    75,    43,     0,     0,     0,    83,     0,
       0,     0,     0,     0,    55,    36,     0,     0,     0,     0,
      76,    70,    78,     0,    78,    78,     0,    85,     0,    64,
      61,    62,     0,    63,     0,    87,    65,     0,     0,     0,
       0,    44,    45,    46,    48,    47,    40,     0,    32,     0,
      75,     0,    73,     0,    71,    72,    83,   105,    59,     0,
     102,    96,    97,    98,    99,   100,   101,     0,     0,     0,
      86,    85,     0,    36,     0,    41,     0,    39,     0,     0,
       0,    77,     0,    78,    84,     0,     0,     0,     0,     0,
     103,    91,    89,    92,    90,    87,     0,     0,    37,    35,
      42,     0,     0,    33,     0,     0,    74,     0,    67,    59,
      56,     0,     0,    88,    66,   104,     0,    30,     0,     0,
       0,     0,     0,    60,     0,     0,     0,    93,    94,    38,
      31,    78,     0,    78,    78,    54,     0,    53,   108,     0,
      58,     0,    81,     0,    79,    80,     0,     0,   106,    59,
      95,    78,   108,     0,     0,    82,   107,     0,   108,    56,
       0,   109,    57,   108,   110
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -213,  -213,  -213,  -213,  -213,  -213,  -213,  -213,  -213,  -213,
    -213,  -213,  -213,  -115,  -213,  -213,    74,   111,  -213,  -158,
    -213,   115,  -212,  -213,    -7,  -213,  -181,  -106,  -213,  -213,
    -213,  -213,   -76,  -104,    99,  -102,    63,    84,   -90,  -213,
    -213,  -124
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     1,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,   129,    29,    30,   120,    95,   157,    87,
     126,    47,   218,    96,   205,    31,   168,   114,    32,    33,
      34,    48,    68,   132,   107,    91,   150,   115,   147,    35,
     166,   228
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
     134,   135,   138,   155,   109,   137,   100,   101,   203,    49,
     109,   151,   158,   215,   232,   109,    36,   102,    37,   215,
     109,   238,    50,   196,   148,   109,    66,   201,   243,   103,
      51,    52,    41,    42,    43,    44,    66,    67,   216,    53,
     211,   172,   174,    54,   183,   217,    55,    99,   234,   176,
      60,   217,   212,   156,   161,    38,   110,   111,   112,   186,
     113,   189,   110,   111,   171,   215,   113,   110,   111,   173,
      56,   113,   110,   111,   206,    57,   113,   110,   111,   191,
      45,   113,   139,    46,   237,   207,    84,    84,    85,   199,
     140,    86,   200,    41,    42,    43,    44,   217,   141,   142,
     143,   144,   145,   146,    39,    58,    40,   222,   236,   224,
     225,    59,     2,   229,   241,    61,     3,     4,    62,   244,
      63,    64,    65,     5,    70,    69,    71,   235,     6,     7,
       8,     9,    10,    11,    72,    73,    74,    12,    13,    14,
     140,    75,    77,    78,    76,    15,    16,    79,   141,   142,
     143,   144,   145,   146,    80,    81,    17,   121,   122,   123,
     124,   125,    89,    90,    82,    83,    88,    92,    98,    66,
     104,    93,   105,    94,    97,   116,   108,   106,   117,   118,
     119,   127,   128,   152,   131,   154,   149,   159,   130,   160,
     133,   163,   136,   165,   167,   169,   170,   177,   179,   180,
     181,   184,   182,   185,   188,   187,   190,   194,   192,   195,
     197,   198,   210,   204,   209,    84,   220,   213,   202,   214,
     219,   208,   221,   227,   223,   226,   230,   178,   231,   233,
     153,   239,   242,   175,   240,   164,     0,     0,   193,     0,
       0,     0,     0,     0,     0,     0,   162
};

static const yytype_int16 yycheck[] =
{
     104,   105,   108,     7,     6,   107,    82,    83,   189,    60,
       6,   117,   127,    16,   226,     6,     8,    23,    10,    16,
       6,   233,     9,   181,   114,     6,    24,   185,   240,    35,
       3,    36,    12,    13,    14,    15,    24,    35,    35,    38,
      23,   147,   148,    60,   159,    48,     3,    35,   229,   151,
      45,    48,    35,    57,   130,    47,    58,    59,    60,   163,
      62,   167,    58,    59,    60,    16,    62,    58,    59,    60,
       3,    62,    58,    59,    60,     3,    62,    58,    59,   169,
      60,    62,    35,    63,    35,   191,    58,    58,    60,    60,
      43,    63,    63,    12,    13,    14,    15,    48,    51,    52,
      53,    54,    55,    56,     8,     3,    10,   211,   232,   213,
     214,     3,     0,   219,   238,    60,     4,     5,    60,   243,
      10,    60,    60,    11,    38,    22,     3,   231,    16,    17,
      18,    19,    20,    21,     3,    60,    60,    25,    26,    27,
      43,    41,    22,    42,    46,    33,    34,    60,    51,    52,
      53,    54,    55,    56,     3,     3,    44,    28,    29,    30,
      31,    32,    37,    39,    60,    60,    60,    60,    42,    24,
      23,    62,    23,    60,    60,     3,    22,    24,    51,    36,
      24,    22,    60,     8,    24,    23,    40,    24,    60,    22,
      60,    23,    60,    49,    24,    60,    57,    60,     3,     6,
      22,    60,    23,    22,     3,    50,    23,     3,    35,     3,
       3,    23,     3,    24,    23,    58,     3,    23,    60,    23,
      22,    60,    35,    24,    60,    60,    60,   153,    23,    60,
     119,    23,   239,   149,    60,   136,    -1,    -1,   175,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   131
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    66,     0,     4,     5,    11,    16,    17,    18,    19,
      20,    21,    25,    26,    27,    33,    34,    44,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    79,
      80,    90,    93,    94,    95,   104,     8,    10,    47,     8,
      10,    12,    13,    14,    15,    60,    63,    86,    96,    60,
       9,     3,    36,    38,    60,     3,     3,     3,     3,     3,
      45,    60,    60,    10,    60,    60,    24,    35,    97,    22,
      38,     3,     3,    60,    60,    41,    46,    22,    42,    60,
       3,     3,    60,    60,    58,    60,    63,    84,    60,    37,
      39,   100,    60,    62,    60,    82,    88,    60,    42,    35,
      97,    97,    23,    35,    23,    23,    24,    99,    22,     6,
      58,    59,    60,    62,    92,   102,     3,    51,    36,    24,
      81,    28,    29,    30,    31,    32,    85,    22,    60,    78,
      60,    24,    98,    60,    98,    98,    60,   100,    92,    35,
      43,    51,    52,    53,    54,    55,    56,   103,   103,    40,
     101,    92,     8,    82,    23,     7,    57,    83,    78,    24,
      22,    97,    86,    23,    99,    49,   105,    24,    91,    60,
      57,    60,    92,    60,    92,   102,   100,    60,    81,     3,
       6,    22,    23,    78,    60,    22,    98,    50,     3,    92,
      23,   103,    35,   101,     3,     3,    84,     3,    23,    60,
      63,    84,    60,    91,    24,    89,    60,    92,    60,    23,
       3,    23,    35,    23,    23,    16,    35,    48,    87,    22,
       3,    35,    98,    60,    98,    98,    60,    24,   106,    92,
      60,    23,    87,    60,    91,    98,   106,    35,    87,    23,
      60,   106,    89,    87,   106
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    65,    66,    66,    67,    67,    67,    67,    67,    67,
      67,    67,    67,    67,    67,    67,    67,    67,    67,    67,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    77,    78,    78,    79,    80,    81,    81,    82,    82,
      83,    83,    83,    84,    85,    85,    85,    85,    85,    86,
      86,    86,    86,    87,    87,    88,    89,    89,    90,    91,
      91,    92,    92,    92,    92,    93,    94,    95,    96,    96,
      96,    96,    96,    96,    96,    97,    97,    97,    98,    98,
      98,    98,    98,    99,    99,   100,   100,   101,   101,   102,
     102,   102,   102,   102,   102,   102,   103,   103,   103,   103,
     103,   103,   103,   103,   104,   105,   105,   105,   106,   106,
     106
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     2,     2,     2,     2,     2,     4,     3,     3,
       9,    10,     1,     3,     4,     8,     0,     3,     6,     3,
       0,     1,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     6,    10,     0,
       3,     1,     1,     1,     1,     5,     8,     8,     1,     2,
       4,     5,     5,     5,     7,     0,     3,     5,     0,     6,
       6,     6,     8,     0,     3,     0,     3,     0,     3,     3,
       3,     3,     3,     5,     5,     7,     1,     1,     1,     1,
       1,     1,     1,     2,     8,     0,     5,     7,     0,     4,
       6
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
        yyerror (scanner, YY_("syntax error: cannot back up")); \
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
                  Kind, Value, scanner); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, void *scanner)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (scanner);
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
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, void *scanner)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep, scanner);
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
                 int yyrule, void *scanner)
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
                       &yyvsp[(yyi + 1) - (yynrhs)], scanner);
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
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, void *scanner)
{
  YY_USE (yyvaluep);
  YY_USE (scanner);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}






/*----------.
| yyparse.  |
`----------*/

int
yyparse (void *scanner)
{
/* Lookahead token kind.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

    /* Number of syntax errors so far.  */
    int yynerrs = 0;

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
      yychar = yylex (&yylval, scanner);
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
  case 21: /* exit: EXIT SEMICOLON  */
#line 182 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_EXIT;//"exit";
    }
#line 1404 "yacc_sql.tab.c"
    break;

  case 22: /* help: HELP SEMICOLON  */
#line 187 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_HELP;//"help";
    }
#line 1412 "yacc_sql.tab.c"
    break;

  case 23: /* sync: SYNC SEMICOLON  */
#line 192 "yacc_sql.y"
                   {
      CONTEXT->ssql->flag = SCF_SYNC;
    }
#line 1420 "yacc_sql.tab.c"
    break;

  case 24: /* begin: TRX_BEGIN SEMICOLON  */
#line 198 "yacc_sql.y"
                        {
      CONTEXT->ssql->flag = SCF_BEGIN;
    }
#line 1428 "yacc_sql.tab.c"
    break;

  case 25: /* commit: TRX_COMMIT SEMICOLON  */
#line 204 "yacc_sql.y"
                         {
      CONTEXT->ssql->flag = SCF_COMMIT;
    }
#line 1436 "yacc_sql.tab.c"
    break;

  case 26: /* rollback: TRX_ROLLBACK SEMICOLON  */
#line 210 "yacc_sql.y"
                           {
      CONTEXT->ssql->flag = SCF_ROLLBACK;
    }
#line 1444 "yacc_sql.tab.c"
    break;

  case 27: /* drop_table: DROP TABLE ID SEMICOLON  */
#line 216 "yacc_sql.y"
                            {
        CONTEXT->ssql->flag = SCF_DROP_TABLE;//"drop_table";
        drop_table_init(&CONTEXT->ssql->sstr.drop_table, (yyvsp[-1].string));
    }
#line 1453 "yacc_sql.tab.c"
    break;

  case 28: /* show_tables: SHOW TABLES SEMICOLON  */
#line 222 "yacc_sql.y"
                          {
      CONTEXT->ssql->flag = SCF_SHOW_TABLES;
    }
#line 1461 "yacc_sql.tab.c"
    break;

  case 29: /* desc_table: DESC ID SEMICOLON  */
#line 228 "yacc_sql.y"
                      {
      CONTEXT->ssql->flag = SCF_DESC_TABLE;
      desc_table_init(&CONTEXT->ssql->sstr.desc_table, (yyvsp[-1].string));
    }
#line 1470 "yacc_sql.tab.c"
    break;

  case 30: /* create_index: CREATE INDEX ID ON ID LBRACE ID_list RBRACE SEMICOLON  */
#line 236 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
			create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-6].string), (yyvsp[-4].string), (yyvsp[-2].string));
		}
#line 1479 "yacc_sql.tab.c"
    break;

  case 31: /* create_index: CREATE UNIQUE INDEX ID ON ID_list LBRACE ID RBRACE SEMICOLON  */
#line 241 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_CREATE_UNIQUE_INDEX;// "create_unique_index";
			create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-6].string), (yyvsp[-4].string), (yyvsp[-2].string));
    		}
#line 1488 "yacc_sql.tab.c"
    break;

  case 32: /* ID_list: ID  */
#line 248 "yacc_sql.y"
                {
    			(yyval.string) = (yyvsp[0].string);
    		}
#line 1496 "yacc_sql.tab.c"
    break;

  case 33: /* ID_list: ID COMMA ID_list  */
#line 252 "yacc_sql.y"
                {
			(yyval.string) = (yyvsp[-2].string);
    		}
#line 1504 "yacc_sql.tab.c"
    break;

  case 34: /* drop_index: DROP INDEX ID SEMICOLON  */
#line 259 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_DROP_INDEX;//"drop_index";
			drop_index_init(&CONTEXT->ssql->sstr.drop_index, (yyvsp[-1].string));
		}
#line 1513 "yacc_sql.tab.c"
    break;

  case 35: /* create_table: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE SEMICOLON  */
#line 266 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_CREATE_TABLE;//"create_table";
			// CONTEXT->ssql->sstr.create_table.attribute_count = CONTEXT->value_length;
			create_table_init_name(&CONTEXT->ssql->sstr.create_table, (yyvsp[-5].string));
			//临时变量清零	
			CONTEXT->value_length = 0;
		}
#line 1525 "yacc_sql.tab.c"
    break;

  case 37: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 276 "yacc_sql.y"
                                   {    }
#line 1531 "yacc_sql.tab.c"
    break;

  case 38: /* attr_def: ID_get type null_def LBRACE number RBRACE  */
#line 281 "yacc_sql.y"
                {
			AttrInfo attribute;
			// 我们让nullable的列增加4个字节
			attr_info_init(&attribute, CONTEXT->id, (yyvsp[-4].number), (yyvsp[-1].number) + (yyvsp[-3].number) * 4, (yyvsp[-3].number));
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			CONTEXT->value_length++;
		}
#line 1543 "yacc_sql.tab.c"
    break;

  case 39: /* attr_def: ID_get type null_def  */
#line 289 "yacc_sql.y"
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
#line 1560 "yacc_sql.tab.c"
    break;

  case 40: /* null_def: %empty  */
#line 305 "yacc_sql.y"
          { (yyval.number) = 0; }
#line 1566 "yacc_sql.tab.c"
    break;

  case 41: /* null_def: NULLABLE_T  */
#line 306 "yacc_sql.y"
                     { (yyval.number) = 1; }
#line 1572 "yacc_sql.tab.c"
    break;

  case 42: /* null_def: NOT NULL_T  */
#line 307 "yacc_sql.y"
                     { (yyval.number) = 0; }
#line 1578 "yacc_sql.tab.c"
    break;

  case 43: /* number: NUMBER  */
#line 312 "yacc_sql.y"
                       {(yyval.number) = (yyvsp[0].number);}
#line 1584 "yacc_sql.tab.c"
    break;

  case 44: /* type: INT_T  */
#line 316 "yacc_sql.y"
              { (yyval.number)=INTS; }
#line 1590 "yacc_sql.tab.c"
    break;

  case 45: /* type: STRING_T  */
#line 317 "yacc_sql.y"
                  { (yyval.number)=CHARS; }
#line 1596 "yacc_sql.tab.c"
    break;

  case 46: /* type: FLOAT_T  */
#line 318 "yacc_sql.y"
                 { (yyval.number)=FLOATS; }
#line 1602 "yacc_sql.tab.c"
    break;

  case 47: /* type: DATE_T  */
#line 319 "yacc_sql.y"
                { (yyval.number)=DATE; }
#line 1608 "yacc_sql.tab.c"
    break;

  case 48: /* type: TEXT_T  */
#line 320 "yacc_sql.y"
                { (yyval.number) = TEXTS; }
#line 1614 "yacc_sql.tab.c"
    break;

  case 49: /* agg_type: MAX  */
#line 324 "yacc_sql.y"
            { (yyval.number) = AGG_MAX; }
#line 1620 "yacc_sql.tab.c"
    break;

  case 50: /* agg_type: MIN  */
#line 325 "yacc_sql.y"
              { (yyval.number) = AGG_MIN; }
#line 1626 "yacc_sql.tab.c"
    break;

  case 51: /* agg_type: COUNT  */
#line 326 "yacc_sql.y"
                { (yyval.number) = AGG_COUNT; }
#line 1632 "yacc_sql.tab.c"
    break;

  case 52: /* agg_type: AVG  */
#line 327 "yacc_sql.y"
              { (yyval.number) = AGG_AVG; }
#line 1638 "yacc_sql.tab.c"
    break;

  case 53: /* order_type: ASC  */
#line 331 "yacc_sql.y"
            { (yyval.number) = ORDER_ASC; }
#line 1644 "yacc_sql.tab.c"
    break;

  case 54: /* order_type: DESC  */
#line 332 "yacc_sql.y"
               { (yyval.number) =ORDER_DESC; }
#line 1650 "yacc_sql.tab.c"
    break;

  case 55: /* ID_get: ID  */
#line 337 "yacc_sql.y"
        {
		char *temp=(yyvsp[0].string); 
		snprintf(CONTEXT->id, sizeof(CONTEXT->id), "%s", temp);
	}
#line 1659 "yacc_sql.tab.c"
    break;

  case 57: /* insert_value_list: COMMA LBRACE value value_list RBRACE insert_value_list  */
#line 346 "yacc_sql.y"
                {

    		}
#line 1667 "yacc_sql.tab.c"
    break;

  case 58: /* insert: INSERT INTO ID VALUES LBRACE value value_list RBRACE insert_value_list SEMICOLON  */
#line 352 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_INSERT;//"insert";
			inserts_init(&CONTEXT->ssql->sstr.insertion, (yyvsp[-7].string), CONTEXT->values, CONTEXT->value_length);

      			//临时变量清零
      			CONTEXT->value_length=0;
    		}
#line 1679 "yacc_sql.tab.c"
    break;

  case 60: /* value_list: COMMA value value_list  */
#line 362 "yacc_sql.y"
                              { 
  		// CONTEXT->values[CONTEXT->value_length++] = *$2;
	  }
#line 1687 "yacc_sql.tab.c"
    break;

  case 61: /* value: NUMBER  */
#line 368 "yacc_sql.y"
                {
  			value_init_integer(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].number));
		}
#line 1695 "yacc_sql.tab.c"
    break;

  case 62: /* value: FLOAT  */
#line 372 "yacc_sql.y"
                {
  			value_init_float(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].floats));
		}
#line 1703 "yacc_sql.tab.c"
    break;

  case 63: /* value: SSS  */
#line 376 "yacc_sql.y"
                {
			(yyvsp[0].string) = substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
  			value_init_string(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].string));
		}
#line 1712 "yacc_sql.tab.c"
    break;

  case 64: /* value: NULL_T  */
#line 381 "yacc_sql.y"
                {
    			value_init_null(&CONTEXT->values[CONTEXT->value_length++]);
    		}
#line 1720 "yacc_sql.tab.c"
    break;

  case 65: /* delete: DELETE FROM ID where SEMICOLON  */
#line 388 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_DELETE;//"delete";
			deletes_init_relation(&CONTEXT->ssql->sstr.deletion, (yyvsp[-2].string));
			deletes_set_conditions(&CONTEXT->ssql->sstr.deletion, 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;	
    }
#line 1732 "yacc_sql.tab.c"
    break;

  case 66: /* update: UPDATE ID SET ID EQ value where SEMICOLON  */
#line 398 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_UPDATE;//"update";
			Value *value = &CONTEXT->values[0];
			updates_init(&CONTEXT->ssql->sstr.update, (yyvsp[-6].string), (yyvsp[-4].string), value, 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;
		}
#line 1744 "yacc_sql.tab.c"
    break;

  case 67: /* select: SELECT select_attr FROM ID rel_list where order SEMICOLON  */
#line 408 "yacc_sql.y"
                {
			// CONTEXT->ssql->sstr.selection.relations[CONTEXT->from_length++]=$4;
			selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-4].string));

			selects_append_conditions(&CONTEXT->ssql->sstr.selection, CONTEXT->conditions, CONTEXT->condition_length);

			CONTEXT->ssql->flag=SCF_SELECT;//"select";
			// CONTEXT->ssql->sstr.selection.attr_num = CONTEXT->select_length;

			//临时变量清零
			CONTEXT->condition_length=0;
			CONTEXT->from_length=0;
			CONTEXT->select_length=0;
			CONTEXT->value_length = 0;
	}
#line 1764 "yacc_sql.tab.c"
    break;

  case 68: /* select_attr: STAR  */
#line 427 "yacc_sql.y"
                {
			RelAttr attr;
			relation_attr_init(&attr, NULL, "*");
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 1774 "yacc_sql.tab.c"
    break;

  case 69: /* select_attr: ID attr_list  */
#line 433 "yacc_sql.y"
                {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 1784 "yacc_sql.tab.c"
    break;

  case 70: /* select_attr: ID DOT ID attr_list  */
#line 439 "yacc_sql.y"
                {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 1794 "yacc_sql.tab.c"
    break;

  case 71: /* select_attr: agg_type LBRACE STAR RBRACE agg_list  */
#line 445 "yacc_sql.y"
                {
			AggDesc agg_desc;
			agg_desc_init_string(&agg_desc, (yyvsp[-4].number), AGG_STAR, NULL, "*");
			selects_append_agg(&CONTEXT->ssql->sstr.selection, &agg_desc);
		}
#line 1804 "yacc_sql.tab.c"
    break;

  case 72: /* select_attr: agg_type LBRACE number RBRACE agg_list  */
#line 451 "yacc_sql.y"
                {
			AggDesc agg_desc;
			agg_desc_init_number(&agg_desc, (yyvsp[-4].number), AGG_NUMBER, (yyvsp[-2].number));
			selects_append_agg(&CONTEXT->ssql->sstr.selection, &agg_desc);
		}
#line 1814 "yacc_sql.tab.c"
    break;

  case 73: /* select_attr: agg_type LBRACE ID RBRACE agg_list  */
#line 457 "yacc_sql.y"
                {
			AggDesc agg_desc;
			agg_desc_init_string(&agg_desc, (yyvsp[-4].number), AGG_FIELD, NULL, (yyvsp[-2].string));
			selects_append_agg(&CONTEXT->ssql->sstr.selection, &agg_desc);
		}
#line 1824 "yacc_sql.tab.c"
    break;

  case 74: /* select_attr: agg_type LBRACE ID DOT ID RBRACE agg_list  */
#line 463 "yacc_sql.y"
                {
			AggDesc agg_desc;
			agg_desc_init_string(&agg_desc, (yyvsp[-6].number), AGG_FIELD, (yyvsp[-4].string), (yyvsp[-2].string));
			selects_append_agg(&CONTEXT->ssql->sstr.selection, &agg_desc);
		}
#line 1834 "yacc_sql.tab.c"
    break;

  case 76: /* attr_list: COMMA ID attr_list  */
#line 471 "yacc_sql.y"
                         {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
     	  // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length].relation_name = NULL;
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length++].attribute_name=$2;
      }
#line 1846 "yacc_sql.tab.c"
    break;

  case 77: /* attr_list: COMMA ID DOT ID attr_list  */
#line 478 "yacc_sql.y"
                                {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length].attribute_name=$4;
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length++].relation_name=$2;
  	  }
#line 1858 "yacc_sql.tab.c"
    break;

  case 79: /* agg_list: COMMA agg_type LBRACE STAR RBRACE agg_list  */
#line 490 "yacc_sql.y"
                {
			AggDesc agg_desc;
			agg_desc_init_string(&agg_desc, (yyvsp[-4].number), AGG_STAR, NULL, "*");
			selects_append_agg(&CONTEXT->ssql->sstr.selection, &agg_desc);
		}
#line 1868 "yacc_sql.tab.c"
    break;

  case 80: /* agg_list: COMMA agg_type LBRACE number RBRACE agg_list  */
#line 496 "yacc_sql.y"
                {
			AggDesc agg_desc;
			agg_desc_init_number(&agg_desc, (yyvsp[-4].number), AGG_NUMBER, (yyvsp[-2].number));
			selects_append_agg(&CONTEXT->ssql->sstr.selection, &agg_desc);
		}
#line 1878 "yacc_sql.tab.c"
    break;

  case 81: /* agg_list: COMMA agg_type LBRACE ID RBRACE agg_list  */
#line 502 "yacc_sql.y"
                {
			AggDesc agg_desc;
			agg_desc_init_string(&agg_desc, (yyvsp[-4].number), AGG_FIELD, NULL, (yyvsp[-2].string));
			selects_append_agg(&CONTEXT->ssql->sstr.selection, &agg_desc);
		}
#line 1888 "yacc_sql.tab.c"
    break;

  case 82: /* agg_list: COMMA agg_type LBRACE ID DOT ID RBRACE agg_list  */
#line 508 "yacc_sql.y"
                {
			AggDesc agg_desc;
			agg_desc_init_string(&agg_desc, (yyvsp[-6].number), AGG_FIELD, (yyvsp[-4].string), (yyvsp[-2].string));
			selects_append_agg(&CONTEXT->ssql->sstr.selection, &agg_desc);
		}
#line 1898 "yacc_sql.tab.c"
    break;

  case 84: /* rel_list: COMMA ID rel_list  */
#line 518 "yacc_sql.y"
                {
			selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-1].string));
		}
#line 1906 "yacc_sql.tab.c"
    break;

  case 86: /* where: WHERE condition condition_list  */
#line 525 "yacc_sql.y"
                {
			// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
		}
#line 1914 "yacc_sql.tab.c"
    break;

  case 88: /* condition_list: AND condition condition_list  */
#line 532 "yacc_sql.y"
                {
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
		}
#line 1922 "yacc_sql.tab.c"
    break;

  case 89: /* condition: ID comOp value  */
#line 538 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));

			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 0, NULL, right_value);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			// $$ = ( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 1;
			// $$->left_attr.relation_name = NULL;
			// $$->left_attr.attribute_name= $1;
			// $$->comp = CONTEXT->comp;
			// $$->right_is_attr = 0;
			// $$->right_attr.relation_name = NULL;
			// $$->right_attr.attribute_name = NULL;
			// $$->right_value = *$3;

		}
#line 1947 "yacc_sql.tab.c"
    break;

  case 90: /* condition: value comOp value  */
#line 559 "yacc_sql.y"
                {
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 2];
			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 0, NULL, left_value, 0, NULL, right_value);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			// $$ = ( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 0;
			// $$->left_attr.relation_name=NULL;
			// $$->left_attr.attribute_name=NULL;
			// $$->left_value = *$1;
			// $$->comp = CONTEXT->comp;
			// $$->right_is_attr = 0;
			// $$->right_attr.relation_name = NULL;
			// $$->right_attr.attribute_name = NULL;
			// $$->right_value = *$3;

		}
#line 1971 "yacc_sql.tab.c"
    break;

  case 91: /* condition: ID comOp ID  */
#line 579 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));
			RelAttr right_attr;
			relation_attr_init(&right_attr, NULL, (yyvsp[0].string));

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 1, &right_attr, NULL);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 1;
			// $$->left_attr.relation_name=NULL;
			// $$->left_attr.attribute_name=$1;
			// $$->comp = CONTEXT->comp;
			// $$->right_is_attr = 1;
			// $$->right_attr.relation_name=NULL;
			// $$->right_attr.attribute_name=$3;

		}
#line 1995 "yacc_sql.tab.c"
    break;

  case 92: /* condition: value comOp ID  */
#line 599 "yacc_sql.y"
                {
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];
			RelAttr right_attr;
			relation_attr_init(&right_attr, NULL, (yyvsp[0].string));

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 0, NULL, left_value, 1, &right_attr, NULL);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;

			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 0;
			// $$->left_attr.relation_name=NULL;
			// $$->left_attr.attribute_name=NULL;
			// $$->left_value = *$1;
			// $$->comp=CONTEXT->comp;
			
			// $$->right_is_attr = 1;
			// $$->right_attr.relation_name=NULL;
			// $$->right_attr.attribute_name=$3;
		
		}
#line 2021 "yacc_sql.tab.c"
    break;

  case 93: /* condition: ID DOT ID comOp value  */
#line 621 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, (yyvsp[-4].string), (yyvsp[-2].string));
			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 0, NULL, right_value);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;

			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 1;
			// $$->left_attr.relation_name=$1;
			// $$->left_attr.attribute_name=$3;
			// $$->comp=CONTEXT->comp;
			// $$->right_is_attr = 0;   //属性值
			// $$->right_attr.relation_name=NULL;
			// $$->right_attr.attribute_name=NULL;
			// $$->right_value =*$5;			
							
    }
#line 2046 "yacc_sql.tab.c"
    break;

  case 94: /* condition: value comOp ID DOT ID  */
#line 642 "yacc_sql.y"
                {
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];

			RelAttr right_attr;
			relation_attr_init(&right_attr, (yyvsp[-2].string), (yyvsp[0].string));

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 0, NULL, left_value, 1, &right_attr, NULL);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 0;//属性值
			// $$->left_attr.relation_name=NULL;
			// $$->left_attr.attribute_name=NULL;
			// $$->left_value = *$1;
			// $$->comp =CONTEXT->comp;
			// $$->right_is_attr = 1;//属性
			// $$->right_attr.relation_name = $3;
			// $$->right_attr.attribute_name = $5;
									
    }
#line 2071 "yacc_sql.tab.c"
    break;

  case 95: /* condition: ID DOT ID comOp ID DOT ID  */
#line 663 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, (yyvsp[-6].string), (yyvsp[-4].string));
			RelAttr right_attr;
			relation_attr_init(&right_attr, (yyvsp[-2].string), (yyvsp[0].string));

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 1, &right_attr, NULL);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 1;		//属性
			// $$->left_attr.relation_name=$1;
			// $$->left_attr.attribute_name=$3;
			// $$->comp =CONTEXT->comp;
			// $$->right_is_attr = 1;		//属性
			// $$->right_attr.relation_name=$5;
			// $$->right_attr.attribute_name=$7;
    }
#line 2094 "yacc_sql.tab.c"
    break;

  case 96: /* comOp: EQ  */
#line 684 "yacc_sql.y"
       { CONTEXT->comp = EQUAL_TO; }
#line 2100 "yacc_sql.tab.c"
    break;

  case 97: /* comOp: LT  */
#line 685 "yacc_sql.y"
         { CONTEXT->comp = LESS_THAN; }
#line 2106 "yacc_sql.tab.c"
    break;

  case 98: /* comOp: GT  */
#line 686 "yacc_sql.y"
         { CONTEXT->comp = GREAT_THAN; }
#line 2112 "yacc_sql.tab.c"
    break;

  case 99: /* comOp: LE  */
#line 687 "yacc_sql.y"
         { CONTEXT->comp = LESS_EQUAL; }
#line 2118 "yacc_sql.tab.c"
    break;

  case 100: /* comOp: GE  */
#line 688 "yacc_sql.y"
         { CONTEXT->comp = GREAT_EQUAL; }
#line 2124 "yacc_sql.tab.c"
    break;

  case 101: /* comOp: NE  */
#line 689 "yacc_sql.y"
         { CONTEXT->comp = NOT_EQUAL; }
#line 2130 "yacc_sql.tab.c"
    break;

  case 102: /* comOp: IS  */
#line 690 "yacc_sql.y"
         { CONTEXT->comp = IS_OP;}
#line 2136 "yacc_sql.tab.c"
    break;

  case 103: /* comOp: IS NOT  */
#line 691 "yacc_sql.y"
             { CONTEXT->comp = IS_NOT_OP;}
#line 2142 "yacc_sql.tab.c"
    break;

  case 104: /* load_data: LOAD DATA INFILE SSS INTO TABLE ID SEMICOLON  */
#line 696 "yacc_sql.y"
                {
		  	CONTEXT->ssql->flag = SCF_LOAD_DATA;
			load_data_init(&CONTEXT->ssql->sstr.load_data, (yyvsp[-1].string), (yyvsp[-4].string));
		}
#line 2151 "yacc_sql.tab.c"
    break;

  case 106: /* order: ORDER BY ID order_type order_attrs  */
#line 704 "yacc_sql.y"
                                             {
			Order order;
			order_info_init(&order,CONTEXT->order_type,NULL,(yyvsp[-2].string));
			selects_append_order(&CONTEXT->ssql->sstr.selection, &order);
		}
#line 2161 "yacc_sql.tab.c"
    break;

  case 107: /* order: ORDER BY ID DOT ID order_type order_attrs  */
#line 709 "yacc_sql.y"
                                                    {
			Order order;
			order_info_init(&order,CONTEXT->order_type,(yyvsp[-4].string),(yyvsp[-2].string));
			selects_append_order(&CONTEXT->ssql->sstr.selection, &order);
		}
#line 2171 "yacc_sql.tab.c"
    break;

  case 109: /* order_attrs: COMMA ID order_type order_attrs  */
#line 717 "yacc_sql.y"
                                         {
			Order order;
			order_info_init(&order,CONTEXT->order_type,NULL,(yyvsp[-2].string));
			selects_append_order(&CONTEXT->ssql->sstr.selection, &order);
		}
#line 2181 "yacc_sql.tab.c"
    break;

  case 110: /* order_attrs: COMMA ID DOT ID order_type order_attrs  */
#line 722 "yacc_sql.y"
                                                {
			Order order;
			order_info_init(&order,CONTEXT->order_type,(yyvsp[-4].string),(yyvsp[-2].string));
			selects_append_order(&CONTEXT->ssql->sstr.selection, &order);
		}
#line 2191 "yacc_sql.tab.c"
    break;


#line 2195 "yacc_sql.tab.c"

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
      yyerror (scanner, YY_("syntax error"));
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, scanner);
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
  yyerror (scanner, YY_("memory exhausted"));
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
                  yytoken, &yylval, scanner);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, scanner);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 729 "yacc_sql.y"

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
