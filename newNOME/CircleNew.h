//
//  Circle.h
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
    std::string numStr;
    std::string radStr;
    void createVertEdgeCircle();
    int updateCircle();
    bool setName(std::string n);
    Session * currSession;
} CircleNew;

///Instance functions
CircleNew* createCircle(double *num, double *rad);
CircleNew* createCircle(CircleNew*);

#endif /* CircleNew_h */
