//
//  Reader.h
//  model
//
//  Created by L on 26/08/2017.
//  Copyright © 2017 L. All rights reserved.
//

#ifndef Reader_h
#define Reader_h

#include <stdio.h>
#include <iostream>
#include <vector>
#include "Data.h"
#include "Mesh.h"

///Reader class for accessing data of a surface using only the indices of its elements
///For efficient calculation and iterative approaches for mesh operations

using namespace std;

typedef class Reader
{
private:
    Mesh* mesh;
    
    int accesses;
    
public:
    ///Vert functions
    Vert* vert(VertI index);
    vector<EdgeI> vertEdges(VertI index);
    vector<FaceI> vertFaces(VertI index);
    ///Edge functions
    bool isBorder(EdgeI index);
    Edge* edge(EdgeI index);
    vector<FaceI> edgeFaces(EdgeI index);
    vector<VertI> edgeVerts(EdgeI index);
    ///Face functions
    vector<EdgeI> faceEdges(FaceI index);
    vector<VertI> faceVerts(FaceI index);
} Reader;

///Instantiation
Reader* createReader();
Reader* createReader(Reader*);


#endif /* Reader_h */
