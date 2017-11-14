//
//  Data.cpp
//  model
//
//  Created by L on 26/08/2017.
//  Copyright © 2017 L. All rights reserved.
//


#include "Data.h"
#include "Reader.h"
#include <glm/vec3.hpp> // glm::vec3

QColor defaultColor = QColor(255, 0, 0);
QColor tmpColor = QColor(255, 255, 0);



///Indices for data instantiation
static int vIndex = 0;
static int eIndex = 0;
static int fIndex = 0;

///Global locks for instancing - in case one day want to multithread
static std::mutex vertLock;
static std::mutex edgeLock;
static std::mutex faceLock;

///Surfaces
Surface* createSurface(double *r, double *g, double *b, std::string name)
{
    Surface * surface0 = new Surface();
    surface0->r = r;
    surface0->g = g;
    surface0->b = b;
    surface0->color = QColor(255 * *r, 255 * *g, 255 * *b);
    surface0->name = name;
    return surface0;
}

QColor Surface::getColor(){
    color = QColor(255 * *r, 255 * *g, 255 * *b);
    return color;
}

///Vertex functions
///Create a default vert, will be at the origin with weight of 1.0
Vert* createVert()
{
    double *x = (double*) malloc(sizeof(double));
    double *y = (double*) malloc(sizeof(double));
    double *z = (double*) malloc(sizeof(double));

    *x = 0.0;
    *y = 0.0;
    *z = 0.0;

    return createVert(x, y, z, 1.0);
}

///Create a vert with specified x, y, z values without having to specify a weight
Vert* createVert(double *x, double *y, double *z)
{
    return createVert(x, y, z, 1.0);
}

///Create a weighted vert at x, y, z value
Vert* createVert(double *x, double *y, double *z, double w)
{
    Vert* v0 = new Vert();
    v0->selected = false;
    vertLock.lock();
    int index = vIndex;
    vIndex++;
    vertLock.unlock();

    v0->index = index;
    v0->setName("v:" + std::to_string(index));
    v0->x = x;
    v0->y = y;
    v0->z = z;

    double *xTr = (double*) malloc(sizeof(double));
    double *yTr = (double*) malloc(sizeof(double));
    double *zTr = (double*) malloc(sizeof(double));
    *xTr = *x;
    *yTr = *y;
    *zTr = *z;
    v0->xTransformed = xTr;
    v0->yTransformed = yTr;
    v0->zTransformed = zTr;

    v0->weight = w;
    std::list<EdgeNew*> edges; std::list<FaceNew*> faces;
    v0->edges = edges; v0->faces = faces;
    
    return v0;
}

Vert* createVert(Vert* toBeCopied){
    double *x = (double*) malloc(sizeof(double));
    double *y = (double*) malloc(sizeof(double));
    double *z = (double*) malloc(sizeof(double));

    x = toBeCopied->x;
    y = toBeCopied->y;
    z = toBeCopied->z;

    return createVert(x, y, z, 1.0);
}

///Edge functions
///Create an edge by specifying two points and knot interval, will create the links for the edge
///Currently assume manifold, so an edge shouldn't need more than two links
EdgeNew* createEdge(Vert* v0, Vert* v1, double interval)
{
    EdgeNew* e0 = new EdgeNew();
    e0->isBorder = false;
    
    e0->interval = interval;
    edgeLock.lock();
    int index = eIndex;
    eIndex++;
    edgeLock.unlock();

    e0->v0 = v0;
    e0->v1 = v1;
    e0->index = index;
    e0->setName("e:" + std::to_string(index));
    e0->faceCount = 0;
    e0->vertCount = 0;
    
    v0->edges.push_back(e0); v1->edges.push_back(e0);

    return e0;
}

///Create edge without specifying knot interval, default to 1.0
EdgeNew* createEdge(Vert* v0, Vert* v1)
{
    return createEdge(v0, v1, 1.0);
}

///Lazy construct, create edge without prior verts
EdgeNew* createEdge(double x0, double y0, double z0, double x1, double y1, double z1, double interval)
{
    Vert* v0 = createVert(&x0, &y0, &z0); Vert* v1 = createVert(&x1, &y1, &z1);
    return createEdge(v0, v1, interval);
}

///Face functions
///Create face helper function
FaceNew* createFace()
{
    FaceNew* f0 = new FaceNew();
    f0->selected = false;
    std::list<EdgeNew*> edges; std::list<Vert*> verts;
    f0->edges = edges; f0->verts = verts;
    
    faceLock.lock();
    int index = fIndex;
    fIndex++;
    faceLock.unlock();
    
    f0->index = index;
    f0->setName("f:" + std::to_string(index));
    return f0;
}

