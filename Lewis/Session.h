//
//  Session.h
//

#ifndef Session_h
#define Session_h

#include <stdio.h>
#include "Data.h"
#include "MeshNew.h"
#include "GroupNew.h"
#include "ObjectNew.h"
#include "BankNew.h"
#include "PolylineNew.h"
#include "CircleNew.h"
#include "FunnelNew.h"
#include "TunnelNew.h"
#include "SubdivisionNew.h"
#include "OffsetNew.h"

typedef struct Session
{
private:
    int accesses;

public:
    std::list<Vert*> verts;
    std::list<EdgeNew*> edges;
    std::list<FaceNew*> faces;
    std::list<MeshNew*> meshes;
    std::list<Surface*> surfaces;
    std::list<GroupNew*> groups;
    std::list<InstanceNew*> instances;
    std::list<PolylineNew*> polylines;
    std::list<CircleNew*> circles;
    std::list<FunnelNew*> funnels;
    std::list<TunnelNew*> tunnels;
    std::list<BankNew*> banks;
    std::list<SubdivisionNew*> subdivisions;
    std::list<OffsetNew*> offsets;
    std::string name;
    std::string fileContent;

    int subdivisionLevel = 0;
    MeshNew* flattenMesh;

    int tmpFaceIndex = 0;

    std::list<Vert*> selectedVerts;
    std::list<FaceNew*> selectedFaces;
    MeshNew* tmpMesh;
    PolylineNew* tmpPolyline;
    InstanceNew* tmpInstance;

    //Naming functions
    bool setName(std::string n);
    std::string getName();
    bool updateNames();
    void addTmpFace();
    void addTmpPolyline();
    void selectVert(GLint hits, GLuint *names, GLdouble posX, GLdouble posY, GLdouble posZ);
    void selectFace(GLint hits, GLuint *names, GLdouble posX, GLdouble posY, GLdouble posZ);
    void selectEdge(GLint hits, GLuint *names, GLdouble posX, GLdouble posY, GLdouble posZ);
    void SaveSessionNom(std::string outputFile);
    void SaveSessionStl(std::string outputFile);
    void consolidateTmpMesh(std::string consolidateInstanceName, std::string consolidateMeshName);
    void clearSelection();
    void saveFileToStr(std::string fileName);
    void deleteFace();
    void draw();
    void drawSubdivide(int subdivision, int previousSubdivisionLevel);
    void createFlattenMesh(bool instance);
private:
    QPushButton * consolidateButton;

} Session;

//Instantiation
Session* createSession();
Session* createSession(Session*);


#endif /* Session_h */
