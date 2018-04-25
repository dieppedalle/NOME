//
//  Mesh.cpp
//  model
//
//  Created by L on 26/08/2017.
//  Copyright © 2017 L. All rights reserved.
//

#include "SweepNew.h"
#include "SweepNew.h"
#include <Vector3.h>
#include <Matrix3x4.h>

static int pIndex = 0;

Vert* newVertex(std::string name, double xx, double yy, double zz)
{
  double *x = (double*) malloc(sizeof(double));
  double *y = (double*) malloc(sizeof(double));
  double *z = (double*) malloc(sizeof(double));

  *x = xx;
  *y = yy;
  *z = zz;

  // double *currentValSet = (double*) malloc(sizeof(double));
  // parseGetBankVal($<string>4, currSession, currentValSet, nomlineno);
  // *x =*currentValSet;
  // parseGetBankVal($<string>5, currSession, currentValSet, nomlineno);
  // *y =*currentValSet;
  // parseGetBankVal($<string>6, currSession, currentValSet, nomlineno);
  // *z =*currentValSet;

  Vert * newVerte = createVert (x, y, z);
  newVerte->setName(name);

  return newVerte;
}

double rotateX(double angle,
	       double x, double y, double z,
	       double ux, double uy, double uz)
{
  double cost = std::cos(angle);
  double sint = std::sin(angle);
  return (cost + ux * ux * (1 - cost)) * x
    + (ux * uy * (1 - cost) - uz * sint) * y
    + (ux * uz * (1 - cost) + uy * sint) * z;
}

double rotateY(double angle,
	       double x, double y, double z,
	       double ux, double uy, double uz)
{
  double cost = std::cos(angle);
  double sint = std::sin(angle);
  return (ux * uy * (1 - cost) + uz * sint) * x
    + (cost + uy * uy * (1 - cost)) * y
    + (uy * uz * (1 - cost) - ux * sint) * z;
}

double rotateZ(double angle,
	       double x, double y, double z,
	       double ux, double uy, double uz)
{
  double cost = std::cos(angle);
  double sint = std::sin(angle);
  return (uz * ux * (1 - cost) - uy * sint) * x
    + (uz * uy * (1 - cost) + ux * sint) * y
    + (cost + uz * uz * (1 - cost)) * z;
}

void rotate(double angle,
	    double* x, double* y, double* z,
	    double ux, double uy, double uz)
{
  double xn = rotateX(angle, *x, *y, *z, ux, uy, uz);
  double yn = rotateY(angle, *x, *y, *z, ux, uy, uz);
  double zn = rotateZ(angle, *x, *y, *z, ux, uy, uz);
  *x = xn;
  *y = yn;
  *z = zn;
}

Vert* nextVertex(int order, Vert* target,
		 double px, double py, double pz,
		 double x, double y, double z,
		 double nx, double ny, double nz,
		 int size, double* width, double* azimuth, double* twist)
{
  double u1 = px - x;
  double u2 = py - y;
  double u3 = pz - z;

  double v1 = nx - x;
  double v2 = ny - y;
  double v3 = nz - z;

  double s1 = u2 * v3 - u3 * v2;
  double s2 = u3 * v1 - u1 * v3;
  double s3 = u1 * v2 - u2 * v1;

  double d1 = v1 - u1;
  double d2 = v2 - u2;
  double d3 = v3 - u3;
  if (order == 0) {
    d1 = v1;
    d2 = v2;
    d3 = v3;
  } else if (order == (size - 1)) {
    d1 = -u1;
    d2 = -u2;
    d3 = -u3;
  }

  double dnorm = std::sqrt(d1*d1+d2*d2+d3*d3);

  d1 = d1 / dnorm;
  d2 = d2 / dnorm;
  d3 = d3 / dnorm;

  double curr_twist = order * (*twist) / (size - 1);
  double angle = *azimuth + curr_twist;
  
  double ts1 = rotateX(angle, s1, s2, s3, d1, d2, d3);
  double ts2 = rotateY(angle, s1, s2, s3, d1, d2, d3);
  double ts3 = rotateZ(angle, s1, s2, s3, d1, d2, d3);

  double targetx = rotateX(1.57, *target->x, *target->y, *target->z, 0, 0, 1);
  double targety = rotateY(1.57, *target->x, *target->y, *target->z, 0, 0, 1);
  double targetz = rotateZ(1.57, *target->x, *target->y, *target->z, 0, 0, 1);

  double norm = std::sqrt(ts1*ts1+ts2*ts2+ts3*ts3);
  
  s1 = 1 * ts1 / norm;
  s2 = 1 * ts2 / norm;
  s3 = 1 * ts3 / norm;

  s1 += x + targetx;
  s2 += y + targety;
  s3 += z + targetz;
  
  return newVertex("sweep_vert_"+std::to_string(order), s1, s2, s3);
}

