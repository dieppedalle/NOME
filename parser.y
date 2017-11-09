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
std::vector<string> tempFaceDelete;
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

%error-verbose
%locations

%union
{
    double number;
    char *string;
    struct {
        char *string; // char *strVal;
        double number;   // int posVal;
    } numPos;
}

%token <string> BANK_EXPR
%token <string> NUMBER

%type <number> num
%type <string> expr

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
        $<numPos.number>$ = $<number>1;
        $<numPos.string>$ = NULL;
    } | expr
    {
        $<numPos.string>$ = $<string>1;
        $<numPos.number>$ = 0;
    }
    ;


num:
    NUMBER
    {
        $<number>$ = (double)atof($1);
    }
    ;

numPosTok:
    NUMBER
    {
        $<numPos.string>$ = strdup($1);
        $<numPos.number>$ = yycolumn;
    }
    ;

comment:
    COMMENT
    {
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
        double *x = (double*) malloc(sizeof(double));
        double *y = (double*) malloc(sizeof(double));
        double *z = (double*) malloc(sizeof(double));
        double *angle = (double*) malloc(sizeof(double));


        if ($<numPos.string>3 == NULL){
            *x = $<numPos.number>3;
        }
        else{
            x = getBankValue($<numPos.string>3);
        }

        if ($<numPos.string>4 == NULL){
            *y = $<numPos.number>4;
        }
        else{
            y = getBankValue($<numPos.string>4);
        }

        if ($<numPos.string>5 == NULL){
            *z = $<numPos.number>5;
        }
        else{
            z = getBankValue($<numPos.string>5);
        }

        if ($<numPos.string>8 == NULL){
            *angle = $<numPos.number>8;
        }
        else{
            angle = getBankValue($<numPos.string>8);
        }

        currentTransformations.push_back(createRotate(x, y, z, angle));

    }
    ;

translateArgs:
    TRANSLATE OPARENTHESES numberValue numberValue numberValue EPARENTHESES
    {
        double *x = (double*) malloc(sizeof(double));
        double *y = (double*) malloc(sizeof(double));
        double *z = (double*) malloc(sizeof(double));


        if ($<numPos.string>3 == NULL){
            *x = $<numPos.number>3;
        }
        else{
            x = getBankValue($<numPos.string>3);
        }

        if ($<numPos.string>4 == NULL){
            *y = $<numPos.number>4;
        }
        else{
            y = getBankValue($<numPos.string>4);
        }

        if ($<numPos.string>5 == NULL){
            *z = $<numPos.number>5;
        }
        else{
            z = getBankValue($<numPos.string>5);
        }

        currentTransformations.push_back(createTranslate(x, y, z));
    }
    ;

scaleArgs:
    SCALE OPARENTHESES numberValue numberValue numberValue EPARENTHESES
    {
        double *x = (double*) malloc(sizeof(double));
        double *y = (double*) malloc(sizeof(double));
        double *z = (double*) malloc(sizeof(double));


        if ($<numPos.string>3 == NULL){
            *x = $<numPos.number>3;
        }
        else{
            x = getBankValue($<numPos.string>3);
        }

        if ($<numPos.string>4 == NULL){
            *y = $<numPos.number>4;
        }
        else{
            y = getBankValue($<numPos.string>4);
        }

        if ($<numPos.string>5 == NULL){
            *z = $<numPos.number>5;
        }
        else{
            z = getBankValue($<numPos.string>5);
        }

        currentTransformations.push_back(createScale(x, y, z));
    }
    ;

mirrorArgs:
    MIRROR OPARENTHESES numberValue numberValue numberValue numberValue EPARENTHESES
    {
        double x = $<numPos.number>3;
        double y = $<numPos.number>4;
        double z = $<numPos.number>5;
        double w = $<numPos.number>5;

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

        MeshNew * currentMesh = currReader->getMesh($<string>3);

        InstanceNew* newInstance;
        if (currentMesh != NULL) {
            newInstance = createInstance(currentMesh, currSession->verts);
            newInstance->setName(strdup($<string>2));
        }
        else{
            yyerror("Incorrect vertex, face, or mesh name");
            YYABORT;
        }

        newInstance->transformations = currentTransformations;
        currentTransformations.clear();

        for (TransformationNew * t : newInstance->transformations){
            newInstance->applyTransformation(t);
        }

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
            currMesh->faces.push_back(*it);
        }

        for (std::list<Vert*>::iterator it=currentMeshVertices.begin(); it != currentMeshVertices.end(); ++it){
            currMesh->verts.push_back(*it);
        }

        for (std::list<EdgeNew*>::iterator it=currentMeshEdges.begin(); it != currentMeshEdges.end(); ++it){
            currMesh->edges.push_back(*it);
        }

        currMesh->setName(strdup($<string>2));
        currSession->meshes.push_back(currMesh);

        currentMeshFaces.clear();
        currentMeshEdges.clear();
        currentMeshVertices.clear();
	}
	;

