//
//  Reader.cpp
//  model
//
//  Created by L on 26/08/2017.
//  Copyright © 2017 L. All rights reserved.
//

#include "Reader.h"

///Reader class, access of an overarching mesh using the indices of data in the mesh
///A reader must be instantiated for each individual meshes, including if the mesh has been edited with an operation
///that generates a new mesh. Not a new mesh will be generated with all mesh operations but to be safe, it is advisable to
///create a new reader after any operation regardless.

using namespace std;

///Vertex Reader functions, reader will take in the index of a vertex from which to return information

///Get pointer to desired vertex
Vert* Reader::vert(VertI index)
{
    for(Vert* v : mesh->verts)
    {
        if(v->index == index)
            return v;
    }
    return NULL;
}


///Get all edges of which vertex is part of
vector<EdgeI> Reader::vertEdges(VertI index)
{
    vector<EdgeI> edges;
    Vert* v0 = Reader::vert(index);
    if(v0 == NULL)
        return edges;
    for(EdgeNew* edge : v0->edges)
    {
        edges.push_back(edge->index);
    }
    return edges;
}

///Get all faces which touch the vertex
vector<FaceI> Reader::vertFaces(VertI index)
{
    vector<FaceI> faces;
    Vert* v0 = Reader::vert(index);
    if(v0 == NULL)
        return faces;
    for(FaceNew* face : v0->faces)
    {
        faces.push_back(face->index);
    }
    return faces;
}

///Edge Functions
vector<FaceI> edgeFaces(EdgeI index);
vector<VertI> edgeVerts(EdgeI index);

///Face functions
vector<EdgeI> faceEdges(FaceI index);
vector<VertI> faceVerts(FaceI index);
