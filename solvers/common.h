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
long double cerlt(long double x, long double y);

#endif // COMMON_H
