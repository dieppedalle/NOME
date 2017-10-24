//
//  Reader.cpp
//

#include "Reader.h"

///Reader instantiation with various fields
//Instatiate reader with no treenode
Reader* createReader(Session* currSession)
{
    Reader* r0 = new Reader();
    r0->session = currSession;
    r0->assigned = false;
    return r0;
}

//Instantiate reader with treenode
Reader* createReader(Session* currSession, Node* node)
{
    Reader* r0 = new Reader();
    r0->session = currSession;
    r0->node = node;
    r0->assigned = true;
    return r0;
}

//Clone reader object
Reader* createReader(Reader r1)
{
    Reader* r0 = new Reader();
    r0->node = r1.node;
    r0->session = r1.session;
    r0->assigned = r1.assigned;
    return r0;
}



///Reader tree traversal
//Link a reader to a node
bool Reader::link(Node* n0)
{
    if(n0 == NULL)
        return false;
    node = n0;
    return true;
}

//Link a reader given string of the node
bool Reader::link(std::string s)
{
    Node* node = NULL;
    if(s[0] == 'm')
    {
        for(MeshNew* m0 : session->meshes)
        {
            if(m0->getName().compare(s) == 0)
                node = m0;
        }
    }
    else if(s[0] == 'i')
    {
        for(InstanceNew* i0 : session->instances)
        {
            if(i0->getName().compare(s) == 0)
                node = i0;
        }
    }
    return link(node);
}

//Search tree for given string
bool Reader::search(std::string s, int mode)
{
    //Loop through string to find
    std::string delimiter = ".";
    size_t pos = 0;
    std::string token;
    bool found = false;
    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        if(token[0] == 'i' && mode == 1)
        {
            found = true;
            link(token);
        }
        else if (token[0] == 'm')
        {
            found = true;
            link(token);
        }
        s.erase(0, pos + delimiter.length());
    }

    return found;
}



///For the parser?
Surface* Reader::surf(std::string n)
{
    for(Surface* s : session->surfaces)
        {
            if(!n.compare(s->name))
                return s;
        }
        return NULL;
}



///Low level reader functions
Vert* Reader::vert(std::string n)
{
    return (Vert*) node->vert(n);
}

Vert* Reader::vert(VertI i)
{
    return (Vert*) node->vert(i);
}

EdgeNew* Reader::edge(std::string n)
{
    return (EdgeNew*) node->edge(n);
}

EdgeNew* Reader::edge(EdgeI i)
{
    return (EdgeNew*) node->edge(i);
}

FaceNew* Reader::face(std::string n)
{
    return (FaceNew*) node->edge(n);
}

FaceNew* Reader::face(FaceI i)
{
    return (FaceNew*) node->edge(i);
}

//For the parser?
MeshNew* Reader::mesh(std::string name){
    for(MeshNew* m : session->meshes)
    {
        if(!name.compare(m->getName()))
            return m;
    }
    for(MeshNew* m : session->polylines)
    {
        if(!name.compare(m->getName()))
            return m;
    }
    for(MeshNew* c : session->circles)
    {
        if(!name.compare(c->getName()))
            return c;
    }
    for(FunnelNew* f : session->funnels)
    {
        if(!name.compare(f->getName()))
            return f;
    }
    for(TunnelNew* t : session->tunnels)
    {
        if(!name.compare(t->getName()))
            return t;
    }

    return NULL;
}

///Reader convenience functions - these are the ones that should actually be called outside of this class
MeshNew* Reader::getMesh(std::string name)
{
    for (MeshNew* m0 : session->meshes){
        std::string currentName = "m:" + name;
        if(m0->name.compare(currentName) == 0)
            return m0;
    }

    if(search(name, 0))
        return (MeshNew*) node;
    return NULL;
}

InstanceNew* Reader::getInstance(std::string name)
{
    if(node->getFullName().compare(name) == 0)
        return (InstanceNew*) node;
    if(search(name, 1))
        return (InstanceNew*) node;
    return NULL;
}

Vert* Reader::getVert(std::string name)
{
    // Check for definitions first
    for (Vert* v0 : session->verts){
        if(v0->name.compare(name) == 0)
            return v0;
    }

    // Check for inside meshes and instances
    if(node->getFullName().find(name) != std::string::npos)
        return (Vert*) node->vert(name);
    if(!search(name, 0))
        return NULL;
    return (Vert*) node->vert(name);
}

EdgeNew* Reader::getEdge(std::string name)
{
    if(node->getFullName().find(name) != std::string::npos)
        return (EdgeNew*) node->edge(name);
    if(!search(name, 0))
        return NULL;
    return (EdgeNew*) node->edge(name);
}

FaceNew* Reader::getFace(std::string name)
{
    if(node->getFullName().find(name) != std::string::npos)
        return (FaceNew*) node->face(name);
    if(!search(name, 0))
        return NULL;
    return (FaceNew*) node->face(name);
}
