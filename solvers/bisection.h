#ifndef BISECTION_H
#define BISECTION_H

#include "common.h"

#define NOT_ENOUGH_ITERATIONS 3

template<typename T> T Bisection(T a, T b, Function *func, long double tolerance, int iterations, bool &reached) {
    check_interval(a, b, func);

    if (iterations < 1) {
        throw NOT_ENOUGH_ITERATIONS;
    }

    T fa, fb, x;
    int i = 0;
    reached = false;
    do {
        ++i;
        x = a + (b - a) / 2.0l;
        fa = func->evaluate(a);
        if (zero_in(fa) || (upper(b) - lower(a)) / 2.0l < tolerance) {
            reached = true;
            break;
        }

        fa = func->evaluate(a);
        fb = func->evaluate(x);

        if (fa * fb > 0) {
            a = x;
        } else {
            b = x;
        }
    } while (i < iterations && !reached);

    return hull(a, b);
}

#endif // BISECTION_H
