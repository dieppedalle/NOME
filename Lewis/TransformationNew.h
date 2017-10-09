//
//  Instance.h
//  model
//
//  Created by L on 21/09/2017.
//  Copyright © 2017 L. All rights reserved.
//

#ifndef TransformationNew_h
#define TransformationNew_h

#include <stdio.h>

class TransformationNew{

};

class Translate : public TransformationNew
{
public:
    double x;
    double y;
    double z;
};

class Mirror : public TransformationNew
{
public:
    double x;
    double y;
    double z;
    double w;
};

class Rotate : public TransformationNew
{
public:
    double x;
    double y;
    double z;
    double angle;
};

Rotate* createRotate(double x, double y, double z, double angle);
Mirror* createMirror(double x, double y, double z, double w);
Translate* createTranslate(double x, double y, double z);


#endif /* TransformationNew_h */
