/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "src/parsing/parser.y" /* yacc.c:339  */

#include <stdio.h>
#include "parser.tab.h"

#include <ast.h>

int yyerror(char *s);
int yylex();

//#define YYDEBUG 1


extern struct ast_node *ast_head;

int linenum = 1;

#line 83 "src/parsing/parser.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "parser.tab.h".  */
#ifndef YY_YY_SRC_PARSING_PARSER_TAB_H_INCLUDED
# define YY_YY_SRC_PARSING_PARSER_TAB_H_INCLUDED
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
    t_IDENTIFIER = 258,
    t_VALUE = 259,
    t_CORE = 260,
    t_MAIN = 261,
    t_SIGNAL = 262,
    t_SOURCE = 263,
    t_MATCH = 264,
    t_SIGEN = 265,
    t_SIGDIS = 266,
    t_LB = 267,
    t_RB = 268,
    t_SC = 269,
    t_COLON = 270,
    t_I32 = 271,
    t_ASSIGNMENT = 272,
    t_IF = 273,
    t_ELSE = 274,
    t_WHILE = 275,
    t_LPAR = 276,
    t_RPAR = 277,
    t_STREAM = 278,
    t_PIPELINE = 279,
    t_EXPOSE = 280,
    t_SHUNT = 281,
    t_NULL = 282,
    t_LINKS = 283,
    t_COMMA = 284,
    t_PERIOD = 285,
    t_PLUS = 286,
    t_TIMES = 287,
    t_MINUS = 288,
    t_DIVIDE = 289,
    t_AND = 290,
    t_OR = 291,
    t_LESS = 292,
    t_LESSEQUAL = 293,
    t_GREATER = 294,
    t_GREATEREQUAL = 295,
    t_EQUALS = 296,
    t_NOTEQUALS = 297,
    t_TRIGGER = 298,
    t_NOP = 299,
    t_PRINT = 300,
    t_PRINTSTRING = 301,
    t_HALT = 302,
    t_FIRE = 303
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 20 "src/parsing/parser.y" /* yacc.c:355  */

        char *var;
        int val;
        struct ast_node *node;
        int op_type;

#line 179 "src/parsing/parser.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_SRC_PARSING_PARSER_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 196 "src/parsing/parser.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

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

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
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
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
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
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  6
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   156

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  49
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  37
/* YYNRULES -- Number of rules.  */
#define YYNRULES  83
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  181

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   303

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
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
      45,    46,    47,    48
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   120,   120,   123,   123,   125,   127,   127,   129,   130,
     131,   132,   134,   144,   150,   151,   154,   157,   158,   160,
     161,   162,   163,   164,   165,   166,   167,   168,   169,   170,
     171,   172,   173,   174,   176,   177,   179,   181,   183,   185,
     187,   189,   195,   205,   212,   218,   219,   222,   223,   224,
     226,   229,   236,   238,   238,   240,   242,   244,   247,   248,
     255,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   268,   269,   270,   271,   275,   283,   290,   291,
     292,   293,   296,   297
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "t_IDENTIFIER", "t_VALUE", "t_CORE",
  "t_MAIN", "t_SIGNAL", "t_SOURCE", "t_MATCH", "t_SIGEN", "t_SIGDIS",
  "t_LB", "t_RB", "t_SC", "t_COLON", "t_I32", "t_ASSIGNMENT", "t_IF",
  "t_ELSE", "t_WHILE", "t_LPAR", "t_RPAR", "t_STREAM", "t_PIPELINE",
  "t_EXPOSE", "t_SHUNT", "t_NULL", "t_LINKS", "t_COMMA", "t_PERIOD",
  "t_PLUS", "t_TIMES", "t_MINUS", "t_DIVIDE", "t_AND", "t_OR", "t_LESS",
  "t_LESSEQUAL", "t_GREATER", "t_GREATEREQUAL", "t_EQUALS", "t_NOTEQUALS",
  "t_TRIGGER", "t_NOP", "t_PRINT", "t_PRINTSTRING", "t_HALT", "t_FIRE",
  "$accept", "prog", "cores", "core", "core_body", "core_construct",
  "stream_function", "func_header", "arg_list", "arg", "construct_body",
  "statement", "print_statement", "print_string_statement",
  "trigger_statement", "halt_statement", "fire_statement", "nop_statement",
  "if_statement", "while_statement", "pipeline_statement", "pipeline_body",
  "pipeline_exp", "expose_stmt", "link_stmt", "match_statement",
  "match_body", "match_case", "var_decl", "var_assign", "expression",
  "operator", "terminal", "stream_push", "stream_pull", "call_arg_list",
  "pull_arg_list", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303
};
# endif

