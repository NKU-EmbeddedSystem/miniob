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
  YYSYMBOL_join_list = 99,                 /* join_list  */
  YYSYMBOL_select_attr = 100,              /* select_attr  */
  YYSYMBOL_attr_list = 101,                /* attr_list  */
  YYSYMBOL_rel_list = 102,                 /* rel_list  */
  YYSYMBOL_where = 103,                    /* where  */
  YYSYMBOL_condition_list = 104,           /* condition_list  */
  YYSYMBOL_condition = 105,                /* condition  */
  YYSYMBOL_group_by = 106,                 /* group_by  */
  YYSYMBOL_group_by_attr_list = 107,       /* group_by_attr_list  */
  YYSYMBOL_comOp = 108,                    /* comOp  */
  YYSYMBOL_load_data = 109,                /* load_data  */
  YYSYMBOL_order = 110,                    /* order  */
  YYSYMBOL_order_attrs = 111               /* order_attrs  */
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
#define YYLAST   277

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  68
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  44
/* YYNRULES -- Number of rules.  */
#define YYNRULES  121
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  271

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
     238,   243,   251,   255,   263,   270,   279,   281,   285,   293,
     310,   311,   312,   317,   321,   322,   323,   324,   325,   329,
     330,   331,   332,   336,   338,   343,   350,   352,   358,   367,
     369,   374,   378,   382,   387,   394,   405,   415,   439,   441,
     448,   454,   460,   466,   472,   478,   484,   492,   494,   501,
     508,   514,   520,   526,   534,   536,   541,   543,   548,   550,
     556,   577,   597,   617,   639,   660,   681,   702,   704,   709,
     716,   718,   723,   731,   732,   733,   734,   735,   736,   737,
     738,   742,   749,   751,   757,   763,   769,   776,   778,   785,
     791,   797
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
  "select", "join_list", "select_attr", "attr_list", "rel_list", "where",
  "condition_list", "condition", "group_by", "group_by_attr_list", "comOp",
  "load_data", "order", "order_attrs", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-223)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -223,    93,  -223,    19,   123,    33,   -26,    29,    50,    18,
      23,    -6,    71,    98,   105,   126,   134,    59,  -223,  -223,
    -223,  -223,  -223,  -223,  -223,  -223,  -223,  -223,  -223,  -223,
    -223,  -223,  -223,  -223,  -223,  -223,    40,    75,   131,    79,
      80,  -223,  -223,  -223,  -223,    55,  -223,   138,   124,   158,
     160,  -223,   102,   106,   129,  -223,  -223,  -223,  -223,  -223,
     119,   150,   136,   111,   179,   180,     0,   122,  -223,   -33,
     127,  -223,  -223,   147,   148,   128,   130,   133,   135,   141,
    -223,  -223,    82,   166,   165,  -223,    21,   169,   170,   151,
     175,     5,   196,   146,   167,  -223,   177,   125,   182,   139,
     142,  -223,    39,  -223,   165,   143,   165,   165,   163,   184,
      30,  -223,  -223,  -223,    90,  -223,   121,   171,  -223,    30,
     201,   133,   187,  -223,  -223,  -223,  -223,  -223,    -1,   149,
     191,   165,    27,   192,   193,  -223,   194,  -223,  -223,   155,
     156,   148,   190,   157,   161,  -223,  -223,  -223,  -223,  -223,
    -223,    10,    15,     5,  -223,   148,   159,   177,   220,  -223,
     218,   203,   202,   204,   149,  -223,   165,   168,   165,   165,
     165,   183,   151,   188,    30,   207,   121,  -223,  -223,  -223,
     197,  -223,   171,   230,   231,  -223,  -223,  -223,   174,   149,
     233,   214,  -223,   215,  -223,  -223,  -223,     5,   184,   186,
     189,   190,   216,    20,   181,  -223,  -223,  -223,   219,  -223,
    -223,   240,   165,   171,  -223,   185,   198,   242,  -223,   224,
     244,   217,  -223,  -223,  -223,  -223,  -223,   151,    97,   195,
    -223,    30,  -223,   199,  -223,   200,   205,  -223,    99,   190,
    -223,   104,   225,  -223,   206,   208,  -223,   226,  -223,   232,
     209,  -223,  -223,   100,     7,  -223,   216,   225,   210,   226,
    -223,   226,  -223,  -223,  -223,     7,  -223,  -223,   226,  -223,
    -223
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
       0,    64,    61,    62,     0,    63,     0,    88,    65,     0,
       0,     0,     0,    44,    45,    46,    48,    47,    40,     0,
       0,    77,     0,     0,     0,    75,     0,    73,    74,     0,
       0,    86,    59,     0,   109,   103,   104,   105,   106,   107,
     108,     0,     0,     0,    87,    86,     0,    36,     0,    41,
       0,    39,    32,     0,     0,    79,    77,     0,    77,    77,
      77,     0,    68,    97,     0,     0,     0,   110,    92,    90,
      93,    91,    88,     0,     0,    37,    35,    42,     0,     0,
       0,     0,    82,     0,    80,    81,    76,     0,    84,     0,
     112,    59,    56,     0,     0,    89,    66,   111,     0,    33,
      30,     0,    77,    88,    85,     0,     0,     0,    60,     0,
       0,     0,    94,    95,    38,    31,    83,    68,   100,     0,
      67,     0,    58,     0,    69,     0,     0,    98,   117,    59,
      96,   100,   100,    54,     0,     0,    53,   117,   114,     0,
       0,   101,    99,   117,   117,   113,    56,   100,     0,   117,
     119,   117,   115,    57,   102,   117,   118,   116,   117,   120,
     121
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -223,  -223,  -223,  -223,  -223,  -223,  -223,  -223,  -223,  -223,
    -223,  -223,  -223,  -155,  -223,  -223,    96,   140,  -223,   -99,
    -223,   211,  -213,  -223,    -2,  -223,  -184,  -109,  -223,  -223,
    -223,  -167,  -223,   -82,    58,  -123,  -174,  -146,  -223,  -222,
    -112,  -223,  -223,   -95
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     1,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,   163,    29,    30,   122,    96,   161,    88,
     128,    47,   247,    97,   220,    31,   175,   116,    32,    33,
      34,   109,    48,    68,   141,    92,   154,   117,   200,   237,
     151,    35,   217,   248
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     101,   142,   103,   134,   152,   198,   159,   182,   205,   191,
     155,   111,    41,    42,    43,    44,   111,   218,   173,   251,
     252,   111,   135,   243,   137,   138,   111,    36,    85,    37,
      86,   244,   183,    87,   209,   264,   111,    49,    50,   227,
     259,   261,   179,   181,   104,    41,    42,    43,    44,   165,
     166,   213,   268,    51,    52,   249,   105,    54,   246,   160,
     234,    53,   167,    82,   203,   201,   112,   113,   114,    38,
     115,   112,   113,   178,    55,   115,   112,   113,   180,    66,
     115,   112,   113,   221,   192,   115,   194,   195,   196,   208,
      67,   112,   113,     2,   222,   115,    45,     3,     4,    46,
      85,    56,   132,    61,     5,   133,    66,    60,    57,     6,
       7,     8,     9,    10,    11,   243,   243,   100,    12,    13,
      14,   235,   239,   244,   244,   143,    15,    16,   235,    58,
     226,    39,   236,    40,   245,   258,   144,    59,    62,   250,
      17,    63,    64,    65,   145,   146,   147,   148,   149,   150,
     246,   246,   255,   123,   124,   125,   126,   127,   260,   262,
      69,    71,    70,    72,   266,    73,   267,   144,    76,    74,
     269,    75,    77,   270,    79,   145,   146,   147,   148,   149,
     150,    78,    80,    81,    90,    84,    99,    91,   102,    66,
      89,    93,   106,   107,   108,    94,    95,   110,    98,   118,
     119,   121,   130,   120,   129,   131,   136,   139,   140,   156,
     158,   153,   162,   164,   174,   168,   169,   170,   171,   172,
     176,   177,   184,   186,   187,   188,   189,   190,   197,   199,
     202,   193,   204,   206,   207,    85,   210,   211,   212,   215,
     219,   216,   224,   225,   223,   230,   231,   232,   228,   235,
     244,   229,   233,   185,   263,   256,   214,     0,   238,     0,
       0,   157,   240,   241,     0,     0,     0,     0,   242,   253,
       0,   254,   257,   265,     0,     0,     0,    83
};

