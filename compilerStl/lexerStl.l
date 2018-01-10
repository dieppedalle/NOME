%{
#include <stdio.h>
#include <string.h>
#include <string>
#include "parserStl.hpp"

int stlcolumn = 0;
#define stl_USER_ACTION stllloc.first_line = stllloc.last_line = stllineno; \
    stllloc.first_column = stlcolumn; stllloc.last_column = stlcolumn + stlleng - 1; \
    stlcolumn += stlleng;

%}

%option prefix="stl"
%option noyywrap

%option yylineno
%x MULTI_COMMENT

%%
[+-]?([0-9]*[.])?[e+\-0-9]+  stllval.string=strdup(stltext); return NUMBER;
\$[a-zA-Z][a-zA-Z0-9]*.[a-zA-Z][a-zA-Z0-9]*  stllval.string=strdup(stltext); return BANK_EXPR;
solid                    return SOLID;
outer                    return OUTER;
facet                    return FACET;
endfacet                 return ENDFACET;
loop                     return LOOP;
endloop                  return ENDLOOP;
vertex                   return VERTEX;
normal                   return NORMAL;
endsolid                 return ENDSOLID;
[a-zA-Z][a-zA-Z0-9_\.\-]*    stllval.string=strdup(stltext); return VARIABLE;
[ \t\n]+                /* ignore whitespace */;
%%