#define YYPACT_NINF -113

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-113)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      -3,    14,    30,  -113,    -3,    17,  -113,  -113,    29,    22,
      26,    38,    40,    31,    29,  -113,  -113,     3,     3,    41,
      33,    28,  -113,  -113,     5,    49,    44,    45,    39,    54,
      58,    73,    63,     7,    75,    65,    66,    69,     3,  -113,
    -113,  -113,  -113,  -113,  -113,  -113,  -113,  -113,  -113,  -113,
    -113,    71,    70,  -113,    72,    40,    21,    12,    74,  -113,
    -113,    21,    21,    77,    76,  -113,    78,    79,    80,  -113,
    -113,  -113,  -113,  -113,  -113,    84,    81,    62,    83,    67,
    -113,    21,    82,    32,  -113,    85,    86,    87,    95,    88,
      89,    15,  -113,  -113,  -113,  -113,  -113,  -113,    72,     3,
      96,    90,  -113,  -113,  -113,  -113,  -113,  -113,  -113,  -113,
    -113,  -113,  -113,  -113,  -113,    21,    12,    12,    91,    92,
      93,    95,   101,   104,    97,    98,   105,    15,  -113,  -113,
    -113,  -113,   106,   102,  -113,  -113,  -113,  -113,    99,   110,
      94,  -113,     3,     3,   114,   100,   112,  -113,  -113,   125,
    -113,     3,  -113,   116,   118,   107,   129,  -113,   108,   117,
     121,    18,   122,   135,   126,    12,  -113,  -113,  -113,   130,
    -113,   111,  -113,  -113,     3,   140,   131,   132,   133,  -113,
    -113
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     2,     3,     0,     1,     4,     0,     0,
       0,     0,     0,     0,     6,    11,    10,     0,     0,     0,
       0,     0,     5,     7,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    17,    30,
      31,    27,    32,    33,    29,    24,    26,    25,    21,    22,
      23,     0,     0,    56,     0,     0,     0,     0,     0,    19,
      20,     0,     0,     0,     0,    40,     0,     0,     0,    38,
      39,     8,    18,    28,     9,     0,     0,    14,     0,    73,
      72,     0,     0,    58,    75,    79,    78,     0,     0,     0,
       0,     0,    37,    35,    34,    36,    16,    13,     0,     0,
       0,     0,    57,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,     0,     0,     0,     0,     0,
       0,    53,     0,     0,     0,     0,     0,    45,    48,    49,
      47,    15,     0,     0,    74,    59,    81,    80,     0,     0,
       0,    54,     0,     0,     0,     0,     0,    46,    12,     0,
      76,     0,    52,     0,     0,     0,     0,    44,    82,     0,
       0,     0,     0,     0,     0,     0,    77,    55,    41,     0,
      43,     0,    50,    83,     0,     0,     0,     0,     0,    51,
      42
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -113,  -113,   141,  -113,   134,  -113,  -113,    50,     2,  -113,
     -18,  -113,  -113,  -113,  -113,  -113,  -113,  -113,  -113,  -113,
    -113,   -23,  -113,  -113,  -113,  -113,    34,  -113,    -7,  -113,
     -53,  -113,  -113,  -113,  -113,  -112,  -113
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,     4,    13,    14,    15,    21,    76,    77,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,   126,   127,   128,   129,    48,   120,   121,    49,    50,
      86,   115,    83,    51,    84,    87,   159
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      52,    16,     1,    82,   136,   137,    24,    16,    89,    90,
      66,    67,    25,    26,    27,    79,    80,     5,   124,    11,
      72,    28,    56,    29,    79,    80,    57,    30,   101,     8,
       6,    11,   168,    81,    17,     9,    10,   169,    18,    85,
     125,    19,    81,    20,    22,    11,    31,    32,    33,    34,
      35,    36,    12,   173,    54,    53,    55,    58,    59,    60,
      61,    63,   135,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,    62,    64,    65,    68,    69,
      70,   132,    71,    74,   130,    73,    88,    96,    75,    91,
      92,    98,    93,    94,    95,    99,   102,   100,   119,   133,
     131,   145,   150,    97,   147,    78,   140,   139,   152,   118,
     122,   123,   134,   142,   116,   117,   143,   155,   146,   148,
     130,   138,   151,   149,   153,   154,   157,   144,   158,   161,
     156,   162,   164,   160,   167,   163,   170,   165,   171,   166,
     172,   175,   174,   177,   178,     7,   179,   180,    23,     0,
       0,     0,     0,     0,     0,   141,   176
};

