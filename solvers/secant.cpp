#include "secant.h"
#include <cmath>
#include <algorithm>

long double FloatingPoint::Secant(long double a, long double b, Function *func) {
    check_interval(a, b, func);

    long double fa, fb, h, x, y;
    h = 0.179372 * (b - a);
    a = a + h;
    b = b - h;
    fa = func->evaluate(a);
    fb = func->evaluate(b);

    if (fabs(fa) < fabs(fb)) {
        std::swap(a, b);
        std::swap(fa, fb);
    }

    while (true) {
        x = fa - fb;
        if (x == 0) {
            return b;
        }

        h = b - a;
        x = b + fb*h/x;
        y = func->evaluate(x);
        if (x == a || x == b || y == 0) {
            return x;
        }

        fa = fb;
        fb = y;
        a = b;
        b = x;
    }
}