static const yytype_int16 yycheck[] =
{
      82,   110,    84,   102,   116,   172,     7,   153,   182,   164,
     119,     6,    12,    13,    14,    15,     6,   201,   141,   241,
     242,     6,   104,    16,   106,   107,     6,     8,    61,    10,
      63,    24,   155,    66,   189,   257,     6,    63,     9,   213,
     253,   254,   151,   152,    23,    12,    13,    14,    15,   131,
      23,   197,   265,     3,    36,   239,    35,    63,    51,    60,
     227,    38,    35,    63,   176,   174,    61,    62,    63,    50,
      65,    61,    62,    63,     3,    65,    61,    62,    63,    24,
      65,    61,    62,    63,   166,    65,   168,   169,   170,   188,
      35,    61,    62,     0,   203,    65,    63,     4,     5,    66,
      61,     3,    63,    63,    11,    66,    24,    48,     3,    16,
      17,    18,    19,    20,    21,    16,    16,    35,    25,    26,
      27,    24,   231,    24,    24,    35,    33,    34,    24,     3,
     212,     8,    35,    10,    35,    35,    46,     3,    63,    35,
      47,    10,    63,    63,    54,    55,    56,    57,    58,    59,
      51,    51,   247,    28,    29,    30,    31,    32,   253,   254,
      22,     3,    38,     3,   259,    63,   261,    46,    49,    63,
     265,    42,    22,   268,    63,    54,    55,    56,    57,    58,
      59,    45,     3,     3,    37,    63,    45,    39,    22,    24,
      63,    63,    23,    23,    43,    65,    63,    22,    63,     3,
      54,    24,    63,    36,    22,    63,    63,    44,    24,     8,
      23,    40,    63,    22,    24,    23,    23,    23,    63,    63,
      63,    60,    63,     3,     6,    22,    24,    23,    45,    41,
      23,    63,    35,     3,     3,    61,     3,    23,    23,    53,
      24,    52,    23,     3,    63,     3,    22,     3,    63,    24,
      24,    53,    35,   157,   256,    23,   198,    -1,    63,    -1,
      -1,   121,    63,    63,    -1,    -1,    -1,    -1,    63,    63,
      -1,    63,    63,    63,    -1,    -1,    -1,    66
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    69,     0,     4,     5,    11,    16,    17,    18,    19,
      20,    21,    25,    26,    27,    33,    34,    47,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    82,
      83,    93,    96,    97,    98,   109,     8,    10,    50,     8,
      10,    12,    13,    14,    15,    63,    66,    89,   100,    63,
       9,     3,    36,    38,    63,     3,     3,     3,     3,     3,
      48,    63,    63,    10,    63,    63,    24,    35,   101,    22,
      38,     3,     3,    63,    63,    42,    49,    22,    45,    63,
       3,     3,    63,    89,    63,    61,    63,    66,    87,    63,
      37,    39,   103,    63,    65,    63,    85,    91,    63,    45,
      35,   101,    22,   101,    23,    35,    23,    23,    43,    99,
      22,     6,    61,    62,    63,    65,    95,   105,     3,    54,
      36,    24,    84,    28,    29,    30,    31,    32,    88,    22,
      63,    63,    63,    66,    87,   101,    63,   101,   101,    44,
      24,   102,    95,    35,    46,    54,    55,    56,    57,    58,
      59,   108,   108,    40,   104,    95,     8,    85,    23,     7,
      60,    86,    63,    81,    22,   101,    23,    35,    23,    23,
      23,    63,    63,   103,    24,    94,    63,    60,    63,    95,
      63,    95,   105,   103,    63,    84,     3,     6,    22,    24,
      23,    81,   101,    63,   101,   101,   101,    45,    99,    41,
     106,    95,    23,   108,    35,   104,     3,     3,    87,    81,
       3,    23,    23,   105,   102,    53,    52,   110,    94,    24,
      92,    63,    95,    63,    23,     3,   101,   104,    63,    53,
       3,    22,     3,    35,    99,    24,    35,   107,    63,    95,
      63,    63,    63,    16,    24,    35,    51,    90,   111,    94,
      35,   107,   107,    63,    63,   111,    23,    63,    35,    90,
     111,    90,   111,    92,   107,    63,   111,   111,    90,   111,
     111
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
     100,   100,   100,   100,   100,   100,   100,   101,   101,   101,
     101,   101,   101,   101,   102,   102,   103,   103,   104,   104,
     105,   105,   105,   105,   105,   105,   105,   106,   106,   106,
     107,   107,   107,   108,   108,   108,   108,   108,   108,   108,
     108,   109,   110,   110,   110,   110,   110,   111,   111,   111,
     111,   111
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
       3,     1,     1,     1,     1,     5,     8,    10,     0,     7,
       1,     2,     4,     5,     5,     5,     7,     0,     3,     5,
       6,     6,     6,     8,     0,     4,     0,     3,     0,     3,
       3,     3,     3,     3,     5,     5,     7,     0,     4,     6,
       0,     3,     5,     1,     1,     1,     1,     1,     1,     1,
       2,     8,     0,     5,     4,     6,     7,     0,     4,     3,
       5,     6
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
#line 1428 "yacc_sql.tab.c"
    break;

  case 22: /* help: HELP SEMICOLON  */
#line 190 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_HELP;//"help";
    }
