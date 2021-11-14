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
  YYSYMBOL_GROUP = 41,                     /* GROUP  */
  YYSYMBOL_SET = 42,                       /* SET  */
  YYSYMBOL_INNER = 43,                     /* INNER  */
  YYSYMBOL_JOIN = 44,                      /* JOIN  */
  YYSYMBOL_ON = 45,                        /* ON  */
  YYSYMBOL_IS = 46,                        /* IS  */
  YYSYMBOL_LOAD = 47,                      /* LOAD  */
  YYSYMBOL_DATA = 48,                      /* DATA  */
  YYSYMBOL_INFILE = 49,                    /* INFILE  */
  YYSYMBOL_UNIQUE = 50,                    /* UNIQUE  */
  YYSYMBOL_ASC = 51,                       /* ASC  */
  YYSYMBOL_ORDER = 52,                     /* ORDER  */
  YYSYMBOL_BY = 53,                        /* BY  */
  YYSYMBOL_EQ = 54,                        /* EQ  */
  YYSYMBOL_LT = 55,                        /* LT  */
  YYSYMBOL_GT = 56,                        /* GT  */
  YYSYMBOL_LE = 57,                        /* LE  */
  YYSYMBOL_GE = 58,                        /* GE  */
  YYSYMBOL_NE = 59,                        /* NE  */
  YYSYMBOL_NOT = 60,                       /* NOT  */
  YYSYMBOL_NUMBER = 61,                    /* NUMBER  */
  YYSYMBOL_FLOAT = 62,                     /* FLOAT  */
  YYSYMBOL_ID = 63,                        /* ID  */
  YYSYMBOL_PATH = 64,                      /* PATH  */
  YYSYMBOL_SSS = 65,                       /* SSS  */
  YYSYMBOL_STAR = 66,                      /* STAR  */
  YYSYMBOL_STRING_V = 67,                  /* STRING_V  */
  YYSYMBOL_YYACCEPT = 68,                  /* $accept  */
  YYSYMBOL_commands = 69,                  /* commands  */
  YYSYMBOL_command = 70,                   /* command  */
  YYSYMBOL_exit = 71,                      /* exit  */
  YYSYMBOL_help = 72,                      /* help  */
  YYSYMBOL_sync = 73,                      /* sync  */
  YYSYMBOL_begin = 74,                     /* begin  */
  YYSYMBOL_commit = 75,                    /* commit  */
  YYSYMBOL_rollback = 76,                  /* rollback  */
  YYSYMBOL_drop_table = 77,                /* drop_table  */
  YYSYMBOL_show_tables = 78,               /* show_tables  */
  YYSYMBOL_desc_table = 79,                /* desc_table  */
  YYSYMBOL_create_index = 80,              /* create_index  */
  YYSYMBOL_ID_list = 81,                   /* ID_list  */
  YYSYMBOL_drop_index = 82,                /* drop_index  */
  YYSYMBOL_create_table = 83,              /* create_table  */
  YYSYMBOL_attr_def_list = 84,             /* attr_def_list  */
  YYSYMBOL_attr_def = 85,                  /* attr_def  */
  YYSYMBOL_null_def = 86,                  /* null_def  */
  YYSYMBOL_number = 87,                    /* number  */
  YYSYMBOL_type = 88,                      /* type  */
  YYSYMBOL_agg_type = 89,                  /* agg_type  */
  YYSYMBOL_order_type = 90,                /* order_type  */
  YYSYMBOL_ID_get = 91,                    /* ID_get  */
  YYSYMBOL_insert_value_list = 92,         /* insert_value_list  */
  YYSYMBOL_insert = 93,                    /* insert  */
  YYSYMBOL_value_list = 94,                /* value_list  */
  YYSYMBOL_value = 95,                     /* value  */
  YYSYMBOL_delete = 96,                    /* delete  */
  YYSYMBOL_update = 97,                    /* update  */
  YYSYMBOL_select = 98,                    /* select  */
  YYSYMBOL_table = 99,                     /* table  */
  YYSYMBOL_join_list = 100,                /* join_list  */
  YYSYMBOL_select_attr = 101,              /* select_attr  */
  YYSYMBOL_attr_list = 102,                /* attr_list  */
  YYSYMBOL_agg_list = 103,                 /* agg_list  */
  YYSYMBOL_rel_list = 104,                 /* rel_list  */
  YYSYMBOL_where = 105,                    /* where  */
  YYSYMBOL_condition_list = 106,           /* condition_list  */
  YYSYMBOL_condition = 107,                /* condition  */
  YYSYMBOL_group_by = 108,                 /* group_by  */
  YYSYMBOL_group_by_attr_list = 109,       /* group_by_attr_list  */
  YYSYMBOL_comOp = 110,                    /* comOp  */
  YYSYMBOL_load_data = 111,                /* load_data  */
  YYSYMBOL_order = 112,                    /* order  */
  YYSYMBOL_order_attrs = 113               /* order_attrs  */
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
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   274

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  68
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  46
/* YYNRULES -- Number of rules.  */
#define YYNRULES  124
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  278

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   322


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
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   159,   159,   161,   165,   166,   167,   168,   169,   170,
     171,   172,   173,   174,   175,   176,   177,   178,   179,   180,
     181,   185,   190,   195,   201,   207,   213,   219,   225,   231,
     238,   243,   251,   254,   261,   268,   277,   279,   283,   291,
     308,   309,   310,   315,   319,   320,   321,   322,   323,   327,
     328,   329,   330,   334,   336,   341,   348,   350,   356,   365,
     367,   372,   376,   380,   385,   392,   403,   413,   431,   434,
     441,   443,   450,   456,   462,   468,   474,   480,   486,   493,
     495,   502,   511,   513,   519,   525,   531,   539,   541,   546,
     548,   553,   555,   561,   582,   602,   622,   644,   665,   686,
     707,   709,   714,   721,   723,   728,   736,   737,   738,   739,
     740,   741,   742,   743,   747,   754,   756,   762,   768,   774,
     781,   783,   790,   796,   802
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
  "HELP", "EXIT", "DOT", "INTO", "VALUES", "FROM", "WHERE", "AND", "GROUP",
  "SET", "INNER", "JOIN", "ON", "IS", "LOAD", "DATA", "INFILE", "UNIQUE",
  "ASC", "ORDER", "BY", "EQ", "LT", "GT", "LE", "GE", "NE", "NOT",
  "NUMBER", "FLOAT", "ID", "PATH", "SSS", "STAR", "STRING_V", "$accept",
  "commands", "command", "exit", "help", "sync", "begin", "commit",
  "rollback", "drop_table", "show_tables", "desc_table", "create_index",
  "ID_list", "drop_index", "create_table", "attr_def_list", "attr_def",
  "null_def", "number", "type", "agg_type", "order_type", "ID_get",
  "insert_value_list", "insert", "value_list", "value", "delete", "update",
  "select", "table", "join_list", "select_attr", "attr_list", "agg_list",
  "rel_list", "where", "condition_list", "condition", "group_by",
  "group_by_attr_list", "comOp", "load_data", "order", "order_attrs", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-224)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -224,   120,  -224,    10,    46,    24,   -41,    31,    45,    19,
      21,     9,    89,    91,    92,   104,   105,    29,  -224,  -224,
    -224,  -224,  -224,  -224,  -224,  -224,  -224,  -224,  -224,  -224,
    -224,  -224,  -224,  -224,  -224,  -224,    49,    50,   106,    51,
      59,  -224,  -224,  -224,  -224,    11,  -224,   101,    96,   132,
     141,  -224,    85,    86,   108,  -224,  -224,  -224,  -224,  -224,
     111,   140,   123,   100,   162,   166,   107,   121,  -224,    66,
     122,  -224,  -224,   146,   147,   124,   125,   126,   128,   148,
    -224,  -224,    62,   164,  -224,    -7,   169,   171,   152,   172,
     175,     3,   195,   145,   165,  -224,   176,   150,   180,   142,
     144,  -224,  -224,   179,   149,   179,   179,   160,   122,   147,
      23,  -224,  -224,  -224,    47,  -224,   118,   168,  -224,    23,
     198,   126,   186,  -224,  -224,  -224,  -224,  -224,    -3,   142,
     187,   188,   164,   143,  -224,   190,  -224,  -224,   151,   172,
     174,   192,   154,   158,  -224,  -224,  -224,  -224,  -224,  -224,
       8,    13,     3,  -224,   147,   156,   176,   217,  -224,   215,
     200,   201,   142,   163,  -224,   203,   179,   178,  -224,   177,
     181,    23,   204,   118,  -224,  -224,  -224,   193,  -224,   168,
     226,   228,  -224,  -224,  -224,   173,   229,  -224,   212,    67,
    -224,     3,   182,   183,   234,   192,   214,    18,   184,  -224,
    -224,  -224,   216,  -224,   237,    -2,   218,   219,   168,    74,
     185,  -224,  -224,   221,   241,   211,  -224,  -224,  -224,  -224,
     179,   189,   179,   179,   206,   191,   194,  -224,    -1,    23,
    -224,   196,  -224,   227,  -224,  -224,   207,  -224,    76,   231,
    -224,   197,   199,  -224,   232,  -224,   192,  -224,   179,   202,
     205,  -224,  -224,    75,     1,  -224,   230,  -224,   213,   231,
     208,   232,  -224,   232,  -224,   214,     3,  -224,     1,  -224,
    -224,  -224,   168,   232,  -224,   206,  -224,  -224
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
       0,    49,    50,    51,    52,    79,    72,     0,     0,     0,
       0,    23,     0,     0,     0,    24,    25,    26,    22,    21,
       0,     0,     0,     0,     0,     0,     0,     0,    73,     0,
       0,    29,    28,     0,    89,     0,     0,     0,     0,     0,
      27,    34,    79,    79,    43,     0,     0,     0,    68,    87,
       0,     0,     0,     0,     0,    55,    36,     0,     0,     0,
       0,    80,    74,    82,     0,    82,    82,     0,     0,    89,
       0,    64,    61,    62,     0,    63,     0,    91,    65,     0,
       0,     0,     0,    44,    45,    46,    48,    47,    40,     0,
      32,     0,    79,     0,    77,     0,    75,    76,     0,    87,
     100,    59,     0,   112,   106,   107,   108,   109,   110,   111,
       0,     0,     0,    90,    89,     0,    36,     0,    41,     0,
      39,     0,     0,     0,    81,     0,    82,     0,    88,     0,
     115,     0,     0,     0,   113,    95,    93,    96,    94,    91,
       0,     0,    37,    35,    42,     0,     0,    33,     0,     0,
      78,     0,     0,     0,     0,    59,    56,     0,     0,    92,
      66,   114,     0,    30,     0,     0,     0,     0,    91,   103,
       0,    67,    60,     0,     0,     0,    97,    98,    38,    31,
      82,     0,    82,    82,    70,     0,     0,   101,   120,     0,
      58,     0,    85,     0,    83,    84,     0,    69,   103,   103,
      54,     0,     0,    53,   120,   117,    59,    99,    82,     0,
       0,   104,   102,   120,   120,   116,     0,    86,     0,   103,
       0,   120,   122,   120,   118,    56,     0,   105,   120,   121,
     119,    57,    91,   120,   123,    70,   124,    71
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -224,  -224,  -224,  -224,  -224,  -224,  -224,  -224,  -224,  -224,
    -224,  -224,  -224,  -121,  -224,  -224,   110,   153,  -224,  -136,
    -224,   130,  -223,  -224,    -4,  -224,  -188,  -108,  -224,  -224,
    -224,   159,   -11,  -224,   -70,  -105,   131,  -103,  -176,  -147,
    -224,  -212,  -106,  -224,  -224,  -102
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     1,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,   131,    29,    30,   122,    96,   160,    87,
     128,    47,   244,    97,   214,    31,   172,   116,    32,    33,
      34,    89,   237,    48,    68,   134,   109,    92,   153,   117,
     170,   227,   150,    35,   194,   245
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     136,   137,   141,   199,   158,   179,   140,   212,   161,   111,
     151,   154,   101,   102,   111,   240,   103,   240,    36,   111,
      37,   220,    49,   241,   111,   241,   251,   252,   104,   111,
     261,   263,   224,   221,   242,    66,    41,    42,    43,    44,
      50,   187,   176,   178,   208,   273,    67,   267,    51,   202,
     243,   180,   243,   207,    39,    52,    40,   159,   256,    53,
      38,   190,   164,   195,   112,   113,   114,   197,   115,   112,
     113,   175,    54,   115,   112,   113,   177,    60,   115,   112,
     113,   215,   142,   115,   112,   113,    66,    45,   115,   216,
      46,   240,    55,   143,    56,    57,   275,   100,   225,   241,
     225,   144,   145,   146,   147,   148,   149,    58,    59,   226,
     260,   250,    61,    62,    64,   232,    63,   234,   235,   272,
       2,   246,    65,    69,     3,     4,   243,    84,    84,    85,
     205,     5,    86,   206,    70,    71,     6,     7,     8,     9,
      10,    11,   255,   257,    72,    12,    13,    14,    73,    74,
      75,   262,   264,    15,    16,    41,    42,    43,    44,   269,
      76,   270,    77,    79,   143,    80,   274,    17,    78,    81,
      82,   276,   144,   145,   146,   147,   148,   149,   123,   124,
     125,   126,   127,    90,    83,    88,    91,    93,    66,    95,
      94,    98,   105,    99,   106,   107,   108,   110,   118,   119,
     121,   120,   129,   133,   138,   130,   155,   132,   152,   157,
     163,   162,   135,   166,   167,   169,   171,   173,   174,   181,
     183,   184,   185,   191,   186,   189,   188,   196,   198,   200,
     192,   201,   203,   193,    84,   204,   210,   211,   213,   218,
     219,   222,   223,   229,   230,   209,   231,   217,   228,   236,
     248,   249,   233,   265,   238,   225,   241,   239,   266,   247,
     253,   271,   254,   165,   277,   258,   182,   139,   259,     0,
     168,   268,     0,     0,   156
};

