%{
#include <stdio.h>
#include <string.h>
#include <string>
//#include "y.tab.h"
#include "parser.hpp"

int yycolumn = 0;
#define YY_USER_ACTION yylloc.first_line = yylloc.last_line = yylineno; \
    yylloc.first_column = yycolumn; yylloc.last_column = yycolumn + yyleng - 1; \
    yycolumn += yyleng;

%}
%option yylineno

%%
(\#(.)*(.|\n))           return COMMENT;
\(\*(.|\n)*\*\)          return MULTI_LINE_COMMENT;
[+-]?([0-9]*[.])?[0-9]+  yylval.string=yytext; return NUMBER;
\$[a-zA-Z][a-zA-Z0-9]*.[a-zA-Z][a-zA-Z0-9]*  yylval.string=strdup(yytext); return BANK_EXPR;
expr                     return EXPR;
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
\{                      return OBRACE;
\}                      return EBRACE;
[a-zA-Z][a-zA-Z0-9\.]*    yylval.string=strdup(yytext); return VARIABLE;
\(                      return OPARENTHESES;
\)                      return EPARENTHESES;
[ \t]+                  /* ignore whitespace */;
%%