FaceNew* createFace(std::list<Vert*> vertices, std::list<EdgeNew*> *edges, Reader * currReader){
    EdgeNew * currentEdge;
    std::list<Vert*>::iterator it = vertices.begin();
    std::list<Vert*>::iterator it2 = vertices.begin();
    std::list<EdgeNew*> currentEdges;
    ++it2;

    while (it != vertices.end()){
        if (it2 != vertices.end()){
            currentEdge = NULL;
            for( auto e0 : *edges ) {
                if ((e0->v0->index == (*it)->index && e0->v1->index == (*it2)->index) || (e0->v0->index == (*it2)->index && e0->v1->index == (*it)->index)){
                    currentEdge = e0;
                }
            }
            //std::cout << currReader->getEdge((*it)->index, (*it2)->index) << std::endl;

            if (currentEdge == NULL){
                currentEdge = createEdge(*it, *it2);
            }
            it2++;
        }
        else{
            currentEdge = NULL;
            for( auto e0 : *edges ) {
                if ((e0->v0->index == vertices.back()->index && e0->v1->index == vertices.front()->index) || (e0->v0->index == vertices.front()->index && e0->v1->index == vertices.back()->index)){
                    currentEdge = e0;
                }
            }

            if (currentEdge == NULL){
                currentEdge = createEdge(vertices.back(), vertices.front());
            }
        }
        it++;

        edges->push_back(currentEdge);
        currentEdges.push_back(currentEdge);
        currentEdge = NULL;
    }


    FaceNew* newFace = createFace(currentEdges, vertices);
    /*newFace->verts.clear();

    for (Vert* vert : vertices){
        newFace->verts.push_back(vert);
    }*/

    return newFace;
}

///Create face given a vector of at least three edges, the edges must be adjacent and form a closed loop, otherwise fails
FaceNew* createFace(std::list<EdgeNew*> edges, std::list<Vert*> verts)
{
    FaceNew* f0 = createFace();
    f0->selected = false;
    std::vector<Vert*> vIndex;

    //Check if more than three edges are given
    if(edges.size() < 3)
    {
        errorMessage("Fewer than 3 edges given", -1);
        return NULL;
    }

    std::list<Vert*>::iterator vertsIt = verts.begin();
    for( EdgeNew* edge : edges )
    {
        if (edge->f0 == NULL){
            edge->f0 = f0;
        }
        else{
            edge->f1 = f0;
        }

        bool b0 = false, b1 = false;
        for( int i = 0; i < vIndex.size(); i++ )
        {
            b0 = b0 | (vIndex[i]->index == edge->v0->index);
            b1 = b1 | (vIndex[i]->index == edge->v1->index);
        }

        if ((*vertsIt)->index == edge->v0->index){
            if( !b0 ) {
                bool found = (std::find(f0->verts.begin(), f0->verts.end(), edge->v0) != f0->verts.end());
                if (!found){
                    f0->verts.push_back(edge->v0);
                    vIndex.push_back(edge->v0);
                }
            }
            if( !b1 ) {
                bool found = (std::find(f0->verts.begin(), f0->verts.end(), edge->v1) != f0->verts.end());
                if (!found){
                    f0->verts.push_back(edge->v1);
                    vIndex.push_back(edge->v1);
                }
            }
        } else{
            if( !b1 ) {
                bool found = (std::find(f0->verts.begin(), f0->verts.end(), edge->v1) != f0->verts.end());
                if (!found){
                    f0->verts.push_back(edge->v1);
                    vIndex.push_back(edge->v1);
                }
            }

            if( !b0 ) {
                bool found = (std::find(f0->verts.begin(), f0->verts.end(), edge->v0) != f0->verts.end());
                if (!found){
                    f0->verts.push_back(edge->v0);
                    vIndex.push_back(edge->v0);
                }
            }
        }
        vertsIt++;

        f0->edges.push_back(edge);
        
        //Check if an edge has more than two adjacent faces
        if( edge->faceCount == 0 )
        {
            edge->f0 = f0;
            edge->faceCount = 1;
        }
        else if (edge->faceCount == 1)
        {
            edge->f1 = f0;
            edge->faceCount = 2;
        }
        else
        {
            errorMessage("Invalid edges given for a face, edges can be adjacent to at most 2 faces.", -1);
            return NULL;
        }
    }

    //Check if edges given are adjacent
    if( vIndex.size() != edges.size() )
    {
        errorMessage("Edges given are not all adjacent", -1);
        return NULL;
    }
    //Add reference to the face for all the vertices in the face
    for( Vert* vert: vIndex )
        vert->faces.push_back(f0);

    return f0;
}

