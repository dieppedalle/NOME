//
//  Session.cpp
//  model
//
//  Created by L on 26/08/2017.
//  Copyright © 2017 L. All rights reserved.
//

#include "Session.h"
#include "Reader.h"
#include "Data.h"
#include <fstream>
#include <sstream>
#include <glm/glm.hpp>


static int sIndex = 0;

Session* createSession()
{
    Session* session0 = new Session();

    session0->setName("s:" + std::to_string(sIndex));
    sIndex++;

    return session0;
}

Session* createSession(Session* s0)
{
    return NULL;
}

bool Session::setName(std::string n)
{
    name = n;
    return updateNames();
}

std::string Session::getName()
{
    return name;
}

bool Session::updateNames()
{
    for(Vert* v0 : verts)
    {
        v0->setPrefix(name);
    }
    for(EdgeNew* e0 : edges)
    {
        e0->setPrefix(name);
    }
    for(FaceNew* f0 : faces)
    {
        f0->setPrefix(name);
    }
    for(GroupNew* g0 : groups)
    {
        g0->setPrefix(name);
        g0->updateNames();
    }
    for(MeshNew* m0 : meshes)
    {
        m0->setPrefix(name);
        m0->updateNames();
    }
    return true;
}

void Session::selectVert(GLint hits, GLuint *names, GLdouble posX, GLdouble posY, GLdouble posZ){
    if(hits > 0) {
        glm::vec3 hit_position = glm::vec3(posX, posY, posZ);
        float min_distance = std::numeric_limits<float>::max();
        Vert * selectedVertex = NULL;
        Reader* currReader = createReader(this);

        for (int i = 0; i < hits; i++) {
            int currentID = names[i * 4 + 3];

            Vert * currentVertex = currReader->getVert(currentID);

            if (currentVertex != NULL){
                glm::vec3 vertex_position = glm::vec3(*(currentVertex->x), *(currentVertex->y), *(currentVertex->z));

                float new_distance = distance(vertex_position, hit_position);

                if(new_distance < min_distance) {
                    min_distance = new_distance;
                    selectedVertex = currentVertex;
                }
            }
        }
        if (selectedVertex != NULL){
            selectedVertex -> selected = !selectedVertex -> selected;
            if (selectedVertex -> selected == true){
                selectedVerts.push_back(selectedVertex);
            }
            else{
                selectedVerts.remove(selectedVertex);
            }
        }

    }
}

void Session::selectEdge(GLint hits, GLuint *names, GLdouble posX, GLdouble posY, GLdouble posZ){
    if(hits > 0) {
        glm::vec3 hit_position = glm::vec3(posX, posY, posZ);
        float min_distance = std::numeric_limits<float>::max();
        Reader* currReader = createReader(this);
        EdgeNew * currentEdge;
        EdgeNew * selectedEdge;

        for (int i = 0; i < hits; i++) {
            int currentID = names[i * 4 + 3];
            currentEdge = currReader->edge(currentID);
            if (currentEdge != NULL){
                std::cout << currentEdge->name << std::endl;
                //selectedFace = currentFace;
            }
        }

        //selectedFace -> selected = !selectedFace -> selected;
    }
}

void Session::selectFace(GLint hits, GLuint *names, GLdouble posX, GLdouble posY, GLdouble posZ){
    if(hits > 0) {
        glm::vec3 hit_position = glm::vec3(posX, posY, posZ);
        float min_distance = std::numeric_limits<float>::max();
        Reader* currReader = createReader(this);
        FaceNew * currentFace;
        FaceNew * selectedFace;

        for (int i = 0; i < hits; i++) {
            int currentID = names[i * 4 + 3];
            currentFace = currReader->getFace(currentID);
            if (currentFace != NULL){
                std::cout << currentFace->name << std::endl;
                selectedFace = currentFace;
                break;
            }
        }

        if (selectedFace != NULL){
            selectedFace -> selected = !selectedFace -> selected;
            if (selectedFace -> selected == true){
                selectedFaces.push_back(selectedFace);
            }
            else{
                selectedFaces.remove(selectedFace);
            }
        }
    }
}

