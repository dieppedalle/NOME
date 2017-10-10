#include "Node.h"

Node::Node()
{
    name = prefix = "";
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
