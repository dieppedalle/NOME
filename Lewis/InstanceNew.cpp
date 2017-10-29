//
//  Instance.cpp
//  model
//
//  Created by L on 21/09/2017.
//  Copyright © 2017 L. All rights reserved.
//
#include <stdio.h>
#include <string.h>
#include <glm/glm.hpp>
#include "Data.h"
#include "InstanceNew.h"


bool setSurface(InstanceNew* i0, Surface* surface){
    i0->surface = surface;
    return true;
}


InstanceNew* createInstance(InstanceNew* i0)
{
    return new InstanceNew();
}

InstanceNew* createInstance(MeshNew* m0, std::list<Vert*> vertsDef)
{
   InstanceNew* i0 = new InstanceNew();
   i0->mesh = m0;
   i0->verts = {};
   for (Vert* v0 : m0->verts){
       if (std::find(vertsDef.begin(), vertsDef.end(), v0) != vertsDef.end()){
           Vert* newVertex = createVert(v0);
           newVertex->name = v0->name;
           i0->verts.push_back(newVertex);
       }
       else{
           i0->verts.push_back(v0);
       }
   }

   for (EdgeNew* e0 : m0->edges){
       Vert* firstVert = NULL;
       Vert* secondVert = NULL;


       for (Vert* v0 : i0->verts){
           if(v0->index == e0->v0->index)
               firstVert = v0;
       }
       if (!firstVert){
           for (Vert* v0 : i0->verts){
               if(v0->name.compare(e0->v0->name) == 0){
                   firstVert = v0;
               }
           }
       }

       for (Vert* v1 : i0->verts){
           if(v1->index == e0->v1->index)
               secondVert = v1;
       }

       if (!secondVert){
           for (Vert* v1 : i0->verts){
               if(v1->name.compare(e0->v1->name) == 0){
                   secondVert = v1;
               }
           }
       }



       /*for (Vert* v0 : i0->verts){
           if(v0->name.compare(e0->v0->name) == 0)
               firstVert = v0;
       }

       for (Vert* v1 : i0->verts){
           if(v1->name.compare(e0->v1->name) == 0)
               secondVert = v1;
       }*/

       EdgeNew* newEdge = createEdge(firstVert, secondVert, 1.0);
       i0->edges.push_back(newEdge);

   }


   for (FaceNew* f0 : m0->faces){
       std::list<EdgeNew*> edgesFace;
       std::list<Vert*> vertFace;
       for (EdgeNew* e0 : f0->edges){
           Vert* firstVert = NULL;

           for (Vert* v0 : i0->verts){
               if(v0->index == e0->v0->index)
                   firstVert = v0;
           }
           if (!firstVert){
               for (Vert* v0 : i0->verts){
                   if(v0->name.compare(e0->v0->name) == 0){
                       firstVert = v0;
                   }
               }
           }

           /*for (Vert* v0 : i0->verts){
               if(v0->name.compare(e0->v0->name) == 0)
                   firstVert = v0;
           }*/

           vertFace.push_back(firstVert);
       }

       FaceNew* newFace = createFace(vertFace, &(i0->edges));
       setName(newFace, f0->name);
       setSurface(newFace, f0->surface);

       i0->faces.push_back(newFace);
   }
   return i0;
}

bool InstanceNew::setName(std::string n)
{
    if(n.find(".") != std::string::npos && n.find(":") != std::string::npos)
        return false;
    name = "i:" + n;
    return updateNames();
}

bool InstanceNew::updateNames()
{
    mesh->setPrefix(getFullName());
    return true;
}

bool InstanceNew::draw()
{
    //std::cout << name << std::endl;
    for(auto v : verts) {
      /*std::cout << v->name << std::endl;
      std::cout << *(v->x) << std::endl;
      std::cout << *(v->y) << std::endl;
      std::cout << *(v->z) << std::endl;*/
      drawVert(v, surface);
    }
    for(auto e : edges) {
      drawEdge(e, surface);
    }
    for(auto f : faces) {
      drawFace(f, surface);
    }

    return true;
}


