#ifndef COMMON_H
#define COMMON_H

#include "../function.h"

#define WRONG_INTERVAL 1
#define NO_REAL_ROOTS 2

void check_interval(long double a, long double b, Function *func, bool require_real_roots = true);
void check_interval(interval a, interval b, Function *func, bool require_real_roots = true);

int sgn(long double x);
int sgn(interval x);

#endif // COMMON_H
