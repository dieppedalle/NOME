/**
 * UC Berkeley, NOME project.
 * Advised by Prof. Sequin H. Carlos.
 */

#ifndef __BSPLINE_H__
#define __BSPLINE_H__
;
#include <vector>
#include <glm/glm.hpp>
#include "mesh.h"
#include "transformation.h"
#include "polyline.h"
using namespace std;
using namespace glm;

class Group;
//////////////////////////////////////////////////////////////////////
// B-Spline Class -- B-Spline is list of vertices, subclass of PolyLine
class BSpline : public PolyLine {
public:
    vector<Vertex*> proxy;
    BSpline();

    string segments_expr;

    int segments;
    int order;

    //setters
    void set_segments(int);
    void set_proxy(Vertex*);
    void set_order(int);

    void updateBSpline();

    //getters
    int get_segments();
    int get_order();

    //calculate
    float basis(int, int, float);
    void calculate(int);

    //constructs a cubic bspline
    void cubic();
};

#endif // __BSPLINE_H__
