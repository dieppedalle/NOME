%code requires{
#include <newNOME/Session.h>

}

%{
#include <stdio.h>
#include <string.h>
#include <list>
#include <newNOME/Data.h>
#include <newNOME/MeshNew.h>
#include <newNOME/Session.h>
#include <newNOME/Reader.h>
#include <newNOME/TransformationNew.h>
#include <newNOME/PolylineNew.h>
#include <newNOME/SweepNew.h>
#include <newNOME/CircleNew.h>
#include <newNOME/FunnelNew.h>
#include <newNOME/TunnelNew.h>
#include <newNOME/InstanceNew.h>
#include <newNOME/BSplineNew.h>
#include <newNOME/BezierCurveNew.h>

extern int nomlineno;
extern char* nomtext;
extern int nomcolumn;

int nomlex(void);
void nomerror(Session* currSession, const char *s) {
  printf("%s on line %d - %s\n", s, nomlineno, nomtext);
}

int nomwrap() {
    return 1;
}

map<string,QColor> surfaces2;
map<string,Vert*> vertices2;
std::vector<string> tempVariables2;
std::vector<string> tempFaceDelete2;
string currentSetName2;
std::list<SetNew *> currentSetList2;
map<string,std::vector<double>> currentBank2;
std::vector<string> currentInstanceList2;
std::list<InstanceNew *> currentGroup2;
std::list<FaceNew *> currentMeshFaces2;
std::list<PolylineNew *> currentMeshPolyline;
std::list<Vert *> currentMeshVertices2;
std::list<EdgeNew *> currentMeshEdges2;
std::list<TransformationNew *> currentTransformations2;
std::string surfaceFromArg;

%}

%parse-param { Session* currSession }

//%defines "compilerNome/parser.h"
//%output "compilerNome/parser.cpp"
//%define api.prefix {nom}

%token COLOR VARIABLE COMMENT NEWLINE SURFACE END_SURFACE MESH END_MESH FACE END_FACE BEG_POINT
END_POINT OBJECT END_OBJECT BANK END_BANK TUNNEL END_TUNNEL FUNNEL END_FUNNEL
POLYLINE SWEEP END_SWEEP END_POLYLINE INSTANCE END_INSTANCE CIRCLE END_CIRCLE BEG_DELETE END_DELETE
GROUP  END_GROUP TRANSLATE ROTATE MIRROR SET OPARENTHESES EPARENTHESES OBRACE
EXPR DOLLAR EBRACE PERIOD TOKHEAT STATE TOKTARGET TOKTEMPERATURE
SCALE SUBDIVISION END_SUBDIVISION SUBDIVISIONS TYPE OFFSET END_OFFSET MIN MAX STEP
BSPLINE END_BSPLINE CLOSED SLICES BEZIERCURVE END_BEZIERCURVE COS SIN TAN EXPONENT
MULTIPLY DIVIDE ADD SUBTRACT SLIDEREXPRESSION REVERSE;

%error-verbose
%locations


%union
{
    std::vector<std::string>* strings;
    double intNumber;
    double number;
    const char *string;
    bool boolean;
    struct {
        const char *string; // char *strVal;
        double number;   // int posVal;
    } numPos;
}

%token <string> BANK_EXPR
%token <string> NUMBER


%type <boolean> closedArgs
%type <number> num
%type <string> expr
%type <numPos> numberValue
%type <strings> variables
%type <strings> parenthesisName


%%

commands: /* empty */
        | commands command
        ;


command:
    comment | mesh | surface | point | face | object | bank |
  tunnel | funnel | polyline | sweep | instance | delete | group | circle |
  subdivision | offset | bspline | beziercurve;

numberValue:
    NUMBER {
        $<string>$ = strdup($<string>1);
    } | SLIDEREXPRESSION
    {
        std::string exprStr = strdup($<string>1);
        exprStr.erase(0, 6);
        exprStr.erase(exprStr.size() - 1);
        $<string>$ = strdup(exprStr.c_str());
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
        $<numPos>$.string = strdup($1);
        $<numPos>$.number = nomcolumn;
    }
    ;

comment:
    COMMENT
    {
    }
    ;


variables: { $$ = new std::vector<std::string>(); }
  |
    variables VARIABLE {
	$$->push_back($<string>2);
        tempVariables2.push_back($<string>2);
    }
        ;

surfaceArgs:
    SURFACE VARIABLE {
        if (surfaceFromArg.length() == 0){
          surfaceFromArg = strdup($<string>2);
        }
    };

