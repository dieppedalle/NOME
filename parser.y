%{
#include <stdio.h>
#include <string.h>
#include <list>
#include <Lewis/Data.h>
#include <Lewis/MeshNew.h>
#include <Lewis/Session.h>
#include <Lewis/Reader.h>
#include <Lewis/TransformationNew.h>

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
std::list<SetNew *> currentSetList;
map<string,std::vector<double>> currentBank;
std::vector<string> currentInstanceList;
std::list<InstanceNew *> currentGroup;
std::list<FaceNew *> currentMeshFaces;
std::list<Vert *> currentMeshVertices;
std::list<EdgeNew *> currentMeshEdges;

std::list<TransformationNew *> currentTransformations;

double *getBankValue(std::string str){
    unsigned first = str.find("$") + 1;
    unsigned last = str.find(".");
    string strNew = str.substr (first,last-first);

    for(auto b : currSession->banks) {
        if (b->name == strNew){
            for(auto s : b->sets) {
                if (s->name == str.substr(last + 1)){
                    return &s->value;
                }
            }
        }
    }
    return NULL;
}

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
        //printf("Comment!\n");
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

        currentTransformations.push_back(createRotate(x, y, z, angle));

        //printf("Rotated\n");
    }
    ;

translateArgs:
    TRANSLATE OPARENTHESES numberValue numberValue numberValue EPARENTHESES
    {
        double x = $<number>3;
        double y = $<number>4;
        double z = $<number>5;

        currentTransformations.push_back(createTranslate(x, y, z));
        //printf("Translated\n");
    }
    ;

scaleArgs:
    SCALE OPARENTHESES numberValue numberValue numberValue EPARENTHESES
    {
        double x = $<number>3;
        double y = $<number>4;
        double z = $<number>5;
        currentTransformations.push_back(createScale(x, y, z));
        //printf("Scaled\n");
    }
    ;

mirrorArgs:
    MIRROR OPARENTHESES numberValue numberValue numberValue numberValue EPARENTHESES
    {
        double x = $<number>3;
        double y = $<number>4;
        double z = $<number>5;
        double w = $<number>5;

        //currentTransformations.push_back(createMirror(x, y, z, w));

        //printf("Mirrored\n");
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
        string instanceName = strdup($<string>2);
        string lookFor = strdup($<string>3);

        MeshNew * currentMesh = currReader->mesh($<string>3);
        InstanceNew* newInstance;
        if (currentMesh != NULL) {
            newInstance = createInstance(currentMesh);
            newInstance->setName(strdup($<string>2));
        }
        else{
            yyerror("Incorrect vertex, face, or mesh name");
            YYABORT;
        }

        newInstance->transformations = currentTransformations;
        currentTransformations.clear();

        string surfaceName = $<string>4;
        // Check if a surface has been applied.
        if (surfaceName.length() != 0){
            Surface * currentSurface = currReader->surf($<string>4);
            if (currentSurface != NULL) {
                setSurface(newInstance, currentSurface);
            }
            else{
                yyerror("Incorrect surface name");
                YYABORT;
            }
        }

        //TODO: ADD TO INSTANCE LIST
        //printf("Created an instance group\n");

        currentGroup.push_back(newInstance);
    }
    ;

faceDeleteArgs:
	| faceDeleteArgs faceDelete
	;

mesh:
	MESH VARIABLE faceArgs END_MESH
    {

        MeshNew* currMesh = createMesh();

        for (std::list<FaceNew*>::iterator it=currentMeshFaces.begin(); it != currentMeshFaces.end(); ++it){
            currMesh->faces.insert(*it);
        }

        for (std::list<Vert*>::iterator it=currentMeshVertices.begin(); it != currentMeshVertices.end(); ++it){
            currMesh->verts.insert(*it);
        }

        for (std::list<EdgeNew*>::iterator it=currentMeshEdges.begin(); it != currentMeshEdges.end(); ++it){
            currMesh->edges.insert(*it);
        }

        currMesh->setName(strdup($<string>2));
        currSession->meshes.push_back(currMesh);
        //printf("Created a mesh\n");
	}
	;

group:
	GROUP VARIABLE instanceArgs END_GROUP
    {
        GroupNew* currGroup = createGroup(currentGroup);
        currGroup->setName(strdup($<string>2));
        currSession->groups.push_back(currGroup);
        currentGroup.clear();
        //printf("Created a group\n");
	}
	;

expr:
    OBRACE EXPR BANK_EXPR EBRACE
    {
        $<string>$ = $3;
        //printf("Expression\n");
    };

delete:
    BEG_DELETE faceDeleteArgs END_DELETE
    {
        //printf("Deleting faces\n");
	}
	;