static const yytype_int16 yycheck[] =
{
     105,   106,   110,   179,     7,   152,   109,   195,   129,     6,
     116,   119,    82,    83,     6,    16,    23,    16,     8,     6,
      10,    23,    63,    24,     6,    24,   238,   239,    35,     6,
     253,   254,   208,    35,    35,    24,    12,    13,    14,    15,
       9,   162,   150,   151,   191,   268,    35,   259,     3,   185,
      51,   154,    51,   189,     8,    36,    10,    60,   246,    38,
      50,   166,   132,   171,    61,    62,    63,   173,    65,    61,
      62,    63,    63,    65,    61,    62,    63,    48,    65,    61,
      62,    63,    35,    65,    61,    62,    24,    63,    65,   197,
      66,    16,     3,    46,     3,     3,   272,    35,    24,    24,
      24,    54,    55,    56,    57,    58,    59,     3,     3,    35,
      35,    35,    63,    63,    63,   220,    10,   222,   223,   266,
       0,   229,    63,    22,     4,     5,    51,    61,    61,    63,
      63,    11,    66,    66,    38,     3,    16,    17,    18,    19,
      20,    21,   244,   248,     3,    25,    26,    27,    63,    63,
      42,   253,   254,    33,    34,    12,    13,    14,    15,   261,
      49,   263,    22,    63,    46,     3,   268,    47,    45,     3,
      63,   273,    54,    55,    56,    57,    58,    59,    28,    29,
      30,    31,    32,    37,    63,    63,    39,    63,    24,    63,
      65,    63,    23,    45,    23,    43,    24,    22,     3,    54,
      24,    36,    22,    24,    44,    63,     8,    63,    40,    23,
      22,    24,    63,    23,    63,    41,    24,    63,    60,    63,
       3,     6,    22,    45,    23,    22,    63,    23,    35,     3,
      53,     3,     3,    52,    61,    23,    53,     3,    24,    23,
       3,    23,    23,    22,     3,    63,    35,    63,    63,    43,
      23,    44,    63,    23,    63,    24,    24,    63,    45,    63,
      63,   265,    63,   133,   275,    63,   156,   108,    63,    -1,
     139,    63,    -1,    -1,   121
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    69,     0,     4,     5,    11,    16,    17,    18,    19,
      20,    21,    25,    26,    27,    33,    34,    47,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    82,
      83,    93,    96,    97,    98,   111,     8,    10,    50,     8,
      10,    12,    13,    14,    15,    63,    66,    89,   101,    63,
       9,     3,    36,    38,    63,     3,     3,     3,     3,     3,
      48,    63,    63,    10,    63,    63,    24,    35,   102,    22,
      38,     3,     3,    63,    63,    42,    49,    22,    45,    63,
       3,     3,    63,    63,    61,    63,    66,    87,    63,    99,
      37,    39,   105,    63,    65,    63,    85,    91,    63,    45,
      35,   102,   102,    23,    35,    23,    23,    43,    24,   104,
      22,     6,    61,    62,    63,    65,    95,   107,     3,    54,
      36,    24,    84,    28,    29,    30,    31,    32,    88,    22,
      63,    81,    63,    24,   103,    63,   103,   103,    44,    99,
     105,    95,    35,    46,    54,    55,    56,    57,    58,    59,
     110,   110,    40,   106,    95,     8,    85,    23,     7,    60,
      86,    81,    24,    22,   102,    89,    23,    63,   104,    41,
     108,    24,    94,    63,    60,    63,    95,    63,    95,   107,
     105,    63,    84,     3,     6,    22,    23,    81,    63,    22,
     103,    45,    53,    52,   112,    95,    23,   110,    35,   106,
       3,     3,    87,     3,    23,    63,    66,    87,   107,    63,
      53,     3,    94,    24,    92,    63,    95,    63,    23,     3,
      23,    35,    23,    23,   106,    24,    35,   109,    63,    22,
       3,    35,   103,    63,   103,   103,    43,   100,    63,    63,
      16,    24,    35,    51,    90,   113,    95,    63,    23,    44,
      35,   109,   109,    63,    63,   113,    94,   103,    63,    63,
      35,    90,   113,    90,   113,    23,    45,   109,    63,   113,
     113,    92,   107,    90,   113,   106,   113,   100
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    68,    69,    69,    70,    70,    70,    70,    70,    70,
      70,    70,    70,    70,    70,    70,    70,    70,    70,    70,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    80,    81,    81,    82,    83,    84,    84,    85,    85,
      86,    86,    86,    87,    88,    88,    88,    88,    88,    89,
      89,    89,    89,    90,    90,    91,    92,    92,    93,    94,
      94,    95,    95,    95,    95,    96,    97,    98,    99,    99,
     100,   100,   101,   101,   101,   101,   101,   101,   101,   102,
     102,   102,   103,   103,   103,   103,   103,   104,   104,   105,
     105,   106,   106,   107,   107,   107,   107,   107,   107,   107,
     108,   108,   108,   109,   109,   109,   110,   110,   110,   110,
     110,   110,   110,   110,   111,   112,   112,   112,   112,   112,
     113,   113,   113,   113,   113
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
       3,     1,     1,     1,     1,     5,     8,     9,     1,     8,
       0,     7,     1,     2,     4,     5,     5,     5,     7,     0,
       3,     5,     0,     6,     6,     6,     8,     0,     3,     0,
       3,     0,     3,     3,     3,     3,     3,     5,     5,     7,
       0,     4,     6,     0,     3,     5,     1,     1,     1,     1,
       1,     1,     1,     2,     8,     0,     5,     4,     6,     7,
       0,     4,     3,     5,     6
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
#line 185 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_EXIT;//"exit";
    }