void standardMode(SweepNew* sw, std::list<Vert*> crosssection, double* width, double* azimuth, double* twist) {
  for (Vert* targetVert: crosssection) {
    int sz = sw->verts.size();
    std::list<Vert*>::iterator it = sw->verts.begin();
    //std::list<EdgeNew*>::iterator edgeIt = sw->edges.begin();
    std::list<Vert*>::iterator it2 = sw->verts.begin();
    ++it2;
    Vert* prevVert = *(sw->verts.rbegin());
    Vert* prevV = 0;
    EdgeNew* prevEdge = 0;
    for (int i = 0; i < sz; ++i) {

      Vert* vert = *it;
      Vert* nextVert = 0;
      if (i == (sz - 1)) {
	nextVert = *(sw->verts.begin());
      } else {
	nextVert = *it2;
      }
    
      Vert* v = nextVertex(i, targetVert,
			   *prevVert->x, *prevVert->y, *prevVert->z,
			   *vert->x, *vert->y, *vert->z,
			   *nextVert->x, *nextVert->y, *nextVert->z,
			   sz, width, azimuth, twist);
      sw->verts.push_back(v);
      EdgeNew* edge = createEdge(v, vert, false);
      sw->edges.push_back(edge);

      if (i != 0) {
	EdgeNew* middleEdge = createEdge(prevV, v, false);
	sw->edges.push_back(middleEdge);
      
	EdgeNew* eEdge = createEdge(v, prevVert, false);
	sw->edges.push_back(eEdge);
      
	std::list<Vert*> verts;
	verts.push_back(prevV);
	verts.push_back(prevVert);      
	verts.push_back(v);      
      
	std::list<EdgeNew*> edges;
	edges.push_back(prevEdge);
	edges.push_back(eEdge);
	edges.push_back(middleEdge);
      
	sw->faces.push_back(createFace(edges, verts));

	EdgeNew* bEdge = createEdge(vert, prevVert, false);
	sw->edges.push_back(eEdge);
      
	std::list<Vert*> verts2;
	verts2.push_back(vert);      
	verts2.push_back(prevVert);
	verts2.push_back(v);                
      
	std::list<EdgeNew*> edges2;
	edges2.push_back(bEdge);
	edges2.push_back(eEdge);
	edges2.push_back(edge);
      
	sw->faces.push_back(createFace(edges2, verts2));
      }

      prevVert = vert;
      prevV = v;
      prevEdge = edge;
      ++it;
      ++it2;
      //++edgeIt;
    }
  }
}

FaceNew* makeFace(MeshNew* mesh,Vert* x, Vert* y, Vert* z, Vert* w, Reader* reader) {
  std::list<Vert*> verts;
  verts.push_back(x);
  verts.push_back(y);
  verts.push_back(z);
  verts.push_back(w);
  
  auto face = createFace(verts, &mesh->edges, reader, false);
  mesh->faces.push_back(face);
  return face;
}

