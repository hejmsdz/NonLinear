#include "bisection.h"

interval Bisection(interval a, interval b, Function *func, long double tolerance, int iterations, bool &reached) {
    check_interval(a, b, func);

    if (iterations < 1) {
        throw NOT_ENOUGH_ITERATIONS;
    }

    interval x, y, right, left, mid;
    x = hull(a, b);
    long double midpoint;
    reached = false;

    for (int i = 0; i < iterations; i++) {
        midpoint = median(x);
        left = interval(lower(x), midpoint);
        mid = interval(midpoint);
        right = interval(midpoint, upper(x));

        y = func->evaluate(mid);

        if (singleton(y) && cereq(y, 0.0l)) {
            reached = true;
            return mid;
        }

        if (width(x) < tolerance) {
            reached = true;
            break;
        }

        if (zero_in(func->evaluate(left))) {
            x = left;
        } else {
            x = right;
        }
    }

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