#line 1430 "yacc_sql.tab.c"
    break;

  case 22: /* help: HELP SEMICOLON  */
#line 190 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_HELP;//"help";
    }
#line 1438 "yacc_sql.tab.c"
    break;

  case 23: /* sync: SYNC SEMICOLON  */
#line 195 "yacc_sql.y"
                   {
      CONTEXT->ssql->flag = SCF_SYNC;
    }
#line 1446 "yacc_sql.tab.c"
    break;

  case 24: /* begin: TRX_BEGIN SEMICOLON  */
#line 201 "yacc_sql.y"
                        {
      CONTEXT->ssql->flag = SCF_BEGIN;
    }
#line 1454 "yacc_sql.tab.c"
    break;

  case 25: /* commit: TRX_COMMIT SEMICOLON  */
#line 207 "yacc_sql.y"
                         {
      CONTEXT->ssql->flag = SCF_COMMIT;
    }
#line 1462 "yacc_sql.tab.c"
    break;

  case 26: /* rollback: TRX_ROLLBACK SEMICOLON  */
#line 213 "yacc_sql.y"
                           {
      CONTEXT->ssql->flag = SCF_ROLLBACK;
    }
#line 1470 "yacc_sql.tab.c"
    break;

  case 27: /* drop_table: DROP TABLE ID SEMICOLON  */
