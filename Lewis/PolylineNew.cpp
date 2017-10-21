//
//  Mesh.cpp
//  model
//
//  Created by L on 26/08/2017.
//  Copyright © 2017 L. All rights reserved.
//

#include "PolylineNew.h"

static int pIndex = 0;

///Polyline functions
PolylineNew* createPolylineNew(std::list<Vert*> verticesPolyline)
{
    PolylineNew* p0 = new PolylineNew();
    //This behaviour depends on the parser
    p0->setName("polyline" + std::to_string(pIndex));
    p0->verts = verticesPolyline;

    EdgeNew * currentEdge;
    std::list<Vert*>::iterator it = verticesPolyline.begin();
    std::list<Vert*>::iterator it2 = verticesPolyline.begin();
    std::list<EdgeNew*> currentEdges;
    ++it2;
    while (it != verticesPolyline.end()){
        if (it2 != verticesPolyline.end()){
            currentEdge = createEdge(*it, *it2);
            it2++;
            p0->edges.push_back(currentEdge);
        }
        it++;

    }

    pIndex++;

    return p0;
}
