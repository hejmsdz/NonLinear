#ifndef BISECTION_H
#define BISECTION_H

#include "common.h"

#define NOT_ENOUGH_ITERATIONS 3

interval Bisection(interval a, interval b, Function *func, long double tolerance, int iterations, bool &reached);
long double Bisection(long double a, long double b, Function *func, long double tolerance, int iterations, bool &reached);

#endif // BISECTION_H