#line 219 "yacc_sql.y"
                            {
        CONTEXT->ssql->flag = SCF_DROP_TABLE;//"drop_table";
        drop_table_init(&CONTEXT->ssql->sstr.drop_table, (yyvsp[-1].string));
    }
#line 1479 "yacc_sql.tab.c"
    break;

  case 28: /* show_tables: SHOW TABLES SEMICOLON  */
#line 225 "yacc_sql.y"
                          {
      CONTEXT->ssql->flag = SCF_SHOW_TABLES;
    }
#line 1487 "yacc_sql.tab.c"
    break;

  case 29: /* desc_table: DESC ID SEMICOLON  */
#line 231 "yacc_sql.y"
                      {
      CONTEXT->ssql->flag = SCF_DESC_TABLE;
      desc_table_init(&CONTEXT->ssql->sstr.desc_table, (yyvsp[-1].string));
    }
#line 1496 "yacc_sql.tab.c"
    break;

  case 30: /* create_index: CREATE INDEX ID ON ID LBRACE ID_list RBRACE SEMICOLON  */
#line 239 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
			create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-6].string), (yyvsp[-4].string), (yyvsp[-2].string));
		}
#line 1505 "yacc_sql.tab.c"
    break;

  case 31: /* create_index: CREATE UNIQUE INDEX ID ON ID_list LBRACE ID RBRACE SEMICOLON  */
