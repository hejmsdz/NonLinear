#ifndef BACKEND_H
#define BACKEND_H

#include <string>
#include "function.h"

class Backend
{
    Function *function = nullptr;

public:
    Backend();
    ~Backend();

    void loadFunction(char filename[]);
    std::string solveFloatingPoint(std::string &a, std::string &b);
};

#endif // BACKEND_H
