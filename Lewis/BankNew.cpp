//
//  Instance.cpp
//  model
//
//  Created by L on 21/09/2017.
//  Copyright © 2017 L. All rights reserved.
//
#include <stdio.h>
#include <string.h>
#include "BankNew.h"

//Instantiation
BankNew* createBank(){
    BankNew* b0 = new BankNew();
    //i0->mesh = m0;
    return b0;
}

SetNew* createSet(std::string name, double value, double start, double end, double stepSize){
    SetNew* s0 = new SetNew();
    s0->name = name;
    s0->value = value;
    s0->start = start;
    s0->end = end;
    s0->stepSize = stepSize;
    return s0;
}