Vert* getFrenetFrameVertex(Vert* target, Vert* prev, Vert* curr, Vert* next, double azimuth, double twist, Reader* reader, bool flipZAxis) {
  double px = *prev->x;
  double py = *prev->y;
  double pz = *prev->z;

  double x = *curr->x;
  double y = *curr->y;
  double z = *curr->z;

  double nx = *next->x;
  double ny = *next->y;
  double nz = *next->z;
  
  double u1 = px - x;
  double u2 = py - y;
  double u3 = pz - z;

  double v1 = nx - x;
  double v2 = ny - y;
  double v3 = nz - z;

  if (false){//flipZAxis) {
    double t1 = u1;
    double t2 = u2;
    double t3 = u3;
    u1 = v1;
    u2 = v2;
    u3 = v3;
    v1 = t1;
    v2 = t2;
    v3 = t3;
  }

  // Cross product
  // Find y
  double yVector1 = u2 * v3 - u3 * v2;
  double yVector2 = u3 * v1 - u1 * v3;
  double yVector3 = u1 * v2 - u2 * v1;

  // Normalize y
  double ynorm = std::sqrt(yVector1*yVector1+yVector2*yVector2+yVector3*yVector3);
  yVector1 = yVector1 / ynorm;
  yVector2 = yVector2 / ynorm;
  yVector3 = yVector3 / ynorm;  

  // Find x
  //double flip = flipZAxis ? -1 : 1;  
  double xVector1 = v2 * yVector3 - v3 * yVector2;
  double xVector2 = v3 * yVector1 - v1 * yVector3;
  double xVector3 = v1 * yVector2 - v2 * yVector1;

  // Normalize x
  double xnorm = std::sqrt(xVector1*xVector1+xVector2*xVector2+xVector3*xVector3);
  xVector1 = xVector1 / xnorm;
  xVector2 = xVector2 / xnorm;
  xVector3 = xVector3 / xnorm;
  
  // Find z
  double zVector1 = xVector2 * yVector3 - xVector3 * yVector2;
  double zVector2 = xVector3 * yVector1 - xVector1 * yVector3;
  double zVector3 = xVector1 * yVector2 - xVector2 * yVector1;

  // Normalize z
  double znorm = std::sqrt(zVector1*zVector1+zVector2*zVector2+zVector3*zVector3);
  zVector1 = zVector1 / xnorm;
  zVector2 = zVector2 / xnorm;
  zVector3 = zVector3 / xnorm;

  
  // double angle = azimuth + twist;
  
  // rotate(angle, &yVector1, &yVector2, &yVector3, d1, d2, d3);


  // rotate(1.57, &xVector1, &xVector2, &xVector3, d1, d2, d3);

  // Bug?
  // double temp1 = yVector1;
  // double temp2 = yVector2;
  // double temp3 = yVector3;
  // yVector1 = xVector1;
  // yVector2 = xVector2;
  // yVector3 = xVector3;
  // xVector1 = temp1;
  // xVector2 = temp2;
  // xVector3 = temp3;

  double angle = azimuth + twist;
  rotate(angle, &xVector1, &xVector2, &xVector3, 0, 0, 1);
  rotate(angle, &yVector1, &yVector2, &yVector3, 0, 0, 1);
  
  // Target
  double tx = *target->x;
  double ty = *target->y;
  double tz = *target->z;

  // auto quaternion = Quaternion(azimuth, Vector3)
  // auto rotationMatrix = glm::rotate(glm::dmat4(), azimuth, glm::dvec3(0.0, 0.0, 1.0));
  // auto targetVector = glm::vec3(tx, ty, tz);
  // auto rc = rotationMatrix * targetVector;

  std::cerr << "xVector: (" << xVector1 << ", " << xVector3 << ", " << xVector3 << ")" << std::endl;
  std::cerr << "yVector: (" << yVector1 << ", " << yVector3 << ", " << yVector3 << ")" << std::endl;
  std::cerr << "zVector: (" << zVector1 << ", " << zVector3 << ", " << zVector3 << ")" << std::endl;
  
  // Change of basis
  return newVertex("dsad",
		   x + xVector1 * tx + yVector1 * ty + zVector1 * tz,
		   y + xVector2 * tx + yVector2 * ty + zVector2 * tz,
		   z + xVector3 * tx + yVector3 * ty + zVector3 * tz);
}

