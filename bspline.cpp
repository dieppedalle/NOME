/**
 * UC Berkeley, NOME project.
 * Advised by Prof. Sequin H. Carlos.
 */

#include bspline.h

BSpline::BSpline(PolyLine *p, int mode, int segments)
{
	/** mode = 0 for open bspline
		mode = 1 for closed bspline 
		segments = no points in between every 4 control points to define the bspline 
	**/
	PolyLine();
	proxy = p->vertices;
	color = p->color;
	vertices.clear();
	cubic(mode, segments);
}

void BSpline::cubic(int mode, int segments)
{
	//mode = 0 -> open, mode = 1 -> closed curve
	//segments = curve segments to define bspline
	int i = vertices.size() - 3;
	isLoop = false;

	float t0[segments];
	float t1[segments];
	float t2[segments];
	float t3[segments];

	vector<Vertex*>::iterator vIt;
	vIt = proxy.begin();

	//create coefficients for the 4 control points at each iteration for no. of segments
	for (int a = 0; a < segments; a++)
	{
		t0[a] = (1 - (3*a) + (3 * (a * a)) - (a * a * a)) / 6;
		t1[a] = (4 - (6 * (a * a)) + (3 * (a* a * a))) / 6;
		t2[a] = (1 + (3*a) + (3 * (a * a)) - (3 * (a * a * a))) / 6;
		t3[a] = (a * a * a) / 6;
	}

	//first loop around all the points to create bspline with segment number of points, all the way up to no. control points-3
	for (int j = 0; j < i; j++)
	{
		vec3 position_a = (*vIt) -> position;
		vec3 position_b = (*vIt + 1) -> position;
		vec3 position_c = (*vIt + 2) -> position;
		vec3 position_d = (*vIt + 3) -> position;

		for (int t = 0; t < segments; t++)
		{
			float x = t0[t] * position_a[0] + t1[t] * position_b[0] + t2[t] * position_c[0] + t3[t] * position_d[0];
			float y = t0[t] * position_a[1] + t1[t] * position_b[1] + t2[t] * position_c[1] + t3[t] * position_d[1];
			float z = t0[t] * position_a[2] + t1[t] * position_b[2] + t2[t] * position_c[2] + t3[t] * position_d[2];

			Vertex* v1 = new Vertex;
			v1 -> ID = j + t; //this is a filler
	        v1 -> name = j + t; //this is a filler

	        float points[3] = {x, y, z};
	        v1 -> position = points;

	        addVertex(v1);
		}

		vIt++;
	}

	//closing the loop in case the bspline is closed
	if (mode == 1)
	{
		isLoop = true;
		vector<Vertex*>::iterator vIt2;
		vIt2 = proxy.begin();

		vec3 a0 = (*vIt) -> position;
		vec3 a1 = (*vIt + 1) -> position;
		vec3 a2 = (*vIt + 2) -> position;
		vec3 a3 = (*vIt2) -> position;

		for (int k = 0; k < 3; k++)
		{
			for (int s = 0; s < segments; s++)
			{
				float x1 = t0[s] * a0[0] + t1[s] * a1[0] + t2[s] * a2[0] + t3[s] * a3[0];
				float y1 = t0[s] * a0[1] + t1[s] * a1[1] + t2[s] * a2[1] + t3[s] * a3[1];
				float z1 = t0[s] * a0[2] + t1[s] * a1[2] + t2[s] * a2[2] + t3[s] * a3[2];


				Vertex* v2 = new Vertex;
				v2 -> ID = k + s + j; //this is a filler
		        v2 -> name = k + s + j; //this is a filler

		        float points1[3] = {x1, y1, z1};
		        v2 -> position = points1;

		        addVertex(v2);
			}

			a0 = a1;
			a1 = a2;
			a2 = a3;
			a3 = (*vIt2 + 1) -> position;
			vIt2++;
		}
	}

	return true;
}