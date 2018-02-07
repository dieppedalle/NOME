//
//  TunnelNew.h
//  model
//
//  Created by L on 26/08/2017.
//  Copyright © 2017 L. All rights reserved.
//

#ifndef TunnelNew_h
#define TunnelNew_h

#include <stdio.h>
#include <set>
#include "Data.h"
#include "MeshNew.h"
class Reader;

///Mesh class, formed by faces, primarily quad faces, valence four vertices
typedef class TunnelNew : public MeshNew
{
public:
    double *n;
    double *ro;
    double *ratio;
    double *h;

    std::string nStr;
    std::string roStr;
    std::string ratioStr;
    std::string hStr;

    Reader * reader;

    std::vector<Vert*> baseCircle;
    std::vector<Vert*> highCircle;
    std::vector<Vert*> lowCircle;

    void createVertEdgeTunnel();
    int updateTunnel();

    bool setName(std::string n);
    Session* currSession;
} TunnelNew;

///Instance functions
TunnelNew* createTunnel(double *n, double *ro, double *ratio, double *h, Reader * reader);
TunnelNew* createTunnel(TunnelNew*);

#endif /* FunnelNew_h */
