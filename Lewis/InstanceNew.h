//
//  Instance.h
//

#ifndef InstanceNew_h
#define InstanceNew_h

#include <stdio.h>
#include <QtOpenGL>
#include "Data.h"
#include "MeshNew.h"
#include "TransformationNew.h"

typedef int InstanceI;

class InstanceNew : public Node
{
public:
    MeshNew* mesh;
    std::list<Vert*> verts;
    std::list<EdgeNew*> edges;
    std::list<FaceNew*> faces;
    bool setName(std::string n);
    bool updateNames();
    bool draw();
    void applyTransformation(TransformationNew* t);
    void undoTransformation(TransformationNew* t);
    Surface* surface;
    std::list<TransformationNew*> transformations;
    std::list<TransformationNew*> appliedTransformations;

    Node* vert(std::string);
    Node* edge(std::string);
    Node* face(std::string);
    Node* vert(int);
    Node* edge(int);
    Node* face(int);
};

bool setSurface(InstanceNew* i0, Surface* surface);
//Instantiation
InstanceNew* createInstance(InstanceNew* i0);
InstanceNew* createInstance(MeshNew* m0);


#endif /* Instance_h */
