#ifndef REGULAFALSI_H
#define REGULAFALSI_H

#include "common.h"

namespace FloatingPoint {
    long double RegulaFalsi(long double a, long double b, Function *func);
}

#endif // REGULAFALSI_H
