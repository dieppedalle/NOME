//
//  Instance.h
//  model
//
//  Created by L on 21/09/2017.
//  Copyright © 2017 L. All rights reserved.
//

#ifndef Instance_h
#define Instance_h

#include <stdio.h>
#include "Mesh.h"

class Instance
{
    Mesh* parent;
    std::vector<Vert*> vertices;
    std::vector<Edge*> edges;
    std::vector<Face*> faces;
};

Instance* createInstance(Mesh* m0);
Instance* createInstance(Instance* i0);

#endif /* Instance_h */