closedArgs:
    {$<boolean>$ = false;}
    | CLOSED {
        $<boolean>$ = true;
    };

transformArgs:
    | faceArgs comment | transformArgs rotateArgs | transformArgs reverseArgs |  transformArgs translateArgs | transformArgs scaleArgs | transformArgs mirrorArgs | transformArgs surfaceArgs
    ;

reverseArgs:
    REVERSE
    {
      Reverse* currReverse = createReverse();
      currentTransformations2.push_back(currReverse);
    };

rotateArgs:
    ROTATE OPARENTHESES numberValue numberValue numberValue EPARENTHESES OPARENTHESES numberValue EPARENTHESES
    {
        double *x = (double*) malloc(sizeof(double));
        double *y = (double*) malloc(sizeof(double));
        double *z = (double*) malloc(sizeof(double));
        double *angle = (double*) malloc(sizeof(double));

        double *currentValSet = (double*) malloc(sizeof(double));
        parseGetBankVal($<string>3, currSession, currentValSet, nomlineno);
        *x = *currentValSet;
        parseGetBankVal($<string>4, currSession, currentValSet, nomlineno);
        *y = *currentValSet;
        parseGetBankVal($<string>5, currSession, currentValSet, nomlineno);
        *z = *currentValSet;
        parseGetBankVal($<string>8, currSession, currentValSet, nomlineno);
        *angle = *currentValSet;

        Rotate* currRotate = createRotate(x, y, z, angle);
        currRotate->xStr = strdup($<string>3);
        currRotate->yStr = strdup($<string>4);
        currRotate->zStr = strdup($<string>5);
        currRotate->angleStr = strdup($<string>8);

        currentTransformations2.push_back(currRotate);

    }
    ;

translateArgs:
    TRANSLATE OPARENTHESES numberValue numberValue numberValue EPARENTHESES
    {
        double *x = (double*) malloc(sizeof(double));
        double *y = (double*) malloc(sizeof(double));
        double *z = (double*) malloc(sizeof(double));

        double *currentValSet = (double*) malloc(sizeof(double));
        parseGetBankVal($<string>3, currSession, currentValSet, nomlineno);
        *x = *currentValSet;
        parseGetBankVal($<string>4, currSession, currentValSet, nomlineno);
        *y = *currentValSet;
        parseGetBankVal($<string>5, currSession, currentValSet, nomlineno);
        *z = *currentValSet;

        Translate* currTranslate = createTranslate(x, y, z);
        currTranslate->xStr = strdup($<string>3);
        currTranslate->yStr = strdup($<string>4);
        currTranslate->zStr = strdup($<string>5);

        currentTransformations2.push_back(currTranslate);
    }
    ;

scaleArgs:
    SCALE OPARENTHESES numberValue numberValue numberValue EPARENTHESES
    {
        double *x = (double*) malloc(sizeof(double));
        double *y = (double*) malloc(sizeof(double));
        double *z = (double*) malloc(sizeof(double));

        double *currentValSet = (double*) malloc(sizeof(double));
        parseGetBankVal($<string>3, currSession, currentValSet, nomlineno);
        *x = *currentValSet;
        parseGetBankVal($<string>4, currSession, currentValSet, nomlineno);
        *y = *currentValSet;
        parseGetBankVal($<string>5, currSession, currentValSet, nomlineno);
        *z = *currentValSet;

        Scale* currScale = createScale(x, y, z);
        currScale->xStr = strdup($<string>3);
        currScale->yStr = strdup($<string>4);
        currScale->zStr = strdup($<string>5);

        currentTransformations2.push_back(currScale);
    }
    ;

mirrorArgs:
    MIRROR OPARENTHESES numberValue numberValue numberValue numberValue EPARENTHESES
    {
        double *currentValSet = (double*) malloc(sizeof(double));
        parseGetBankVal($<string>3, currSession, currentValSet, nomlineno);
        double x = *currentValSet;
        parseGetBankVal($<string>4, currSession, currentValSet, nomlineno);
        double y = *currentValSet;
        parseGetBankVal($<string>5, currSession, currentValSet, nomlineno);
        double z = *currentValSet;
        parseGetBankVal($<string>6, currSession, currentValSet, nomlineno);
        double w = *currentValSet;

    }
    ;

faceArgs:
    | faceArgs faceMesh | faceArgs comment | faceArgs polylineMesh
        ;

