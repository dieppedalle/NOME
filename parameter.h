#ifndef PARAMETER_H
#define PARAMETER_H

#include <QString>
#include <vector>
class MySlider;
class Mesh;
class Vertex;
class PolyLine;
class Transformation;
class BSpline;
using namespace std;


/**
 * @brief The Parameter class. The parameter to control the shape.
 * Every parameter will be controled by a slider bar.
 */
class Parameter
{
public:
    Parameter();
    QString name;
    float start;
    float end;
    float stepsize;
    float value;
    float getValue();
    /* The slider of this parameter. */
    MySlider *slider;
    /* A list of objects to update when changing value of this parameter. */
    vector<Vertex*> influenceVertices;
    vector<Mesh*> influenceMeshes;
    vector<PolyLine*> influencePolylines;
    vector<Transformation*> influenceTransformations;
    void update();
    void addInfluenceMesh(Mesh * mesh);
    void addInfluenceTransformation(Transformation *t);
    void addInfluenceVertex(Vertex * vertex);
    void addInfluencePolyline(PolyLine * polyline);
    void changeParameterValue(float value);
};

#endif // PARAMETER_H
