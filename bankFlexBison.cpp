// Wrapper class over the STL file parser.
#include <newNOME/Session.h>
#include "compilerBank/parserBank.hpp"

using namespace std;

class BankCompiler {
  public:
    BankCompiler (const char* input, Session* sessionParse, double* output, int lineNumber) {
        extern double parse_string(const char* in, Session* sessionParse, int lineNumber);
        *output = parse_string(input, sessionParse, lineNumber) ;
    };
};