void Session::SaveSession(std::string outputFile){
    ofstream file(outputFile);
    if (!file.is_open())
    {
        cout <<"Error: COULD NOT OPEN THE FILE.\n";
    }

    file<< this->fileContent;

}

void Session::addTmpFace(){
    if (tmpMesh == NULL){
        tmpMesh = createMesh();
        tmpFaceIndex = 0;
    }
    FaceNew * newFace = createFace(selectedVerts, &(tmpMesh->edges));
    setTmpSurface(newFace);

    newFace->setName("f" + std::to_string(tmpFaceIndex));

    tmpMesh->faces.push_back(newFace);
    for (Vert * selectedVert: selectedVerts){
        tmpMesh->verts.push_back(selectedVert);
    }
    tmpMesh->setName("tmpMesh");
    tmpInstance = createInstance(tmpMesh, this->verts);
    tmpInstance->setName("tmpInstance");
    clearSelection();
    tmpFaceIndex += 1;
}

void Session::addTmpPolyline(){
    tmpPolyline = createPolylineNew(selectedVerts);
    tmpPolyline->setName("tmpPolyline");
    tmpInstance = createInstance(tmpPolyline, this->verts);
    tmpInstance->setName("tmpInstance");
    clearSelection();
}

void Session::consolidateTmpMesh(std::string consolidateInstanceName, std::string consolidateMeshName){
    Reader* currReader = createReader(this);
    if (tmpInstance != NULL){
        for (FaceNew * tmpFace: tmpInstance->faces){
            setSurface(tmpFace, NULL);
        }
    }
    if (tmpPolyline != NULL){
        tmpPolyline->setName(consolidateMeshName);
        polylines.push_back(tmpPolyline);
        this->fileContent += "\npolyline " + consolidateMeshName + " (";

        for (Vert* currVert : tmpPolyline->verts){
            this->fileContent += currReader->getVertName(currVert->index) + " ";
        }

        this->fileContent += ") endpolyline\n";
    }
    if (tmpMesh != NULL){
        tmpMesh->setName(consolidateMeshName);
        meshes.push_back(tmpMesh);
        this->fileContent += "\nmesh " + consolidateMeshName + "\n";
        for (FaceNew * currFace : tmpMesh->faces){
            this->fileContent += "face " + currFace->name + " (";
            for (Vert* currVert : currFace->verts){
                this->fileContent += currReader->getVertName(currVert->index) + " ";
            }
            this->fileContent += ") endface\n";
        }
        this->fileContent += "endmesh\n";
    }
    if (tmpInstance != NULL){
        tmpInstance->setName(consolidateInstanceName);
        instances.push_back(tmpInstance);
        this->fileContent += "instance " + consolidateInstanceName + " " + consolidateMeshName + " endinstance";
    }

    tmpMesh = NULL;
    tmpInstance = NULL;
    tmpPolyline = NULL;


    clearSelection();
}


void Session::clearSelection(){
    for (Vert * selectedVert: selectedVerts){
        selectedVert->selected = !selectedVert->selected;
    }

    for (FaceNew * selectedFace: selectedFaces){
        selectedFace->selected = !selectedFace->selected;
    }

    selectedFaces.clear();
    selectedVerts.clear();
}

void Session::saveFileToStr(string fileName){
    ifstream inFile;
    inFile.open(fileName.c_str());//open the input file

    stringstream strStream;
    strStream << inFile.rdbuf();//read the file
    string str = strStream.str();
    this->fileContent = str;
}

void Session::deleteFace(){
    Reader* currReader = createReader(this);
    this->fileContent += "\ndelete\n";
    for (FaceNew* selectedFace : selectedFaces){
        this->fileContent += "face " + currReader->getFaceName(selectedFace->index) + " endface\n";
        currReader->deleteFace(selectedFace);
    }
    this->fileContent += "enddelete\n";
    clearSelection();
}
