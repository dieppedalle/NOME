//
//  Group.h
//  model
//
//  Created by L on 22/09/2017.
//  Copyright © 2017 L. All rights reserved.
//

#ifndef GroupNew_h
#define GroupNew_h

#include "MeshNew.h"
#include <vector>

class GroupNew : public Node
{
public:
    std::list<InstanceNew*> instances;
    std::list<MeshNew*> meshes;

    bool updateNames();
};

GroupNew* createGroup(std::list<InstanceNew*>);
GroupNew* createGroup(GroupNew*);

#endif /* Group_h */
