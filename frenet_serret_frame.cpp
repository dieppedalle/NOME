#ifndef FRENET_SERRET_FRAME_CPP
#define FRENET_SERRET_FRAME_CPP

#include "curvature.h"
#include "mesh.h"
#include <glm/gtx/rotate_vector.hpp>


vec3 Curvature::distanceVector(vec3 x, vec3 y) const
{
    vec3 z;
    z.x = x.x - y.x;
    z.y = x.y - y.y;
    z.z = x.z - y.z;
    return z;
}

vec3 Curvature::tangentVector(vec3 prev, vec3 curr, vec3 next) const
{
    vec3 leftVector = normalize(distanceVector(curr, next));
    vec3 rightVector = normalize(distanceVector(curr, prev));
    return distanceVector(leftVector, rightVector);
}

vec3 Curvature::normalVector(vec3 prev, vec3 curr, vec3 next) const
{
    vec3 leftVector = normalize(distanceVector(curr, next));
    vec3 rightVector = normalize(distanceVector(curr, prev));
    return cross(leftVector, rightVector);
}

void FrenetSerretFrame::makeRibbon(Mesh* ribbon) const
{
    int size = ribbon->vertList.size();
    int last = ribbon->vertList.size() - 1;
    unordered_map<int, vec3> binormals;
    for(int i = 0; i < size; ++i){
        ribbon->addVertex(nullptr);
    }
    for(int i = 0; binormals.size() != size; ++i, ++last){
        if(i == size && binormals.size() < 2){
            break;
        }else if(binormals.find(i%size) == binormals.end()){

            Vertex* previous = ribbon->vertList[last % size];
            Vertex* current = ribbon->vertList[i % size];
            Vertex* next = ribbon->vertList[(i+1) % size];

            vec3 normal = normalVector(previous->position, current->position, next->position);

            vec3 tangent = tangentVector(previous->position, current->position, next->position);

            vec3 binormalVector = normalize(cross(tangent, normal));

            if(isnan(binormalVector.x) || isnan(binormalVector.y) || isnan(binormalVector.z)){
                if(binormals.size() < 2){
                    continue;
                }else{
                    vec3 prevBinormal = binormals[(i-1)%size];
                    int j = i+1;
                    while(binormals.find(j%size) == binormals.end()){
                        ++j;
                    }
                    vec3 nextBinormal = binormals[j%size];
                    binormalVector = (prevBinormal + nextBinormal) * vec3(.5,.5,.5);
                }
            }

            vec3 vector = current->position + rotate(binormalVector,
                                 ribbon->azimuth + ribbon->twist * ((float)i/size), tangent) * vec3(ribbon->scale_factor, ribbon->scale_factor, ribbon->scale_factor);


            Vertex* v = new Vertex;
            v->ID = size+(i%size);
            v->name = "bs" + std::to_string(i%size);
            v->position =  vector;
            //v->params = nullptr;
            ribbon->vertList[(i%size)+size] = v;
            binormals[i%size] = binormalVector;
        }
    }
}

#endif // FRENET_SERRET_FRAME_CPP
