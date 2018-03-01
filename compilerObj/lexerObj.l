%{
#include <stdio.h>
#include <string.h>
#include <string>
#include "parserObj.hpp"

#define objterminate() return token::END

int objcolumn = 0;
#define obj_USER_ACTION objlloc.first_line = objlloc.last_line = objlineno; \
    objlloc.first_column = objcolumn; objlloc.last_column = objcolumn + objleng - 1; \
    objcolumn += objleng;

static int isatty(int) {return 0;}
%}

%option prefix="obj"
%option noyywrap

%option nounistd
%option yylineno
%x MULTI_COMMENT

%%
(\#(.)*(.|\n))           return COMMENT;
[+-]?([0-9]*[.])?[e+\-0-9]+  objlval.string=strdup(objtext); return NUMBER;
v                     return V;
vt                    return VT;
vn                    return VN;
vp                    return VP;
f                     return F;
l                     return L;
o                     return O;
g                     return G;
s                     return S;
mtllib                return MTLLIB;
usemtl                return USEMTL;
[a-zA-Z\.\/][\/a-zA-Z0-9_\.\-]*    objlval.string=strdup(objtext); return VARIABLE;
[ \t\n]+                /* ignore whitespace */;
%%
