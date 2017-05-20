#ifndef BACKEND_H
#define BACKEND_H

#include <string>
#include "function.h"

class Backend
{
    Function *function = nullptr;

    static long double stringToFloat(const std::string &value);
    static interval stringToInterval(const std::string &value, char separator = ':');
public:
    Backend();
    ~Backend();

    void loadFunction(char filename[]);
    std::string solveFloatingPoint(const std::string &a, const std::string &b);
    std::string solveInterval(const std::string &a, const std::string &b);
};

#endif // BACKEND_H
