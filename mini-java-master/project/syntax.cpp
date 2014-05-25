/* A Bison parser, made by GNU Bison 2.7.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2012 Free Software Foundation, Inc.
   
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
#define YYBISON_VERSION "2.7"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
/* Line 371 of yacc.c  */
#line 1 "C:\\Users\\Серёга\\Desktop\\mini-java-master\\mini-java-master\\project\\syntax.txt"

  #include <math.h>
  #include <stdio.h>
  #include <interface.h>
  #include <syntax.hpp>
  #include<string>
  int yylex (void);
  void yyerror (char const *);
  extern IProgram* yyprogram=0;

/* Line 371 of yacc.c  */
#line 79 "syntax.cpp"

# ifndef YY_NULL
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULL nullptr
#  else
#   define YY_NULL 0
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
   by #include "syntax.hpp".  */
#ifndef YY_YY_SYNTAX_HPP_INCLUDED
# define YY_YY_SYNTAX_HPP_INCLUDED
/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     _ID = 258,
     _NUM = 259,
     _STR = 260,
     _IF = 261,
     _ELSE = 262,
     _WHILE = 263,
     _SYSTEMOP = 264,
     _CLASS = 265,
     _MAIN = 266,
     _PUBLIC = 267,
     _STATIC = 268,
     _RETURN = 269,
     _EXTENDS = 270,
     _INT = 271,
     _BOOLEAN = 272,
     _VOID = 273,
     _STRING = 274,
     _TRUE = 275,
     _FALSE = 276,
     _THIS = 277,
     _NEW = 278,
     _LENGTH = 279,
     _POINT = 280,
     _SEMICOLUMN = 281,
     _STAR = 282,
     _ASSIGNMENT = 283,
     _WOW = 284,
     __COMMA = 285,
     _RL_BRACKET = 286,
     _RR_BRACKET = 287,
     _SL_BRACKET = 288,
     _SR_BRACKET = 289,
     _FL_BRACKET = 290,
     _FR_BRACKET = 291,
     _OPPLUS = 292,
     _OPMINUS = 293,
     _OPMULT = 294,
     _OPDIV = 295,
     _OPAND = 296,
     _OPLESS = 297,
     NEG = 298
   };
#endif


#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{
/* Line 387 of yacc.c  */
#line 84 "C:\\Users\\Серёга\\Desktop\\mini-java-master\\mini-java-master\\project\\syntax.txt"

 int IntV;
 char* StringV;
 CBinop Binop;
 //CT IdType;
 char* SymbolTable;
 IProgram* Program;
 IMainClass* MainClass;
 IClassDecl* ClassDecl;
 IClassDeclList* ClassDeclList;
 IVarDecl* VarDecl;
 IVarDeclList* VarDeclList;
 IMethodDecl* MethodDecl;
 IMethodDeclList* MethodDeclList;
 IFormalList* FormalList;
 IType* Type;    
 IStm* Stm;
 IStmList* StmList;
 IExp* Exp ;
 IExpList* ExpList ;


/* Line 387 of yacc.c  */
#line 188 "syntax.cpp"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
} YYLTYPE;
# define yyltype YYLTYPE /* obsolescent; will be withdrawn */
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;
extern YYLTYPE yylloc;
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */

#endif /* !YY_YY_SYNTAX_HPP_INCLUDED  */

/* Copy the second part of user declarations.  */

