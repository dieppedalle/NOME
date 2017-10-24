//
//  Transformation.h
//

#ifndef TransformationNew_h
#define TransformationNew_h

#include <stdio.h>

class TransformationNew{
public:
    virtual ~TransformationNew(){}
    void applyTransformation();
};

class Translate : public TransformationNew
{
public:
    double x;
    double y;
    double z;
};

class Scale : public TransformationNew
{
public:
    double x;
    double y;
    double z;
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
Scale* createScale(double x, double y, double z);
Translate* createTranslate(double x, double y, double z);


#endif /* TransformationNew_h */
