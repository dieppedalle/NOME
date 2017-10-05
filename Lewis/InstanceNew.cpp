//
//  Instance.cpp
//  model
//
//  Created by L on 21/09/2017.
//  Copyright © 2017 L. All rights reserved.
//
#include <stdio.h>
#include <string.h>
#include "InstanceNew.h"

InstanceNew* createInstance(InstanceNew* i0)
{
    return NULL;
}

bool InstanceNew::setName(std::string n)
{
    std::cout << "HELLO" << std::endl;
    //std::cout << name << std::endl;
    std::cout << "BYE" << std::endl;
    //name = n;
    //updateNames();
    return true;
}

bool InstanceNew::setPrefix(std::string name)
{
    prefix = name;
    return true;
}

std::string InstanceNew::getFullName()
{
    return prefix + name;
}

bool InstanceNew::updateNames()
{
    for(Vert* v0 : verts)
    {
        v0->setPrefix(getFullName());
    }
    for(EdgeNew* e0 : edges)
    {
        e0->setPrefix(getFullName());
    }
    for(FaceNew* f0 : faces)
    {
        f0->setPrefix(getFullName());
    }
    return true;
}