/* Line 390 of yacc.c  */
#line 229 "syntax.cpp"

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
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
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
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(N) (N)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
	     && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

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
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   239

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  44
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  17
/* YYNRULES -- Number of rules.  */
#define YYNRULES  53
/* YYNRULES -- Number of states.  */
#define YYNSTATES  147

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   298

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
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
      35,    36,    37,    38,    39,    40,    41,    42,    43
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     6,    24,    30,    37,    46,    49,    50,
      53,    54,    57,    58,    62,    76,    79,    80,    84,    85,
      90,    91,    95,    97,    99,   101,   105,   113,   119,   125,
     130,   138,   142,   146,   150,   154,   158,   162,   167,   171,
     178,   180,   182,   184,   186,   188,   190,   196,   201,   204,
     208,   211,   212,   216
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      45,     0,    -1,    46,    48,    -1,    10,     3,    35,    12,
      13,    18,    11,    31,    19,    33,    34,     3,    32,    35,
      57,    36,    36,    -1,    10,     3,    35,     1,    36,    -1,
      10,     3,    35,    50,    49,    36,    -1,    10,     3,    15,
       3,    35,    50,    49,    36,    -1,    47,    48,    -1,    -1,
      52,    49,    -1,    -1,    50,    51,    -1,    -1,    56,     3,
      26,    -1,    12,    56,     3,    31,    54,    32,    35,    50,
      53,    14,    58,    26,    36,    -1,    57,    53,    -1,    -1,
      56,     3,    55,    -1,    -1,    30,    56,     3,    55,    -1,
      -1,    16,    33,    34,    -1,    17,    -1,    16,    -1,     3,
      -1,    35,    53,    36,    -1,     6,    31,    58,    32,    57,
       7,    57,    -1,     8,    31,    58,    32,    57,    -1,     9,
      31,    58,    32,    26,    -1,     3,    28,    58,    26,    -1,
       3,    33,    58,    34,    28,    58,    26,    -1,    58,    37,
      58,    -1,    58,    38,    58,    -1,    58,    39,    58,    -1,
      58,    40,    58,    -1,    58,    42,    58,    -1,    58,    41,
      58,    -1,    58,    33,    58,    34,    -1,    58,    25,    24,
      -1,    58,    25,     3,    31,    59,    32,    -1,     4,    -1,
       5,    -1,    20,    -1,    21,    -1,     3,    -1,    22,    -1,
      23,    16,    33,    58,    34,    -1,    23,     3,    31,    32,
      -1,    29,    58,    -1,    31,    58,    32,    -1,    58,    60,
      -1,    -1,    30,    58,    60,    -1,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,   107,   107,   109,   113,   115,   116,   118,   119,   121,
     122,   124,   125,   127,   129,   133,   134,   136,   137,   139,
     140,   143,   144,   145,   146,   148,   149,   150,   151,   152,
     153,   156,   157,   158,   159,   160,   161,   162,   163,   164,
     165,   166,   167,   168,   169,   170,   171,   172,   173,   174,
     176,   177,   179,   180
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "_ID", "_NUM", "_STR", "_IF", "_ELSE",
  "_WHILE", "_SYSTEMOP", "_CLASS", "_MAIN", "_PUBLIC", "_STATIC",
  "_RETURN", "_EXTENDS", "_INT", "_BOOLEAN", "_VOID", "_STRING", "_TRUE",
  "_FALSE", "_THIS", "_NEW", "_LENGTH", "_POINT", "_SEMICOLUMN", "_STAR",
  "_ASSIGNMENT", "_WOW", "__COMMA", "_RL_BRACKET", "_RR_BRACKET",
  "_SL_BRACKET", "_SR_BRACKET", "_FL_BRACKET", "_FR_BRACKET", "_OPPLUS",
  "_OPMINUS", "_OPMULT", "_OPDIV", "_OPAND", "_OPLESS", "NEG", "$accept",
  "Program", "MainClass", "ClassDecl", "ClassDeclList", "MethodDeclList",
  "VarDeclList", "VarDecl", "MethodDecl", "StmList", "FormalList",
  "FormalRest", "Type", "Stm", "Exp", "ExpList", "ExpRest", YY_NULL
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    44,    45,    46,    47,    47,    47,    48,    48,    49,
      49,    50,    50,    51,    52,    53,    53,    54,    54,    55,
      55,    56,    56,    56,    56,    57,    57,    57,    57,    57,
      57,    58,    58,    58,    58,    58,    58,    58,    58,    58,
      58,    58,    58,    58,    58,    58,    58,    58,    58,    58,
      59,    59,    60,    60
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,    17,     5,     6,     8,     2,     0,     2,
       0,     2,     0,     3,    13,     2,     0,     3,     0,     4,
       0,     3,     1,     1,     1,     3,     7,     5,     5,     4,
       7,     3,     3,     3,     3,     3,     3,     4,     3,     6,
       1,     1,     1,     1,     1,     1,     5,     4,     2,     3,
       2,     0,     3,     0
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     8,     0,     1,     0,     8,     2,     0,
       0,     7,     0,     0,     0,     0,     0,     0,    10,     0,
      12,     4,    24,     0,    23,    22,     0,    11,    10,     0,
       0,    10,     0,     0,     5,     9,     0,     0,     0,     0,
      21,    13,     0,     6,    18,     0,     0,     0,     0,     0,
      20,     0,    12,     0,    17,     0,    16,     0,     0,    24,
       0,     0,     0,    16,     0,    16,    20,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    15,    19,     0,    44,
      40,    41,    42,    43,    45,     0,     0,     0,     0,     0,
       0,     0,     0,    25,     0,     3,     0,     0,    48,     0,
       0,    29,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    49,     0,    38,     0,
      31,    32,    33,    34,    36,    35,     0,     0,    27,    28,
      14,    47,     0,    51,    37,     0,     0,    46,    53,     0,
      30,    26,     0,    50,    39,    53,    52
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,     7,     8,    26,    18,    27,    28,    64,
      46,    54,    29,    65,    88,   139,   143
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -70
static const yytype_int16 yypact[] =
{
      -2,    62,    19,    15,    31,   -70,    67,    15,   -70,    60,
      16,   -70,    61,    73,     4,    69,    84,    72,   169,    86,
     -70,   -70,   -70,   185,    65,   -70,    93,   -70,    97,   127,
     109,   169,   139,   118,   -70,   -70,   144,   188,   135,   178,
     -70,   -70,   177,   -70,   185,   179,   180,   208,   211,   181,
     189,   183,   -70,   185,   -70,   186,     6,   215,    21,    26,
     191,   192,   193,    21,   206,    21,   189,    26,   190,    40,
      40,    40,    40,    40,   194,    40,   -70,   -70,   195,   -70,
     -70,   -70,   -70,   -70,   -70,    10,    40,    40,    42,    52,
      63,    74,    85,   -70,    95,   -70,   196,   199,    22,   106,
       8,   -70,    40,    40,    40,    40,    40,    40,    40,   197,
      21,    21,   202,   198,   201,    40,   -70,   204,   -70,   116,
     164,   164,   157,   157,   175,    22,    40,   222,   -70,   -70,
     -70,   -70,   126,    40,   -70,   136,    21,   -70,   154,   205,
     -70,   -70,    40,   -70,   -70,   154,   -70
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -70,   -70,   -70,   -70,   229,   152,   -10,   -70,   -70,   -15,
     -70,   172,     5,   -58,   -69,   -70,    94
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -13
static const yytype_int16 yytable[] =
{
      68,    89,    90,    91,    92,    17,    94,   -12,     1,    59,
      31,   117,    60,    96,    61,    62,   -12,    98,    99,     5,
     -12,   -12,    24,    25,    67,     6,    97,    60,    32,    61,
      62,    13,   118,   119,   120,   121,   122,   123,   124,   125,
     -12,    63,    56,    79,    80,    81,   132,   100,    74,    47,
      76,    14,   127,   128,    69,   102,    63,   135,    57,    70,
      82,    83,    84,    85,   138,     4,     9,   100,   101,    86,
      10,    87,    12,   145,    15,   102,    16,   100,   141,   103,
     104,   105,   106,   107,   108,   102,   109,    19,   100,   103,
     104,   105,   106,   107,   108,   110,   102,    30,    33,   100,
     103,   104,   105,   106,   107,   108,   111,   102,    21,    23,
     100,   103,   104,   105,   106,   107,   108,   112,   102,    20,
     100,   113,   103,   104,   105,   106,   107,   108,   102,    34,
      36,   100,   103,   104,   105,   106,   107,   108,   116,   102,
      37,   100,    39,   103,   104,   105,   106,   107,   108,   102,
     134,   100,    40,   103,   104,   105,   106,   107,   108,   102,
     137,   100,   140,   103,   104,   105,   106,   107,   108,   102,
      41,    43,    22,   103,   104,   105,   106,   107,   108,   100,
      35,    23,   100,    38,   142,    24,    25,   102,    22,   100,
     102,   103,   104,   105,   106,   107,   108,   102,   107,   108,
     100,    24,    25,   105,   106,   107,   108,    42,   102,    44,
      45,    50,    49,    48,    51,    55,    52,   108,    66,    53,
      75,    58,    71,    72,    73,   126,    78,   114,   129,   136,
      93,    95,   115,   131,   130,   133,    11,   144,    77,   146
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-70)))

