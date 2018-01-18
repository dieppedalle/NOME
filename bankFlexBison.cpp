// Wrapper class over the STL file parser.
#include <Lewis/Session.h>
#include "compilerBank\parserBank.hpp"

using namespace std;

class BankCompiler {
  public:
    BankCompiler (const char* input, Session* sessionParse, double* output) {
        extern double parse_string(const char* in, Session* sessionParse);
        *output = parse_string(input, sessionParse) ;
    };
};
