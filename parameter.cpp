#include "parameter.h"
#include "mesh.h"
#include "myslider.h"
#include "polyline.h"
#include "bspline.h"

Parameter::Parameter()
{
    this -> name = QString("");
    influenceMeshes.clear();
    influencePolylines.clear();
    influenceBSpline.clear();
    influenceVertices.clear();
    influenceTransformations.clear();
}

float Parameter::getValue()
{
    return value;
}

void Parameter::update()
{
    //cout << "HELLO" << endl;
    for(Mesh*& m : influenceMeshes)
    {
        switch(m -> type)
        {
        case 1:
            m -> updateFunnel();
            break;
        case 2:
            m -> updateTunnel();
            break;
        }
    }
    //cout << influencePolylines.size() << endl;
    for(PolyLine*& p : influencePolylines)
    {
        //std::cout << typeid(p).name() << '\n';
        //cout << BSpline(p).segments << endl;
        //cout << "Update polyline" << endl;
        p -> updateCircle();
    }

    /*for(PolyLine*& p : influenceBSpline)
    {
        //cout << p->segments << endl;
        //cout << "Update polyline" << endl;
        //p -> updateCircle();
        cout << "OOOO" << endl;
    }*/

    for(Transformation*& t : influenceTransformations)
    {
        t -> update();
    }
    for(Vertex*& v : influenceVertices)
    {
        v -> update();
    }

}

void Parameter::addInfluenceMesh(Mesh * mesh)
{
    influenceMeshes.push_back(mesh);
}

void Parameter::addInfluencePolyline(PolyLine * polyline)
{
    influencePolylines.push_back(polyline);
}

void Parameter::addInfluenceBSpline(BSpline * polyline)
{
    influenceBSpline.push_back(polyline);
}


void Parameter::addInfluenceTransformation(Transformation * t)
{
    influenceTransformations.push_back(t);
}

void Parameter::addInfluenceVertex(Vertex * vertex)
{
    influenceVertices.push_back(vertex);
}

void Parameter::changeParameterValue(float value)
{
    this -> value = value;
    slider -> slider -> setValue(int((this -> value - this -> start) / this -> stepsize + 0.5 ));
}
