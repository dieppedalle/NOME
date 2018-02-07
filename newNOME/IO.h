//
//  IO.h
//  model
//

#ifndef IO_h
#define IO_h

#include <iostream>
#include <stdio.h>
#include <string>

///Print an error message with desired exit code
void errorMessage(std::string msg, int exit);

///Print message to console
void printMessage(std::string msg);

#endif /* IO_h */
