//
//  PolylineNew.h
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
    setName(std::string n);
} PolylineNew;

///Instance functions
PolylineNew* createPolylineNew(std::list<Vert*> verticesPolyline);
PolylineNew* createPolylineNew(PolylineNew*);

#endif /* PolylineNew_h */
