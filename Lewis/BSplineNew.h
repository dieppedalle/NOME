//
//  BSplineNew.h
//

#ifndef BSplineNew_h
#define BSplineNew_h

#include <stdio.h>
#include <set>
#include "Data.h"
#include "MeshNew.h"

///Mesh class, formed by faces, primarily quad faces, valence four vertices
typedef class BSplineNew : public MeshNew
{
public:
    std::vector<Vert*> proxy;
    std::vector<std::string> proxyStr;
    double segments;
    std::string segmentsStr;

    Session* currSession;
    //double prevSegment;
    int order;
    bool isLoop;

    bool setName(std::string n);

    void set_segments(double);
    void set_proxy(Vert*);
    void set_order(int);

    bool updateBSpline();

    //getters
    //double get_segments();
    //int get_order();

    //calculate
    float basis(int, int, float);
    void calculate(int, bool);
} BSplineNew;

///Instance functions
BSplineNew* createBSplineNew();
BSplineNew* createBSplineNew(BSplineNew*);

#endif /* BSplineNew_h */
