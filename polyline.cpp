/**
 * @author Andy Wang, UC Berkeley.
 * Copyright 2016 reserve.
 * UC Berkeley, Slide_2016 project.
 * Advised by Prof. Sequin H. Carlos.
 */

#include "polyline.h"

PolyLine::PolyLine()
{
    isCircle = false;
    isLoop = false;
    vertices.clear();
    user_set_color = false;
    transformations_up.clear();
    n = 0;
    ro = 0;

    n_expr = "";
    ro_expr = "";
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
        //cout<<(*dIt)<<endl;
    }
    return distances;
}

void PolyLine::setColor(QColor color)
{
    this -> color = color;
}

void PolyLine::addParam(Parameter* param)
{
    influencingParams.push_back(param);
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

void PolyLine::setGlobalParameter(unordered_map<string, Parameter> *params)
{
    this -> params = params;
}

float PolyLine::basis(int i, int k, float t)
{
    //calculate basis function, i = control point index, k = order, t = variable parameter
    if (k < 0)
    {
        return 0;
    }

    else if (k == 0)
    {
        int comp = (int) floor(t);

        if ((comp < i + 1) && (comp >= i))
        {
            return 1;
        }
        return 0;
    }

    else {
        float a = (t - i)/k;
        float b = (i + k + 1 - t)/k;

        a = a * basis(i, k-1, t);
        b = b * basis(i+1, k-1, t);

        return a + b;
    }

}

void PolyLine::calculate (int order)
{
    int degree = order - 1;
    //calculate bspline for general order bspline, order>=2 is enforced
    if (order >= 2)
    {
        //clear all vertices just in case
        vertices.clear();


        float lim = degree + proxy.size() - 2;

        float add = ((float) (proxy.size() - degree))/(segments);

        int realLimit = segments;

        float upper;

        float t = degree + 1;

        //calculate bspline at each t
        for (int vertexNumber = 0; vertexNumber <= realLimit; vertexNumber++)//{
        {
            float x = 0;
            float y = 0;
            float z = 0;

            for (int i = 1; i <= proxy.size(); i++)
            {
                float temp = basis(i, degree, t);

                vec3 pos = proxy[i-1] -> position;

                x = x + (temp * pos[0]);
                y = y + (temp * pos[1]);
                z = z + (temp * pos[2]);

            }
            Vertex* newBSplineVertex = new Vertex(x, y, z, t);
            newBSplineVertex -> name = std::to_string(vertexNumber);
            addVertex(newBSplineVertex);
            t = t + add;
        }
    }
}

void PolyLine::cubic()
{
    calculate(order);
}

void PolyLine::set_proxy(Vertex *v)
{
    proxy.push_back(v);
}


void PolyLine::set_segments(int a)
{
    segments = a;
}

void PolyLine::set_order(int a)
{
    order = a;
}

int PolyLine::get_segments()
{
    return segments;
}

int PolyLine::get_order()
{
    return order;
}


void PolyLine::updateCircle()
{

    //cout << int(evaluate_expression(segments_expr, params)) << endl;
    //cout << this->segments << endl;
    //cout << this->segments_expr << endl;
    if (segments_expr != ""){
        int new_segments = int(evaluate_expression(segments_expr, params));
        if(new_segments != segments)
        {
            vertices.clear();
            segments = new_segments;
            //cout << "PPPP" << endl;
            calculate(order);
            //updateCircle_n();
        }
    }

    if(n_expr != ""){
        int new_n = int(evaluate_expression(n_expr, params));
        if(new_n != n)
        {
            vertices.clear();
            n = new_n;
            updateCircle_n();
        }


    }

    if(ro_expr != ""){
        float new_ro = float(evaluate_expression(ro_expr, params));
        if(new_ro != ro)
        {
            ro = new_ro;
            updateCircle_ro();
        }
    }


}

void PolyLine::updateCircle_n()
{
    if(n < 3) {
        cout << "Error: Circle method needs to have a n parameter that is higher than 2." << endl;
        //return 1;
    }
    vector<Vertex*> vertList;
    vector<Face*> faceList;
    unordered_map<Vertex*, vector<Edge*> > edgeTable;
    vertList.clear();
    edgeTable.clear();
    faceList.clear();
    vector<Vertex*> baseCircle;
    vector<Vertex*> highCircle;
    vector<Vertex*> lowCircle;
    for(int i = 0; i < n; i++)
    {
        Vertex * newVertex = new Vertex;
        newVertex->ID = i;
        newVertex->name = "bc" + to_string(i);

        float currAngle = 2.0 * i / n * PI;
        newVertex -> position = vec3(ro * glm::cos(currAngle),
                                     ro * glm::sin(currAngle), 0);
        baseCircle.push_back(newVertex);
        addVertex(newVertex);
    }
}

void PolyLine::getVertexNormal(Vertex * currVert){
    Edge * firstEdge = currVert -> oneEdge;
    if(firstEdge == NULL) {
        //cout<<"Lonely vertex without any adjacent edges"<<endl;
        return;
    }
    Edge * currEdge = firstEdge;
    Face * currFace = currEdge -> fa;
    vec3 avgNorm(0, 0, 0);
    int mobiusCounter = 0;
    do {
        if(mobiusCounter % 2 == 0) {
            avgNorm += currFace -> normal;
        } else {
            avgNorm -= currFace -> normal;
        }
        if(currEdge -> mobius) {
            mobiusCounter += 1;
        }
        currFace = currEdge -> theOtherFace(currFace);
        if(currFace == NULL) { //If the face is NULL, need to skip this face
            Edge * nextEdge = currEdge -> nextEdge(currVert, currFace);
            if(nextEdge -> va == currEdge -> va || nextEdge -> vb == currEdge -> vb) {
                mobiusCounter += 1;
            }
            currEdge = nextEdge;
            currFace = currEdge -> theOtherFace(currFace);
        }
        currEdge = currEdge -> nextEdge(currVert, currFace);
    } while ( currEdge != firstEdge);
    //if(currVert -> onMobius) {
    //cout<<"The value of avgNorm is :"<<avgNorm[0]<<" "<<avgNorm[1]<<" "<<avgNorm[2]<<endl;
    //cout<<"The position of this vertex is :"<<currVert -> position[0]<<" "<<currVert -> position[1]<<" "<<currVert -> position[2]<<endl;
    //}//cout<<"ID: "<<currVert -> ID <<" has "<<mobiusCounter<<" mConter"<<endl;
    currVert -> normal = normalize(avgNorm);
}

void PolyLine::computeNormals(){
    vector<Vertex*>::iterator vIt;

    //cout << "HELLO" << endl;

    //cout << vertices.size() << endl;
    for(vIt = vertices.begin(); vIt != vertices.end(); vIt++) {
        //cout<<"Now calculating vertex with ID: ";
        getVertexNormal(*vIt);
    }

}

void PolyLine::updateCircle_ro()
{
    for(int i = 0; i < n; i++)
    {
        Vertex * newVertex = vertices[i];

        float currAngle = 2.0 * i / n * PI;
        //cout << n << endl;
        newVertex -> position = vec3(ro * glm::cos(currAngle),
                                     ro * glm::sin(currAngle), 0);
    }

    computeNormals();
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
    newPolyline.influencingParams = influencingParams;
    newPolyline.params = params;
    newPolyline.n_expr = n_expr;
    newPolyline.n = n;
    newPolyline.ro_expr = ro_expr;
    newPolyline.ro = ro;
    newPolyline.segments = segments;
    newPolyline.segments_expr = segments_expr;
    newPolyline.order = order;
    newPolyline.proxy = proxy;

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
    newPolyline.segments = segments;
    newPolyline.segments_expr = segments_expr;
    newPolyline.order = order;
    newPolyline.proxy = proxy;

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

void PolyLine::drawLineWithCubes(int start_index)
{
    int counter = 0;
    updateCubeSizes();
    for(Vertex*& v : vertices)
    {
        glLoadName(start_index + counter);
        drawCubeAroundVertex(v, 0.1 * cubeSizes[counter]);
        counter++;
    }
    drawLine(start_index);
}

void PolyLine::drawCubeAroundVertex(Vertex *v, float size)
{
    vec3 p = v -> position;
    float x = p[0];
    float y = p[1];
    float z = p[2];
    //cout << size << endl;
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
    /*glBegin(GL_QUADS);
        glNormal3f(0, 0, -1);
        glVertex3f(x + 0.2 / 2, y + 0.2 / 2, z - 0.2 / 2);
        glVertex3f(x + 0.2 / 2, y - 0.2 / 2, z - 0.2 / 2);
        glVertex3f(x - 0.2 / 2, y - 0.2 / 2, z - 0.2 / 2);
        glVertex3f(x - 0.2 / 2, y + 0.2 / 2, z - 0.2 / 2);
    glEnd();
    glBegin(GL_QUADS);
        glNormal3f(-1, 0, 0);
        glVertex3f(x - 0.2 / 2, y + 0.2 / 2, z - 0.2 / 2);
        glVertex3f(x - 0.2 / 2, y - 0.2 / 2, z - 0.2 / 2);
        glVertex3f(x - 0.2 / 2, y - 0.2 / 2, z + 0.2 / 2);
        glVertex3f(x - 0.2 / 2, y + 0.2 / 2, z + 0.2 / 2);
    glEnd();*/
    glBegin(GL_QUADS);
        glNormal3f(0, 1, 0);
        glVertex3f(x + 0.1 / 2, y, z - 0.1 / 2);
        glVertex3f(x + 0.1 / 2, y, z + 0.1 / 2);
        glVertex3f(x - 0.1 / 2, y, z + 0.1 / 2);
        glVertex3f(x - 0.1 / 2, y, z - 0.1 / 2);
    glEnd();
    /*glBegin(GL_QUADS);
        glNormal3f(0, -1, 0);
        glVertex3f(x + 0.2 / 2, y - 0.2 / 2, z + 0.2 / 2);
        glVertex3f(x + 0.2 / 2, y - 0.2 / 2, z - 0.2 / 2);
        glVertex3f(x - 0.2 / 2, y - 0.2 / 2, z - 0.2 / 2);
        glVertex3f(x - 0.2 / 2, y - 0.2 / 2, z + 0.2 / 2);
    glEnd();*/
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
