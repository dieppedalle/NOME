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
   return i0;
}

bool InstanceNew::setName(std::string n)
{
    name = n;
    return updateNames();
}

bool InstanceNew::updateNames()
{
    mesh->setPrefix(getFullName());
    return true;
}

bool InstanceNew::draw()
{
    for(auto t : transformations) {
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
    }

    //std::cout << "START" << std::endl;
    for(auto v : mesh->verts) {
      //std::cout << v->getFullName() << std::endl;
      drawVert(v, surface);
    }
    for(auto e : mesh->edges) {
      drawEdge(e, surface);
    }
    for(auto f : mesh->faces) {
      drawFace(f, surface);
    }

    for (std::list<TransformationNew *>::reverse_iterator rit=transformations.rbegin(); rit!=transformations.rend(); ++rit){
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
    }

    return true;
}

