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
    std::vector<MeshNew*> meshes;
    std::string prefix;
    std::string name;

public:
    bool setName(std::string n);
    bool setPrefix(std::string name);
    std::string getName();
    std::string getFullName();
    bool updateNames();
};

GroupNew* createGroup(std::vector<MeshNew*>);
GroupNew* createGroup(GroupNew*);

#endif /* Group_h */