#line 244 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_CREATE_UNIQUE_INDEX;// "create_unique_index";
			create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-6].string), (yyvsp[-4].string), (yyvsp[-2].string));
    		}
#line 1514 "yacc_sql.tab.c"
    break;

  case 32: /* ID_list: ID  */
#line 251 "yacc_sql.y"
                {
    			(yyval.string) = (yyvsp[0].string);
    		}
#line 1522 "yacc_sql.tab.c"
    break;

  case 33: /* ID_list: ID COMMA ID_list  */
#line 255 "yacc_sql.y"
                {
			(yyval.string) = (yyvsp[-2].string);
    		}
#line 1530 "yacc_sql.tab.c"
    break;

  case 34: /* drop_index: DROP INDEX ID SEMICOLON  */
#line 262 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_DROP_INDEX;//"drop_index";
			drop_index_init(&CONTEXT->ssql->sstr.drop_index, (yyvsp[-1].string));
		}
#line 1539 "yacc_sql.tab.c"
    break;

  case 35: /* create_table: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE SEMICOLON  */
#line 269 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_CREATE_TABLE;//"create_table";
			// CONTEXT->ssql->sstr.create_table.attribute_count = CONTEXT->value_length;
			create_table_init_name(&CONTEXT->ssql->sstr.create_table, (yyvsp[-5].string));
			//临时变量清零	
			CONTEXT->value_length = 0;
		}
#line 1551 "yacc_sql.tab.c"
    break;

  case 37: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 279 "yacc_sql.y"
                                   {    }
#line 1557 "yacc_sql.tab.c"
    break;

  case 38: /* attr_def: ID_get type null_def LBRACE number RBRACE  */
#line 284 "yacc_sql.y"
                {
			AttrInfo attribute;
			// 我们让nullable的列增加4个字节
			attr_info_init(&attribute, CONTEXT->id, (yyvsp[-4].number), (yyvsp[-1].number) + (yyvsp[-3].number) * 4, (yyvsp[-3].number));
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			CONTEXT->value_length++;
		}
#line 1569 "yacc_sql.tab.c"
    break;

  case 39: /* attr_def: ID_get type null_def  */
#line 292 "yacc_sql.y"
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
#line 1586 "yacc_sql.tab.c"
    break;

  case 40: /* null_def: %empty  */
#line 308 "yacc_sql.y"
          { (yyval.number) = 0; }
#line 1592 "yacc_sql.tab.c"
    break;

  case 41: /* null_def: NULLABLE_T  */
#line 309 "yacc_sql.y"
                     { (yyval.number) = 1; }
#line 1598 "yacc_sql.tab.c"
    break;

  case 42: /* null_def: NOT NULL_T  */
#line 310 "yacc_sql.y"
                     { (yyval.number) = 0; }
#line 1604 "yacc_sql.tab.c"
    break;

  case 43: /* number: NUMBER  */
#line 315 "yacc_sql.y"
                       {(yyval.number) = (yyvsp[0].number);}
#line 1610 "yacc_sql.tab.c"
    break;

  case 44: /* type: INT_T  */
#line 319 "yacc_sql.y"
              { (yyval.number)=INTS; }
#line 1616 "yacc_sql.tab.c"
    break;

  case 45: /* type: STRING_T  */
#line 320 "yacc_sql.y"
                  { (yyval.number)=CHARS; }
#line 1622 "yacc_sql.tab.c"
    break;

  case 46: /* type: FLOAT_T  */
#line 321 "yacc_sql.y"
                 { (yyval.number)=FLOATS; }
#line 1628 "yacc_sql.tab.c"
    break;

  case 47: /* type: DATE_T  */
#line 322 "yacc_sql.y"
                { (yyval.number)=DATE; }
#line 1634 "yacc_sql.tab.c"
    break;

  case 48: /* type: TEXT_T  */
#line 323 "yacc_sql.y"
                { (yyval.number) = TEXTS; }
#line 1640 "yacc_sql.tab.c"
    break;

  case 49: /* agg_type: MAX  */
#line 327 "yacc_sql.y"
            { (yyval.number) = AGG_MAX; }
#line 1646 "yacc_sql.tab.c"
    break;

  case 50: /* agg_type: MIN  */
#line 328 "yacc_sql.y"
              { (yyval.number) = AGG_MIN; }
#line 1652 "yacc_sql.tab.c"
    break;

  case 51: /* agg_type: COUNT  */
#line 329 "yacc_sql.y"
                { (yyval.number) = AGG_COUNT; }
#line 1658 "yacc_sql.tab.c"
    break;

  case 52: /* agg_type: AVG  */
#line 330 "yacc_sql.y"
              { (yyval.number) = AGG_AVG; }
#line 1664 "yacc_sql.tab.c"
    break;

  case 53: /* order_type: ASC  */
#line 334 "yacc_sql.y"
            {
	(yyval.number) = ORDER_ASC; printf("I am ASC\n");}
#line 1671 "yacc_sql.tab.c"
    break;

  case 54: /* order_type: DESC  */
#line 336 "yacc_sql.y"
               {
	(yyval.number) = ORDER_DESC; printf("I am DESC\n");}
#line 1678 "yacc_sql.tab.c"
    break;

  case 55: /* ID_get: ID  */
#line 342 "yacc_sql.y"
        {
		char *temp=(yyvsp[0].string); 
		snprintf(CONTEXT->id, sizeof(CONTEXT->id), "%s", temp);
	}
#line 1687 "yacc_sql.tab.c"
    break;

  case 57: /* insert_value_list: COMMA LBRACE value value_list RBRACE insert_value_list  */
#line 351 "yacc_sql.y"
                {

    		}
