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

class GroupNew
{
    std::string prefix;
    std::string name;

public:
    std::list<InstanceNew*> instances;
    bool setName(std::string n);
    bool setPrefix(std::string name);
    std::string getName();
    std::string getFullName();
    bool updateNames();
};

GroupNew* createGroup(std::list<InstanceNew*>);
GroupNew* createGroup(GroupNew*);

#endif /* Group_h */
