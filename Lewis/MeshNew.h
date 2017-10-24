//
//  Mesh.h
//  model
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

    bool setName(std::string n);
    bool updateNames();

    Node* vert(std::string);
    Node* edge(std::string);
    Node* face(std::string);
    Node* vert(int);
    Node* edge(int);
    Node* face(int);
    Node* surface();

} MeshNew;

///Instance functions
MeshNew* createMesh();
MeshNew* createMesh(MeshNew*);

#endif /* Mesh_h */
