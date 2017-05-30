#include "regulafalsi.h"

interval RegulaFalsi(interval a, interval b, Function *func) {
    check_interval(a, b, func);

    interval fa, fb, fx, x;
    int sign_fa, sign_fx;

    fa = func->evaluate(a);
    fb = func->evaluate(b);
    sign_fa = sgn(fa);

    x = b - fb * (b - a) / (fb - fa);
    while (upper(a) < lower(x) && upper(x) < lower(b)) {
        fx = func->evaluate(x);
        sign_fx = sgn(fx);

        if (sign_fa == sign_fx) {
            a = x;
            fa = fx;
        } else if (sign_fa == -sign_fx) {
            b = x;
            fb = fx;
        } else {
            break;
        }

        if (zero_in(fb - fa)) {
            break;
        }

        x = b - fb * (b - a) / (fb - fa);
    }

    return x;
}

long double RegulaFalsi(long double a, long double b, Function *func) {
    check_interval(a, b, func);

    long double fa, fb, fx, x;
    int sign_fa, sign_fx;

    fa = func->evaluate(a);
    fb = func->evaluate(b);
    sign_fa = sgn(fa);

    x = b - fb * (b - a) / (fb - fa);

    while (a < x && x < b) {
        fx = func->evaluate(x);
        sign_fx = sgn(fx);

        if (sign_fa == sign_fx) {
            a = x;
            fa = fx;
        } else {
            b = x;
            fb = fx;
        }

        x = b - fb * (b - a) / (fb - fa);
    }

    return x;
}
