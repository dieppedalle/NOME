/* A Bison parser, made by GNU Bison 3.0.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

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
#define YYBISON_VERSION "3.0"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1


/* Substitute the variable and function names.  */
#define yyparse         nomparse
#define yylex           nomlex
#define yyerror         nomerror
#define yydebug         nomdebug
#define yynerrs         nomnerrs

#define yylval          nomlval
#define yychar          nomchar
#define yylloc          nomlloc

/* Copy the first part of user declarations.  */
#line 5 "C:\\Users\\dieppedalle\\Documents\\nomeProject\\nome\\compilerNome\\parser.y" /* yacc.c:339  */

#include <FlexLexer.h>
#include <stdio.h>
#include <string.h>
#include <list>
#include <Lewis/Data.h>
#include <Lewis/MeshNew.h>
#include <Lewis/Session.h>
#include <Lewis/Reader.h>
#include <Lewis/TransformationNew.h>
#include <Lewis/PolylineNew.h>
#include <Lewis/CircleNew.h>
#include <Lewis/FunnelNew.h>
#include <Lewis/TunnelNew.h>
#include <Lewis/InstanceNew.h>
#include <Lewis/BSplineNew.h>

extern int nomlineno;
extern char* nomtext;
extern int nomcolumn;

int nomlex(void);
int nomerror(Session* currSession, const char *s) {
  printf("%s on line %d - %s\n", s, nomlineno, nomtext);
}

int nomwrap() {
    return 1;
}

map<string,QColor> surfaces2;
map<string,Vert*> vertices2;
std::vector<string> tempVariables2;
std::vector<string> tempFaceDelete2;
string currentSetName2;
std::list<SetNew *> currentSetList2;
map<string,std::vector<double>> currentBank2;
std::vector<string> currentInstanceList2;
std::list<InstanceNew *> currentGroup2;
std::list<FaceNew *> currentMeshFaces2;
std::list<Vert *> currentMeshVertices2;
std::list<EdgeNew *> currentMeshEdges2;

std::list<TransformationNew *> currentTransformations2;

double *getBankValue(std::string str, Session* currSession){
    unsigned first = str.find("$") + 1;
    unsigned last = str.find(".");
    string strNew = str.substr (first,last-first);

    for(auto b : currSession->banks) {
        if (b->name == strNew){
            for(auto s : b->sets) {
                if (s->name == str.substr(last + 1)){
                    return &s->value;
                }
            }
        }
    }
    return NULL;
}




#line 141 "C:\\Users\\dieppedalle\\Documents\\nomeProject\\nome\\compilerNome\\parser.cpp" /* yacc.c:339  */

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
# define YYERROR_VERBOSE 1
#endif

/* In a future release of Bison, this section will be replaced
   by #include "parser.hpp".  */
#ifndef YY_NOM_C_USERS_DIEPPEDALLE_DOCUMENTS_NOMEPROJECT_NOME_COMPILERNOME_PARSER_HPP_INCLUDED
# define YY_NOM_C_USERS_DIEPPEDALLE_DOCUMENTS_NOMEPROJECT_NOME_COMPILERNOME_PARSER_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int nomdebug;
#endif
/* "%code requires" blocks.  */
#line 1 "C:\\Users\\dieppedalle\\Documents\\nomeProject\\nome\\compilerNome\\parser.y" /* yacc.c:355  */

#include <Lewis/Session.h>

#line 175 "C:\\Users\\dieppedalle\\Documents\\nomeProject\\nome\\compilerNome\\parser.cpp" /* yacc.c:355  */

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    COLOR = 258,
    VARIABLE = 259,
    COMMENT = 260,
    NEWLINE = 261,
    SURFACE = 262,
    END_SURFACE = 263,
    MESH = 264,
    END_MESH = 265,
    FACE = 266,
    END_FACE = 267,
    BEG_POINT = 268,
    END_POINT = 269,
    OBJECT = 270,
    END_OBJECT = 271,
    BANK = 272,
    END_BANK = 273,
    TUNNEL = 274,
    END_TUNNEL = 275,
    FUNNEL = 276,
    END_FUNNEL = 277,
    POLYLINE = 278,
    END_POLYLINE = 279,
    INSTANCE = 280,
    END_INSTANCE = 281,
    CIRCLE = 282,
    END_CIRCLE = 283,
    BEG_DELETE = 284,
    END_DELETE = 285,
    GROUP = 286,
    END_GROUP = 287,
    TRANSLATE = 288,
    ROTATE = 289,
    MIRROR = 290,
    SET = 291,
    OPARENTHESES = 292,
    EPARENTHESES = 293,
    OBRACE = 294,
    EXPR = 295,
    DOLLAR = 296,
    EBRACE = 297,
    PERIOD = 298,
    TOKHEAT = 299,
    STATE = 300,
    TOKTARGET = 301,
    TOKTEMPERATURE = 302,
    SCALE = 303,
    SUBDIVISION = 304,
    END_SUBDIVISION = 305,
    SUBDIVISIONS = 306,
    TYPE = 307,
    OFFSET = 308,
    END_OFFSET = 309,
    MIN = 310,
    MAX = 311,
    STEP = 312,
    BSPLINE = 313,
    END_BSPLINE = 314,
    CLOSED = 315,
    SLICES = 316,
    BANK_EXPR = 317,
    NUMBER = 318
  };
#endif
/* Tokens.  */
#define COLOR 258
#define VARIABLE 259
#define COMMENT 260
#define NEWLINE 261
#define SURFACE 262
#define END_SURFACE 263
#define MESH 264
#define END_MESH 265
#define FACE 266
#define END_FACE 267
#define BEG_POINT 268
#define END_POINT 269
#define OBJECT 270
#define END_OBJECT 271
#define BANK 272
#define END_BANK 273
#define TUNNEL 274
#define END_TUNNEL 275
#define FUNNEL 276
#define END_FUNNEL 277
#define POLYLINE 278
#define END_POLYLINE 279
#define INSTANCE 280
#define END_INSTANCE 281
#define CIRCLE 282
#define END_CIRCLE 283
#define BEG_DELETE 284
#define END_DELETE 285
#define GROUP 286
#define END_GROUP 287
#define TRANSLATE 288
#define ROTATE 289
#define MIRROR 290
#define SET 291
#define OPARENTHESES 292
#define EPARENTHESES 293
#define OBRACE 294
#define EXPR 295
#define DOLLAR 296
#define EBRACE 297
#define PERIOD 298
#define TOKHEAT 299
#define STATE 300
#define TOKTARGET 301
#define TOKTEMPERATURE 302
#define SCALE 303
#define SUBDIVISION 304
#define END_SUBDIVISION 305
#define SUBDIVISIONS 306
#define TYPE 307
#define OFFSET 308
#define END_OFFSET 309
#define MIN 310
#define MAX 311
#define STEP 312
#define BSPLINE 313
#define END_BSPLINE 314
#define CLOSED 315
#define SLICES 316
#define BANK_EXPR 317
#define NUMBER 318

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 90 "C:\\Users\\dieppedalle\\Documents\\nomeProject\\nome\\compilerNome\\parser.y" /* yacc.c:355  */

    double intNumber;
    double number;
    char *string;
    bool boolean;
    struct {
        char *string; // char *strVal;
        double number;   // int posVal;
    } numPos;

