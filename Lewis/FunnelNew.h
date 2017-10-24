//
//  FunnelNew.h
//  model
//
//  Created by L on 26/08/2017.
//  Copyright © 2017 L. All rights reserved.
//

#ifndef FunnelNew_h
#define FunnelNew_h

#include <stdio.h>
#include <set>
#include "Data.h"
#include "MeshNew.h"

///Mesh class, formed by faces, primarily quad faces, valence four vertices
typedef class FunnelNew : public MeshNew
{
public:
    double *n;
    double *ro;
    double *ratio;
    double *h;
    void createVertEdgeFunnel();
    void updateFunnel();
} FunnelNew;

///Instance functions
FunnelNew* createFunnel(double *n, double *ro, double *ratio, double *h);
FunnelNew* createFunnel(FunnelNew*);

#endif /* FunnelNew_h */
