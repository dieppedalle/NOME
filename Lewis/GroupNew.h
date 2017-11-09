//
//  Group.h
//

#ifndef GROUPNEW_H
#define GROUPNEW_H

#include "InstanceNew.h"
#include <vector>

typedef class GroupNew : public Node
{
public:
    std::list<InstanceNew*> instances;
    bool setName(std::string n);
    bool updateNames();
    bool draw();
} GroupNew;

GroupNew* createGroup(std::list<InstanceNew*>);
GroupNew* createGroup(GroupNew*);

#endif /* Group_h */