#line 324 "C:\\Users\\dieppedalle\\Documents\\nomeProject\\nome\\compilerNome\\parser.cpp" /* yacc.c:355  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE nomlval;
extern YYLTYPE nomlloc;
int nomparse (Session* currSession);

#endif /* !YY_NOM_C_USERS_DIEPPEDALLE_DOCUMENTS_NOMEPROJECT_NOME_COMPILERNOME_PARSER_HPP_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 353 "C:\\Users\\dieppedalle\\Documents\\nomeProject\\nome\\compilerNome\\parser.cpp" /* yacc.c:358  */

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

#ifndef __attribute__
/* This feature is available in gcc versions 2.5 and later.  */
# if (! defined __GNUC__ || __GNUC__ < 2 \
      || (__GNUC__ == 2 && __GNUC_MINOR__ < 5))
#  define __attribute__(Spec) /* empty */
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
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   181

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  64
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  43
/* YYNRULES -- Number of rules.  */
#define YYNRULES  74
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  198

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   318

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
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   109,   109,   110,   115,   115,   115,   115,   115,   115,
     115,   116,   116,   116,   116,   116,   116,   116,   117,   117,
     117,   120,   123,   132,   139,   147,   153,   155,   161,   162,
     168,   169,   174,   175,   175,   175,   175,   179,   221,   254,
     287,   297,   298,   301,   302,   306,   348,   349,   353,   358,
     359,   363,   380,   414,   441,   451,   457,   470,   488,   489,
     489,   493,   545,   556,   584,   631,   678,   684,   725,   732,
     786,   812,   862,   868,   900
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "COLOR", "VARIABLE", "COMMENT",
  "NEWLINE", "SURFACE", "END_SURFACE", "MESH", "END_MESH", "FACE",
  "END_FACE", "BEG_POINT", "END_POINT", "OBJECT", "END_OBJECT", "BANK",
  "END_BANK", "TUNNEL", "END_TUNNEL", "FUNNEL", "END_FUNNEL", "POLYLINE",
  "END_POLYLINE", "INSTANCE", "END_INSTANCE", "CIRCLE", "END_CIRCLE",
  "BEG_DELETE", "END_DELETE", "GROUP", "END_GROUP", "TRANSLATE", "ROTATE",
  "MIRROR", "SET", "OPARENTHESES", "EPARENTHESES", "OBRACE", "EXPR",
  "DOLLAR", "EBRACE", "PERIOD", "TOKHEAT", "STATE", "TOKTARGET",
  "TOKTEMPERATURE", "SCALE", "SUBDIVISION", "END_SUBDIVISION",
  "SUBDIVISIONS", "TYPE", "OFFSET", "END_OFFSET", "MIN", "MAX", "STEP",
  "BSPLINE", "END_BSPLINE", "CLOSED", "SLICES", "BANK_EXPR", "NUMBER",
  "$accept", "commands", "command", "numberValue", "num", "numPosTok",
  "comment", "variables", "surfaceArgs", "closedArgs", "transformArgs",
  "rotateArgs", "translateArgs", "scaleArgs", "mirrorArgs", "faceArgs",
  "instanceArgs", "instanceGroup", "faceDeleteArgs",
  "instanceOffseSubdivide", "instanceOffseSubdivideArgs", "subdivision",
  "offset", "mesh", "group", "expr", "delete", "set", "setArgs",
  "faceMesh", "bank", "circle", "tunnel", "funnel", "parenthesisName",
  "face", "faceDelete", "bspline", "polyline", "instance", "object",
  "surface", "point", YY_NULL
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
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318
};
# endif

#define YYPACT_NINF -62

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-62)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int8 yypact[] =
{
     -62,   123,   -62,   -62,    11,    14,    16,    23,    24,    27,
      30,    36,    37,    38,    40,   -62,    41,    42,    43,    45,
     -62,   -62,   -62,   -62,   -62,   -62,   -62,   -62,   -62,   -62,
     -62,   -62,   -62,   -62,   -62,   -62,   -62,   -62,    48,   -62,
      17,    21,    17,   -62,    26,    34,    17,    55,    35,     2,
     -62,   -62,     6,    13,    39,    12,   -62,    66,   -25,    59,
       1,   -25,   -25,    53,    66,   -25,    74,   -62,   -62,   -16,
     -17,   -25,   -25,   -25,   -62,    75,   -62,    -2,    76,    71,
      44,   -62,   -25,   -62,   -62,   -62,   -62,    81,   -62,   -62,
     -25,   -25,   -62,   -62,   -25,    78,    83,   -62,   -62,    84,
      87,   -62,    46,    17,   -25,    17,   -62,   -62,   -62,   -62,
      49,   -25,    33,   -25,   -25,    -9,    60,   -62,    93,   -62,
      50,   -25,    52,   -25,    66,    58,    65,   -62,   -25,   -25,
     -25,   -62,    68,    69,    77,    79,   -62,   -62,   -62,   -62,
      85,    66,   -25,    61,   -62,    66,    86,   103,   -62,   111,
     -25,    88,    91,   -25,   -25,   -25,   -25,   -62,   -62,    67,
     -25,    72,   127,   -62,   -62,   -25,   117,   119,   -25,   -25,
     -25,   -25,    22,   -62,    89,   -62,   -62,   -62,   -62,   -62,
     -25,   -25,   -25,   -25,   -62,   -62,   101,   107,   -25,   109,
     -62,   112,   113,   -62,   -25,   -62,   115,   -62
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     1,    25,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    46,     0,     0,     0,     0,
       3,     4,    18,    19,     5,    16,    15,    10,    17,    11,
      12,     8,    20,    13,    14,     9,     6,     7,     0,    41,
       0,     0,     0,    58,     0,     0,     0,     0,     0,     0,
      43,    49,     0,     0,     0,     0,    26,    28,     0,     0,
       0,     0,     0,     0,    28,     0,     0,    56,    47,     0,
       0,     0,     0,     0,    53,     0,    42,     0,     0,     0,
       0,    23,     0,    21,    22,    72,    62,     0,    60,    59,
       0,     0,    70,    32,     0,     0,     0,    54,    44,     0,
       0,    50,     0,     0,     0,     0,    27,    66,    29,    67,
       0,     0,     0,     0,     0,     0,     0,    68,     0,    48,
       0,     0,    30,     0,    28,     0,     0,    24,     0,     0,
       0,    71,     0,     0,     0,     0,    33,    34,    35,    36,
       0,    28,     0,     0,    31,    28,     0,     0,    55,     0,
       0,     0,     0,     0,     0,     0,     0,    63,    32,     0,
       0,     0,     0,    61,    74,     0,     0,     0,     0,     0,
       0,     0,     0,    51,     0,    69,    73,    57,    64,    65,
       0,     0,     0,     0,    45,    52,     0,     0,     0,     0,
      38,     0,     0,    39,     0,    40,     0,    37
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -62,   -62,   -62,   -61,   -62,   -62,    95,   -62,   -59,   -62,
      -1,   -62,   -62,   -62,   -62,   -62,   -62,   -62,   -62,   -62,
     -62,   -62,   -62,   -62,   -62,   -62,   -62,   -62,   -62,   -62,
     -62,   -62,   -62,   -62,   -39,   -62,   -62,   -62,   -62,   -62,
     -62,   -62,   -62
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,    20,    82,    83,   128,    21,    77,    79,   145,
     115,   136,   137,   138,   139,    55,    69,    98,    49,   101,
      70,    22,    23,    24,    25,    84,    26,    89,    60,    76,
      27,    28,    29,    30,    57,    31,    68,    32,    33,    34,
      35,    36,    37
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      90,    91,   106,    59,    94,    93,     3,    63,    99,    96,
     102,   103,   104,    66,    80,    38,    97,   131,    39,    86,
      40,   111,    74,    75,   132,   133,   134,    41,    42,   113,
     114,    43,    67,   116,    44,   100,   107,    87,    81,   135,
      45,    46,    47,   123,    48,    50,    51,    52,   184,    53,
     126,    54,   129,   130,    56,   132,   133,   134,    58,    64,
     143,    71,   146,    61,   122,   147,   124,   150,   151,   152,
     135,    62,    65,    78,    72,    85,    73,    92,    95,   105,
     108,   159,   158,   109,   110,   112,   161,   118,   119,   165,
     117,   120,   168,   169,   170,   171,   127,   141,   140,   174,
     148,   142,   121,   149,   177,   153,   154,   180,   181,   182,
     183,   125,   144,   157,   155,   163,   156,   173,   160,   186,
     187,   188,   189,     2,   162,   164,   166,   192,     3,   167,
       4,   175,     5,   196,     6,   176,     7,   178,     8,   190,
       9,   179,    10,   185,    11,   191,    12,   193,    13,   194,
      14,   195,    15,   197,    16,    88,     0,   172,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    17,     0,     0,     0,    18,     0,     0,     0,
       0,    19
};

