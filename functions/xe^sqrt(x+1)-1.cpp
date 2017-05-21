#include "function.h"

long double evalFloat(long double x) {
	return x * exp(sqrt(x + 1)) - 1;
}

interval evalInterval(interval x) {
	return x * exp(sqrt(x + 1.0l)) - 1.0l;
}
