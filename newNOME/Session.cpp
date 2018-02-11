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

#include "bankFlexBison.cpp"

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
    //std::cout << hits << std::endl;
    if(hits > 0) {
        glm::vec3 hit_position = glm::vec3(posX, posY, posZ);
        float min_distance = std::numeric_limits<float>::max();
        Vert * selectedVertex = NULL;
        Reader* currReader = createReader(this);

        for (int i = 0; i < hits; i++) {
            int currentID = names[i * 4 + 3];
            Vert * currentVertex = currReader->getVert(currentID);

            //std::cout << "+++" << std::endl;
            //std::cout << currentVertex << std::endl;
            if (currentVertex != NULL){
                //std::cout << "HELLO" << std::endl;
                //std::cout << currentVertex->name << std::endl;
                glm::vec3 vertex_position = glm::vec3(*(currentVertex->x), *(currentVertex->y), *(currentVertex->z));

                float new_distance = distance(vertex_position, hit_position);

                if(new_distance < min_distance) {
                    min_distance = new_distance;
                    selectedVertex = currentVertex;
                }
            }
        }

        if (selectedVertex != NULL){
            /*std::cout << "GGGGG" << std::endl;
            std::cout << selectedVertex->index << std::endl;*/
            //std::cout << currReader->getVertName(selectedVertex->index) << std::endl;
            //std::cout << selectedVertex->faces.size() << std::endl;
            std::cout << currReader->getVertName(selectedVertex->index) << std::endl;

            selectedVertex -> selected = !selectedVertex -> selected;

            if (selectedVertex -> selected == true){
                selectedVerts.push_back(selectedVertex);
            }
            else{
                selectedVerts.remove(selectedVertex);
            }
        }

    }
    std::cout << "CLICKED ON SCREEN!" << std::endl;
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
                currentEdge->v0->selected = false;
                currentEdge->v1->selected = false;
                selectedEdges.push_back(currentEdge);
                //selectedFace = currentFace;
            }
        }

        //selectedFace -> selected = !selectedFace -> selected;
    }
}

void Session::selectBorder(GLint hits, GLuint *names, GLdouble posX, GLdouble posY, GLdouble posZ){
    std::cout << "CLICKED" << std::endl;
    std::cout << hits << std::endl;
    vector<Vert*> selectedVertsLoop = vector<Vert*>();

    if(hits > 0) {
        glm::vec3 hit_position = glm::vec3(posX, posY, posZ);
        float min_distance = std::numeric_limits<float>::max();
        Reader* currReader = createReader(this);
        Vert * startVert;
        Vert * selectedEdge;

        for (int i = 0; i < hits; i++) {
            int currentID = names[i * 4 + 3];
            startVert = currReader->getVert(currentID);
            //std::cout << "currentEdge->name" << std::endl;
            if (startVert != NULL){
                selectedVertsLoop = findLoop(startVert, selectedVertsLoop);
                //selectedFace = currentFace;
            }
        }
        //selectedFace -> selected = !selectedFace -> selected;
    }
}