static const yytype_int16 yycheck[] =
{
      61,    62,     4,    42,    65,    64,     5,    46,    25,    25,
      71,    72,    73,    11,    39,     4,    32,    26,     4,    18,
       4,    82,    10,    11,    33,    34,    35,     4,     4,    90,
      91,     4,    30,    94,     4,    52,    38,    36,    63,    48,
       4,     4,     4,   104,     4,     4,     4,     4,    26,     4,
     111,     3,   113,   114,    37,    33,    34,    35,    37,     4,
     121,    55,   123,    37,   103,   124,   105,   128,   129,   130,
      48,    37,    37,     7,    61,    16,    37,    24,     4,     4,
       4,   142,   141,    12,    40,     4,   145,     4,     4,   150,
      12,     4,   153,   154,   155,   156,    63,     4,    38,   160,
      42,    51,    56,    38,   165,    37,    37,   168,   169,   170,
     171,    62,    60,    28,    37,    12,    37,    50,    57,   180,
     181,   182,   183,     0,    38,    14,    38,   188,     5,    38,
       7,    59,     9,   194,    11,     8,    13,    20,    15,    38,
      17,    22,    19,    54,    21,    38,    23,    38,    25,    37,
      27,    38,    29,    38,    31,    60,    -1,   158,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    49,    -1,    -1,    -1,    53,    -1,    -1,    -1,
      -1,    58
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    65,     0,     5,     7,     9,    11,    13,    15,    17,
      19,    21,    23,    25,    27,    29,    31,    49,    53,    58,
      66,    70,    85,    86,    87,    88,    90,    94,    95,    96,
      97,    99,   101,   102,   103,   104,   105,   106,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,    82,
       4,     4,     4,     4,     3,    79,    37,    98,    37,    98,
      92,    37,    37,    98,     4,    37,    11,    30,   100,    80,
      84,    55,    61,    37,    10,    11,    93,    71,     7,    72,
      39,    63,    67,    68,    89,    16,    18,    36,    70,    91,
      67,    67,    24,    72,    67,     4,    25,    32,    81,    25,
      52,    83,    67,    67,    67,     4,     4,    38,     4,    12,
      40,    67,     4,    67,    67,    74,    67,    12,     4,     4,
       4,    56,    98,    67,    98,    62,    67,    63,    69,    67,
      67,    26,    33,    34,    35,    48,    75,    76,    77,    78,
      38,     4,    51,    67,    60,    73,    67,    72,    42,    38,
      67,    67,    67,    37,    37,    37,    37,    28,    72,    67,
      57,    72,    38,    12,    14,    67,    38,    38,    67,    67,
      67,    67,    74,    50,    67,    59,     8,    67,    20,    22,
      67,    67,    67,    67,    26,    54,    67,    67,    67,    67,
      38,    38,    67,    38,    37,    38,    67,    38
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    64,    65,    65,    66,    66,    66,    66,    66,    66,
      66,    66,    66,    66,    66,    66,    66,    66,    66,    66,
      66,    67,    67,    68,    69,    70,    71,    71,    72,    72,
      73,    73,    74,    74,    74,    74,    74,    75,    76,    77,
      78,    79,    79,    80,    80,    81,    82,    82,    83,    84,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    92,
      92,    93,    94,    95,    96,    97,    98,    99,   100,   101,
     102,   103,   104,   105,   106
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     2,     0,     2,
       0,     1,     0,     2,     2,     2,     2,     9,     6,     6,
       7,     0,     2,     0,     2,     6,     0,     2,     2,     0,
       2,     8,     9,     4,     4,     4,     3,     6,     0,     2,
       2,     5,     4,     7,     9,     9,     3,     5,     3,     8,
       4,     6,     4,     9,     8
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
      yyerror (currSession, YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
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
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


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


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

__attribute__((__unused__))
static unsigned
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  unsigned res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
 }

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, Location, currSession); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, Session* currSession)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  YYUSE (yylocationp);
  YYUSE (currSession);
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
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, Session* currSession)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp, currSession);
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule, Session* currSession)
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
                       , &(yylsp[(yyi + 1) - (yynrhs)])                       , currSession);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule, currSession); \
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

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, Session* currSession)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  YYUSE (currSession);
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

int
yyparse (Session* currSession)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.
       'yyls': related to locations.

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
     '$$ = $1'.

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
        case 21:
