#ifndef SECANT_H
#define SECANT_H

#include "common.h"

#include <cmath>
#include <algorithm>

interval Secant(interval a, interval b, Function *func);
long double Secant(long double a, long double b, Function *func);

#endif // SECANT_H