bool setName(Vert* v0, std::string n)
{
    return v0->setName(n);
}

bool setName(EdgeNew* e0, std::string n)
{
    return e0->setName(n);
}

bool setName(FaceNew* f0, std::string n)
{
    return f0->setName(n);
}


bool setSurface(FaceNew* f0, Surface* surface){
    f0->surface = surface;
    return true;
}

bool setTmpSurface(FaceNew* f0){
    double *r = (double*) malloc(sizeof(double));
    double *g = (double*) malloc(sizeof(double));
    double *b = (double*) malloc(sizeof(double));

    *r = 1.0;
    *g = 1.0;
    *b = 0.0;
    Surface * tmpSurface = createSurface(r, g, b, "tmpSurface");
    f0->surface = tmpSurface;
    return true;
}

///Deletion functions
///When a vertex is deleted, the adjacent edges and faces are also deleted
bool deleteVert(Vert* vert)
{
    if (!vert)
        return false;
    for(EdgeNew* e : vert->edges)
    {
        deleteEdge(e);
    }
    for(FaceNew* f : vert->faces)
    {
        deleteFace(f);
    }
    vert->edges.clear(); vert->faces.clear();
    return vert->edges.empty() && vert->faces.empty();
}

///When an edge is deleted, the two end verts are deleted as are the two adjacent faces
bool deleteEdge(EdgeNew* edge)
{
    if(!edge)
        return false;
    if(edge->vertCount == 2)
    { deleteVert(edge->v0); deleteVert(edge->v1); edge->vertCount = 0; }
    else if (edge->vertCount == 1)
    { deleteVert(edge->v0); edge->vertCount = 0; }
    if(edge->faceCount == 2)
    { deleteFace(edge->f0); deleteFace(edge->f1); edge->faceCount = 0; }
    else if (edge->faceCount == 1)
    { deleteFace(edge->f0); edge->faceCount = 0; }
    return edge->vertCount == 0 && edge->faceCount == 0;
}

///When a face is deleted, the neighbouring edges and vertices are not
bool deleteFace(FaceNew* face)
{
    if(!face)
        return false;
    for(Vert* v0 : face->verts)
    {
        v0->faces.remove(face);
    }
    for(EdgeNew* e0 : face->edges)
    {
        if(e0->f0 == face)
        { e0->f0 = e0->f1; e0->faceCount = 1; }
        else if(e0->f1 == face)
        { e0->faceCount = 1; }
    }
    face->edges.clear(); face->verts.clear();
    return face->edges.empty() && face->verts.empty();
}

bool drawVert(Vert* v0, Surface * instSurface){
    QColor color;
    if (instSurface != NULL){
        color = instSurface->color;
    } else {
        color = defaultColor;
    }


    GLfloat fcolor[4] = {0,0,0,0};
    if (v0->selected){
        fcolor[0] = 0;
        fcolor[1] = 1;
        fcolor[2] = 1;
        fcolor[3] = 0;
    } else {
        fcolor[0] = 1.0f * color.red() / 255;
        fcolor[1] = 1.0f * color.green() / 255;
        fcolor[2] = 1.0f * color.blue() / 255;
        fcolor[3] = 1.0f * color.alpha() /255;
    }

    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, fcolor);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, fcolor);

    glLoadName(v0->index);

    float x = *v0->xTransformed;
    float y = *v0->yTransformed;
    float z = *v0->zTransformed;
    glBegin(GL_QUADS);
        glNormal3f(0, 0, 1);
        glVertex3f(x + 0.1 / 2, y + 0.1 / 2, z);
        glVertex3f(x - 0.1 / 2, y + 0.1 / 2, z);
        glVertex3f(x - 0.1 / 2, y - 0.1 / 2, z);
        glVertex3f(x + 0.1 / 2, y - 0.1 / 2, z);
    glEnd();
    glBegin(GL_QUADS);
        glNormal3f(1, 0, 0);
        glVertex3f(x, y + 0.1 / 2, z + 0.1 / 2);
        glVertex3f(x, y - 0.1 / 2, z + 0.1 / 2);
        glVertex3f(x, y - 0.1 / 2, z - 0.1 / 2);
        glVertex3f(x, y + 0.1 / 2, z - 0.1 / 2);
    glEnd();
    glBegin(GL_QUADS);
        glNormal3f(0, 1, 0);
        glVertex3f(x + 0.1 / 2, y, z - 0.1 / 2);
        glVertex3f(x + 0.1 / 2, y, z + 0.1 / 2);
        glVertex3f(x - 0.1 / 2, y, z + 0.1 / 2);
        glVertex3f(x - 0.1 / 2, y, z - 0.1 / 2);
    glEnd();
    return true;
}

