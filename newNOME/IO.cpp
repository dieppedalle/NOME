//
//  Error.cpp
//  model
//
//  Created by L on 28/08/2017.
//  Copyright © 2017 L. All rights reserved.
//

#include "IO.h"

void errorMessage(std::string msg, int no)
{
    std::cout << msg << std::endl;
    std::exit(no);
}