group:
	GROUP VARIABLE instanceArgs END_GROUP
    {
        GroupNew* currGroup = createGroup(currentGroup);
        currGroup->setName(strdup($<string>2));
        currSession->groups.push_back(currGroup);
        currentGroup.clear();
	}
	;

expr:
    OBRACE EXPR BANK_EXPR EBRACE
    {
        $<string>$ = $3;
    };

delete:
    BEG_DELETE faceDeleteArgs END_DELETE
    {
        for (std::string currFace : tempFaceDelete){
            currReader->deleteFace(currReader->getFace(currFace));
        }

        tempFaceDelete.clear();
	}
	;

set:
    SET VARIABLE numPosTok numberValue numberValue numberValue
    {
        string currentSetName = $<string>2;
        double currentSetValue = (double)atof($<numPos.string>3);
        double currentSetStart = $<numPos.number>4;
        double currentSetEnd = $<numPos.number>5;
        double currentSetStepSize = $<numPos.number>6;
        string currentSetValueString = $<numPos.string>3;

        int begPos = $<numPos.number>3-currentSetValueString.length();
        int lengthValChar = currentSetValueString.length();

        SetNew * currentSet = createSet(currentSetName, currentSetValue, currentSetStart, currentSetEnd, currentSetStepSize, begPos, lengthValChar);

        currentSetList.push_back(currentSet);
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
            Vert * currentVertex = currReader->getVert(*it);
            if (currentVertex != NULL) {
                verticesFace.push_back(currentVertex);
                bool found = false;
                for (Vert* currentMeshVertex: currentMeshVertices){
                    if (currentMeshVertex->index == currentVertex->index){
                        found = true;
                    }
                }
                if (found == false){
                    currentMeshVertices.push_back(currentVertex);
                }

            }
            else{
                yyerror("Incorrect vertex name");
                YYABORT;
            }
        }
        FaceNew * newFace = createFace(verticesFace, &currentMeshEdges);
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

        currentMeshFaces.push_back(newFace);

        tempVariables.clear();
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
	}
	;

circle:
    CIRCLE VARIABLE OPARENTHESES numberValue numberValue EPARENTHESES END_CIRCLE
    {
        string name = $<string>2;
        double *num = (double*) malloc(sizeof(double));
        double *rad = (double*) malloc(sizeof(double));


        if ($<numPos.string>4 == NULL){
            *num = $<numPos.number>4;
        }
        else{
            num = getBankValue($<numPos.string>4);
        }

        if ($<numPos.string>5 == NULL){
            *rad = $<numPos.number>5;
        }
        else{
            rad = getBankValue($<numPos.string>5);
        }

        CircleNew* currCircle = createCircle(num, rad);
        currCircle->setName(strdup($<string>2));

        currSession->circles.push_back(currCircle);
    };

tunnel:
    TUNNEL VARIABLE OPARENTHESES numberValue numberValue numberValue numberValue EPARENTHESES
  END_TUNNEL
	{
        string name = $<string>2;
        double *n = (double*) malloc(sizeof(double));
        double *ro = (double*) malloc(sizeof(double));
        double *ratio = (double*) malloc(sizeof(double));
        double *h = (double*) malloc(sizeof(double));

        if ($<numPos.string>4 == NULL){
            *n = $<numPos.number>4;
        }
        else{
            n = getBankValue($<numPos.string>4);
        }

        if ($<numPos.string>5 == NULL){
            *ro = $<numPos.number>5;
        }
        else{
            ro = getBankValue($<numPos.string>5);
        }

        if ($<numPos.string>6 == NULL){
            *ratio = $<numPos.number>6;
        }
        else{
            ratio = getBankValue($<numPos.string>6);
        }

        if ($<numPos.string>7 == NULL){
            *h = $<numPos.number>7;
        }
        else{
            h = getBankValue($<numPos.string>7);
        }

        TunnelNew* currTunnel = createTunnel(n, ro, ratio, h);
        currTunnel->setName(strdup($<string>2));

        currSession->tunnels.push_back(currTunnel);
	}
	;

