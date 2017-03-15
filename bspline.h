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
class BSpline : PolyLine {
public:
    vector<Vertex*> proxy;
    BSpline();
    int mode;
    int segments;

    //setters
    void set_mode(int);
    void set_segments(int);

    void set_proxy(Vertex*);


    //getters
    int get_mode();
    int get_segments();

    //constructs a cubic bspline
    void cubic();
};

#endif // __BSPLINE_H__
