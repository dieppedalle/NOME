//
//  Object.h
//  model
//
//  Created by L on 26/08/2017.
//  Copyright © 2017 L. All rights reserved.
//

#ifndef Object_h
#define Object_h

#include <stdio.h>
#include "Data.h"

///Mesh class, formed by faces, primarily quad faces, valence four vertices
typedef class ObjectNew
{
    std::string name;

public:
    std::list<FaceNew*> faces;

    //Naming functions
    bool setName(std::string n);

} ObjectNew;

///Instance functions
ObjectNew* createObject(std::list<FaceNew*>);

#endif /* Object_h */
