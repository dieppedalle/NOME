//
//  Subdivision.cpp
//  model
//
//  Created by L on 21/09/2017.
//  Copyright © 2017 L. All rights reserved.
//
#include <stdio.h>
#include <string.h>
#include "SubdivisionNew.h"

//Instantiation
SubdivisionNew* createSubdivision(std::string name, std::string type, double * subdivisions){
    SubdivisionNew* s0 = new SubdivisionNew();
    s0->name = name;
    s0->type = type;
    s0->subdivisions = subdivisions;
    return s0;
}
