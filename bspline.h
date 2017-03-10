/**
 * UC Berkeley, NOME project.
 * Advised by Prof. Sequin H. Carlos.
 */

#ifndef __POLYLINE_H__
#define __POLYLINE_H__
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
class BSpline : PolyLine {
public:
    vector<Vertex*> proxy;

    //Bspline constructor: pass in a polyline, the order of the desired bspline, and mode, where mode = 0 is an open curve, mode = 1 a closed curve
    BSpline(PolyLine p, int order, int segments);

    //constructs a cubic bspline
    void BSpline::cubic(int mode, int segments);
};

#endif // __BSPLINE_H__