bool drawEdge(EdgeNew* e0, Surface * instSurface)
{
    QColor color;
    if (instSurface != NULL){
        color = instSurface->color;
    } else{
        color = defaultColor;
    }

    GLfloat fcolor[] = {1.0f * color.red() / 255,
                        1.0f * color.green() / 255,
                        1.0f * color.blue() / 255,
                        1.0f * color.alpha() /255};


    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, fcolor);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, fcolor);
    glLoadName(e0->index);
    glBegin(GL_LINE_STRIP);
        glVertex3f(*e0->v0->xTransformed, *e0->v0->yTransformed, *e0->v0->zTransformed);
        glVertex3f(*e0->v1->xTransformed, *e0->v1->yTransformed, *e0->v1->zTransformed);
    glEnd();
    return true;
}

std::vector<double> FaceNew::getNormal(){
    std::list<Vert*>::iterator it = this->verts.begin();

    std::vector<Vert*> vert1;
    vert1.push_back(*it);
    it++;
    vert1.push_back(*it);
    it++;
    vert1.push_back(*it);


    std::vector<double> a;
    a.push_back(*(vert1[0]->xTransformed) - *(vert1[1]->xTransformed));
    a.push_back(*(vert1[0]->yTransformed) - *(vert1[1]->yTransformed));
    a.push_back(*(vert1[0]->zTransformed) - *(vert1[1]->zTransformed));

    std::vector<double> b;
    b.push_back(*(vert1[2]->xTransformed) - *(vert1[1]->xTransformed));
    b.push_back(*(vert1[2]->yTransformed) - *(vert1[1]->yTransformed));
    b.push_back(*(vert1[2]->zTransformed) - *(vert1[1]->zTransformed));

    double xCross = -10*(a[1]*b[2] - a[2]*b[1]);
    double yCross = -10*(a[2]*b[0] - a[0]*b[2]);
    double zCross = -10*(a[0]*b[1] - a[1]*b[0]);
    double norm = sqrt(pow(xCross, 2) + pow(yCross, 2) + pow(zCross, 2));

    std::vector<double> aCrossb;
    aCrossb.push_back(xCross / norm);
    aCrossb.push_back(yCross / norm);
    aCrossb.push_back(zCross / norm);

    return aCrossb;
}

bool drawFace(FaceNew* f0, Surface * instSurface)
{
    QColor color;
    if (instSurface != NULL){
        color = instSurface->getColor();
    }
    else if (f0->surface != NULL){
        color = f0->surface->getColor();
    } else{
        color = defaultColor;
    }

    GLfloat fcolor[4] = {0,0,0,0};
    if (f0->selected){
        fcolor[0] = 0;
        fcolor[1] = 1;
        fcolor[2] = 1;
        fcolor[3] = 0;
    } else {
        fcolor[0] = 1.0f * color.red() / 255;
        fcolor[1] = 1.0f * color.green() / 255;
        fcolor[2] = 1.0f * color.blue() / 255;
        fcolor[3] = 1.0f * color.alpha() /255;
    }

    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, fcolor);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, fcolor);
    glLoadName(f0->index);

    std::vector<double> normalVector = f0->getNormal();

    glBegin(GL_POLYGON);
    glNormal3f(normalVector[0], normalVector[1], normalVector[2]);
    for(auto v0 : f0->verts) {
      glVertex3f(*v0->xTransformed, *v0->yTransformed, *v0->zTransformed);
    }
    glEnd();

    return true;
}

