//
//  SweepNew.h
//  Author: Beren Oguz <beren@berkeley.edu>
//

#ifndef SweepNew_h
#define SweepNew_h

#include <stdio.h>
#include <set>
#include "Data.h"
#include "MeshNew.h"

///Mesh class, formed by faces, primarily quad faces, valence four vertices
typedef class SweepNew : public MeshNew
{
public:
    bool setName(std::string n);
} SweepNew;

///Instance functions
SweepNew* createSweepNew(std::list<Vert*> verticesSweep, std::list<Vert*> crosssection, double* width, double* azimuth, double* twist, Reader* reader);
//SweepNew* createSweepNew(std::list<Vert*> verticesSweep, std::list<EdgeNew*> *edgeList);
SweepNew* createSweepNew(SweepNew*);

#endif /* SweepNew_h */
