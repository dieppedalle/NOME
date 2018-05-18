//
//  Offset.cpp
//  model
//
//  Created by L on 21/09/2017.
//  Copyright © 2017 L. All rights reserved.
//
#include <stdio.h>
#include <string.h>
#include "Session.h"
#include "OffsetNew.h"


//Instantiation
OffsetNew* createOffset(std::string name, double *  min, double *  max, double *  step){
    OffsetNew* s0 = new OffsetNew();
    s0->name = name;
    s0->min = min;
    s0->value = *min;
    s0->max = max;
    s0->step = step;
    return s0;
}
