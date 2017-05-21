#include "function.h"

long double evalFloat(long double x) {
	long double s = sin(x);
	return s * (s + 0.5) - 0.5;
}

interval evalInterval(interval x) {
	interval s = sin(x);
	return s * (s + 0.5l) - 0.5l;
}
