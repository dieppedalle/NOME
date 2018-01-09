// Wrapper class over the NOME parser.

#include "Lewis/Session.h"
#include "compilerNome\parser.hpp"

using namespace std;

class NOMECompiler {
  Session* currSession;
  public:
    NOMECompiler (string input) {
        extern FILE* nomin;
        nomin = fopen(input.c_str(), "r");
        currSession = createSession();
        currSession->saveFileToStr(input);
        nomparse(currSession);
    };

    Session* getSession () {return currSession;}
};
