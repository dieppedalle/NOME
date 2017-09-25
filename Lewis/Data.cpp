//
//  Data.cpp
//  model
//
//  Created by L on 26/08/2017.
//  Copyright © 2017 L. All rights reserved.
//

#include "Data.h"

///Indices for data instantiation
static int vIndex = 0;
static int eIndex = 0;
static int fIndex = 0;

///Global locks for instancing - in case one day want to multithread
static std::mutex vertLock;
static std::mutex edgeLock;
static std::mutex faceLock;

///Create a default vert, will be at the origin with weight of 1.0
Vert* createVert()
{
    return createVert(0.0, 0.0, 0.0, 1.0);
}

///Create a vert with specified x, y, z values without having to specify a weight
Vert* createVert(double x, double y, double z)
{
    return createVert(x, y, z, 1.0);
}

///Create a weighted vert at x, y, z value
Vert* createVert(double x, double y, double z, double w)
{
    Vert* v0 = new Vert();
    vertLock.lock();
    int index = vIndex;
    vIndex++;
    vertLock.unlock();
    
    v0->index = index;
    v0->x = x;
    v0->y = y;
    v0->z = z;
    v0->weight = w;
    std::list<Edge*> edges; std::list<Face*> faces;
    v0->edges = edges; v0->faces = faces;
    
    return v0;
}

///Create an edge by specifying two points and knot interval, will create the links for the edge
///Currently assume manifold, so an edge shouldn't need more than two links
Edge* createEdge(Vert* v0, Vert* v1, double interval)
{
    Edge* e0 = new Edge();
    e0->isBorder = false;
    
    e0->interval = interval;
    edgeLock.lock();
    int index = eIndex;
    eIndex++;
    edgeLock.unlock();

    e0->v0 = v0;
    e0->v1 = v1;
    e0->index = index;
    e0->faceCount = 0;
    e0->vertCount = 0;
    
    v0->edges.push_back(e0); v1->edges.push_back(e0);
    return e0;
}

///Create edge without specifying knot interval, default to 1.0
Edge* createEdge(Vert* v0, Vert* v1)
{
    return createEdge(v0, v1, 1.0);
}

///Lazy construct, create edge without prior verts
Edge* createEdge(double x0, double y0, double z0, double x1, double y1, double z1, double interval)
{
    Vert* v0 = createVert(x0, y0, z0); Vert* v1 = createVert(x1, y1, z1);
    return createEdge(v0, v1, interval);
}

///Create face helper function
Face* createFace()
{
    Face* f0 = new Face();
    std::list<Edge*> edges; std::list<Vert*> verts;
    f0->edges = edges; f0->verts = verts;
    
    faceLock.lock();
    int index = fIndex;
    fIndex++;
    faceLock.unlock();
    
    f0->index = index;
    return f0;
}

///Create face given a vector of at least three edges, the edges must be adjacent and form a closed loop, otherwise fails
Face* createFace(std::list<Edge*> edges)
{
    Face* f0 = createFace();
    std::vector<Vert*> vIndex;
    //Check if more than three edges are given
    if(edges.size() < 3)
    {
        errorMessage("Fewer than 3 edges given", -1);
        return NULL;
    }
    for( Edge* edge : edges )
    {
        bool b0 = false, b1 = false;
        for( int i = 0; i < vIndex.size(); i++ )
        {
            b0 = b0 | (vIndex[i]->index == edge->v0->index);
            b1 = b1 | (vIndex[i]->index == edge->v1->index);
        }
        if( !b0 ) { f0->verts.push_back(edge->v0); vIndex.push_back(edge->v0); }
        if( !b1 ) { f0->verts.push_back(edge->v1); vIndex.push_back(edge->v1); }
        f0->edges.push_back(edge);
        
        //Check if an edge has more than two adjacent faces
        if( edge->faceCount == 0 )
        {
            edge->f0 = f0;
            edge->faceCount = 1;
        }
        else if (edge->faceCount == 1)
        {
            edge->f1 = f0;
            edge->faceCount = 2;
        }
        else
        {
            errorMessage("Invalid edges given for a face, edges can be adjacent to at most 2 faces.", -1);
            return NULL;
        }
    }
    //Check if edges given are adjacent
    if( vIndex.size() != edges.size() )
    {
        errorMessage("Edges given are not all adjacent", -1);
        return NULL;
    }
    //Add reference to the face for all the vertices in the face
    for( Vert* vert: vIndex )
        vert->faces.push_back(f0);
    return f0;
}

///I need to bring this up: what is the desired behaviour when deleting a vert???
bool deleteVert(Vert* vert)
{
    return true;
}

bool deleteEdge(Edge* edge)
{
    return true;
}

bool deleteFace(Face* face)
{
    return true;
}


