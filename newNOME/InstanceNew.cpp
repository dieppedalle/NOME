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
#include "FunnelNew.h"
#include "TunnelNew.h"
#include "CircleNew.h"
#include "GroupNew.h"
#include "Reader.h"

class Reader;
bool setSurface(InstanceNew* i0, Surface* surface){
    i0->surface = surface;
    return true;
}


InstanceNew* createInstance(InstanceNew* i0)
{
    return new InstanceNew();
}

InstanceNew* createInstance(GroupNew* g0, std::list<Vert*> vertsDef, Reader* currReader, Session* currSession)
{
   InstanceNew* i0 = new InstanceNew();
   i0->group = g0;

   std::list<InstanceNew*> listInstances;
   for (InstanceNew* instanceNest : g0->instances){
       MeshNew* currentMesh = instanceNest->mesh;
       std::string currentName = instanceNest->name;
       std::list<TransformationNew*> currentTransformations = instanceNest->transformations;

       if (currentMesh != NULL){
           InstanceNew* newInstance;
           newInstance = createInstance(currentMesh, vertsDef, currReader, true, false, false, currSession);
           currentName = currentName.substr(currentName.find(":") + 1);
           newInstance->setName(currentName);
           newInstance->transformations = currentTransformations;
           i0->listInstances.push_back(newInstance);
       }
   }

   return i0;
}