#line 1436 "yacc_sql.tab.c"
    break;

  case 23: /* sync: SYNC SEMICOLON  */
#line 195 "yacc_sql.y"
                   {
      CONTEXT->ssql->flag = SCF_SYNC;
    }
#line 1444 "yacc_sql.tab.c"
    break;

  case 24: /* begin: TRX_BEGIN SEMICOLON  */
#line 201 "yacc_sql.y"
                        {
      CONTEXT->ssql->flag = SCF_BEGIN;
    }
#line 1452 "yacc_sql.tab.c"
    break;

  case 25: /* commit: TRX_COMMIT SEMICOLON  */
#line 207 "yacc_sql.y"
                         {
      CONTEXT->ssql->flag = SCF_COMMIT;
    }
#line 1460 "yacc_sql.tab.c"
    break;

  case 26: /* rollback: TRX_ROLLBACK SEMICOLON  */
#line 213 "yacc_sql.y"
                           {
      CONTEXT->ssql->flag = SCF_ROLLBACK;
    }
#line 1468 "yacc_sql.tab.c"
    break;

  case 27: /* drop_table: DROP TABLE ID SEMICOLON  */
#line 219 "yacc_sql.y"
                            {
        CONTEXT->ssql->flag = SCF_DROP_TABLE;//"drop_table";
        drop_table_init(&CONTEXT->ssql->sstr.drop_table, (yyvsp[-1].string));
    }
