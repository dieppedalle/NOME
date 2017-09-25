//
//  main.cpp
//  model
//
//  Created by L on 26/08/2017.
//  Copyright © 2017 L. All rights reserved.
//

#include <iostream>
#include "Data.h"

int main(int argc, const char * argv[]) {
    // insert code here...
    Vert* v0 = createVert(0, 0 ,0, 1);
    Vert* v1 = createVert(0, 1 ,0, 1);
    Vert* v2 = createVert(0, 2 ,0, 1);
    Vert* v3 = createVert(0, 3 ,0, 1);
    Edge* e0 = createEdge(v0, v1);
    Edge* e1 = createEdge(v1, v2);
    Edge* e2 = createEdge(v2, v3);
    Edge* e3 = createEdge(v3, v0);
    std::list<Edge*> l0;
    l0.push_back(e0); l0.push_back(e1); l0.push_back(e2); l0.push_back(e3);
    Face* f0 = createFace(l0);
    printf("Done.");
    
}