#define yytable_value_is_error(Yytable_value) \
  YYID (0)

static const yytype_uint8 yycheck[] =
{
      58,    70,    71,    72,    73,     1,    75,     3,    10,     3,
      20,     3,     6,     3,     8,     9,    12,    86,    87,     0,
      16,    17,    16,    17,     3,    10,    16,     6,    23,     8,
       9,    15,    24,   102,   103,   104,   105,   106,   107,   108,
      36,    35,    52,     3,     4,     5,   115,    25,    63,    44,
      65,    35,   110,   111,    28,    33,    35,   126,    53,    33,
      20,    21,    22,    23,   133,     3,    35,    25,    26,    29,
       3,    31,    12,   142,    13,    33,     3,    25,   136,    37,
      38,    39,    40,    41,    42,    33,    34,    18,    25,    37,
      38,    39,    40,    41,    42,    32,    33,    11,    33,    25,
      37,    38,    39,    40,    41,    42,    32,    33,    36,    12,
      25,    37,    38,    39,    40,    41,    42,    32,    33,    35,
      25,    26,    37,    38,    39,    40,    41,    42,    33,    36,
       3,    25,    37,    38,    39,    40,    41,    42,    32,    33,
      31,    25,     3,    37,    38,    39,    40,    41,    42,    33,
      34,    25,    34,    37,    38,    39,    40,    41,    42,    33,
      34,    25,    26,    37,    38,    39,    40,    41,    42,    33,
      26,    36,     3,    37,    38,    39,    40,    41,    42,    25,
      28,    12,    25,    31,    30,    16,    17,    33,     3,    25,
      33,    37,    38,    39,    40,    41,    42,    33,    41,    42,
      25,    16,    17,    39,    40,    41,    42,    19,    33,    31,
      33,     3,    32,    34,     3,    32,    35,    42,     3,    30,
      14,    35,    31,    31,    31,    28,    36,    31,    26,     7,
      36,    36,    33,    32,    36,    31,     7,    32,    66,   145
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    10,    45,    46,     3,     0,    10,    47,    48,    35,
       3,    48,    12,    15,    35,    13,     3,     1,    50,    18,
      35,    36,     3,    12,    16,    17,    49,    51,    52,    56,
      11,    50,    56,    33,    36,    49,     3,    31,    49,     3,
      34,    26,    19,    36,    31,    33,    54,    56,    34,    32,
       3,     3,    35,    30,    55,    32,    50,    56,    35,     3,
       6,     8,     9,    35,    53,    57,     3,     3,    57,    28,
      33,    31,    31,    31,    53,    14,    53,    55,    36,     3,
       4,     5,    20,    21,    22,    23,    29,    31,    58,    58,
      58,    58,    58,    36,    58,    36,     3,    16,    58,    58,
      25,    26,    33,    37,    38,    39,    40,    41,    42,    34,
      32,    32,    32,    26,    31,    33,    32,     3,    24,    58,
      58,    58,    58,    58,    58,    58,    28,    57,    57,    26,
      36,    32,    58,    31,    34,    58,     7,    34,    58,    59,
      26,    57,    30,    60,    32,    58,    60
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

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
      YYERROR;							\
    }								\