#line 120 "C:\\Users\\dieppedalle\\Documents\\nomeProject\\nome\\compilerNome\\parser.y" /* yacc.c:1646  */
    {
        (yyval.numPos.number) = (yyvsp[0].number);
        (yyval.numPos.string) = NULL;
    }
#line 1651 "C:\\Users\\dieppedalle\\Documents\\nomeProject\\nome\\compilerNome\\parser.cpp" /* yacc.c:1646  */
    break;

  case 22:
#line 124 "C:\\Users\\dieppedalle\\Documents\\nomeProject\\nome\\compilerNome\\parser.y" /* yacc.c:1646  */
    {
        (yyval.numPos.string) = (yyvsp[0].string);
        (yyval.numPos.number) = 0;
    }
#line 1660 "C:\\Users\\dieppedalle\\Documents\\nomeProject\\nome\\compilerNome\\parser.cpp" /* yacc.c:1646  */
    break;

  case 23:
#line 133 "C:\\Users\\dieppedalle\\Documents\\nomeProject\\nome\\compilerNome\\parser.y" /* yacc.c:1646  */
    {
        (yyval.number) = (double)atof((yyvsp[0].string));
    }
#line 1668 "C:\\Users\\dieppedalle\\Documents\\nomeProject\\nome\\compilerNome\\parser.cpp" /* yacc.c:1646  */
    break;

  case 24:
#line 140 "C:\\Users\\dieppedalle\\Documents\\nomeProject\\nome\\compilerNome\\parser.y" /* yacc.c:1646  */
    {
        (yyval.numPos.string) = strdup((yyvsp[0].string));
        (yyval.numPos.number) = nomcolumn;
    }
#line 1677 "C:\\Users\\dieppedalle\\Documents\\nomeProject\\nome\\compilerNome\\parser.cpp" /* yacc.c:1646  */
    break;

  case 25:
#line 148 "C:\\Users\\dieppedalle\\Documents\\nomeProject\\nome\\compilerNome\\parser.y" /* yacc.c:1646  */
    {
    }
#line 1684 "C:\\Users\\dieppedalle\\Documents\\nomeProject\\nome\\compilerNome\\parser.cpp" /* yacc.c:1646  */
    break;

  case 27:
#line 155 "C:\\Users\\dieppedalle\\Documents\\nomeProject\\nome\\compilerNome\\parser.y" /* yacc.c:1646  */
    {
        tempVariables2.push_back((yyvsp[0].string));
    }
#line 1692 "C:\\Users\\dieppedalle\\Documents\\nomeProject\\nome\\compilerNome\\parser.cpp" /* yacc.c:1646  */
    break;

  case 28:
#line 161 "C:\\Users\\dieppedalle\\Documents\\nomeProject\\nome\\compilerNome\\parser.y" /* yacc.c:1646  */
    {(yyval.string) = "";}
#line 1698 "C:\\Users\\dieppedalle\\Documents\\nomeProject\\nome\\compilerNome\\parser.cpp" /* yacc.c:1646  */
    break;

  case 29:
#line 162 "C:\\Users\\dieppedalle\\Documents\\nomeProject\\nome\\compilerNome\\parser.y" /* yacc.c:1646  */
    {
        (yyval.string) = (yyvsp[0].string);
    }
#line 1706 "C:\\Users\\dieppedalle\\Documents\\nomeProject\\nome\\compilerNome\\parser.cpp" /* yacc.c:1646  */
    break;

  case 30:
#line 168 "C:\\Users\\dieppedalle\\Documents\\nomeProject\\nome\\compilerNome\\parser.y" /* yacc.c:1646  */
    {(yyval.boolean) = false;}
#line 1712 "C:\\Users\\dieppedalle\\Documents\\nomeProject\\nome\\compilerNome\\parser.cpp" /* yacc.c:1646  */
    break;

  case 31:
#line 169 "C:\\Users\\dieppedalle\\Documents\\nomeProject\\nome\\compilerNome\\parser.y" /* yacc.c:1646  */
    {
        (yyval.boolean) = true;
    }
#line 1720 "C:\\Users\\dieppedalle\\Documents\\nomeProject\\nome\\compilerNome\\parser.cpp" /* yacc.c:1646  */
    break;

  case 37:
#line 180 "C:\\Users\\dieppedalle\\Documents\\nomeProject\\nome\\compilerNome\\parser.y" /* yacc.c:1646  */
    {
        double *x = (double*) malloc(sizeof(double));
        double *y = (double*) malloc(sizeof(double));
        double *z = (double*) malloc(sizeof(double));
        double *angle = (double*) malloc(sizeof(double));


        if ((yyvsp[-6].numPos.string) == NULL){
            *x = (yyvsp[-6].numPos.number);
        }
        else{
            x = getBankValue((yyvsp[-6].numPos.string), currSession);
        }

        if ((yyvsp[-5].numPos.string) == NULL){
            *y = (yyvsp[-5].numPos.number);
        }
        else{
            y = getBankValue((yyvsp[-5].numPos.string), currSession);
        }

        if ((yyvsp[-4].numPos.string) == NULL){
            *z = (yyvsp[-4].numPos.number);
        }
        else{
            z = getBankValue((yyvsp[-4].numPos.string), currSession);
        }

        if ((yyvsp[-1].numPos.string) == NULL){
            *angle = (yyvsp[-1].numPos.number);
        }
        else{
            angle = getBankValue((yyvsp[-1].numPos.string), currSession);
        }

        currentTransformations2.push_back(createRotate(x, y, z, angle));

    }
#line 1763 "C:\\Users\\dieppedalle\\Documents\\nomeProject\\nome\\compilerNome\\parser.cpp" /* yacc.c:1646  */
    break;

  case 38:
#line 222 "C:\\Users\\dieppedalle\\Documents\\nomeProject\\nome\\compilerNome\\parser.y" /* yacc.c:1646  */
    {
        double *x = (double*) malloc(sizeof(double));
        double *y = (double*) malloc(sizeof(double));
        double *z = (double*) malloc(sizeof(double));


        if ((yyvsp[-3].numPos.string) == NULL){
            *x = (yyvsp[-3].numPos.number);
        }
        else{
            x = getBankValue((yyvsp[-3].numPos.string), currSession);
        }

        if ((yyvsp[-2].numPos.string) == NULL){
            *y = (yyvsp[-2].numPos.number);
        }
        else{
            y = getBankValue((yyvsp[-2].numPos.string), currSession);
        }

        if ((yyvsp[-1].numPos.string) == NULL){
            *z = (yyvsp[-1].numPos.number);
        }
        else{
            z = getBankValue((yyvsp[-1].numPos.string), currSession);
        }

        currentTransformations2.push_back(createTranslate(x, y, z));
    }
