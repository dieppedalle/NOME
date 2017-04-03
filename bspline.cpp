/**
 * UC Berkeley, NOME project.
 * Advised by Prof. Sequin H. Carlos.
 */

#include "bspline.h"

BSpline::BSpline(void)
{
    PolyLine();
    vertices.clear();
}


void BSpline::set_proxy(Vertex *v)
{
    proxy.push_back(v);
}


void BSpline::set_segments(int a)
{
    segments = a;
}

int BSpline::get_segments()
{
    return segments;
}

float BSpline::basis(float i, float k, float t)
{
    //calculate basis function, i = control point index, k = order, t = variable parameter
    if (k <= 0)
    {
        return 0;
    }

    else if (k == 1)
    {
        int comp = (int) floor(t);

        if ((comp < i + 1) && (comp >= i))
        {
            return 1;
        }
        return 0;
    }

    else {
        float a = (t - i)/(k - 1.0);
        float b = (i + k - t)/(k - 1.0);

        a = a * basis(i, k-1, t);
        b = b * basis(i+1, k-1, t);

        return a + b;
    }

}

void BSpline::calculate (int order)
{
    //calculate bspline for general order bspline, order>=2 is enforced
    if (order >= 2)
    {
        //clear all vertices just in case
        vertices.clear();

        /**add first order-1 points to end of loop if a closed spline is desired
        if (isLoop)
        {
            vector<Vertex*>::iterator iter;
            iter = proxy.begin();
            for (int x = 0; x < order - 1; x++)
            {
                proxy.push_back(*iter);
                iter++;
            }
        }**/

        //https://www.cl.cam.ac.uk/teaching/2000/AGraphHCI/SMEG/node4.html

        float lim = order + proxy.size() - 2;
        float add = lim/(segments + 2);

        //calculate bspline at each t
        for (float t = 2.0; t <= lim; t = t + add)
        {
            float x = 0;
            float y = 0;
            float z = 0;

            //cout << t << endl;

            for (int i = 1; i <= proxy.size(); i++)
            {
                float temp = basis(i, order, t);
                //cout << temp << endl;
                vec3 pos = proxy[i-1] -> position;

                x = x + (temp * pos[0]);
                y = y + (temp * pos[1]);
                z = z + (temp * pos[2]);
            }

            addVertex(new Vertex(x, y, z, t));

        }
    }
}


void BSpline::cubic()
{
    calculate(4);
}