#line 1477 "yacc_sql.tab.c"
    break;

  case 28: /* show_tables: SHOW TABLES SEMICOLON  */
#line 225 "yacc_sql.y"
                          {
      CONTEXT->ssql->flag = SCF_SHOW_TABLES;
    }
#line 1485 "yacc_sql.tab.c"
    break;

  case 29: /* desc_table: DESC ID SEMICOLON  */
#line 231 "yacc_sql.y"
                      {
      CONTEXT->ssql->flag = SCF_DESC_TABLE;
      desc_table_init(&CONTEXT->ssql->sstr.desc_table, (yyvsp[-1].string));
    }
#line 1494 "yacc_sql.tab.c"
    break;

  case 30: /* create_index: CREATE INDEX ID ON ID LBRACE ID_list RBRACE SEMICOLON  */
#line 239 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
			create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-6].string), (yyvsp[-4].string));
		}
#line 1503 "yacc_sql.tab.c"
    break;

  case 31: /* create_index: CREATE UNIQUE INDEX ID ON ID LBRACE ID_list RBRACE SEMICOLON  */
#line 244 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_CREATE_UNIQUE_INDEX;// "create_unique_index";
			create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-6].string), (yyvsp[-4].string));
    		}
#line 1512 "yacc_sql.tab.c"
    break;

  case 32: /* ID_list: ID  */
#line 251 "yacc_sql.y"
                {
			create_index_append_attribution(&CONTEXT->ssql->sstr.create_index, (yyvsp[0].string));
//    			$$ = $1;
    		}
#line 1521 "yacc_sql.tab.c"
    break;

  case 33: /* ID_list: ID COMMA ID_list  */
#line 256 "yacc_sql.y"
                {
    			create_index_append_attribution(&CONTEXT->ssql->sstr.create_index, (yyvsp[-2].string));
//			$$ = $1;
    		}
#line 1530 "yacc_sql.tab.c"
    break;

  case 34: /* drop_index: DROP INDEX ID SEMICOLON  */
#line 264 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_DROP_INDEX;//"drop_index";
			drop_index_init(&CONTEXT->ssql->sstr.drop_index, (yyvsp[-1].string));
		}
#line 1539 "yacc_sql.tab.c"
    break;

  case 35: /* create_table: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE SEMICOLON  */
#line 271 "yacc_sql.y"
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
#line 281 "yacc_sql.y"
                                   {    }
#line 1557 "yacc_sql.tab.c"
    break;

  case 38: /* attr_def: ID_get type null_def LBRACE number RBRACE  */
#line 286 "yacc_sql.y"
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
#line 294 "yacc_sql.y"
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
#line 310 "yacc_sql.y"
          { (yyval.number) = 0; }
#line 1592 "yacc_sql.tab.c"
    break;

  case 41: /* null_def: NULLABLE_T  */
#line 311 "yacc_sql.y"
                     { (yyval.number) = 1; }
#line 1598 "yacc_sql.tab.c"
    break;

  case 42: /* null_def: NOT NULL_T  */
#line 312 "yacc_sql.y"
                     { (yyval.number) = 0; }
#line 1604 "yacc_sql.tab.c"
    break;

  case 43: /* number: NUMBER  */
