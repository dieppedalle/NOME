//
//  Data.h
//  model
//
//  Created by L on 26/08/2017.
//  Copyright © 2017 L. All rights reserved.
//

#ifndef Data_h
#define Data_h

#include <stdio.h>
#include <list>
#include <vector>
#include <iostream>
#include <string>
#include <thread>
#include <mutex>

#include "IO.h"

///Baseline data structure class, every point is defined by a vertex, joined by edges. Edges are joined up to form faces.

///Indices for data structures
typedef int VertI;
typedef int EdgeI;
typedef int FaceI;

class Vert;
class Edge;
class Face;

///Vertex - Usual definition of a vertex in 3d space
typedef class Vert
{
public:
    double x, y, z;
    double weight;
    VertI index;
    std::string name;
    std::list<Edge*> edges;
    std::list<Face*> faces;
} Vert;

///Edge - normal edge construct as defined in 3d space, must have at least two links
typedef class Edge
{
public:
    bool isBorder;
    double interval;
    Vert* v0; Vert* v1;
    int faceCount;
    int vertCount;
    Face* f0; Face* f1;
    EdgeI index;
    std::string name;
} Edge;

///Face - normal face construct in 3d space, must consist of at least 3 edges that form a cycle
typedef class Face
{
public:
    std::list<Edge*> edges;
    std::list<Vert*> verts;
    std::string name;
    FaceI index;
} Face;

///Vert Instantiation
Vert* createVert();
Vert* createVert(Vert*);
Vert* createVert(double x, double y, double z);
Vert* createVert(double x, double y, double z, double w);

///Edge Instantiation
Edge* createEdge(Edge*);
Edge* createEdge(Vert* v0, Vert* v1);
Edge* createEdge(Vert* v0, Vert* v1, double interval);
Edge* createEdge(double x0, double y0, double z0, double x1, double y1, double z1, double interval);

///Face Instantiation
Face* createFace();
Face* createFace(Face*);
Face* createFace(std::list<Edge*> edges);

///Deletion helper functions, unlink from other data structures
bool deleteVert(Vert* vert);
bool deleteEdge(Edge* edge);
bool deleteFace(Face* face);

#endif /* Data_h */