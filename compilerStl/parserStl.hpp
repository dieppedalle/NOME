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

#ifndef YY_STL_C_USERS_DIEPPEDALLE_DOCUMENTS_NOMEPROJECT_NOME_COMPILERSTL_PARSERSTL_HPP_INCLUDED
# define YY_STL_C_USERS_DIEPPEDALLE_DOCUMENTS_NOMEPROJECT_NOME_COMPILERSTL_PARSERSTL_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int stldebug;
#endif
/* "%code requires" blocks.  */
#line 1 "C:\\Users\\dieppedalle\\Documents\\nomeProject\\nome\\compilerStl\\parserStl.y" /* yacc.c:1909  */

#include <Lewis/Session.h>

#line 48 "C:\\Users\\dieppedalle\\Documents\\nomeProject\\nome\\compilerStl\\parserStl.hpp" /* yacc.c:1909  */

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    OUTER = 258,
    SOLID = 259,
    FACET = 260,
    ENDFACET = 261,
    LOOP = 262,
    ENDLOOP = 263,
    VERTEX = 264,
    NORMAL = 265,
    ENDSOLID = 266,
    COLOR = 267,
    VARIABLE = 268,
    COMMENT = 269,
    NEWLINE = 270,
    SURFACE = 271,
    END_SURFACE = 272,
    MESH = 273,
    END_MESH = 274,
    FACE = 275,
    END_FACE = 276,
    BEG_POINT = 277,
    END_POINT = 278,
    OBJECT = 279,
    END_OBJECT = 280,
    BANK = 281,
    END_BANK = 282,
    TUNNEL = 283,
    END_TUNNEL = 284,
    FUNNEL = 285,
    END_FUNNEL = 286,
    POLYLINE = 287,
    END_POLYLINE = 288,
    INSTANCE = 289,
    END_INSTANCE = 290,
    CIRCLE = 291,
    END_CIRCLE = 292,
    BEG_DELETE = 293,
    END_DELETE = 294,
    GROUP = 295,
    END_GROUP = 296,
    TRANSLATE = 297,
    ROTATE = 298,
    MIRROR = 299,
    SET = 300,
    OPARENTHESES = 301,
    EPARENTHESES = 302,
    OBRACE = 303,
    EXPR = 304,
    DOLLAR = 305,
    EBRACE = 306,
    PERIOD = 307,
    TOKHEAT = 308,
    STATE = 309,
    TOKTARGET = 310,
    TOKTEMPERATURE = 311,
    SCALE = 312,
    SUBDIVISION = 313,
    END_SUBDIVISION = 314,
    SUBDIVISIONS = 315,
    TYPE = 316,
    OFFSET = 317,
    END_OFFSET = 318,
    MIN = 319,
    MAX = 320,
    STEP = 321,
    BANK_EXPR = 322,
    NUMBER = 323
  };
#endif
/* Tokens.  */
#define OUTER 258
#define SOLID 259
#define FACET 260
#define ENDFACET 261
#define LOOP 262
#define ENDLOOP 263
#define VERTEX 264
#define NORMAL 265
#define ENDSOLID 266
#define COLOR 267
#define VARIABLE 268
#define COMMENT 269
#define NEWLINE 270
#define SURFACE 271
#define END_SURFACE 272
#define MESH 273
#define END_MESH 274
#define FACE 275
#define END_FACE 276
#define BEG_POINT 277
#define END_POINT 278
#define OBJECT 279
#define END_OBJECT 280
#define BANK 281
#define END_BANK 282
#define TUNNEL 283
#define END_TUNNEL 284
#define FUNNEL 285
#define END_FUNNEL 286
#define POLYLINE 287
#define END_POLYLINE 288
#define INSTANCE 289
#define END_INSTANCE 290
#define CIRCLE 291
#define END_CIRCLE 292
#define BEG_DELETE 293
#define END_DELETE 294
#define GROUP 295
#define END_GROUP 296
#define TRANSLATE 297
#define ROTATE 298
#define MIRROR 299
#define SET 300
#define OPARENTHESES 301
#define EPARENTHESES 302
#define OBRACE 303
#define EXPR 304
#define DOLLAR 305
#define EBRACE 306
#define PERIOD 307
#define TOKHEAT 308
#define STATE 309
#define TOKTARGET 310
#define TOKTEMPERATURE 311
#define SCALE 312
#define SUBDIVISION 313
#define END_SUBDIVISION 314
#define SUBDIVISIONS 315
#define TYPE 316
#define OFFSET 317
#define END_OFFSET 318
#define MIN 319
#define MAX 320
#define STEP 321
#define BANK_EXPR 322
#define NUMBER 323

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 95 "C:\\Users\\dieppedalle\\Documents\\nomeProject\\nome\\compilerStl\\parserStl.y" /* yacc.c:1909  */

    double number;
    char *string;
    struct {
        char *string; // char *strVal;
        double number;   // int posVal;
    } numPos;

#line 205 "C:\\Users\\dieppedalle\\Documents\\nomeProject\\nome\\compilerStl\\parserStl.hpp" /* yacc.c:1909  */
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


extern YYSTYPE stllval;
extern YYLTYPE stllloc;
int stlparse (Session* currSession);

#endif /* !YY_STL_C_USERS_DIEPPEDALLE_DOCUMENTS_NOMEPROJECT_NOME_COMPILERSTL_PARSERSTL_HPP_INCLUDED  */
