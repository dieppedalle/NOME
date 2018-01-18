%{
#include <stdio.h>
#include <string.h>
#include <string>
#include "parserBank.hpp"

int bankcolumn = 0;
#define bank_USER_ACTION banklloc.first_line = banklloc.last_line = banklineno; \
    banklloc.first_column = bankcolumn; banklloc.last_column = bankcolumn + bankleng - 1; \
    bankcolumn += bankleng;

%}

%option prefix="bank"
%option noyywrap

%option yylineno
%x MULTI_COMMENT

%%
sqrt                     return SQRT;
cos                      return COS;
sin                      return SIN;
tan                      return TAN;
sec                      return SEC;
cot                      return COT;
csc                      return CSC;
arccos                   return ARCCOS;
arcsin                   return ARCSIN;
arctan                   return ARCTAN;
arcsec                   return ARCSEC;
arccot                   return ARCCOT;
arccsc                   return ARCCSC;
log                      return LOG;
e                        return E;
ln                       return LN;
\+                       return ADD;
\-                       return SUBTRACT;
\*                       return MULTIPLY;
\/                       return DIVIDE;
\^                       return EXP;
\(                       return LPAREN;
\)                       return RPAREN;
\$[a-zA-Z][a-zA-Z0-9]*.[a-zA-Z][a-zA-Z0-9]*  banklval.string=strdup(banktext); return BANK_EXPR;
[0-9\.]+                 banklval.number=(double)atof(banktext); return NUM;
[ \t\n]+                /* ignore whitespace */;
%%

void set_input_string(const char* in) {
  bank_scan_string(in);
}

void end_lexical_scan(void) {
  bank_delete_buffer(YY_CURRENT_BUFFER);
}
