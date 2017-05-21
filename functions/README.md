# Sample functions

This directory contains a skeleton of function code that works with the program
along with three functions provided as an example in the book [1].
They should be compiled into a dynamic library (.so on Linux).

## Compilation

```
g++ -Wall -shared -fPIC -lboost_system -o outfile.so infile.cpp
```

## Writing your own functions

Use the following template:

```c++
#include "function.h"

long double evalFloat(long double x) {
	return x;
}

interval evalInterval(interval x) {
	return x;
}
```

and compile it using the command above.
You can use functions available in `cmath`and `boost::numeric::interval_lib`
(see the [documentation](http://www.boost.org/doc/libs/1_64_0/libs/numeric/interval/doc/interval.htm)).

## References

[1] A. Marciniak, D. Gregulec, J. Kaczmarek: *Podstawowe procedury numeryczne w języku Turbo Pascal*. Wydawnictwo Nakom, Poznań, 2000
