#ifndef REGULAFALSI_H
#define REGULAFALSI_H

#include "common.h"

template<typename T> T RegulaFalsi(T a, T b, Function *func) {
    check_interval(a, b, func);

    T fa, fb, v, x;
    int sign_fa, sign_v;

    fa = func->evaluate(a);
    fb = func->evaluate(b);
    sign_fa = sgn(fa);

    x = b - fb * (b - a) / (fb - fa);

    while (cerlt(a, x) && cerlt(x, b)) {
        v = func->evaluate(x);
        sign_v = sgn(v);

        if (sign_fa == sign_v) {
            a = x;
            fa = v;
        } else {
            b = x;
            fb = v;
        }

        x = b - fb * (b - a) / (fb - fa);
    }

    return x;
}

#endif // REGULAFALSI_H
