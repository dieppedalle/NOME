//
//  BezierCurveNew.h
//

#ifndef BezierCurveNew_h
#define BezierCurveNew_h

#include <stdio.h>
#include <set>
#include "Data.h"
#include "MeshNew.h"

///Mesh class, formed by faces, primarily quad faces, valence four vertices
typedef class BezierCurveNew : public MeshNew
{
public:
    std::vector<Vert*> proxy;
    double* segments;
    //double prevSegment;
    Session* currSession;
    std::string segmentsStr;

    bool setName(std::string n);

    bool calculate(bool);
    void updateBezierCurve();
    Vert* interpolatePoint(double t, Vert* pt1, Vert* pt2);
    void calculateBezierVertex(std::vector<Vert*> temp1, double t, bool createNewVertices, int numVertexCreated);
} BezierCurveNew;

///Instance functions
BezierCurveNew* createBezierCurveNew();
BezierCurveNew* createBezierCurveNew(BezierCurveNew*);

#endif /* BezierCurveNew_h */