#line 317 "yacc_sql.y"
                       {(yyval.number) = (yyvsp[0].number);}
#line 1610 "yacc_sql.tab.c"
    break;

  case 44: /* type: INT_T  */
#line 321 "yacc_sql.y"
              { (yyval.number)=INTS; }
#line 1616 "yacc_sql.tab.c"
    break;

  case 45: /* type: STRING_T  */
#line 322 "yacc_sql.y"
                  { (yyval.number)=CHARS; }
#line 1622 "yacc_sql.tab.c"
    break;

  case 46: /* type: FLOAT_T  */
#line 323 "yacc_sql.y"
                 { (yyval.number)=FLOATS; }
#line 1628 "yacc_sql.tab.c"
    break;

  case 47: /* type: DATE_T  */
#line 324 "yacc_sql.y"
                { (yyval.number)=DATE; }
#line 1634 "yacc_sql.tab.c"
    break;

  case 48: /* type: TEXT_T  */
#line 325 "yacc_sql.y"
                { (yyval.number) = TEXTS; }
#line 1640 "yacc_sql.tab.c"
    break;

  case 49: /* agg_type: MAX  */
#line 329 "yacc_sql.y"
            { (yyval.number) = AGG_MAX; }
#line 1646 "yacc_sql.tab.c"
    break;

  case 50: /* agg_type: MIN  */
#line 330 "yacc_sql.y"
              { (yyval.number) = AGG_MIN; }
#line 1652 "yacc_sql.tab.c"
    break;

  case 51: /* agg_type: COUNT  */
#line 331 "yacc_sql.y"
                { (yyval.number) = AGG_COUNT; }
#line 1658 "yacc_sql.tab.c"
    break;

  case 52: /* agg_type: AVG  */
#line 332 "yacc_sql.y"
              { (yyval.number) = AGG_AVG; }
#line 1664 "yacc_sql.tab.c"
    break;

  case 53: /* order_type: ASC  */
#line 336 "yacc_sql.y"
            {
	(yyval.number) = ORDER_ASC; printf("I am ASC\n");}
#line 1671 "yacc_sql.tab.c"
    break;

  case 54: /* order_type: DESC  */
#line 338 "yacc_sql.y"
               {
	(yyval.number) = ORDER_DESC; printf("I am DESC\n");}
#line 1678 "yacc_sql.tab.c"
    break;

  case 55: /* ID_get: ID  */
#line 344 "yacc_sql.y"
        {
		char *temp=(yyvsp[0].string); 
		snprintf(CONTEXT->id, sizeof(CONTEXT->id), "%s", temp);
	}
#line 1687 "yacc_sql.tab.c"
    break;

  case 57: /* insert_value_list: COMMA LBRACE value value_list RBRACE insert_value_list  */
#line 353 "yacc_sql.y"
                {

    		}
#line 1695 "yacc_sql.tab.c"
    break;

  case 58: /* insert: INSERT INTO ID VALUES LBRACE value value_list RBRACE insert_value_list SEMICOLON  */
#line 359 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_INSERT;//"insert";
			inserts_init(&CONTEXT->ssql->sstr.insertion, (yyvsp[-7].string), CONTEXT->values, CONTEXT->value_length);

      			//临时变量清零
      			CONTEXT->value_length=0;
    		}
#line 1707 "yacc_sql.tab.c"
    break;

  case 60: /* value_list: COMMA value value_list  */
#line 369 "yacc_sql.y"
                              { 
  		// CONTEXT->values[CONTEXT->value_length++] = *$2;
	  }
#line 1715 "yacc_sql.tab.c"
    break;

  case 61: /* value: NUMBER  */
#line 375 "yacc_sql.y"
                {
  			value_init_integer(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].number));
		}
#line 1723 "yacc_sql.tab.c"
    break;

  case 62: /* value: FLOAT  */
#line 379 "yacc_sql.y"
                {
  			value_init_float(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].floats));
		}
#line 1731 "yacc_sql.tab.c"
    break;

  case 63: /* value: SSS  */
#line 383 "yacc_sql.y"
                {
			(yyvsp[0].string) = substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
  			value_init_string(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].string));
		}
#line 1740 "yacc_sql.tab.c"
    break;

  case 64: /* value: NULL_T  */
#line 388 "yacc_sql.y"
                {
    			value_init_null(&CONTEXT->values[CONTEXT->value_length++]);
    		}
#line 1748 "yacc_sql.tab.c"
    break;

  case 65: /* delete: DELETE FROM ID where SEMICOLON  */