Node* InstanceNew::vert(std::string name)
{
    std::string str = findSubstring(name, 'v', ".");
    if(str.compare("") == 0)
        return NULL;
    std::string id = str.substr(3);
    for(Vert* v0 : verts)
    {
        if(v0->name.compare(id) == 0)
            return v0;
    }
    return NULL;
}

Node* InstanceNew::edge(std::string name)
{
    std::string str = findSubstring(name, 'e', ".");
    if(str.compare("") == 0)
        return NULL;
    std::string id = str.substr(3);
    for(EdgeNew* e0 : edges)
    {
        if(e0->name.compare(id) == 0)
            return e0;
    }
    return NULL;
}

Node* InstanceNew::face(std::string name)
{
    std::string str = findSubstring(name, 'f', ".");
    if(str.compare("") == 0)
        return NULL;
    std::string id = str.substr(3);
    for(FaceNew* f0 : faces)
    {
        if(f0->name.compare(id) == 0)
            return f0;
    }
    return NULL;
}

Node* InstanceNew::vert(int i)
{
    for(Vert* v0 : verts)
    {
        if(v0->index == i)
            return v0;
    }
    return NULL;
}

Node* InstanceNew::edge(int i)
{
    for(EdgeNew* e0 : edges)
    {
        if(e0->index == i)
            return e0;
    }
    return NULL;
}

Node* InstanceNew::face(int i)
{
    for(FaceNew* f0 : faces)
    {
        if(f0->index == i)
            return f0;
    }
    return NULL;
}

void InstanceNew::updateVerts(){
    for (Vert* v0 : verts){
        double *x = (double*) malloc(sizeof(double));
        double *y = (double*) malloc(sizeof(double));
        double *z = (double*) malloc(sizeof(double));

        *x = *(v0->x);
        *y = *(v0->y);
        *z = *(v0->z);

        v0->xTransformed = x;
        v0->yTransformed = y;
        v0->zTransformed = z;
    }
}

void InstanceNew::applyTransformation(TransformationNew* t){
    if (dynamic_cast<Rotate*>(t)){
        Rotate* rotate = dynamic_cast<Rotate*>(t);
        for (Vert* v0 : verts){
            double *x = (double*) malloc(sizeof(double));
            double *y = (double*) malloc(sizeof(double));
            double *z = (double*) malloc(sizeof(double));

            // Rotation around an axis
            // http://ksuweb.kennesaw.edu/~plaval//math4490/rotgen.pdf
            double radAngle = *rotate->angle * (3.141592f/180.0f);
            double t = 1 - glm::cos(radAngle);
            double S = glm::sin(radAngle);
            double C = glm::cos(radAngle);

            double x1 = t * pow(*rotate->x, 2) + C;
            double x2 = t * *rotate->x * *rotate->y - S * *rotate->z;
            double x3 = t * *rotate->x * *rotate->z + S * *rotate->y;
            double y1 = t * *rotate->x * *rotate->y + S * *rotate->z;
            double y2 = t * pow(*rotate->y, 2) + C;
            double y3 = t * *rotate->y * *rotate->z - S * *rotate->x;
            double z1 = t * *rotate->x * *rotate->z - S * *rotate->y;
            double z2 = t * *rotate->y * *rotate->z + S * *rotate->x;
            double z3 = t * pow(*rotate->z, 2) + C;

            // Matrix multiplication
            // https://i.ytimg.com/vi/r-WlZLV0E0s/hqdefault.jpg
            double ax = *v0->x * x1 + *v0->y * x2 + *v0->z * x3;
            double ay = *v0->x * y1 + *v0->y * y2 + *v0->z * y3;
            double az = *v0->x * z1 + *v0->y * z2 + *v0->z * z3;

            *x = ax;
            *y = ay;
            *z = az;
            v0->xTransformed = x;
            v0->yTransformed = y;
            v0->zTransformed = z;
        }
    }
    else if (dynamic_cast<Scale*>(t)){
        Scale* scale = dynamic_cast<Scale*>(t);
        for (Vert* v0 : verts){
            double *x = (double*) malloc(sizeof(double));
            double *y = (double*) malloc(sizeof(double));
            double *z = (double*) malloc(sizeof(double));

            *x = *v0->x * *scale->x;
            *y = *v0->y * *scale->y;
            *z = *v0->z * *scale->z;
            v0->xTransformed = x;
            v0->yTransformed = y;
            v0->zTransformed = z;
        }
    }
    else if (dynamic_cast<Translate*>(t)){

        Translate* translate = dynamic_cast<Translate*>(t);
        for (Vert* v0 : verts){
            double *x = (double*) malloc(sizeof(double));
            double *y = (double*) malloc(sizeof(double));
            double *z = (double*) malloc(sizeof(double));

            *x = *v0->x + *translate->x;
            *y = *v0->y + *translate->y;
            *z = *v0->z + *translate->z;
            v0->xTransformed = x;
            v0->yTransformed = y;
            v0->zTransformed = z;

        }

    }
}

