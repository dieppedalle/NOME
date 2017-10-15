//
//  Mesh.cpp
//  model
//
//  Created by L on 26/08/2017.
//  Copyright © 2017 L. All rights reserved.
//

#include "MeshNew.h"

static int mIndex = 0;

///Mesh class methods, see header file for more details
bool MeshNew::hasVert(Vert* v0)
{
    return getVert(v0) != NULL;
}

bool MeshNew::hasEdge(EdgeNew* e0)
{
    return getEdge(e0) != NULL;
}

bool MeshNew::hasFace(FaceNew* f0)
{
    return getFace(f0) != NULL;
}
    
Vert* MeshNew::getVert(Vert* v0)
{
    for( Vert* v1 : this->verts )
    {
        if( v0->index == v1->index )
            return v1;
    }
    return NULL;
}

EdgeNew* MeshNew::getEdge(EdgeNew* e0)
{
    for( EdgeNew* e1 : this->edges )
    {
        if( e0->index == e1->index )
            return e1;
    }
    return NULL;
}

FaceNew* MeshNew::getFace(FaceNew* f0)
{
    for( FaceNew* f1 : this->faces )
    {
        if( f0->index == f1->index )
            return f1;
    }
    return NULL;
}
    
bool MeshNew::deleteVert(Vert* v0)
{
    deleteVert(v0);
    this->verts.erase(v0);
    return true;
}

bool MeshNew::deleteEdge(EdgeNew* e0)
{
    deleteEdge(e0);
    this->edges.erase(e0);
    return true;
}

bool MeshNew::deleteFace(FaceNew* f0)
{
    deleteFace(f0);
    this->faces.erase(f0);
    return true;
}

bool MeshNew::setName(std::string n)
{
    name = n;
    bool error = updateNames();

    return error;
}

bool MeshNew::updateNames()
{
    for(Vert* v0 : verts)
    {
        v0->setPrefix(getFullName());
    }
    for(EdgeNew* e0 : edges)
    {
        e0->setPrefix(getFullName());
    }
    for(FaceNew* f0 : faces)
    {
        f0->setPrefix(getFullName());
    }
    /*
    std::cout << "mid" << std::endl;
    for(Vert* v0 : verts)
    {
        std::cout << v0->getFullName() << std::endl;
    }
    for(EdgeNew* e0 : edges)
    {
        std::cout << e0->getFullName() << std::endl;
    }
    for(FaceNew* f0 : faces)
    {
        std::cout << f0->getFullName() << std::endl;
    }
    std::cout << "end" << std::endl;
    */
    return true;
}


///Instance functions
MeshNew* createMesh()
{
    MeshNew* m0 = new MeshNew();
    //std::list<Vert*> verts; std::list<EdgeNew*> edges; std::list<FaceNew*> faces;
    //m0->verts = verts; m0->edges = edges; m0->faces = faces;
    //This behaviour depends on the parser
    m0->setName("mesh" + std::to_string(mIndex));
    mIndex++;
    //std::cout << m0->getFullName() << std::endl;
    return m0;
}