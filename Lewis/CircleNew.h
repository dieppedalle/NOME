//
//  PolylineNew.h
//  model
//
//  Created by L on 26/08/2017.
//  Copyright © 2017 L. All rights reserved.
//

#ifndef CircleNew_h
#define CircleNew_h

#include <stdio.h>
#include <set>
#include "Data.h"
#include "MeshNew.h"

///Mesh class, formed by faces, primarily quad faces, valence four vertices
typedef class CircleNew : public MeshNew
{
public:
    double *num;
    double *rad;
    void createVertEdgeCircle();
    void updateCircle();
} CircleNew;

///Instance functions
CircleNew* createCircle(double *num, double *rad);
CircleNew* createCircle(CircleNew*);

#endif /* CircleNew_h */
