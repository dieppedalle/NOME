//
//  Mesh.cpp
//  model
//
//  Created by L on 26/08/2017.
//  Copyright © 2017 L. All rights reserved.
//

#include "FunnelNew.h"
#include <math.h>
#include <glm/glm.hpp>
#include "Data.h"
#include "Session.h"

static int fIndex = 0;

///Funnel functions
FunnelNew* createFunnel(double *n, double *ro, double *ratio, double *h, Reader* currReader)
{
    FunnelNew* f0 = new FunnelNew();
    //This behaviour depends on the parser
    f0->setName(std::to_string(fIndex));
    f0->n = n;
    f0->ro = ro;
    f0->ratio = ratio;
    f0->h = h;
    f0->reader = currReader;

    fIndex++;

    f0->createVertEdgeFunnel();
    return f0;
}

bool FunnelNew::setName(std::string n)
{
    if(n.find(".") != std::string::npos && n.find(":") != std::string::npos)
        return false;
    name = n;
    bool error = updateNames();
    return error;
}

void FunnelNew::createVertEdgeFunnel(){
    verts.clear();
    edges.clear();
    faces.clear();

    std::vector<Vert*> baseCircle;
    std::vector<Vert*> highCircle;

    for(int i = 0; i < *n; i++)
    {
        float currAngle = 2.0 * i / *n * M_PI;

        double *x = (double*) malloc(sizeof(double));
        double *y = (double*) malloc(sizeof(double));
        double *z = (double*) malloc(sizeof(double));

        *x = *ro * glm::cos(currAngle);
        *y = *ro * glm::sin(currAngle);
        *z = 0;

        Vert * newVertex = createVert (x, y, z);
        newVertex->setName("v1_" + std::to_string(i));
        baseCircle.push_back(newVertex);
        verts.push_back(newVertex);
    }

    float ri = *ro * (1 + *ratio);
    for(int i = 0; i < *n; i++)
    {
        float currAngle = 2.0 * i / *n * M_PI;

        double *x = (double*) malloc(sizeof(double));
        double *y = (double*) malloc(sizeof(double));
        double *z = (double*) malloc(sizeof(double));

        *x = ri * glm::cos(currAngle);
        *y = ri * glm::sin(currAngle);
        *z = *h;

        Vert * newVertex = createVert (x, y, z);
        newVertex->setName("v2_" + std::to_string(i));
        highCircle.push_back(newVertex);
        verts.push_back(newVertex);
    }

    for(int i = 0; i < *n; i++)
    {
        std::list<Vert*> verticesFace;
        verticesFace.push_back(baseCircle[i]);
        if (i == *n - 1){
            verticesFace.push_back(baseCircle[0]);
            verticesFace.push_back(highCircle[0]);
        }
        else{
            verticesFace.push_back(baseCircle[i + 1]);
            verticesFace.push_back(highCircle[i + 1]);

        }
        verticesFace.push_back(highCircle[i]);
        FaceNew * newFace = createFace(verticesFace, &(edges), reader, false);
        newFace->setName("f1_" + std::to_string(i));
        faces.push_back(newFace);
        verticesFace.clear();
    }
}


int FunnelNew::updateFunnel() {
    double *currentValN = (double*) malloc(sizeof(double));
    parseGetBankVal(nStr.c_str(), this->currSession, currentValN, 0);

    double *currentValRo = (double*) malloc(sizeof(double));
    parseGetBankVal(roStr.c_str(), this->currSession, currentValRo, 0);

    double *currentValRatio = (double*) malloc(sizeof(double));
    parseGetBankVal(ratioStr.c_str(), this->currSession, currentValRatio, 0);

    double *currentValH = (double*) malloc(sizeof(double));
    parseGetBankVal(hStr.c_str(), this->currSession, currentValH, 0);

    // Used when the sliders are changing values.
    // Check if we need to create new vertices (if the number of vertices has changed).
    if (*n != *currentValN){
        *n = *currentValN;
        createVertEdgeFunnel();
        return 1;
    }
    else if (*ro != *currentValRo || *ratio != *currentValRatio || *h != *currentValH){
        *ro = *currentValRo;
        *ratio = *currentValRatio;
        *h = *currentValH;
        // Redraw in case the radius has changed.
        int i = 0;
        for (std::list<Vert*>::const_iterator iterator = verts.begin(), end = verts.end(); iterator != end; ++iterator) {
            if (i >= verts.size() / 2){
                float currAngle = 2.0 * i / *n * M_PI;
                float ri = *ro * (1 + *ratio);

                *((*iterator)->x) = ri * glm::cos(currAngle);
                *((*iterator)->y) = ri * glm::sin(currAngle);
                *((*iterator)->z) = *h;

            }
            else{
                float currAngle = 2.0 * i / *n * M_PI;

                *((*iterator)->x) = *ro * glm::cos(currAngle);
                *((*iterator)->y) = *ro * glm::sin(currAngle);
                *((*iterator)->z) = 0;
            }
            i++;
        }
        return 0;
    }

}