static const yytype_int16 yycheck[] =
{
      18,     8,     5,    56,   116,   117,     3,    14,    61,    62,
       3,     4,     9,    10,    11,     3,     4,     3,     3,    16,
      38,    18,    17,    20,     3,     4,    21,    24,    81,    12,
       0,    16,    14,    21,    12,     6,     7,    19,    12,    27,
      25,     3,    21,     3,    13,    16,    43,    44,    45,    46,
      47,    48,    23,   165,    21,    14,    28,     8,    14,    14,
      21,     3,   115,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    21,     3,    14,     3,    14,
      14,    99,    13,    13,    91,    14,    12,     3,    16,    12,
      14,    29,    14,    14,    14,    12,    14,    30,     3,     3,
      98,     3,     3,    22,   127,    55,    13,    15,    14,    22,
      22,    22,    22,    12,    29,    29,    12,     3,    13,    13,
     127,    30,    12,    21,   142,   143,    14,    30,     3,    13,
      30,    13,     3,   151,    13,    28,    14,    29,     3,    22,
      14,    30,    12,     3,    13,     4,    14,    14,    14,    -1,
      -1,    -1,    -1,    -1,    -1,   121,   174
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     5,    50,    51,    52,     3,     0,    51,    12,     6,
       7,    16,    23,    53,    54,    55,    77,    12,    12,     3,
       3,    56,    13,    53,     3,     9,    10,    11,    18,    20,
      24,    43,    44,    45,    46,    47,    48,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    74,    77,
      78,    82,    59,    14,    21,    28,    17,    21,     8,    14,
      14,    21,    21,     3,     3,    14,     3,     4,     3,    14,
      14,    13,    59,    14,    13,    16,    57,    58,    56,     3,
       4,    21,    79,    81,    83,    27,    79,    84,    12,    79,
      79,    12,    14,    14,    14,    14,     3,    22,    29,    12,
      30,    79,    14,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    80,    29,    29,    22,     3,
      75,    76,    22,    22,     3,    25,    70,    71,    72,    73,
      77,    57,    59,     3,    22,    79,    84,    84,    30,    15,
      13,    75,    12,    12,    30,     3,    13,    70,    13,    21,
       3,    12,    14,    59,    59,     3,    30,    14,     3,    85,
      59,    13,    13,    28,     3,    29,    22,    13,    14,    19,
      14,     3,    14,    84,    12,    30,    59,     3,    13,    14,
      14
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    49,    50,    51,    51,    52,    53,    53,    54,    54,
      54,    54,    55,    56,    57,    57,    58,    59,    59,    60,
      60,    60,    60,    60,    60,    60,    60,    60,    60,    60,
      60,    60,    60,    60,    61,    61,    62,    63,    64,    65,
      66,    67,    67,    68,    69,    70,    70,    71,    71,    71,
      72,    73,    74,    75,    75,    76,    77,    78,    79,    79,
      80,    80,    80,    80,    80,    80,    80,    80,    80,    80,
      80,    80,    81,    81,    81,    81,    82,    83,    84,    84,
      84,    84,    85,    85
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     2,     5,     1,     2,     4,     4,
       1,     1,     7,     4,     1,     3,     2,     1,     2,     2,
       2,     1,     1,     1,     1,     1,     1,     1,     2,     1,
       1,     1,     1,     1,     3,     3,     3,     3,     2,     2,
       2,     8,    12,     8,     6,     1,     2,     1,     1,     1,
       5,     8,     6,     1,     2,     5,     3,     4,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     1,     6,     6,     1,     1,
       3,     3,     1,     3
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
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
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
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
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
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
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
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
            /* Fall through.  */
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

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
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
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

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
      int yyn = yypact[*yyssp];
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
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
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
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
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
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
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
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

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
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
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
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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
      yychar = yylex ();
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
| yyreduce -- Do a reduction.  |
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
        case 2:
#line 120 "src/parsing/parser.y" /* yacc.c:1646  */
    { ast_head = (yyval.node) = new_ast_program((yyvsp[0].node)); }
#line 1399 "src/parsing/parser.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 123 "src/parsing/parser.y" /* yacc.c:1646  */
    {(yyval.node) = (yyvsp[0].node);}
#line 1405 "src/parsing/parser.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 123 "src/parsing/parser.y" /* yacc.c:1646  */
    { (yyvsp[-1].node)->side = (yyvsp[0].node); (yyval.node)=(yyvsp[-1].node); }
#line 1411 "src/parsing/parser.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 125 "src/parsing/parser.y" /* yacc.c:1646  */
    { (yyval.node) = new_ast_core((yyvsp[-3].var),(yyvsp[-1].node)); }
#line 1417 "src/parsing/parser.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 127 "src/parsing/parser.y" /* yacc.c:1646  */
    { (yyval.node)=(yyvsp[0].node); }
#line 1423 "src/parsing/parser.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 127 "src/parsing/parser.y" /* yacc.c:1646  */
    { (yyvsp[-1].node)->side = (yyvsp[0].node); (yyval.node) = (yyvsp[-1].node); }
#line 1429 "src/parsing/parser.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 129 "src/parsing/parser.y" /* yacc.c:1646  */
    { (yyval.node)=new_ast_main((yyvsp[-1].node)); }
#line 1435 "src/parsing/parser.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 130 "src/parsing/parser.y" /* yacc.c:1646  */
    { (yyval.node)=new_ast_signal((yyvsp[-1].node)); }
#line 1441 "src/parsing/parser.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 131 "src/parsing/parser.y" /* yacc.c:1646  */
    {(yyval.node) = (yyvsp[0].node); }
#line 1447 "src/parsing/parser.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 132 "src/parsing/parser.y" /* yacc.c:1646  */
    {(yyval.node) = (yyvsp[0].node);}
#line 1453 "src/parsing/parser.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 135 "src/parsing/parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = new_ast_stream((yyvsp[-5].node)->name,(yyvsp[-3].node)->name);
                    (yyval.node)->down = (yyvsp[-1].node);

                    (yyval.node)->stream_in = (yyvsp[-5].node);
                    (yyval.node)->stream_out = (yyvsp[-3].node);
                  }