InstanceNew* createInstance(MeshNew* m0, std::list<Vert*> vertsDef, Reader* currReader, bool connect, bool doNotCreateVertices, bool onlyCreateNewVertices, Session* currSession)
{
   InstanceNew* i0 = new InstanceNew();
   i0->mesh = m0;
   i0->verts = {};
   i0->currSession = currSession;

   // Copy all the vertices from the mesh to the instance.
   for (Vert* v0 : m0->verts){
       //GAUTHIER ADDED THAT ON 1/29
       //std::cout << currReader->getVert(v0->index) << std::endl;
       //std::cout << (std::find(vertsDef.begin(), vertsDef.end(), v0) != vertsDef.end()) << std::endl;
       //std::cout << dynamic_cast<FunnelNew*>(m0) << std::endl;
       //std::cout << doNotCreateVertices << std::endl;
       //std::cout << dynamic_cast<TunnelNew*>(m0) << std::endl;
       //std::cout << (((std::find(vertsDef.begin(), vertsDef.end(), v0) != vertsDef.end() || dynamic_cast<FunnelNew*>(m0) || dynamic_cast<TunnelNew*>(m0) || dynamic_cast<CircleNew*>(m0)  || dynamic_cast<BezierCurveNew*>(m0)  || dynamic_cast<BSplineNew*>(m0)) || doNotCreateVertices == false)) << std::endl;
       if (onlyCreateNewVertices == true){
           Vert* newVertex = createVert(v0);
           newVertex->name = v0->name;
           // MAYBE CHECK TRANSFORMATIONS.
           newVertex->transformations = currReader->getVertTransformations(v0->index);
           newVertex->copyOfVert = v0;
           setSurface(newVertex, m0->surface);
           i0->verts.push_back(newVertex);
       }
       else if (((std::find(vertsDef.begin(), vertsDef.end(), v0) != vertsDef.end() || dynamic_cast<FunnelNew*>(m0) || dynamic_cast<TunnelNew*>(m0) || dynamic_cast<CircleNew*>(m0)  || dynamic_cast<BezierCurveNew*>(m0)  || dynamic_cast<BSplineNew*>(m0)) && doNotCreateVertices == false)){
           Vert* newVertex = createVert(v0);
           newVertex->name = v0->name;
           newVertex->copyOfVert = v0;
           setSurface(newVertex, m0->surface);
           i0->verts.push_back(newVertex);
       }
       else{
           //std::cout << "USING VERTEX" << std::endl;
           v0->copyOfVert = v0;
           i0->verts.push_back(v0);
       }
   }

   // Copy all the edges from the mesh to the instance.
   for (EdgeNew* e0 : m0->edges){
       Vert* firstVert = NULL;
       Vert* secondVert = NULL;

       // Check if vertex is a vertex already in the scene.
       for (Vert* v0 : i0->verts){
           if(v0->index == e0->v0->index)
               firstVert = v0;
       }

       // Otherwise it must be a vertex definition which has a unique name.
       if (!firstVert){
           for (Vert* v0 : i0->verts){
               if(v0->name.compare(e0->v0->name) == 0){
                   firstVert = v0;
               }
           }
       }

       // Do the same thing for the second vertex.
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

       // Check if the edge is already defined
       EdgeNew* newEdge = NULL;
       for( auto e0 : i0->edges ) {
           if ((e0->v0->index == firstVert->index && e0->v1->index == secondVert->index) || (e0->v0->index == secondVert->index && e0->v1->index == firstVert->index)){
               newEdge = e0;
           }
       }

       if (newEdge == NULL){
           newEdge = currReader->getEdge(firstVert->index, secondVert->index);
           //std::cout << "+++++" << std::endl;
           /*if (currReader->getVert(firstVert->index) != NULL){
               std::cout << currReader->getVertName(firstVert->index) << std::endl;
           }
           if (currReader->getVert(secondVert->index) != NULL){
               std::cout << currReader->getVertName(secondVert->index) << std::endl;
           }*/
           if (newEdge != NULL){
               setSurface(newEdge, m0->surface);
                i0->edges.push_back(newEdge);
           }
       }

       if (newEdge == NULL){
            //std::cout << "NEW EDGE" << std::endl;
            newEdge = createEdge(firstVert, secondVert, connect);
            setSurface(newEdge, m0->surface);
            i0->edges.push_back(newEdge);
       }


   }
   //std::cout << i0->edges.size() << std::endl;

   for (FaceNew* f0 : m0->faces){
       std::list<EdgeNew*> edgesFace;
       std::list<Vert*> vertFace;
       for (Vert* vF : f0->verts){
           Vert* firstVert = NULL;
           for (Vert* v0 : i0->verts){
               if(v0->copyOfVert->index == vF->index)
                   firstVert = v0;
           }
           if (!firstVert){
               for (Vert* v0 : i0->verts){
                   if(v0->copyOfVert->index == (vF->index)){
                       firstVert = v0;
                   }
               }
           }
           //std::cout << firstVert->name << std::endl;
           vertFace.push_back(firstVert);
       }
       FaceNew* newFace = createFace(vertFace, &(i0->edges), currReader, connect);

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
    if (mesh != NULL){
        mesh->setPrefix(getFullName());
        return true;
    }
    return false;
}

bool InstanceNew::draw()
{
    //std::cout << this->name << std::endl;
    for(auto v : verts) {
      drawVert(v, surface);
    }
    for(auto e : edges) {
      drawEdge(e, surface);
    }
    for(auto f : faces) {
      /*for(auto v : f->verts) {
          std::cout << v->name << std::endl;
      }*/
      drawFace(f, surface);
    }

    for (auto i : listInstances) {
        i->draw();
    }

    return true;
}

void InstanceNew::flattenInstance(MeshNew* flattenedMesh)
{
    for(Vert* v : verts) {
      bool contains = false;
      for (Vert* vf : flattenedMesh->verts){
          if (v->index == vf->index){
              contains = true;
              break;
          }
      }
      if (!contains){
          flattenedMesh->verts.push_back(v);
      }
    }

    for(EdgeNew* e : edges) {

        bool contains = false;
        for (EdgeNew* ef : flattenedMesh->edges){
            if (e->index == ef->index){
                contains = true;
                break;
            }
        }
        if (!contains){
            if (e->f0 == NULL && e->f1 == NULL){
                for (Vert* v : flattenedMesh->verts){
                    if ((v->index == e->v0->index) || (v->index == e->v1->index)){
                        v->edges.remove(e);
                    }
                }
            } else{
                // ADDED TUESDAY
                /*std::cout << "T" << std::endl;
                for (EdgeNew* ef : flattenedMesh->edges){
                    if ((abs(*(e->v0->xTransformed) - *(ef->v0->xTransformed)) < 0.01
                        && abs(*(e->v0->yTransformed) - *(ef->v0->yTransformed)) < 0.01
                        && abs(*(e->v0->zTransformed) - *(ef->v0->zTransformed)) < 0.01
                        && abs(*(e->v1->xTransformed) - *(ef->v1->xTransformed)) < 0.01
                        && abs(*(e->v1->yTransformed) - *(ef->v1->yTransformed)) < 0.01
                        && abs(*(e->v1->zTransformed) - *(ef->v1->zTransformed)) < 0.01)
                        || (abs(*(e->v0->xTransformed) - *(ef->v1->xTransformed)) < 0.01
                            && abs(*(e->v0->yTransformed) - *(ef->v1->yTransformed)) < 0.01
                            && abs(*(e->v0->zTransformed) - *(ef->v1->zTransformed)) < 0.01
                            && abs(*(e->v1->xTransformed) - *(ef->v0->xTransformed)) < 0.01
                            && abs(*(e->v1->yTransformed) - *(ef->v0->yTransformed)) < 0.01
                            && abs(*(e->v1->zTransformed) - *(ef->v0->zTransformed)) < 0.01)){
                        std::cout << "ALERT" << std::endl;
                        //if (ef->f)
                    }
                }*/
                //==========

                flattenedMesh->edges.push_back(e);
            }

        }


    }
    for(FaceNew* f : faces) {
        bool contains = false;
        for (FaceNew* ff : flattenedMesh->faces){
            if (f->index == ff->index){
                contains = true;
                break;
            }
        }
        if (!contains){
            flattenedMesh->faces.push_back(f);
        }
    }

    for (InstanceNew* i : listInstances) {
        i->flattenInstance(flattenedMesh);
    }


}

bool InstanceNew::drawFaces()
{
    for(auto f : faces) {
      drawFace(f, surface);
    }

    for (auto i : listInstances) {
        i->drawFaces();
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
    if (mesh != NULL){
        for (Vert* v0 : verts){
            /*double *x = (double*) malloc(sizeof(double));
            double *y = (double*) malloc(sizeof(double));
            double *z = (double*) malloc(sizeof(double));

            *x = *(v0->x);
            *y = *(v0->y);
            *z = *(v0->z);

            v0->xTransformed = x;
            v0->yTransformed = y;
            v0->zTransformed = z;*/

            *(v0->xTransformed) = *(v0->x);
            *(v0->yTransformed) = *(v0->y);
            *(v0->zTransformed) = *(v0->z);

        }
    }
    else if (group != NULL){
        for (InstanceNew* i0 : listInstances){
            for (Vert* v0 : i0->verts){
                /*double *x = (double*) malloc(sizeof(double));
                double *y = (double*) malloc(sizeof(double));
                double *z = (double*) malloc(sizeof(double));

                *x = *(v0->x);
                *y = *(v0->y);
                *z = *(v0->z);

                v0->xTransformed = x;
                v0->yTransformed = y;
                v0->zTransformed = z;*/

                *(v0->xTransformed) = *(v0->x);
                *(v0->yTransformed) = *(v0->y);
                *(v0->zTransformed) = *(v0->z);
            }
        }
    }
}

void InstanceNew::applyTransformationGroup(){
    if (group != NULL){
        for (InstanceNew* currInstance : listInstances){
            for (TransformationNew * t : currInstance->transformations){
                currInstance->applyTransformation(t);
            }
        }
    }
}

void InstanceNew::applyTransformation(TransformationNew* t){
    if (mesh != NULL){
        if (dynamic_cast<Rotate*>(t)){
            Rotate* rotate = dynamic_cast<Rotate*>(t);
            for (Vert* v0 : verts){
                // https://en.wikipedia.org/wiki/Rotation_matrix#Non-standard_orientation_of_the_coordinate_system
                double *x = (double*) malloc(sizeof(double));
                double *y = (double*) malloc(sizeof(double));
                double *z = (double*) malloc(sizeof(double));

                double normalizeLength = sqrt(((*rotate->x) * (*rotate->x)) + ((*rotate->y) * (*rotate->y)) + ((*rotate->z) * (*rotate->z)));
                double normalizeX = (*rotate->x) / normalizeLength;
                double normalizeY = (*rotate->y) / normalizeLength;
                double normalizeZ = (*rotate->z) / normalizeLength;

                double radAngle = *rotate->angle * (3.141592f/180.0f);

                double x1 = glm::cos(radAngle) + (normalizeX * normalizeX) * (1 - glm::cos(radAngle));
                double x2 = normalizeX * normalizeY * (1 - glm::cos(radAngle)) - normalizeZ * glm::sin(radAngle);
                double x3 = normalizeX * normalizeZ * (1 - glm::cos(radAngle)) + normalizeY * glm::sin(radAngle);
                double y1 = normalizeY * normalizeX * (1 - glm::cos(radAngle)) + normalizeZ * glm::sin(radAngle);
                double y2 = glm::cos(radAngle) + normalizeY * normalizeY * (1 - glm::cos(radAngle));
                double y3 = normalizeY * normalizeZ * (1 - glm::cos(radAngle)) - normalizeX * glm::sin(radAngle);
                double z1 = normalizeZ * normalizeX * (1 - glm::cos(radAngle)) - normalizeY * glm::sin(radAngle);
                double z2 = normalizeZ * normalizeY * (1 - glm::cos(radAngle)) + normalizeX * glm::sin(radAngle);
                double z3 = glm::cos(radAngle) + normalizeZ * normalizeZ * (1 - glm::cos(radAngle));
                *x = *v0->xTransformed * x1 + *v0->yTransformed * x2 + *v0->zTransformed * x3;
                *y = *v0->xTransformed * y1 + *v0->yTransformed * y2 + *v0->zTransformed * y3;
                *z = *v0->xTransformed * z1 + *v0->yTransformed * z2 + *v0->zTransformed * z3;
                /*
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
                double ax = *v0->xTransformed * x1 + *v0->yTransformed * x2 + *v0->zTransformed * x3;
                double ay = *v0->xTransformed * y1 + *v0->yTransformed * y2 + *v0->zTransformed * y3;
                double az = *v0->xTransformed * z1 + *v0->yTransformed * z2 + *v0->zTransformed * z3;

                *x = ax;
                *y = ay;
                *z = az;*/

                /*v0->xTransformed = x;
                v0->yTransformed = y;
                v0->zTransformed = z;*/
                *v0->xTransformed = *x;
                *v0->yTransformed = *y;
                *v0->zTransformed = *z;

            }
        }
        else if (dynamic_cast<Scale*>(t)){
            Scale* scale = dynamic_cast<Scale*>(t);
            for (Vert* v0 : verts){
                /*double *x = (double*) malloc(sizeof(double));
                double *y = (double*) malloc(sizeof(double));
                double *z = (double*) malloc(sizeof(double));

                *x = *v0->xTransformed * *scale->x;
                *y = *v0->yTransformed * *scale->y;
                *z = *v0->zTransformed * *scale->z;
                v0->xTransformed = x;
                v0->yTransformed = y;
                v0->zTransformed = z;*/

                *v0->xTransformed = *v0->xTransformed * *scale->x;
                *v0->yTransformed = *v0->yTransformed * *scale->y;
                *v0->zTransformed = *v0->zTransformed * *scale->z;
            }
        }
        else if (dynamic_cast<Translate*>(t)){

            Translate* translate = dynamic_cast<Translate*>(t);
            for (Vert* v0 : verts){
                /*double *x = (double*) malloc(sizeof(double));
                double *y = (double*) malloc(sizeof(double));
                double *z = (double*) malloc(sizeof(double));

                *x = *v0->xTransformed + *translate->x;
                *y = *v0->yTransformed + *translate->y;
                *z = *v0->zTransformed + *translate->z;
                v0->xTransformed = x;
                v0->yTransformed = y;
                v0->zTransformed = z;*/

                *v0->xTransformed = *v0->xTransformed + *translate->x;
                *v0->yTransformed = *v0->yTransformed + *translate->y;
                *v0->zTransformed = *v0->zTransformed + *translate->z;

            }
        }
    }
    else if (group != NULL){
        for (InstanceNew* i0 : listInstances){
            i0->applyTransformation(t);
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

void InstanceNew::update(){
    Vert* lastVertSeen = NULL;
    for (Vert* vI : verts){
        for (Vert* vM : this->mesh->verts){
            if (vI->name == vM->name){
                lastVertSeen = vM;
                break;
            }
        }
        if (lastVertSeen != NULL){
            vI->x = lastVertSeen->x;
            vI->y = lastVertSeen->y;
            vI->z = lastVertSeen->z;
            lastVertSeen = NULL;
        }
    }

}

void InstanceNew::updateTransformations(){
    for (TransformationNew* t : this->transformations){
        if (dynamic_cast<Scale*>(t)){
            Scale* scale = dynamic_cast<Scale*>(t);

            double *xValSet = (double*) malloc(sizeof(double));
            parseGetBankVal(scale->xStr.c_str(), currSession, xValSet, 0);
            *(scale->x) = *xValSet;

            double *yValSet = (double*) malloc(sizeof(double));
            parseGetBankVal(scale->yStr.c_str(), currSession, yValSet, 0);
            *(scale->y) = *yValSet;

            double *zValSet = (double*) malloc(sizeof(double));
            parseGetBankVal(scale->zStr.c_str(), currSession, zValSet, 0);
            *(scale->z) = *zValSet;
        } else if (dynamic_cast<Translate*>(t)){
            Translate* translate = dynamic_cast<Translate*>(t);

            double *xValSet = (double*) malloc(sizeof(double));
            parseGetBankVal(translate->xStr.c_str(), currSession, xValSet, 0);
            *(translate->x) = *xValSet;

            double *yValSet = (double*) malloc(sizeof(double));
            parseGetBankVal(translate->yStr.c_str(), currSession, yValSet, 0);
            *(translate->y) = *yValSet;

            double *zValSet = (double*) malloc(sizeof(double));
            parseGetBankVal(translate->zStr.c_str(), currSession, zValSet, 0);
            *(translate->z) = *zValSet;

        } else if (dynamic_cast<Rotate*>(t)){
            Rotate* rotate = dynamic_cast<Rotate*>(t);

            double *xValSet = (double*) malloc(sizeof(double));
            parseGetBankVal(rotate->xStr.c_str(), currSession, xValSet, 0);
            *(rotate->x) = *xValSet;

            double *yValSet = (double*) malloc(sizeof(double));
            parseGetBankVal(rotate->yStr.c_str(), currSession, yValSet, 0);
            *(rotate->y) = *yValSet;

            double *zValSet = (double*) malloc(sizeof(double));
            parseGetBankVal(rotate->zStr.c_str(), currSession, zValSet, 0);
            *(rotate->z) = *zValSet;

            double *angleValSet = (double*) malloc(sizeof(double));
            parseGetBankVal(rotate->angleStr.c_str(), currSession, angleValSet, 0);
            *(rotate->angle) = *angleValSet;
        }
    }
}