#line 1797 "C:\\Users\\dieppedalle\\Documents\\nomeProject\\nome\\compilerNome\\parser.cpp" /* yacc.c:1646  */
    break;

  case 39:
#line 255 "C:\\Users\\dieppedalle\\Documents\\nomeProject\\nome\\compilerNome\\parser.y" /* yacc.c:1646  */
    {
        double *x = (double*) malloc(sizeof(double));
        double *y = (double*) malloc(sizeof(double));
        double *z = (double*) malloc(sizeof(double));


        if ((yyvsp[-3].numPos.string) == NULL){
            *x = (yyvsp[-3].numPos.number);
        }
        else{
            x = getBankValue((yyvsp[-3].numPos.string), currSession);
        }

        if ((yyvsp[-2].numPos.string) == NULL){
            *y = (yyvsp[-2].numPos.number);
        }
        else{
            y = getBankValue((yyvsp[-2].numPos.string), currSession);
        }

        if ((yyvsp[-1].numPos.string) == NULL){
            *z = (yyvsp[-1].numPos.number);
        }
        else{
            z = getBankValue((yyvsp[-1].numPos.string), currSession);
        }

        currentTransformations2.push_back(createScale(x, y, z));
    }
#line 1831 "C:\\Users\\dieppedalle\\Documents\\nomeProject\\nome\\compilerNome\\parser.cpp" /* yacc.c:1646  */
    break;

  case 40:
#line 288 "C:\\Users\\dieppedalle\\Documents\\nomeProject\\nome\\compilerNome\\parser.y" /* yacc.c:1646  */
    {
        double x = (yyvsp[-4].numPos.number);
        double y = (yyvsp[-3].numPos.number);
        double z = (yyvsp[-2].numPos.number);
        double w = (yyvsp[-2].numPos.number);

    }
#line 1843 "C:\\Users\\dieppedalle\\Documents\\nomeProject\\nome\\compilerNome\\parser.cpp" /* yacc.c:1646  */
    break;

  case 45:
#line 307 "C:\\Users\\dieppedalle\\Documents\\nomeProject\\nome\\compilerNome\\parser.y" /* yacc.c:1646  */
    {
        Reader* currReader = createReader(currSession);
        string instanceName = strdup((yyvsp[-4].string));
        string lookFor = strdup((yyvsp[-3].string));

        MeshNew * currentMesh = currReader->getMesh((yyvsp[-3].string));

        InstanceNew* newInstance;
        if (currentMesh != NULL) {
            newInstance = createInstance(currentMesh, currSession->verts, currReader, false);
            newInstance->setName(strdup((yyvsp[-4].string)));
        }
        else{
            nomerror(currSession, "Incorrect vertex, face, or mesh name");
            YYABORT;
        }

        newInstance->transformations = currentTransformations2;
        currentTransformations2.clear();

        for (TransformationNew * t : newInstance->transformations){
            newInstance->applyTransformation(t);
        }

        string surfaceName = (yyvsp[-2].string);
        // Check if a surface has been applied.
        if (surfaceName.length() != 0){
            Surface * currentSurface = currReader->surf((yyvsp[-2].string));
            if (currentSurface != NULL) {
                setSurface(newInstance, currentSurface);
            }
            else{
                nomerror(currSession, "Incorrect surface name");
                YYABORT;
            }
        }

        currentGroup2.push_back(newInstance);
    }
#line 1887 "C:\\Users\\dieppedalle\\Documents\\nomeProject\\nome\\compilerNome\\parser.cpp" /* yacc.c:1646  */
    break;

  case 48:
#line 354 "C:\\Users\\dieppedalle\\Documents\\nomeProject\\nome\\compilerNome\\parser.y" /* yacc.c:1646  */
    {
        string instanceName = strdup((yyvsp[0].string));
    }
#line 1895 "C:\\Users\\dieppedalle\\Documents\\nomeProject\\nome\\compilerNome\\parser.cpp" /* yacc.c:1646  */
    break;

  case 51:
#line 364 "C:\\Users\\dieppedalle\\Documents\\nomeProject\\nome\\compilerNome\\parser.y" /* yacc.c:1646  */
    {
        double *subdivision = (double*) malloc(sizeof(double));


        if ((yyvsp[-1].numPos.string) == NULL){
            *subdivision = (yyvsp[-1].numPos.number);
        }
        else{
            subdivision = getBankValue((yyvsp[-1].numPos.string), currSession);
        }

        SubdivisionNew* currSubdivision = createSubdivision(strdup((yyvsp[-5].string)), strdup((yyvsp[-3].string)), subdivision);
        currSession->subdivisions.push_back(currSubdivision);
    }
#line 1914 "C:\\Users\\dieppedalle\\Documents\\nomeProject\\nome\\compilerNome\\parser.cpp" /* yacc.c:1646  */
    break;

  case 52:
#line 381 "C:\\Users\\dieppedalle\\Documents\\nomeProject\\nome\\compilerNome\\parser.y" /* yacc.c:1646  */
    {
        double *min = (double*) malloc(sizeof(double));
        double *max = (double*) malloc(sizeof(double));
        double *step = (double*) malloc(sizeof(double));


        if ((yyvsp[-5].numPos.string) == NULL){
            *min = (yyvsp[-5].numPos.number);
        }
        else{
            min = getBankValue((yyvsp[-5].numPos.string), currSession);
        }

        if ((yyvsp[-3].numPos.string) == NULL){
            *max = (yyvsp[-3].numPos.number);
        }
        else{
            max = getBankValue((yyvsp[-3].numPos.string), currSession);
        }

        if ((yyvsp[-1].numPos.string) == NULL){
            *step = (yyvsp[-1].numPos.number);
        }
        else{
            step = getBankValue((yyvsp[-1].numPos.string), currSession);
        }

        OffsetNew* currOffset = createOffset(strdup((yyvsp[-7].string)), min, max, step);

        currSession->offsets.push_back(currOffset);
    }
#line 1950 "C:\\Users\\dieppedalle\\Documents\\nomeProject\\nome\\compilerNome\\parser.cpp" /* yacc.c:1646  */
    break;

  case 53:
#line 415 "C:\\Users\\dieppedalle\\Documents\\nomeProject\\nome\\compilerNome\\parser.y" /* yacc.c:1646  */
    {

        MeshNew* currMesh = createMesh();

        for (std::list<FaceNew*>::iterator it=currentMeshFaces2.begin(); it != currentMeshFaces2.end(); ++it){
            currMesh->faces.push_back(*it);
        }

        for (std::list<Vert*>::iterator it=currentMeshVertices2.begin(); it != currentMeshVertices2.end(); ++it){
            currMesh->verts.push_back(*it);
        }

        for (std::list<EdgeNew*>::iterator it=currentMeshEdges2.begin(); it != currentMeshEdges2.end(); ++it){
            currMesh->edges.push_back(*it);
        }

        currMesh->setName(strdup((yyvsp[-2].string)));
        currSession->meshes.push_back(currMesh);

        currentMeshFaces2.clear();
        currentMeshEdges2.clear();
        currentMeshVertices2.clear();
	}