#line 1465 "src/parsing/parser.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 145 "src/parsing/parser.y" /* yacc.c:1646  */
    { 
                (yyval.node)=new_ast_func_header((yyvsp[-3].var));
                (yyval.node)->down = (yyvsp[-1].node); 
              }
#line 1474 "src/parsing/parser.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 150 "src/parsing/parser.y" /* yacc.c:1646  */
    { (yyval.node)=(yyvsp[0].node); }
#line 1480 "src/parsing/parser.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 151 "src/parsing/parser.y" /* yacc.c:1646  */
    { (yyvsp[-2].node)->side=(yyvsp[0].node); (yyval.node)=(yyvsp[-2].node); }
#line 1486 "src/parsing/parser.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 154 "src/parsing/parser.y" /* yacc.c:1646  */
    { (yyval.node)=new_ast_i32var_decl((yyvsp[0].var)); }
#line 1492 "src/parsing/parser.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 157 "src/parsing/parser.y" /* yacc.c:1646  */
    { (yyval.node)=(yyvsp[0].node); }
#line 1498 "src/parsing/parser.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 158 "src/parsing/parser.y" /* yacc.c:1646  */
    { (yyvsp[-1].node)->side=(yyvsp[0].node); (yyval.node)=(yyvsp[-1].node); }
#line 1504 "src/parsing/parser.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 160 "src/parsing/parser.y" /* yacc.c:1646  */
    { (yyval.node)=new_ast_sigen(); }
#line 1510 "src/parsing/parser.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 161 "src/parsing/parser.y" /* yacc.c:1646  */
    { (yyval.node)=new_ast_sigdis(); }
#line 1516 "src/parsing/parser.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 162 "src/parsing/parser.y" /* yacc.c:1646  */
    { (yyval.node)=(yyvsp[0].node); }
#line 1522 "src/parsing/parser.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 163 "src/parsing/parser.y" /* yacc.c:1646  */
    { (yyval.node)=(yyvsp[0].node); }
#line 1528 "src/parsing/parser.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 164 "src/parsing/parser.y" /* yacc.c:1646  */
    { (yyval.node)=(yyvsp[0].node); }
