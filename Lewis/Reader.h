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
#include "MeshNew.h"

///Reader class for accessing data of a surface using only the indices of its elements
///For efficient calculation and iterative approaches for mesh operations

using namespace std;

typedef class Reader
{
private:
    Mesh* mesh;
    MeshNew* mesh;
    int accesses;
    
public:
    ///Vert functions
    Vert* vert(VertI index);
    vector<EdgeI> vertEdges(VertI index);
    vector<FaceI> vertFaces(VertI index);
    Vert* vert(std::string name);
    vector<EdgeI> vertEdges(std::string name);
    vector<FaceI> vertFaces(std::string name);
    
    ///Edge functions
    bool isBorder(EdgeI index);
    EdgeNew* edge(EdgeI index);
    vector<FaceI> edgeFaces(EdgeI index);
    vector<VertI> edgeVerts(EdgeI index);
    bool isBorder(std::string name);
    Edge* edge(std::string name);
    vector<FaceI> edgeFaces(std::string name);
    vector<VertI> edgeVerts(std::string name);
    
    ///Face functions
    Face* face(FaceI index);
    vector<EdgeI> faceEdges(FaceI index);
    vector<VertI> faceVerts(FaceI index);
    Face* face(std::string name);
    vector<EdgeI> faceEdges(std::string name);
    vector<VertI> faceVerts(std::string name);
} Reader;

///Instantiation
Reader* createReader();
Reader* createReader(Mesh*);
Reader* createReader(Reader*);


#endif /* Reader_h */
