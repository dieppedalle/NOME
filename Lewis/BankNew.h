//
//  Bank.h
//

#ifndef BankNew_h
#define BankNew_h

#include <stdio.h>
#include <list>
#include <string>
#include <QWidget>

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
    //bool draw();
};



//Instantiation
BankNew* createBank();
SetNew* createSet(std::string name, double value, double start, double end, double stepSize);


#endif /* BankNew_h */