#line 1695 "yacc_sql.tab.c"
    break;

  case 58: /* insert: INSERT INTO ID VALUES LBRACE value value_list RBRACE insert_value_list SEMICOLON  */
#line 357 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_INSERT;//"insert";
			inserts_init(&CONTEXT->ssql->sstr.insertion, (yyvsp[-7].string), CONTEXT->values, CONTEXT->value_length);

      			//临时变量清零
      			CONTEXT->value_length=0;
    		}
#line 1707 "yacc_sql.tab.c"
    break;

  case 60: /* value_list: COMMA value value_list  */
#line 367 "yacc_sql.y"
                              { 
  		// CONTEXT->values[CONTEXT->value_length++] = *$2;
	  }
#line 1715 "yacc_sql.tab.c"
    break;

  case 61: /* value: NUMBER  */
#line 373 "yacc_sql.y"
                {
  			value_init_integer(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].number));
		}
#line 1723 "yacc_sql.tab.c"
    break;

  case 62: /* value: FLOAT  */
#line 377 "yacc_sql.y"
                {
  			value_init_float(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].floats));
		}
#line 1731 "yacc_sql.tab.c"
    break;

  case 63: /* value: SSS  */
#line 381 "yacc_sql.y"
                {
			(yyvsp[0].string) = substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
  			value_init_string(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].string));
		}
#line 1740 "yacc_sql.tab.c"
    break;

  case 64: /* value: NULL_T  */
#line 386 "yacc_sql.y"
                {
    			value_init_null(&CONTEXT->values[CONTEXT->value_length++]);
    		}
#line 1748 "yacc_sql.tab.c"
    break;

  case 65: /* delete: DELETE FROM ID where SEMICOLON  */
#line 393 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_DELETE;//"delete";
			deletes_init_relation(&CONTEXT->ssql->sstr.deletion, (yyvsp[-2].string));
			deletes_set_conditions(&CONTEXT->ssql->sstr.deletion, 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;	
    }
#line 1760 "yacc_sql.tab.c"
    break;

  case 66: /* update: UPDATE ID SET ID EQ value where SEMICOLON  */
#line 404 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_UPDATE;//"update";
			Value *value = &CONTEXT->values[0];
			updates_init(&CONTEXT->ssql->sstr.update, (yyvsp[-6].string), (yyvsp[-4].string), value, 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;
		}
#line 1772 "yacc_sql.tab.c"
    break;

  case 67: /* select: SELECT select_attr FROM table rel_list where group_by order SEMICOLON  */
#line 414 "yacc_sql.y"
                {
			// CONTEXT->ssql->sstr.selection.relations[CONTEXT->from_length++]=$4;
//			selects_append_relation(&CONTEXT->ssql->sstr.selection, $4);
			selects_append_conditions(&CONTEXT->ssql->sstr.selection, CONTEXT->conditions, CONTEXT->condition_length);

			CONTEXT->ssql->flag=SCF_SELECT;//"select";
			// CONTEXT->ssql->sstr.selection.attr_num = CONTEXT->select_length;

			//临时变量清零
			CONTEXT->condition_length=0;
			CONTEXT->from_length=0;
			CONTEXT->select_length=0;
			CONTEXT->value_length = 0;
	}
#line 1791 "yacc_sql.tab.c"
    break;

  case 68: /* table: ID  */
#line 431 "yacc_sql.y"
                {
			selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[0].string));
		}
#line 1799 "yacc_sql.tab.c"
    break;

  case 69: /* table: ID INNER JOIN ID ON condition condition_list join_list  */
#line 435 "yacc_sql.y"
                {
			selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-7].string));
			selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-4].string));
		}
#line 1808 "yacc_sql.tab.c"
    break;

  case 71: /* join_list: INNER JOIN ID ON condition condition_list join_list  */
#line 444 "yacc_sql.y"
                {
			selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-4].string));
		}
#line 1816 "yacc_sql.tab.c"
    break;

  case 72: /* select_attr: STAR  */
#line 451 "yacc_sql.y"
                {
			RelAttr attr;
			relation_attr_init(&attr, NULL, "*");
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 1826 "yacc_sql.tab.c"
    break;

  case 73: /* select_attr: ID attr_list  */
#line 457 "yacc_sql.y"
                {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 1836 "yacc_sql.tab.c"
    break;

  case 74: /* select_attr: ID DOT ID attr_list  */
#line 463 "yacc_sql.y"
                {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 1846 "yacc_sql.tab.c"
    break;

  case 75: /* select_attr: agg_type LBRACE STAR RBRACE agg_list  */
#line 469 "yacc_sql.y"
                {
			AggDesc agg_desc;
			agg_desc_init_string(&agg_desc, (yyvsp[-4].number), AGG_STAR, NULL, "*");
			selects_append_agg(&CONTEXT->ssql->sstr.selection, &agg_desc);
		}
#line 1856 "yacc_sql.tab.c"
    break;

  case 76: /* select_attr: agg_type LBRACE number RBRACE agg_list  */
#line 475 "yacc_sql.y"
                {
			AggDesc agg_desc;
			agg_desc_init_number(&agg_desc, (yyvsp[-4].number), AGG_NUMBER, (yyvsp[-2].number));
			selects_append_agg(&CONTEXT->ssql->sstr.selection, &agg_desc);
		}
#line 1866 "yacc_sql.tab.c"
    break;

  case 77: /* select_attr: agg_type LBRACE ID RBRACE agg_list  */
#line 481 "yacc_sql.y"
                {
			AggDesc agg_desc;
			agg_desc_init_string(&agg_desc, (yyvsp[-4].number), AGG_FIELD, NULL, (yyvsp[-2].string));
			selects_append_agg(&CONTEXT->ssql->sstr.selection, &agg_desc);
		}
#line 1876 "yacc_sql.tab.c"
    break;

  case 78: /* select_attr: agg_type LBRACE ID DOT ID RBRACE agg_list  */
#line 487 "yacc_sql.y"
                {
			AggDesc agg_desc;
			agg_desc_init_string(&agg_desc, (yyvsp[-6].number), AGG_FIELD, (yyvsp[-4].string), (yyvsp[-2].string));
			selects_append_agg(&CONTEXT->ssql->sstr.selection, &agg_desc);
		}
#line 1886 "yacc_sql.tab.c"
    break;

  case 80: /* attr_list: COMMA ID attr_list  */
#line 495 "yacc_sql.y"
                         {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
     	  // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length].relation_name = NULL;
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length++].attribute_name=$2;
      }
#line 1898 "yacc_sql.tab.c"
    break;

  case 81: /* attr_list: COMMA ID DOT ID attr_list  */
#line 502 "yacc_sql.y"
                                {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length].attribute_name=$4;
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length++].relation_name=$2;
  	  }
