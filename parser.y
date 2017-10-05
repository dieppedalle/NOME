%{
#include <stdio.h>
#include <string.h>
#include <list>
#include <Lewis/Data.h>
#include <Lewis/MeshNew.h>
#include <Lewis/Session.h>
#include <Lewis/Reader.h>

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

Session* currSession = createSession();
Reader* currReader = createReader(currSession);

map<string,QColor> surfaces;
map<string,Vertex*> vertices;
std::vector<string> tempVariables;
string currentSetName;
std::vector<double> currentSetList;
map<string,std::vector<double>> currentBank;
std::vector<string> currentInstanceList;
std::vector<std::vector<string>> currentGroup;
std::list<FaceNew *> currentMeshFaces;
std::list<Vert *> currentMeshVertices;
std::list<EdgeNew *> currentMeshEdges;

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
    | faceArgs faceMesh
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
        MeshNew* currMesh = createMesh();

        currMesh->setName(strdup($<string>2));
        currMesh->faces.splice((currMesh->faces.end()), currentMeshFaces);
        currMesh->verts.splice(currMesh->verts.end(), currentMeshVertices);
        currMesh->edges.splice(currMesh->edges.end(), currentMeshEdges);

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

faceMesh:
    FACE VARIABLE parenthesisName surfaceArgs END_FACE
    {
        std::list<Vert*> verticesFace;


        for (std::vector<string>::iterator it = tempVariables.begin() ; it != tempVariables.end(); ++it){
            Vert * currentVertex = currReader->vert(*it);
            if (currentVertex != NULL) {
                verticesFace.push_back(currentVertex);
                currentMeshVertices.push_back(currentVertex);
            }
            else{
                yyerror("Incorrect vertex name");
                YYABORT;
            }
        }

        FaceNew * newFace = createFace(verticesFace, &currentMeshEdges);

        newFace->setName(strdup($<string>2));

        string surfaceName = $<string>4;
        // Check if a surface has been applied.
        if (surfaceName.length() != 0){
            Surface * currentSurface = currReader->surf($<string>4);
            if (currentSurface != NULL) {
                setSurface(newFace, currentSurface);
            }
            else{
                yyerror("Incorrect surface name");
                YYABORT;
            }
        }

        //https://stackoverflow.com/questions/1449703/how-to-append-a-listt-object-to-another
        currentMeshFaces.push_back(newFace);
        //currSession->faces.push_back(newFace);
        //currSession->faces.push_back(currentMeshEdges);

        tempVariables.clear();

        printf("Created a face\n");
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
	}
	;

face:
	FACE VARIABLE parenthesisName surfaceArgs END_FACE
    {
        std::list<Vert*> verticesFace;
        for (std::vector<string>::iterator it = tempVariables.begin() ; it != tempVariables.end(); ++it){
            Vert * currentVertex = currReader->vert(*it);
            if (currentVertex != NULL) {
                verticesFace.push_back(currentVertex);
            }
            else{
                yyerror("Incorrect vertex name");
                YYABORT;
            }
        }

        FaceNew * newFace = createFace(verticesFace, &(currSession->edges));

        setName(newFace, strdup($<string>2));

        string surfaceName = $<string>4;
        // Check if a surface has been applied.
        if (surfaceName.length() != 0){
            Surface * currentSurface = currReader->surf($<string>4);
            if (currentSurface != NULL) {
                setSurface(newFace, currentSurface);
            }
            else{
                yyerror("Incorrect surface name");
                YYABORT;
            }
        }

        currSession->faces.push_back(newFace);

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
       std::vector<FaceNew*> facesObject;
       for (std::vector<string>::iterator it = tempVariables.begin() ; it != tempVariables.end(); ++it){
           FaceNew * currentFace = currReader->face(*it);
           if (currentFace != NULL) {
               facesObject.push_back(currentFace);
           }
           else{
               yyerror("Incorrect face name");
               YYABORT;
           }
       }

        tempVariables.clear();

        //TODO: Create object

		printf("Created an object\n");
	}
	;

surface:
    SURFACE VARIABLE COLOR OPARENTHESES numberValue numberValue numberValue EPARENTHESES END_SURFACE
    {
        currSession->surfaces.push_back(createSurface($<number>5, $<number>6, $<number>7, strdup($<string>2)));
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
        Vert * newVertex = createVert ($<number>4, $<number>5, $<number>6);
        newVertex->setName(strdup($<string>2));
        currSession->verts.push_back(newVertex);
	}
	;