void EdgeNew::calculateEdgePoint(){
    double *xEdgePoint = (double*) malloc(sizeof(double));
    double *yEdgePoint = (double*) malloc(sizeof(double));
    double *zEdgePoint = (double*) malloc(sizeof(double));
    *xEdgePoint = 0;
    *yEdgePoint = 0;
    *zEdgePoint = 0;

    //Check if it is on a border.
    if (this->f1 != NULL){
        *xEdgePoint = (*this->f0->facePoint->x + *this->f1->facePoint->x + *this->v0->xTransformed + *this->v1->xTransformed) / 4.0;
        *yEdgePoint = (*this->f0->facePoint->y + *this->f1->facePoint->y + *this->v0->yTransformed + *this->v1->yTransformed) / 4.0;
        *zEdgePoint = (*this->f0->facePoint->z + *this->f1->facePoint->z + *this->v0->zTransformed + *this->v1->zTransformed) / 4.0;
    }
    else{
        *xEdgePoint = (*this->v0->xTransformed + *this->v1->xTransformed) / 2.0;
        *yEdgePoint = (*this->v0->yTransformed + *this->v1->yTransformed) / 2.0;
        *zEdgePoint = (*this->v0->zTransformed + *this->v1->zTransformed) / 2.0;
    }

    this->edgePoint = createVert (xEdgePoint, yEdgePoint, zEdgePoint);
}

void FaceNew::calculateFacePoint(){
    // Takes the average of all the point on the face.
    double *xFacePoint = (double*) malloc(sizeof(double));
    double *yFacePoint = (double*) malloc(sizeof(double));
    double *zFacePoint = (double*) malloc(sizeof(double));
    *xFacePoint = 0;
    *yFacePoint = 0;
    *zFacePoint = 0;


    for (Vert * currVert : this->verts){
        *xFacePoint += *currVert->xTransformed;
        *yFacePoint += *currVert->yTransformed;
        *zFacePoint += *currVert->zTransformed;
    }

    *xFacePoint = *xFacePoint / this->verts.size();
    *yFacePoint = *yFacePoint / this->verts.size();
    *zFacePoint = *zFacePoint / this->verts.size();


    this->facePoint = createVert (xFacePoint, yFacePoint, zFacePoint);
}

void Vert::calculateVertPoint(){
    double Rx = 0;
    double Ry = 0;
    double Rz = 0;

    double n;

    double Sx = *xTransformed;
    double Sy = *yTransformed;
    double Sz = *zTransformed;

    double *xVertPoint = (double*) malloc(sizeof(double));
    double *yVertPoint = (double*) malloc(sizeof(double));
    double *zVertPoint = (double*) malloc(sizeof(double));
    if (faces.size() != edges.size()){
        n = 0;
        Rx = 0;
        Ry = 0;
        Rz = 0;
        for (EdgeNew* currEdge : edges){
            if (currEdge->f1 == NULL){
                Rx += (*currEdge->v0->x + *currEdge->v1->x) / 2.0;
                Ry += (*currEdge->v0->y + *currEdge->v1->y) / 2.0;
                Rz += (*currEdge->v0->z + *currEdge->v1->z) / 2.0;
                n++;
            }
        }

        *xVertPoint = (Sx + Rx) / (n+1);
        *yVertPoint = (Sy + Ry) / (n+1);
        *zVertPoint = (Sz + Rz) / (n+1);
    }
    else{
        //(Q/n) + (2R/n) + (S(n-3)/n)

        // The valence of a point is simply the number of edges that connect to that point.
        n = faces.size();

        double Qx = 0;
        double Qy = 0;
        double Qz = 0;
        // Q is the average of the surrounding face points
        for (FaceNew* currFace : faces){
            Qx += *currFace->facePoint->x;
            Qy += *currFace->facePoint->y;
            Qz += *currFace->facePoint->z;
        }

        Qx = Qx / faces.size();
        Qy = Qy / faces.size();
        Qz = Qz / faces.size();

        // R is the average of all surround edge midpoints

        for (EdgeNew* currEdge : edges){
            Rx += (*currEdge->v0->x + *currEdge->v1->x) / 2.0;
            Ry += (*currEdge->v0->y + *currEdge->v1->y) / 2.0;
            Rz += (*currEdge->v0->z + *currEdge->v1->z) / 2.0;
        }
        Rx = Rx / edges.size();
        Ry = Ry / edges.size();
        Rz = Rz / edges.size();

        *xVertPoint = (Qx + 2 * Rx + Sx * (n - 3)) / n;
        *yVertPoint = (Qy + 2 * Ry + Sy * (n - 3)) / n;
        *zVertPoint = (Qz + 2 * Rz + Sz * (n - 3)) / n;
    }

    this->vertPoint = createVert (xVertPoint, yVertPoint, zVertPoint);
}
