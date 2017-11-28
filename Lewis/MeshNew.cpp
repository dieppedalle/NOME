//
//  Mesh.cpp
//  model
//
//  Created by L on 26/08/2017.
//  Copyright © 2017 L. All rights reserved.
//

#include "MeshNew.h"

static int mIndex = 0;

///Mesh class methods, see header file for more details
bool MeshNew::hasVert(Vert* v0)
{
    return getVert(v0) != NULL;
}

bool MeshNew::hasEdge(EdgeNew* e0)
{
    return getEdge(e0) != NULL;
}

bool MeshNew::hasFace(FaceNew* f0)
{
    return getFace(f0) != NULL;
}
    
Vert* MeshNew::getVert(Vert* v0)
{
    for( Vert* v1 : this->verts )
    {
        if( v0->index == v1->index )
            return v1;
    }
    return NULL;
}

EdgeNew* MeshNew::getEdge(EdgeNew* e0)
{
    for( EdgeNew* e1 : this->edges )
    {
        if( e0->index == e1->index )
            return e1;
    }
    return NULL;
}

FaceNew* MeshNew::getFace(FaceNew* f0)
{
    for( FaceNew* f1 : this->faces )
    {
        if( f0->index == f1->index )
            return f1;
    }
    return NULL;
}
    
bool MeshNew::deleteVert(Vert* v0)
{
    deleteVert(v0);
    this->verts.remove(v0);
    return true;
}

bool MeshNew::deleteEdge(EdgeNew* e0)
{
    deleteEdge(e0);
    this->edges.remove(e0);
    return true;
}

bool MeshNew::deleteFace(FaceNew* f0)
{
    deleteFace(f0);
    this->faces.remove(f0);
    return true;
}

bool MeshNew::setName(std::string n)
{
    if(n.find(".") != std::string::npos && n.find(":") != std::string::npos)
        return false;
    name = "m:"+ n;
    bool error = updateNames();
    return error;
}

bool MeshNew::updateNames()
{
    for(Vert* v0 : verts)
    {
        v0->setPrefix(getFullName());
    }
    for(EdgeNew* e0 : edges)
    {
        e0->setPrefix(getFullName());
    }
    for(FaceNew* f0 : faces)
    {
        f0->setPrefix(getFullName());
    }
    return true;
}


///Instance functions
MeshNew* createMesh()
{
    MeshNew* m0 = new MeshNew();
    //std::list<Vert*> verts; std::list<EdgeNew*> edges; std::list<FaceNew*> faces;
    //m0->verts = verts; m0->edges = edges; m0->faces = faces;
    //This behaviour depends on the parser
    m0->verts = {};
    m0->edges = {};
    m0->faces = {};

    m0->setName("mesh" + std::to_string(mIndex));
    mIndex++;
    //std::cout << m0->getFullName() << std::endl;
    return m0;
}

Node* MeshNew::vert(std::string name)
{
    std::string str = findSubstring(name, 'v', ".");
    if(str.compare("") == 0)
        return NULL;
    std::string id = str.substr(3);
    for(Vert* v0 : verts)
    {
        if(v0->name.compare(id) == 0)
            return v0;
    }
    return NULL;
}

Node* MeshNew::edge(std::string name)
{
    std::string str = findSubstring(name, 'e', ".");
    if(str.compare("") == 0)
        return NULL;
    std::string id = str.substr(3);
    for(EdgeNew* e0 : edges)
    {
        if(e0->name.compare(id) == 0)
            return e0;
    }
    return NULL;
}

Node* MeshNew::face(std::string name)
{
    std::string str = findSubstring(name, 'f', ".");
    if(str.compare("") == 0)
        return NULL;
    std::string id = str.substr(3);
    for(FaceNew* f0 : faces)
    {
        if(f0->name.compare(id) == 0)
            return f0;
    }
    return NULL;
}

Node* MeshNew::vert(int i)
{
    for(Vert* v0 : verts)
    {
        if(v0->index == i)
            return v0;
    }
    return NULL;
}

Node* MeshNew::edge(int i)
{
    for(EdgeNew* e0 : edges)
    {
        if(e0->index == i)
            return e0;
    }
    return NULL;
}

Node* MeshNew::face(int i)
{
    for(FaceNew* f0 : faces)
    {
        if(f0->index == i)
            return f0;
    }
    return NULL;
}

bool MeshNew::drawFaces()
{
    for(FaceNew* f : faces) {
      drawFace(f, NULL);
    }

    return true;
}

bool MeshNew::draw()
{
    //std::cout << this->name << std::endl;
    /*for(auto v : verts) {
      drawVert(v, NULL);
    }*/
    /*for(auto e : edges) {
      drawEdge(e, NULL);
    }*/
    for(auto f : faces) {
      drawFace(f, NULL);
    }

    return true;
}

bool isInList(Vert* vert, std::list<Vert*> listOfStrs){
    std::list<Vert*>::iterator it;
    it = std::find(listOfStrs.begin(), listOfStrs.end(), vert);

    // Check if iterator points to end or not
    if(it != listOfStrs.end())
        return true;
    return false;
}

