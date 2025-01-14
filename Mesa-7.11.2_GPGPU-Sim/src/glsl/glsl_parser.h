/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison interface for Yacc-like parsers in C
   
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

/* Line 2068 of yacc.c  */
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



/* Line 2068 of yacc.c  */
#line 277 "glsl_parser.h"
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



