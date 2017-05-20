#include "sofunction.h"
#include <dlfcn.h>
#include <iostream>

SOFunction::SOFunction(char library_path[])
{
    lib = dlopen(library_path, RTLD_LAZY);
    if (!lib) {
        throw dlerror();
    }
    evalFloat = (evalFloatType)dlsym(lib, "evalFloat");
    evalInterval = (evalIntervalType)dlsym(lib, "evalInterval");
    if (!evalFloat || !evalInterval) {
        throw dlerror();
    }
}

long double SOFunction::evaluate(long double x)
{
    return evalFloat(x);
}

interval SOFunction::evaluate(interval x)
{
    return evalInterval(x);
}

SOFunction::~SOFunction()
{
    dlclose(lib);
}