instanceArgs:
    | instanceArgs instanceGroup
        ;

instanceGroup:
    INSTANCE VARIABLE VARIABLE transformArgs END_INSTANCE
    {
        Reader* currReader = createReader(currSession);
        string instanceName = strdup($<string>2);
        string lookFor = strdup($<string>3);

        MeshNew * currentMesh = currReader->getMesh($<string>3);

        InstanceNew* newInstance;
        if (currentMesh != NULL) {
            newInstance = createInstance(currentMesh, currSession->verts, currReader, false, false, false, currSession);
            newInstance->currSession = currSession;
            newInstance->setName(strdup($<string>2));
        }
        else{
            nomerror(currSession, "Incorrect vertex, face, or mesh name");
            YYABORT;
        }

        newInstance->transformations = currentTransformations2;
        currentTransformations2.clear();

        for (TransformationNew * t : newInstance->transformations){
            newInstance->applyTransformation(t);
        }

        string surfaceName = surfaceFromArg;
        // Check if a surface has been applied.
        if (surfaceName.length() != 0){
            Surface * currentSurface = currReader->surf(surfaceFromArg);
            if (currentSurface != NULL) {
                setSurface(newInstance, currentSurface);
            }
            else{
                nomerror(currSession, "Incorrect surface name");
                YYABORT;
            }
        }
        currentGroup2.push_back(newInstance);
        surfaceFromArg = "";
    }
    ;

faceDeleteArgs:
        | faceDeleteArgs faceDelete
        ;

instanceOffseSubdivide:
    INSTANCE VARIABLE
    {
        string instanceName = strdup($<string>2);
    };

instanceOffseSubdivideArgs:
    | instanceOffseSubdivideArgs instanceOffseSubdivide
    ;

subdivision:
    SUBDIVISION VARIABLE instanceOffseSubdivideArgs TYPE VARIABLE SUBDIVISIONS numberValue END_SUBDIVISION
    {
        double *subdivision = (double*) malloc(sizeof(double));

        double *currentValSet = (double*) malloc(sizeof(double));
        parseGetBankVal($<string>7, currSession, currentValSet, nomlineno);
        *subdivision = *currentValSet;

        SubdivisionNew* currSubdivision = createSubdivision(strdup($<string>3), strdup($<string>5), subdivision);
        currSession->subdivisions.push_back(currSubdivision);
    };

offset:
    OFFSET VARIABLE MIN numberValue MAX numberValue STEP numberValue END_OFFSET
    {
        double *min = (double*) malloc(sizeof(double));
        double *max = (double*) malloc(sizeof(double));
        double *step = (double*) malloc(sizeof(double));

        double *currentValSet = (double*) malloc(sizeof(double));
        parseGetBankVal($<string>4, currSession, currentValSet, nomlineno);
        *min = *currentValSet;
        parseGetBankVal($<string>6, currSession, currentValSet, nomlineno);
        *max = *currentValSet;
        parseGetBankVal($<string>8, currSession, currentValSet, nomlineno);
        *step = *currentValSet;

        OffsetNew* currOffset = createOffset(strdup($<string>2), min, max, step);

        currSession->offsets.push_back(currOffset);
    };

mesh:
        MESH VARIABLE faceArgs END_MESH
    {

        MeshNew* currMesh = createMesh();

        for (std::list<FaceNew*>::iterator it=currentMeshFaces2.begin(); it != currentMeshFaces2.end(); ++it){
            currMesh->faces.push_back(*it);
        }

        for (std::list<Vert*>::iterator it=currentMeshVertices2.begin(); it != currentMeshVertices2.end(); ++it){
            currMesh->verts.push_back(*it);
        }

        for (std::list<EdgeNew*>::iterator it=currentMeshEdges2.begin(); it != currentMeshEdges2.end(); ++it){
            currMesh->edges.push_back(*it);
        }

        currMesh->setName(strdup($<string>2));
        currSession->meshes.push_back(currMesh);

        currentMeshFaces2.clear();
        currentMeshEdges2.clear();
        currentMeshVertices2.clear();
        }
        ;

group:
        GROUP VARIABLE instanceArgs END_GROUP
    {
        GroupNew* currGroup = createGroup(currentGroup2);
        currGroup->setName(strdup($<string>2));
        currSession->groups.push_back(currGroup);
        currentGroup2.clear();
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
        Reader* currReader = createReader(currSession);

        for (std::string currFace : tempFaceDelete2){
            currReader->deleteFace(currReader->getFace(currFace));
        }

        tempFaceDelete2.clear();
        }
        ;

