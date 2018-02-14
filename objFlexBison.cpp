// Wrapper class over the STL file parser.

#include "newNOME/Session.h"
#include "compilerObj/parserObj.hpp"

using namespace std;

class ObjCompiler {
  Session* currSession;
  public:
    ObjCompiler (string input) {
        extern FILE* objin;
        objin = fopen(input.c_str(), "r");
        currSession = createSession();
        //currSession->saveFileToStr(input);
        objparse(currSession);
    };

    Session* getSession () {return currSession;}
};
