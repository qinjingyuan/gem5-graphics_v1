/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2011 Free Software Foundation, Inc.
   
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
#define YYBISON_VERSION "2.5"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 1

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 1

/* Substitute the variable and function names.  */
#define yyparse         _mesa_glsl_parse
#define yylex           _mesa_glsl_lex
#define yyerror         _mesa_glsl_error
#define yylval          _mesa_glsl_lval
#define yychar          _mesa_glsl_char
#define yydebug         _mesa_glsl_debug
#define yynerrs         _mesa_glsl_nerrs
#define yylloc          _mesa_glsl_lloc

/* Copy the first part of user declarations.  */

/* Line 268 of yacc.c  */
#line 1 "glsl_parser.yy"

/*
 * Copyright © 2008, 2009 Intel Corporation
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
    
#include "ast.h"
#include "glsl_parser_extras.h"
#include "glsl_types.h"

#define YYLEX_PARAM state->scanner



/* Line 268 of yacc.c  */
#line 116 "glsl_parser.cpp"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     ATTRIBUTE = 258,
     CONST_TOK = 259,
     BOOL_TOK = 260,
     FLOAT_TOK = 261,
     INT_TOK = 262,
     UINT_TOK = 263,
     BREAK = 264,
     CONTINUE = 265,
     DO = 266,
     ELSE = 267,
     FOR = 268,
     IF = 269,
     DISCARD = 270,
     RETURN = 271,
     SWITCH = 272,
     CASE = 273,
     DEFAULT = 274,
     BVEC2 = 275,
     BVEC3 = 276,
     BVEC4 = 277,
     IVEC2 = 278,
     IVEC3 = 279,
     IVEC4 = 280,
     UVEC2 = 281,
     UVEC3 = 282,
     UVEC4 = 283,
     VEC2 = 284,
     VEC3 = 285,
     VEC4 = 286,
     CENTROID = 287,
     IN_TOK = 288,
     OUT_TOK = 289,
     INOUT_TOK = 290,
     UNIFORM = 291,
     VARYING = 292,
     NOPERSPECTIVE = 293,
     FLAT = 294,
     SMOOTH = 295,
     MAT2X2 = 296,
     MAT2X3 = 297,
     MAT2X4 = 298,
     MAT3X2 = 299,
     MAT3X3 = 300,
     MAT3X4 = 301,
     MAT4X2 = 302,
     MAT4X3 = 303,
     MAT4X4 = 304,
     SAMPLER1D = 305,
     SAMPLER2D = 306,
     SAMPLER3D = 307,
     SAMPLERCUBE = 308,
     SAMPLER1DSHADOW = 309,
     SAMPLER2DSHADOW = 310,
     SAMPLERCUBESHADOW = 311,
     SAMPLER1DARRAY = 312,
     SAMPLER2DARRAY = 313,
     SAMPLER1DARRAYSHADOW = 314,
     SAMPLER2DARRAYSHADOW = 315,
     ISAMPLER1D = 316,
     ISAMPLER2D = 317,
     ISAMPLER3D = 318,
     ISAMPLERCUBE = 319,
     ISAMPLER1DARRAY = 320,
     ISAMPLER2DARRAY = 321,
     USAMPLER1D = 322,
     USAMPLER2D = 323,
     USAMPLER3D = 324,
     USAMPLERCUBE = 325,
     USAMPLER1DARRAY = 326,
     USAMPLER2DARRAY = 327,
     STRUCT = 328,
     VOID_TOK = 329,
     WHILE = 330,
     IDENTIFIER = 331,
     TYPE_IDENTIFIER = 332,
     NEW_IDENTIFIER = 333,
     FLOATCONSTANT = 334,
     INTCONSTANT = 335,
     UINTCONSTANT = 336,
     BOOLCONSTANT = 337,
     FIELD_SELECTION = 338,
     LEFT_OP = 339,
     RIGHT_OP = 340,
     INC_OP = 341,
     DEC_OP = 342,
     LE_OP = 343,
     GE_OP = 344,
     EQ_OP = 345,
     NE_OP = 346,
     AND_OP = 347,
     OR_OP = 348,
     XOR_OP = 349,
     MUL_ASSIGN = 350,
     DIV_ASSIGN = 351,
     ADD_ASSIGN = 352,
     MOD_ASSIGN = 353,
     LEFT_ASSIGN = 354,
     RIGHT_ASSIGN = 355,
     AND_ASSIGN = 356,
     XOR_ASSIGN = 357,
     OR_ASSIGN = 358,
     SUB_ASSIGN = 359,
     INVARIANT = 360,
     LOWP = 361,
     MEDIUMP = 362,
     HIGHP = 363,
     SUPERP = 364,
     PRECISION = 365,
     VERSION = 366,
     EXTENSION = 367,
     LINE = 368,
     COLON = 369,
     EOL = 370,
     INTERFACE = 371,
     OUTPUT = 372,
     PRAGMA_DEBUG_ON = 373,
     PRAGMA_DEBUG_OFF = 374,
     PRAGMA_OPTIMIZE_ON = 375,
     PRAGMA_OPTIMIZE_OFF = 376,
     PRAGMA_INVARIANT_ALL = 377,
     LAYOUT_TOK = 378,
     ASM = 379,
     CLASS = 380,
     UNION = 381,
     ENUM = 382,
     TYPEDEF = 383,
     TEMPLATE = 384,
     THIS = 385,
     PACKED_TOK = 386,
     GOTO = 387,
     INLINE_TOK = 388,
     NOINLINE = 389,
     VOLATILE = 390,
     PUBLIC_TOK = 391,
     STATIC = 392,
     EXTERN = 393,
     EXTERNAL = 394,
     LONG_TOK = 395,
     SHORT_TOK = 396,
     DOUBLE_TOK = 397,
     HALF = 398,
     FIXED_TOK = 399,
     UNSIGNED = 400,
     INPUT_TOK = 401,
     OUPTUT = 402,
     HVEC2 = 403,
     HVEC3 = 404,
     HVEC4 = 405,
     DVEC2 = 406,
     DVEC3 = 407,
     DVEC4 = 408,
     FVEC2 = 409,
     FVEC3 = 410,
     FVEC4 = 411,
     SAMPLER2DRECT = 412,
     SAMPLER3DRECT = 413,
     SAMPLER2DRECTSHADOW = 414,
     SIZEOF = 415,
     CAST = 416,
     NAMESPACE = 417,
     USING = 418,
     ERROR_TOK = 419,
     COMMON = 420,
     PARTITION = 421,
     ACTIVE = 422,
     SAMPLERBUFFER = 423,
     FILTER = 424,
     IMAGE1D = 425,
     IMAGE2D = 426,
     IMAGE3D = 427,
     IMAGECUBE = 428,
     IMAGE1DARRAY = 429,
     IMAGE2DARRAY = 430,
     IIMAGE1D = 431,
     IIMAGE2D = 432,
     IIMAGE3D = 433,
     IIMAGECUBE = 434,
     IIMAGE1DARRAY = 435,
     IIMAGE2DARRAY = 436,
     UIMAGE1D = 437,
     UIMAGE2D = 438,
     UIMAGE3D = 439,
     UIMAGECUBE = 440,
     UIMAGE1DARRAY = 441,
     UIMAGE2DARRAY = 442,
     IMAGE1DSHADOW = 443,
     IMAGE2DSHADOW = 444,
     IMAGEBUFFER = 445,
     IIMAGEBUFFER = 446,
     UIMAGEBUFFER = 447,
     IMAGE1DARRAYSHADOW = 448,
     IMAGE2DARRAYSHADOW = 449,
     ROW_MAJOR = 450
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 293 of yacc.c  */
#line 52 "glsl_parser.yy"

   int n;
   float real;
   char *identifier;

   struct ast_type_qualifier type_qualifier;

   ast_node *node;
   ast_type_specifier *type_specifier;
   ast_fully_specified_type *fully_specified_type;
   ast_function *function;
   ast_parameter_declarator *parameter_declarator;
   ast_function_definition *function_definition;
   ast_compound_statement *compound_statement;
   ast_expression *expression;
   ast_declarator_list *declarator_list;
   ast_struct_specifier *struct_specifier;
   ast_declaration *declaration;

   struct {
      ast_node *cond;
      ast_expression *rest;
   } for_rest_statement;

   struct {
      ast_node *then_statement;
      ast_node *else_statement;
   } selection_rest_statement;



/* Line 293 of yacc.c  */
#line 379 "glsl_parser.cpp"
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


/* Copy the second part of user declarations.  */


