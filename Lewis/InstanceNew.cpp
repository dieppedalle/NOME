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
      bool error = drawVert(v);
    }
    for(auto e : mesh->edges) {
      bool error = drawEdge(e);
    }
    for(auto f : mesh->faces) {
      bool error = drawFace(f);
    }

    return true;
}

