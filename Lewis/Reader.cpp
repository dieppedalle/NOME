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



///Low level reader functions
Surface* surf(std::string);
Surface* surf(int);
Vert* vert(std::string);
Vert* vert(VertI);
EdgeNew* edge(std::string);
EdgeNew* edge(EdgeI);
FaceNew* face(std::string);
FaceNew* face(FaceI);

//For the parser?
MeshNew* mesh(std::string);

///Reader convenience functions - these are the ones that should actually be called outside of this class
Surface* getSurf(std::string);
MeshNew* getMesh(std::string);
InstanceNew* getInstance(std::string);
Vert* getVert(std::string);
EdgeNew* getEdge(std::string);
FaceNew* getFace(std::string);
