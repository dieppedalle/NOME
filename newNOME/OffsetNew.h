//
//  SubdivisionNew.h
//

#ifndef Offset_h
#define OffsetNew_h

#include <stdio.h>
#include <list>
#include <string>
#include <QWidget>

class OffsetNew
{
public:
    std::string name;
    double * min;
    double * max;
    double * step;
    double value;
};

//Instantiation
OffsetNew* createOffset(std::string name, double *  min, double *  max, double *  step);

#endif /* OffsetNew_h */
