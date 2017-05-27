#ifndef BISECTION_H
#define BISECTION_H

#include "common.h"
#include "../backend.h"
#include <iostream>

#define NOT_ENOUGH_ITERATIONS 3

interval Bisection(interval a, interval b, Function *func, long double tolerance, int iterations, bool &reached) {
    check_interval(a, b, func);

    if (iterations < 1) {
        throw NOT_ENOUGH_ITERATIONS;
    }

    interval x, y;
    interval right, left, mid;
    x = hull(a, b);
    long double midpoint;

    int i = 0;
    reached = false;
    do {
        ++i;

        midpoint = median(x);
        left = interval(lower(x), midpoint);
        mid = interval(midpoint);
        right = interval(midpoint, upper(x));

        y = func->evaluate(mid);
        std::cout << Backend::intervalToString(x) << Backend::intervalToString(func->evaluate(x)) << std::endl;

        if ((singleton(y) && cereq(y, 0.0l))) {
            reached = true;
            return mid;
        }

        if (width(x) < tolerance) {
            reached = true;
            break;
        }

        if (zero_in(func->evaluate(left))) {
            x = left;
        } else if (zero_in(func->evaluate(right))) {
            x = right;
        } else {
            throw -100;
        }
    } while (i < iterations);

    return x;
}


long double Bisection(long double a, long double b, Function *func, long double tolerance, int iterations, bool &reached) {
    check_interval(a, b, func);

    if (iterations < 1) {
        throw NOT_ENOUGH_ITERATIONS;
    }

    long double fa, x, fx;
    int i = 0;
    reached = false;
    do {
        ++i;
        x = (a + b) / 2.0l;
        fa = func->evaluate(x);
        if (fa == 0.0l || (b - a) / 2.0l < tolerance) {
            reached = true;
            break;
        }

        fa = func->evaluate(a);
        fx = func->evaluate(x);

        if (fa * fx > 0) {
            a = x;
        } else {
            b = x;
        }
    } while (i < iterations && !reached);

    return x;
}

#endif // BISECTION_H
