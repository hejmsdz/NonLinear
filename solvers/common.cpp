#include "common.h"

void check_interval(long double a, long double b, Function *func) {
    if (a >= b) {
        throw WRONG_INTERVAL;
    }

    if (func->evaluate(a) * func->evaluate(b) > 0) {
        throw NO_REAL_ROOTS;
    }
}
