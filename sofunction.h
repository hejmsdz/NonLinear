#ifndef SOFUNCTION_H
#define SOFUNCTION_H

#include "function.h"

typedef long double(*evalFloatType)(long double);
typedef interval(*evalIntervalType)(interval);

class SOFunction : public Function
{
    void *lib;
    evalFloatType evalFloat;
    evalIntervalType evalInterval;
public:
    SOFunction(char library_path[]);
    long double evaluate(long double x);
    interval evaluate(interval x);
    virtual ~SOFunction();
};

#endif // SOFUNCTION_H
