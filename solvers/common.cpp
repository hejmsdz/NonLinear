#include "common.h"

void check_interval(long double a, long double b, Function *func) {
    if (a >= b) {
        throw WRONG_INTERVAL;
    }

    if (func->evaluate(a) * func->evaluate(b) > 0) {
        throw NO_REAL_ROOTS;
    }
}

void check_interval(interval a, interval b, Function *func) {
    if (posge(a, b)) {
        throw WRONG_INTERVAL;
    }

    if (posgt(func->evaluate(a) * func->evaluate(b), interval(0))) {
        throw NO_REAL_ROOTS;
    }
}

int sgn(long double x) {
    return (x > 0) - (x < 0);
}

int sgn(interval x) {
    try {
        if (x > 0) {
            return 1;
        }
        if (x < 0) {
            return -1;
        }
    } catch (boost::numeric::interval_lib::comparison_error &error) {
        // do nothing
    }
    return 0;
}

long double cerlt(long double x, long double y) {
    return x < y;
}

