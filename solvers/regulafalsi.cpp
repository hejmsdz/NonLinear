#include "regulafalsi.h"

interval RegulaFalsi(interval a, interval b, Function *func) {
    using namespace boost::numeric::interval_lib;
    check_interval(a, b, func);

    interval fa, fb, v, x;
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

    if (sign_fa == +1) {
        return hull(a, x);
    } else {
        return hull(x, b);
    }
}

long double RegulaFalsi(long double a, long double b, Function *func) {
    check_interval(a, b, func);

    long double fa, fb, v, x;
    int sign_fa, sign_v;

    fa = func->evaluate(a);
    fb = func->evaluate(b);
    sign_fa = sgn(fa);

    x = b - fb * (b - a) / (fb - fa);

    while (a < x && x < b) {
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