#line 1910 "yacc_sql.tab.c"
    break;

  case 83: /* agg_list: COMMA agg_type LBRACE STAR RBRACE agg_list  */
#line 514 "yacc_sql.y"
                {
			AggDesc agg_desc;
			agg_desc_init_string(&agg_desc, (yyvsp[-4].number), AGG_STAR, NULL, "*");
			selects_append_agg(&CONTEXT->ssql->sstr.selection, &agg_desc);
		}
#line 1920 "yacc_sql.tab.c"
    break;

  case 84: /* agg_list: COMMA agg_type LBRACE number RBRACE agg_list  */
#line 520 "yacc_sql.y"
                {
			AggDesc agg_desc;
			agg_desc_init_number(&agg_desc, (yyvsp[-4].number), AGG_NUMBER, (yyvsp[-2].number));
			selects_append_agg(&CONTEXT->ssql->sstr.selection, &agg_desc);
		}
#line 1930 "yacc_sql.tab.c"
    break;

  case 85: /* agg_list: COMMA agg_type LBRACE ID RBRACE agg_list  */
#line 526 "yacc_sql.y"
                {
			AggDesc agg_desc;
			agg_desc_init_string(&agg_desc, (yyvsp[-4].number), AGG_FIELD, NULL, (yyvsp[-2].string));
			selects_append_agg(&CONTEXT->ssql->sstr.selection, &agg_desc);
		}
#line 1940 "yacc_sql.tab.c"
    break;

  case 86: /* agg_list: COMMA agg_type LBRACE ID DOT ID RBRACE agg_list  */
#line 532 "yacc_sql.y"
                {
			AggDesc agg_desc;
			agg_desc_init_string(&agg_desc, (yyvsp[-6].number), AGG_FIELD, (yyvsp[-4].string), (yyvsp[-2].string));
			selects_append_agg(&CONTEXT->ssql->sstr.selection, &agg_desc);
		}
#line 1950 "yacc_sql.tab.c"
    break;

  case 88: /* rel_list: COMMA table rel_list  */
#line 542 "yacc_sql.y"
                {
//			selects_append_relation(&CONTEXT->ssql->sstr.selection, $2);
		}
#line 1958 "yacc_sql.tab.c"
    break;

  case 90: /* where: WHERE condition condition_list  */
#line 549 "yacc_sql.y"
                {
			// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
		}
#line 1966 "yacc_sql.tab.c"
    break;

  case 92: /* condition_list: AND condition condition_list  */
#line 556 "yacc_sql.y"
                {
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
		}
#line 1974 "yacc_sql.tab.c"
    break;

  case 93: /* condition: ID comOp value  */
#line 562 "yacc_sql.y"
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
#line 1999 "yacc_sql.tab.c"
    break;

  case 94: /* condition: value comOp value  */
#line 583 "yacc_sql.y"
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
#line 2023 "yacc_sql.tab.c"
    break;

  case 95: /* condition: ID comOp ID  */
#line 603 "yacc_sql.y"
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
#line 2047 "yacc_sql.tab.c"
    break;

  case 96: /* condition: value comOp ID  */
#line 623 "yacc_sql.y"
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
#line 2073 "yacc_sql.tab.c"
    break;

  case 97: /* condition: ID DOT ID comOp value  */
#line 645 "yacc_sql.y"
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
#line 2098 "yacc_sql.tab.c"
    break;

  case 98: /* condition: value comOp ID DOT ID  */
#line 666 "yacc_sql.y"
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
#line 2123 "yacc_sql.tab.c"
    break;

  case 99: /* condition: ID DOT ID comOp ID DOT ID  */
#line 687 "yacc_sql.y"
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
#line 2146 "yacc_sql.tab.c"
    break;

  case 101: /* group_by: GROUP BY ID group_by_attr_list  */
