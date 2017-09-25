//
//  Group.h
//  model
//
//  Created by L on 22/09/2017.
//  Copyright © 2017 L. All rights reserved.
//

#ifndef Group_h
#define Group_h

#include "Mesh.h"
#include <vector>

class Group
{
    std::vector<Mesh*> meshes;
};

Group* createGroup(std::vector<Mesh*>);
Group* createGroup(Group*);

#endif /* Group_h */
