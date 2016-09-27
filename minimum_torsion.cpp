#include "curvature.h"
#include "mesh.h"
#include <glm/gtx/rotate_vector.hpp>

vec3 distanceVector(vec3 x, vec3 y)
{
    vec3 z;
    z.x = x.x - y.x;
    z.y = x.y - y.y;
    z.z = x.z - y.z;
    return z;
}

vec3 scale(vec3 x, float y)
{
    vec3 z;
    z.x = x.x * y;
    z.y = x.y * y;
    z.z = x.z * y;
    return z;
}

vec3 getNext(vec3 x, vec3 y, vec3 z, vec3 t)
{
    vec3 f = cross(distanceVector(x,y),distanceVector(z,t));
    return f;
}

vec3 normalByThreePoints(vec3 before, vec3 x, vec3 after)
{
    vec3 prev = x+normalize(distanceVector(x, before));
    vec3 next = x+normalize(distanceVector(x, after));
    vec3 normal = distanceVector(next,prev);
    return normal;
}

vec3 rotate(float ang, vec3 vec, vec3 before, vec3 x, vec3 after){
    vec3 final = rotate(vec, ang, normalByThreePoints(before,x,after));
    return final;
}

void MinimumTorsion::makeRibbon(Mesh* ribbon) const
{
    bool flag = false;
    bool pass = false;
    vec3 prev;
    int s = ribbon->vertList.size();
    int l = ribbon->vertList.size() - 1;
    for(int i = 0; i < s; ++i){
        vec3 final = getNext(ribbon->vertList[i%s]->position,
                ribbon->vertList[(i+1)%s]->position,
                ribbon->vertList[l%s]->position, ribbon->vertList[i%s]->position);
        if(!flag){
            prev = final;
            flag = true;
        }
        else{
            final = reflect(final, prev);
        }
        if(std::isnan(final.x) && std::isnan(final.y) && std::isnan(final.z)){
            final = distanceVector(ribbon->vertList[ribbon->vertList.size() - 1]->position, ribbon->vertList[l%s]->position);
        }

        float az = ribbon->azimuth;
        float tw = ribbon->twist * ((float)i/s);
        final = rotate(az+tw, final, ribbon->vertList[l%s]->position, ribbon->vertList[i%s]->position, ribbon->vertList[(i+1)%s]->position);
        final = scale(normalize(final),ribbon->scale_factor);
        Vertex* v = new Vertex;
        v->position = vec3(ribbon->vertList[i%s]->position.x + final.x,
                ribbon->vertList[i%s]->position.y + final.y,
                ribbon->vertList[i%s]->position.z + final.z);
        v->ID = s+i;
        v->name = "bc" + to_string(s+i);
        v->params = nullptr;
        ribbon->addVertex(v);
        ++l;
    }
}