std::vector<Vert*> Session::findLoop(Vert* startVert, std::vector<Vert*> selectedVertsLoop){
    for (EdgeNew* currEdge : startVert->edges){
        if (currEdge->isBorder()){
            currEdge->v0->selected = true;
            currEdge->v1->selected = true;
            selectedVertsLoop.push_back(startVert);
            selectedEdges.push_back(currEdge);
        }

    }
    return selectedVertsLoop;
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

static std::string dbl2str(double d)
{
    size_t len = std::snprintf(0, 0, "%.10f", d);
    std::string s(len+1, 0);
    // technically non-portable, see below
    std::snprintf(&s[0], len+1, "%.10f", d);
    // remove nul terminator
    s.pop_back();
    // remove trailing zeros
    s.erase(s.find_last_not_of('0') + 1, std::string::npos);
    // remove trailing point
    if(s.back() == '.') {
        s.pop_back();
    }
    return s;
}

void Session::SaveSessionNom(std::string outputFile){
    int offset = 0;
    for (BankNew * b0 : banks){
        for (SetNew * s0 : b0->sets){
            this->fileContent.replace(s0->begValPosFile + offset, s0->lengthValChar, dbl2str(s0->value));
            offset += dbl2str(s0->value).length() - s0->lengthValChar;
        }
    }

    ofstream file(outputFile);
    if (!file.is_open())
    {
        cout <<"Error: COULD NOT OPEN THE FILE.\n";
    }

    file<< this->fileContent;
}

void Session::addTmpFace(){
    if (selectedVerts.size() != 0){
        if (tmpMesh == NULL){
            tmpMesh = createMesh();
            tmpFaceIndex = 0;
        }
        Reader* currReader = createReader(this);
        FaceNew * newFace = createFace(selectedVerts, &(tmpMesh->edges), currReader, false);

        setTmpSurface(newFace);

        newFace->setName("f" + std::to_string(tmpFaceIndex));

        tmpMesh->faces.push_back(newFace);
        for (Vert * selectedVert: selectedVerts){
            tmpMesh->verts.push_back(selectedVert);
        }
        tmpMesh->setName("tmpMesh");

        tmpInstance = createInstance(tmpMesh, this->verts, currReader, false, true, false, this);
        tmpInstance->setName("tmpInstance");
        clearSelection();
        tmpFaceIndex += 1;
    }

    /*if (tmpMesh == NULL){
        tmpMesh = createMesh();
        tmpFaceIndex = 0;
    }
    Reader* currReader = createReader(this);
    FaceNew * newFace = createFace(selectedVerts, &(tmpMesh->edges), currReader, false);

    setTmpSurface(newFace);
    newFace->setName("f" + std::to_string(tmpFaceIndex));
    tmpMesh->faces.push_back(newFace);

    for (Vert * selectedVert: selectedVerts){
        tmpMesh->verts.push_back(selectedVert);
    }
    tmpMesh->setName("tmpMesh");
    tmpInstance = createInstance(tmpMesh, this->verts, currReader, false, true, false, this);
    tmpInstance->setName("tmpInstance");
    clearSelection();
    tmpFaceIndex += 1;*/
}

void Session::addTmpPolyline(){
    /*Reader* currReader = createReader(this);
    tmpPolyline = createPolylineNew(selectedVerts);
    tmpPolyline->setName("tmpPolyline");
    tmpInstance = createInstance(tmpPolyline, this->verts, currReader, false, true, false, this);
    tmpInstance->setName("tmpInstance");
    clearSelection();*/
    if (selectedVerts.size() != 0){
        Reader* currReader = createReader(this);
        tmpPolyline = createPolylineNew(selectedVerts);
        tmpPolyline->setName("tmpPolyline");
        tmpInstance = createInstance(tmpPolyline, this->verts, currReader, false, true, false, this);
        tmpInstance->setName("tmpInstance");
        clearSelection();
    }
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

        InstanceNew* newInstance;
        if (tmpMesh != NULL){
            newInstance = createInstance(tmpMesh, this->verts, currReader, true, true, false, this);
        } else{
            newInstance = createInstance(tmpPolyline, this->verts, currReader, true, true, false, this);
        }

        newInstance->setName(consolidateInstanceName);
        for (FaceNew * tmpFace: newInstance->faces){
            setSurface(tmpFace, NULL);
        }

        instances.push_back(newInstance);

        //instances.push_back(tmpInstance);
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

    for (EdgeNew * selectedEdge: selectedEdges){
        selectedEdge->v0->selected = false;
        selectedEdge->v1->selected = false;
    }


    for (FaceNew * selectedFace: selectedFaces){
        selectedFace->selected = !selectedFace->selected;
    }

    selectedFaces.clear();
    selectedVerts.clear();
    selectedEdges.clear();

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

void Session::draw(){
    //std::cout << "DRAW" << std::endl;
    for (std::list<InstanceNew*>::iterator itMesh = instances.begin(); itMesh != instances.end(); itMesh++){
        //std::cout << "TRUE INSTANCE" << std::endl;
        //std::cout << (*itMesh)->name << std::endl;
        (*itMesh)->draw();
    }

    if (tmpInstance != NULL){
        //std::cout << "TMP INSTANCE" << std::endl;
        tmpInstance->draw();
    }
}

void Session::createFlattenMesh(bool instance){
    MeshNew* tmpflattenMesh = createMesh();
    if (instance){
        //std::cout << "INSTANCE" << std::endl;
        for (std::list<InstanceNew*>::iterator itMesh = instances.begin(); itMesh != instances.end(); itMesh++){
            (*itMesh)->flattenInstance(tmpflattenMesh);
        }
    }
    else{
        tmpflattenMesh = flattenMesh;
    }

    //std::cout << "SUCCESS" << std::endl;
    // http://www.rorydriscoll.com/2008/08/01/catmull-clark-subdivision-the-basics/
    // STEP 1: Calculate face points.
    for (FaceNew* currFace : tmpflattenMesh->faces){
        currFace->calculateFacePoint();
    }
    for (EdgeNew* currEdge : tmpflattenMesh->edges){
        currEdge->calculateEdgePoint();
    }

    for (Vert* currVert : tmpflattenMesh->verts){
        currVert->calculateVertPoint();
    }
    flattenMesh = tmpflattenMesh;
}

void Session::drawSubdivide(int subdivision, int previousSubdivisionLevel, double offset, bool calculateOffset, bool calculateSubdivide, bool calculateSlider){

    /*if (!calculateOffset && !calculateSubdivide){
        for (FaceNew* f : flattenMesh->inFaces){
            drawFace(f, NULL);
        }
        for (FaceNew* f : flattenMesh->outFaces){
            drawFace(f, NULL);
        }
        for (FaceNew* f : flattenMesh->faces){
            drawFace(f, NULL);
        }
        return;
    }*/



    if (calculateSubdivide){
        if ((flattenMeshList.size() != 0) && (flattenMeshList.size() >= subdivision + 1)){
            flattenMesh = flattenMeshList[subdivision];
        } else{
            int startIndex = 0;
            if ((flattenMeshList.size() != 0)){
                std::cout << flattenMeshList.size() - 1 << std::endl;
                startIndex = flattenMeshList.size() - 1;
            } else{
                createFlattenMesh(true);
                flattenMeshList.push_back(flattenMesh);
            }

            for (int i = startIndex; i < subdivision; i++){
                createFlattenMesh(false);
                flattenMesh = flattenMesh->subdivideMesh();
                flattenMeshList.push_back(flattenMesh);
            }
        }

        subdivisionLevel = subdivision;
    }

    flattenMesh->calculateNormal();

    flattenMesh->draw(offset);

}

void saveFaceSTL(FaceNew* currFace, std::ofstream& file){
    std::vector<double> normalVector = currFace->getNormal();
    std::list<Vert*>::iterator itVert = currFace->verts.begin();

    Vert* initVertex = *itVert;
    itVert++;
    Vert* currVertex = *itVert;
    itVert++;
    Vert* lastVert = *itVert;

    while (itVert != currFace->verts.end()){

        lastVert = *itVert;
        std::vector<Vert *> vL;
        vL.push_back(initVertex);
        vL.push_back(currVertex);
        vL.push_back(lastVert);
        std::vector<double> nV = getNormalFromVerts(vL);
        file << "  facet normal " + dbl2str(nV[0]) + " " + dbl2str(nV[1]) + " " + dbl2str(nV[2]) + "\n";
        file << "    outer loop\n";
        file << "      vertex " + dbl2str(roundf(*(initVertex->xTransformed) * 10000) / 10000) + " " + dbl2str(roundf(*(initVertex->yTransformed) * 10000) / 10000) + " " + dbl2str(roundf(*(initVertex->zTransformed) * 10000) / 10000) + "\n";
        file << "      vertex " + dbl2str(roundf(*(currVertex->xTransformed) * 10000) / 10000) + " " + dbl2str(roundf(*(currVertex->yTransformed) * 10000) / 10000) + " " + dbl2str(roundf(*(currVertex->zTransformed) * 10000) / 10000) + "\n";
        file << "      vertex " + dbl2str(roundf(*(lastVert->xTransformed) * 10000) / 10000) + " " + dbl2str(roundf(*(lastVert->yTransformed) * 10000) / 10000) + " " + dbl2str(roundf(*(lastVert->zTransformed) * 10000) / 10000) + "\n";
        file << "    endloop\n";
        file << "  endfacet\n";

        currVertex = lastVert;
        itVert++;
    }
}

void Session::SaveSessionStl(std::string outputFile){
    ofstream file(outputFile);
    if (!file.is_open())
    {
        cout <<"Error: COULD NOT OPEN THE FILE.\n";
    }

    if (flattenMesh == NULL){
        createFlattenMesh(true);
    }

    file << "solid convertedFile\n";
    if (flattenMesh->inFaces.size() == 0){
        for (FaceNew * currFace : flattenMesh->faces){
            saveFaceSTL(currFace, file);
        }
    }
    else{
        for (FaceNew * currFace : flattenMesh->inFaces){
            saveFaceSTL(currFace, file);
        }

        for (FaceNew * currFace : flattenMesh->outFaces){
            saveFaceSTL(currFace, file);
        }
    }

    file<< "endsolid convertedFile";
}

void parseGetBankVal(const char* input, Session* sessionParse, double* output, int lineNumber){
    //std::cout << "AAA" << std::endl;
    BankCompiler* bankCompilerSession = new BankCompiler (input, sessionParse, output, lineNumber);
    //std::cout << "BBB" << std::endl;
    //*output = bankCompilerSession->getResult();
}
