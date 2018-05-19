//
//  Bank.h
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
    int begValPosFile;
    int lengthValChar;
};

class BankNew
{
public:
    std::list<SetNew*> sets;
    std::string name;
    //bool draw();
};



//Instantiation
BankNew* createBank();
SetNew* createSet(std::string name, double value, double start, double end, double stepSize, int begValPosFile, int lengthValChar);


#endif /* BankNew_h */
