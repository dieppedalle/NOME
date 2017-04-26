/**
 * UC Berkeley, NOME project.
 * Advised by Prof. Sequin H. Carlos.
 */

#include "bspline.h"

BSpline::BSpline(void)
{
    PolyLine();
    vertices.clear();
    set_order(4);
}

void BSpline::updateBSpline()
{


    if(segments_expr != ""){
        int new_segments = int(evaluate_expression(segments_expr, params));
        if(new_segments != segments)
        {
            vertices.clear();
            segments = new_segments;

            cubic();
        }


    }
}

void BSpline::set_proxy(Vertex *v)
{
    proxy.push_back(v);
}


void BSpline::set_segments(int a)
{
    segments = a;
}

void BSpline::set_order(int a)
{
    order = a;
}

int BSpline::get_segments()
{
    return segments;
}

int BSpline::get_order()
{
    return order;
}

float BSpline::basis(int i, int k, float t)
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

void BSpline::calculate (int order)
{
    int degree = order - 1;
    //calculate bspline for general order bspline, order>=2 is enforced
    if (order >= 2)
    {
        //clear all vertices just in case
        vertices.clear();


        float lim = degree + proxy.size() - 2;
        //float add = (lim - degree - 1)/(segments);
        float add = ((float) (proxy.size() - degree))/(segments);
        //cout << add << endl;

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


void BSpline::cubic()
{
    calculate(get_order());
}
