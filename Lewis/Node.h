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

class Node
{
public:
    std::string name;
    std::string prefix;

    Node();

    std::string getName();
    std::string getPrefix();
    std::string getFullName();

    bool setName(std::string n);
    bool setPrefix(std::string name);
    bool updateNames();
};

#endif // NODE_H
