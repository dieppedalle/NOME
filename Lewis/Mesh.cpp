//
//  Mesh.cpp
//  model
//
//  Created by L on 26/08/2017.
//  Copyright © 2017 L. All rights reserved.
//

#include "Mesh.h"

///Mesh class methods, see header file for more details
bool Mesh::hasVert(Vert* v0)
{
    return getVert(v0) != NULL;
}

bool Mesh::hasEdge(Edge* e0)
{
    return getEdge(e0) != NULL;
}

bool Mesh::hasFace(Face* f0)
{
    return getFace(f0) != NULL;
}
    
Vert* Mesh::getVert(Vert* v0)
{
    for( Vert* v1 : this->verts )
    {
        if( v0->index == v1->index )
            return v1;
    }
    return NULL;
}

Edge* Mesh::getEdge(Edge* e0)
{
    for( Edge* e1 : this->edges )
    {
        if( e0->index == e1->index )
            return e1;
    }
    return NULL;
}

Face* Mesh::getFace(Face* f0)
{
    for( Face* f1 : this->faces )
    {
        if( f0->index == f1->index )
            return f1;
    }
    return NULL;
}
    
bool Mesh::deleteVert(Vert* v0)
{
    deleteVert(v0);
    this->verts.remove(v0);
    return true;
}

bool Mesh::deleteEdge(Edge* e0)
{
    deleteEdge(e0);
    this->edges.remove(e0);
    return true;
}

bool Mesh::deleteFace(Face* f0)
{
    deleteFace(f0);
    this->faces.remove(f0);
    return true;
}

bool Mesh::setName(std::string name)
{
    this->name = name;
    return true;
}

///Instance functions
Mesh* createMesh()
{
    Mesh* m0;
    std::list<Vert*> verts; std::list<Edge*> edges; std::list<Face*> faces;
    m0->verts = verts; m0->edges = edges; m0->faces = faces;
    //This behaviour depends on the parser
    return m0;
}