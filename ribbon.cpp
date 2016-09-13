#include "ribbon.h"

/**
 * @author Andy Wang, UC Berkeley.
 * Copyright 2016 reserve.
 * UC Berkeley, Slide_2016 project.
 * Advised by Prof. Sequin H. Carlos.
 */

#include "polyline.h"

#define PolyLine PolyLine

PolyLine::PolyLine()
{
    isLoop = true;
    vertices.clear();
    user_set_color = false;
    transformations_up.clear();
}

void PolyLine::drawLine(int start_index)
{
    if(!isLoop)
    {
        glBegin(GL_LINE_STRIP);
    }
    else
    {
        glBegin(GL_LINE_LOOP);
    }
    vector<Vertex*>::iterator vIt;
    for(vIt = vertices.begin(); vIt < vertices.end(); vIt ++)
    {
        vec3 position = (*vIt) -> position;
        glVertex3f(position[0], position[1], position[2]);
    }
    glEnd();
}

void PolyLine::clear()
{
    vertices.clear();
    transformations_up.clear();
}

bool PolyLine::isEmpty()
{
    return vertices.size() == 0;
}

vector<float> PolyLine::skewness()
{
    if(vertices.size() < 2) {
        cout<<"ERROR: Can not find the skewness of a polyline with one vertex."<<endl;
        exit(0);
    }
    vector<float> distances;
    distances.push_back(0);
    vector<Vertex*>::iterator vIt;
    float sum = 0;
    for(vIt = vertices.begin(); vIt < vertices.end() - 1; vIt++) {
        float currDistance = distance((*(vIt + 1)) -> position, (*vIt) -> position);
        sum += currDistance;
        distances.push_back(sum);
    }
    if(isLoop) {
        sum += distance(vertices[0] -> position, (*vIt) -> position);
    }
    vector<float>::iterator dIt;
    for(dIt = distances.begin(); dIt < distances.end(); dIt++) {
        (*dIt) /= sum;
        cout<<(*dIt)<<endl;
    }
    return distances;
}

void PolyLine::setColor(QColor color)
{
    this -> color = color;
}

void PolyLine::addTransformation(Transformation new_transform)
{
    transformations_up.push_back(new_transform);
}

void PolyLine::setTransformation(vector<Transformation> new_transform)
{
    transformations_up = new_transform;
}

void PolyLine::addVertex(Vertex *v)
{
    vertices.push_back(v);
}

void PolyLine::transform(Transformation *t)
{
    mat4 matrix = t -> getMatrix();
    vector<Vertex*>::iterator vIt;
    for(vIt = vertices.begin(); vIt < vertices.end(); vIt++) {
        (*vIt) -> position = vec3(matrix * vec4((*vIt) -> position, 1));
    }
}

PolyLine PolyLine::makeCopy(string copy_polyline_name)
{
    PolyLine newPolyline;
    newPolyline.clear();
    if(copy_polyline_name == "")
    {
        newPolyline.name = this -> name;
    }
    else
    {
        newPolyline.name = copy_polyline_name;
    }
    newPolyline.isLoop = this->isLoop;
    newPolyline.color = color;
    for(Vertex*& v: vertices)
    {
        Vertex* newVertex = new Vertex;
        newVertex -> ID = v -> ID;
        newVertex -> name = v -> name;
        newVertex -> position = v -> position;
        newVertex -> isParametric = v -> isParametric;
        if(v -> isParametric)
        {
            newVertex -> x_expr = v -> x_expr;
            newVertex -> y_expr = v -> y_expr;
            newVertex -> z_expr = v -> z_expr;
            newVertex -> influencingParams = v -> influencingParams;
            newVertex -> params = v -> params;
        }
        newPolyline.addVertex(newVertex);
    }
    return newPolyline;
}

PolyLine PolyLine::makeCopyForTransform()
{
    PolyLine newPolyline;
    newPolyline.before_transform_polyline = this;
    newPolyline.name = this -> name;
    newPolyline.isLoop = this->isLoop;
    newPolyline.color = color;
    for(Vertex*& v: vertices)
    {
        Vertex* newVertex = new Vertex;
        newVertex -> ID = v -> ID;
        newVertex -> name = v -> name;
        newVertex -> position = v -> position;
        newVertex -> before_transform_vertex = v;
        newPolyline.addVertex(newVertex);
    }
    return newPolyline;
}

