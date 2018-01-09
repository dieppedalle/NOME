// Wrapper class over the STL file parser.

#include "Lewis/Session.h"
#include "compilerStl\parserStl.hpp"

using namespace std;

class StlCompiler {
  Session* currSession;
  public:
    StlCompiler (string input) {
        extern FILE* stlin;
        stlin = fopen(input.c_str(), "r");
        currSession = createSession();
        //currSession->saveFileToStr(input);
        stlparse(currSession);
    };

    Session* getSession () {return currSession;}
};