while (YYID (0))

/* Error token number */
#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (YYID (N))                                                     \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (YYID (0))
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef __attribute__
/* This feature is available in gcc versions 2.5 and later.  */
# if (! defined __GNUC__ || __GNUC__ < 2 \
      || (__GNUC__ == 2 && __GNUC_MINOR__ < 5))
#  define __attribute__(Spec) /* empty */
# endif
#endif

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

__attribute__((__unused__))
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static unsigned
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
#else
static unsigned
yy_location_print_ (yyo, yylocp)
    FILE *yyo;
    YYLTYPE const * const yylocp;
#endif
{
  unsigned res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += fprintf (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += fprintf (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += fprintf (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += fprintf (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += fprintf (yyo, "-%d", end_col);
    }
  return res;
 }

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */
#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value, Location); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
#endif
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
  YYUSE (yylocationp);
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
        break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep, yylocationp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yylsp, yyrule)
    YYSTYPE *yyvsp;
    YYLTYPE *yylsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       , &(yylsp[(yyi + 1) - (yynrhs)])		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, yylsp, Rule); \
} while (YYID (0))

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
#ifndef	YYINITDEPTH
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
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
  YYSIZE_T yysize0 = yytnamerr (YY_NULL, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULL;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
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
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULL, yytname[yyx]);
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

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
#else
static void
yydestruct (yymsg, yytype, yyvaluep, yylocationp)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
    YYLTYPE *yylocationp;
#endif
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
        break;
    }
}




/* The lookahead symbol.  */
int yychar;


#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval YY_INITIAL_VALUE(yyval_default);

/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;


