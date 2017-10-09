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


bool InstanceNew::updateNames()
{
    mesh->setPrefix(getFullName());
    return true;
}

bool InstanceNew::draw()
{
    for(auto v : mesh->verts) {
      bool error = drawVert(v, surface);
    }
    for(auto e : mesh->edges) {
      bool error = drawEdge(e, surface);
    }
    for(auto f : mesh->faces) {
      bool error = drawFace(f, surface);
    }

    return true;
}