/* Line 343 of yacc.c  */
#line 404 "glsl_parser.cpp"

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
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
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
/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   3692

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  220
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  93
/* YYNRULES -- Number of rules.  */
#define YYNRULES  291
/* YYNRULES -- Number of states.  */
#define YYNSTATES  434

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   450

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   204,     2,     2,     2,   208,   211,     2,
     196,   197,   206,   202,   201,   203,   200,   207,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,   215,   217,
     209,   216,   210,   214,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   198,     2,   199,   212,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   218,   213,   219,   205,     2,     2,     2,
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
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   148,   149,   150,   151,   152,   153,   154,
     155,   156,   157,   158,   159,   160,   161,   162,   163,   164,
     165,   166,   167,   168,   169,   170,   171,   172,   173,   174,
     175,   176,   177,   178,   179,   180,   181,   182,   183,   184,
     185,   186,   187,   188,   189,   190,   191,   192,   193,   194,
     195
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     4,     9,    10,    14,    17,    20,    23,
      26,    29,    30,    33,    35,    37,    39,    45,    47,    50,
      52,    54,    56,    58,    60,    62,    64,    68,    70,    75,
      77,    81,    84,    87,    89,    91,    93,    97,   100,   103,
     106,   108,   111,   115,   118,   120,   122,   124,   127,   130,
     133,   135,   138,   142,   145,   147,   150,   153,   156,   158,
     160,   162,   164,   166,   170,   174,   178,   180,   184,   188,
     190,   194,   198,   200,   204,   208,   212,   216,   218,   222,
     226,   228,   232,   234,   238,   240,   244,   246,   250,   252,
     256,   258,   262,   264,   270,   272,   276,   278,   280,   282,
     284,   286,   288,   290,   292,   294,   296,   298,   300,   304,
     306,   309,   312,   317,   320,   322,   324,   327,   331,   335,
     338,   344,   348,   351,   355,   358,   359,   361,   363,   365,
     367,   369,   373,   379,   386,   394,   403,   409,   411,   414,
     419,   425,   432,   440,   445,   448,   450,   453,   458,   460,
     464,   466,   470,   472,   474,   476,   478,   480,   482,   485,
     487,   490,   493,   497,   499,   501,   503,   505,   508,   510,
     512,   515,   518,   520,   522,   525,   527,   531,   536,   538,
     540,   542,   544,   546,   548,   550,   552,   554,   556,   558,
     560,   562,   564,   566,   568,   570,   572,   574,   576,   578,
     580,   582,   584,   586,   588,   590,   592,   594,   596,   598,
     600,   602,   604,   606,   608,   610,   612,   614,   616,   618,
     620,   622,   624,   626,   628,   630,   632,   634,   636,   638,
     640,   642,   644,   646,   648,   650,   656,   661,   663,   666,
     670,   672,   676,   678,   683,   685,   687,   689,   691,   693,
     695,   697,   699,   701,   703,   705,   708,   709,   714,   716,
     718,   721,   725,   727,   730,   732,   735,   741,   745,   747,
     749,   754,   760,   764,   767,   773,   781,   788,   790,   792,
     794,   795,   798,   802,   805,   808,   811,   815,   818,   820,
     822,   824
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     221,     0,    -1,    -1,   223,   225,   222,   228,    -1,    -1,
     111,    80,   115,    -1,   118,   115,    -1,   119,   115,    -1,
     120,   115,    -1,   121,   115,    -1,   122,   115,    -1,    -1,
     225,   227,    -1,    76,    -1,    77,    -1,    78,    -1,   112,
     226,   114,   226,   115,    -1,   311,    -1,   228,   311,    -1,
      76,    -1,    78,    -1,   229,    -1,    80,    -1,    81,    -1,
      79,    -1,    82,    -1,   196,   260,   197,    -1,   230,    -1,
     231,   198,   232,   199,    -1,   233,    -1,   231,   200,   226,
      -1,   231,    86,    -1,   231,    87,    -1,   260,    -1,   234,
      -1,   235,    -1,   231,   200,   240,    -1,   237,   197,    -1,
     236,   197,    -1,   238,    74,    -1,   238,    -1,   238,   258,
      -1,   237,   201,   258,    -1,   239,   196,    -1,   281,    -1,
     229,    -1,    83,    -1,   242,   197,    -1,   241,   197,    -1,
     243,    74,    -1,   243,    -1,   243,   258,    -1,   242,   201,
     258,    -1,   229,   196,    -1,   231,    -1,    86,   244,    -1,
      87,   244,    -1,   245,   244,    -1,   202,    -1,   203,    -1,
     204,    -1,   205,    -1,   244,    -1,   246,   206,   244,    -1,
     246,   207,   244,    -1,   246,   208,   244,    -1,   246,    -1,
     247,   202,   246,    -1,   247,   203,   246,    -1,   247,    -1,
     248,    84,   247,    -1,   248,    85,   247,    -1,   248,    -1,
     249,   209,   248,    -1,   249,   210,   248,    -1,   249,    88,
     248,    -1,   249,    89,   248,    -1,   249,    -1,   250,    90,
     249,    -1,   250,    91,   249,    -1,   250,    -1,   251,   211,
     250,    -1,   251,    -1,   252,   212,   251,    -1,   252,    -1,
     253,   213,   252,    -1,   253,    -1,   254,    92,   253,    -1,
     254,    -1,   255,    94,   254,    -1,   255,    -1,   256,    93,
     255,    -1,   256,    -1,   256,   214,   260,   215,   258,    -1,
     257,    -1,   244,   259,   258,    -1,   216,    -1,    95,    -1,
      96,    -1,    98,    -1,    97,    -1,   104,    -1,    99,    -1,
     100,    -1,   101,    -1,   102,    -1,   103,    -1,   258,    -1,
     260,   201,   258,    -1,   257,    -1,   263,   217,    -1,   271,
     217,    -1,   110,   285,   282,   217,    -1,   264,   197,    -1,
     266,    -1,   265,    -1,   266,   268,    -1,   265,   201,   268,
      -1,   273,   229,   196,    -1,   281,   226,    -1,   281,   226,
     198,   261,   199,    -1,   278,   269,   267,    -1,   269,   267,
      -1,   278,   269,   270,    -1,   269,   270,    -1,    -1,    33,
      -1,    34,    -1,    35,    -1,   281,    -1,   272,    -1,   271,
     201,   226,    -1,   271,   201,   226,   198,   199,    -1,   271,
     201,   226,   198,   261,   199,    -1,   271,   201,   226,   198,
     199,   216,   291,    -1,   271,   201,   226,   198,   261,   199,
     216,   291,    -1,   271,   201,   226,   216,   291,    -1,   273,
      -1,   273,   226,    -1,   273,   226,   198,   199,    -1,   273,
     226,   198,   261,   199,    -1,   273,   226,   198,   199,   216,
     291,    -1,   273,   226,   198,   261,   199,   216,   291,    -1,
     273,   226,   216,   291,    -1,   105,   229,    -1,   281,    -1,
     279,   281,    -1,   123,   196,   275,   197,    -1,   276,    -1,
     275,   201,   276,    -1,   226,    -1,   226,   216,    80,    -1,
      40,    -1,    39,    -1,    38,    -1,     4,    -1,   280,    -1,
     274,    -1,   274,   280,    -1,   277,    -1,   277,   280,    -1,
     105,   280,    -1,   105,   277,   280,    -1,   105,    -1,     4,
      -1,     3,    -1,    37,    -1,    32,    37,    -1,    33,    -1,
      34,    -1,    32,    33,    -1,    32,    34,    -1,    36,    -1,
     282,    -1,   285,   282,    -1,   283,    -1,   283,   198,   199,
      -1,   283,   198,   261,   199,    -1,   284,    -1,   286,    -1,
      77,    -1,    74,    -1,     6,    -1,     7,    -1,     8,    -1,
       5,    -1,    29,    -1,    30,    -1,    31,    -1,    20,    -1,
      21,    -1,    22,    -1,    23,    -1,    24,    -1,    25,    -1,
      26,    -1,    27,    -1,    28,    -1,    41,    -1,    42,    -1,
      43,    -1,    44,    -1,    45,    -1,    46,    -1,    47,    -1,
      48,    -1,    49,    -1,    50,    -1,    51,    -1,   157,    -1,
      52,    -1,    53,    -1,    54,    -1,    55,    -1,   159,    -1,
      56,    -1,    57,    -1,    58,    -1,    59,    -1,    60,    -1,
      61,    -1,    62,    -1,    63,    -1,    64,    -1,    65,    -1,
      66,    -1,    67,    -1,    68,    -1,    69,    -1,    70,    -1,
      71,    -1,    72,    -1,   108,    -1,   107,    -1,   106,    -1,
      73,   226,   218,   287,   219,    -1,    73,   218,   287,   219,
      -1,   288,    -1,   287,   288,    -1,   281,   289,   217,    -1,
     290,    -1,   289,   201,   290,    -1,   226,    -1,   226,   198,
     261,   199,    -1,   258,    -1,   262,    -1,   295,    -1,   294,
      -1,   292,    -1,   300,    -1,   301,    -1,   304,    -1,   305,
      -1,   306,    -1,   310,    -1,   218,   219,    -1,    -1,   218,
     296,   299,   219,    -1,   298,    -1,   294,    -1,   218,   219,
      -1,   218,   299,   219,    -1,   293,    -1,   299,   293,    -1,
     217,    -1,   260,   217,    -1,    14,   196,   260,   197,   302,
      -1,   293,    12,   293,    -1,   293,    -1,   260,    -1,   273,
     226,   216,   291,    -1,    17,   196,   260,   197,   295,    -1,
      18,   260,   215,    -1,    19,   215,    -1,    75,   196,   303,
     197,   297,    -1,    11,   293,    75,   196,   260,   197,   217,
      -1,    13,   196,   307,   309,   197,   297,    -1,   300,    -1,
     292,    -1,   303,    -1,    -1,   308,   217,    -1,   308,   217,
     260,    -1,    10,   217,    -1,     9,   217,    -1,    16,   217,
      -1,    16,   260,   217,    -1,    15,   217,    -1,   312,    -1,
     262,    -1,   224,    -1,   263,   298,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   218,   218,   217,   229,   231,   271,   272,   273,   274,
     275,   287,   289,   293,   294,   295,   299,   308,   316,   327,
     328,   332,   339,   346,   353,   360,   367,   374,   375,   381,
     385,   392,   398,   407,   411,   415,   416,   425,   426,   430,
     431,   435,   441,   453,   457,   463,   470,   480,   481,   485,
     486,   490,   496,   508,   519,   520,   526,   532,   542,   543,
     544,   545,   549,   550,   556,   562,   571,   572,   578,   587,
     588,   594,   603,   604,   610,   616,   622,   631,   632,   638,
     647,   648,   657,   658,   667,   668,   677,   678,   687,   688,
     697,   698,   707,   708,   717,   718,   727,   728,   729,   730,
     731,   732,   733,   734,   735,   736,   737,   741,   745,   761,
     765,   770,   774,   783,   787,   788,   792,   797,   805,   819,
     829,   844,   851,   856,   867,   880,   883,   888,   893,   902,
     906,   907,   917,   927,   937,   947,   957,   971,   978,   987,
     996,  1005,  1014,  1023,  1032,  1046,  1053,  1064,  1071,  1072,
    1091,  1143,  1184,  1189,  1194,  1202,  1210,  1211,  1212,  1217,
    1218,  1223,  1228,  1234,  1242,  1247,  1252,  1257,  1263,  1268,
    1273,  1278,  1283,  1291,  1295,  1303,  1304,  1310,  1319,  1325,
    1331,  1340,  1341,  1342,  1343,  1344,  1345,  1346,  1347,  1348,
    1349,  1350,  1351,  1352,  1353,  1354,  1355,  1356,  1357,  1358,
    1359,  1360,  1361,  1362,  1363,  1364,  1365,  1366,  1367,  1368,
    1369,  1370,  1371,  1372,  1373,  1374,  1375,  1376,  1377,  1378,
    1379,  1380,  1381,  1382,  1383,  1384,  1385,  1386,  1387,  1388,
    1389,  1390,  1394,  1404,  1414,  1427,  1434,  1443,  1448,  1456,
    1471,  1476,  1484,  1491,  1500,  1504,  1510,  1511,  1515,  1516,
    1517,  1518,  1519,  1520,  1521,  1525,  1532,  1531,  1545,  1546,
    1550,  1556,  1565,  1575,  1587,  1593,  1602,  1611,  1616,  1624,
    1628,  1642,  1646,  1647,  1651,  1658,  1665,  1675,  1676,  1680,
    1682,  1688,  1693,  1702,  1708,  1714,  1720,  1726,  1735,  1736,
    1737,  1741
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ATTRIBUTE", "CONST_TOK", "BOOL_TOK",
  "FLOAT_TOK", "INT_TOK", "UINT_TOK", "BREAK", "CONTINUE", "DO", "ELSE",
  "FOR", "IF", "DISCARD", "RETURN", "SWITCH", "CASE", "DEFAULT", "BVEC2",
  "BVEC3", "BVEC4", "IVEC2", "IVEC3", "IVEC4", "UVEC2", "UVEC3", "UVEC4",
  "VEC2", "VEC3", "VEC4", "CENTROID", "IN_TOK", "OUT_TOK", "INOUT_TOK",
  "UNIFORM", "VARYING", "NOPERSPECTIVE", "FLAT", "SMOOTH", "MAT2X2",
  "MAT2X3", "MAT2X4", "MAT3X2", "MAT3X3", "MAT3X4", "MAT4X2", "MAT4X3",
  "MAT4X4", "SAMPLER1D", "SAMPLER2D", "SAMPLER3D", "SAMPLERCUBE",
  "SAMPLER1DSHADOW", "SAMPLER2DSHADOW", "SAMPLERCUBESHADOW",
  "SAMPLER1DARRAY", "SAMPLER2DARRAY", "SAMPLER1DARRAYSHADOW",
  "SAMPLER2DARRAYSHADOW", "ISAMPLER1D", "ISAMPLER2D", "ISAMPLER3D",
  "ISAMPLERCUBE", "ISAMPLER1DARRAY", "ISAMPLER2DARRAY", "USAMPLER1D",
  "USAMPLER2D", "USAMPLER3D", "USAMPLERCUBE", "USAMPLER1DARRAY",
  "USAMPLER2DARRAY", "STRUCT", "VOID_TOK", "WHILE", "IDENTIFIER",
  "TYPE_IDENTIFIER", "NEW_IDENTIFIER", "FLOATCONSTANT", "INTCONSTANT",
  "UINTCONSTANT", "BOOLCONSTANT", "FIELD_SELECTION", "LEFT_OP", "RIGHT_OP",
  "INC_OP", "DEC_OP", "LE_OP", "GE_OP", "EQ_OP", "NE_OP", "AND_OP",
  "OR_OP", "XOR_OP", "MUL_ASSIGN", "DIV_ASSIGN", "ADD_ASSIGN",
  "MOD_ASSIGN", "LEFT_ASSIGN", "RIGHT_ASSIGN", "AND_ASSIGN", "XOR_ASSIGN",
  "OR_ASSIGN", "SUB_ASSIGN", "INVARIANT", "LOWP", "MEDIUMP", "HIGHP",
  "SUPERP", "PRECISION", "VERSION", "EXTENSION", "LINE", "COLON", "EOL",
  "INTERFACE", "OUTPUT", "PRAGMA_DEBUG_ON", "PRAGMA_DEBUG_OFF",
  "PRAGMA_OPTIMIZE_ON", "PRAGMA_OPTIMIZE_OFF", "PRAGMA_INVARIANT_ALL",
  "LAYOUT_TOK", "ASM", "CLASS", "UNION", "ENUM", "TYPEDEF", "TEMPLATE",
  "THIS", "PACKED_TOK", "GOTO", "INLINE_TOK", "NOINLINE", "VOLATILE",
  "PUBLIC_TOK", "STATIC", "EXTERN", "EXTERNAL", "LONG_TOK", "SHORT_TOK",
  "DOUBLE_TOK", "HALF", "FIXED_TOK", "UNSIGNED", "INPUT_TOK", "OUPTUT",
  "HVEC2", "HVEC3", "HVEC4", "DVEC2", "DVEC3", "DVEC4", "FVEC2", "FVEC3",
  "FVEC4", "SAMPLER2DRECT", "SAMPLER3DRECT", "SAMPLER2DRECTSHADOW",
  "SIZEOF", "CAST", "NAMESPACE", "USING", "ERROR_TOK", "COMMON",
  "PARTITION", "ACTIVE", "SAMPLERBUFFER", "FILTER", "IMAGE1D", "IMAGE2D",
  "IMAGE3D", "IMAGECUBE", "IMAGE1DARRAY", "IMAGE2DARRAY", "IIMAGE1D",
  "IIMAGE2D", "IIMAGE3D", "IIMAGECUBE", "IIMAGE1DARRAY", "IIMAGE2DARRAY",
  "UIMAGE1D", "UIMAGE2D", "UIMAGE3D", "UIMAGECUBE", "UIMAGE1DARRAY",
  "UIMAGE2DARRAY", "IMAGE1DSHADOW", "IMAGE2DSHADOW", "IMAGEBUFFER",
  "IIMAGEBUFFER", "UIMAGEBUFFER", "IMAGE1DARRAYSHADOW",
  "IMAGE2DARRAYSHADOW", "ROW_MAJOR", "'('", "')'", "'['", "']'", "'.'",
  "','", "'+'", "'-'", "'!'", "'~'", "'*'", "'/'", "'%'", "'<'", "'>'",
  "'&'", "'^'", "'|'", "'?'", "':'", "'='", "';'", "'{'", "'}'", "$accept",
  "translation_unit", "$@1", "version_statement", "pragma_statement",
  "extension_statement_list", "any_identifier", "extension_statement",
  "external_declaration_list", "variable_identifier", "primary_expression",
  "postfix_expression", "integer_expression", "function_call",
  "function_call_or_method", "function_call_generic",
  "function_call_header_no_parameters",
  "function_call_header_with_parameters", "function_call_header",
  "function_identifier", "method_call_generic",
  "method_call_header_no_parameters", "method_call_header_with_parameters",
  "method_call_header", "unary_expression", "unary_operator",
  "multiplicative_expression", "additive_expression", "shift_expression",
  "relational_expression", "equality_expression", "and_expression",
  "exclusive_or_expression", "inclusive_or_expression",
  "logical_and_expression", "logical_xor_expression",
  "logical_or_expression", "conditional_expression",
  "assignment_expression", "assignment_operator", "expression",
  "constant_expression", "declaration", "function_prototype",
  "function_declarator", "function_header_with_parameters",
  "function_header", "parameter_declarator", "parameter_declaration",
  "parameter_qualifier", "parameter_type_specifier",
  "init_declarator_list", "single_declaration", "fully_specified_type",
  "layout_qualifier", "layout_qualifier_id_list", "layout_qualifier_id",
  "interpolation_qualifier", "parameter_type_qualifier", "type_qualifier",
  "storage_qualifier", "type_specifier", "type_specifier_no_prec",
  "type_specifier_nonarray", "basic_type_specifier_nonarray",
  "precision_qualifier", "struct_specifier", "struct_declaration_list",
  "struct_declaration", "struct_declarator_list", "struct_declarator",
  "initializer", "declaration_statement", "statement", "simple_statement",
  "compound_statement", "$@2", "statement_no_new_scope",
  "compound_statement_no_new_scope", "statement_list",
  "expression_statement", "selection_statement",
  "selection_rest_statement", "condition", "switch_statement",
  "case_label", "iteration_statement", "for_init_statement",
  "conditionopt", "for_rest_statement", "jump_statement",
  "external_declaration", "function_definition", 0
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
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357,   358,   359,   360,   361,   362,   363,   364,
     365,   366,   367,   368,   369,   370,   371,   372,   373,   374,
     375,   376,   377,   378,   379,   380,   381,   382,   383,   384,
     385,   386,   387,   388,   389,   390,   391,   392,   393,   394,
     395,   396,   397,   398,   399,   400,   401,   402,   403,   404,
     405,   406,   407,   408,   409,   410,   411,   412,   413,   414,
     415,   416,   417,   418,   419,   420,   421,   422,   423,   424,
     425,   426,   427,   428,   429,   430,   431,   432,   433,   434,
     435,   436,   437,   438,   439,   440,   441,   442,   443,   444,
     445,   446,   447,   448,   449,   450,    40,    41,    91,    93,
      46,    44,    43,    45,    33,   126,    42,    47,    37,    60,
      62,    38,    94,   124,    63,    58,    61,    59,   123,   125
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint16 yyr1[] =
{
       0,   220,   222,   221,   223,   223,   224,   224,   224,   224,
     224,   225,   225,   226,   226,   226,   227,   228,   228,   229,
     229,   230,   230,   230,   230,   230,   230,   231,   231,   231,
     231,   231,   231,   232,   233,   234,   234,   235,   235,   236,
     236,   237,   237,   238,   239,   239,   239,   240,   240,   241,
     241,   242,   242,   243,   244,   244,   244,   244,   245,   245,
     245,   245,   246,   246,   246,   246,   247,   247,   247,   248,
     248,   248,   249,   249,   249,   249,   249,   250,   250,   250,
     251,   251,   252,   252,   253,   253,   254,   254,   255,   255,
     256,   256,   257,   257,   258,   258,   259,   259,   259,   259,
     259,   259,   259,   259,   259,   259,   259,   260,   260,   261,
     262,   262,   262,   263,   264,   264,   265,   265,   266,   267,
     267,   268,   268,   268,   268,   269,   269,   269,   269,   270,
     271,   271,   271,   271,   271,   271,   271,   272,   272,   272,
     272,   272,   272,   272,   272,   273,   273,   274,   275,   275,
     276,   276,   277,   277,   277,   278,   279,   279,   279,   279,
     279,   279,   279,   279,   280,   280,   280,   280,   280,   280,
     280,   280,   280,   281,   281,   282,   282,   282,   283,   283,
     283,   284,   284,   284,   284,   284,   284,   284,   284,   284,
     284,   284,   284,   284,   284,   284,   284,   284,   284,   284,
     284,   284,   284,   284,   284,   284,   284,   284,   284,   284,
     284,   284,   284,   284,   284,   284,   284,   284,   284,   284,
     284,   284,   284,   284,   284,   284,   284,   284,   284,   284,
     284,   284,   285,   285,   285,   286,   286,   287,   287,   288,
     289,   289,   290,   290,   291,   292,   293,   293,   294,   294,
     294,   294,   294,   294,   294,   295,   296,   295,   297,   297,
     298,   298,   299,   299,   300,   300,   301,   302,   302,   303,
     303,   304,   305,   305,   306,   306,   306,   307,   307,   308,
     308,   309,   309,   310,   310,   310,   310,   310,   311,   311,
     311,   312
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     4,     0,     3,     2,     2,     2,     2,
       2,     0,     2,     1,     1,     1,     5,     1,     2,     1,
       1,     1,     1,     1,     1,     1,     3,     1,     4,     1,
       3,     2,     2,     1,     1,     1,     3,     2,     2,     2,
       1,     2,     3,     2,     1,     1,     1,     2,     2,     2,
       1,     2,     3,     2,     1,     2,     2,     2,     1,     1,
       1,     1,     1,     3,     3,     3,     1,     3,     3,     1,
       3,     3,     1,     3,     3,     3,     3,     1,     3,     3,
       1,     3,     1,     3,     1,     3,     1,     3,     1,     3,
       1,     3,     1,     5,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     1,
       2,     2,     4,     2,     1,     1,     2,     3,     3,     2,
       5,     3,     2,     3,     2,     0,     1,     1,     1,     1,
       1,     3,     5,     6,     7,     8,     5,     1,     2,     4,
       5,     6,     7,     4,     2,     1,     2,     4,     1,     3,
       1,     3,     1,     1,     1,     1,     1,     1,     2,     1,
       2,     2,     3,     1,     1,     1,     1,     2,     1,     1,
       2,     2,     1,     1,     2,     1,     3,     4,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     5,     4,     1,     2,     3,
       1,     3,     1,     4,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     2,     0,     4,     1,     1,
       2,     3,     1,     2,     1,     2,     5,     3,     1,     1,
       4,     5,     3,     2,     5,     7,     6,     1,     1,     1,
       0,     2,     3,     2,     2,     2,     3,     2,     1,     1,
       1,     2
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       4,     0,     0,    11,     0,     1,     2,     5,     0,     0,
      12,    13,    14,    15,     0,   165,   164,   185,   182,   183,
     184,   189,   190,   191,   192,   193,   194,   195,   196,   197,
     186,   187,   188,     0,   168,   169,   172,   166,   154,   153,
     152,   198,   199,   200,   201,   202,   203,   204,   205,   206,
     207,   208,   210,   211,   212,   213,   215,   216,   217,   218,
     219,   220,   221,   222,   223,   224,   225,   226,   227,   228,
     229,   230,   231,     0,   181,   180,   163,   234,   233,   232,
       0,     0,     0,     0,     0,     0,     0,   209,   214,   290,
       3,   289,     0,     0,   115,   125,     0,   130,   137,   157,
     159,     0,   156,   145,   173,   175,   178,     0,   179,    17,
     288,     0,   170,   171,   167,     0,     0,    19,    20,   144,
       0,   161,     0,     6,     7,     8,     9,    10,     0,    18,
     110,     0,   291,   113,   125,   155,   126,   127,   128,   116,
       0,   125,     0,   111,    13,    15,   138,     0,   158,   160,
     146,     0,   174,     0,     0,     0,   237,     0,   162,     0,
     150,     0,   148,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    24,    22,    23,    25,    46,     0,
       0,     0,    58,    59,    60,    61,   264,   256,   260,    21,
      27,    54,    29,    34,    35,     0,     0,    40,     0,    62,
       0,    66,    69,    72,    77,    80,    82,    84,    86,    88,
      90,    92,    94,   107,     0,   245,     0,   145,   248,   262,
     247,   246,     0,   249,   250,   251,   252,   253,   254,   117,
     122,   124,   129,     0,   131,     0,     0,   118,   176,    62,
     109,     0,    44,    16,   242,     0,   240,   236,   238,     0,
     112,     0,   147,     0,   284,   283,     0,     0,     0,   287,
     285,     0,     0,     0,   273,     0,    55,    56,     0,   255,
       0,    31,    32,     0,     0,    38,    37,     0,   181,    41,
      43,    97,    98,   100,    99,   102,   103,   104,   105,   106,
     101,    96,     0,    57,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   265,   261,   263,   119,   121,
     123,     0,     0,   139,     0,   244,   143,   177,     0,     0,
     239,   235,   151,   149,     0,   278,   277,   280,     0,   286,
       0,   272,   163,   269,     0,     0,    26,     0,     0,    33,
      30,     0,    36,     0,     0,    50,    42,    95,    63,    64,
      65,    67,    68,    70,    71,    75,    76,    73,    74,    78,
      79,    81,    83,    85,    87,    89,    91,     0,   108,     0,
     132,     0,   136,     0,   140,     0,   241,     0,   279,     0,
       0,     0,     0,     0,     0,   257,    28,    53,    48,    47,
       0,   181,    51,     0,     0,     0,   133,   141,     0,   243,
       0,   281,     0,   268,   266,   271,     0,   259,   274,   258,
      52,    93,   120,   134,     0,   142,     0,   282,   276,     0,
     270,   135,   275,   267
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     9,     3,    89,     6,   160,    10,    90,   189,
     190,   191,   348,   192,   193,   194,   195,   196,   197,   198,
     352,   353,   354,   355,   199,   200,   201,   202,   203,   204,
     205,   206,   207,   208,   209,   210,   211,   212,   213,   292,
     214,   241,   215,   216,    93,    94,    95,   230,   139,   140,
     231,    96,    97,    98,    99,   161,   162,   100,   141,   101,
     102,   242,   104,   105,   106,   107,   108,   155,   156,   245,
     246,   326,   218,   219,   220,   221,   270,   418,   419,   222,
     223,   224,   414,   345,   225,   226,   227,   337,   389,   390,
     228,   109,   110
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -366
static const yytype_int16 yypact[] =
{
     -57,   -43,    62,  -366,   -50,  -366,   -30,  -366,    67,  3341,
    -366,  -366,  -366,  -366,    -6,  -366,  -366,  -366,  -366,  -366,
    -366,  -366,  -366,  -366,  -366,  -366,  -366,  -366,  -366,  -366,
    -366,  -366,  -366,     8,  -366,  -366,  -366,  -366,  -366,  -366,
    -366,  -366,  -366,  -366,  -366,  -366,  -366,  -366,  -366,  -366,
    -366,  -366,  -366,  -366,  -366,  -366,  -366,  -366,  -366,  -366,
    -366,  -366,  -366,  -366,  -366,  -366,  -366,  -366,  -366,  -366,
    -366,  -366,  -366,   -65,  -366,  -366,   226,  -366,  -366,  -366,
      51,   -31,   -28,     6,    13,    15,   -44,  -366,  -366,  -366,
    3341,  -366,  -183,   -47,   -29,    18,  -169,  -366,   140,    24,
      24,  3460,  -366,  -366,  -366,   -24,  -366,  3533,  -366,  -366,
    -366,    67,  -366,  -366,  -366,  3460,   -48,  -366,  -366,  -366,
      24,  -366,  3533,  -366,  -366,  -366,  -366,  -366,    67,  -366,
    -366,   408,  -366,  -366,    55,  -366,  -366,  -366,  -366,  -366,
    3460,   200,    67,  -366,   -20,   -18,  -178,    23,  -366,  -366,
    -366,  2225,  -366,    72,    67,  1598,  -366,  3460,  -366,     4,
      10,   -84,  -366,    11,    14,  1059,    40,    42,    29,  1836,
      43,  2783,    34,    54,  -366,  -366,  -366,  -366,  -366,  2783,
    2783,  2783,  -366,  -366,  -366,  -366,  -366,    32,  -366,    56,
    -366,   -71,  -366,  -366,  -366,    57,   -81,  2969,    61,   -27,
    2783,    35,   -88,   -41,   -70,    33,    60,    41,    59,   181,
     180,   -89,  -366,  -366,  -168,  -366,    58,    80,  -366,  -366,
    -366,  -366,   625,  -366,  -366,  -366,  -366,  -366,  -366,  -366,
    -366,  -366,    67,  3460,  -177,  2411,  2783,  -366,  -366,  -366,
    -366,    78,  -366,  -366,    81,  -137,  -366,  -366,  -366,  1717,
    -366,   201,  -366,    67,  -366,  -366,   205,  1478,  2783,  -366,
    -366,  -134,  2783,  -115,  -366,  2039,  -366,  -366,   -60,  -366,
    1059,  -366,  -366,  2783,   140,  -366,  -366,  2783,    85,  -366,
    -366,  -366,  -366,  -366,  -366,  -366,  -366,  -366,  -366,  -366,
    -366,  -366,  2783,  -366,  2783,  2783,  2783,  2783,  2783,  2783,
    2783,  2783,  2783,  2783,  2783,  2783,  2783,  2783,  2783,  2783,
    2783,  2783,  2783,  2783,  2783,  -366,  -366,  -366,    86,  -366,
    -366,  2597,  2783,    69,    87,  -366,  -366,  -366,  2783,    67,
    -366,  -366,  -366,  -366,    91,  -366,  -366,  2039,   -59,  -366,
     -46,  -366,   129,    88,    67,    93,  -366,   842,    89,    88,
    -366,    95,  -366,    96,   -37,  3155,  -366,  -366,  -366,  -366,
    -366,    35,    35,   -88,   -88,   -41,   -41,   -41,   -41,   -70,
     -70,    33,    60,    41,    59,   181,   180,   -96,  -366,  2783,
      76,    97,  -366,  2783,    79,    98,  -366,  2783,  -366,    77,
     101,  1059,    83,    90,  1275,  -366,  -366,  -366,  -366,  -366,
    2783,   102,  -366,  2783,   108,  2783,    94,  -366,  2783,  -366,
     -26,  2783,  1275,   297,  -366,  -366,  2783,  -366,  -366,  -366,
    -366,  -366,  -366,  -366,  2783,  -366,   100,    88,  -366,  1059,
    -366,  -366,  -366,  -366
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -366,  -366,  -366,  -366,  -366,  -366,    -7,  -366,  -366,   -62,
    -366,  -366,  -366,  -366,  -366,  -366,  -366,  -366,  -366,  -366,
    -366,  -366,  -366,  -366,  -101,  -366,  -113,  -109,  -121,   -61,
       5,     3,     9,    16,     2,     7,  -366,  -142,  -100,  -366,
    -164,  -225,    21,    22,  -366,  -366,  -366,    82,   186,   173,
      92,  -366,  -366,  -242,  -366,  -366,    68,   -73,  -366,  -366,
     -74,    -9,   -67,  -366,  -366,   243,  -366,   170,  -147,  -366,
       0,  -298,    73,  -159,  -365,   -58,  -366,   -80,   239,    63,
      84,  -366,  -366,    -2,  -366,  -366,  -366,  -366,  -366,  -366,
    -366,   246,  -366
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -115
static const yytype_int16 yytable[] =
{
     103,    14,   121,   120,   312,   261,   256,   263,   248,   240,
     324,    11,    12,    13,   119,   271,   272,   268,   301,   302,
     235,   321,   135,   344,   382,   148,   149,    15,    16,   417,
      91,    92,   142,   314,   130,   131,   147,     4,   236,   322,
     152,   112,   113,   299,   300,   114,   158,   417,   143,   315,
     239,   136,   137,   138,     1,   159,    33,    34,    35,   135,
      36,    37,     5,   317,   329,     7,   116,   314,   281,   282,
     283,   284,   285,   286,   287,   288,   289,   290,   266,   267,
     330,   103,     8,   339,   123,   407,   314,   124,   136,   137,
     138,   146,   150,   240,   338,   344,   381,   279,   340,   293,
     341,   343,   248,   385,   153,   314,   154,   423,   111,   349,
     425,    91,    92,   252,   297,   298,   276,   253,   430,   403,
     277,   125,   217,   305,   306,   313,   431,   273,   126,   274,
     127,   232,    15,    16,   239,   234,   325,   346,   391,   303,
     304,   314,   314,    11,    12,    13,   154,   244,   154,   377,
     133,   392,   128,   115,   404,   314,   217,    77,    78,    79,
     399,    33,    34,    35,   400,    36,    37,    38,    39,    40,
     157,   426,   134,   343,   151,   314,   -19,   356,   -20,   240,
     365,   366,   367,   368,   361,   362,   240,   243,   317,   291,
     363,   364,   357,   358,   359,   360,   239,   239,   239,   239,
     239,   239,   239,   239,   239,   239,   239,   239,   239,   239,
     239,   239,   351,   217,   378,  -114,   144,    12,   145,   237,
     239,   250,   325,   410,   232,   318,   251,   239,   254,    15,
      16,   255,   413,   136,   137,   138,   257,   240,   258,   262,
     154,   294,   295,   296,   369,   370,   259,   427,   217,   264,
     265,   269,   -45,   308,   275,   402,   217,   280,    33,    34,
      35,   217,    36,    37,    38,    39,    40,   350,   121,   120,
     433,   307,   309,   310,   311,   130,   -44,   327,   239,   328,
     334,   332,   -39,   325,   379,   383,   384,   387,   396,   314,
     394,   397,   405,   398,   411,   408,   406,   409,   412,   -49,
     420,   187,   117,   421,   118,   325,   416,   422,   325,   429,
     424,   372,   371,   375,   233,   319,   325,   432,   373,   376,
     229,   333,   244,   122,   325,   320,   374,   249,   217,   386,
     335,   132,   428,   347,   415,   388,   129,   393,   217,     0,
       0,   336,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   217,     0,     0,   217,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   217,     0,     0,     0,     0,     0,     0,
       0,    15,    16,    17,    18,    19,    20,   163,   164,   165,
     217,   166,   167,   168,   169,   170,   171,   172,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,     0,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,   173,   117,    75,   118,   174,   175,   176,
     177,   178,     0,     0,   179,   180,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    76,    77,    78,    79,     0,    80,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    86,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    87,     0,    88,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   181,     0,     0,     0,     0,     0,
     182,   183,   184,   185,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   186,   187,   188,    15,    16,
      17,    18,    19,    20,   163,   164,   165,     0,   166,   167,
     168,   169,   170,   171,   172,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
       0,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
     173,   117,    75,   118,   174,   175,   176,   177,   178,     0,
       0,   179,   180,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      76,    77,    78,    79,     0,    80,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    86,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    87,     0,    88,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   181,     0,     0,     0,     0,     0,   182,   183,   184,
     185,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   186,   187,   316,    15,    16,    17,    18,    19,
      20,   163,   164,   165,     0,   166,   167,   168,   169,   170,
     171,   172,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,     0,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,   173,   117,    75,
     118,   174,   175,   176,   177,   178,     0,     0,   179,   180,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    76,    77,    78,
      79,     0,    80,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    86,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    87,
       0,    88,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   181,     0,
       0,     0,     0,     0,   182,   183,   184,   185,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   186,
     187,   395,    15,    16,    17,    18,    19,    20,   163,   164,
     165,     0,   166,   167,   168,   169,   170,   171,   172,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,     0,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,   173,   117,    75,   118,   174,   175,
     176,   177,   178,     0,     0,   179,   180,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    76,    77,    78,    79,     0,    80,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    86,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    87,     0,    88,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   181,     0,     0,     0,     0,
       0,   182,   183,   184,   185,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   186,   187,    15,    16,
      17,    18,    19,    20,   163,   164,   165,     0,   166,   167,
     168,   169,   170,   171,   172,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
       0,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
     173,   117,    75,   118,   174,   175,   176,   177,   178,     0,
       0,   179,   180,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      76,    77,    78,    79,     0,    80,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    86,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    87,     0,    88,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   181,     0,     0,     0,     0,     0,   182,   183,   184,
     185,    15,    16,    17,    18,    19,    20,     0,     0,     0,
       0,     0,   186,   131,     0,     0,     0,     0,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,     0,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,     0,   117,    75,   118,   174,   175,   176,
     177,   178,     0,     0,   179,   180,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    76,    77,    78,    79,     0,    80,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    86,     0,    17,    18,    19,    20,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
       0,     0,     0,     0,     0,    87,     0,    88,     0,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,     0,   181,    75,     0,     0,     0,     0,
     182,   183,   184,   185,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   186,     0,     0,     0,     0,
       0,     0,     0,     0,    77,    78,    79,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    17,    18,    19,    20,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,     0,
       0,     0,     0,     0,     0,    87,     0,    88,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,     0,     0,    75,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   247,     0,     0,
       0,     0,     0,    77,    78,    79,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    17,    18,    19,    20,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,     0,     0,
       0,     0,     0,     0,    87,     0,    88,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,     0,   117,    75,   118,   174,   175,   176,   177,   178,
       0,     0,   179,   180,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   331,     0,     0,     0,
       0,     0,    77,    78,    79,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    87,     0,    88,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   181,     0,     0,     0,     0,     0,   182,   183,
     184,   185,    15,    16,    17,    18,    19,    20,     0,     0,
       0,     0,     0,   260,     0,     0,     0,     0,     0,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,     0,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,     0,   117,    75,   118,   174,   175,
     176,   177,   178,     0,     0,   179,   180,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   342,    77,    78,    79,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    86,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    87,     0,    88,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      17,    18,    19,    20,     0,   181,     0,     0,     0,     0,
       0,   182,   183,   184,   185,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
       0,   117,    75,   118,   174,   175,   176,   177,   178,     0,
       0,   179,   180,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    77,    78,    79,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    87,     0,    88,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    17,    18,    19,    20,
       0,   181,     0,     0,   238,     0,     0,   182,   183,   184,
     185,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,     0,   117,    75,   118,
     174,   175,   176,   177,   178,     0,     0,   179,   180,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    77,    78,    79,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    87,     0,
      88,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    17,    18,    19,    20,     0,   181,     0,     0,
     323,     0,     0,   182,   183,   184,   185,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,     0,   117,    75,   118,   174,   175,   176,   177,
     178,     0,     0,   179,   180,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    77,    78,    79,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    87,     0,    88,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    17,    18,
      19,    20,     0,   181,     0,     0,   380,     0,     0,   182,
     183,   184,   185,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,     0,   117,
      75,   118,   174,   175,   176,   177,   178,     0,     0,   179,
     180,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    77,
      78,    79,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      87,     0,    88,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    17,    18,    19,    20,     0,   181,
       0,     0,     0,     0,     0,   182,   183,   184,   185,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,   278,     0,   117,    75,   118,   174,   175,
     176,   177,   178,     0,     0,   179,   180,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    77,    78,    79,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    87,     0,    88,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      17,    18,    19,    20,     0,   181,     0,     0,     0,     0,
       0,   182,   183,   184,   185,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,   401,
       0,   117,    75,   118,   174,   175,   176,   177,   178,     0,
       0,   179,   180,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    77,    78,    79,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    87,     0,    88,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    15,    16,    17,    18,    19,    20,
       0,   181,     0,     0,     0,     0,     0,   182,   183,   184,
     185,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,     0,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,     0,     0,    75,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    76,    77,    78,    79,
       0,    80,     0,     0,     0,     0,     0,     0,     0,    81,
      82,    83,    84,    85,    86,    17,    18,    19,    20,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,     0,     0,     0,     0,     0,     0,    87,     0,
      88,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,     0,     0,    75,    17,    18,
      19,    20,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,     0,    77,    78,    79,     0,
       0,     0,     0,     0,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,     0,     0,
      75,     0,     0,     0,     0,     0,     0,    87,     0,    88,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      87,     0,    88
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-366))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
       9,     8,    76,    76,    93,   169,   165,   171,   155,   151,
     235,    76,    77,    78,    76,    86,    87,   181,    88,    89,
     198,   198,     4,   265,   322,    99,   100,     3,     4,   394,
       9,     9,   201,   201,   217,   218,    98,    80,   216,   216,
     107,    33,    34,    84,    85,    37,   120,   412,   217,   217,
     151,    33,    34,    35,   111,   122,    32,    33,    34,     4,
      36,    37,     0,   222,   201,   115,    73,   201,    95,    96,
      97,    98,    99,   100,   101,   102,   103,   104,   179,   180,
     217,    90,   112,   217,   115,   383,   201,   115,    33,    34,
      35,    98,   101,   235,   258,   337,   321,   197,   262,   200,
     215,   265,   249,   328,   111,   201,   115,   405,   114,   273,
     408,    90,    90,   197,   202,   203,   197,   201,   416,   215,
     201,   115,   131,    90,    91,   214,   424,   198,   115,   200,
     115,   140,     3,     4,   235,   142,   236,   197,   197,   209,
     210,   201,   201,    76,    77,    78,   155,   154,   157,   313,
     197,   197,   196,   218,   379,   201,   165,   106,   107,   108,
     197,    32,    33,    34,   201,    36,    37,    38,    39,    40,
     218,   197,   201,   337,   198,   201,   196,   277,   196,   321,
     301,   302,   303,   304,   297,   298,   328,   115,   347,   216,
     299,   300,   292,   294,   295,   296,   297,   298,   299,   300,
     301,   302,   303,   304,   305,   306,   307,   308,   309,   310,
     311,   312,   274,   222,   314,   197,    76,    77,    78,   196,
     321,   217,   322,   387,   233,   232,   216,   328,   217,     3,
       4,   217,   391,    33,    34,    35,   196,   379,   196,   196,
     249,   206,   207,   208,   305,   306,   217,   411,   257,   215,
     196,   219,   196,   212,   197,   355,   265,   196,    32,    33,
      34,   270,    36,    37,    38,    39,    40,   274,   342,   342,
     429,   211,   213,    92,    94,   217,   196,   199,   379,   198,
      75,    80,   197,   383,   198,   216,   199,   196,   199,   201,
     197,   196,   216,   197,   217,   216,   199,   199,   197,   197,
     400,   218,    76,   403,    78,   405,   216,   199,   408,    12,
     216,   308,   307,   311,   141,   233,   416,   217,   309,   312,
     134,   253,   329,    80,   424,   233,   310,   157,   337,   329,
     257,    92,   412,   270,   392,   337,    90,   344,   347,    -1,
      -1,   257,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   391,    -1,    -1,   394,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   412,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     3,     4,     5,     6,     7,     8,     9,    10,    11,
     429,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    -1,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    -1,    -1,    86,    87,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   105,   106,   107,   108,    -1,   110,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   123,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   157,    -1,   159,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   196,    -1,    -1,    -1,    -1,    -1,
     202,   203,   204,   205,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   217,   218,   219,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    -1,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      -1,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    -1,
      -1,    86,    87,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     105,   106,   107,   108,    -1,   110,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   123,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   157,    -1,   159,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   196,    -1,    -1,    -1,    -1,    -1,   202,   203,   204,
     205,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   217,   218,   219,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    -1,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    -1,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    -1,    -1,    86,    87,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   105,   106,   107,
     108,    -1,   110,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   123,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   157,
      -1,   159,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   196,    -1,
      -1,    -1,    -1,    -1,   202,   203,   204,   205,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   217,
     218,   219,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    -1,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    -1,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    -1,    -1,    86,    87,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   105,   106,   107,   108,    -1,   110,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   123,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   157,    -1,   159,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   196,    -1,    -1,    -1,    -1,
      -1,   202,   203,   204,   205,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   217,   218,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    -1,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      -1,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    -1,
      -1,    86,    87,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     105,   106,   107,   108,    -1,   110,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   123,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   157,    -1,   159,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   196,    -1,    -1,    -1,    -1,    -1,   202,   203,   204,
     205,     3,     4,     5,     6,     7,     8,    -1,    -1,    -1,
      -1,    -1,   217,   218,    -1,    -1,    -1,    -1,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    -1,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    -1,    76,    77,    78,    79,    80,    81,
      82,    83,    -1,    -1,    86,    87,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   105,   106,   107,   108,    -1,   110,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   123,    -1,     5,     6,     7,     8,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      -1,    -1,    -1,    -1,    -1,   157,    -1,   159,    -1,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    -1,   196,    77,    -1,    -1,    -1,    -1,
     202,   203,   204,   205,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   217,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   106,   107,   108,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,     5,     6,     7,     8,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    -1,
      -1,    -1,    -1,    -1,    -1,   157,    -1,   159,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    -1,    -1,    77,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   219,    -1,    -1,
      -1,    -1,    -1,   106,   107,   108,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     5,     6,     7,     8,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    -1,    -1,
      -1,    -1,    -1,    -1,   157,    -1,   159,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    -1,    76,    77,    78,    79,    80,    81,    82,    83,
      -1,    -1,    86,    87,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   219,    -1,    -1,    -1,
      -1,    -1,   106,   107,   108,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   157,    -1,   159,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   196,    -1,    -1,    -1,    -1,    -1,   202,   203,
     204,   205,     3,     4,     5,     6,     7,     8,    -1,    -1,
      -1,    -1,    -1,   217,    -1,    -1,    -1,    -1,    -1,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    -1,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    -1,    76,    77,    78,    79,    80,
      81,    82,    83,    -1,    -1,    86,    87,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   105,   106,   107,   108,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   123,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   157,    -1,   159,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       5,     6,     7,     8,    -1,   196,    -1,    -1,    -1,    -1,
      -1,   202,   203,   204,   205,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      -1,    76,    77,    78,    79,    80,    81,    82,    83,    -1,
      -1,    86,    87,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   106,   107,   108,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   157,    -1,   159,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     5,     6,     7,     8,
      -1,   196,    -1,    -1,   199,    -1,    -1,   202,   203,   204,
     205,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    -1,    76,    77,    78,
      79,    80,    81,    82,    83,    -1,    -1,    86,    87,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   106,   107,   108,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   157,    -1,
     159,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,     5,     6,     7,     8,    -1,   196,    -1,    -1,
     199,    -1,    -1,   202,   203,   204,   205,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    -1,    76,    77,    78,    79,    80,    81,    82,
      83,    -1,    -1,    86,    87,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   106,   107,   108,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   157,    -1,   159,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     5,     6,
       7,     8,    -1,   196,    -1,    -1,   199,    -1,    -1,   202,
     203,   204,   205,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    -1,    76,
      77,    78,    79,    80,    81,    82,    83,    -1,    -1,    86,
      87,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   106,
     107,   108,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     157,    -1,   159,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     5,     6,     7,     8,    -1,   196,
      -1,    -1,    -1,    -1,    -1,   202,   203,   204,   205,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    -1,    76,    77,    78,    79,    80,
      81,    82,    83,    -1,    -1,    86,    87,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   106,   107,   108,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   157,    -1,   159,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       5,     6,     7,     8,    -1,   196,    -1,    -1,    -1,    -1,
      -1,   202,   203,   204,   205,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      -1,    76,    77,    78,    79,    80,    81,    82,    83,    -1,
      -1,    86,    87,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   106,   107,   108,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   157,    -1,   159,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     3,     4,     5,     6,     7,     8,
      -1,   196,    -1,    -1,    -1,    -1,    -1,   202,   203,   204,
     205,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    -1,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    -1,    -1,    77,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   105,   106,   107,   108,
      -1,   110,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   118,
     119,   120,   121,   122,   123,     5,     6,     7,     8,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    -1,    -1,    -1,    -1,    -1,    -1,   157,    -1,
     159,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    -1,    -1,    77,     5,     6,
       7,     8,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    -1,   106,   107,   108,    -1,
      -1,    -1,    -1,    -1,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    -1,    -1,
      77,    -1,    -1,    -1,    -1,    -1,    -1,   157,    -1,   159,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     157,    -1,   159
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint16 yystos[] =
{
       0,   111,   221,   223,    80,     0,   225,   115,   112,   222,
     227,    76,    77,    78,   226,     3,     4,     5,     6,     7,
       8,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    77,   105,   106,   107,   108,
     110,   118,   119,   120,   121,   122,   123,   157,   159,   224,
     228,   262,   263,   264,   265,   266,   271,   272,   273,   274,
     277,   279,   280,   281,   282,   283,   284,   285,   286,   311,
     312,   114,    33,    34,    37,   218,   226,    76,    78,   229,
     277,   280,   285,   115,   115,   115,   115,   115,   196,   311,
     217,   218,   298,   197,   201,     4,    33,    34,    35,   268,
     269,   278,   201,   217,    76,    78,   226,   229,   280,   280,
     281,   198,   282,   226,   281,   287,   288,   218,   280,   282,
     226,   275,   276,     9,    10,    11,    13,    14,    15,    16,
      17,    18,    19,    75,    79,    80,    81,    82,    83,    86,
      87,   196,   202,   203,   204,   205,   217,   218,   219,   229,
     230,   231,   233,   234,   235,   236,   237,   238,   239,   244,
     245,   246,   247,   248,   249,   250,   251,   252,   253,   254,
     255,   256,   257,   258,   260,   262,   263,   281,   292,   293,
     294,   295,   299,   300,   301,   304,   305,   306,   310,   268,
     267,   270,   281,   269,   226,   198,   216,   196,   199,   244,
     257,   261,   281,   115,   226,   289,   290,   219,   288,   287,
     217,   216,   197,   201,   217,   217,   293,   196,   196,   217,
     217,   260,   196,   260,   215,   196,   244,   244,   260,   219,
     296,    86,    87,   198,   200,   197,   197,   201,    74,   258,
     196,    95,    96,    97,    98,    99,   100,   101,   102,   103,
     104,   216,   259,   244,   206,   207,   208,   202,   203,    84,
      85,    88,    89,   209,   210,    90,    91,   211,   212,   213,
      92,    94,    93,   214,   201,   217,   219,   293,   226,   267,
     270,   198,   216,   199,   261,   258,   291,   199,   198,   201,
     217,   219,    80,   276,    75,   292,   300,   307,   260,   217,
     260,   215,   105,   260,   273,   303,   197,   299,   232,   260,
     226,   229,   240,   241,   242,   243,   258,   258,   244,   244,
     244,   246,   246,   247,   247,   248,   248,   248,   248,   249,
     249,   250,   251,   252,   253,   254,   255,   260,   258,   198,
     199,   261,   291,   216,   199,   261,   290,   196,   303,   308,
     309,   197,   197,   226,   197,   219,   199,   196,   197,   197,
     201,    74,   258,   215,   261,   216,   199,   291,   216,   199,
     260,   217,   197,   293,   302,   295,   216,   294,   297,   298,
     258,   258,   199,   291,   216,   291,   197,   260,   297,    12,
     291,   291,   217,   293
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

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (&yylloc, state, YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (&yylval, &yylloc, YYLEX_PARAM)
#else
# define YYLEX yylex (&yylval, &yylloc, scanner)
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
		  Type, Value, Location, state); \
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
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, struct _mesa_glsl_parse_state *state)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp, state)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
    struct _mesa_glsl_parse_state *state;
