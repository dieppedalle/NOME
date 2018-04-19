//
//  Session.h
//

#ifndef Session_h
#define Session_h

#include <stdio.h>
#include <fstream>
#include "Data.h"
#include "MeshNew.h"
#include "GroupNew.h"
#include "ObjectNew.h"
#include "BankNew.h"
#include "PolylineNew.h"
#include "SweepNew.h"
#include "BSplineNew.h"
#include "BezierCurveNew.h"
#include "CircleNew.h"
#include "FunnelNew.h"
#include "TunnelNew.h"
#include "SubdivisionNew.h"
#include "OffsetNew.h"
#include "Octree.h"
#include "OctreeProxy.h"

class Session
{
public:
    std::list<Vert*> verts;
    std::list<EdgeNew*> edges;
    std::list<FaceNew*> faces;
    std::list<MeshNew*> meshes;
    std::list<Surface*> surfaces;
    std::list<GroupNew*> groups;
    std::list<InstanceNew*> instances;
    std::list<PolylineNew*> polylines;
    std::list<SweepNew*> sweeps;
    std::list<BSplineNew*> bsplines;
    std::list<BezierCurveNew*> bezierCurves;
    std::list<CircleNew*> circles;
    std::list<FunnelNew*> funnels;
    std::list<TunnelNew*> tunnels;
    std::list<BankNew*> banks;
    std::list<SubdivisionNew*> subdivisions;
    std::list<OffsetNew*> offsets;
    std::string name;
    std::string fileContent;
    std::vector<std::tuple<std::vector<Vert*>, std::vector<EdgeNew*>>> borders = std::vector<std::tuple<std::vector<Vert*>, std::vector<EdgeNew*>>>();
    std::tuple<std::vector<Vert*>, std::vector<EdgeNew*>> tmpBorder;
    bool isBorderSelected = false;

    int subdivisionType = 0;
    int offsetType = 0;

    bool recalculateOffset = true;
    bool recalculateSubdivision = true;
    bool recalculateSlider = true;

    int subdivisionLevel = 0;
    MeshNew* flattenMesh;
    std::vector<MeshNew*> flattenMeshList = std::vector<MeshNew*>();

    int tmpFaceIndex = 0;
    int tmpPolylineIndex = 0;

    std::list<EdgeNew*> selectedEdges;
    std::list<Vert*> selectedVerts;

    std::list<FaceNew*> selectedFaces;
    MeshNew* tmpMesh = nullptr;
    PolylineNew* tmpPolyline = nullptr;
    InstanceNew* tmpInstance = nullptr;

    bool normalVectShow = true;

    Surface* foreColor;
    Surface* backColor;
    Surface* outsideColor;
    Surface* insideColor;
    Surface* offsetColor;

    Session();
    ~Session();

    //Naming functions
    bool setName(std::string n);
    std::string getName();
    bool updateNames();
    void groupFaces(std::string consolidateInstanceName, std::string consolidateMeshName);
    void addTmpFace();
    void deleteTmpFace();
    void addTmpPolyline();
    void selectVert(GLint hits, GLuint *names, GLdouble posX, GLdouble posY, GLdouble posZ);
    void selectFace(GLint hits, GLuint *names, GLdouble posX, GLdouble posY, GLdouble posZ);
    void selectEdge(GLint hits, GLuint *names, GLdouble posX, GLdouble posY, GLdouble posZ);
    void selectBorder(GLint hits, GLuint *names, GLdouble posX, GLdouble posY, GLdouble posZ);
    void SaveSessionNom(std::string outputFile);
    void SaveSessionStl(std::string outputFile);
    void consolidateTmpMesh(std::string consolidateInstanceName, std::string consolidateMeshName);
    void clearSelection();
    void saveFileToStr(std::string fileName);
    void deleteFace();
    void draw();
    void drawSubdivide(int subdivision, int previousSubdivisionLevel, double offset, bool calculateOffset, bool calculateSubdivide, bool calculateSlider);
    void createFlattenMesh(bool instance);
    std::vector<Vert*> findLoop(Vert* startVert, std::vector<Vert*> selectedVertsLoop);
    std::tuple<std::vector<Vert*>, std::vector<EdgeNew*>> findBorder(Vert* startVert);
    std::tuple<std::vector<Vert*>, std::vector<EdgeNew*>> findBorderRec(Vert* startVert, std::vector<Vert*> borderVerts, std::vector<EdgeNew*> seenEdges);
    void zipBorders();

    OctantNew* getOctreeRoot() const { return OctreeRoot; }

    static Session& getSingleton();

private:
    int accesses;

    OctantNew* OctreeRoot;
};

//Instantiation
Session* createSession();
Session* createSession(Session*);
void saveFaceSTL(FaceNew* currFace, std::ofstream& file);
void parseGetBankVal(const char* input, Session* sessionParse, double* output, int lineNumber);

#endif /* Session_h */
