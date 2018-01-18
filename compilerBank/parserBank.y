%code requires{
#include <Lewis/Session.h>
}

%{
#include <stdio.h>
#include <string.h>
#include <list>
#include <Lewis/Data.h>
#include <Lewis/MeshNew.h>
#include <Lewis/Session.h>
#include <Lewis/Reader.h>
#include <Lewis/TransformationNew.h>
#include <Lewis/PolylineNew.h>
#include <Lewis/CircleNew.h>
#include <Lewis/FunnelNew.h>
#include <Lewis/TunnelNew.h>
#include <Lewis/InstanceNew.h>

extern int banklineno;
extern char* banktext;

extern int bankcolumn;

int result = 0;

int banklex(void);
int bankerror(Session* currSession, const char *s) {
  printf("%s on line %d - %s\n", s, banklineno, banktext);
}

int bankwrap() {
    return 1;
}

%}

%parse-param { Session* currSession }

%token COS SIN TAN SEC CSC COT E LN LOG SQRT LPAREN RPAREN EXP MULTIPLY DIVIDE
ADD SUBTRACT NUM ARCCOS ARCCOT ARCCSC ARCSEC ARCSIN ARCTAN BANK_EXPR
;

%error-verbose
%locations

%union
{
    double number;
    char *string;
}

%%

commands: /* empty */
    | commands command
    ;


command:
    calc {
    result = $<number>1;
    };

calc:
    calc ADD priority
    {$<number>$ = $<number>1 + $<number>3;}
    | calc SUBTRACT priority
    {$<number>$ = $<number>1 - $<number>3;}
    | priority
    {$<number>$ = $<number>1;};

priority:
    priority MULTIPLY exp {$<number>$ = $<number>1 * $<number>3;}
    | priority DIVIDE exp {$<number>$ = $<number>1 / $<number>3;}
    | exp {$<number>$ = $<number>1;};

exp:
    exp EXP function {$<number>$ = pow($<number>1, $<number>3);}
    | function { $<number>$ = $<number>1; };

function:
    SQRT parenth {$<number>$ = sqrt($<number>2);}
    | COS parenth {$<number>$ = cos($<number>2);}
    | SIN parenth {$<number>$ = sin($<number>2);}
    | TAN parenth {$<number>$ = tan($<number>2);}
    | SEC parenth {$<number>$ = 1/(cos($<number>2));}
    | CSC parenth {$<number>$ = 1/(sin($<number>2));}
    | COT parenth {$<number>$ = tan($<number>2);}
    | ARCCOS parenth {$<number>$ = acos($<number>2);}
    | ARCSIN parenth {$<number>$ = asin($<number>2);}
    | ARCTAN parenth {$<number>$ = atan($<number>2);}
    | ARCSEC parenth {$<number>$ = 1/(acos($<number>2));}
    | ARCCSC parenth {$<number>$ = 1/(asin($<number>2));}
    | ARCCOT parenth {$<number>$ = 1/(atan($<number>2));}
    | LOG parenth {$<number>$ = log10($<number>2);}
    | LN parenth {$<number>$ = log($<number>2);}
    | SUBTRACT parenth {$<number>$ = -1 * $<number>2;}
    | function parenth {$<number>$ = $<number>1 *$<number>2;}
    | parenth {$<number>$ = $<number>1;};

parenth:
    LPAREN calc RPAREN {$<number>$ = $<number>2;}
    | number {$<number>$ = $<number>1;};

number:
    E { $<number>$ = M_E;}
    | NUM {$<number>$ = $<number>1;};
    | BANK_EXPR {$<number>$ = *getBankValue($<string>1, currSession);}

%%
/* Declarations */
void set_input_string(const char* in);
void end_lexical_scan(void);


/* This function parses a string */
double parse_string(const char* in, Session* sessionParse) {
  set_input_string(in);
  int rv = bankparse(sessionParse);
  end_lexical_scan();

  return result;
}
