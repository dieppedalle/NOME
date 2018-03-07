//
//  Transformation.h
//

#ifndef TransformationNew_h
#define TransformationNew_h

#include <stdio.h>
#include <list>
#include <string>

class TransformationNew{
public:
    virtual ~TransformationNew(){}
    void applyTransformation();
};

class Translate : public TransformationNew
{
public:
    double *x;
    double *y;
    double *z;

    std::string xStr;
    std::string yStr;
    std::string zStr;
};

class Scale : public TransformationNew
{
public:
    double *x;
    double *y;
    double *z;

    std::string xStr;
    std::string yStr;
    std::string zStr;
};

class Rotate : public TransformationNew
{
public:
    double *x;
    double *y;
    double *z;
    double *angle;

    std::string xStr;
    std::string yStr;
    std::string zStr;
    std::string angleStr;
};

class Reverse : public TransformationNew
{
public:
};

Rotate* createRotate(double *x, double *y, double *z, double *angle);
Scale* createScale(double *x, double *y, double *z);
Translate* createTranslate(double *x, double *y, double *z);
Reverse* createReverse();
void copyStateTransformation(TransformationNew * t, std::list<TransformationNew*> *transformations);

#endif /* TransformationNew_h */
