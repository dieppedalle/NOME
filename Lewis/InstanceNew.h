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


class InstanceNew : public Node
{
public:
    MeshNew* mesh;
    bool updateNames();
    bool draw();
};

//Instantiation
InstanceNew* createInstance(InstanceNew* i0);
InstanceNew* createInstance(MeshNew* m0);


#endif /* Instance_h */