void frenetFrame(SweepNew* sw, std::list<Vert*> crosssection, double* width, double* azimuth, double* twist, Reader* reader) {
  int sz = sw->verts.size();
  int sz2 = crosssection.size();
  std::list<Vert*>::iterator it = sw->verts.begin();
  //std::list<EdgeNew*>::iterator edgeIt = sw->edges.begin();
  std::list<Vert*>::iterator it2 = sw->verts.begin();
  ++it2;
  Vert* prevVert = *(sw->verts.rbegin());
  Vert* prevV = 0;
  EdgeNew* prevEdge = 0;
  std::vector<Vert*> prevCrosssection;
  std::vector<Vert*> toBeDeleted;
  for (int i = 0; i < sz; ++i) {
    Vert* currVert = *it;
    Vert* nextVert;
    if (i == sz - 1) {
      nextVert = *sw->verts.begin();
    } else {
      nextVert = *it2;
    }

    if (i > 0) {
      sw->edges.push_back(createEdge(currVert, prevVert, false));
    }
      
    if (i == 0) {
      for (Vert* v: crosssection) {
	Vert* nv = getFrenetFrameVertex(v, prevVert, currVert, nextVert, *azimuth, *twist * (i / (double)sz), reader, i == sz - 1);
	//EdgeNew* edge = createEdge(currVert, nv, false);
	sw->verts.push_back(nv);
	//sw->verts.remove(currVert);
	//sw->edges.push_back(edge);
	prevCrosssection.push_back(nv);
      }
    } else {
      int j = 0;
      std::vector<Vert*> currCrosssection;      
      for (Vert* v: crosssection) {
	Vert* nv = getFrenetFrameVertex(v, prevVert, currVert, nextVert, *azimuth, *twist * (i / (double)sz), reader, i == sz - 1);
	//sw->verts.remove(currVert);	
	//EdgeNew* edge = createEdge(currVert, nv, false);
	sw->verts.push_back(nv);	  		
	//sw->edges.push_back(edge);
	if (j > 0) {
	  if (nv == 0) {
	    std::cerr << "New vertex is null" << std::endl;
	    exit(1);
	  }
	  if (currCrosssection[j-1] == 0) {
	    std::cerr << "currCrosssection[j-1] is null" << std::endl;
	    exit(1);
	  }
	  if (prevCrosssection[j-1] == 0) {
	    std::cerr << "prevCrosssection[j-1] is null" << std::endl;
	    exit(1);
	  }
	  if (prevCrosssection[j] == 0) {
	    std::cerr << "prevCrosssection[j] is null" << std::endl;
	    exit(1);
	  }
	  makeFace(sw, nv, currCrosssection[j-1], prevCrosssection[j-1], prevCrosssection[j], reader);
	}
	++j;
	currCrosssection.push_back(nv);
	}

      prevCrosssection = currCrosssection;
    }

    toBeDeleted.push_back(currVert);
    //sw->verts.remove(currVert);
    prevVert = currVert;
    ++it;
    ++it2;
  }

  // for (Vert* v: toBeDeleted) {
  //   sw->verts.remove(v);
  // }
}

///Sweep functions
SweepNew* createSweepNew(std::list<Vert*> verticesPolyline, std::list<Vert*> crosssection, double* width, double* azimuth, double* twist, Reader* reader)
{
  SweepNew* p0 = new SweepNew();
  //This behaviour depends on the parser
  p0->setName("polyline" + std::to_string(pIndex));
  p0->verts = verticesPolyline;

  EdgeNew * currentEdge;
  std::list<Vert*>::iterator it = verticesPolyline.begin();
  std::list<Vert*>::iterator it2 = verticesPolyline.begin();
  std::list<EdgeNew*> currentEdges;
  ++it2;
  std::cerr << verticesPolyline.size() << std::endl;
  std::cerr << crosssection.size() << std::endl;
  while (it != verticesPolyline.end()){
    if (it2 != verticesPolyline.end()){
      //currentEdge = createEdge(*it2, *it, false);
      it2++;
      //p0->edges.push_back(currentEdge);
    }
    it++;

  }

  frenetFrame(p0, crosssection, width, azimuth, twist, reader);
  
  pIndex++;

  return p0;
}

bool SweepNew::setName(std::string n)
{
  if(n.find(".") != std::string::npos && n.find(":") != std::string::npos)
    return false;
  name = "m:sw:" + n;
  bool error = updateNames();
  return error;
}