set:
    SET VARIABLE numPosTok numberValue numberValue numberValue
    {
        string currentSetName = $<string>2;
        double currentSetValue = (double)atof($<numPos>3.string);
        double *currentValSet = (double*) malloc(sizeof(double));
        parseGetBankVal($<string>4, currSession, currentValSet, nomlineno);
        double currentSetStart = *currentValSet;
        parseGetBankVal($<string>5, currSession, currentValSet, nomlineno);
        double currentSetEnd = *currentValSet;
        parseGetBankVal($<string>6, currSession, currentValSet, nomlineno);
        double currentSetStepSize = *currentValSet;
        string currentSetValueString = $<numPos>3.string;


        int begPos = $<numPos>3.number-currentSetValueString.length();
        int lengthValChar = currentSetValueString.length();

        SetNew * currentSet = createSet(currentSetName, currentSetValue, currentSetStart, currentSetEnd, currentSetStepSize, begPos, lengthValChar);

        currentSetList2.push_back(currentSet);
        }
        ;

setArgs:
    | setArgs set |  setArgs comment
        ;

polylineMesh:
POLYLINE VARIABLE parenthesisName transformArgs END_POLYLINE
{
    Reader* currReader = createReader(currSession);

    // Create list of vertices of face.
    std::list<Vert*> verticesPolyline;
    for (std::vector<string>::iterator it = tempVariables2.begin() ; it != tempVariables2.end(); ++it){
        Vert * currentVertex = currReader->getVert(*it);
        if (currentVertex != NULL) {
            verticesPolyline.push_back(currentVertex);
            currentMeshVertices2.push_back(currentVertex);
        }
        else{
            nomerror(currSession, "Incorrect vertex name");
            YYABORT;
        }
    }

    PolylineNew* currPolyline = createPolylineNew(verticesPolyline);
    for (EdgeNew* e : currPolyline->edges){
      currentMeshEdges2.push_back(e);
    }

    currPolyline->setName(strdup($<string>2));

    string surfaceName = surfaceFromArg;
    // Check if a surface has been applied.
    if (surfaceName.length() != 0){
        Surface * currentSurface = currReader->surf(surfaceFromArg);
        if (currentSurface != NULL) {
            currPolyline->setSurface(currentSurface);
        }
        else{
            nomerror(currSession, "Incorrect surface name");
            YYABORT;
        }
    }
    currentMeshPolyline.push_back(currPolyline);

    tempVariables2.clear();
    surfaceFromArg = "";
}
;

faceMesh:
    FACE VARIABLE parenthesisName transformArgs END_FACE
    {
        Reader* currReader = createReader(currSession);

        std::list<Vert*> verticesFace;
        //std::cout << "FACE MESH" << std::endl;
        for (std::vector<string>::iterator it = tempVariables2.begin() ; it != tempVariables2.end(); ++it){
            Vert * currentVertex = currReader->getVert(*it);
            if (currentVertex != NULL) {
                verticesFace.push_back(currentVertex);
                bool found = false;
                for (Vert* currentMeshVertex: currentMeshVertices2){
                    if (currentMeshVertex->index == currentVertex->index){
                        found = true;
                    }
                }
                if (found == false){
                    currentMeshVertices2.push_back(currentVertex);
                }

            }
            else{
                std::string errorMessage = "Incorrect vertex name " + *it;
                const char * errorMessageC = errorMessage.c_str();
                nomerror(currSession, errorMessageC);
                YYABORT;
            }
        }

        FaceNew * newFace = createFace(verticesFace, &currentMeshEdges2, currReader, false);
        setName(newFace, strdup($<string>2));

        string surfaceName = surfaceFromArg;
        // Check if a surface has been applied.
        if (surfaceName.length() != 0){
            Surface * currentSurface = currReader->surf(surfaceFromArg);
            if (currentSurface != NULL) {
                setSurface(newFace, currentSurface);
            }
            else{
                nomerror(currSession, "Incorrect surface name");
                YYABORT;
            }
        }

        currentMeshFaces2.push_back(newFace);

        tempVariables2.clear();
        surfaceFromArg = "";
    }
    ;

