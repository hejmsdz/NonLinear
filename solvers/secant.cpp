#include "secant.h"

#include <cmath>
#include <algorithm>

interval Secant(interval a, interval b, Function *func) {
    check_interval(a, b, func);

    interval fa, fb, h, x, fx;
    h = (b - a) * 0.179372l;
    a += h;
    b -= h;
    fa = func->evaluate(a);
    fb = func->evaluate(b);

    if (cerlt(abs(fa), abs(fb))) {
        std::swap(a, b);
        std::swap(fa, fb);
    }

    while (true) {
        if (zero_in(fa - fb)) {
            break;
        }

        x = b + fb * (b - a) / (fa - fb);
        fx = func->evaluate(x);
        if (overlap(a, x) || overlap(b, x) || (singleton(fx) && zero_in(fx))) {
            break;
        }

        fa = fb;
        fb = fx;
        a = b;
        b = x;
    }

    return hull(x, hull(a, b));
}

long double Secant(long double a, long double b, Function *func) {
    check_interval(a, b, func);

    long double fa, fb, h, x, fx;
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
        if (fa - fb == 0.0l) {
            return b;
        }

        x = b + fb * (b - a) / (fa - fb);
        fx = func->evaluate(x);
        if (a == x || b == x || fx == 0.0l) {
            return x;
        }

        fa = fb;
        fb = fx;
        a = b;
        b = x;
    }
}