#line 1978 "C:\\Users\\dieppedalle\\Documents\\nomeProject\\nome\\compilerNome\\parser.cpp" /* yacc.c:1646  */
    break;

  case 54:
#line 442 "C:\\Users\\dieppedalle\\Documents\\nomeProject\\nome\\compilerNome\\parser.y" /* yacc.c:1646  */
    {
        GroupNew* currGroup = createGroup(currentGroup2);
        currGroup->setName(strdup((yyvsp[-2].string)));
        currSession->groups.push_back(currGroup);
        currentGroup2.clear();
	}
#line 1989 "C:\\Users\\dieppedalle\\Documents\\nomeProject\\nome\\compilerNome\\parser.cpp" /* yacc.c:1646  */
    break;

  case 55:
#line 452 "C:\\Users\\dieppedalle\\Documents\\nomeProject\\nome\\compilerNome\\parser.y" /* yacc.c:1646  */
    {
        (yyval.string) = (yyvsp[-1].string);
    }
#line 1997 "C:\\Users\\dieppedalle\\Documents\\nomeProject\\nome\\compilerNome\\parser.cpp" /* yacc.c:1646  */
    break;

  case 56:
#line 458 "C:\\Users\\dieppedalle\\Documents\\nomeProject\\nome\\compilerNome\\parser.y" /* yacc.c:1646  */
    {
        Reader* currReader = createReader(currSession);

        for (std::string currFace : tempFaceDelete2){
            currReader->deleteFace(currReader->getFace(currFace));
        }

        tempFaceDelete2.clear();
	}
#line 2011 "C:\\Users\\dieppedalle\\Documents\\nomeProject\\nome\\compilerNome\\parser.cpp" /* yacc.c:1646  */
    break;

  case 57:
#line 471 "C:\\Users\\dieppedalle\\Documents\\nomeProject\\nome\\compilerNome\\parser.y" /* yacc.c:1646  */
    {
        string currentSetName = (yyvsp[-4].string);
        double currentSetValue = (double)atof((yyvsp[-3].numPos.string));
        double currentSetStart = (yyvsp[-2].numPos.number);
        double currentSetEnd = (yyvsp[-1].numPos.number);
        double currentSetStepSize = (yyvsp[0].numPos.number);
        string currentSetValueString = (yyvsp[-3].numPos.string);

        int begPos = (yyvsp[-3].numPos.number)-currentSetValueString.length();
        int lengthValChar = currentSetValueString.length();

        SetNew * currentSet = createSet(currentSetName, currentSetValue, currentSetStart, currentSetEnd, currentSetStepSize, begPos, lengthValChar);

        currentSetList2.push_back(currentSet);
	}
#line 2031 "C:\\Users\\dieppedalle\\Documents\\nomeProject\\nome\\compilerNome\\parser.cpp" /* yacc.c:1646  */
    break;

  case 61:
#line 494 "C:\\Users\\dieppedalle\\Documents\\nomeProject\\nome\\compilerNome\\parser.y" /* yacc.c:1646  */
    {
        Reader* currReader = createReader(currSession);

        //std::cout << "Create face mesh" << std::endl;
        std::list<Vert*> verticesFace;

        for (std::vector<string>::iterator it = tempVariables2.begin() ; it != tempVariables2.end(); ++it){
            Vert * currentVertex = currReader->getVert(*it);

            if (currentVertex != NULL) {
                verticesFace.push_back(currentVertex);
                bool found = false;
                for (Vert* currentMeshVertex: currentMeshVertices2){
                    if (currentMeshVertex->index == currentVertex->index){
                        found = true;
                    }
                }
                if (found == false){
                    currentMeshVertices2.push_back(currentVertex);
                }

            }
            else{
                nomerror(currSession, "Incorrect vertex name");
                YYABORT;
            }
        }

        FaceNew * newFace = createFace(verticesFace, &currentMeshEdges2, currReader, false);
        setName(newFace, strdup((yyvsp[-3].string)));

        string surfaceName = (yyvsp[-1].string);
        // Check if a surface has been applied.
        if (surfaceName.length() != 0){
            Surface * currentSurface = currReader->surf((yyvsp[-1].string));
            if (currentSurface != NULL) {
                setSurface(newFace, currentSurface);
            }
            else{
                nomerror(currSession, "Incorrect surface name");
                YYABORT;
            }
        }

        currentMeshFaces2.push_back(newFace);

        tempVariables2.clear();
    }
#line 2084 "C:\\Users\\dieppedalle\\Documents\\nomeProject\\nome\\compilerNome\\parser.cpp" /* yacc.c:1646  */
    break;

  case 62:
#line 546 "C:\\Users\\dieppedalle\\Documents\\nomeProject\\nome\\compilerNome\\parser.y" /* yacc.c:1646  */
    {
        BankNew * currentBank2 = createBank();
        currentBank2->name = strdup((yyvsp[-2].string));
        currentBank2->sets = currentSetList2;
        currSession->banks.push_back(currentBank2);
        currentSetList2.clear();
	}
#line 2096 "C:\\Users\\dieppedalle\\Documents\\nomeProject\\nome\\compilerNome\\parser.cpp" /* yacc.c:1646  */
    break;

  case 63:
#line 557 "C:\\Users\\dieppedalle\\Documents\\nomeProject\\nome\\compilerNome\\parser.y" /* yacc.c:1646  */
    {
        string name = (yyvsp[-5].string);
        double *num = (double*) malloc(sizeof(double));
        double *rad = (double*) malloc(sizeof(double));


        if ((yyvsp[-3].numPos.string) == NULL){
            *num = (yyvsp[-3].numPos.number);
        }
        else{
            num = getBankValue((yyvsp[-3].numPos.string), currSession);
        }

        if ((yyvsp[-2].numPos.string) == NULL){
            *rad = (yyvsp[-2].numPos.number);
        }
        else{
            rad = getBankValue((yyvsp[-2].numPos.string), currSession);
        }

        CircleNew* currCircle = createCircle(num, rad);
        currCircle->setName(strdup((yyvsp[-5].string)));

        currSession->circles.push_back(currCircle);
    }
#line 2126 "C:\\Users\\dieppedalle\\Documents\\nomeProject\\nome\\compilerNome\\parser.cpp" /* yacc.c:1646  */
    break;

  case 64:
