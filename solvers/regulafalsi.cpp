#include "regulafalsi.h"
#define SGN(x) (((x) > 0) - ((x) < 0))

long double FloatingPoint::RegulaFalsi(long double a, long double b, Function *func) {
    check_interval(a, b, func);

    long double fa, fb, v, x;
    int sign_fa, sign_v;

    fa = func->evaluate(a);
    fb = func->evaluate(b);
    sign_fa = SGN(fa);

    x = b-fb*(b-a)/(fb-fa);

    while (a < x && x < b) {
        v = func->evaluate(x);
        sign_v = SGN(v);

        if (sign_fa == sign_v) {
            a = x;
            fa = v;
        } else {
            b = x;
            fb = v;
        }

        x = b-fb*(b-a)/(fb-fa);
    }

    return x;
}
