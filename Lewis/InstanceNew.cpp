//
//  Instance.cpp
//  model
//
//  Created by L on 21/09/2017.
//  Copyright © 2017 L. All rights reserved.
//
#include <stdio.h>
#include <string.h>
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
    for(auto f : mesh->verts) {
      std::cout << f->getName() << std::endl;
      glLoadName(f->index);
      float x = f->x;
      float y = f->y;
      float z = f->z;
      glBegin(GL_QUADS);
          glNormal3f(0, 0, 1);
          glVertex3f(x + 0.1 / 2, y + 0.1 / 2, z);
          glVertex3f(x - 0.1 / 2, y + 0.1 / 2, z);
          glVertex3f(x - 0.1 / 2, y - 0.1 / 2, z);
          glVertex3f(x + 0.1 / 2, y - 0.1 / 2, z);
      glEnd();
      glBegin(GL_QUADS);
          glNormal3f(1, 0, 0);
          glVertex3f(x, y + 0.1 / 2, z + 0.1 / 2);
          glVertex3f(x, y - 0.1 / 2, z + 0.1 / 2);
          glVertex3f(x, y - 0.1 / 2, z - 0.1 / 2);
          glVertex3f(x, y + 0.1 / 2, z - 0.1 / 2);
      glEnd();
      glBegin(GL_QUADS);
          glNormal3f(0, 1, 0);
          glVertex3f(x + 0.1 / 2, y, z - 0.1 / 2);
          glVertex3f(x + 0.1 / 2, y, z + 0.1 / 2);
          glVertex3f(x - 0.1 / 2, y, z + 0.1 / 2);
          glVertex3f(x - 0.1 / 2, y, z - 0.1 / 2);
      glEnd();
    }

    return true;
}

