//
//  TunnelNew.cpp
//  model
//
//  Created by L on 26/08/2017.
//  Copyright © 2017 L. All rights reserved.
//

#include "TunnelNew.h"
#include <math.h>
#include <glm/glm.hpp>
#include "Data.h"

static int tIndex = 0;

///Polyline functions
TunnelNew* createTunnel(double *n, double *ro, double *ratio, double *h)
{
    TunnelNew* t0 = new TunnelNew();
    //This behaviour depends on the parser
    t0->setName("t" + std::to_string(tIndex));
    t0->n = n;
    t0->ro = ro;
    t0->ratio = ratio;
    t0->h = h;

    tIndex++;

    t0->createVertEdgeTunnel();
    return t0;
}

void TunnelNew::createVertEdgeTunnel(){
    verts.clear();
    edges.clear();
    faces.clear();

    std::vector<Vert*> baseCircle;
    std::vector<Vert*> highCircle;
    std::vector<Vert*> lowCircle;

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
        highCircle.push_back(newVertex);
        verts.push_back(newVertex);
    }

    for(int i = 0; i < *n; i++)
    {
        float currAngle = 2.0 * i / *n * M_PI;

        double *x = (double*) malloc(sizeof(double));
        double *y = (double*) malloc(sizeof(double));
        double *z = (double*) malloc(sizeof(double));

        *x = ri * glm::cos(currAngle);
        *y = ri * glm::sin(currAngle);
        *z = -*h;

        Vert * newVertex = createVert (x, y, z);
        lowCircle.push_back(newVertex);
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

        FaceNew * newFace = createFace(verticesFace, &(edges));
        faces.push_back(newFace);
        verticesFace.clear();
    }

    for(int i = 0; i < *n; i++)
    {
        std::list<Vert*> verticesFace;
        verticesFace.push_back(baseCircle[i]);
        if (i == *n - 1){
            verticesFace.push_back(baseCircle[0]);
            verticesFace.push_back(lowCircle[0]);
        }
        else{
            verticesFace.push_back(baseCircle[i + 1]);
            verticesFace.push_back(lowCircle[i + 1]);
        }
        verticesFace.push_back(lowCircle[i]);

        FaceNew * newFace = createFace(verticesFace, &(edges));
        faces.push_back(newFace);
        verticesFace.clear();
    }
}


void TunnelNew::updateTunnel() {
    // Used when the sliders are changing values.
    // Check if we need to create new vertices (if the number of vertices has changed).
    if (*n != verts.size() / 2){
        createVertEdgeTunnel();
    }
    else{
        // Redraw in case the radius has changed.
        int i = 0;
        for (std::list<Vert*>::const_iterator iterator = verts.begin(), end = verts.end(); iterator != end; ++iterator) {
            if (i >= verts.size() / 3 && i < (2 * verts.size()) / 3){
                float currAngle = 2.0 * i / *n * M_PI;
                float ri = *ro * (1 + *ratio);

                double *x = (double*) malloc(sizeof(double));
                double *y = (double*) malloc(sizeof(double));
                double *z = (double*) malloc(sizeof(double));

                *x = ri * glm::cos(currAngle);
                *y = ri * glm::sin(currAngle);
                *z = *h;

                (*iterator)->x = x;
                (*iterator)->y = y;
                (*iterator)->z = z;

            }
            else if (i >= (2 * verts.size()) / 3){
                float currAngle = 2.0 * i / *n * M_PI;

                double *x = (double*) malloc(sizeof(double));
                double *y = (double*) malloc(sizeof(double));
                double *z = (double*) malloc(sizeof(double));

                *x = *ro * glm::cos(currAngle);
                *y = *ro * glm::sin(currAngle);
                *z = 0;

                (*iterator)->x = x;
                (*iterator)->y = y;
                (*iterator)->z = z;
            }
            else{
                float currAngle = 2.0 * i / *n * M_PI;
                float ri = *ro * (1 + *ratio);

                double *x = (double*) malloc(sizeof(double));
                double *y = (double*) malloc(sizeof(double));
                double *z = (double*) malloc(sizeof(double));

                *x = ri * glm::cos(currAngle);
                *y = ri * glm::sin(currAngle);
                *z = -*h;

                (*iterator)->x = x;
                (*iterator)->y = y;
                (*iterator)->z = z;
            }
            i++;
        }
    }

}

