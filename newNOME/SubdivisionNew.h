//
//  SubdivisionNew.h
//

#pragma once

#include <stdio.h>
#include <list>
#include <string>
#include <QWidget>

class SubdivisionNew
{
public:
    std::string name;
    std::string type;
    double value;
    double* subdivisions;
    double previousSubdivisionLevel;
};

//Instantiation
SubdivisionNew* createSubdivision(std::string name, std::string type, double * subdivisions);
