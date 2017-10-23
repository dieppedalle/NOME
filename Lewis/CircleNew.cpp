//
//  Mesh.cpp
//  model
//
//  Created by L on 26/08/2017.
//  Copyright © 2017 L. All rights reserved.
//

#include "CircleNew.h"
#include <math.h>
#include <glm/glm.hpp>

static int cIndex = 0;

///Polyline functions
CircleNew* createCircle(double *num, double *rad)
{
    CircleNew* c0 = new CircleNew();
    //This behaviour depends on the parser
    c0->setName("circle" + std::to_string(cIndex));
    c0->num = num;
    c0->rad = rad;

    cIndex++;

    c0->createVertEdgeCircle();
    c0-> updateCircle();
    return c0;
}

void CircleNew::updateCircle() {
    // Check if we need to create new vertices (if the number of vertices has changed).
    if (*num != verts.size()){
        createVertEdgeCircle();
    }
    else{
        // Redraw in case the radius has changed.
        int i = 0;
        for (std::list<Vert*>::const_iterator iterator = verts.begin(), end = verts.end(); iterator != end; ++iterator) {
            float currAngle = 2.0 * i / *num * M_PI;

            double *x = (double*) malloc(sizeof(double));
            double *y = (double*) malloc(sizeof(double));
            double *z = (double*) malloc(sizeof(double));

            *x = *rad * glm::cos(currAngle);
            *y = *rad * glm::sin(currAngle);
            *z = 0;

            (*iterator)->x = x;
            (*iterator)->y = y;
            (*iterator)->z = z;
            i++;
        }
    }

}

void CircleNew::createVertEdgeCircle(){
    verts.clear();
    edges.clear();
    for(int i = 0; i < *num; i++)
    {
        float currAngle = 2.0 * i / *num * M_PI;

        double *x = (double*) malloc(sizeof(double));
        double *y = (double*) malloc(sizeof(double));
        double *z = (double*) malloc(sizeof(double));

        *x = *rad * glm::cos(currAngle);
        *y = *rad * glm::sin(currAngle);
        *z = 0;

        Vert * newVertex = createVert (x, y, z);
        newVertex->setName(name + "." +  std::to_string(i));
        verts.push_back(newVertex);
    }

    std::list<Vert*>::iterator it = verts.begin();
    std::list<Vert*>::iterator it2 = verts.begin();
    EdgeNew *currentEdge;
    ++it2;
    while (it != verts.end()){
        if (it2 != verts.end()){
            currentEdge = createEdge(*it, *it2);
            it2++;
        }
        else{
            currentEdge = createEdge(verts.back(), verts.front());
        }
        it++;
        edges.push_back(currentEdge);
    }


}