#endif
{
  if (!yyvaluep)
    return;
  YYUSE (yylocationp);
  YYUSE (state);
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
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, struct _mesa_glsl_parse_state *state)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep, yylocationp, state)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
    struct _mesa_glsl_parse_state *state;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp, state);
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
yy_reduce_print (YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule, struct _mesa_glsl_parse_state *state)
#else
static void
yy_reduce_print (yyvsp, yylsp, yyrule, state)
    YYSTYPE *yyvsp;
    YYLTYPE *yylsp;
    int yyrule;
    struct _mesa_glsl_parse_state *state;
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
		       , &(yylsp[(yyi + 1) - (yynrhs)])		       , state);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, yylsp, Rule, state); \
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
  YYSIZE_T yysize0 = yytnamerr (0, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  YYSIZE_T yysize1;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = 0;
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
                yysize1 = yysize + yytnamerr (0, yytname[yyx]);
                if (! (yysize <= yysize1
                       && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                  return 2;
                yysize = yysize1;
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

  yysize1 = yysize + yystrlen (yyformat);
  if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
    return 2;
  yysize = yysize1;

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
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, struct _mesa_glsl_parse_state *state)
#else
static void
yydestruct (yymsg, yytype, yyvaluep, yylocationp, state)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
    YYLTYPE *yylocationp;
    struct _mesa_glsl_parse_state *state;
#endif
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  YYUSE (state);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (struct _mesa_glsl_parse_state *state);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


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
yyparse (struct _mesa_glsl_parse_state *state)
#else
int
yyparse (state)
    struct _mesa_glsl_parse_state *state;
#endif
#endif
{
/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Location data for the lookahead symbol.  */
YYLTYPE yylloc;

    /* Number of syntax errors so far.  */
    int yynerrs;

    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.
       `yyls': related to locations.

       Refer to the stacks thru separate pointers, to allow yyoverflow
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
  int yytoken;
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

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;
  yylsp = yyls;

#if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  /* Initialize the default location before parsing starts.  */
  yylloc.first_line   = yylloc.last_line   = 1;
  yylloc.first_column = yylloc.last_column = 1;
#endif

/* User initialization code.  */

/* Line 1590 of yacc.c  */
#line 41 "glsl_parser.yy"
{
   yylloc.first_line = 1;
   yylloc.first_column = 1;
   yylloc.last_line = 1;
   yylloc.last_column = 1;
   yylloc.source = 0;
}

/* Line 1590 of yacc.c  */
#line 2688 "glsl_parser.cpp"
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
  *++yyvsp = yylval;
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

/* Line 1806 of yacc.c  */
#line 218 "glsl_parser.yy"
    {
	   _mesa_glsl_initialize_types(state);
	}
    break;

  case 3:

/* Line 1806 of yacc.c  */
#line 222 "glsl_parser.yy"
    {
	   delete state->symbols;
	   state->symbols = new(ralloc_parent(state)) glsl_symbol_table;
	   _mesa_glsl_initialize_types(state);
	}
    break;

  case 5:

/* Line 1806 of yacc.c  */
#line 232 "glsl_parser.yy"
    {
	   bool supported = false;

	   switch ((yyvsp[(2) - (3)].n)) {
	   case 100:
	      state->es_shader = true;
	      supported = state->Const.GLSL_100ES;
	      break;
	   case 110:
	      supported = state->Const.GLSL_110;
	      break;
	   case 120:
	      supported = state->Const.GLSL_120;
	      break;
	   case 130:
	      supported = state->Const.GLSL_130;
	      break;
	   default:
	      supported = false;
	      break;
	   }

	   state->language_version = (yyvsp[(2) - (3)].n);
	   state->version_string =
	      ralloc_asprintf(state, "GLSL%s %d.%02d",
			      state->es_shader ? " ES" : "",
			      state->language_version / 100,
			      state->language_version % 100);

	   if (!supported) {
	      _mesa_glsl_error(& (yylsp[(2) - (3)]), state, "%s is not supported. "
			       "Supported versions are: %s\n",
			       state->version_string,
			       state->supported_version_string);
	   }
	}
    break;

  case 10:

/* Line 1806 of yacc.c  */
#line 276 "glsl_parser.yy"
    {
	   if (state->language_version < 120) {
	      _mesa_glsl_warning(& (yylsp[(1) - (2)]), state,
				 "pragma `invariant(all)' not supported in %s",
				 state->version_string);
	   } else {
	      state->all_invariant = true;
	   }
	}
    break;

  case 16:

