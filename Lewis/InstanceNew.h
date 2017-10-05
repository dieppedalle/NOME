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
#include "Data.h"

class InstanceNew
{

    std::string prefix = "";
    std::string name = "asd";

public:
    std::list<Vert*> verts;
    std::list<EdgeNew*> edges;
    std::list<FaceNew*> faces;
    bool setName(std::string n);
    bool setPrefix(std::string name);
    std::string getName();
    std::string getFullName();
    bool updateNames();
};

InstanceNew* createInstance(InstanceNew* i0);


#endif /* Instance_h */