bank:
        BANK VARIABLE setArgs END_BANK
    {
        BankNew * currentBank2 = createBank();
        currentBank2->name = strdup($<string>2);
        currentBank2->sets = currentSetList2;
        currSession->banks.push_back(currentBank2);
        currentSetList2.clear();
        }
        ;

circle:
    CIRCLE VARIABLE OPARENTHESES numberValue numberValue EPARENTHESES END_CIRCLE
    {
        string name = $<string>2;
        double *num = (double*) malloc(sizeof(double));
        double *rad = (double*) malloc(sizeof(double));

        double *currentValSet = (double*) malloc(sizeof(double));
        parseGetBankVal($<string>4, currSession, currentValSet, nomlineno);
        *num = *currentValSet;

        parseGetBankVal($<string>5, currSession, currentValSet, nomlineno);
        *rad = *currentValSet;

        CircleNew* currCircle = createCircle(num, rad);
        currCircle->setName(strdup($<string>2));
        currCircle->numStr = strdup($<string>4);
        currCircle->radStr = strdup($<string>5);
        currCircle->currSession = currSession;
        currCircle->createVertEdgeCircle();

        currSession->circles.push_back(currCircle);
    };

tunnel:
    TUNNEL VARIABLE OPARENTHESES numberValue numberValue numberValue numberValue EPARENTHESES
  END_TUNNEL
        {
        Reader* currReader = createReader(currSession);

        string name = $<string>2;
        double *n = (double*) malloc(sizeof(double));
        double *ro = (double*) malloc(sizeof(double));
        double *ratio = (double*) malloc(sizeof(double));
        double *h = (double*) malloc(sizeof(double));

        double *currentValSet = (double*) malloc(sizeof(double));
        parseGetBankVal($<string>4, currSession, currentValSet, nomlineno);
        *n = *currentValSet;
        parseGetBankVal($<string>5, currSession, currentValSet, nomlineno);
        *ro = *currentValSet;
        parseGetBankVal($<string>6, currSession, currentValSet, nomlineno);
        *ratio = *currentValSet;
        parseGetBankVal($<string>7, currSession, currentValSet, nomlineno);
        *h = *currentValSet;

        TunnelNew* currTunnel = createTunnel(n, ro, ratio, h, currReader);
        currTunnel->setName(strdup($<string>2));
        currTunnel->nStr = strdup($<string>4);
        currTunnel->roStr = strdup($<string>5);
        currTunnel->ratioStr = strdup($<string>6);
        currTunnel->hStr = strdup($<string>7);
        currTunnel->currSession = currSession;

        currSession->tunnels.push_back(currTunnel);
        }
        ;

funnel:
    FUNNEL VARIABLE OPARENTHESES numberValue numberValue numberValue numberValue EPARENTHESES
  END_FUNNEL
        {
        Reader* currReader = createReader(currSession);

        string name = $<string>2;
        double *n = (double*) malloc(sizeof(double));
        double *ro = (double*) malloc(sizeof(double));
        double *ratio = (double*) malloc(sizeof(double));
        double *h = (double*) malloc(sizeof(double));

        double *currentValSet = (double*) malloc(sizeof(double));
        parseGetBankVal($<string>4, currSession, currentValSet, nomlineno);
        *n = *currentValSet;
        parseGetBankVal($<string>5, currSession, currentValSet, nomlineno);
        *ro = *currentValSet;
        parseGetBankVal($<string>6, currSession, currentValSet, nomlineno);
        *ratio = *currentValSet;
        parseGetBankVal($<string>7, currSession, currentValSet, nomlineno);
        *h = *currentValSet;

        FunnelNew* currFunnel = createFunnel(n, ro, ratio, h, currReader);
        currFunnel->setName(strdup($<string>2));

        currFunnel->nStr = strdup($<string>4);
        currFunnel->roStr = strdup($<string>5);
        currFunnel->ratioStr = strdup($<string>6);
        currFunnel->hStr = strdup($<string>7);
        currFunnel->currSession = currSession;

        currSession->funnels.push_back(currFunnel);
        }
        ;

parenthesisName:
        OPARENTHESES variables EPARENTHESES
    { $$ = $2;
        }
        ;

