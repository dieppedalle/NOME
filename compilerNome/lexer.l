
%{
#include <stdio.h>
#include <string.h>
#include <string>
#include "parser.hpp"

int nomcolumn = 0;
#define nom_USER_ACTION nomlloc.first_line = nomlloc.last_line = nomlineno; \
    nomlloc.first_column = nomcolumn; nomlloc.last_column = nomcolumn + nomleng - 1; \
    nomcolumn += nomleng;

%}

%option prefix="nom"
%option noyywrap

%option yylineno
%x MULTI_COMMENT

%%
(\#(.)*(.|\n))           return COMMENT;
"(*"                     { BEGIN(MULTI_COMMENT); }
<MULTI_COMMENT>"*)"      { BEGIN(INITIAL); }
<MULTI_COMMENT>.         {}
[+-]?([0-9]*[.])?[0-9]+  nomlval.string=nomtext; return NUMBER;
\$[a-zA-Z][a-zA-Z0-9]*.[a-zA-Z][a-zA-Z0-9]*  nomlval.string=strdup(nomtext); return BANK_EXPR;
expr                     return EXPR;
bspline[0-9]+            nomlval.intNumber = std::stoi(std::string(nomtext).substr (7)); return BSPLINE;
endbspline[0-9]+         nomlval.intNumber = std::stoi(std::string(nomtext).substr (10)); return END_BSPLINE;
closed                   return CLOSED;
slices                   return SLICES;
offset                   return OFFSET;
endoffset                return END_OFFSET;
min                      return MIN;
max                      return MAX;
step                     return STEP;
surface                  return SURFACE;
endsurface               return END_SURFACE;
point                    return BEG_POINT;
color                    return COLOR;
endpoint                 return END_POINT;
bank                     return BANK;
endbank                  return END_BANK;
set                      return SET;
face                     return FACE;
endface                  return END_FACE;
object                   return OBJECT;
endobject                return END_OBJECT;
mesh                    return MESH;
endmesh                 return END_MESH;
tunnel                  return TUNNEL;
endtunnel               return END_TUNNEL;
funnel                  return FUNNEL;
endfunnel               return END_FUNNEL;
polyline                return POLYLINE;
circle                  return CIRCLE;
endcircle               return END_CIRCLE;
scale                   return SCALE;
endpolyline             return END_POLYLINE;
instance                return INSTANCE;
endinstance             return END_INSTANCE;
translate               return TRANSLATE;
rotate                  return ROTATE;
mirror                  return MIRROR;
delete                  return BEG_DELETE;
enddelete               return END_DELETE;
group                   return GROUP;
endgroup                return END_GROUP;
subdivision             return SUBDIVISION;
endsubdivision          return END_SUBDIVISION;
subdivisions            return SUBDIVISIONS;
type                    return TYPE;
\{                      return OBRACE;
\}                      return EBRACE;
[a-zA-Z][a-zA-Z0-9_\.]*    nomlval.string=strdup(nomtext); return VARIABLE;
\(                      return OPARENTHESES;
\)                      return EPARENTHESES;
[ \t\n]+                /* ignore whitespace */;
%%
