//
//  Group.h
//

#ifndef GroupNew_h
#define GroupNew_h

#include "InstanceNew.h"
#include <vector>

class GroupNew : public Node
{
public:
    std::list<InstanceNew*> instances;
    bool setName(std::string n);
    bool updateNames();
};

GroupNew* createGroup(std::list<InstanceNew*>);
GroupNew* createGroup(GroupNew*);

#endif /* Group_h */
