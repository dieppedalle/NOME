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
#include "MeshNew.h"

class InstanceNew
{
    MeshNew* parent;
    std::vector<Vert*> vertices;
    std::vector<EdgeNew*> edges;
    std::vector<FaceNew*> faces;
};

InstanceNew* createInstance(MeshNew* m0);
InstanceNew* createInstance(InstanceNew* i0);

#endif /* Instance_h */
