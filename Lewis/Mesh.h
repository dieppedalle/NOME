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

///Mesh class, formed by faces, primarily quad faces, valence four vertices
typedef class Mesh
{
    bool isManifold;
    bool hasHoles;
    
public:
    std::list<Vert*> verts;
    std::list<Edge*> edges;
    std::list<Face*> faces;
    
    bool hasVert(Vert*);
    bool hasEdge(Edge*);
    bool hasFace(Face*);
    
    Vert* getVert(Vert*);
    Edge* getEdge(Edge*);
    Face* getFace(Face*);
    
    bool deleteVert(Vert*);
    bool deleteEdge(Edge*);
    bool deleteFace(Face*);

} Mesh;

///Instance functions
Mesh* createMesh();
Mesh* createMesh(Mesh*);

#endif /* Mesh_h */