void PolyLine::updateCopyForTransform()
{
    transformations_up = before_transform_polyline -> transformations_up;
    for(Vertex*& v: vertices)
    {
        v -> position = v -> before_transform_vertex -> position;
    }
}

vec3 distanceVector(vec3 x, vec3 y){
    vec3 z;
    z.x = x.x - y.x;
    z.y = x.y - y.y;
    z.z = x.z - y.z;
    return z;
}

vec3 scale(vec3 x, float y){
    vec3 z;
    z.x = x.x * y;
    z.y = x.y * y;
    z.z = x.z * y;
    return z;
}

vec3 getNext(vec3 x, vec3 y, vec3 z, vec3 t){
    vec3 f = scale(normalize(cross(distanceVector(x,y),distanceVector(z,t))),0.4);
    return f;
}

void PolyLine::finalize(){
    ribbonVertices.clear();
    if(vertices.size() > 0){
        bool flag = false;
        bool pass = false;
        vec3 prev;
        int l = vertices.size() - 1;
        for(int i = 0; i < vertices.size(); ++i){
            vec3 final = getNext(vertices[i%vertices.size()]->position, vertices[(i+1)%vertices.size()]->position, vertices[l%vertices.size()]->position, vertices[i%vertices.size()]->position);
            if(!flag){
                prev = final;
                flag = true;
            }
            else{
                final = reflect(final, prev);
            }
            if(std::isnan(final.x) && std::isnan(final.y) && std::isnan(final.z)){
                final = distanceVector(ribbonVertices[ribbonVertices.size() - 1]->position, vertices[l%vertices.size()]->position);
            }
            Vertex* v = new Vertex(vertices[i%vertices.size()]->position.x + final.x,
                    vertices[i%vertices.size()]->position.y + final.y,
                    vertices[i%vertices.size()]->position.z + final.z,
                    vertices[i%vertices.size()]->ID + vertices.size());
            ribbonVertices.push_back(v);
            ++l;
        }
    }
}

void PolyLine::drawLineWithCubes(int start_index)
{
    GLfloat fcolor[] = {1.0f * color.red() / 255,
                        1.0f * color.green() / 255,
                        1.0f * color.blue() / 255,
                        1.0f * color.alpha() /255};
    GLfloat acolor[] = {0 / 255,
                         1.0f - 1.0f * color.green() / 255,
                         0 / 255,
                         1.0f - 1.0f * color.alpha() /255};
    GLfloat bcolor[] = {0 / 255,
                         1.0f - 1.0f * color.green() / 255,
                         1.0f - 1.0f * color.blue() / 255,
                         1.0f - 1.0f * color.alpha() /255};
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, fcolor);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, fcolor);
    if(ribbonVertices.size() == 0){
        finalize();
    }
    int counter = 0;
    updateCubeSizes();
    for(Vertex*& v : vertices)
    {
        glLoadName(start_index + counter);
        drawCubeAroundVertex(v, 0.08 * cubeSizes[counter]);
        counter++;
    }
    counter = 0;
    for(Vertex*& v : ribbonVertices)
    {
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, bcolor);
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, bcolor);
        glBegin(GL_LINE_STRIP);
        glVertex3f(vertices[counter]->position[0],vertices[counter]->position[1],vertices[counter]->position[2]);
        glVertex3f(v->position[0],v->position[1],v->position[2]);
        glEnd();
        glLoadName(start_index + counter);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, acolor);
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, acolor);
        drawCubeAroundVertex(v, 0.05);
        counter++;
    }
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, acolor);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, acolor);
    glBegin(GL_LINE_STRIP);
    for(Vertex*& v : ribbonVertices)
    {
        glVertex3f(v->position[0],v->position[1],v->position[2]);
    }
    glVertex3f(ribbonVertices[0]->position[0],ribbonVertices[0]->position[1],ribbonVertices[0]->position[2]);
    glEnd();
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, fcolor);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, fcolor);
    drawLine(start_index);
}

