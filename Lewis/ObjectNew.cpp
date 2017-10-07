//
//  Mesh.cpp
//  model
//
//  Created by L on 26/08/2017.
//  Copyright © 2017 L. All rights reserved.
//

#include "ObjectNew.h"

///Mesh class methods, see header file for more details



bool ObjectNew::setName(std::string n)
{
    name = n;
    return true;
}

ObjectNew* createObject(std::list<FaceNew*> m0)
{
    ObjectNew* g0 = new ObjectNew();
    g0->faces = m0;
    return g0;
}