void InstanceNew::undoTransformation(TransformationNew* t){
    if (dynamic_cast<Rotate*>(t)){
        Rotate* rotate = dynamic_cast<Rotate*>(t);
        for (Vert* v0 : verts){
            double *x = (double*) malloc(sizeof(double));
            double *y = (double*) malloc(sizeof(double));
            double *z = (double*) malloc(sizeof(double));

            // Rotation around an axis
            // http://ksuweb.kennesaw.edu/~plaval//math4490/rotgen.pdf
            double radAngle = -*rotate->angle * (3.141592f/180.0f);
            double t = 1 - glm::cos(radAngle);
            double S = glm::sin(radAngle);
            double C = glm::cos(radAngle);

            double x1 = t * pow(*rotate->x, 2) + C;
            double x2 = t * *rotate->x * *rotate->y - S * *rotate->z;
            double x3 = t * *rotate->x * *rotate->z + S * *rotate->y;
            double y1 = t * *rotate->x * *rotate->y + S * *rotate->z;
            double y2 = t * pow(*rotate->y, 2) + C;
            double y3 = t * *rotate->y * *rotate->z - S * *rotate->x;
            double z1 = t * *rotate->x * *rotate->z - S * *rotate->y;
            double z2 = t * *rotate->y * *rotate->z + S * *rotate->x;
            double z3 = t * pow(*rotate->z, 2) + C;

            // Matrix multiplication
            // https://i.ytimg.com/vi/r-WlZLV0E0s/hqdefault.jpg
            double ax = *v0->x * x1 + *v0->y * x2 + *v0->z * x3;
            double ay = *v0->x * y1 + *v0->y * y2 + *v0->z * y3;
            double az = *v0->x * z1 + *v0->y * z2 + *v0->z * z3;

            *x = ax;
            *y = ay;
            *z = az;
            v0->x = x;
            v0->y = y;
            v0->z = z;
        }
    }
    else if (dynamic_cast<Scale*>(t)){
        Scale* scale = dynamic_cast<Scale*>(t);
        for (Vert* v0 : verts){
            double *x = (double*) malloc(sizeof(double));
            double *y = (double*) malloc(sizeof(double));
            double *z = (double*) malloc(sizeof(double));

            *x = *v0->x * (1.0 / *scale->x);
            *y = *v0->y * (1.0 / *scale->y);
            *z = *v0->z * (1.0 / *scale->z);
            v0->x = x;
            v0->y = y;
            v0->z = z;
        }
    }
    else if (dynamic_cast<Translate*>(t)){

        Translate* translate = dynamic_cast<Translate*>(t);
        for (Vert* v0 : verts){
            double *x = (double*) malloc(sizeof(double));
            double *y = (double*) malloc(sizeof(double));
            double *z = (double*) malloc(sizeof(double));

            *x = *v0->x - *translate->x;
            *y = *v0->y - *translate->y;
            *z = *v0->z - *translate->z;
            v0->x = x;
            v0->y = y;
            v0->z = z;

        }

    }
}
