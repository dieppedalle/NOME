#ifndef CURVATURE_H
#define CURVATURE_H

#include <glm/glm.hpp>

using namespace glm;

class Mesh;

class Curvature
{
public:
    virtual void makeRibbon(Mesh*) const = 0;

protected:
    vec3 distanceVector(vec3 x, vec3 y) const;
    vec3 tangentVector(vec3 prev, vec3 curr, vec3 next) const;
    vec3 normalVector(vec3 prev, vec3 curr, vec3 next) const;
};

class MinimumTorsion: public Curvature
{
public:
    virtual void makeRibbon(Mesh*) const;

private:
};

class FrenetSerretFrame: public Curvature
{
public:
    virtual void makeRibbon(Mesh*) const;

private:
};

#endif // CURVATURE_H
