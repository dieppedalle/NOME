//
//  CircleNew.cpp
//  model
//
//  Created by L on 26/08/2017.
//  Copyright © 2017 L. All rights reserved.
//

#include "CircleNew.h"
#include "Session.h"
#include <math.h>
#include <glm/glm.hpp>

static int cIndex = 0;

///Circle functions
CircleNew* createCircle(double *num, double *rad)
{
    CircleNew* c0 = new CircleNew();
    //This behaviour depends on the parser
    c0->setName(std::to_string(cIndex));
    double *numPtr = (double*) malloc(sizeof(double));
    c0->num = numPtr;
    double *radPtr = (double*) malloc(sizeof(double));
    c0->rad = radPtr;

    *c0->num = *num;
    *c0->rad = *rad;

    cIndex++;

    /*c0->createVertEdgeCircle();
    c0-> updateCircle();*/
    return c0;
}

bool CircleNew::setName(std::string n)
{
    if(n.find(".") != std::string::npos && n.find(":") != std::string::npos)
        return false;
    name = "m:cl:" + n;
    bool error = updateNames();
    return error;
}

int CircleNew::updateCircle() {
    double *currentValNum = (double*) malloc(sizeof(double));
    parseGetBankVal(numStr.c_str(), this->currSession, currentValNum);

    double *currentValRad = (double*) malloc(sizeof(double));
    parseGetBankVal(radStr.c_str(), this->currSession, currentValRad);

    // Check if we need to create new vertices (if the number of vertices has changed).
    if (*num != *currentValNum){
        *num = *currentValNum;
        createVertEdgeCircle();
        return 1;
    }
    else if (*rad != *currentValRad){
        *rad = *currentValRad;

        // Redraw in case the radius has changed.
        float i = 0;
        for (Vert* vert : verts) {
            float currAngle = 2.0 * i / *num * M_PI;

            *(vert->x) = *rad * glm::cos(currAngle);
            *(vert->y) = *rad * glm::sin(currAngle);
            *(vert->z) = 0;
            i++;
        }
        return 0;
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
        newVertex->setName("v1_" + std::to_string(i));
        //newVertex->setName(name + "." +  std::to_string(i));
        verts.push_back(newVertex);
    }

    std::list<Vert*>::iterator it = verts.begin();
    std::list<Vert*>::iterator it2 = verts.begin();
    EdgeNew *currentEdge;
    ++it2;
    while (it != verts.end()){
        if (it2 != verts.end()){
            currentEdge = createEdge(*it, *it2, false);
            it2++;
        }
        else{
            currentEdge = createEdge(verts.back(), verts.front(), false);
        }
        it++;
        edges.push_back(currentEdge);
    }
}
