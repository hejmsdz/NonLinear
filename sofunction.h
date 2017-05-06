#ifndef SOFUNCTION_H
#define SOFUNCTION_H

#include "function.h"

typedef long double(*evaluate_function)(long double);

class SOFunction : public Function
{
    void *lib;
    evaluate_function f;
public:
    SOFunction(char library_path[]);
    long double evaluate(long double x);
    virtual ~SOFunction();
};

#endif // SOFUNCTION_H
