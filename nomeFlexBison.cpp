// Wrapper class over the NOME parser.

#include "newNOME/Session.h"
#include "compilerNome/parser.hpp"

using namespace std;

class NOMECompiler {
  Session* currSession;
  public:
    NOMECompiler (string input) {
        currSession = new Session();
        currSession->saveFileToStr(input);
		currSession->parseSavedStr();
    };

    Session* getSession () {return currSession;}
};
