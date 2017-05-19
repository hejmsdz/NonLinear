#include "bisection.h"

long double FloatingPoint::Bisection(long double a, long double b, Function *func, long double tolerance, int iterations, bool &reached) {
    if (iterations < 1) {
        throw NOT_ENOUGH_ITERATIONS;
    }

    long double fa, fb, x;
    int i = 0;
    reached = false;
    do {
        i++;
        x = a + (b - a)/2;
        fa = func->evaluate(a);
        if (fa == 0 || (b-a)/2 < tolerance) {
            reached = true;
        } else {
            fa = func->evaluate(a);
            fb = func->evaluate(x);

            if (fa * fb > 0) {
                a = x;
            } else {
                b = x;
            }
        }
    } while (i < iterations && !reached);

    return x;
}
