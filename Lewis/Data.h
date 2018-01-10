//
//  Data.h
//

#ifndef Data_h
#define Data_h

#include <stdio.h>
#include <list>
#include <vector>
#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <QColor>
#include <QtOpenGL>
#include <set>
#include <unordered_set>

#include "IO.h"
#include "Node.h"
class Reader;

///Baseline data structure class, every point is defined by a vertex, joined by edges. Edges are joined up to form faces.

///Indices for data structures
typedef int VertI;
typedef int EdgeI;
typedef int FaceI;

class Vert;
class EdgeNew;
class FaceNew;

typedef class Surface
{
public:
    double *r;
    double *g;
    double *b;
    QColor color;
    std::string name;
    QColor getColor();
} Surface;

Surface* createSurface(double *r, double *g, double *b, std::string name);

///Vertex - Usual definition of a vertex in 3d space
typedef class Vert : public Node
{
public:
    double *x;
    double *y;
    double *z;
    double *xTransformed;
    double *yTransformed;
    double *zTransformed;
    double weight;
    bool selected;
    VertI index;
    std::list<EdgeNew*> edges;
    std::list<FaceNew*> faces;
    std::vector<double> normal;

    // Used for subdivision
    Vert* vertPoint;
    void calculateVertPoint();
    Vert* normalInVert;
    Vert* normalOutVert;
    void updateOutOffsetVertex(double offset);
    void updateInOffsetVertex(double offset);
} Vert;

///Edge - normal edge construct as defined in 3d space, must have at least two links
typedef class EdgeNew : public Node
{
public:
    bool isBorder;
    double interval;
    Vert* v0; Vert* v1;
    int faceCount;
    int vertCount;
    FaceNew* f0; FaceNew* f1;
    EdgeI index;

    // Used for subdivision
    Vert* edgePoint;
    
    void calculateEdgePoint();
    bool isMobiusEdge();
} EdgeNew;


///Face - normal face construct in 3d space, must consist of at least 3 edges that form a cycle
typedef class FaceNew : public Node
{
public:
    std::list<EdgeNew*> edges;
    std::list<Vert*> verts;
    FaceI index;
    Surface* surface;
    bool selected;
    // Used for subdivision
    Vert* facePoint;

    void calculateFacePoint();

    std::vector<double> getNormal();
} FaceNew;

std::vector<double> getNormalFromVerts(std::vector<Vert*> vert1);
std::vector<double> getNormalFromVertsForOffset(std::vector<Vert*> vert1, MeshNew* mesh)
double getAngleFromVerts(std::vector<Vert*> vert1);

///Vert Instantiation
Vert* createVert();
Vert* createVert(Vert*);
Vert* createVert(double *x, double *y, double *z);
Vert* createVert(double *x, double *y, double *z, double w);

///Edge Instantiation
EdgeNew* createEdge(EdgeNew*);
EdgeNew* createEdge(Vert* v0, Vert* v1, bool connect);
EdgeNew* createEdge(Vert* v0, Vert* v1, double interval, bool connect);
EdgeNew* createEdge(double x0, double y0, double z0, double x1, double y1, double z1, double interval);

///Face Instantiation
FaceNew* createFace();
FaceNew* createFace(FaceNew*);
FaceNew* createFace(std::list<EdgeNew*> edges, std::list<Vert*> verts);
FaceNew* createFace(std::list<Vert*> vertices, std::list<EdgeNew*> *edges, Reader * currReader, bool connect);
FaceNew* createOffsetFace(std::list<Vert*> verts);


///Naming functions
bool setName(Vert* v0, std::string n);
bool setName(EdgeNew* e0, std::string n);
bool setName(FaceNew* f0, std::string n);

bool setSurface(FaceNew* f0, Surface* surface);
bool setTmpSurface(FaceNew* f0);

///Deletion helper functions, unlink from other data structures
bool deleteVert(Vert* vert);
bool deleteEdge(EdgeNew* edge);
bool deleteFace(FaceNew* face);

bool drawVert(Vert* v0, Surface * instSurface);
bool drawEdge(EdgeNew* e0, Surface * instSurface);
bool drawFace(FaceNew* f0, Surface * instSurface);

#endif /* Data_h */
