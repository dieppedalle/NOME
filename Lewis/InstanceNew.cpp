//
//  Instance.cpp
//  model
//
//  Created by L on 21/09/2017.
//  Copyright © 2017 L. All rights reserved.
//
#include <stdio.h>
#include <string.h>
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

InstanceNew* createInstance(MeshNew* m0)
{
   InstanceNew* i0 = new InstanceNew();
   i0->mesh = m0;
   for (Vert* v0 : m0->verts){

       Vert* newVertex = createVert(v0);
       newVertex->name = v0->name;
       i0->verts.push_back(newVertex);
   }
   /*for (EdgeNew* e0 : m0->edges){
       Vert* firstVert;
       Vert* secondVert;

       for (Vert* v0 : i0->verts){
           if(v0->name.compare(e0->v0->name) == 0)
               firstVert = v0;
       }

       for (Vert* v1 : i0->verts){
           if(v1->name.compare(e0->v1->name) == 0)
               secondVert = v1;
       }

       EdgeNew* newEdge = createEdge(firstVert, secondVert, 1.0);
       i0->edges.push_back(newEdge);
   }*/

   for (FaceNew* f0 : m0->faces){
       std::list<EdgeNew*> edgesFace;
       std::list<Vert*> vertFace;
       for (EdgeNew* e0 : f0->edges){
           Vert* firstVert;
           Vert* secondVert;

           for (Vert* v0 : i0->verts){
               if(v0->name.compare(e0->v0->name) == 0)
                   firstVert = v0;
           }

           for (Vert* v1 : i0->verts){
               if(v1->name.compare(e0->v1->name) == 0)
                   secondVert = v1;
           }

           EdgeNew* newEdge = createEdge(firstVert, secondVert, 1.0);
           edgesFace.push_back(newEdge);
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
    /*for(auto t : transformations) {
        if (dynamic_cast<Rotate*>(t)){
            Rotate* rotate = dynamic_cast<Rotate*>(t);
            glRotatef(rotate->angle, rotate->x, rotate->y, rotate->z);
        }
        else if (dynamic_cast<Scale*>(t)){
            Scale* scale = dynamic_cast<Scale*>(t);
            glScalef(scale->x, scale->y, scale->z);
        }
        else if (dynamic_cast<Translate*>(t)){
            Translate* translate = dynamic_cast<Translate*>(t);
            glTranslatef(translate->x, translate->y, translate->z);
        }
    }*/

    for(auto v : verts) {
      drawVert(v, surface);
    }
    for(auto e : edges) {
      drawEdge(e, surface);
    }
    for(auto f : faces) {
      drawFace(f, surface);
    }

    /*for (std::list<TransformationNew *>::reverse_iterator rit=transformations.rbegin(); rit!=transformations.rend(); ++rit){
        if (dynamic_cast<Rotate*>(*rit)){
            Rotate* rotate = dynamic_cast<Rotate*>(*rit);
            glRotatef(-rotate->angle, rotate->x, rotate->y, rotate->z);
        }
        else if (dynamic_cast<Scale*>(*rit)){
            Scale* scale = dynamic_cast<Scale*>(*rit);
            glScalef(-scale->x, -scale->y, -scale->z);
        }
        else if (dynamic_cast<Translate*>(*rit)){
            Translate* translate = dynamic_cast<Translate*>(*rit);
            glTranslatef(-translate->x, -translate->y, -translate->z);
        }
    }*/

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

void InstanceNew::applyTransformation(TransformationNew* t){
    if (dynamic_cast<Rotate*>(t)){
        //Rotate* rotate = dynamic_cast<Rotate*>(t);
        //glRotatef(rotate->angle, rotate->x, rotate->y, rotate->z);
    }
    else if (dynamic_cast<Scale*>(t)){
        Scale* scale = dynamic_cast<Scale*>(t);
        for (Vert* v0 : verts){
            *v0->x *= scale->x;
            *v0->y *= scale->y;
            *v0->z *= scale->z;
        }

        //glScalef(scale->x, scale->y, scale->z);
    }
    else if (dynamic_cast<Translate*>(t)){
        Translate* translate = dynamic_cast<Translate*>(t);
        for (Vert* v0 : verts){
            *v0->x += translate->x;
            *v0->y += translate->y;
            *v0->z += translate->z;
        }
    }
}