face:
        FACE VARIABLE parenthesisName transformArgs END_FACE
    {
        Reader* currReader = createReader(currSession);

        std::list<Vert*> verticesFace;
        for (std::vector<string>::iterator it = tempVariables2.begin() ; it != tempVariables2.end(); ++it){
            Vert * currentVertex = currReader->getVert(*it);
            if (currentVertex != NULL) {
                verticesFace.push_back(currentVertex);
            }
            else{
                nomerror(currSession, "Incorrect vertex name");
                YYABORT;
            }
        }

        FaceNew * newFace = createFace(verticesFace, &(currSession->edges), currReader, false);

        setName(newFace, strdup($<string>2));


        string surfaceName = surfaceFromArg;
        // Check if a surface has been applied.
        if (surfaceName.length() != 0){
            Surface * currentSurface = currReader->surf(surfaceFromArg);
            if (currentSurface != NULL) {
                setSurface(newFace, currentSurface);
            }
            else{
                nomerror(currSession, "Incorrect surface name");
                YYABORT;
            }
        }

        currSession->faces.push_back(newFace);

        tempVariables2.clear();
        surfaceFromArg = "";
        }
        ;

faceDelete:
        FACE VARIABLE END_FACE
        {
        tempFaceDelete2.push_back($<string>2);
        }
        ;

beziercurve:
  BEZIERCURVE VARIABLE parenthesisName SLICES numberValue transformArgs END_BEZIERCURVE{
    double *slices = (double*) malloc(sizeof(double));
    Reader* currReader = createReader(currSession);


    BezierCurveNew* currBezierCurve = createBezierCurveNew();
    currBezierCurve->setName(strdup($<string>2));
    double *currentValSet = (double*) malloc(sizeof(double));
    //parseGetBankVal($<string>5, currSession, currentValSet);
    //*slices = *currentValSet;
    *slices = 0;
    currBezierCurve->segments = slices;
    currBezierCurve->segmentsStr = strdup($<string>5);
    currBezierCurve->currSession = currSession;

    // Create list of vertices of face.
    for (std::vector<string>::iterator it = tempVariables2.begin() ; it != tempVariables2.end(); ++it){
        Vert * currentVertex = currReader->getVert(*it);
        if (currentVertex != NULL) {
            currBezierCurve->proxy.push_back(currentVertex);
        }
        else{
            nomerror(currSession, "Incorrect vertex name");
            YYABORT;
        }
    }

    currBezierCurve->updateBezierCurve();

    string surfaceName = surfaceFromArg;
    // Check if a surface has been applied.
    if (surfaceName.length() != 0){
        Surface * currentSurface = currReader->surf(surfaceFromArg);
        if (currentSurface != NULL) {
            currBezierCurve->setSurface(currentSurface);
        }
        else{
            nomerror(currSession, "Incorrect surface name");
            YYABORT;
        }
    }

    currSession->bezierCurves.push_back(currBezierCurve);
    tempVariables2.clear();
    surfaceFromArg = "";
};


bspline:
        BSPLINE VARIABLE parenthesisName closedArgs SLICES numberValue transformArgs END_BSPLINE{
    if ($<intNumber>1 != $<intNumber>8) {
        nomerror(currSession, "bspline and endbspline do not have the same number.");
        YYABORT;
    }

    Reader* currReader = createReader(currSession);

    BSplineNew* currBSpline = createBSplineNew();
    currBSpline->setName(strdup($<string>2));
    currBSpline->set_order($<intNumber>1);
    double *currentValSet = (double*) malloc(sizeof(double));
    parseGetBankVal($<string>6, currSession, currentValSet, nomlineno);
    currBSpline->segments = -1;
    currBSpline->currSession = currSession;

    currBSpline->segmentsStr = strdup($<string>6);


    // Create list of vertices of face.
    for (std::vector<string>::iterator it = tempVariables2.begin() ; it != tempVariables2.end(); ++it){
        Vert * currentVertex = currReader->getVert(*it);
        if (currentVertex != NULL) {
            currBSpline->proxy.push_back(currentVertex);
        }
        else{
            nomerror(currSession, "Incorrect vertex name");
            YYABORT;
        }
    }

    currBSpline->isLoop = $<boolean>4;

    if (currBSpline->order > currBSpline->proxy.size()){
      std::string errorStr = "bspline order (";
      errorStr += currBSpline->order;
      errorStr += ") must be <= #controlpoints (";
      errorStr += currBSpline->proxy.size();
      errorStr += ").";
      nomerror(currSession, errorStr.c_str());
      YYABORT;
    }

    currBSpline->updateBSpline();

    string surfaceName = surfaceFromArg;
    // Check if a surface has been applied.
    if (surfaceName.length() != 0){
        Surface * currentSurface = currReader->surf(surfaceFromArg);
        if (currentSurface != NULL) {
            currBSpline->setSurface(currentSurface);
        }
        else{
            nomerror(currSession, "Incorrect surface name");
            YYABORT;
        }
    }


    currSession->bsplines.push_back(currBSpline);

    tempVariables2.clear();
    surfaceFromArg = "";
  };

