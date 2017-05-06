#include "sofunction.h"
#include <dlfcn.h>
#include <iostream>

SOFunction::SOFunction(char library_path[])
{
    lib = dlopen(library_path, RTLD_LAZY);
    if (!lib) {
        throw dlerror();
    }
    f = (evaluate_function)dlsym(lib, "evaluate");
    if (!f) {
        throw dlerror();
    }
}

long double SOFunction::evaluate(long double x)
{
    return f(x);
}

SOFunction::~SOFunction()
{
    dlclose(lib);
}
