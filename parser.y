%{
#include <stdio.h>
#include <string.h>
#include <list>

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

map<string,QColor> surfaces;
map<string,Vertex*> vertices;
std::vector<string> tempVariables;
string currentSetName;
std::vector<double> currentSetList;
map<string,std::vector<double>> currentBank;
std::vector<string> currentInstanceList;
std::vector<std::vector<string>> currentGroup;

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

%union
{
    double number;
    char *string;
}

%token <string> BANK_EXPR
%token <number> NUMBER


%%

commands: /* empty */
	| commands command
	;


command:
	comment | multi_line_comment | mesh | surface | point | face | object | bank |
  tunnel | funnel | polyline | instance | delete | group | circle
	;

numberValue:
    num {
        $<number>$ = $<number>1;
    } | expr
    {
        $<string>$ = $<string>1;
    }
    ;


num:
    NUMBER
    {
        $<number>$ = $1;
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
    variables VARIABLE {
        tempVariables.push_back($<string>2);
    }
	;

surfaceArgs:
    {$<string>$ = "";}
    | SURFACE VARIABLE {
        $<string>$ = $<string>2;
    }
	;

transformArgs:
    | transformArgs rotateArgs |  transformArgs translateArgs | transformArgs scaleArgs | transformArgs mirrorArgs
    ;

rotateArgs:
    ROTATE OPARENTHESES numberValue numberValue numberValue EPARENTHESES OPARENTHESES numberValue EPARENTHESES
    {
        double x = $<number>3;
        double y = $<number>4;
        double z = $<number>5;

        double angle = $<number>8;

        printf("Rotated\n");
    }
    ;

translateArgs:
    TRANSLATE OPARENTHESES numberValue numberValue numberValue EPARENTHESES
    {
        double x = $<number>3;
        double y = $<number>4;
        double z = $<number>5;
        printf("Translated\n");
    }
    ;

scaleArgs:
    SCALE OPARENTHESES numberValue numberValue numberValue EPARENTHESES
    {
        double x = $<number>3;
        double y = $<number>4;
        double z = $<number>5;
        printf("Scaled\n");
    }
    ;

mirrorArgs:
    MIRROR OPARENTHESES numberValue numberValue numberValue numberValue EPARENTHESES
    {
        double x = $<number>3;
        double y = $<number>4;
        double z = $<number>5;
        double w = $<number>5;

        printf("Mirrored\n");
    }
    ;

faceArgs:
	| faceArgs face
	;

instanceArgs:
    | instanceArgs instanceGroup
	;

instanceGroup:
    INSTANCE VARIABLE VARIABLE surfaceArgs transformArgs END_INSTANCE
    {
        currentInstanceList.clear();
        currentInstanceList.push_back($<string>2);
        currentInstanceList.push_back($<string>3);
        currentGroup.push_back(currentInstanceList);
    }
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
        cout << "Length of the group" << endl;
        cout << currentGroup.size() << endl;
        currentGroup.clear();
		printf("Created a group\n");
	}
	;

expr:
    OBRACE EXPR BANK_EXPR EBRACE
    {
        $<string>$ = $3;
        printf("Expression\n");
    };

delete:
    BEG_DELETE faceDeleteArgs END_DELETE
    {
		printf("Deleting faces\n");
	}
	;

set:
    SET VARIABLE numberValue numberValue numberValue numberValue
    {
        currentSetName = $<string>2;
        currentSetList.clear();
        currentSetList.push_back($<number>3);
        currentSetList.push_back($<number>4);
        currentSetList.push_back($<number>5);
		printf("Created a Set\n");
	}
	;

setArgs:
    | setArgs set |  setArgs comment {
        currentBank.insert({currentSetName, currentSetList});
    }
	;


bank:
	BANK VARIABLE setArgs END_BANK
    {
        //currentBank contains element in bank
        currentBank.clear();
		printf("Created a bank\n");
	}
	;

circle:
    CIRCLE VARIABLE OPARENTHESES numberValue numberValue EPARENTHESES END_CIRCLE
    {
        string name = $<string>2;
        double num = $<number>4;
        double rad = $<number>5;

        printf("Created a circle\n");
    };

tunnel:
    TUNNEL VARIABLE OPARENTHESES numberValue numberValue numberValue numberValue EPARENTHESES
  END_TUNNEL
	{
        string name = $<string>2;
        double n = $<number>4;
        double ro = $<number>5;
        double ratio = $<number>6;
        double h = $<number>7;

		printf("Created a tunnel\n");
	}
	;

funnel:
    FUNNEL VARIABLE OPARENTHESES numberValue numberValue numberValue numberValue EPARENTHESES
  END_FUNNEL
	{
        string name = $<string>2;
        double n = $<number>4;
        double ro = $<number>5;
        double ratio = $<number>6;
        double h = $<number>7;


		printf("Created a funnel\n");
	}
	;

parenthesisName:
	OPARENTHESES variables EPARENTHESES
    {
        printf("Created a parenthesis\n");
	}
	;

face:
	FACE VARIABLE parenthesisName surfaceArgs END_FACE
    {
        // verticesFace $<string>1

        // Create list of vertices of face.
        std::vector<Vertex*> verticesFace;
        for (std::vector<string>::iterator it = tempVariables.begin() ; it != tempVariables.end(); ++it){
            std::map<string,Vertex*>::iterator st = vertices.find(*it);

            if (st != vertices.end()){
                verticesFace.push_back(st->second);
            }
            else{
                yyerror("Incorrect vertex name");
                YYABORT;
            }
        }

        // Check if a surface has been applied.
        if ($<string>4 != NULL){
            std::map<string,QColor>::iterator qt = surfaces.find($<string>4);
            QColor surfaceApplied;

            if (qt != surfaces.end()){
                 surfaceApplied = qt->second;
            }
            else{
                yyerror("Incorrect surface name");
                YYABORT;
            }
        }
        else{
            // Create without surface

        }

        tempVariables.clear();

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
        // Create list of vertices of face.
        std::vector<Vertex*> verticesPolyline;
        for (std::vector<string>::iterator it = tempVariables.begin() ; it != tempVariables.end(); ++it){
            std::map<string,Vertex*>::iterator st = vertices.find(*it);

            if (st != vertices.end()){
                verticesPolyline.push_back(st->second);
            }
            else{
                yyerror("Incorrect vertex name");
                YYABORT;
            }
        }

        tempVariables.clear();

		printf("Created a polyline\n");
	}
	;

instance:
    INSTANCE VARIABLE VARIABLE surfaceArgs transformArgs END_INSTANCE
	{
        string instanceName = $<string>2;
        string lookFor = $<string>3;

        // Check if a surface has been applied.
        if (strlen($<string>4) != 0){
            std::map<string,QColor>::iterator qt = surfaces.find($<string>4);
            QColor surfaceApplied;

            if (qt != surfaces.end()){
                 surfaceApplied = qt->second;
            }
            else{
                yyerror("Incorrect surface name");
                YYABORT;
            }
        }

		printf("Created an instance\n");
	}
	;

object:
	OBJECT VARIABLE parenthesisName END_OBJECT
	{
        std::vector<Vertex*> verticesFace;
        for (std::vector<string>::iterator it = tempVariables.begin() ; it != tempVariables.end(); ++it){
            std::map<string,Vertex*>::iterator st = vertices.find(*it);

            verticesFace.push_back(st->second);
        }

        tempVariables.clear();
		printf("Created an object\n");
	}
	;

surface:
    SURFACE VARIABLE COLOR OPARENTHESES numberValue numberValue numberValue EPARENTHESES END_SURFACE
    {
        string name = strdup($<string>2);

        if ($<number>5 < 0 || $<number>5 > 1 || $<number>6 < 0 || $<number>6 > 1 || $<number>7 < 0 || $<number>7 > 1) {
            yyerror("RGB values of surface out of bounds.");
            YYABORT;
        }
        surfaces[name] = QColor(255 * $<number>5, 255 * $<number>6, 255 * $<number>7);
	}
	;

multi_line_comment:
	MULTI_LINE_COMMENT
	{
		printf("Created a multiline comment.\n");
	}
	;

point:
    BEG_POINT VARIABLE OPARENTHESES numberValue numberValue numberValue EPARENTHESES END_POINT
	{
        string name = strdup($<string>2);
        vertices[name] = new Vertex($<number>4, $<number>5, $<number>6, $<string>2, 0);
		printf("Created a point.\n");
	}
	;

