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
#include "Data.h"

typedef int MeshI;

///Mesh class, formed by faces, primarily quad faces, valence four vertices
typedef class MeshNew
{
    bool isManifold;
    bool hasHoles;
    MeshI index;
    std::string name;

public:
    std::list<Vert*> verts;
    std::list<EdgeNew*> edges;
    std::list<FaceNew*> faces;

    bool hasVert(Vert*);
    bool hasEdge(EdgeNew*);
    bool hasFace(FaceNew*);

    Vert* getVert(Vert*);
    EdgeNew* getEdge(EdgeNew*);
    FaceNew* getFace(FaceNew*);

    bool deleteVert(Vert*);
    bool deleteEdge(EdgeNew*);
    bool deleteFace(FaceNew*);
    bool setName(std::string name);

} MeshNew;

///Instance functions
MeshNew* createMesh();
MeshNew* createMesh(MeshNew*);

#endif /* Mesh_h */