/* Line 1806 of yacc.c  */
#line 300 "glsl_parser.yy"
    {
	   if (!_mesa_glsl_process_extension((yyvsp[(2) - (5)].identifier), & (yylsp[(2) - (5)]), (yyvsp[(4) - (5)].identifier), & (yylsp[(4) - (5)]), state)) {
	      YYERROR;
	   }
	}
    break;

  case 17:

/* Line 1806 of yacc.c  */
#line 309 "glsl_parser.yy"
    {
	   /* FINISHME: The NULL test is required because pragmas are set to
	    * FINISHME: NULL. (See production rule for external_declaration.)
	    */
	   if ((yyvsp[(1) - (1)].node) != NULL)
	      state->translation_unit.push_tail(& (yyvsp[(1) - (1)].node)->link);
	}
    break;

  case 18:

/* Line 1806 of yacc.c  */
#line 317 "glsl_parser.yy"
    {
	   /* FINISHME: The NULL test is required because pragmas are set to
	    * FINISHME: NULL. (See production rule for external_declaration.)
	    */
	   if ((yyvsp[(2) - (2)].node) != NULL)
	      state->translation_unit.push_tail(& (yyvsp[(2) - (2)].node)->link);
	}
    break;

  case 21:

/* Line 1806 of yacc.c  */
#line 333 "glsl_parser.yy"
    {
	   void *ctx = state;
	   (yyval.expression) = new(ctx) ast_expression(ast_identifier, NULL, NULL, NULL);
	   (yyval.expression)->set_location(yylloc);
	   (yyval.expression)->primary_expression.identifier = (yyvsp[(1) - (1)].identifier);
	}
    break;

  case 22:

/* Line 1806 of yacc.c  */
#line 340 "glsl_parser.yy"
    {
	   void *ctx = state;
	   (yyval.expression) = new(ctx) ast_expression(ast_int_constant, NULL, NULL, NULL);
	   (yyval.expression)->set_location(yylloc);
	   (yyval.expression)->primary_expression.int_constant = (yyvsp[(1) - (1)].n);
	}
    break;

  case 23:

/* Line 1806 of yacc.c  */
#line 347 "glsl_parser.yy"
    {
	   void *ctx = state;
	   (yyval.expression) = new(ctx) ast_expression(ast_uint_constant, NULL, NULL, NULL);
	   (yyval.expression)->set_location(yylloc);
	   (yyval.expression)->primary_expression.uint_constant = (yyvsp[(1) - (1)].n);
	}
    break;

  case 24:

/* Line 1806 of yacc.c  */
#line 354 "glsl_parser.yy"
    {
	   void *ctx = state;
	   (yyval.expression) = new(ctx) ast_expression(ast_float_constant, NULL, NULL, NULL);
	   (yyval.expression)->set_location(yylloc);
	   (yyval.expression)->primary_expression.float_constant = (yyvsp[(1) - (1)].real);
	}
    break;

  case 25:

