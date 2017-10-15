//
//  Instance.h
//  model
//
//  Created by L on 21/09/2017.
//  Copyright © 2017 L. All rights reserved.
//

#ifndef InstanceNew_h
#define InstanceNew_h

#include <stdio.h>
#include <QtOpenGL>
#include "Data.h"
#include "MeshNew.h"
#include "TransformationNew.h"

class InstanceNew : public Node
{
public:
    MeshNew* mesh;
    bool setName(std::string n);
    bool updateNames();
    bool draw();
    Surface* surface;
    std::list<TransformationNew *> transformations;
};

bool setSurface(InstanceNew* i0, Surface* surface);
//Instantiation
InstanceNew* createInstance(InstanceNew* i0);
InstanceNew* createInstance(MeshNew* m0);


#endif /* Instance_h */
