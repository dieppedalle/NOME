
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
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
     COLOR = 258,
     VARIABLE = 259,
     MULTI_LINE_COMMENT = 260,
     COMMENT = 261,
     NEWLINE = 262,
     OMULTI_LINE_COMMENT = 263,
     EMULTI_LINE_COMMENT = 264,
     SURFACE = 265,
     END_SURFACE = 266,
     MESH = 267,
     END_MESH = 268,
     FACE = 269,
     END_FACE = 270,
     BEG_POINT = 271,
     END_POINT = 272,
     OBJECT = 273,
     END_OBJECT = 274,
     BANK = 275,
     END_BANK = 276,
     TUNNEL = 277,
     END_TUNNEL = 278,
     FUNNEL = 279,
     END_FUNNEL = 280,
     POLYLINE = 281,
     END_POLYLINE = 282,
     INSTANCE = 283,
     END_INSTANCE = 284,
     CIRCLE = 285,
     END_CIRCLE = 286,
     BEG_DELETE = 287,
     END_DELETE = 288,
     GROUP = 289,
     END_GROUP = 290,
     TRANSLATE = 291,
     ROTATE = 292,
     MIRROR = 293,
     SET = 294,
     OPARENTHESES = 295,
     EPARENTHESES = 296,
     OBRACE = 297,
     EXPR = 298,
     DOLLAR = 299,
     EBRACE = 300,
     NUMBER = 301,
     PERIOD = 302,
     TOKHEAT = 303,
     STATE = 304,
     TOKTARGET = 305,
     TOKTEMPERATURE = 306,
     BANK_EXPR = 307,
     SCALE = 308
   };
#endif
/* Tokens.  */
#define COLOR 258
#define VARIABLE 259
#define MULTI_LINE_COMMENT 260
#define COMMENT 261
#define NEWLINE 262
#define OMULTI_LINE_COMMENT 263
#define EMULTI_LINE_COMMENT 264
#define SURFACE 265
#define END_SURFACE 266
#define MESH 267
#define END_MESH 268
#define FACE 269
#define END_FACE 270
#define BEG_POINT 271
#define END_POINT 272
#define OBJECT 273
#define END_OBJECT 274
#define BANK 275
#define END_BANK 276
#define TUNNEL 277
#define END_TUNNEL 278
#define FUNNEL 279
#define END_FUNNEL 280
#define POLYLINE 281
#define END_POLYLINE 282
#define INSTANCE 283
#define END_INSTANCE 284
#define CIRCLE 285
#define END_CIRCLE 286
#define BEG_DELETE 287
#define END_DELETE 288
#define GROUP 289
#define END_GROUP 290
#define TRANSLATE 291
#define ROTATE 292
#define MIRROR 293
#define SET 294
#define OPARENTHESES 295
#define EPARENTHESES 296
#define OBRACE 297
#define EXPR 298
#define DOLLAR 299
#define EBRACE 300
#define NUMBER 301
#define PERIOD 302
#define TOKHEAT 303
#define STATE 304
#define TOKTARGET 305
#define TOKTEMPERATURE 306
#define BANK_EXPR 307
#define SCALE 308




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 1676 of yacc.c  */
#line 78 "C:\\Users\\dieppedalle\\Documents\\nomeProject\\nome\\parser.y"

    double number;
    char *string;
    struct {
        char *strVal;
        int posVal;
    } numPos;



/* Line 1676 of yacc.c  */
#line 169 "C:\\Users\\dieppedalle\\Documents\\nomeProject\\nome\\parser.hpp"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;

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

extern YYLTYPE yylloc;