#line 1534 "src/parsing/parser.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 165 "src/parsing/parser.y" /* yacc.c:1646  */
    { (yyval.node)=(yyvsp[0].node); }
#line 1540 "src/parsing/parser.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 166 "src/parsing/parser.y" /* yacc.c:1646  */
    { (yyval.node)=(yyvsp[0].node); }
#line 1546 "src/parsing/parser.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 167 "src/parsing/parser.y" /* yacc.c:1646  */
    { (yyval.node)=(yyvsp[0].node); }
#line 1552 "src/parsing/parser.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 168 "src/parsing/parser.y" /* yacc.c:1646  */
    { (yyval.node)=(yyvsp[0].node); }
#line 1558 "src/parsing/parser.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 169 "src/parsing/parser.y" /* yacc.c:1646  */
    { (yyval.node)=(yyvsp[-1].node); }
#line 1564 "src/parsing/parser.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 170 "src/parsing/parser.y" /* yacc.c:1646  */
    { (yyval.node)=(yyvsp[0].node); }
#line 1570 "src/parsing/parser.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 171 "src/parsing/parser.y" /* yacc.c:1646  */
    { (yyval.node)=(yyvsp[0].node); }
#line 1576 "src/parsing/parser.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 172 "src/parsing/parser.y" /* yacc.c:1646  */
    { (yyval.node)=(yyvsp[0].node); }
#line 1582 "src/parsing/parser.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 173 "src/parsing/parser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 1588 "src/parsing/parser.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 174 "src/parsing/parser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 1594 "src/parsing/parser.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 176 "src/parsing/parser.y" /* yacc.c:1646  */
    { (yyval.node)=new_ast_print((yyvsp[-1].val)); }
#line 1600 "src/parsing/parser.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 177 "src/parsing/parser.y" /* yacc.c:1646  */
    { (yyval.node)=new_ast_print_identifier((yyvsp[-1].var)); }
#line 1606 "src/parsing/parser.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 179 "src/parsing/parser.y" /* yacc.c:1646  */
    { (yyval.node)=new_ast_printstring((yyvsp[-1].var)); }
#line 1612 "src/parsing/parser.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 181 "src/parsing/parser.y" /* yacc.c:1646  */
    { (yyval.node)=new_ast_trigger((yyvsp[-1].var)); }
#line 1618 "src/parsing/parser.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 183 "src/parsing/parser.y" /* yacc.c:1646  */
    { (yyval.node)=new_ast_halt(); }
#line 1624 "src/parsing/parser.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 185 "src/parsing/parser.y" /* yacc.c:1646  */
    { (yyval.node)=new_ast_fire(); }
#line 1630 "src/parsing/parser.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 187 "src/parsing/parser.y" /* yacc.c:1646  */
    { (yyval.node)=new_ast_nop(); }
#line 1636 "src/parsing/parser.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 190 "src/parsing/parser.y" /* yacc.c:1646  */
    { 
                (yyval.node) = new_ast_if((struct ast_node *)0); 
                (yyval.node)->condition = (yyvsp[-5].node);
                (yyval.node)->down = (yyvsp[-2].node); 
              }
#line 1646 "src/parsing/parser.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 196 "src/parsing/parser.y" /* yacc.c:1646  */
    {
                struct ast_node *tmp = new_ast_else((yyvsp[-2].node));

                (yyval.node) = new_ast_if(tmp); 
                (yyval.node)->condition = (yyvsp[-9].node);
                (yyval.node)->down = (yyvsp[-6].node);
              }
#line 1658 "src/parsing/parser.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 206 "src/parsing/parser.y" /* yacc.c:1646  */
    {
                    (yyval.node) = new_ast_while(); 
                    (yyval.node)->condition = (yyvsp[-5].node);
                    (yyval.node)->down = (yyvsp[-2].node);
                  }
#line 1668 "src/parsing/parser.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 213 "src/parsing/parser.y" /* yacc.c:1646  */
    { 
                      (yyval.node)=new_ast_pipeline((yyvsp[-4].var));
                      (yyval.node)->down = (yyvsp[-2].node); 
                    }
#line 1677 "src/parsing/parser.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 218 "src/parsing/parser.y" /* yacc.c:1646  */
    { (yyval.node)=(yyvsp[0].node); }
