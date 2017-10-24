#include "Node.h"

Node::Node()
{
    name = prefix = "";
}

//These functions are defaulted to returning NULL, redefine functionality in subclasses
Node* Node::vert(std::string)
{
    return NULL;
}

Node* Node::edge(std::string)
{
    return NULL;
}

Node* Node::face(std::string)
{
    return NULL;
}

Node* Node::vert(int)
{
    return NULL;
}

Node* Node::edge(int)
{
    return NULL;
}

Node* Node::face(int)
{
    return NULL;
}

Node* Node::surface()
{
    return NULL;
}

///Set local name of node element
bool Node::setName(std::string n)
{
    name = n;
    this->updateNames();
    return true;
}

///Set hierarchy prefix of node element
bool Node::setPrefix(std::string name)
{
    prefix = name;
    return true;
}

///Update names of node elements below current element in tree
bool Node::updateNames()
{
    return true;
}

///Get local name of element
std::string Node::getName()
{
    return name;
}

///Get hierarchy prefix of element
std::string Node::getPrefix()
{
    return prefix;
}

///Obtain full hierarchical name of element
std::string Node::getFullName()
{
    return prefix + '.' + name;
}