#line 395 "yacc_sql.y"
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
#line 406 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_UPDATE;//"update";
			Value *value = &CONTEXT->values[0];
			updates_init(&CONTEXT->ssql->sstr.update, (yyvsp[-6].string), (yyvsp[-4].string), value, 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;
		}
#line 1772 "yacc_sql.tab.c"
    break;

  case 67: /* select: SELECT select_attr FROM ID join_list rel_list where group_by order SEMICOLON  */
#line 416 "yacc_sql.y"
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
#line 1791 "yacc_sql.tab.c"
    break;

  case 69: /* join_list: INNER JOIN ID ON condition condition_list join_list  */
#line 442 "yacc_sql.y"
                {
			selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-4].string));
		}
#line 1799 "yacc_sql.tab.c"
    break;

  case 70: /* select_attr: STAR  */
#line 449 "yacc_sql.y"
                {
			RelAttr attr;
			relation_attr_init(&attr, NULL, "*");
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 1809 "yacc_sql.tab.c"
    break;

  case 71: /* select_attr: ID attr_list  */
#line 455 "yacc_sql.y"
                {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 1819 "yacc_sql.tab.c"
    break;

  case 72: /* select_attr: ID DOT ID attr_list  */
#line 461 "yacc_sql.y"
                {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 1829 "yacc_sql.tab.c"
    break;

  case 73: /* select_attr: agg_type LBRACE STAR RBRACE attr_list  */
#line 467 "yacc_sql.y"
                {
			AggDesc agg_desc;
			agg_desc_init_string(&agg_desc, (yyvsp[-4].number), AGG_STAR, NULL, "*");
			selects_append_agg(&CONTEXT->ssql->sstr.selection, &agg_desc);
		}
#line 1839 "yacc_sql.tab.c"
    break;

  case 74: /* select_attr: agg_type LBRACE number RBRACE attr_list  */
#line 473 "yacc_sql.y"
                {
			AggDesc agg_desc;
			agg_desc_init_number(&agg_desc, (yyvsp[-4].number), AGG_NUMBER, (yyvsp[-2].number));
			selects_append_agg(&CONTEXT->ssql->sstr.selection, &agg_desc);
		}
#line 1849 "yacc_sql.tab.c"
    break;

  case 75: /* select_attr: agg_type LBRACE ID RBRACE attr_list  */
#line 479 "yacc_sql.y"
                {
			AggDesc agg_desc;
			agg_desc_init_string(&agg_desc, (yyvsp[-4].number), AGG_FIELD, NULL, (yyvsp[-2].string));
			selects_append_agg(&CONTEXT->ssql->sstr.selection, &agg_desc);
		}
#line 1859 "yacc_sql.tab.c"
    break;

  case 76: /* select_attr: agg_type LBRACE ID DOT ID RBRACE attr_list  */
#line 485 "yacc_sql.y"
                {
			AggDesc agg_desc;
			agg_desc_init_string(&agg_desc, (yyvsp[-6].number), AGG_FIELD, (yyvsp[-4].string), (yyvsp[-2].string));
			selects_append_agg(&CONTEXT->ssql->sstr.selection, &agg_desc);
		}
#line 1869 "yacc_sql.tab.c"
    break;

  case 78: /* attr_list: COMMA ID attr_list  */
#line 494 "yacc_sql.y"
                         {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
     	  // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length].relation_name = NULL;
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length++].attribute_name=$2;
      }
#line 1881 "yacc_sql.tab.c"
    break;

  case 79: /* attr_list: COMMA ID DOT ID attr_list  */
#line 501 "yacc_sql.y"
                                {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length].attribute_name=$4;
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length++].relation_name=$2;
  	  }
#line 1893 "yacc_sql.tab.c"
    break;

  case 80: /* attr_list: COMMA agg_type LBRACE STAR RBRACE attr_list  */
#line 509 "yacc_sql.y"
                {
			AggDesc agg_desc;
			agg_desc_init_string(&agg_desc, (yyvsp[-4].number), AGG_STAR, NULL, "*");
			selects_append_agg(&CONTEXT->ssql->sstr.selection, &agg_desc);
		}
#line 1903 "yacc_sql.tab.c"
    break;

  case 81: /* attr_list: COMMA agg_type LBRACE number RBRACE attr_list  */
#line 515 "yacc_sql.y"
                {
			AggDesc agg_desc;
			agg_desc_init_number(&agg_desc, (yyvsp[-4].number), AGG_NUMBER, (yyvsp[-2].number));
			selects_append_agg(&CONTEXT->ssql->sstr.selection, &agg_desc);
		}