MeshNew* MeshNew::subdivideMesh(){
    MeshNew* newMesh = createMesh();

    for (FaceNew* currFace: this->faces){
        std::list<Vert*>::iterator vertIt = currFace->verts.begin();
        Vert * previousEdgePoint = NULL;
        for (EdgeNew* currEdge: currFace->edges){
            if (previousEdgePoint == NULL){
                previousEdgePoint = currEdge->edgePoint;
            }
            else{
                std::list<Vert*> listFace;
                listFace.clear();

                listFace.push_back(previousEdgePoint);
                //std::cout << "VERT POINT" << std::endl;
                listFace.push_back((*vertIt)->vertPoint);
                listFace.push_back(currEdge->edgePoint);
                listFace.push_back(currFace->facePoint);
                //std::cout << "START CREATE FACE" << std::endl;
                FaceNew* f0 = createFace(listFace, &(newMesh->edges), NULL, true);
                //std::cout << "END CREATE FACE" << std::endl;

                if(!isInList(previousEdgePoint, newMesh->verts)){
                    newMesh->verts.push_back(previousEdgePoint);
                }
                if(!isInList((*vertIt)->vertPoint, newMesh->verts)){
                    newMesh->verts.push_back((*vertIt)->vertPoint);
                }
                if(!isInList(currEdge->edgePoint, newMesh->verts)){
                    newMesh->verts.push_back(currEdge->edgePoint);
                }
                if(!isInList(currFace->facePoint, newMesh->verts)){
                    newMesh->verts.push_back(currFace->facePoint);
                }

                newMesh->faces.push_back(f0);

                previousEdgePoint = currEdge->edgePoint;
            }

            vertIt++;
        }
        vertIt = currFace->verts.begin();
        std::list<EdgeNew*>::iterator edgeIt = currFace->edges.begin();
        std::list<Vert*> listFace;
        listFace.clear();
        listFace.push_back(previousEdgePoint);
        listFace.push_back((*vertIt)->vertPoint);
        listFace.push_back((*edgeIt)->edgePoint);
        listFace.push_back(currFace->facePoint);

        if(!isInList(previousEdgePoint, newMesh->verts)){
            newMesh->verts.push_back(previousEdgePoint);
        }
        if(!isInList((*vertIt)->vertPoint, newMesh->verts)){
            newMesh->verts.push_back((*vertIt)->vertPoint);
        }
        if(!isInList((*edgeIt)->edgePoint, newMesh->verts)){
            newMesh->verts.push_back((*edgeIt)->edgePoint);
        }
        if(!isInList(currFace->facePoint, newMesh->verts)){
            newMesh->verts.push_back(currFace->facePoint);
        }

        FaceNew* f0 = createFace(listFace, &(newMesh->edges), NULL, true);
        newMesh->faces.push_back(f0);

    }
    return newMesh;
}

void MeshNew::calculateNormal(){
    for (Vert* currVert : this->verts){
        currVert->normal = {0, 0, 0};
    }

    for (FaceNew* currFace : this->faces){
        std::list<Vert*>::iterator it = currFace->verts.begin();
        std::vector<Vert*> firstVerts;

        int i = -1;
        while (it != currFace->verts.end()){
            if (i == 3){
                break;
            }

            if (firstVerts.size() == 3){
                /*std::cout << "======" << std::endl;
                for (Vert* vertexNum : firstVerts){
                    std::cout << vertexNum->name << std::endl;
                }*/
                std::vector<double> normalVector;
                normalVector = getNormalFromVerts(firstVerts);
                double magnitude = sqrt(normalVector[0] * normalVector[0] + normalVector[1] * normalVector[1] + normalVector[2] + normalVector[2]);
                double new_magnitude = getAngleFromVerts(firstVerts);

                normalVector[0] = normalVector[0] * (new_magnitude / magnitude);
                normalVector[1] = normalVector[1] * (new_magnitude / magnitude);
                normalVector[2] = normalVector[2] * (new_magnitude / magnitude);
                firstVerts[1] -> normal[0] += normalVector[0];
                firstVerts[1] -> normal[1] += normalVector[1];
                firstVerts[1] -> normal[2] += normalVector[2];

                firstVerts.erase(firstVerts.begin());
            }
            firstVerts.push_back((*it));

            it++;

            if (i != -1){
                i++;
            }

            if ((i == -1) && (it == currFace->verts.end())){
                it = currFace->verts.begin();
                i++;
            }
        }

        std::cout << "Face" << std::endl;
    }

    for (Vert* currVert : this->verts){
        double magnitude = sqrt(currVert->normal[0] * currVert->normal[0] + currVert->normal[1] * currVert->normal[1] + currVert->normal[2] + currVert->normal[2]);
        currVert->normal[0] = currVert->normal[0] / magnitude;
        currVert->normal[1] = currVert->normal[1] / magnitude;
        currVert->normal[2] = currVert->normal[2] / magnitude;

        std::cout <<  currVert->normal[0] << std::endl;
        std::cout <<  currVert->normal[1] << std::endl;
        std::cout <<  currVert->normal[2] << std::endl;
    }
}
