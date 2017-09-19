%{
#include <stdio.h>
#include <string.h>


extern int yylineno;
extern char* yytext;
extern FILE *yyin;
int yylex(void);
int yyerror(char *s) {
  printf("%s on line %d - %s\n", s, yylineno, yytext);
}
extern "C" int yyparse (void);

int yywrap() {
    return 1;
}

/*main() {

    yyin = fopen("test.txt", "r");

    yyparse();
    //fclose(fd);
}*/

%}
%token COLOR VARIABLE MULTI_LINE_COMMENT COMMENT NEWLINE OMULTI_LINE_COMMENT
EMULTI_LINE_COMMENT SURFACE END_SURFACE MESH END_MESH FACE END_FACE BEG_POINT
END_POINT OBJECT END_OBJECT BANK END_BANK TUNNEL END_TUNNEL FUNNEL END_FUNNEL
POLYLINE END_POLYLINE INSTANCE END_INSTANCE CIRCLE END_CIRCLE BEG_DELETE END_DELETE
GROUP  END_GROUP TRANSLATE ROTATE MIRROR SET OPARENTHESES EPARENTHESES OBRACE
EXPR DOLLAR EBRACE NUMBER PERIOD TOKHEAT STATE TOKTARGET TOKTEMPERATURE BANK_EXPR
SCALE


%%

commands: /* empty */
	| commands command
	;


command:
	comment | multi_line_comment | mesh | surface | point | face | object | bank |
  tunnel | funnel | polyline | instance | delete | group | circle
	;

number:
    NUMBER | expr
    {
        printf("Seeing a number!\n");
    }
    ;

comment:
    COMMENT
    {
        printf("Comment!\n");
    }
    ;


variables:
  |
	variables VARIABLE
	;

surfaceArgs:
	| SURFACE VARIABLE
	;

transformArgs:
    | transformArgs rotateArgs |  transformArgs translateArgs | transformArgs scaleArgs | transformArgs mirrorArgs
    ;

rotateArgs:
    ROTATE OPARENTHESES number number number EPARENTHESES OPARENTHESES number EPARENTHESES
    {
      printf("Rotated\n");
  }
  ;

translateArgs:
    TRANSLATE OPARENTHESES number number number EPARENTHESES
    {
      printf("Translated\n");
  }
  ;

scaleArgs:
    SCALE OPARENTHESES number number number EPARENTHESES
    {
      printf("Scaled\n");
  }
  ;

mirrorArgs:
    MIRROR OPARENTHESES number number number number EPARENTHESES
    {
      printf("Mirrored\n");
  }
  ;

faceArgs:
	| faceArgs face
	;

instanceArgs:
	| instanceArgs instance
	;

faceDeleteArgs:
	| faceDeleteArgs faceDelete
	;

mesh:
	MESH VARIABLE faceArgs END_MESH
    {
		printf("Created a mesh\n");
	}
	;

group:
	GROUP VARIABLE instanceArgs END_GROUP
    {
		printf("Created a group\n");
	}
	;

expr:
    OBRACE EXPR BANK_EXPR EBRACE
    {
        printf("Expression\n");
    };

delete:
    BEG_DELETE faceDeleteArgs END_DELETE
    {
		printf("Deleting faces\n");
	}
	;

set:
    SET VARIABLE number number number number
	{
		printf("Created a Set\n");
	}
	;

setArgs:
    | setArgs set |  setArgs comment
	;


bank:
	BANK VARIABLE setArgs END_BANK
  {
		printf("Created a bank\n");
	}
	;

circle:
    CIRCLE VARIABLE OPARENTHESES number number EPARENTHESES END_CIRCLE
    {
        printf("Created a circle\n");
    };

tunnel:
    TUNNEL VARIABLE OPARENTHESES number number number number EPARENTHESES
  END_TUNNEL
	{
		printf("Created a tunnel\n");
	}
	;

funnel:
    FUNNEL VARIABLE OPARENTHESES number number number number EPARENTHESES
  END_FUNNEL
	{
		printf("Created a funnel\n");
	}
	;

parenthesisName:
	OPARENTHESES variables EPARENTHESES
	{
		printf("Created a surface\n");
	}
	;

face:
	FACE VARIABLE parenthesisName surfaceArgs END_FACE
	{
		printf("Created a face\n");
	}
	;

faceDelete:
	FACE VARIABLE END_FACE
	{
		printf("Deleting face\n");
	}
	;

polyline:
	POLYLINE VARIABLE parenthesisName END_POLYLINE
	{
		printf("Created a polyline\n");
	}
	;

instance:
    INSTANCE VARIABLE VARIABLE surfaceArgs transformArgs
  END_INSTANCE
	{
		printf("Created an instance\n");
	}
	;

object:
	OBJECT VARIABLE parenthesisName END_OBJECT
	{
		printf("Created an object\n");
	}
	;

surface:
    SURFACE VARIABLE COLOR OPARENTHESES number number number EPARENTHESES
  END_SURFACE
    {
        //printf("%s\n", $2);
		printf("Created a surface\n");
	}
	;

multi_line_comment:
	MULTI_LINE_COMMENT
	{
		printf("Created a multiline comment.\n");
	}
	;

point:
    BEG_POINT VARIABLE OPARENTHESES number number number EPARENTHESES END_POINT
	{
		printf("Created a point.\n");
	}
	;

