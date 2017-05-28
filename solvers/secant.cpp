#include "secant.h"

#include <cmath>
#include <algorithm>

interval Secant(interval a, interval b, Function *func) {
    using namespace boost::numeric::interval_lib;
    check_interval(a, b, func);

    interval fa, fb, h, x, y;
    h = (b - a) * 0.179372l;
    a = a + h;
    b = b - h;
    fa = func->evaluate(a);
    fb = func->evaluate(b);

    if (cerlt(abs(fa), abs(fb))) {
        std::swap(a, b);
        std::swap(fa, fb);
    }

    while (true) {
        x = fa - fb;
        if (zero_in(x)) {
            return b;
        }

        h = b - a;
        x = b + fb*h/x;
        y = func->evaluate(x);
        if (overlap(a, x) || overlap(b, x) || zero_in(y)) {
            return hull(a, b);
        }

        fa = fb;
        fb = y;
        a = b;
        b = x;
    }
}

long double Secant(long double a, long double b, Function *func) {
    check_interval(a, b, func);

    long double fa, fb, h, x, y;
    h = (b - a) * 0.179372l;
    a = a + h;
    b = b - h;
    fa = func->evaluate(a);
    fb = func->evaluate(b);

    if (abs(fa) < abs(fb)) {
        std::swap(a, b);
        std::swap(fa, fb);
    }

    while (true) {
        x = fa - fb;
        if (x == 0.0l) {
            return b;
        }

        h = b - a;
        x = b + fb*h/x;
        y = func->evaluate(x);
        if (a == x || b == x || y == 0.0l) {
            return x;
        }

        fa = fb;
        fb = y;
        a = b;
        b = x;
    }
}
