#ifndef COMMON_H
#define COMMON_H

#include "../function.h"
#include <boost/io/ios_state.hpp>

#define WRONG_INTERVAL 1
#define NO_REAL_ROOTS 2

void check_interval(long double a, long double b, Function *func);
void check_interval(interval a, interval b, Function *func);

int sgn(long double x);
int sgn(interval x);

inline bool cerlt(long double x, long double y) {
    return x < y;
}

inline bool zero_in(long double x) {
    return x == 0;
}

inline bool overlap(long double x, long double y) {
    return x == y;
}

inline long double upper(long double x) {
    return x;
}

inline long double lower(long double x) {
    return x;
}

inline long double hull(long double x, long double y) {
    return (x + y) / 2.0l;
}


#endif // COMMON_H