#line 1913 "yacc_sql.tab.c"
    break;

  case 82: /* attr_list: COMMA agg_type LBRACE ID RBRACE attr_list  */
#line 521 "yacc_sql.y"
                {
			AggDesc agg_desc;
			agg_desc_init_string(&agg_desc, (yyvsp[-4].number), AGG_FIELD, NULL, (yyvsp[-2].string));
			selects_append_agg(&CONTEXT->ssql->sstr.selection, &agg_desc);
		}
#line 1923 "yacc_sql.tab.c"
    break;

  case 83: /* attr_list: COMMA agg_type LBRACE ID DOT ID RBRACE attr_list  */
#line 527 "yacc_sql.y"
                {
			AggDesc agg_desc;
			agg_desc_init_string(&agg_desc, (yyvsp[-6].number), AGG_FIELD, (yyvsp[-4].string), (yyvsp[-2].string));
			selects_append_agg(&CONTEXT->ssql->sstr.selection, &agg_desc);
		}
#line 1933 "yacc_sql.tab.c"
    break;

  case 85: /* rel_list: COMMA ID join_list rel_list  */
#line 537 "yacc_sql.y"
                {
			selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-2].string));
		}
#line 1941 "yacc_sql.tab.c"
    break;

  case 87: /* where: WHERE condition condition_list  */
#line 544 "yacc_sql.y"
                {
			// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
		}
#line 1949 "yacc_sql.tab.c"
    break;

  case 89: /* condition_list: AND condition condition_list  */
#line 551 "yacc_sql.y"
                {
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
		}
#line 1957 "yacc_sql.tab.c"
    break;

  case 90: /* condition: ID comOp value  */
#line 557 "yacc_sql.y"
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
#line 1982 "yacc_sql.tab.c"
    break;

  case 91: /* condition: value comOp value  */
#line 578 "yacc_sql.y"
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
#line 2006 "yacc_sql.tab.c"
    break;

  case 92: /* condition: ID comOp ID  */
#line 598 "yacc_sql.y"
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
#line 2030 "yacc_sql.tab.c"
    break;

  case 93: /* condition: value comOp ID  */
#line 618 "yacc_sql.y"
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
#line 2056 "yacc_sql.tab.c"
    break;

  case 94: /* condition: ID DOT ID comOp value  */
#line 640 "yacc_sql.y"
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
#line 2081 "yacc_sql.tab.c"
    break;

  case 95: /* condition: value comOp ID DOT ID  */
#line 661 "yacc_sql.y"
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
#line 2106 "yacc_sql.tab.c"
    break;

  case 96: /* condition: ID DOT ID comOp ID DOT ID  */
#line 682 "yacc_sql.y"
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
#line 2129 "yacc_sql.tab.c"
    break;

  case 98: /* group_by: GROUP BY ID group_by_attr_list  */
