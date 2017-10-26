//
//  Session.cpp
//  model
//
//  Created by L on 26/08/2017.
//  Copyright © 2017 L. All rights reserved.
//

#include "Session.h"
#include "Reader.h"
#include <fstream>
#include <glm/glm.hpp>

static int sIndex = 0;

Session* createSession()
{
    Session* session0 = new Session();
    session0->setName("s:" + std::to_string(sIndex));
    sIndex++;
    std::cout << session0->getName() << std::endl;

    return session0;
}

Session* createSession(Session* s0)
{
    return NULL;
}

bool Session::setName(std::string n)
{
    name = n;
    return updateNames();
}

std::string Session::getName()
{
    return name;
}

bool Session::updateNames()
{
    for(Vert* v0 : verts)
    {
        v0->setPrefix(name);
    }
    for(EdgeNew* e0 : edges)
    {
        e0->setPrefix(name);
    }
    for(FaceNew* f0 : faces)
    {
        f0->setPrefix(name);
    }
    for(GroupNew* g0 : groups)
    {
        g0->setPrefix(name);
        g0->updateNames();
    }
    for(MeshNew* m0 : meshes)
    {
        m0->setPrefix(name);
        m0->updateNames();
    }
    return true;
}

void Session::selectVert(GLint hits, GLuint *names, GLdouble posX, GLdouble posY, GLdouble posZ){
    if(hits > 0) {
        glm::vec3 hit_position = glm::vec3(posX, posY, posZ);
        float min_distance = std::numeric_limits<float>::max();
        Vert * selectedVertex = NULL;
        Reader* currReader = createReader(this);

        for (int i = 0; i < hits; i++) {
            int currentID = names[i * 4 + 3];

            Vert * currentVertex = currReader->getVert(currentID);

            if (currentVertex != NULL){
                glm::vec3 vertex_position = glm::vec3(*(currentVertex->x), *(currentVertex->y), *(currentVertex->z));

                float new_distance = distance(vertex_position, hit_position);

                if(new_distance < min_distance) {
                    min_distance = new_distance;
                    selectedVertex = currentVertex;
                }
            }
        }
        if (selectedVertex != NULL){
            selectedVertex -> selected = !selectedVertex -> selected;
            if (selectedVertex -> selected == true){
                selectedVerts.push_back(selectedVertex);
            }
            else{
                selectedVerts.remove(selectedVertex);
            }
        }

    }
}

void Session::selectEdge(GLint hits, GLuint *names, GLdouble posX, GLdouble posY, GLdouble posZ){
    if(hits > 0) {
        glm::vec3 hit_position = glm::vec3(posX, posY, posZ);
        float min_distance = std::numeric_limits<float>::max();
        Reader* currReader = createReader(this);
        EdgeNew * currentEdge;
        EdgeNew * selectedEdge;

        for (int i = 0; i < hits; i++) {
            int currentID = names[i * 4 + 3];
            currentEdge = currReader->edge(currentID);
            if (currentEdge != NULL){
                std::cout << currentEdge->name << std::endl;
                //selectedFace = currentFace;
            }
        }

        //selectedFace -> selected = !selectedFace -> selected;
    }
}

void Session::selectFace(GLint hits, GLuint *names, GLdouble posX, GLdouble posY, GLdouble posZ){
    if(hits > 0) {
        glm::vec3 hit_position = glm::vec3(posX, posY, posZ);
        float min_distance = std::numeric_limits<float>::max();
        Reader* currReader = createReader(this);
        FaceNew * currentFace;
        FaceNew * selectedFace;

        for (int i = 0; i < hits; i++) {
            int currentID = names[i * 4 + 3];
            currentFace = currReader->getFace(currentID);
            if (currentFace != NULL){
                std::cout << currentFace->name << std::endl;
                selectedFace = currentFace;
                break;
            }
        }

        if (selectedFace != NULL){
            selectedFace -> selected = !selectedFace -> selected;
        }
    }
}

void Session::SaveSession(std::string outputFile){
    ofstream file(outputFile);
    if (!file.is_open())
    {
        cout <<"Error: COULD NOT OPEN THE FILE.\n";
    }

    for (Surface* s : surfaces){
        file<<"surface " << s->name << " color (" << *s->r << " " << *s->g << " " << *s->b << ") endsurface\n";
    }
    if (surfaces.size() != 0){
        file << "\n";
    }

    for (BankNew* b : banks){
        file << "bank " << b->name << "\n";
        for (SetNew* s : b->sets){
            file << "set " << s->name << " " << s->value << " " << s->start << " " << s->end << " " << s->stepSize << "\n";
        }
        file << "endbank\n\n";
    }

    for (Vert* p : verts){
        file << "point " << p->name << " (" << *p->x << " " << *p->y << " " << *p->z << ") endpoint\n";
    }
    if (verts.size() != 0){
        file << "\n";
    }

    for (FaceNew* f : faces){
        file << "face " << f->name << " (";
        for (Vert* v : f->verts){
            file << v->name << " ";
        }
        file << ") endface\n";
    }

    if (faces.size() != 0){
        file << "\n";
    }

    for (PolylineNew* p : polylines){
        file << "polyline " << p->name << " (";
        for (Vert* v : p->verts){
            file << v->name << " ";
        }
        file << ") endpolyline\n";
    }

    if (polylines.size() != 0){
        file << "\n";
    }

    for (FunnelNew* f : funnels){
        file << "funnel " << f->name << "(" << f->n << " " << f->ro << " " << f->ratio << f->h << ") endfunnel\n";
    }
    if (funnels.size() != 0){
        file << "\n";
    }

    for (TunnelNew* t : tunnels){
        file << "tunnel " << t->name << "(" << t->n << " " << t->ro << " " << t->ratio << t->h << ") endtunnel\n";
    }
    if (tunnels.size() != 0){
        file << "\n";
    }

    for (CircleNew* c : circles){
        file << "circle " << c->name << "(" << c->num << " " << c->rad << ") endcircle\n";
    }
    if (circles.size() != 0){
        file << "\n";
    }

    for (MeshNew* m : meshes){
        file << "mesh " << m->name << "\n";
        for (FaceNew* f : m->faces){
            file << "face " << f->name << " (";
            for (Vert* v : f->verts){
                file << v->name << " ";
            }
            file << ") endface\n";
        }
        file << "endmesh\n\n";
    }

    for (InstanceNew* i : instances){
        file << "instance " << i->name << " " << i->mesh->name << " endinstance\n";
    }

    if (instances.size() != 0){
        file << "\n";
    }


}