sweep:
        SWEEP VARIABLE parenthesisName parenthesisName numberValue numberValue transformArgs END_SWEEP
        {
        Reader* currReader = createReader(currSession);

        // Create list of vertices of face.
        std::list<Vert*> verticesPolyline;
        for (std::vector<string>::iterator it = $3->begin() ; it != $3->end(); ++it){
            Vert * currentVertex = currReader->getVert(*it);
            if (currentVertex != NULL) {
                verticesPolyline.push_back(currentVertex);
            }
            else{
                nomerror(currSession, "Incorrect vertex name");
                YYABORT;
            }
        }

        // Create list of vertices of face.
        std::list<Vert*> crosssectionPolyline;
        for (std::vector<string>::iterator it = $4->begin() ; it != $4->end(); ++it){
            Vert * currentVertex = currReader->getVert(*it);
            if (currentVertex != NULL) {
               crosssectionPolyline.push_back(currentVertex);
            }
            else{
                nomerror(currSession, "Incorrect vertex name");
                YYABORT;
            }
        }


        double *width = (double*) malloc(sizeof(double));
        double *azimuth = (double*) malloc(sizeof(double));
        double *twist = (double*) malloc(sizeof(double));

        double *currentValSet = (double*) malloc(sizeof(double));
        parseGetBankVal($<string>5, currSession, currentValSet, nomlineno);
        *width = *currentValSet;
        parseGetBankVal($<string>5, currSession, currentValSet, nomlineno);
        *azimuth = *currentValSet;
        parseGetBankVal($<string>6, currSession, currentValSet, nomlineno);
        *twist = *currentValSet;


        SweepNew* currPolyline = createSweepNew(verticesPolyline, crosssectionPolyline, width, azimuth, twist, currReader);
        currPolyline->setName(strdup($<string>2));

        string surfaceName = surfaceFromArg;
        // Check if a surface has been applied.
        if (surfaceName.length() != 0){
            Surface * currentSurface = currReader->surf(surfaceFromArg);
            if (currentSurface != NULL) {
                currPolyline->setSurface(currentSurface);
            }
            else{
                nomerror(currSession, "Incorrect surface name");
                YYABORT;
            }
        }
        currSession->sweeps.push_back(currPolyline);
        tempVariables2.clear();
        surfaceFromArg = "";
        }
        ;

polyline:
        POLYLINE VARIABLE parenthesisName transformArgs END_POLYLINE
        {
        Reader* currReader = createReader(currSession);

        // Create list of vertices of face.
        std::list<Vert*> verticesPolyline;
        for (std::vector<string>::iterator it = tempVariables2.begin() ; it != tempVariables2.end(); ++it){
            Vert * currentVertex = currReader->getVert(*it);
            if (currentVertex != NULL) {
                verticesPolyline.push_back(currentVertex);
            }
            else{
                nomerror(currSession, "Incorrect vertex name");
                YYABORT;
            }
        }

        PolylineNew* currPolyline = createPolylineNew(verticesPolyline);
        currPolyline->setName(strdup($<string>2));

        string surfaceName = surfaceFromArg;
        // Check if a surface has been applied.
        if (surfaceName.length() != 0){
            Surface * currentSurface = currReader->surf(surfaceFromArg);
            if (currentSurface != NULL) {
                currPolyline->setSurface(currentSurface);
            }
            else{
                nomerror(currSession, "Incorrect surface name");
                YYABORT;
            }
        }
        currSession->polylines.push_back(currPolyline);
        tempVariables2.clear();
        surfaceFromArg = "";
        }
        ;

