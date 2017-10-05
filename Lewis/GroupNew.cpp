//
//  Group.cpp
//  model
//
//  Created by L on 22/09/2017.
//  Copyright © 2017 L. All rights reserved.
//

#include <stdio.h>
#include "GroupNew.h"

GroupNew* createGroup(std::vector<MeshNew*> m0)
{
    return NULL;
}

GroupNew* createGroup(GroupNew*)
{
    return NULL;
}

bool GroupNew::setPrefix(std::string name)
{
    prefix = name;
    return true;
}

bool GroupNew::setName(std::string n)
{
    name = n;
    return true;
}

std::string GroupNew::getFullName()
{
    return prefix + name;
}

bool GroupNew::updateNames()
{
    for (MeshNew* m0 : meshes)
    {
        m0->setPrefix(getFullName());
        m0->updateNames();
    }
}
