//
//  PolylineNew.h
//  model
//
//  Created by L on 26/08/2017.
//  Copyright © 2017 L. All rights reserved.
//

#ifndef PolylineNew_h
#define PolylineNew_h

#include <stdio.h>
#include <set>
#include "Data.h"
#include "MeshNew.h"

///Mesh class, formed by faces, primarily quad faces, valence four vertices
typedef class PolylineNew : public MeshNew
{

} PolylineNew;

///Instance functions
PolylineNew* createPolylineNew(std::list<Vert*> verticesPolyline);
PolylineNew* createPolylineNew(PolylineNew*);

#endif /* PolylineNew_h */