#line 704 "yacc_sql.y"
                                         {
		RelAttr attr;
		relation_attr_init(&attr, NULL, (yyvsp[-1].string));
		selects_append_group_by_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 2139 "yacc_sql.tab.c"
    break;

  case 99: /* group_by: GROUP BY ID DOT ID group_by_attr_list  */
#line 709 "yacc_sql.y"
                                                {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
		selects_append_group_by_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 2149 "yacc_sql.tab.c"
    break;

  case 101: /* group_by_attr_list: COMMA ID group_by_attr_list  */
#line 718 "yacc_sql.y"
                                      {
		RelAttr attr;
		relation_attr_init(&attr, NULL, (yyvsp[-1].string));
		selects_append_group_by_attribute(&CONTEXT->ssql->sstr.selection, &attr);
    }
#line 2159 "yacc_sql.tab.c"
    break;

  case 102: /* group_by_attr_list: COMMA ID DOT ID group_by_attr_list  */
#line 723 "yacc_sql.y"
                                         {
		RelAttr attr;
		relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
		selects_append_group_by_attribute(&CONTEXT->ssql->sstr.selection, &attr);
  	}
#line 2169 "yacc_sql.tab.c"
    break;

  case 103: /* comOp: EQ  */
#line 731 "yacc_sql.y"
       { CONTEXT->comp = EQUAL_TO; }
#line 2175 "yacc_sql.tab.c"
    break;

  case 104: /* comOp: LT  */
#line 732 "yacc_sql.y"
         { CONTEXT->comp = LESS_THAN; }
#line 2181 "yacc_sql.tab.c"
    break;

  case 105: /* comOp: GT  */
#line 733 "yacc_sql.y"
         { CONTEXT->comp = GREAT_THAN; }
#line 2187 "yacc_sql.tab.c"
    break;

  case 106: /* comOp: LE  */
#line 734 "yacc_sql.y"
         { CONTEXT->comp = LESS_EQUAL; }
#line 2193 "yacc_sql.tab.c"
    break;

  case 107: /* comOp: GE  */
#line 735 "yacc_sql.y"
         { CONTEXT->comp = GREAT_EQUAL; }
#line 2199 "yacc_sql.tab.c"
    break;

  case 108: /* comOp: NE  */
#line 736 "yacc_sql.y"
         { CONTEXT->comp = NOT_EQUAL; }
#line 2205 "yacc_sql.tab.c"
    break;

  case 109: /* comOp: IS  */
#line 737 "yacc_sql.y"
         { CONTEXT->comp = IS_OP;}
#line 2211 "yacc_sql.tab.c"
    break;

  case 110: /* comOp: IS NOT  */
#line 738 "yacc_sql.y"
             { CONTEXT->comp = IS_NOT_OP;}
#line 2217 "yacc_sql.tab.c"
    break;

  case 111: /* load_data: LOAD DATA INFILE SSS INTO TABLE ID SEMICOLON  */
#line 743 "yacc_sql.y"
                {
		  	CONTEXT->ssql->flag = SCF_LOAD_DATA;
			load_data_init(&CONTEXT->ssql->sstr.load_data, (yyvsp[-1].string), (yyvsp[-4].string));
		}
#line 2226 "yacc_sql.tab.c"
    break;

  case 113: /* order: ORDER BY ID order_type order_attrs  */
#line 752 "yacc_sql.y"
                {
			Order order;
			order_info_init(&order, (yyvsp[-1].number), NULL,(yyvsp[-2].string));
			selects_append_order(&CONTEXT->ssql->sstr.selection, &order);
		}
#line 2236 "yacc_sql.tab.c"
    break;

  case 114: /* order: ORDER BY ID order_attrs  */
#line 758 "yacc_sql.y"
                {
			Order order;
			order_info_init(&order, ASC, NULL, (yyvsp[-1].string));
			selects_append_order(&CONTEXT->ssql->sstr.selection, &order);
		}
#line 2246 "yacc_sql.tab.c"
    break;

  case 115: /* order: ORDER BY ID DOT ID order_attrs  */
#line 764 "yacc_sql.y"
                {
			Order order;
			order_info_init(&order, ASC, (yyvsp[-3].string), (yyvsp[-1].string));
			selects_append_order(&CONTEXT->ssql->sstr.selection, &order);
		}
#line 2256 "yacc_sql.tab.c"
    break;

  case 116: /* order: ORDER BY ID DOT ID order_type order_attrs  */
#line 770 "yacc_sql.y"
                {
			Order order;
			order_info_init(&order, (yyvsp[-1].number), (yyvsp[-4].string), (yyvsp[-2].string));
			selects_append_order(&CONTEXT->ssql->sstr.selection, &order);
		}
#line 2266 "yacc_sql.tab.c"
    break;

  case 118: /* order_attrs: COMMA ID order_type order_attrs  */
#line 779 "yacc_sql.y"
                {
			Order order;
			printf("odered_type : %d\n", CONTEXT->order_type);
			order_info_init(&order, (yyvsp[-1].number), NULL,(yyvsp[-2].string));
			selects_append_order(&CONTEXT->ssql->sstr.selection, &order);
		}
#line 2277 "yacc_sql.tab.c"
    break;

  case 119: /* order_attrs: COMMA ID order_attrs  */
#line 786 "yacc_sql.y"
                {
			Order order;
			order_info_init(&order, ASC, NULL, (yyvsp[-1].string));
			selects_append_order(&CONTEXT->ssql->sstr.selection, &order);
		}
#line 2287 "yacc_sql.tab.c"
    break;

  case 120: /* order_attrs: COMMA ID DOT ID order_attrs  */
#line 792 "yacc_sql.y"
                {
			Order order;
			order_info_init(&order, ASC, (yyvsp[-3].string), (yyvsp[-1].string));
			selects_append_order(&CONTEXT->ssql->sstr.selection, &order);
		}
#line 2297 "yacc_sql.tab.c"
    break;

  case 121: /* order_attrs: COMMA ID DOT ID order_type order_attrs  */
#line 797 "yacc_sql.y"
                                                {
			Order order;
			order_info_init(&order, (yyvsp[-1].number), (yyvsp[-4].string),(yyvsp[-2].string));
			selects_append_order(&CONTEXT->ssql->sstr.selection, &order);
		}
#line 2307 "yacc_sql.tab.c"
    break;


#line 2311 "yacc_sql.tab.c"

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

#line 804 "yacc_sql.y"

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
