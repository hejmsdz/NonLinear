#ifndef SECANT_H
#define SECANT_H

#include "common.h"
#include <cmath>
#include <algorithm>

template<typename T> T Secant(T a, T b, Function *func) {
    using namespace boost::numeric::interval_lib;
    check_interval(a, b, func);

    T fa, fb, h, x, y;
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
        if (zero_in(x)) {
            return b;
        }

        h = b - a;
        x = b + fb*h/x;
        y = func->evaluate(x);
        if (overlap(a, x) || overlap(b, x) || zero_in(y)) {
            return x;
        }

        fa = fb;
        fb = y;
        a = b;
        b = x;
    }
}

#endif // SECANT_H
