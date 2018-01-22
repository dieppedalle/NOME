//
//  Instance.h
//

#ifndef INSTANCENEW_H
#define INSTANCENEW_H

#include <stdio.h>
#include <QtOpenGL>
#include "Data.h"
#include "MeshNew.h"
#include "CircleNew.h"
#include "TransformationNew.h"
//#include "GroupNew.h"

typedef int InstanceI;
class GroupNew;
class Reader;

class InstanceNew : public Node
{
public:
    MeshNew* mesh = NULL;

    // This is used only if the instance is an instance of a group.
    GroupNew* group = NULL;
    std::list<InstanceNew*> listInstances;

    std::list<Vert*> verts;
    std::list<EdgeNew*> edges;
    std::list<FaceNew*> faces;
    bool setName(std::string n);
    bool updateNames();
    bool draw();
    void applyTransformationGroup();
    void applyTransformation(TransformationNew* t);
    void undoTransformation(TransformationNew* t);
    void updateVerts();
    bool drawFaces();
    void flattenInstance(MeshNew*);
    Surface* surface;
    std::list<TransformationNew*> transformations;
    std::list<TransformationNew*> appliedTransformations;

    Node* vert(std::string);
    Node* edge(std::string);
    Node* face(std::string);
    Node* vert(int);
    Node* edge(int);
    Node* face(int);

    void update();
};

bool setSurface(InstanceNew* i0, Surface* surface);
//Instantiation
InstanceNew* createInstance(InstanceNew* i0);
InstanceNew* createInstance(MeshNew* m0, std::list<Vert*> vertsDef, Reader* currReader, bool connect, bool doNotCreateVertices);
InstanceNew* createInstance(GroupNew* g0, std::list<Vert*> vertsDef, Reader* currReader);


#endif /* Instance_h */
