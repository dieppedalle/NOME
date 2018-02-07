#ifndef NODE_H
#define NODE_H

#include <stdio.h>
#include <list>
#include <vector>
#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <QColor>

/// Template class for items in the tree hierarchy, all tree nodes must have basic hierarchy name functionality
/// along with easy tree destructors
///


class Node
{
public:
    Node* parent;
    bool hasParent;
    std::string name;
    std::string prefix;

    Node();

    Node* vert(std::string);
    Node* edge(std::string);
    Node* face(std::string);
    Node* vert(int);
    Node* edge(int);
    Node* face(int);
    Node* surface();

    std::string getName();
    std::string getPrefix();
    std::string getFullName();

    bool setName(std::string n);
    bool setPrefix(std::string name);
    bool updateNames();
};

std::string findSubstring(std::string, char, std::string);

#endif // NODE_H
