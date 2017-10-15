//
//  Group.cpp
//  model
//
//  Created by L on 22/09/2017.
//  Copyright © 2017 L. All rights reserved.
//

#include <stdio.h>
#include "GroupNew.h"

GroupNew* createGroup(std::list<InstanceNew*> m0)
{
    GroupNew* g0 = new GroupNew();
    g0->instances = m0;
    return g0;
}

GroupNew* createGroup(GroupNew*)
{
    return NULL;
}

bool GroupNew::setName(std::string n)
{
    name = n;
    return updateNames();
}

bool GroupNew::updateNames()
{
    for (InstanceNew* m0 : instances)
    {
        m0->setPrefix(getFullName());
        m0->updateNames();
    }
    return true;
}