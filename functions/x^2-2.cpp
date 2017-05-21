#include "function.h"

long double evalFloat(long double x) {
	return x*x - 2;
}

interval evalInterval(interval x) {
	return square(x) - 2.0l;
}