#line 586 "C:\\Users\\dieppedalle\\Documents\\nomeProject\\nome\\compilerNome\\parser.y" /* yacc.c:1646  */
    {
        Reader* currReader = createReader(currSession);

        string name = (yyvsp[-7].string);
        double *n = (double*) malloc(sizeof(double));
        double *ro = (double*) malloc(sizeof(double));
        double *ratio = (double*) malloc(sizeof(double));
        double *h = (double*) malloc(sizeof(double));

        if ((yyvsp[-5].numPos.string) == NULL){
            *n = (yyvsp[-5].numPos.number);
        }
        else{
            n = getBankValue((yyvsp[-5].numPos.string), currSession);
        }

        if ((yyvsp[-4].numPos.string) == NULL){
            *ro = (yyvsp[-4].numPos.number);
        }
        else{
            ro = getBankValue((yyvsp[-4].numPos.string), currSession);
        }

        if ((yyvsp[-3].numPos.string) == NULL){
            *ratio = (yyvsp[-3].numPos.number);
        }
        else{
            ratio = getBankValue((yyvsp[-3].numPos.string), currSession);
        }

        if ((yyvsp[-2].numPos.string) == NULL){
            *h = (yyvsp[-2].numPos.number);
        }
        else{
            h = getBankValue((yyvsp[-2].numPos.string), currSession);
        }

        TunnelNew* currTunnel = createTunnel(n, ro, ratio, h, currReader);
        currTunnel->setName(strdup((yyvsp[-7].string)));

        currSession->tunnels.push_back(currTunnel);
	}
#line 2173 "C:\\Users\\dieppedalle\\Documents\\nomeProject\\nome\\compilerNome\\parser.cpp" /* yacc.c:1646  */
    break;

  case 65:
#line 633 "C:\\Users\\dieppedalle\\Documents\\nomeProject\\nome\\compilerNome\\parser.y" /* yacc.c:1646  */
    {
        Reader* currReader = createReader(currSession);

        string name = (yyvsp[-7].string);
        double *n = (double*) malloc(sizeof(double));
        double *ro = (double*) malloc(sizeof(double));
        double *ratio = (double*) malloc(sizeof(double));
        double *h = (double*) malloc(sizeof(double));

        if ((yyvsp[-5].numPos.string) == NULL){
            *n = (yyvsp[-5].numPos.number);
        }
        else{
            n = getBankValue((yyvsp[-5].numPos.string), currSession);
        }

        if ((yyvsp[-4].numPos.string) == NULL){
            *ro = (yyvsp[-4].numPos.number);
        }
        else{
            ro = getBankValue((yyvsp[-4].numPos.string), currSession);
        }

        if ((yyvsp[-3].numPos.string) == NULL){
            *ratio = (yyvsp[-3].numPos.number);
        }
        else{
            ratio = getBankValue((yyvsp[-3].numPos.string), currSession);
        }

        if ((yyvsp[-2].numPos.string) == NULL){
            *h = (yyvsp[-2].number);
        }
        else{
            h = getBankValue((yyvsp[-2].numPos.string), currSession);
        }

        FunnelNew* currFunnel = createFunnel(n, ro, ratio, h, currReader);
        currFunnel->setName(strdup((yyvsp[-7].string)));

        currSession->funnels.push_back(currFunnel);
	}
#line 2220 "C:\\Users\\dieppedalle\\Documents\\nomeProject\\nome\\compilerNome\\parser.cpp" /* yacc.c:1646  */
    break;

  case 66:
#line 679 "C:\\Users\\dieppedalle\\Documents\\nomeProject\\nome\\compilerNome\\parser.y" /* yacc.c:1646  */
    {
	}
#line 2227 "C:\\Users\\dieppedalle\\Documents\\nomeProject\\nome\\compilerNome\\parser.cpp" /* yacc.c:1646  */
    break;

  case 67:
#line 685 "C:\\Users\\dieppedalle\\Documents\\nomeProject\\nome\\compilerNome\\parser.y" /* yacc.c:1646  */
    {
        Reader* currReader = createReader(currSession);

        std::list<Vert*> verticesFace;
        for (std::vector<string>::iterator it = tempVariables2.begin() ; it != tempVariables2.end(); ++it){
            Vert * currentVertex = currReader->vert(*it);
            if (currentVertex != NULL) {
                verticesFace.push_back(currentVertex);
            }
            else{
                nomerror(currSession, "Incorrect vertex name");
                YYABORT;
            }
        }

        FaceNew * newFace = createFace(verticesFace, &(currSession->edges), currReader, false);

        setName(newFace, strdup((yyvsp[-3].string)));


        string surfaceName = (yyvsp[-1].string);
        // Check if a surface has been applied.
        if (surfaceName.length() != 0){
            Surface * currentSurface = currReader->surf((yyvsp[-1].string));
            if (currentSurface != NULL) {
                setSurface(newFace, currentSurface);
            }
            else{
                nomerror(currSession, "Incorrect surface name");
                YYABORT;
            }
        }

        currSession->faces.push_back(newFace);

        tempVariables2.clear();
	}
#line 2269 "C:\\Users\\dieppedalle\\Documents\\nomeProject\\nome\\compilerNome\\parser.cpp" /* yacc.c:1646  */
    break;

  case 68:
#line 726 "C:\\Users\\dieppedalle\\Documents\\nomeProject\\nome\\compilerNome\\parser.y" /* yacc.c:1646  */
    {
        tempFaceDelete2.push_back((yyvsp[-1].string));
	}
#line 2277 "C:\\Users\\dieppedalle\\Documents\\nomeProject\\nome\\compilerNome\\parser.cpp" /* yacc.c:1646  */
    break;

  case 69:
#line 732 "C:\\Users\\dieppedalle\\Documents\\nomeProject\\nome\\compilerNome\\parser.y" /* yacc.c:1646  */
    {
    if ((yyvsp[-7].intNumber) != (yyvsp[0].intNumber)) {
        nomerror(currSession, "bspline and endbspline do not have the same number.");
        YYABORT;
    }
    double *slices = (double*) malloc(sizeof(double));

    if ((yyvsp[-4].numPos.string) == NULL){
        *slices = (yyvsp[-4].numPos.number);
    }
    else{
        slices = getBankValue((yyvsp[-4].numPos.string), currSession);
    }

    Reader* currReader = createReader(currSession);

    BSplineNew* currBSpline = createBSplineNew();
    currBSpline->setName(strdup((yyvsp[-6].string)));
    currBSpline->set_order((yyvsp[-7].intNumber));
    currBSpline->segments = slices;

    // Create list of vertices of face.
    for (std::vector<string>::iterator it = tempVariables2.begin() ; it != tempVariables2.end(); ++it){
        Vert * currentVertex = currReader->getVert(*it);
        if (currentVertex != NULL) {
            currBSpline->proxy.push_back(currentVertex);
        }
        else{
            nomerror(currSession, "Incorrect vertex name");
            YYABORT;
        }
    }

    currBSpline->isLoop = (yyvsp[-2].boolean);

    if (currBSpline->order > currBSpline->proxy.size()){
      std::string errorStr = "bspline order (";
      errorStr += currBSpline->order;
      errorStr += ") must be <= #controlpoints (";
      errorStr += currBSpline->proxy.size();
      errorStr += ").";
      nomerror(currSession, errorStr.c_str());
      YYABORT;
    }


    currBSpline->updateBSpline();

    currSession->bsplines.push_back(currBSpline);

    tempVariables2.clear();
  }
