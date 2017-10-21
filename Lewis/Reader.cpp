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

Reader* createReader(Session* currSession){
    Reader* reader0 = new Reader();
    reader0->session = currSession;
    return reader0;
}

///Vertex Reader functions, reader will take in the index of a vertex from which to return information


///Get pointer to desired vertex
Vert* Reader::vert(VertI index)
{
    for(Vert* v : session->verts)
    {
        if(v->index == index)
            return v;
    }
    return NULL;
}

FaceNew* Reader::face(FaceI index)
{
    for(FaceNew* f : session->faces)
    {
        if(f->index == index)
            return f;
    }

    for (InstanceNew* i: session->instances)
    {
        for(FaceNew* f : i->mesh->faces)
        {
            if(f->index == index)
                return f;
        }
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

///Vertex Reader functions by name

///Get pointer to desired vertex
Vert* Reader::vert(std::string name)
{
    for(Vert* v : session->verts)
    {
        if(!name.compare(v->getName()))
            return v;
    }

    for(FaceNew* f : session->faces)
    {
        for(Vert* v : f->verts)
        {
            if(!name.compare(f->getName() + "." + v->getName()))
                return v;
        }
    }

    for(InstanceNew* i : session->instances)
    {
        for(FaceNew* f : i->mesh->faces)
        {
            for(Vert* v : f->verts)
            {
                if(!name.compare(i->getName() + "." + f->getName() + "." + v->getName()))
                    return v;
            }
        }
    }

    return NULL;
}

Surface* Reader::surf(std::string name)
{
    for(Surface* s : session->surfaces)
    {
        if(!name.compare(s->name))
            return s;
    }
    return NULL;
}


///Get all edges of which vertex is part of
vector<EdgeI> Reader::vertEdges(std::string name)
{
    vector<EdgeI> edges;
    Vert* v0 = Reader::vert(name);
    if(v0 == NULL)
        return edges;
    for(EdgeNew* edge : v0->edges)
    {
        edges.push_back(edge->index);
    }
    return edges;
}

///Get all faces which touch the vertex
vector<FaceI> Reader::vertFaces(std::string name)
{
    vector<FaceI> faces;
    Vert* v0 = Reader::vert(name);
    if(v0 == NULL)
        return faces;
    for(FaceNew* face : v0->faces)
    {
        faces.push_back(face->index);
    }
    return faces;
}

///Edge functions
bool isBorder(EdgeI index);
EdgeNew* Reader::edge(EdgeI index){
    return NULL;
}

vector<FaceI> edgeFaces(EdgeI index);
vector<VertI> edgeVerts(EdgeI index);
bool isBorder(std::string name);
EdgeNew* edge(std::string name);
vector<FaceI> edgeFaces(std::string name);
vector<VertI> edgeVerts(std::string name);

///Face functions
FaceNew* face(FaceI index);

vector<EdgeI> faceEdges(FaceI index);
vector<VertI> faceVerts(FaceI index);
FaceNew* Reader::face(std::string name){
    for(FaceNew* f : session->faces)
    {
        if(!name.compare(f->getName()))
            return f;
    }
    return NULL;
}

MeshNew* Reader::mesh(std::string name){
    for(MeshNew* m : session->meshes)
    {
        if(!name.compare(m->getName()))
            return m;
    }
    for(MeshNew* m : session->polylines)
    {
        if(!name.compare(m->getName()))
            return m;
    }
    return NULL;
}

vector<EdgeI> faceEdges(std::string name);
vector<VertI> faceVerts(std::string name);