instance:
    INSTANCE VARIABLE VARIABLE transformArgs END_INSTANCE
    {
        Reader* currReader = createReader(currSession);

        string instanceName = strdup($<string>2);
        string lookFor = strdup($<string>3);

        MeshNew * currentMesh = currReader->getMesh($<string>3);

        InstanceNew* newInstance = NULL;
        bool onlyCreateNewVertices = false;
        if (currentMesh != NULL) {
            //if (currentTransformations2.size() > 0){
              onlyCreateNewVertices = true;
            //}
            newInstance = createInstance(currentMesh, currSession->verts, currReader, true, false, onlyCreateNewVertices, currSession);
            newInstance->currSession = currSession;
        }
        else{
            GroupNew * currentGroup2 = currReader->getGroup($<string>3);
            if (currentGroup2 != NULL) {
                newInstance = createInstance(currentGroup2, currSession->verts, currReader, currSession);
                newInstance->currSession = currSession;
            }
            else{
                nomerror(currSession, "Incorrect vertex, face, or mesh name");
                YYABORT;
            }
        }

        newInstance->setName(strdup($<string>2));
        newInstance->transformations = currentTransformations2;
        currentTransformations2.clear();

        for (TransformationNew * t : newInstance->transformations){
            newInstance->applyTransformation(t);
        }

        string surfaceName = surfaceFromArg;
        // Check if a surface has been applied.
        if (surfaceName.length() != 0){
            Surface * currentSurface = currReader->surf(surfaceFromArg);
            if (currentSurface != NULL) {
                setSurface(newInstance, currentSurface);
            }
            else{
                nomerror(currSession, "Incorrect surface name");
                YYABORT;
            }
        }

        currSession->instances.push_back(newInstance);
        surfaceFromArg = "";
        }
        ;

object:
        OBJECT VARIABLE parenthesisName END_OBJECT
        {
          Reader* currReader = createReader(currSession);

          std::list<FaceNew*> facesObject;
          for (std::vector<string>::iterator it = tempVariables2.begin() ; it != tempVariables2.end(); ++it){
              FaceNew * currentFace = currReader->getFace(*it);
              if (currentFace != NULL) {
                  facesObject.push_back(currentFace);
              }
              else{
                  nomerror(currSession, "Incorrect face name");
                  YYABORT;
              }
          }

          MeshNew* currMesh = createMesh();

          for (std::list<FaceNew*>::iterator it=facesObject.begin(); it != facesObject.end(); ++it){
              currMesh->faces.push_back(*it);
              for (Vert* currVert : (*it)->verts){
                  currMesh->verts.push_back(currVert);
              }
              for (EdgeNew* currEdge : (*it)->edges){
                  currMesh->edges.push_back(currEdge);
              }
          }

          currMesh->setName(strdup($<string>2));
          currSession->meshes.push_back(currMesh);

          tempVariables2.clear();
        }
        ;

surface:
    SURFACE VARIABLE COLOR OPARENTHESES numberValue numberValue numberValue EPARENTHESES END_SURFACE
    {
        double *r = (double*) malloc(sizeof(double));
        double *g = (double*) malloc(sizeof(double));
        double *b = (double*) malloc(sizeof(double));

        double *currentValSet = (double*) malloc(sizeof(double));
        parseGetBankVal($<string>5, currSession, currentValSet, nomlineno);
        *r = *currentValSet;
        parseGetBankVal($<string>6, currSession, currentValSet, nomlineno);
        *g = *currentValSet;
        parseGetBankVal($<string>7, currSession, currentValSet, nomlineno);
        *b = *currentValSet;

        Surface* currSurface = createSurface(r, g, b, strdup($<string>2));

        currSurface->rStr = strdup($<string>5);
        currSurface->gStr = strdup($<string>6);
        currSurface->bStr = strdup($<string>7);
        currSurface->currSession = currSession;

        currSession->surfaces.push_back(currSurface);
        }
        ;

point:
    BEG_POINT VARIABLE OPARENTHESES numberValue numberValue numberValue EPARENTHESES END_POINT
    {
        double *x = (double*) malloc(sizeof(double));
        double *y = (double*) malloc(sizeof(double));
        double *z = (double*) malloc(sizeof(double));

        double *currentValSet = (double*) malloc(sizeof(double));
        parseGetBankVal($<string>4, currSession, currentValSet, nomlineno);
        *x =*currentValSet;
        parseGetBankVal($<string>5, currSession, currentValSet, nomlineno);
        *y =*currentValSet;
        parseGetBankVal($<string>6, currSession, currentValSet, nomlineno);
        *z =*currentValSet;

        Vert * newVertex = createVert (x, y, z);
        newVertex->setName(strdup($<string>2));

        newVertex->currSession = currSession;
        newVertex->xStr = strdup($<string>4);
        newVertex->yStr = strdup($<string>5);
        newVertex->zStr = strdup($<string>6);

        currSession->verts.push_back(newVertex);
        }
        ;