#line 1683 "src/parsing/parser.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 219 "src/parsing/parser.y" /* yacc.c:1646  */
    { (yyvsp[-1].node)->side=(yyvsp[0].node); (yyval.node)=(yyvsp[-1].node); }
#line 1689 "src/parsing/parser.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 222 "src/parsing/parser.y" /* yacc.c:1646  */
    { (yyval.node)=(yyvsp[0].node); }
#line 1695 "src/parsing/parser.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 223 "src/parsing/parser.y" /* yacc.c:1646  */
    { (yyval.node)=(yyvsp[0].node); }
#line 1701 "src/parsing/parser.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 224 "src/parsing/parser.y" /* yacc.c:1646  */
    { (yyval.node)=(yyvsp[0].node); }
#line 1707 "src/parsing/parser.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 226 "src/parsing/parser.y" /* yacc.c:1646  */
    { (yyval.node) = new_ast_expose((yyvsp[-3].var),(yyvsp[-1].var)); }
#line 1713 "src/parsing/parser.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 230 "src/parsing/parser.y" /* yacc.c:1646  */
    {
            (yyval.node) = new_ast_link((yyvsp[-7].var),(yyvsp[-5].var));
            (yyval.node)->link_port = new_ast_linkport((yyvsp[-3].var),(yyvsp[-1].var));
          }
#line 1722 "src/parsing/parser.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 236 "src/parsing/parser.y" /* yacc.c:1646  */
    { (yyval.node)=new_ast_match_source((yyvsp[-2].node)); }
#line 1728 "src/parsing/parser.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 238 "src/parsing/parser.y" /* yacc.c:1646  */
    { (yyval.node)=(yyvsp[0].node); }
#line 1734 "src/parsing/parser.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 238 "src/parsing/parser.y" /* yacc.c:1646  */
    { (yyvsp[-1].node)->side=(yyvsp[0].node); (yyval.node)=(yyvsp[-1].node); }
#line 1740 "src/parsing/parser.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 240 "src/parsing/parser.y" /* yacc.c:1646  */
    { (yyval.node)=new_ast_match_case_identifier((yyvsp[-4].var),(yyvsp[-1].node)); }
#line 1746 "src/parsing/parser.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 242 "src/parsing/parser.y" /* yacc.c:1646  */
    { (yyval.node)=new_ast_i32var_decl((yyvsp[-1].var)); }
#line 1752 "src/parsing/parser.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 244 "src/parsing/parser.y" /* yacc.c:1646  */
    {(yyval.node) = new_ast_var_assign((yyvsp[-3].var), (yyvsp[-1].node)); }
#line 1758 "src/parsing/parser.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 247 "src/parsing/parser.y" /* yacc.c:1646  */
    { (yyval.node) = (yyvsp[0].node); }
#line 1764 "src/parsing/parser.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 249 "src/parsing/parser.y" /* yacc.c:1646  */
    {  
            (yyval.node) = new_ast_expression((yyvsp[-1].op_type));
            (yyval.node)->left = (yyvsp[-2].node);
            (yyval.node)->right = (yyvsp[0].node);
          }
#line 1774 "src/parsing/parser.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 255 "src/parsing/parser.y" /* yacc.c:1646  */
    { (yyval.op_type) = PLUS;}
#line 1780 "src/parsing/parser.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 256 "src/parsing/parser.y" /* yacc.c:1646  */
    { (yyval.op_type) = TIMES;}
#line 1786 "src/parsing/parser.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 257 "src/parsing/parser.y" /* yacc.c:1646  */
    { (yyval.op_type) = MINUS;}
#line 1792 "src/parsing/parser.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 258 "src/parsing/parser.y" /* yacc.c:1646  */
    { (yyval.op_type) = DIVIDE;}
#line 1798 "src/parsing/parser.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 259 "src/parsing/parser.y" /* yacc.c:1646  */
    { (yyval.op_type) = AND;}
#line 1804 "src/parsing/parser.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 260 "src/parsing/parser.y" /* yacc.c:1646  */
    { (yyval.op_type) = OR;}
#line 1810 "src/parsing/parser.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 261 "src/parsing/parser.y" /* yacc.c:1646  */
    { (yyval.op_type) = LESS;}
#line 1816 "src/parsing/parser.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 262 "src/parsing/parser.y" /* yacc.c:1646  */
    { (yyval.op_type) = LESSEQUAL;}