#line 2334 "C:\\Users\\dieppedalle\\Documents\\nomeProject\\nome\\compilerNome\\parser.cpp" /* yacc.c:1646  */
    break;

  case 70:
#line 787 "C:\\Users\\dieppedalle\\Documents\\nomeProject\\nome\\compilerNome\\parser.y" /* yacc.c:1646  */
    {
        Reader* currReader = createReader(currSession);

        // Create list of vertices of face.
        std::list<Vert*> verticesPolyline;
        for (std::vector<string>::iterator it = tempVariables2.begin() ; it != tempVariables2.end(); ++it){
            Vert * currentVertex = currReader->getVert(*it);
            if (currentVertex != NULL) {
                verticesPolyline.push_back(currentVertex);
            }
            else{
                nomerror(currSession, "Incorrect vertex name");
                YYABORT;
            }
        }

        PolylineNew* currPolyline = createPolylineNew(verticesPolyline);
        currPolyline->setName(strdup((yyvsp[-2].string)));

        currSession->polylines.push_back(currPolyline);
        tempVariables2.clear();
	}
#line 2361 "C:\\Users\\dieppedalle\\Documents\\nomeProject\\nome\\compilerNome\\parser.cpp" /* yacc.c:1646  */
    break;

  case 71:
#line 813 "C:\\Users\\dieppedalle\\Documents\\nomeProject\\nome\\compilerNome\\parser.y" /* yacc.c:1646  */
    {
        Reader* currReader = createReader(currSession);

        string instanceName = strdup((yyvsp[-4].string));
        string lookFor = strdup((yyvsp[-3].string));

        MeshNew * currentMesh = currReader->getMesh((yyvsp[-3].string));

        InstanceNew* newInstance = NULL;
        if (currentMesh != NULL) {
            newInstance = createInstance(currentMesh, currSession->verts, currReader, true);
        }
        else{
            GroupNew * currentGroup2 = currReader->getGroup((yyvsp[-3].string));
            if (currentGroup2 != NULL) {
                newInstance = createInstance(currentGroup2, currSession->verts, currReader);
            }
            else{
                nomerror(currSession, "Incorrect vertex, face, or mesh name");
                YYABORT;
            }
        }

        newInstance->setName(strdup((yyvsp[-4].string)));
        newInstance->transformations = currentTransformations2;
        currentTransformations2.clear();

        for (TransformationNew * t : newInstance->transformations){
            newInstance->applyTransformation(t);
        }

        string surfaceName = (yyvsp[-2].string);
        // Check if a surface has been applied.
        if (surfaceName.length() != 0){
            Surface * currentSurface = currReader->surf((yyvsp[-2].string));
            if (currentSurface != NULL) {
                setSurface(newInstance, currentSurface);
            }
            else{
                nomerror(currSession, "Incorrect surface name");
                YYABORT;
            }
        }

        currSession->instances.push_back(newInstance);
	}
#line 2412 "C:\\Users\\dieppedalle\\Documents\\nomeProject\\nome\\compilerNome\\parser.cpp" /* yacc.c:1646  */
    break;

  case 72:
#line 863 "C:\\Users\\dieppedalle\\Documents\\nomeProject\\nome\\compilerNome\\parser.y" /* yacc.c:1646  */
    {
	}
#line 2419 "C:\\Users\\dieppedalle\\Documents\\nomeProject\\nome\\compilerNome\\parser.cpp" /* yacc.c:1646  */
    break;

  case 73:
#line 869 "C:\\Users\\dieppedalle\\Documents\\nomeProject\\nome\\compilerNome\\parser.y" /* yacc.c:1646  */
    {
        double *r = (double*) malloc(sizeof(double));
        double *g = (double*) malloc(sizeof(double));
        double *b = (double*) malloc(sizeof(double));

        if ((yyvsp[-4].numPos.string) == NULL){
            *r = (yyvsp[-4].numPos.number);
        }
        else{
            r = getBankValue((yyvsp[-4].numPos.string), currSession);
        }

        if ((yyvsp[-3].numPos.string) == NULL){
            *g = (yyvsp[-3].numPos.number);
        }
        else{
            g = getBankValue((yyvsp[-3].numPos.string), currSession);
        }

        if ((yyvsp[-2].numPos.string) == NULL){
            *b = (yyvsp[-2].numPos.number);
        }
        else{
            b = getBankValue((yyvsp[-2].numPos.string), currSession);
        }

        currSession->surfaces.push_back(createSurface(r, g, b, strdup((yyvsp[-7].string))));
	}
#line 2452 "C:\\Users\\dieppedalle\\Documents\\nomeProject\\nome\\compilerNome\\parser.cpp" /* yacc.c:1646  */
    break;

  case 74:
#line 901 "C:\\Users\\dieppedalle\\Documents\\nomeProject\\nome\\compilerNome\\parser.y" /* yacc.c:1646  */
    {
        double *x = (double*) malloc(sizeof(double));
        double *y = (double*) malloc(sizeof(double));
        double *z = (double*) malloc(sizeof(double));


        if ((yyvsp[-4].numPos.string) == NULL){
            *x = (yyvsp[-4].numPos.number);
        }
        else{
            x = getBankValue((yyvsp[-4].numPos.string), currSession);
        }

        if ((yyvsp[-3].numPos.string) == NULL){
            *y = (yyvsp[-3].numPos.number);
        }
        else{
            y = getBankValue((yyvsp[-3].numPos.string), currSession);
        }

        if ((yyvsp[-2].numPos.string) == NULL){
            *z = (yyvsp[-2].numPos.number);
        }
        else{
            z = getBankValue((yyvsp[-2].numPos.string), currSession);
        }

        Vert * newVertex = createVert (x, y, z);
        newVertex->setName(strdup((yyvsp[-6].string)));
        currSession->verts.push_back(newVertex);
	}
#line 2488 "C:\\Users\\dieppedalle\\Documents\\nomeProject\\nome\\compilerNome\\parser.cpp" /* yacc.c:1646  */
    break;


#line 2492 "C:\\Users\\dieppedalle\\Documents\\nomeProject\\nome\\compilerNome\\parser.cpp" /* yacc.c:1646  */
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
      yyerror (currSession, YY_("syntax error"));
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
        yyerror (currSession, yymsgp);
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
                      yytoken, &yylval, &yylloc, currSession);
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

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp, yylsp, currSession);
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
  yyerror (currSession, YY_("memory exhausted"));
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
                  yytoken, &yylval, &yylloc, currSession);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp, yylsp, currSession);
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
