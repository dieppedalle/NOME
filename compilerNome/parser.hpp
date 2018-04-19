/* A Bison parser, made by GNU Bison 3.0.  */

/* Bison interface for Yacc-like parsers in C

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
#line 1 "C:\\Users\\dieppedalle\\Documents\\nomeProject\\nome\\compilerNome\\parser.y" /* yacc.c:1909  */

#include <newNOME/Session.h>


#line 49 "C:\\Users\\dieppedalle\\Documents\\nomeProject\\nome\\compilerNome\\parser.hpp" /* yacc.c:1909  */

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
    SWEEP = 279,
    END_SWEEP = 280,
    END_POLYLINE = 281,
    INSTANCE = 282,
    END_INSTANCE = 283,
    CIRCLE = 284,
    END_CIRCLE = 285,
    BEG_DELETE = 286,
    END_DELETE = 287,
    GROUP = 288,
    END_GROUP = 289,
    TRANSLATE = 290,
    ROTATE = 291,
    MIRROR = 292,
    SET = 293,
    OPARENTHESES = 294,
    EPARENTHESES = 295,
    OBRACE = 296,
    EXPR = 297,
    DOLLAR = 298,
    EBRACE = 299,
    PERIOD = 300,
    TOKHEAT = 301,
    STATE = 302,
    TOKTARGET = 303,
    TOKTEMPERATURE = 304,
    SCALE = 305,
    SUBDIVISION = 306,
    END_SUBDIVISION = 307,
    SUBDIVISIONS = 308,
    TYPE = 309,
    OFFSET = 310,
    END_OFFSET = 311,
    MIN = 312,
    MAX = 313,
    STEP = 314,
    BSPLINE = 315,
    END_BSPLINE = 316,
    CLOSED = 317,
    SLICES = 318,
    BEZIERCURVE = 319,
    END_BEZIERCURVE = 320,
    COS = 321,
    SIN = 322,
    TAN = 323,
    EXPONENT = 324,
    MULTIPLY = 325,
    DIVIDE = 326,
    ADD = 327,
    SUBTRACT = 328,
    SLIDEREXPRESSION = 329,
    REVERSE = 330,
    FOREGROUND = 331,
    END_FOREGROUND = 332,
    BACKGROUND = 333,
    END_BACKGROUND = 334,
    INSIDEFACES = 335,
    END_INSIDEFACES = 336,
    OUTSIDEFACES = 337,
    END_OUTSIDEFACES = 338,
    OFFSETFACES = 339,
    END_OFFSETFACES = 340,
    BANK_EXPR = 341,
    NUMBER = 342
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
#define SWEEP 279
#define END_SWEEP 280
#define END_POLYLINE 281
#define INSTANCE 282
#define END_INSTANCE 283
#define CIRCLE 284
#define END_CIRCLE 285
#define BEG_DELETE 286
#define END_DELETE 287
#define GROUP 288
#define END_GROUP 289
#define TRANSLATE 290
#define ROTATE 291
#define MIRROR 292
#define SET 293
#define OPARENTHESES 294
#define EPARENTHESES 295
#define OBRACE 296
#define EXPR 297
#define DOLLAR 298
#define EBRACE 299
#define PERIOD 300
#define TOKHEAT 301
#define STATE 302
#define TOKTARGET 303
#define TOKTEMPERATURE 304
#define SCALE 305
#define SUBDIVISION 306
#define END_SUBDIVISION 307
#define SUBDIVISIONS 308
#define TYPE 309
#define OFFSET 310
#define END_OFFSET 311
#define MIN 312
#define MAX 313
#define STEP 314
#define BSPLINE 315
#define END_BSPLINE 316
#define CLOSED 317
#define SLICES 318
#define BEZIERCURVE 319
#define END_BEZIERCURVE 320
#define COS 321
#define SIN 322
#define TAN 323
#define EXPONENT 324
#define MULTIPLY 325
#define DIVIDE 326
#define ADD 327
#define SUBTRACT 328
#define SLIDEREXPRESSION 329
#define REVERSE 330
#define FOREGROUND 331
#define END_FOREGROUND 332
#define BACKGROUND 333
#define END_BACKGROUND 334
#define INSIDEFACES 335
#define END_INSIDEFACES 336
#define OUTSIDEFACES 337
#define END_OUTSIDEFACES 338
#define OFFSETFACES 339
#define END_OFFSETFACES 340
#define BANK_EXPR 341
#define NUMBER 342

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 76 "C:\\Users\\dieppedalle\\Documents\\nomeProject\\nome\\compilerNome\\parser.y" /* yacc.c:1909  */

    std::vector<std::string>* strings;
    double intNumber;
    double number;
    const char *string;
    bool boolean;
    struct {
        const char *string; // char *strVal;
        double number;   // int posVal;
    } numPos;

#line 247 "C:\\Users\\dieppedalle\\Documents\\nomeProject\\nome\\compilerNome\\parser.hpp" /* yacc.c:1909  */
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