#line 1822 "src/parsing/parser.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 263 "src/parsing/parser.y" /* yacc.c:1646  */
    { (yyval.op_type) = GREATER;}
#line 1828 "src/parsing/parser.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 264 "src/parsing/parser.y" /* yacc.c:1646  */
    { (yyval.op_type) = GREATEREQUAL;}
#line 1834 "src/parsing/parser.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 265 "src/parsing/parser.y" /* yacc.c:1646  */
    { (yyval.op_type) = EQUALS;}
#line 1840 "src/parsing/parser.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 266 "src/parsing/parser.y" /* yacc.c:1646  */
    { (yyval.op_type) = NOTEQUALS;}
#line 1846 "src/parsing/parser.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 268 "src/parsing/parser.y" /* yacc.c:1646  */
    { (yyval.node) = new_ast_const((yyvsp[0].val)); }
#line 1852 "src/parsing/parser.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 269 "src/parsing/parser.y" /* yacc.c:1646  */
    { (yyval.node) = new_ast_identifier((yyvsp[0].var)); }
#line 1858 "src/parsing/parser.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 270 "src/parsing/parser.y" /* yacc.c:1646  */
    { (yyval.node)=(yyvsp[-1].node); }
#line 1864 "src/parsing/parser.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 271 "src/parsing/parser.y" /* yacc.c:1646  */
    { (yyval.node)=(yyvsp[0].node); }
#line 1870 "src/parsing/parser.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 276 "src/parsing/parser.y" /* yacc.c:1646  */
    {
                (yyval.node) = new_ast_stream_push((yyvsp[-5].var),(yyvsp[0].var));
                (yyval.node)->down = (yyvsp[-3].node);
                populate_stream_names((yyvsp[-5].var),(yyvsp[0].var),(yyvsp[-3].node));
              }
#line 1880 "src/parsing/parser.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 284 "src/parsing/parser.y" /* yacc.c:1646  */
    {
                (yyval.node) = new_ast_stream_pull((yyvsp[-3].var),(yyvsp[-5].var));
                (yyval.node)->down = (yyvsp[-1].node);
                populate_pull_stream_names((yyvsp[-3].var),(yyvsp[-5].var),(yyvsp[-1].node));
              }
#line 1890 "src/parsing/parser.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 290 "src/parsing/parser.y" /* yacc.c:1646  */
    { (yyval.node)=new_ast_call_arg();    (yyval.node)->down=(yyvsp[0].node); }
#line 1896 "src/parsing/parser.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 291 "src/parsing/parser.y" /* yacc.c:1646  */
    { (yyval.node)=new_ast_call_arg();    (yyval.node)->down=new_ast_null(); }
#line 1902 "src/parsing/parser.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 292 "src/parsing/parser.y" /* yacc.c:1646  */
    { (yyval.node)=new_ast_call_arg(); (yyval.node)->side=(yyvsp[0].node); (yyval.node)->down=(yyvsp[-2].node); }
#line 1908 "src/parsing/parser.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 293 "src/parsing/parser.y" /* yacc.c:1646  */
    { (yyval.node)=new_ast_call_arg(); (yyval.node)->side=(yyvsp[0].node); (yyval.node)->down=new_ast_null();  }
#line 1914 "src/parsing/parser.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 296 "src/parsing/parser.y" /* yacc.c:1646  */
    { (yyval.node)=new_ast_pull_arg();    (yyval.node)->down=new_ast_identifier((yyvsp[0].var)); }
#line 1920 "src/parsing/parser.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 297 "src/parsing/parser.y" /* yacc.c:1646  */
    { (yyval.node)=new_ast_pull_arg(); (yyval.node)->side=(yyvsp[0].node); (yyval.node)->down=new_ast_identifier((yyvsp[-2].var));  }
#line 1926 "src/parsing/parser.tab.c" /* yacc.c:1646  */
    break;


#line 1930 "src/parsing/parser.tab.c" /* yacc.c:1646  */
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

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

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
      yyerror (YY_("syntax error"));
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
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
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
        yyerror (yymsgp);
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

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
                  yystos[yystate], yyvsp);
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
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
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
                  yystos[*yyssp], yyvsp);
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
#line 301 "src/parsing/parser.y" /* yacc.c:1906  */


int yyerror(char *s) 
{
  printf("yyerror : %s at line %d\n",s,linenum);
  return 0;
}


