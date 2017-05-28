#ifndef REGULAFALSI_H
#define REGULAFALSI_H

#include "common.h"

interval RegulaFalsi(interval a, interval b, Function *func);
long double RegulaFalsi(long double a, long double b, Function *func);

#endif // REGULAFALSI_H