funnel:
    FUNNEL VARIABLE OPARENTHESES numberValue numberValue numberValue numberValue EPARENTHESES
  END_FUNNEL
	{
        string name = $<string>2;
        double *n = (double*) malloc(sizeof(double));
        double *ro = (double*) malloc(sizeof(double));
        double *ratio = (double*) malloc(sizeof(double));
        double *h = (double*) malloc(sizeof(double));

        if ($<numPos.string>4 == NULL){
            *n = $<numPos.number>4;
        }
        else{
            n = getBankValue($<numPos.string>4);
        }

        if ($<numPos.string>5 == NULL){
            *ro = $<numPos.number>5;
        }
        else{
            ro = getBankValue($<numPos.string>5);
        }

        if ($<numPos.string>6 == NULL){
            *ratio = $<numPos.number>6;
        }
        else{
            ratio = getBankValue($<numPos.string>6);
        }

        if ($<numPos.string>7 == NULL){
            *h = $<number>7;
        }
        else{
            h = getBankValue($<numPos.string>7);
        }

        FunnelNew* currFunnel = createFunnel(n, ro, ratio, h);
        currFunnel->setName(strdup($<string>2));

        currSession->funnels.push_back(currFunnel);
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
	}
	;

faceDelete:
	FACE VARIABLE END_FACE
	{
        tempFaceDelete.push_back($<string>2);
	}
	;

polyline:
	POLYLINE VARIABLE parenthesisName END_POLYLINE
	{
        // Create list of vertices of face.
        std::list<Vert*> verticesPolyline;
        for (std::vector<string>::iterator it = tempVariables.begin() ; it != tempVariables.end(); ++it){
            Vert * currentVertex = currReader->getVert(*it);
            if (currentVertex != NULL) {
                verticesPolyline.push_back(currentVertex);
            }
            else{
                yyerror("Incorrect vertex name");
                YYABORT;
            }
        }

        PolylineNew* currPolyline = createPolylineNew(verticesPolyline);
        currPolyline->setName(strdup($<string>2));

        currSession->polylines.push_back(currPolyline);
        tempVariables.clear();
	}
	;

instance:
    INSTANCE VARIABLE VARIABLE surfaceArgs transformArgs END_INSTANCE
    {

        string instanceName = strdup($<string>2);
        string lookFor = strdup($<string>3);

        MeshNew * currentMesh = currReader->getMesh($<string>3);

        InstanceNew* newInstance = NULL;
        if (currentMesh != NULL) {
            newInstance = createInstance(currentMesh, currSession->verts);
            newInstance->setName(strdup($<string>2));

            newInstance->transformations = currentTransformations;
            currentTransformations.clear();

            for (TransformationNew * t : newInstance->transformations){
                newInstance->applyTransformation(t);
            }
        }
        else{

            GroupNew * currentGroup = currReader->getGroup($<string>3);
            if (currentGroup != NULL) {
                newInstance = createInstance(currentGroup, currSession->verts);
                newInstance->setName(strdup($<string>2));
            }
            else{
                yyerror("Incorrect vertex, face, or mesh name");
                YYABORT;
            }
        }

        /*newInstance->transformations = currentTransformations;
        currentTransformations.clear();

        for (TransformationNew * t : newInstance->transformations){
            newInstance->applyTransformation(t);
        }*/

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

        if ($<numPos.string>5 == NULL){
            *r = $<numPos.number>5;
        }
        else{
            r = getBankValue($<numPos.string>5);
        }

        if ($<numPos.string>6 == NULL){
            *g = $<numPos.number>6;
        }
        else{
            g = getBankValue($<numPos.string>6);
        }

        if ($<numPos.string>7 == NULL){
            *b = $<numPos.number>7;
        }
        else{
            b = getBankValue($<numPos.string>7);
        }

        currSession->surfaces.push_back(createSurface(r, g, b, strdup($<string>2)));
	}
	;

multi_line_comment:
	MULTI_LINE_COMMENT
    {
	}
	;

point:
    BEG_POINT VARIABLE OPARENTHESES numberValue numberValue numberValue EPARENTHESES END_POINT
    {
        double *x = (double*) malloc(sizeof(double));
        double *y = (double*) malloc(sizeof(double));
        double *z = (double*) malloc(sizeof(double));


        if ($<numPos.string>4 == NULL){
            *x = $<numPos.number>4;
        }
        else{
            x = getBankValue($<numPos.string>4);
        }

        if ($<numPos.string>5 == NULL){
            *y = $<numPos.number>5;
        }
        else{
            y = getBankValue($<numPos.string>5);
        }

        if ($<numPos.string>6 == NULL){
            *z = $<numPos.number>6;
        }
        else{
            z = getBankValue($<numPos.string>6);
        }

        Vert * newVertex = createVert (x, y, z);
        newVertex->setName(strdup($<string>2));
        currSession->verts.push_back(newVertex);
	}
	;