/* Line 1806 of yacc.c  */
#line 361 "glsl_parser.yy"
    {
	   void *ctx = state;
	   (yyval.expression) = new(ctx) ast_expression(ast_bool_constant, NULL, NULL, NULL);
	   (yyval.expression)->set_location(yylloc);
	   (yyval.expression)->primary_expression.bool_constant = (yyvsp[(1) - (1)].n);
	}
    break;

  case 26:

/* Line 1806 of yacc.c  */
#line 368 "glsl_parser.yy"
    {
	   (yyval.expression) = (yyvsp[(2) - (3)].expression);
	}
    break;

  case 28:

/* Line 1806 of yacc.c  */
#line 376 "glsl_parser.yy"
    {
	   void *ctx = state;
	   (yyval.expression) = new(ctx) ast_expression(ast_array_index, (yyvsp[(1) - (4)].expression), (yyvsp[(3) - (4)].expression), NULL);
	   (yyval.expression)->set_location(yylloc);
	}
    break;

  case 29:

/* Line 1806 of yacc.c  */
#line 382 "glsl_parser.yy"
    {
	   (yyval.expression) = (yyvsp[(1) - (1)].expression);
	}
    break;

  case 30:

/* Line 1806 of yacc.c  */
#line 386 "glsl_parser.yy"
    {
	   void *ctx = state;
	   (yyval.expression) = new(ctx) ast_expression(ast_field_selection, (yyvsp[(1) - (3)].expression), NULL, NULL);
	   (yyval.expression)->set_location(yylloc);
	   (yyval.expression)->primary_expression.identifier = (yyvsp[(3) - (3)].identifier);
	}
    break;

  case 31:

/* Line 1806 of yacc.c  */
#line 393 "glsl_parser.yy"
    {
	   void *ctx = state;
	   (yyval.expression) = new(ctx) ast_expression(ast_post_inc, (yyvsp[(1) - (2)].expression), NULL, NULL);
	   (yyval.expression)->set_location(yylloc);
	}
    break;

  case 32:

/* Line 1806 of yacc.c  */
#line 399 "glsl_parser.yy"
    {
	   void *ctx = state;
	   (yyval.expression) = new(ctx) ast_expression(ast_post_dec, (yyvsp[(1) - (2)].expression), NULL, NULL);
	   (yyval.expression)->set_location(yylloc);
	}
    break;

  case 36:

/* Line 1806 of yacc.c  */
#line 417 "glsl_parser.yy"
    {
	   void *ctx = state;
	   (yyval.expression) = new(ctx) ast_expression(ast_field_selection, (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression), NULL);
	   (yyval.expression)->set_location(yylloc);
	}
    break;

  case 41:

/* Line 1806 of yacc.c  */
#line 436 "glsl_parser.yy"
    {
	   (yyval.expression) = (yyvsp[(1) - (2)].expression);
	   (yyval.expression)->set_location(yylloc);
	   (yyval.expression)->expressions.push_tail(& (yyvsp[(2) - (2)].expression)->link);
	}
    break;

  case 42:

/* Line 1806 of yacc.c  */
#line 442 "glsl_parser.yy"
    {
	   (yyval.expression) = (yyvsp[(1) - (3)].expression);
	   (yyval.expression)->set_location(yylloc);
	   (yyval.expression)->expressions.push_tail(& (yyvsp[(3) - (3)].expression)->link);
	}
    break;

  case 44:

/* Line 1806 of yacc.c  */
#line 458 "glsl_parser.yy"
    {
	   void *ctx = state;
	   (yyval.expression) = new(ctx) ast_function_expression((yyvsp[(1) - (1)].type_specifier));
	   (yyval.expression)->set_location(yylloc);
   	}
    break;

  case 45:

/* Line 1806 of yacc.c  */
#line 464 "glsl_parser.yy"
    {
	   void *ctx = state;
	   ast_expression *callee = new(ctx) ast_expression((yyvsp[(1) - (1)].identifier));
	   (yyval.expression) = new(ctx) ast_function_expression(callee);
	   (yyval.expression)->set_location(yylloc);
   	}
    break;

  case 46:

/* Line 1806 of yacc.c  */
#line 471 "glsl_parser.yy"
    {
	   void *ctx = state;
	   ast_expression *callee = new(ctx) ast_expression((yyvsp[(1) - (1)].identifier));
	   (yyval.expression) = new(ctx) ast_function_expression(callee);
	   (yyval.expression)->set_location(yylloc);
   	}
    break;

  case 51:

/* Line 1806 of yacc.c  */
#line 491 "glsl_parser.yy"
    {
	   (yyval.expression) = (yyvsp[(1) - (2)].expression);
	   (yyval.expression)->set_location(yylloc);
	   (yyval.expression)->expressions.push_tail(& (yyvsp[(2) - (2)].expression)->link);
	}
    break;

  case 52:

/* Line 1806 of yacc.c  */
#line 497 "glsl_parser.yy"
    {
	   (yyval.expression) = (yyvsp[(1) - (3)].expression);
	   (yyval.expression)->set_location(yylloc);
	   (yyval.expression)->expressions.push_tail(& (yyvsp[(3) - (3)].expression)->link);
	}
    break;

  case 53:

/* Line 1806 of yacc.c  */
#line 509 "glsl_parser.yy"
    {
	   void *ctx = state;
	   ast_expression *callee = new(ctx) ast_expression((yyvsp[(1) - (2)].identifier));
	   (yyval.expression) = new(ctx) ast_function_expression(callee);
	   (yyval.expression)->set_location(yylloc);
   	}
    break;

  case 55:

/* Line 1806 of yacc.c  */
#line 521 "glsl_parser.yy"
    {
	   void *ctx = state;
	   (yyval.expression) = new(ctx) ast_expression(ast_pre_inc, (yyvsp[(2) - (2)].expression), NULL, NULL);
	   (yyval.expression)->set_location(yylloc);
	}
    break;

  case 56:

/* Line 1806 of yacc.c  */
#line 527 "glsl_parser.yy"
    {
	   void *ctx = state;
	   (yyval.expression) = new(ctx) ast_expression(ast_pre_dec, (yyvsp[(2) - (2)].expression), NULL, NULL);
	   (yyval.expression)->set_location(yylloc);
	}
    break;

  case 57:

/* Line 1806 of yacc.c  */
#line 533 "glsl_parser.yy"
    {
	   void *ctx = state;
	   (yyval.expression) = new(ctx) ast_expression((yyvsp[(1) - (2)].n), (yyvsp[(2) - (2)].expression), NULL, NULL);
	   (yyval.expression)->set_location(yylloc);
	}
    break;

  case 58:

/* Line 1806 of yacc.c  */
#line 542 "glsl_parser.yy"
    { (yyval.n) = ast_plus; }
    break;

  case 59:

/* Line 1806 of yacc.c  */
#line 543 "glsl_parser.yy"
    { (yyval.n) = ast_neg; }
    break;

  case 60:

/* Line 1806 of yacc.c  */
#line 544 "glsl_parser.yy"
    { (yyval.n) = ast_logic_not; }
    break;

  case 61:

/* Line 1806 of yacc.c  */
#line 545 "glsl_parser.yy"
    { (yyval.n) = ast_bit_not; }
    break;

  case 63:

