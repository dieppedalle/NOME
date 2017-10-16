//
//  Mesh.h
//  model
//
//  Created by L on 26/08/2017.
//  Copyright © 2017 L. All rights reserved.
//

#ifndef Mesh_h
#define Mesh_h

#include <stdio.h>
#include <set>
#include "Data.h"

typedef int MeshI;

///Mesh class, formed by faces, primarily quad faces, valence four vertices
typedef class MeshNew : public Node
{
    bool isManifold;
    bool hasHoles;
    MeshI index;

public:
    std::unordered_set<Vert*> verts;
    std::unordered_set<EdgeNew*> edges;
    std::unordered_set<FaceNew*> faces;

    bool hasVert(Vert*);
    bool hasEdge(EdgeNew*);
    bool hasFace(FaceNew*);

    Vert* getVert(Vert*);
    EdgeNew* getEdge(EdgeNew*);
    FaceNew* getFace(FaceNew*);

    bool deleteVert(Vert*);
    bool deleteEdge(EdgeNew*);
    bool deleteFace(FaceNew*);

    bool setName(std::string n);
    bool updateNames();

} MeshNew;

///Instance functions
MeshNew* createMesh();
MeshNew* createMesh(MeshNew*);

#endif /* Mesh_h */
