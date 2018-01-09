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
(\#(.)*(.|\n))           return COMMENT;
"(*"                     { BEGIN(MULTI_COMMENT); }
<MULTI_COMMENT>"*)"      { BEGIN(INITIAL); }
<MULTI_COMMENT>.         {}
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
expr                     return EXPR;
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
[a-zA-Z][a-zA-Z0-9_\.\-]*    stllval.string=strdup(stltext); return VARIABLE;
\(                      return OPARENTHESES;
\)                      return EPARENTHESES;
[ \t\n]+                /* ignore whitespace */;
%%
