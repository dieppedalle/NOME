//
//  Instance.h
//  model
//
//  Created by L on 21/09/2017.
//  Copyright © 2017 L. All rights reserved.
//

#ifndef BankNew_h
#define BankNew_h

#include <stdio.h>
#include <list>
#include <string>

class SetNew
{
public:
    std::string name;
    double value;
    double start;
    double end;
    double stepSize;
};

class BankNew
{
public:
    std::list<SetNew*> sets;
    std::string name;
};



//Instantiation
BankNew* createBank();
SetNew* createSet(std::string name, double value, double start, double end, double stepSize);


#endif /* BankNew_h */
