//
//  Session.h
//  model
//
//  Created by L on 26/08/2017.
//  Copyright © 2017 L. All rights reserved.
//

#ifndef Session_h
#define Session_h

#include <stdio.h>
#include "Data.h"

typedef struct Session
{
private:
    int accesses;

public:
    std::vector<Vert*> verts;
    std::vector<EdgeNew*> edges;
    std::vector<FaceNew*> faces;
} Session;

Session* createSession();
Session* createSession(Session*);

#endif /* Session_h */
