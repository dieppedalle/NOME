//
//  BezierCurveNew.cpp
//  model
//
//  Created by L on 26/08/2017.
//  Copyright © 2017 L. All rights reserved.
//

#include "BezierCurveNew.h"
#include "Data.h"
#include <glm/glm.hpp>
#include "Session.h"

Vert* BezierCurveNew::interpolatePoint(double t, Vert* pt1, Vert* pt2){
    double *x = (double*) malloc(sizeof(double));
    double *y = (double*) malloc(sizeof(double));
    double *z = (double*) malloc(sizeof(double));

    *x = *pt1->xTransformed * (1 - t) + *pt2->xTransformed * t;
    *y = *pt1->yTransformed * (1 - t) + *pt2->yTransformed * t;
    *z = *pt1->zTransformed * (1 - t) + *pt2->zTransformed * t;

    Vert * newVert = createVert(x, y, z);

    return newVert;
}

void BezierCurveNew::calculateBezierVertex(std::vector<Vert*> interpolatedPoints, double t, bool createNewVertices, int numVertexCreated){
    // Use De Casteljau's algorithm.
    if (interpolatedPoints.size() == 1){
        if (createNewVertices){
            verts.push_back(interpolatedPoints.at(0));
            std::list<Vert*>::iterator it = verts.begin();
            std::advance(it, numVertexCreated);
            (*it)->setName("v" + std::to_string(numVertexCreated));
        } else{
            std::list<Vert*>::iterator it = verts.begin();
            std::advance(it, numVertexCreated);
            *((*it)->x) = *(interpolatedPoints.at(0)->x);
            *((*it)->y) = *(interpolatedPoints.at(0)->y);
            *((*it)->z) = *(interpolatedPoints.at(0)->z);
        }
    }
    else{
        std::vector<Vert*> newInterpolatedPoints;

        for(int i = 0; i < interpolatedPoints.size()-1; i++){
            newInterpolatedPoints.push_back(this->interpolatePoint(t, interpolatedPoints.at(i), interpolatedPoints.at(i+1)));
        }
        this->calculateBezierVertex(newInterpolatedPoints, t, createNewVertices, numVertexCreated);
    }
}

void BezierCurveNew::updateBezierCurve(){
    double *currentValSet = (double*) malloc(sizeof(double));
    parseGetBankVal(segmentsStr.c_str(), this->currSession, currentValSet, 0);
    if (*currentValSet != *segments){
        *segments = *currentValSet;
        verts.clear();
        edges.clear();
        calculate(true);

        std::list<Vert*>::iterator it = verts.begin();
        std::list<Vert*>::iterator it2 = verts.begin();
        EdgeNew *currentEdge;
        ++it2;
        while (it != verts.end()){
            if (it2 != verts.end()){
                currentEdge = createEdge(*it, *it2, false);
                edges.push_back(currentEdge);
                it2++;
            }
            it++;
        }
    }
    else{
        calculate(false);
    }
}

bool BezierCurveNew::calculate(bool createNewVertices){
    int numVertexCreated = 0;
    double t = 0;
    for (int i = 0; i <= *segments; i += 1){
        std::vector<Vert*> controlPointsTmp = proxy;
        calculateBezierVertex(controlPointsTmp, t, createNewVertices, numVertexCreated);
        numVertexCreated += 1;
        t += 1 / *segments;
    }

    return true;
}

static int bIndex = 0;

///BSpline functions
BezierCurveNew* createBezierCurveNew()
{
    BezierCurveNew* b0 = new BezierCurveNew();
    //This behaviour depends on the parser
    b0->setName("beziercurve" + std::to_string(bIndex));
    bIndex++;
    //b0->prevSegment = -1;

    return b0;
}

bool BezierCurveNew::setName(std::string n)
{
    if(n.find(".") != std::string::npos && n.find(":") != std::string::npos)
        return false;
    name = "m:bc:" + n;
    bool error = updateNames();
    return error;
}