/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.
       `yyls': related to locations.

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

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yylsp = yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  yylsp[0] = yylloc;
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
	YYLTYPE *yyls1 = yyls;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yyls1, yysize * sizeof (*yylsp),
		    &yystacksize);

	yyls = yyls1;
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
	YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

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
      yychar = YYLEX;
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
  *++yylsp = yylloc;
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
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
/* Line 1792 of yacc.c  */
#line 107 "C:\\Users\\Серёга\\Desktop\\mini-java-master\\mini-java-master\\project\\syntax.txt"
    {yyprogram = (yyval.Program) = new CProgram ((yyvsp[(1) - (2)].MainClass), (yyvsp[(2) - (2)].ClassDeclList));}
    break;

  case 3:
/* Line 1792 of yacc.c  */
#line 111 "C:\\Users\\Серёга\\Desktop\\mini-java-master\\mini-java-master\\project\\syntax.txt"
    {(yyval.MainClass) = new CMainClass ((yyvsp[(2) - (17)].SymbolTable), (yyvsp[(12) - (17)].SymbolTable), (yyvsp[(15) - (17)].Stm));}
    break;

  case 4:
/* Line 1792 of yacc.c  */
#line 114 "C:\\Users\\Серёга\\Desktop\\mini-java-master\\mini-java-master\\project\\syntax.txt"
    { fprintf( stderr, "[%d, %d] Class error!", (yylsp[(3) - (5)]).first_line, (yylsp[(3) - (5)]).first_column ); }
    break;

  case 5:
/* Line 1792 of yacc.c  */
#line 115 "C:\\Users\\Серёга\\Desktop\\mini-java-master\\mini-java-master\\project\\syntax.txt"
    {(yyval.ClassDecl) = new CClassDecl ((yyvsp[(2) - (6)].SymbolTable), (yyvsp[(4) - (6)].VarDeclList), (yyvsp[(5) - (6)].MethodDeclList));}
    break;

  case 6:
/* Line 1792 of yacc.c  */
#line 116 "C:\\Users\\Серёга\\Desktop\\mini-java-master\\mini-java-master\\project\\syntax.txt"
    {(yyval.ClassDecl) =  new CExClassDecl ((yyvsp[(2) - (8)].SymbolTable), (yyvsp[(4) - (8)].SymbolTable), (yyvsp[(6) - (8)].VarDeclList), (yyvsp[(7) - (8)].MethodDeclList));}
    break;

  case 7:
/* Line 1792 of yacc.c  */
#line 118 "C:\\Users\\Серёга\\Desktop\\mini-java-master\\mini-java-master\\project\\syntax.txt"
    {(yyval.ClassDeclList) = new CClassDeclList((yyvsp[(1) - (2)].ClassDecl), (yyvsp[(2) - (2)].ClassDeclList));}
    break;

  case 8:
/* Line 1792 of yacc.c  */
#line 119 "C:\\Users\\Серёга\\Desktop\\mini-java-master\\mini-java-master\\project\\syntax.txt"
    {(yyval.ClassDeclList)=0;}
    break;

  case 9:
/* Line 1792 of yacc.c  */
#line 121 "C:\\Users\\Серёга\\Desktop\\mini-java-master\\mini-java-master\\project\\syntax.txt"
    {(yyval.MethodDeclList) = new CMethodDeclList((yyvsp[(1) - (2)].MethodDecl), (yyvsp[(2) - (2)].MethodDeclList));}
    break;

  case 10:
/* Line 1792 of yacc.c  */
#line 122 "C:\\Users\\Серёга\\Desktop\\mini-java-master\\mini-java-master\\project\\syntax.txt"
    {(yyval.MethodDeclList)=0;}
    break;

  case 11:
/* Line 1792 of yacc.c  */
#line 124 "C:\\Users\\Серёга\\Desktop\\mini-java-master\\mini-java-master\\project\\syntax.txt"
    {(yyval.VarDeclList) = new CVarDeclList((yyvsp[(2) - (2)].VarDecl), (yyvsp[(1) - (2)].VarDeclList));}
    break;

  case 12:
/* Line 1792 of yacc.c  */
#line 125 "C:\\Users\\Серёга\\Desktop\\mini-java-master\\mini-java-master\\project\\syntax.txt"
    {(yyval.VarDeclList)=0;}
    break;

  case 13:
/* Line 1792 of yacc.c  */
#line 127 "C:\\Users\\Серёга\\Desktop\\mini-java-master\\mini-java-master\\project\\syntax.txt"
    {(yyval.VarDecl) = new CVarDecl((yyvsp[(1) - (3)].SymbolTable), (yyvsp[(2) - (3)].SymbolTable));}
    break;

  case 14:
/* Line 1792 of yacc.c  */
#line 131 "C:\\Users\\Серёга\\Desktop\\mini-java-master\\mini-java-master\\project\\syntax.txt"
    {(yyval.MethodDecl) = new CMethodDecl((yyvsp[(2) - (13)].SymbolTable), (yyvsp[(3) - (13)].SymbolTable), (yyvsp[(5) - (13)].FormalList), (yyvsp[(8) - (13)].VarDeclList), (yyvsp[(9) - (13)].StmList), (yyvsp[(11) - (13)].Exp));}
    break;

  case 15:
/* Line 1792 of yacc.c  */
#line 133 "C:\\Users\\Серёга\\Desktop\\mini-java-master\\mini-java-master\\project\\syntax.txt"
    {(yyval.StmList) = new CStmList((yyvsp[(1) - (2)].Stm), (yyvsp[(2) - (2)].StmList));}
    break;

  case 16:
/* Line 1792 of yacc.c  */
#line 134 "C:\\Users\\Серёга\\Desktop\\mini-java-master\\mini-java-master\\project\\syntax.txt"
    {(yyval.StmList)=0;}
    break;

  case 17:
/* Line 1792 of yacc.c  */
#line 136 "C:\\Users\\Серёга\\Desktop\\mini-java-master\\mini-java-master\\project\\syntax.txt"
    {(yyval.FormalList) = new CFormalList((yyvsp[(1) - (3)].SymbolTable), (yyvsp[(2) - (3)].SymbolTable), (yyvsp[(3) - (3)].FormalList));}
    break;

  case 18:
/* Line 1792 of yacc.c  */
#line 137 "C:\\Users\\Серёга\\Desktop\\mini-java-master\\mini-java-master\\project\\syntax.txt"
    {(yyval.FormalList)=0;}
    break;

  case 19:
/* Line 1792 of yacc.c  */
#line 139 "C:\\Users\\Серёга\\Desktop\\mini-java-master\\mini-java-master\\project\\syntax.txt"
    {(yyval.FormalList) = new CFormalList((yyvsp[(2) - (4)].SymbolTable), (yyvsp[(3) - (4)].SymbolTable), (yyvsp[(4) - (4)].FormalList));}
    break;

  case 20:
/* Line 1792 of yacc.c  */
#line 140 "C:\\Users\\Серёга\\Desktop\\mini-java-master\\mini-java-master\\project\\syntax.txt"
    {(yyval.FormalList)=0;}
    break;

  case 21:
/* Line 1792 of yacc.c  */
#line 143 "C:\\Users\\Серёга\\Desktop\\mini-java-master\\mini-java-master\\project\\syntax.txt"
    {(yyval.SymbolTable) = "int[]";}
    break;

  case 22:
/* Line 1792 of yacc.c  */
#line 144 "C:\\Users\\Серёга\\Desktop\\mini-java-master\\mini-java-master\\project\\syntax.txt"
    {(yyval.SymbolTable) = "boolean";}
    break;

  case 23:
/* Line 1792 of yacc.c  */
#line 145 "C:\\Users\\Серёга\\Desktop\\mini-java-master\\mini-java-master\\project\\syntax.txt"
    {(yyval.SymbolTable) = "int";}
    break;

  case 24:
/* Line 1792 of yacc.c  */
#line 146 "C:\\Users\\Серёга\\Desktop\\mini-java-master\\mini-java-master\\project\\syntax.txt"
    {(yyval.SymbolTable) = (yyvsp[(1) - (1)].SymbolTable);}
    break;

  case 25:
/* Line 1792 of yacc.c  */
#line 148 "C:\\Users\\Серёга\\Desktop\\mini-java-master\\mini-java-master\\project\\syntax.txt"
    {(yyval.Stm) = new CCompStm((yyvsp[(2) - (3)].StmList));}
    break;

  case 26:
/* Line 1792 of yacc.c  */
#line 149 "C:\\Users\\Серёга\\Desktop\\mini-java-master\\mini-java-master\\project\\syntax.txt"
    {(yyval.Stm) = new CIfStm ((yyvsp[(3) - (7)].Exp), (yyvsp[(5) - (7)].Stm), (yyvsp[(7) - (7)].Stm));}
    break;

  case 27:
/* Line 1792 of yacc.c  */
#line 150 "C:\\Users\\Серёга\\Desktop\\mini-java-master\\mini-java-master\\project\\syntax.txt"
    {(yyval.Stm) = new CWhStm ((yyvsp[(3) - (5)].Exp), (yyvsp[(5) - (5)].Stm));}
    break;

  case 28:
/* Line 1792 of yacc.c  */
#line 151 "C:\\Users\\Серёга\\Desktop\\mini-java-master\\mini-java-master\\project\\syntax.txt"
    {(yyval.Stm) = new CSOPStm ((yyvsp[(3) - (5)].Exp));}
    break;

  case 29:
/* Line 1792 of yacc.c  */
#line 152 "C:\\Users\\Серёга\\Desktop\\mini-java-master\\mini-java-master\\project\\syntax.txt"
    {(yyval.Stm) = new CAsStm((yyvsp[(1) - (4)].SymbolTable), (yyvsp[(3) - (4)].Exp));}
    break;

  case 30:
/* Line 1792 of yacc.c  */
#line 153 "C:\\Users\\Серёга\\Desktop\\mini-java-master\\mini-java-master\\project\\syntax.txt"
    {(yyval.Stm) = new CAsExpStm ((yyvsp[(1) - (7)].SymbolTable), (yyvsp[(3) - (7)].Exp), (yyvsp[(6) - (7)].Exp));}
    break;

  case 31:
/* Line 1792 of yacc.c  */
#line 156 "C:\\Users\\Серёга\\Desktop\\mini-java-master\\mini-java-master\\project\\syntax.txt"
    { (yyval.Exp) = new COpExp ((yyvsp[(1) - (3)].Exp), B_Plus, (yyvsp[(3) - (3)].Exp)) ;}
    break;

  case 32:
/* Line 1792 of yacc.c  */
#line 157 "C:\\Users\\Серёга\\Desktop\\mini-java-master\\mini-java-master\\project\\syntax.txt"
    { (yyval.Exp) = new COpExp((yyvsp[(1) - (3)].Exp), B_Minus , (yyvsp[(3) - (3)].Exp)); }
    break;

  case 33:
/* Line 1792 of yacc.c  */
#line 158 "C:\\Users\\Серёга\\Desktop\\mini-java-master\\mini-java-master\\project\\syntax.txt"
    { (yyval.Exp) = new COpExp((yyvsp[(1) - (3)].Exp), B_Mult, (yyvsp[(3) - (3)].Exp)); }
    break;

  case 34:
/* Line 1792 of yacc.c  */
#line 159 "C:\\Users\\Серёга\\Desktop\\mini-java-master\\mini-java-master\\project\\syntax.txt"
    {(yyval.Exp) = new COpExp((yyvsp[(1) - (3)].Exp), B_Div, (yyvsp[(3) - (3)].Exp));}
    break;

  case 35:
/* Line 1792 of yacc.c  */
#line 160 "C:\\Users\\Серёга\\Desktop\\mini-java-master\\mini-java-master\\project\\syntax.txt"
    {(yyval.Exp) = new COpExp((yyvsp[(1) - (3)].Exp), B_Less, (yyvsp[(3) - (3)].Exp));}
    break;

  case 36:
/* Line 1792 of yacc.c  */
#line 161 "C:\\Users\\Серёга\\Desktop\\mini-java-master\\mini-java-master\\project\\syntax.txt"
    {(yyval.Exp) = new COpExp((yyvsp[(1) - (3)].Exp), B_And, (yyvsp[(3) - (3)].Exp));}
    break;

  case 37:
/* Line 1792 of yacc.c  */
#line 162 "C:\\Users\\Серёга\\Desktop\\mini-java-master\\mini-java-master\\project\\syntax.txt"
    {(yyval.Exp) = new CExExp((yyvsp[(1) - (4)].Exp), (yyvsp[(3) - (4)].Exp));}
    break;

  case 38:
/* Line 1792 of yacc.c  */
#line 163 "C:\\Users\\Серёга\\Desktop\\mini-java-master\\mini-java-master\\project\\syntax.txt"
    {(yyval.Exp) = new CLenExp((yyvsp[(1) - (3)].Exp));}
    break;

  case 39:
/* Line 1792 of yacc.c  */
#line 164 "C:\\Users\\Серёга\\Desktop\\mini-java-master\\mini-java-master\\project\\syntax.txt"
    {(yyval.Exp) = new CIdClExp ((yyvsp[(1) - (6)].Exp), (yyvsp[(3) - (6)].SymbolTable), (yyvsp[(5) - (6)].ExpList));}
    break;

  case 40:
/* Line 1792 of yacc.c  */
#line 165 "C:\\Users\\Серёга\\Desktop\\mini-java-master\\mini-java-master\\project\\syntax.txt"
    { (yyval.Exp) = new CNExp ((yyvsp[(1) - (1)].IntV)); }
    break;

  case 41:
/* Line 1792 of yacc.c  */
#line 166 "C:\\Users\\Серёга\\Desktop\\mini-java-master\\mini-java-master\\project\\syntax.txt"
    { (yyval.Exp) = new CStrExp ((yyvsp[(1) - (1)].StringV)); }
    break;

  case 42:
/* Line 1792 of yacc.c  */
#line 167 "C:\\Users\\Серёга\\Desktop\\mini-java-master\\mini-java-master\\project\\syntax.txt"
    {(yyval.Exp) = new CTrExp();}
    break;

  case 43:
/* Line 1792 of yacc.c  */
#line 168 "C:\\Users\\Серёга\\Desktop\\mini-java-master\\mini-java-master\\project\\syntax.txt"
    {(yyval.Exp) = new CFExp();}
    break;

  case 44:
/* Line 1792 of yacc.c  */
#line 169 "C:\\Users\\Серёга\\Desktop\\mini-java-master\\mini-java-master\\project\\syntax.txt"
    { (yyval.Exp) = new CIdExp ((yyvsp[(1) - (1)].SymbolTable));}
    break;

  case 45:
/* Line 1792 of yacc.c  */
#line 170 "C:\\Users\\Серёга\\Desktop\\mini-java-master\\mini-java-master\\project\\syntax.txt"
    {(yyval.Exp) = new CThExp();}
    break;

  case 46:
/* Line 1792 of yacc.c  */
#line 171 "C:\\Users\\Серёга\\Desktop\\mini-java-master\\mini-java-master\\project\\syntax.txt"
    {(yyval.Exp) = new CNewIntExp((yyvsp[(4) - (5)].Exp));}
    break;

  case 47:
/* Line 1792 of yacc.c  */
#line 172 "C:\\Users\\Серёга\\Desktop\\mini-java-master\\mini-java-master\\project\\syntax.txt"
    {(yyval.Exp) = new CNewIdExp((yyvsp[(2) - (4)].SymbolTable));}
    break;

  case 48:
/* Line 1792 of yacc.c  */
#line 173 "C:\\Users\\Серёга\\Desktop\\mini-java-master\\mini-java-master\\project\\syntax.txt"
    {(yyval.Exp) = new CNotExp((yyvsp[(2) - (2)].Exp));}
    break;

  case 49:
/* Line 1792 of yacc.c  */
#line 174 "C:\\Users\\Серёга\\Desktop\\mini-java-master\\mini-java-master\\project\\syntax.txt"
    {(yyval.Exp) = new CBrExp((yyvsp[(2) - (3)].Exp));}
    break;

  case 50:
/* Line 1792 of yacc.c  */
#line 176 "C:\\Users\\Серёга\\Desktop\\mini-java-master\\mini-java-master\\project\\syntax.txt"
    {(yyval.ExpList) = new CExpList((yyvsp[(1) - (2)].Exp), (yyvsp[(2) - (2)].ExpList));}
    break;

  case 51:
/* Line 1792 of yacc.c  */
#line 177 "C:\\Users\\Серёга\\Desktop\\mini-java-master\\mini-java-master\\project\\syntax.txt"
    {(yyval.ExpList)=0;}
    break;

  case 52:
/* Line 1792 of yacc.c  */
#line 179 "C:\\Users\\Серёга\\Desktop\\mini-java-master\\mini-java-master\\project\\syntax.txt"
    {(yyval.ExpList) = new CExpList((yyvsp[(2) - (3)].Exp), (yyvsp[(3) - (3)].ExpList));}
    break;

  case 53:
/* Line 1792 of yacc.c  */
#line 180 "C:\\Users\\Серёга\\Desktop\\mini-java-master\\mini-java-master\\project\\syntax.txt"
    {(yyval.ExpList)=0;}
    break;


/* Line 1792 of yacc.c  */
#line 1980 "syntax.cpp"
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
  *++yylsp = yyloc;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
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

  yyerror_range[1] = yylloc;

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
		      yytoken, &yylval, &yylloc);
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

  yyerror_range[1] = yylsp[1-yylen];
  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

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

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
  *++yylsp = yyloc;

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
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp, yylsp);
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
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


/* Line 2055 of yacc.c  */
#line 182 "C:\\Users\\Серёга\\Desktop\\mini-java-master\\mini-java-master\\project\\syntax.txt"

 
void yyerror (char const * msg)
{
	fprintf( stderr, "[%d,%d-%d,%d] %s\n", yylloc.first_line, yylloc.first_column,
		yylloc.last_line, yylloc.last_column, msg );
}