void PolyLine::drawCubeAroundVertex(Vertex *v, float size)
{
    vec3 p = v -> position;
    float x = p[0];
    float y = p[1];
    float z = p[2];
    glBegin(GL_QUADS);
        glNormal3f(0, 0, 1);
        glVertex3f(x + size / 2, y + size / 2, z + size / 2);
        glVertex3f(x - size / 2, y + size / 2, z + size / 2);
        glVertex3f(x - size / 2, y - size / 2, z + size / 2);
        glVertex3f(x + size / 2, y - size / 2, z + size / 2);
    glEnd();
    glBegin(GL_QUADS);
        glNormal3f(1, 0, 0);
        glVertex3f(x + size / 2, y + size / 2, z + size / 2);
        glVertex3f(x + size / 2, y - size / 2, z + size / 2);
        glVertex3f(x + size / 2, y - size / 2, z - size / 2);
        glVertex3f(x + size / 2, y + size / 2, z - size / 2);
    glEnd();
    glBegin(GL_QUADS);
        glNormal3f(0, 0, -1);
        glVertex3f(x + size / 2, y + size / 2, z - size / 2);
        glVertex3f(x + size / 2, y - size / 2, z - size / 2);
        glVertex3f(x - size / 2, y - size / 2, z - size / 2);
        glVertex3f(x - size / 2, y + size / 2, z - size / 2);
    glEnd();
    glBegin(GL_QUADS);
        glNormal3f(-1, 0, 0);
        glVertex3f(x - size / 2, y + size / 2, z - size / 2);
        glVertex3f(x - size / 2, y - size / 2, z - size / 2);
        glVertex3f(x - size / 2, y - size / 2, z + size / 2);
        glVertex3f(x - size / 2, y + size / 2, z + size / 2);
    glEnd();
    glBegin(GL_QUADS);
        glNormal3f(0, 1, 0);
        glVertex3f(x + size / 2, y + size / 2, z - size / 2);
        glVertex3f(x + size / 2, y + size / 2, z + size / 2);
        glVertex3f(x - size / 2, y + size / 2, z + size / 2);
        glVertex3f(x - size / 2, y + size / 2, z - size / 2);
    glEnd();
    glBegin(GL_QUADS);
        glNormal3f(0, -1, 0);
        glVertex3f(x + size / 2, y - size / 2, z + size / 2);
        glVertex3f(x + size / 2, y - size / 2, z - size / 2);
        glVertex3f(x - size / 2, y - size / 2, z - size / 2);
        glVertex3f(x - size / 2, y - size / 2, z + size / 2);
    glEnd();
}

void PolyLine::updateCubeSizes()
{
    cubeSizes.clear();
    vector<Vertex*>::iterator vIt;
    vector<float> distances;
    for(vIt = vertices.begin(); vIt < vertices.end() - 1; vIt++)
    {
        distances.push_back(glm::distance((*vIt) -> position, (*(vIt + 1)) -> position));
    }
    if(isLoop)
    {
        distances.push_back(glm::distance((*vIt) -> position, vertices[0] -> position));
        for(size_t i = 0; i < distances.size(); i++)
        {
            if(i == 0)
            {
                cubeSizes.push_back((distances[0] + *(distances.end() - 1)) / 2);
            }
            else
            {
                cubeSizes.push_back((distances[i] + distances[i - 1]) / 2);
            }
        }
    }
    else
    {
        for(size_t i = 0; i <= distances.size(); i++)
        {
            if(i == 0)
            {
                cubeSizes.push_back(distances[0]);
            }
            else if(i == distances.size())
            {
                cubeSizes.push_back(distances[distances.size() - 1]);
            }
            else
            {
                cubeSizes.push_back((distances[i - 1] + distances[i]) / 2);
            }
        }
    }
}

void PolyLine::drawVertices()
{
    glPointSize(10);
    glBegin(GL_POINTS);
    for(Vertex*& v : vertices)
    {
        if(v -> selected)
        {
            vec3 p = v -> position;
            glNormal3f(p[0] * 100, p[1] * 100, p[2] * 100);
            glVertex3f(p[0], p[1], p[2]);
        }
    }
    glEnd();
}

Vertex * PolyLine::findVertexInThisPolyline(string name)
{
    for(Vertex*& v: vertices)
    {
        if(v->name == name)
        {
            return v;
        }
    }
    return NULL;
}