#line 709 "yacc_sql.y"
                                         {
		RelAttr attr;
		relation_attr_init(&attr, NULL, (yyvsp[-1].string));
		selects_append_group_by_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 2156 "yacc_sql.tab.c"
    break;

  case 102: /* group_by: GROUP BY ID DOT ID group_by_attr_list  */
#line 714 "yacc_sql.y"
                                                {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
		selects_append_group_by_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 2166 "yacc_sql.tab.c"
    break;

  case 104: /* group_by_attr_list: COMMA ID group_by_attr_list  */
#line 723 "yacc_sql.y"
                                      {
		RelAttr attr;
		relation_attr_init(&attr, NULL, (yyvsp[-1].string));
		selects_append_group_by_attribute(&CONTEXT->ssql->sstr.selection, &attr);
    }
#line 2176 "yacc_sql.tab.c"
    break;

  case 105: /* group_by_attr_list: COMMA ID DOT ID group_by_attr_list  */
#line 728 "yacc_sql.y"
                                         {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
		selects_append_group_by_attribute(&CONTEXT->ssql->sstr.selection, &attr);
  	}
#line 2186 "yacc_sql.tab.c"
    break;

  case 106: /* comOp: EQ  */
#line 736 "yacc_sql.y"
       { CONTEXT->comp = EQUAL_TO; }
#line 2192 "yacc_sql.tab.c"
    break;

  case 107: /* comOp: LT  */
#line 737 "yacc_sql.y"
         { CONTEXT->comp = LESS_THAN; }
#line 2198 "yacc_sql.tab.c"
    break;

  case 108: /* comOp: GT  */
#line 738 "yacc_sql.y"
         { CONTEXT->comp = GREAT_THAN; }
#line 2204 "yacc_sql.tab.c"
    break;

  case 109: /* comOp: LE  */
#line 739 "yacc_sql.y"
         { CONTEXT->comp = LESS_EQUAL; }
#line 2210 "yacc_sql.tab.c"
    break;

  case 110: /* comOp: GE  */
#line 740 "yacc_sql.y"
         { CONTEXT->comp = GREAT_EQUAL; }
#line 2216 "yacc_sql.tab.c"
    break;

  case 111: /* comOp: NE  */
#line 741 "yacc_sql.y"
         { CONTEXT->comp = NOT_EQUAL; }
#line 2222 "yacc_sql.tab.c"
    break;

  case 112: /* comOp: IS  */
#line 742 "yacc_sql.y"
         { CONTEXT->comp = IS_OP;}
#line 2228 "yacc_sql.tab.c"
    break;

  case 113: /* comOp: IS NOT  */
#line 743 "yacc_sql.y"
             { CONTEXT->comp = IS_NOT_OP;}
#line 2234 "yacc_sql.tab.c"
    break;

  case 114: /* load_data: LOAD DATA INFILE SSS INTO TABLE ID SEMICOLON  */
#line 748 "yacc_sql.y"
                {
		  	CONTEXT->ssql->flag = SCF_LOAD_DATA;
			load_data_init(&CONTEXT->ssql->sstr.load_data, (yyvsp[-1].string), (yyvsp[-4].string));
		}
#line 2243 "yacc_sql.tab.c"
    break;

  case 116: /* order: ORDER BY ID order_type order_attrs  */
#line 757 "yacc_sql.y"
                {
			Order order;
			order_info_init(&order, (yyvsp[-1].number), NULL,(yyvsp[-2].string));
			selects_append_order(&CONTEXT->ssql->sstr.selection, &order);
		}
#line 2253 "yacc_sql.tab.c"
    break;

  case 117: /* order: ORDER BY ID order_attrs  */
#line 763 "yacc_sql.y"
                {
			Order order;
			order_info_init(&order, ASC, NULL, (yyvsp[-1].string));
			selects_append_order(&CONTEXT->ssql->sstr.selection, &order);
		}
#line 2263 "yacc_sql.tab.c"
    break;

  case 118: /* order: ORDER BY ID DOT ID order_attrs  */
#line 769 "yacc_sql.y"
                {
			Order order;
			order_info_init(&order, ASC, (yyvsp[-3].string), (yyvsp[-1].string));
			selects_append_order(&CONTEXT->ssql->sstr.selection, &order);
		}
#line 2273 "yacc_sql.tab.c"
    break;

  case 119: /* order: ORDER BY ID DOT ID order_type order_attrs  */
#line 775 "yacc_sql.y"
                {
			Order order;
			order_info_init(&order, (yyvsp[-1].number), (yyvsp[-4].string), (yyvsp[-2].string));
			selects_append_order(&CONTEXT->ssql->sstr.selection, &order);
		}
#line 2283 "yacc_sql.tab.c"
    break;

  case 121: /* order_attrs: COMMA ID order_type order_attrs  */
#line 784 "yacc_sql.y"
                {
			Order order;
			printf("odered_type : %d\n", CONTEXT->order_type);
			order_info_init(&order, (yyvsp[-1].number), NULL,(yyvsp[-2].string));
			selects_append_order(&CONTEXT->ssql->sstr.selection, &order);
		}
#line 2294 "yacc_sql.tab.c"
    break;

  case 122: /* order_attrs: COMMA ID order_attrs  */
#line 791 "yacc_sql.y"
                {
			Order order;
			order_info_init(&order, ASC, NULL, (yyvsp[-1].string));
			selects_append_order(&CONTEXT->ssql->sstr.selection, &order);
		}
#line 2304 "yacc_sql.tab.c"
    break;

  case 123: /* order_attrs: COMMA ID DOT ID order_attrs  */
#line 797 "yacc_sql.y"
                {
			Order order;
			order_info_init(&order, ASC, (yyvsp[-3].string), (yyvsp[-1].string));
			selects_append_order(&CONTEXT->ssql->sstr.selection, &order);
		}
#line 2314 "yacc_sql.tab.c"
    break;

  case 124: /* order_attrs: COMMA ID DOT ID order_type order_attrs  */
#line 802 "yacc_sql.y"
                                                {
			Order order;
			order_info_init(&order, (yyvsp[-1].number), (yyvsp[-4].string),(yyvsp[-2].string));
			selects_append_order(&CONTEXT->ssql->sstr.selection, &order);
		}
#line 2324 "yacc_sql.tab.c"
    break;


#line 2328 "yacc_sql.tab.c"

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

#line 809 "yacc_sql.y"

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