/* Line 1806 of yacc.c  */
#line 551 "glsl_parser.yy"
    {
	   void *ctx = state;
	   (yyval.expression) = new(ctx) ast_expression_bin(ast_mul, (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
	   (yyval.expression)->set_location(yylloc);
	}
    break;

  case 64:

/* Line 1806 of yacc.c  */
#line 557 "glsl_parser.yy"
    {
	   void *ctx = state;
	   (yyval.expression) = new(ctx) ast_expression_bin(ast_div, (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
	   (yyval.expression)->set_location(yylloc);
	}
    break;

  case 65:

/* Line 1806 of yacc.c  */
#line 563 "glsl_parser.yy"
    {
	   void *ctx = state;
	   (yyval.expression) = new(ctx) ast_expression_bin(ast_mod, (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
	   (yyval.expression)->set_location(yylloc);
	}
    break;

  case 67:

/* Line 1806 of yacc.c  */
#line 573 "glsl_parser.yy"
    {
	   void *ctx = state;
	   (yyval.expression) = new(ctx) ast_expression_bin(ast_add, (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
	   (yyval.expression)->set_location(yylloc);
	}
    break;

  case 68:

/* Line 1806 of yacc.c  */
#line 579 "glsl_parser.yy"
    {
	   void *ctx = state;
	   (yyval.expression) = new(ctx) ast_expression_bin(ast_sub, (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
	   (yyval.expression)->set_location(yylloc);
	}
    break;

  case 70:

/* Line 1806 of yacc.c  */
#line 589 "glsl_parser.yy"
    {
	   void *ctx = state;
	   (yyval.expression) = new(ctx) ast_expression_bin(ast_lshift, (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
	   (yyval.expression)->set_location(yylloc);
	}
    break;

  case 71:

/* Line 1806 of yacc.c  */
#line 595 "glsl_parser.yy"
    {
	   void *ctx = state;
	   (yyval.expression) = new(ctx) ast_expression_bin(ast_rshift, (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
	   (yyval.expression)->set_location(yylloc);
	}
    break;

  case 73:

/* Line 1806 of yacc.c  */
#line 605 "glsl_parser.yy"
    {
	   void *ctx = state;
	   (yyval.expression) = new(ctx) ast_expression_bin(ast_less, (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
	   (yyval.expression)->set_location(yylloc);
	}
    break;

  case 74:

/* Line 1806 of yacc.c  */
#line 611 "glsl_parser.yy"
    {
	   void *ctx = state;
	   (yyval.expression) = new(ctx) ast_expression_bin(ast_greater, (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
	   (yyval.expression)->set_location(yylloc);
	}
    break;

  case 75:

/* Line 1806 of yacc.c  */
#line 617 "glsl_parser.yy"
    {
	   void *ctx = state;
	   (yyval.expression) = new(ctx) ast_expression_bin(ast_lequal, (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
	   (yyval.expression)->set_location(yylloc);
	}
    break;

  case 76:

/* Line 1806 of yacc.c  */
#line 623 "glsl_parser.yy"
    {
	   void *ctx = state;
	   (yyval.expression) = new(ctx) ast_expression_bin(ast_gequal, (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
	   (yyval.expression)->set_location(yylloc);
	}
    break;

  case 78:

/* Line 1806 of yacc.c  */
#line 633 "glsl_parser.yy"
    {
	   void *ctx = state;
	   (yyval.expression) = new(ctx) ast_expression_bin(ast_equal, (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
	   (yyval.expression)->set_location(yylloc);
	}
    break;

  case 79:

/* Line 1806 of yacc.c  */
#line 639 "glsl_parser.yy"
    {
	   void *ctx = state;
	   (yyval.expression) = new(ctx) ast_expression_bin(ast_nequal, (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
	   (yyval.expression)->set_location(yylloc);
	}
    break;

  case 81:

/* Line 1806 of yacc.c  */
#line 649 "glsl_parser.yy"
    {
	   void *ctx = state;
	   (yyval.expression) = new(ctx) ast_expression_bin(ast_bit_and, (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
	   (yyval.expression)->set_location(yylloc);
	}
    break;

  case 83:

/* Line 1806 of yacc.c  */
#line 659 "glsl_parser.yy"
    {
	   void *ctx = state;
	   (yyval.expression) = new(ctx) ast_expression_bin(ast_bit_xor, (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
	   (yyval.expression)->set_location(yylloc);
	}
    break;

  case 85:

/* Line 1806 of yacc.c  */
#line 669 "glsl_parser.yy"
    {
	   void *ctx = state;
	   (yyval.expression) = new(ctx) ast_expression_bin(ast_bit_or, (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
	   (yyval.expression)->set_location(yylloc);
	}
    break;

  case 87:

/* Line 1806 of yacc.c  */
#line 679 "glsl_parser.yy"
    {
	   void *ctx = state;
	   (yyval.expression) = new(ctx) ast_expression_bin(ast_logic_and, (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
	   (yyval.expression)->set_location(yylloc);
	}
    break;

  case 89:

/* Line 1806 of yacc.c  */
#line 689 "glsl_parser.yy"
    {
	   void *ctx = state;
	   (yyval.expression) = new(ctx) ast_expression_bin(ast_logic_xor, (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
	   (yyval.expression)->set_location(yylloc);
	}
    break;

  case 91:

/* Line 1806 of yacc.c  */
#line 699 "glsl_parser.yy"
    {
	   void *ctx = state;
	   (yyval.expression) = new(ctx) ast_expression_bin(ast_logic_or, (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression));
	   (yyval.expression)->set_location(yylloc);
	}
    break;

  case 93:

/* Line 1806 of yacc.c  */
#line 709 "glsl_parser.yy"
    {
	   void *ctx = state;
	   (yyval.expression) = new(ctx) ast_expression(ast_conditional, (yyvsp[(1) - (5)].expression), (yyvsp[(3) - (5)].expression), (yyvsp[(5) - (5)].expression));
	   (yyval.expression)->set_location(yylloc);
	}
    break;

  case 95:

/* Line 1806 of yacc.c  */
#line 719 "glsl_parser.yy"
    {
	   void *ctx = state;
	   (yyval.expression) = new(ctx) ast_expression((yyvsp[(2) - (3)].n), (yyvsp[(1) - (3)].expression), (yyvsp[(3) - (3)].expression), NULL);
	   (yyval.expression)->set_location(yylloc);
	}
    break;

  case 96:

/* Line 1806 of yacc.c  */
#line 727 "glsl_parser.yy"
    { (yyval.n) = ast_assign; }
    break;

  case 97:

/* Line 1806 of yacc.c  */
#line 728 "glsl_parser.yy"
    { (yyval.n) = ast_mul_assign; }
    break;

  case 98:

/* Line 1806 of yacc.c  */
#line 729 "glsl_parser.yy"
    { (yyval.n) = ast_div_assign; }
    break;

  case 99:

/* Line 1806 of yacc.c  */
#line 730 "glsl_parser.yy"
    { (yyval.n) = ast_mod_assign; }
    break;

  case 100:

/* Line 1806 of yacc.c  */
#line 731 "glsl_parser.yy"
    { (yyval.n) = ast_add_assign; }
    break;

  case 101:

/* Line 1806 of yacc.c  */
#line 732 "glsl_parser.yy"
    { (yyval.n) = ast_sub_assign; }
    break;

  case 102:

/* Line 1806 of yacc.c  */
#line 733 "glsl_parser.yy"
    { (yyval.n) = ast_ls_assign; }
    break;

  case 103:

/* Line 1806 of yacc.c  */
#line 734 "glsl_parser.yy"
    { (yyval.n) = ast_rs_assign; }
    break;

  case 104:

/* Line 1806 of yacc.c  */
#line 735 "glsl_parser.yy"
    { (yyval.n) = ast_and_assign; }
    break;

  case 105:

/* Line 1806 of yacc.c  */
#line 736 "glsl_parser.yy"
    { (yyval.n) = ast_xor_assign; }
    break;

  case 106:

/* Line 1806 of yacc.c  */
#line 737 "glsl_parser.yy"
    { (yyval.n) = ast_or_assign; }
    break;

  case 107:

/* Line 1806 of yacc.c  */
#line 742 "glsl_parser.yy"
    {
	   (yyval.expression) = (yyvsp[(1) - (1)].expression);
	}
    break;

  case 108:

/* Line 1806 of yacc.c  */
#line 746 "glsl_parser.yy"
    {
	   void *ctx = state;
	   if ((yyvsp[(1) - (3)].expression)->oper != ast_sequence) {
	      (yyval.expression) = new(ctx) ast_expression(ast_sequence, NULL, NULL, NULL);
	      (yyval.expression)->set_location(yylloc);
	      (yyval.expression)->expressions.push_tail(& (yyvsp[(1) - (3)].expression)->link);
	   } else {
	      (yyval.expression) = (yyvsp[(1) - (3)].expression);
	   }

	   (yyval.expression)->expressions.push_tail(& (yyvsp[(3) - (3)].expression)->link);
	}
    break;

  case 110:

/* Line 1806 of yacc.c  */
#line 766 "glsl_parser.yy"
    {
	   state->symbols->pop_scope();
	   (yyval.node) = (yyvsp[(1) - (2)].function);
	}
    break;

  case 111:

/* Line 1806 of yacc.c  */
#line 771 "glsl_parser.yy"
    {
	   (yyval.node) = (yyvsp[(1) - (2)].declarator_list);
	}
    break;

  case 112:

/* Line 1806 of yacc.c  */
#line 775 "glsl_parser.yy"
    {
	   (yyvsp[(3) - (4)].type_specifier)->precision = (yyvsp[(2) - (4)].n);
	   (yyvsp[(3) - (4)].type_specifier)->is_precision_statement = true;
	   (yyval.node) = (yyvsp[(3) - (4)].type_specifier);
	}
    break;

  case 116:

/* Line 1806 of yacc.c  */
#line 793 "glsl_parser.yy"
    {
	   (yyval.function) = (yyvsp[(1) - (2)].function);
	   (yyval.function)->parameters.push_tail(& (yyvsp[(2) - (2)].parameter_declarator)->link);
	}
    break;

  case 117:

/* Line 1806 of yacc.c  */
#line 798 "glsl_parser.yy"
    {
	   (yyval.function) = (yyvsp[(1) - (3)].function);
	   (yyval.function)->parameters.push_tail(& (yyvsp[(3) - (3)].parameter_declarator)->link);
	}
    break;

  case 118:

/* Line 1806 of yacc.c  */
#line 806 "glsl_parser.yy"
    {
	   void *ctx = state;
	   (yyval.function) = new(ctx) ast_function();
	   (yyval.function)->set_location(yylloc);
	   (yyval.function)->return_type = (yyvsp[(1) - (3)].fully_specified_type);
	   (yyval.function)->identifier = (yyvsp[(2) - (3)].identifier);

	   state->symbols->add_function(new(state) ir_function((yyvsp[(2) - (3)].identifier)));
	   state->symbols->push_scope();
	}
    break;

  case 119:

/* Line 1806 of yacc.c  */
#line 820 "glsl_parser.yy"
    {
	   void *ctx = state;
	   (yyval.parameter_declarator) = new(ctx) ast_parameter_declarator();
	   (yyval.parameter_declarator)->set_location(yylloc);
	   (yyval.parameter_declarator)->type = new(ctx) ast_fully_specified_type();
	   (yyval.parameter_declarator)->type->set_location(yylloc);
	   (yyval.parameter_declarator)->type->specifier = (yyvsp[(1) - (2)].type_specifier);
	   (yyval.parameter_declarator)->identifier = (yyvsp[(2) - (2)].identifier);
	}
    break;

  case 120:

/* Line 1806 of yacc.c  */
#line 830 "glsl_parser.yy"
    {
	   void *ctx = state;
	   (yyval.parameter_declarator) = new(ctx) ast_parameter_declarator();
	   (yyval.parameter_declarator)->set_location(yylloc);
	   (yyval.parameter_declarator)->type = new(ctx) ast_fully_specified_type();
	   (yyval.parameter_declarator)->type->set_location(yylloc);
	   (yyval.parameter_declarator)->type->specifier = (yyvsp[(1) - (5)].type_specifier);
	   (yyval.parameter_declarator)->identifier = (yyvsp[(2) - (5)].identifier);
	   (yyval.parameter_declarator)->is_array = true;
	   (yyval.parameter_declarator)->array_size = (yyvsp[(4) - (5)].expression);
	}
    break;

  case 121:

/* Line 1806 of yacc.c  */
#line 845 "glsl_parser.yy"
    {
	   (yyvsp[(1) - (3)].type_qualifier).flags.i |= (yyvsp[(2) - (3)].type_qualifier).flags.i;

	   (yyval.parameter_declarator) = (yyvsp[(3) - (3)].parameter_declarator);
	   (yyval.parameter_declarator)->type->qualifier = (yyvsp[(1) - (3)].type_qualifier);
	}
    break;

  case 122:

/* Line 1806 of yacc.c  */
#line 852 "glsl_parser.yy"
    {
	   (yyval.parameter_declarator) = (yyvsp[(2) - (2)].parameter_declarator);
	   (yyval.parameter_declarator)->type->qualifier = (yyvsp[(1) - (2)].type_qualifier);
	}
    break;

  case 123:

/* Line 1806 of yacc.c  */
#line 857 "glsl_parser.yy"
    {
	   void *ctx = state;
	   (yyvsp[(1) - (3)].type_qualifier).flags.i |= (yyvsp[(2) - (3)].type_qualifier).flags.i;

	   (yyval.parameter_declarator) = new(ctx) ast_parameter_declarator();
	   (yyval.parameter_declarator)->set_location(yylloc);
	   (yyval.parameter_declarator)->type = new(ctx) ast_fully_specified_type();
	   (yyval.parameter_declarator)->type->qualifier = (yyvsp[(1) - (3)].type_qualifier);
	   (yyval.parameter_declarator)->type->specifier = (yyvsp[(3) - (3)].type_specifier);
	}
    break;

  case 124:

/* Line 1806 of yacc.c  */
#line 868 "glsl_parser.yy"
    {
	   void *ctx = state;
	   (yyval.parameter_declarator) = new(ctx) ast_parameter_declarator();
	   (yyval.parameter_declarator)->set_location(yylloc);
	   (yyval.parameter_declarator)->type = new(ctx) ast_fully_specified_type();
	   (yyval.parameter_declarator)->type->qualifier = (yyvsp[(1) - (2)].type_qualifier);
	   (yyval.parameter_declarator)->type->specifier = (yyvsp[(2) - (2)].type_specifier);
	}
    break;

  case 125:

/* Line 1806 of yacc.c  */
#line 880 "glsl_parser.yy"
    {
	   memset(& (yyval.type_qualifier), 0, sizeof((yyval.type_qualifier)));
	}
    break;

  case 126:

/* Line 1806 of yacc.c  */
#line 884 "glsl_parser.yy"
    {
	   memset(& (yyval.type_qualifier), 0, sizeof((yyval.type_qualifier)));
	   (yyval.type_qualifier).flags.q.in = 1;
	}
    break;

  case 127:

/* Line 1806 of yacc.c  */
#line 889 "glsl_parser.yy"
    {
	   memset(& (yyval.type_qualifier), 0, sizeof((yyval.type_qualifier)));
	   (yyval.type_qualifier).flags.q.out = 1;
	}
    break;

  case 128:

/* Line 1806 of yacc.c  */
#line 894 "glsl_parser.yy"
    {
	   memset(& (yyval.type_qualifier), 0, sizeof((yyval.type_qualifier)));
	   (yyval.type_qualifier).flags.q.in = 1;
	   (yyval.type_qualifier).flags.q.out = 1;
	}
    break;

  case 131:

/* Line 1806 of yacc.c  */
#line 908 "glsl_parser.yy"
    {
	   void *ctx = state;
	   ast_declaration *decl = new(ctx) ast_declaration((yyvsp[(3) - (3)].identifier), false, NULL, NULL);
	   decl->set_location(yylloc);

	   (yyval.declarator_list) = (yyvsp[(1) - (3)].declarator_list);
	   (yyval.declarator_list)->declarations.push_tail(&decl->link);
	   state->symbols->add_variable(new(state) ir_variable(NULL, (yyvsp[(3) - (3)].identifier), ir_var_auto));
	}
    break;

  case 132:

/* Line 1806 of yacc.c  */
#line 918 "glsl_parser.yy"
    {
	   void *ctx = state;
	   ast_declaration *decl = new(ctx) ast_declaration((yyvsp[(3) - (5)].identifier), true, NULL, NULL);
	   decl->set_location(yylloc);

	   (yyval.declarator_list) = (yyvsp[(1) - (5)].declarator_list);
	   (yyval.declarator_list)->declarations.push_tail(&decl->link);
	   state->symbols->add_variable(new(state) ir_variable(NULL, (yyvsp[(3) - (5)].identifier), ir_var_auto));
	}
    break;

  case 133:

/* Line 1806 of yacc.c  */
#line 928 "glsl_parser.yy"
    {
	   void *ctx = state;
	   ast_declaration *decl = new(ctx) ast_declaration((yyvsp[(3) - (6)].identifier), true, (yyvsp[(5) - (6)].expression), NULL);
	   decl->set_location(yylloc);

	   (yyval.declarator_list) = (yyvsp[(1) - (6)].declarator_list);
	   (yyval.declarator_list)->declarations.push_tail(&decl->link);
	   state->symbols->add_variable(new(state) ir_variable(NULL, (yyvsp[(3) - (6)].identifier), ir_var_auto));
	}
    break;

  case 134:

/* Line 1806 of yacc.c  */
#line 938 "glsl_parser.yy"
    {
	   void *ctx = state;
	   ast_declaration *decl = new(ctx) ast_declaration((yyvsp[(3) - (7)].identifier), true, NULL, (yyvsp[(7) - (7)].expression));
	   decl->set_location(yylloc);

	   (yyval.declarator_list) = (yyvsp[(1) - (7)].declarator_list);
	   (yyval.declarator_list)->declarations.push_tail(&decl->link);
	   state->symbols->add_variable(new(state) ir_variable(NULL, (yyvsp[(3) - (7)].identifier), ir_var_auto));
	}
    break;

  case 135:

/* Line 1806 of yacc.c  */
#line 948 "glsl_parser.yy"
    {
	   void *ctx = state;
	   ast_declaration *decl = new(ctx) ast_declaration((yyvsp[(3) - (8)].identifier), true, (yyvsp[(5) - (8)].expression), (yyvsp[(8) - (8)].expression));
	   decl->set_location(yylloc);

	   (yyval.declarator_list) = (yyvsp[(1) - (8)].declarator_list);
	   (yyval.declarator_list)->declarations.push_tail(&decl->link);
	   state->symbols->add_variable(new(state) ir_variable(NULL, (yyvsp[(3) - (8)].identifier), ir_var_auto));
	}
    break;

  case 136:

/* Line 1806 of yacc.c  */
#line 958 "glsl_parser.yy"
    {
	   void *ctx = state;
	   ast_declaration *decl = new(ctx) ast_declaration((yyvsp[(3) - (5)].identifier), false, NULL, (yyvsp[(5) - (5)].expression));
	   decl->set_location(yylloc);

	   (yyval.declarator_list) = (yyvsp[(1) - (5)].declarator_list);
	   (yyval.declarator_list)->declarations.push_tail(&decl->link);
	   state->symbols->add_variable(new(state) ir_variable(NULL, (yyvsp[(3) - (5)].identifier), ir_var_auto));
	}
    break;

  case 137:

/* Line 1806 of yacc.c  */
#line 972 "glsl_parser.yy"
    {
	   void *ctx = state;
	   /* Empty declaration list is valid. */
	   (yyval.declarator_list) = new(ctx) ast_declarator_list((yyvsp[(1) - (1)].fully_specified_type));
	   (yyval.declarator_list)->set_location(yylloc);
	}
    break;

  case 138:

/* Line 1806 of yacc.c  */
#line 979 "glsl_parser.yy"
    {
	   void *ctx = state;
	   ast_declaration *decl = new(ctx) ast_declaration((yyvsp[(2) - (2)].identifier), false, NULL, NULL);

	   (yyval.declarator_list) = new(ctx) ast_declarator_list((yyvsp[(1) - (2)].fully_specified_type));
	   (yyval.declarator_list)->set_location(yylloc);
	   (yyval.declarator_list)->declarations.push_tail(&decl->link);
	}
    break;

  case 139:

/* Line 1806 of yacc.c  */
#line 988 "glsl_parser.yy"
    {
	   void *ctx = state;
	   ast_declaration *decl = new(ctx) ast_declaration((yyvsp[(2) - (4)].identifier), true, NULL, NULL);

	   (yyval.declarator_list) = new(ctx) ast_declarator_list((yyvsp[(1) - (4)].fully_specified_type));
	   (yyval.declarator_list)->set_location(yylloc);
	   (yyval.declarator_list)->declarations.push_tail(&decl->link);
	}
    break;

  case 140:

/* Line 1806 of yacc.c  */
#line 997 "glsl_parser.yy"
    {
	   void *ctx = state;
	   ast_declaration *decl = new(ctx) ast_declaration((yyvsp[(2) - (5)].identifier), true, (yyvsp[(4) - (5)].expression), NULL);

	   (yyval.declarator_list) = new(ctx) ast_declarator_list((yyvsp[(1) - (5)].fully_specified_type));
	   (yyval.declarator_list)->set_location(yylloc);
	   (yyval.declarator_list)->declarations.push_tail(&decl->link);
	}
    break;

  case 141:

/* Line 1806 of yacc.c  */
#line 1006 "glsl_parser.yy"
    {
	   void *ctx = state;
	   ast_declaration *decl = new(ctx) ast_declaration((yyvsp[(2) - (6)].identifier), true, NULL, (yyvsp[(6) - (6)].expression));

	   (yyval.declarator_list) = new(ctx) ast_declarator_list((yyvsp[(1) - (6)].fully_specified_type));
	   (yyval.declarator_list)->set_location(yylloc);
	   (yyval.declarator_list)->declarations.push_tail(&decl->link);
	}
    break;

  case 142:

/* Line 1806 of yacc.c  */
#line 1015 "glsl_parser.yy"
    {
	   void *ctx = state;
	   ast_declaration *decl = new(ctx) ast_declaration((yyvsp[(2) - (7)].identifier), true, (yyvsp[(4) - (7)].expression), (yyvsp[(7) - (7)].expression));

	   (yyval.declarator_list) = new(ctx) ast_declarator_list((yyvsp[(1) - (7)].fully_specified_type));
	   (yyval.declarator_list)->set_location(yylloc);
	   (yyval.declarator_list)->declarations.push_tail(&decl->link);
	}
    break;

  case 143:

/* Line 1806 of yacc.c  */
#line 1024 "glsl_parser.yy"
    {
	   void *ctx = state;
	   ast_declaration *decl = new(ctx) ast_declaration((yyvsp[(2) - (4)].identifier), false, NULL, (yyvsp[(4) - (4)].expression));

	   (yyval.declarator_list) = new(ctx) ast_declarator_list((yyvsp[(1) - (4)].fully_specified_type));
	   (yyval.declarator_list)->set_location(yylloc);
	   (yyval.declarator_list)->declarations.push_tail(&decl->link);
	}
    break;

  case 144:

/* Line 1806 of yacc.c  */
#line 1033 "glsl_parser.yy"
    {
	   void *ctx = state;
	   ast_declaration *decl = new(ctx) ast_declaration((yyvsp[(2) - (2)].identifier), false, NULL, NULL);

	   (yyval.declarator_list) = new(ctx) ast_declarator_list(NULL);
	   (yyval.declarator_list)->set_location(yylloc);
	   (yyval.declarator_list)->invariant = true;

	   (yyval.declarator_list)->declarations.push_tail(&decl->link);
	}
    break;

  case 145:

/* Line 1806 of yacc.c  */
#line 1047 "glsl_parser.yy"
    {
	   void *ctx = state;
	   (yyval.fully_specified_type) = new(ctx) ast_fully_specified_type();
	   (yyval.fully_specified_type)->set_location(yylloc);
	   (yyval.fully_specified_type)->specifier = (yyvsp[(1) - (1)].type_specifier);
	}
    break;

  case 146:

/* Line 1806 of yacc.c  */
#line 1054 "glsl_parser.yy"
    {
	   void *ctx = state;
	   (yyval.fully_specified_type) = new(ctx) ast_fully_specified_type();
	   (yyval.fully_specified_type)->set_location(yylloc);
	   (yyval.fully_specified_type)->qualifier = (yyvsp[(1) - (2)].type_qualifier);
	   (yyval.fully_specified_type)->specifier = (yyvsp[(2) - (2)].type_specifier);
	}
    break;

  case 147:

/* Line 1806 of yacc.c  */
#line 1065 "glsl_parser.yy"
    {
	  (yyval.type_qualifier) = (yyvsp[(3) - (4)].type_qualifier);
	}
    break;

  case 149:

/* Line 1806 of yacc.c  */
#line 1073 "glsl_parser.yy"
    {
	   if (((yyvsp[(1) - (3)].type_qualifier).flags.i & (yyvsp[(3) - (3)].type_qualifier).flags.i) != 0) {
	      _mesa_glsl_error(& (yylsp[(3) - (3)]), state,
			       "duplicate layout qualifiers used\n");
	      YYERROR;
	   }

	   (yyval.type_qualifier).flags.i = (yyvsp[(1) - (3)].type_qualifier).flags.i | (yyvsp[(3) - (3)].type_qualifier).flags.i;

	   if ((yyvsp[(1) - (3)].type_qualifier).flags.q.explicit_location)
	      (yyval.type_qualifier).location = (yyvsp[(1) - (3)].type_qualifier).location;

	   if ((yyvsp[(3) - (3)].type_qualifier).flags.q.explicit_location)
	      (yyval.type_qualifier).location = (yyvsp[(3) - (3)].type_qualifier).location;
	}
    break;

  case 150:

/* Line 1806 of yacc.c  */
#line 1092 "glsl_parser.yy"
    {
	   bool got_one = false;

	   memset(& (yyval.type_qualifier), 0, sizeof((yyval.type_qualifier)));

	   /* Layout qualifiers for ARB_fragment_coord_conventions. */
	   if (!got_one && state->ARB_fragment_coord_conventions_enable) {
	      if (strcmp((yyvsp[(1) - (1)].identifier), "origin_upper_left") == 0) {
		 got_one = true;
		 (yyval.type_qualifier).flags.q.origin_upper_left = 1;
	      } else if (strcmp((yyvsp[(1) - (1)].identifier), "pixel_center_integer") == 0) {
		 got_one = true;
		 (yyval.type_qualifier).flags.q.pixel_center_integer = 1;
	      }

	      if (got_one && state->ARB_fragment_coord_conventions_warn) {
		 _mesa_glsl_warning(& (yylsp[(1) - (1)]), state,
				    "GL_ARB_fragment_coord_conventions layout "
				    "identifier `%s' used\n", (yyvsp[(1) - (1)].identifier));
	      }
	   }

	   /* Layout qualifiers for AMD_conservative_depth. */
	   if (!got_one && state->AMD_conservative_depth_enable) {
	      if (strcmp((yyvsp[(1) - (1)].identifier), "depth_any") == 0) {
	         got_one = true;
	         (yyval.type_qualifier).flags.q.depth_any = 1;
	      } else if (strcmp((yyvsp[(1) - (1)].identifier), "depth_greater") == 0) {
	         got_one = true;
	         (yyval.type_qualifier).flags.q.depth_greater = 1;
	      } else if (strcmp((yyvsp[(1) - (1)].identifier), "depth_less") == 0) {
	         got_one = true;
	         (yyval.type_qualifier).flags.q.depth_less = 1;
	      } else if (strcmp((yyvsp[(1) - (1)].identifier), "depth_unchanged") == 0) {
	         got_one = true;
	         (yyval.type_qualifier).flags.q.depth_unchanged = 1;
	      }
	
	      if (got_one && state->AMD_conservative_depth_warn) {
	         _mesa_glsl_warning(& (yylsp[(1) - (1)]), state,
	                            "GL_AMD_conservative_depth "
	                            "layout qualifier `%s' is used\n", (yyvsp[(1) - (1)].identifier));
	      }
	   }

	   if (!got_one) {
	      _mesa_glsl_error(& (yylsp[(1) - (1)]), state, "unrecognized layout identifier "
			       "`%s'\n", (yyvsp[(1) - (1)].identifier));
	      YYERROR;
	   }
	}
    break;

  case 151:

/* Line 1806 of yacc.c  */
#line 1144 "glsl_parser.yy"
    {
	   bool got_one = false;

	   memset(& (yyval.type_qualifier), 0, sizeof((yyval.type_qualifier)));

	   if (state->ARB_explicit_attrib_location_enable) {
	      /* FINISHME: Handle 'index' once GL_ARB_blend_func_exteneded and
	       * FINISHME: GLSL 1.30 (or later) are supported.
	       */
	      if (strcmp("location", (yyvsp[(1) - (3)].identifier)) == 0) {
		 got_one = true;

		 (yyval.type_qualifier).flags.q.explicit_location = 1;

		 if ((yyvsp[(3) - (3)].n) >= 0) {
		    (yyval.type_qualifier).location = (yyvsp[(3) - (3)].n);
		 } else {
		    _mesa_glsl_error(& (yylsp[(3) - (3)]), state,
				     "invalid location %d specified\n", (yyvsp[(3) - (3)].n));
		    YYERROR;
		 }
	      }
	   }

	   /* If the identifier didn't match any known layout identifiers,
	    * emit an error.
	    */
	   if (!got_one) {
	      _mesa_glsl_error(& (yylsp[(1) - (3)]), state, "unrecognized layout identifier "
			       "`%s'\n", (yyvsp[(1) - (3)].identifier));
	      YYERROR;
	   } else if (state->ARB_explicit_attrib_location_warn) {
	      _mesa_glsl_warning(& (yylsp[(1) - (3)]), state,
				 "GL_ARB_explicit_attrib_location layout "
				 "identifier `%s' used\n", (yyvsp[(1) - (3)].identifier));
	   }
	}
    break;

  case 152:

/* Line 1806 of yacc.c  */
#line 1185 "glsl_parser.yy"
    {
	   memset(& (yyval.type_qualifier), 0, sizeof((yyval.type_qualifier)));
	   (yyval.type_qualifier).flags.q.smooth = 1;
	}
    break;

  case 153:

/* Line 1806 of yacc.c  */
#line 1190 "glsl_parser.yy"
    {
	   memset(& (yyval.type_qualifier), 0, sizeof((yyval.type_qualifier)));
	   (yyval.type_qualifier).flags.q.flat = 1;
	}
    break;

  case 154:

/* Line 1806 of yacc.c  */
#line 1195 "glsl_parser.yy"
    {
	   memset(& (yyval.type_qualifier), 0, sizeof((yyval.type_qualifier)));
	   (yyval.type_qualifier).flags.q.noperspective = 1;
	}
    break;

  case 155:

/* Line 1806 of yacc.c  */
#line 1203 "glsl_parser.yy"
    {
	   memset(& (yyval.type_qualifier), 0, sizeof((yyval.type_qualifier)));
	   (yyval.type_qualifier).flags.q.constant = 1;
	}
    break;

  case 158:

/* Line 1806 of yacc.c  */
#line 1213 "glsl_parser.yy"
    {
	   (yyval.type_qualifier) = (yyvsp[(1) - (2)].type_qualifier);
	   (yyval.type_qualifier).flags.i |= (yyvsp[(2) - (2)].type_qualifier).flags.i;
	}
    break;

  case 160:

/* Line 1806 of yacc.c  */
#line 1219 "glsl_parser.yy"
    {
	   (yyval.type_qualifier) = (yyvsp[(1) - (2)].type_qualifier);
	   (yyval.type_qualifier).flags.i |= (yyvsp[(2) - (2)].type_qualifier).flags.i;
	}
    break;

  case 161:

/* Line 1806 of yacc.c  */
#line 1224 "glsl_parser.yy"
    {
	   (yyval.type_qualifier) = (yyvsp[(2) - (2)].type_qualifier);
	   (yyval.type_qualifier).flags.q.invariant = 1;
	}
    break;

  case 162:

/* Line 1806 of yacc.c  */
#line 1229 "glsl_parser.yy"
    {
	   (yyval.type_qualifier) = (yyvsp[(2) - (3)].type_qualifier);
	   (yyval.type_qualifier).flags.i |= (yyvsp[(3) - (3)].type_qualifier).flags.i;
	   (yyval.type_qualifier).flags.q.invariant = 1;
	}
    break;

  case 163:

/* Line 1806 of yacc.c  */
#line 1235 "glsl_parser.yy"
    {
	   memset(& (yyval.type_qualifier), 0, sizeof((yyval.type_qualifier)));
	   (yyval.type_qualifier).flags.q.invariant = 1;
	}
    break;

  case 164:

/* Line 1806 of yacc.c  */
#line 1243 "glsl_parser.yy"
    {
	   memset(& (yyval.type_qualifier), 0, sizeof((yyval.type_qualifier)));
	   (yyval.type_qualifier).flags.q.constant = 1;
	}
    break;

  case 165:

/* Line 1806 of yacc.c  */
#line 1248 "glsl_parser.yy"
    {
	   memset(& (yyval.type_qualifier), 0, sizeof((yyval.type_qualifier)));
	   (yyval.type_qualifier).flags.q.attribute = 1;
	}
    break;

  case 166:

/* Line 1806 of yacc.c  */
#line 1253 "glsl_parser.yy"
    {
	   memset(& (yyval.type_qualifier), 0, sizeof((yyval.type_qualifier)));
	   (yyval.type_qualifier).flags.q.varying = 1;
	}
    break;

  case 167:

/* Line 1806 of yacc.c  */
#line 1258 "glsl_parser.yy"
    {
	   memset(& (yyval.type_qualifier), 0, sizeof((yyval.type_qualifier)));
	   (yyval.type_qualifier).flags.q.centroid = 1;
	   (yyval.type_qualifier).flags.q.varying = 1;
	}
    break;

  case 168:

/* Line 1806 of yacc.c  */
#line 1264 "glsl_parser.yy"
    {
	   memset(& (yyval.type_qualifier), 0, sizeof((yyval.type_qualifier)));
	   (yyval.type_qualifier).flags.q.in = 1;
	}
    break;

  case 169:

/* Line 1806 of yacc.c  */
#line 1269 "glsl_parser.yy"
    {
	   memset(& (yyval.type_qualifier), 0, sizeof((yyval.type_qualifier)));
	   (yyval.type_qualifier).flags.q.out = 1;
	}
    break;

  case 170:

/* Line 1806 of yacc.c  */
#line 1274 "glsl_parser.yy"
    {
	   memset(& (yyval.type_qualifier), 0, sizeof((yyval.type_qualifier)));
	   (yyval.type_qualifier).flags.q.centroid = 1; (yyval.type_qualifier).flags.q.in = 1;
	}
    break;

  case 171:

/* Line 1806 of yacc.c  */
#line 1279 "glsl_parser.yy"
    {
	   memset(& (yyval.type_qualifier), 0, sizeof((yyval.type_qualifier)));
	   (yyval.type_qualifier).flags.q.centroid = 1; (yyval.type_qualifier).flags.q.out = 1;
	}
    break;

  case 172:

/* Line 1806 of yacc.c  */
#line 1284 "glsl_parser.yy"
    {
	   memset(& (yyval.type_qualifier), 0, sizeof((yyval.type_qualifier)));
	   (yyval.type_qualifier).flags.q.uniform = 1;
	}
    break;

  case 173:

/* Line 1806 of yacc.c  */
#line 1292 "glsl_parser.yy"
    {
	   (yyval.type_specifier) = (yyvsp[(1) - (1)].type_specifier);
	}
    break;

  case 174:

/* Line 1806 of yacc.c  */
#line 1296 "glsl_parser.yy"
    {
	   (yyval.type_specifier) = (yyvsp[(2) - (2)].type_specifier);
	   (yyval.type_specifier)->precision = (yyvsp[(1) - (2)].n);
	}
    break;

  case 176:

/* Line 1806 of yacc.c  */
#line 1305 "glsl_parser.yy"
    {
	   (yyval.type_specifier) = (yyvsp[(1) - (3)].type_specifier);
	   (yyval.type_specifier)->is_array = true;
	   (yyval.type_specifier)->array_size = NULL;
	}
    break;

  case 177:

/* Line 1806 of yacc.c  */
#line 1311 "glsl_parser.yy"
    {
	   (yyval.type_specifier) = (yyvsp[(1) - (4)].type_specifier);
	   (yyval.type_specifier)->is_array = true;
	   (yyval.type_specifier)->array_size = (yyvsp[(3) - (4)].expression);
	}
    break;

  case 178:

/* Line 1806 of yacc.c  */
#line 1320 "glsl_parser.yy"
    {
	   void *ctx = state;
	   (yyval.type_specifier) = new(ctx) ast_type_specifier((yyvsp[(1) - (1)].n));
	   (yyval.type_specifier)->set_location(yylloc);
	}
    break;

  case 179:

/* Line 1806 of yacc.c  */
#line 1326 "glsl_parser.yy"
    {
	   void *ctx = state;
	   (yyval.type_specifier) = new(ctx) ast_type_specifier((yyvsp[(1) - (1)].struct_specifier));
	   (yyval.type_specifier)->set_location(yylloc);
	}
    break;

  case 180:

/* Line 1806 of yacc.c  */
#line 1332 "glsl_parser.yy"
    {
	   void *ctx = state;
	   (yyval.type_specifier) = new(ctx) ast_type_specifier((yyvsp[(1) - (1)].identifier));
	   (yyval.type_specifier)->set_location(yylloc);
	}
    break;

  case 181:

/* Line 1806 of yacc.c  */
#line 1340 "glsl_parser.yy"
    { (yyval.n) = ast_void; }
    break;

  case 182:

/* Line 1806 of yacc.c  */
#line 1341 "glsl_parser.yy"
    { (yyval.n) = ast_float; }
    break;

  case 183:

/* Line 1806 of yacc.c  */
#line 1342 "glsl_parser.yy"
    { (yyval.n) = ast_int; }
    break;

  case 184:

/* Line 1806 of yacc.c  */
#line 1343 "glsl_parser.yy"
    { (yyval.n) = ast_uint; }
    break;

  case 185:

/* Line 1806 of yacc.c  */
#line 1344 "glsl_parser.yy"
    { (yyval.n) = ast_bool; }
    break;

  case 186:

/* Line 1806 of yacc.c  */
#line 1345 "glsl_parser.yy"
    { (yyval.n) = ast_vec2; }
    break;

  case 187:

/* Line 1806 of yacc.c  */
#line 1346 "glsl_parser.yy"
    { (yyval.n) = ast_vec3; }
    break;

  case 188:

/* Line 1806 of yacc.c  */
#line 1347 "glsl_parser.yy"
    { (yyval.n) = ast_vec4; }
    break;

  case 189:

/* Line 1806 of yacc.c  */
#line 1348 "glsl_parser.yy"
    { (yyval.n) = ast_bvec2; }
    break;

  case 190:

/* Line 1806 of yacc.c  */
#line 1349 "glsl_parser.yy"
    { (yyval.n) = ast_bvec3; }
    break;

  case 191:

/* Line 1806 of yacc.c  */
#line 1350 "glsl_parser.yy"
    { (yyval.n) = ast_bvec4; }
    break;

  case 192:

/* Line 1806 of yacc.c  */
#line 1351 "glsl_parser.yy"
    { (yyval.n) = ast_ivec2; }
    break;

  case 193:

/* Line 1806 of yacc.c  */
#line 1352 "glsl_parser.yy"
    { (yyval.n) = ast_ivec3; }
    break;

  case 194:

/* Line 1806 of yacc.c  */
#line 1353 "glsl_parser.yy"
    { (yyval.n) = ast_ivec4; }
    break;

  case 195:

/* Line 1806 of yacc.c  */
#line 1354 "glsl_parser.yy"
    { (yyval.n) = ast_uvec2; }
    break;

  case 196:

/* Line 1806 of yacc.c  */
#line 1355 "glsl_parser.yy"
    { (yyval.n) = ast_uvec3; }
    break;

  case 197:

/* Line 1806 of yacc.c  */
#line 1356 "glsl_parser.yy"
    { (yyval.n) = ast_uvec4; }
    break;

  case 198:

/* Line 1806 of yacc.c  */
#line 1357 "glsl_parser.yy"
    { (yyval.n) = ast_mat2; }
    break;

  case 199:

/* Line 1806 of yacc.c  */
#line 1358 "glsl_parser.yy"
    { (yyval.n) = ast_mat2x3; }
    break;

  case 200:

/* Line 1806 of yacc.c  */
#line 1359 "glsl_parser.yy"
    { (yyval.n) = ast_mat2x4; }
    break;

  case 201:

/* Line 1806 of yacc.c  */
#line 1360 "glsl_parser.yy"
    { (yyval.n) = ast_mat3x2; }
    break;

  case 202:

/* Line 1806 of yacc.c  */
#line 1361 "glsl_parser.yy"
    { (yyval.n) = ast_mat3; }
    break;

  case 203:

/* Line 1806 of yacc.c  */
#line 1362 "glsl_parser.yy"
    { (yyval.n) = ast_mat3x4; }
    break;

  case 204:

/* Line 1806 of yacc.c  */
#line 1363 "glsl_parser.yy"
    { (yyval.n) = ast_mat4x2; }
    break;

  case 205:

/* Line 1806 of yacc.c  */
#line 1364 "glsl_parser.yy"
    { (yyval.n) = ast_mat4x3; }
    break;

  case 206:

/* Line 1806 of yacc.c  */
#line 1365 "glsl_parser.yy"
    { (yyval.n) = ast_mat4; }
    break;

  case 207:

/* Line 1806 of yacc.c  */
#line 1366 "glsl_parser.yy"
    { (yyval.n) = ast_sampler1d; }
    break;

  case 208:

/* Line 1806 of yacc.c  */
#line 1367 "glsl_parser.yy"
    { (yyval.n) = ast_sampler2d; }
    break;

  case 209:

/* Line 1806 of yacc.c  */
#line 1368 "glsl_parser.yy"
    { (yyval.n) = ast_sampler2drect; }
    break;

  case 210:

/* Line 1806 of yacc.c  */
#line 1369 "glsl_parser.yy"
    { (yyval.n) = ast_sampler3d; }
    break;

  case 211:

/* Line 1806 of yacc.c  */
#line 1370 "glsl_parser.yy"
    { (yyval.n) = ast_samplercube; }
    break;

  case 212:

/* Line 1806 of yacc.c  */
#line 1371 "glsl_parser.yy"
    { (yyval.n) = ast_sampler1dshadow; }
    break;

  case 213:

/* Line 1806 of yacc.c  */
#line 1372 "glsl_parser.yy"
    { (yyval.n) = ast_sampler2dshadow; }
    break;

  case 214:

/* Line 1806 of yacc.c  */
#line 1373 "glsl_parser.yy"
    { (yyval.n) = ast_sampler2drectshadow; }
    break;

  case 215:

/* Line 1806 of yacc.c  */
#line 1374 "glsl_parser.yy"
    { (yyval.n) = ast_samplercubeshadow; }
    break;

  case 216:

/* Line 1806 of yacc.c  */
#line 1375 "glsl_parser.yy"
    { (yyval.n) = ast_sampler1darray; }
    break;

  case 217:

/* Line 1806 of yacc.c  */
#line 1376 "glsl_parser.yy"
    { (yyval.n) = ast_sampler2darray; }
    break;

  case 218:

/* Line 1806 of yacc.c  */
#line 1377 "glsl_parser.yy"
    { (yyval.n) = ast_sampler1darrayshadow; }
    break;

  case 219:

/* Line 1806 of yacc.c  */
#line 1378 "glsl_parser.yy"
    { (yyval.n) = ast_sampler2darrayshadow; }
    break;

  case 220:

/* Line 1806 of yacc.c  */
#line 1379 "glsl_parser.yy"
    { (yyval.n) = ast_isampler1d; }
    break;

  case 221:

/* Line 1806 of yacc.c  */
#line 1380 "glsl_parser.yy"
    { (yyval.n) = ast_isampler2d; }
    break;

  case 222:

/* Line 1806 of yacc.c  */
#line 1381 "glsl_parser.yy"
    { (yyval.n) = ast_isampler3d; }
    break;

  case 223:

/* Line 1806 of yacc.c  */
#line 1382 "glsl_parser.yy"
    { (yyval.n) = ast_isamplercube; }
    break;

  case 224:

/* Line 1806 of yacc.c  */
#line 1383 "glsl_parser.yy"
    { (yyval.n) = ast_isampler1darray; }
    break;

  case 225:

/* Line 1806 of yacc.c  */
#line 1384 "glsl_parser.yy"
    { (yyval.n) = ast_isampler2darray; }
    break;

  case 226:

/* Line 1806 of yacc.c  */
#line 1385 "glsl_parser.yy"
    { (yyval.n) = ast_usampler1d; }
    break;

  case 227:

/* Line 1806 of yacc.c  */
#line 1386 "glsl_parser.yy"
    { (yyval.n) = ast_usampler2d; }
    break;

  case 228:

/* Line 1806 of yacc.c  */
#line 1387 "glsl_parser.yy"
    { (yyval.n) = ast_usampler3d; }
    break;

  case 229:

/* Line 1806 of yacc.c  */
#line 1388 "glsl_parser.yy"
    { (yyval.n) = ast_usamplercube; }
    break;

  case 230:

/* Line 1806 of yacc.c  */
#line 1389 "glsl_parser.yy"
    { (yyval.n) = ast_usampler1darray; }
    break;

  case 231:

/* Line 1806 of yacc.c  */
#line 1390 "glsl_parser.yy"
    { (yyval.n) = ast_usampler2darray; }
    break;

  case 232:

/* Line 1806 of yacc.c  */
#line 1394 "glsl_parser.yy"
    {
		     if (!state->es_shader && state->language_version < 130)
			_mesa_glsl_error(& (yylsp[(1) - (1)]), state,
				         "precision qualifier forbidden "
					 "in %s (1.30 or later "
					 "required)\n",
					 state->version_string);

		     (yyval.n) = ast_precision_high;
		  }
    break;

  case 233:

/* Line 1806 of yacc.c  */
#line 1404 "glsl_parser.yy"
    {
		     if (!state->es_shader && state->language_version < 130)
			_mesa_glsl_error(& (yylsp[(1) - (1)]), state,
					 "precision qualifier forbidden "
					 "in %s (1.30 or later "
					 "required)\n",
					 state->version_string);

		     (yyval.n) = ast_precision_medium;
		  }
    break;

  case 234:

/* Line 1806 of yacc.c  */
#line 1414 "glsl_parser.yy"
    {
		     if (!state->es_shader && state->language_version < 130)
			_mesa_glsl_error(& (yylsp[(1) - (1)]), state,
					 "precision qualifier forbidden "
					 "in %s (1.30 or later "
					 "required)\n",
					 state->version_string);

		     (yyval.n) = ast_precision_low;
		  }
    break;

  case 235:

/* Line 1806 of yacc.c  */
#line 1428 "glsl_parser.yy"
    {
	   void *ctx = state;
	   (yyval.struct_specifier) = new(ctx) ast_struct_specifier((yyvsp[(2) - (5)].identifier), (yyvsp[(4) - (5)].node));
	   (yyval.struct_specifier)->set_location(yylloc);
	   state->symbols->add_type((yyvsp[(2) - (5)].identifier), glsl_type::void_type);
	}
    break;

  case 236:

/* Line 1806 of yacc.c  */
#line 1435 "glsl_parser.yy"
    {
	   void *ctx = state;
	   (yyval.struct_specifier) = new(ctx) ast_struct_specifier(NULL, (yyvsp[(3) - (4)].node));
	   (yyval.struct_specifier)->set_location(yylloc);
	}
    break;

  case 237:

/* Line 1806 of yacc.c  */
#line 1444 "glsl_parser.yy"
    {
	   (yyval.node) = (ast_node *) (yyvsp[(1) - (1)].declarator_list);
	   (yyvsp[(1) - (1)].declarator_list)->link.self_link();
	}
    break;

  case 238:

/* Line 1806 of yacc.c  */
#line 1449 "glsl_parser.yy"
    {
	   (yyval.node) = (ast_node *) (yyvsp[(1) - (2)].node);
	   (yyval.node)->link.insert_before(& (yyvsp[(2) - (2)].declarator_list)->link);
	}
    break;

  case 239:

/* Line 1806 of yacc.c  */
#line 1457 "glsl_parser.yy"
    {
	   void *ctx = state;
	   ast_fully_specified_type *type = new(ctx) ast_fully_specified_type();
	   type->set_location(yylloc);

	   type->specifier = (yyvsp[(1) - (3)].type_specifier);
	   (yyval.declarator_list) = new(ctx) ast_declarator_list(type);
	   (yyval.declarator_list)->set_location(yylloc);

	   (yyval.declarator_list)->declarations.push_degenerate_list_at_head(& (yyvsp[(2) - (3)].declaration)->link);
	}
    break;

  case 240:

/* Line 1806 of yacc.c  */
#line 1472 "glsl_parser.yy"
    {
	   (yyval.declaration) = (yyvsp[(1) - (1)].declaration);
	   (yyvsp[(1) - (1)].declaration)->link.self_link();
	}
    break;

  case 241:

/* Line 1806 of yacc.c  */
#line 1477 "glsl_parser.yy"
    {
	   (yyval.declaration) = (yyvsp[(1) - (3)].declaration);
	   (yyval.declaration)->link.insert_before(& (yyvsp[(3) - (3)].declaration)->link);
	}
    break;

  case 242:

/* Line 1806 of yacc.c  */
#line 1485 "glsl_parser.yy"
    {
	   void *ctx = state;
	   (yyval.declaration) = new(ctx) ast_declaration((yyvsp[(1) - (1)].identifier), false, NULL, NULL);
	   (yyval.declaration)->set_location(yylloc);
	   state->symbols->add_variable(new(state) ir_variable(NULL, (yyvsp[(1) - (1)].identifier), ir_var_auto));
	}
    break;

  case 243:

/* Line 1806 of yacc.c  */
#line 1492 "glsl_parser.yy"
    {
	   void *ctx = state;
	   (yyval.declaration) = new(ctx) ast_declaration((yyvsp[(1) - (4)].identifier), true, (yyvsp[(3) - (4)].expression), NULL);
	   (yyval.declaration)->set_location(yylloc);
	}
    break;

  case 246:

/* Line 1806 of yacc.c  */
#line 1510 "glsl_parser.yy"
    { (yyval.node) = (ast_node *) (yyvsp[(1) - (1)].compound_statement); }
    break;

  case 251:

/* Line 1806 of yacc.c  */
#line 1518 "glsl_parser.yy"
    { (yyval.node) = NULL; }
    break;

  case 252:

/* Line 1806 of yacc.c  */
#line 1519 "glsl_parser.yy"
    { (yyval.node) = NULL; }
    break;

  case 255:

/* Line 1806 of yacc.c  */
#line 1526 "glsl_parser.yy"
    {
	   void *ctx = state;
	   (yyval.compound_statement) = new(ctx) ast_compound_statement(true, NULL);
	   (yyval.compound_statement)->set_location(yylloc);
	}
    break;

  case 256:

/* Line 1806 of yacc.c  */
#line 1532 "glsl_parser.yy"
    {
	   state->symbols->push_scope();
	}
    break;

  case 257:

/* Line 1806 of yacc.c  */
#line 1536 "glsl_parser.yy"
    {
	   void *ctx = state;
	   (yyval.compound_statement) = new(ctx) ast_compound_statement(true, (yyvsp[(3) - (4)].node));
	   (yyval.compound_statement)->set_location(yylloc);
	   state->symbols->pop_scope();
	}
    break;

  case 258:

/* Line 1806 of yacc.c  */
#line 1545 "glsl_parser.yy"
    { (yyval.node) = (ast_node *) (yyvsp[(1) - (1)].compound_statement); }
    break;

  case 260:

/* Line 1806 of yacc.c  */
#line 1551 "glsl_parser.yy"
    {
	   void *ctx = state;
	   (yyval.compound_statement) = new(ctx) ast_compound_statement(false, NULL);
	   (yyval.compound_statement)->set_location(yylloc);
	}
    break;

  case 261:

/* Line 1806 of yacc.c  */
#line 1557 "glsl_parser.yy"
    {
	   void *ctx = state;
	   (yyval.compound_statement) = new(ctx) ast_compound_statement(false, (yyvsp[(2) - (3)].node));
	   (yyval.compound_statement)->set_location(yylloc);
	}
    break;

  case 262:

/* Line 1806 of yacc.c  */
#line 1566 "glsl_parser.yy"
    {
	   if ((yyvsp[(1) - (1)].node) == NULL) {
	      _mesa_glsl_error(& (yylsp[(1) - (1)]), state, "<nil> statement\n");
	      assert((yyvsp[(1) - (1)].node) != NULL);
	   }

	   (yyval.node) = (yyvsp[(1) - (1)].node);
	   (yyval.node)->link.self_link();
	}
    break;

  case 263:

/* Line 1806 of yacc.c  */
#line 1576 "glsl_parser.yy"
    {
	   if ((yyvsp[(2) - (2)].node) == NULL) {
	      _mesa_glsl_error(& (yylsp[(2) - (2)]), state, "<nil> statement\n");
	      assert((yyvsp[(2) - (2)].node) != NULL);
	   }
	   (yyval.node) = (yyvsp[(1) - (2)].node);
	   (yyval.node)->link.insert_before(& (yyvsp[(2) - (2)].node)->link);
	}
    break;

  case 264:

/* Line 1806 of yacc.c  */
#line 1588 "glsl_parser.yy"
    {
	   void *ctx = state;
	   (yyval.node) = new(ctx) ast_expression_statement(NULL);
	   (yyval.node)->set_location(yylloc);
	}
    break;

  case 265:

/* Line 1806 of yacc.c  */
#line 1594 "glsl_parser.yy"
    {
	   void *ctx = state;
	   (yyval.node) = new(ctx) ast_expression_statement((yyvsp[(1) - (2)].expression));
	   (yyval.node)->set_location(yylloc);
	}
    break;

  case 266:

/* Line 1806 of yacc.c  */
#line 1603 "glsl_parser.yy"
    {
	   (yyval.node) = new(state) ast_selection_statement((yyvsp[(3) - (5)].expression), (yyvsp[(5) - (5)].selection_rest_statement).then_statement,
						   (yyvsp[(5) - (5)].selection_rest_statement).else_statement);
	   (yyval.node)->set_location(yylloc);
	}
    break;

  case 267:

/* Line 1806 of yacc.c  */
#line 1612 "glsl_parser.yy"
    {
	   (yyval.selection_rest_statement).then_statement = (yyvsp[(1) - (3)].node);
	   (yyval.selection_rest_statement).else_statement = (yyvsp[(3) - (3)].node);
	}
    break;

  case 268:

/* Line 1806 of yacc.c  */
#line 1617 "glsl_parser.yy"
    {
	   (yyval.selection_rest_statement).then_statement = (yyvsp[(1) - (1)].node);
	   (yyval.selection_rest_statement).else_statement = NULL;
	}
    break;

  case 269:

/* Line 1806 of yacc.c  */
#line 1625 "glsl_parser.yy"
    {
	   (yyval.node) = (ast_node *) (yyvsp[(1) - (1)].expression);
	}
    break;

  case 270:

/* Line 1806 of yacc.c  */
#line 1629 "glsl_parser.yy"
    {
	   void *ctx = state;
	   ast_declaration *decl = new(ctx) ast_declaration((yyvsp[(2) - (4)].identifier), false, NULL, (yyvsp[(4) - (4)].expression));
	   ast_declarator_list *declarator = new(ctx) ast_declarator_list((yyvsp[(1) - (4)].fully_specified_type));
	   decl->set_location(yylloc);
	   declarator->set_location(yylloc);

	   declarator->declarations.push_tail(&decl->link);
	   (yyval.node) = declarator;
	}
    break;

  case 274:

/* Line 1806 of yacc.c  */
#line 1652 "glsl_parser.yy"
    {
	   void *ctx = state;
	   (yyval.node) = new(ctx) ast_iteration_statement(ast_iteration_statement::ast_while,
	   					    NULL, (yyvsp[(3) - (5)].node), NULL, (yyvsp[(5) - (5)].node));
	   (yyval.node)->set_location(yylloc);
	}
    break;

  case 275:

/* Line 1806 of yacc.c  */
#line 1659 "glsl_parser.yy"
    {
	   void *ctx = state;
	   (yyval.node) = new(ctx) ast_iteration_statement(ast_iteration_statement::ast_do_while,
						    NULL, (yyvsp[(5) - (7)].expression), NULL, (yyvsp[(2) - (7)].node));
	   (yyval.node)->set_location(yylloc);
	}
    break;

  case 276:

/* Line 1806 of yacc.c  */
#line 1666 "glsl_parser.yy"
    {
	   void *ctx = state;
	   (yyval.node) = new(ctx) ast_iteration_statement(ast_iteration_statement::ast_for,
						    (yyvsp[(3) - (6)].node), (yyvsp[(4) - (6)].for_rest_statement).cond, (yyvsp[(4) - (6)].for_rest_statement).rest, (yyvsp[(6) - (6)].node));
	   (yyval.node)->set_location(yylloc);
	}
    break;

  case 280:

/* Line 1806 of yacc.c  */
#line 1682 "glsl_parser.yy"
    {
	   (yyval.node) = NULL;
	}
    break;

  case 281:

/* Line 1806 of yacc.c  */
#line 1689 "glsl_parser.yy"
    {
	   (yyval.for_rest_statement).cond = (yyvsp[(1) - (2)].node);
	   (yyval.for_rest_statement).rest = NULL;
	}
    break;

  case 282:

/* Line 1806 of yacc.c  */
#line 1694 "glsl_parser.yy"
    {
	   (yyval.for_rest_statement).cond = (yyvsp[(1) - (3)].node);
	   (yyval.for_rest_statement).rest = (yyvsp[(3) - (3)].expression);
	}
    break;

  case 283:

/* Line 1806 of yacc.c  */
#line 1703 "glsl_parser.yy"
    {
	   void *ctx = state;
	   (yyval.node) = new(ctx) ast_jump_statement(ast_jump_statement::ast_continue, NULL);
	   (yyval.node)->set_location(yylloc);
	}
    break;

  case 284:

/* Line 1806 of yacc.c  */
#line 1709 "glsl_parser.yy"
    {
	   void *ctx = state;
	   (yyval.node) = new(ctx) ast_jump_statement(ast_jump_statement::ast_break, NULL);
	   (yyval.node)->set_location(yylloc);
	}
    break;

  case 285:

/* Line 1806 of yacc.c  */
#line 1715 "glsl_parser.yy"
    {
	   void *ctx = state;
	   (yyval.node) = new(ctx) ast_jump_statement(ast_jump_statement::ast_return, NULL);
	   (yyval.node)->set_location(yylloc);
	}
    break;

  case 286:

/* Line 1806 of yacc.c  */
#line 1721 "glsl_parser.yy"
    {
	   void *ctx = state;
	   (yyval.node) = new(ctx) ast_jump_statement(ast_jump_statement::ast_return, (yyvsp[(2) - (3)].expression));
	   (yyval.node)->set_location(yylloc);
	}
    break;

  case 287:

/* Line 1806 of yacc.c  */
#line 1727 "glsl_parser.yy"
    {
	   void *ctx = state;
	   (yyval.node) = new(ctx) ast_jump_statement(ast_jump_statement::ast_discard, NULL);
	   (yyval.node)->set_location(yylloc);
	}
    break;

  case 288:

/* Line 1806 of yacc.c  */
#line 1735 "glsl_parser.yy"
    { (yyval.node) = (yyvsp[(1) - (1)].function_definition); }
    break;

  case 289:

/* Line 1806 of yacc.c  */
#line 1736 "glsl_parser.yy"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 290:

/* Line 1806 of yacc.c  */
#line 1737 "glsl_parser.yy"
    { (yyval.node) = NULL; }
    break;

  case 291:

/* Line 1806 of yacc.c  */
#line 1742 "glsl_parser.yy"
    {
	   void *ctx = state;
	   (yyval.function_definition) = new(ctx) ast_function_definition();
	   (yyval.function_definition)->set_location(yylloc);
	   (yyval.function_definition)->prototype = (yyvsp[(1) - (2)].function);
	   (yyval.function_definition)->body = (yyvsp[(2) - (2)].compound_statement);

	   state->symbols->pop_scope();
	}
    break;



/* Line 1806 of yacc.c  */
#line 5267 "glsl_parser.cpp"
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
      yyerror (&yylloc, state, YY_("syntax error"));
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
        yyerror (&yylloc, state, yymsgp);
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
		      yytoken, &yylval, &yylloc, state);
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
		  yystos[yystate], yyvsp, yylsp, state);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;

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

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (&yylloc, state, YY_("memory exhausted"));
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
                  yytoken, &yylval, &yylloc, state);
    }
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp, yylsp, state);
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



