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
#include <QColor>

#include "IO.h"

///Baseline data structure class, every point is defined by a vertex, joined by edges. Edges are joined up to form faces.

///Indices for data structures
typedef int VertI;
typedef int EdgeI;
typedef int FaceI;

class Vert;
class EdgeNew;
class FaceNew;

typedef class Surface
{
public:
    QColor color;
    std::string name;
} Surface;

Surface* createSurface(double r, double g, double b, std::string name);

///Vertex - Usual definition of a vertex in 3d space
typedef class Vert
{
public:
    double x, y, z;
    double weight;
    VertI index;
    std::string name;
    std::list<EdgeNew*> edges;
    std::list<FaceNew*> faces;
} Vert;

///Edge - normal edge construct as defined in 3d space, must have at least two links
typedef class EdgeNew
{
public:
    bool isBorder;
    double interval;
    Vert* v0; Vert* v1;
    int faceCount;
    int vertCount;
    FaceNew* f0; FaceNew* f1;
    EdgeI index;
    std::string name;
} EdgeNew;

///Face - normal face construct in 3d space, must consist of at least 3 edges that form a cycle
typedef class FaceNew
{
public:
    std::list<EdgeNew*> edges;
    std::list<Vert*> verts;
    std::string name;
    FaceI index;
    Surface* surface;
} FaceNew;

///Vert Instantiation
Vert* createVert();
Vert* createVert(Vert*);
Vert* createVert(double x, double y, double z);
Vert* createVert(double x, double y, double z, double w);

///Edge Instantiation
EdgeNew* createEdge(EdgeNew*);
EdgeNew* createEdge(Vert* v0, Vert* v1);
EdgeNew* createEdge(Vert* v0, Vert* v1, double interval);
EdgeNew* createEdge(double x0, double y0, double z0, double x1, double y1, double z1, double interval);

///Face Instantiation
FaceNew* createFace();
FaceNew* createFace(FaceNew*);
FaceNew* createFace(std::list<EdgeNew*> edges);
FaceNew* createFace(std::list<Vert*> vertices, std::list<EdgeNew*>* edges);


bool setName(Vert* v0, std::string name);
bool setName(EdgeNew* e0, std::string name);
bool setName(FaceNew* f0, std::string name);

bool setSurface(FaceNew* f0, Surface* surface);

///Deletion helper functions, unlink from other data structures
bool deleteVert(Vert* vert);
bool deleteEdge(EdgeNew* edge);
bool deleteFace(FaceNew* face);

#endif /* Data_h */