set:
    SET VARIABLE numberValue numberValue numberValue numberValue
    {
        string currentSetName = $<string>2;
        double currentSetValue = $<number>3;
        double currentSetStart = $<number>4;
        double currentSetEnd = $<number>5;
        double currentSetStepSize = $<number>6;

        SetNew * currentSet = createSet(currentSetName, currentSetValue, currentSetStart, currentSetEnd, currentSetStepSize);

        currentSetList.push_back(currentSet);
        //printf("Created a Set\n");
	}
	;

setArgs:
    | setArgs set |  setArgs comment
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

        currentMeshFaces.push_back(newFace);

        tempVariables.clear();

        //printf("Created a face\n");
    }
    ;

bank:
	BANK VARIABLE setArgs END_BANK
    {
        BankNew * currentBank = createBank();
        currentBank->name = strdup($<string>2);
        currentBank->sets = currentSetList;
        currSession->banks.push_back(currentBank);
        currentSetList.clear();

        //printf("Created a bank\n");
	}
	;

circle:
    CIRCLE VARIABLE OPARENTHESES numberValue numberValue EPARENTHESES END_CIRCLE
    {
        string name = $<string>2;
        double num = $<number>4;
        double rad = $<number>5;

        //printf("Created a circle\n");
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

        //printf("Created a tunnel\n");
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


        //printf("Created a funnel\n");
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

        //printf("Created a face\n");
	}
	;

faceDelete:
	FACE VARIABLE END_FACE
	{
        //printf("Deleting face\n");
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

        //printf("Created a polyline\n");
	}
	;

instance:
    INSTANCE VARIABLE VARIABLE surfaceArgs transformArgs END_INSTANCE
    {

        string instanceName = strdup($<string>2);
        string lookFor = strdup($<string>3);

        MeshNew * currentMesh = currReader->mesh($<string>3);
        InstanceNew* newInstance;
        if (currentMesh != NULL) {
            newInstance = createInstance(currentMesh);
            newInstance->setName(strdup($<string>2));
        }
        else{
            yyerror("Incorrect vertex, face, or mesh name");
            YYABORT;
        }

        newInstance->transformations = currentTransformations;
        currentTransformations.clear();

        string surfaceName = $<string>4;
        // Check if a surface has been applied.
        if (surfaceName.length() != 0){
            Surface * currentSurface = currReader->surf($<string>4);
            if (currentSurface != NULL) {
                setSurface(newInstance, currentSurface);
            }
            else{
                yyerror("Incorrect surface name");
                YYABORT;
            }
        }

        currSession->instances.push_back(newInstance);



        //TODO: ADD TO INSTANCE LIST
        //printf("Created an instance\n");
	}
	;

object:
	OBJECT VARIABLE parenthesisName END_OBJECT
	{
        /*std::list<FaceNew*> facesObject;
        for (std::vector<string>::iterator it = tempVariables.begin() ; it != tempVariables.end(); ++it){
            FaceNew * currentFace = currReader->face(*it);
            if (currentFace != NULL) {
                facesObject.push_back(currentFace);
            }
            else{
                yyerror("Incorrect vertex name");
                YYABORT;
            }
        }

        MeshNew * newObject = createMesh(facesObject);

        newObject->setName(strdup($<string>2));

        currSession->objects.push_back(newObject);

        tempVariables.clear();*/

        //printf("Created an object\n");
	}
	;

surface:
    SURFACE VARIABLE COLOR OPARENTHESES numberValue numberValue numberValue EPARENTHESES END_SURFACE
    {
        double *r = (double*) malloc(sizeof(double));
        double *g = (double*) malloc(sizeof(double));
        double *b = (double*) malloc(sizeof(double));
        if ($<string>5 == NULL){
            *r = $<number>5;
        }
        else{
            r = getBankValue($<string>5);
        }

        if ($<string>6 == NULL){
            *g = $<number>6;
        }
        else{
            g = getBankValue($<string>6);
        }

        if ($<string>7 == NULL){
            *b = $<number>7;
        }
        else{
            b = getBankValue($<string>7);
        }

        currSession->surfaces.push_back(createSurface(r, g, b, strdup($<string>2)));
	}
	;

multi_line_comment:
	MULTI_LINE_COMMENT
	{
        //printf("Created a multiline comment.\n");
	}
	;

point:
    BEG_POINT VARIABLE OPARENTHESES numberValue numberValue numberValue EPARENTHESES END_POINT
    {
        double *x = (double*) malloc(sizeof(double));
        double *y = (double*) malloc(sizeof(double));
        double *z = (double*) malloc(sizeof(double));


        if ($<string>4 == NULL){
            *x = $<number>4;
        }
        else{
            x = getBankValue($<string>4);
        }

        if ($<string>5 == NULL){
            *y = $<number>5;
        }
        else{
            y = getBankValue($<string>5);
        }

        if ($<string>6 == NULL){
            *z = $<number>6;
        }
        else{
            z = getBankValue($<string>6);
        }

        Vert * newVertex = createVert (x, y, z);
        newVertex->setName(strdup($<string>2));
        currSession->verts.push_back(newVertex);
	}
	;

