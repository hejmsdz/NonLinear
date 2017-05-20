#ifndef FUNCTION_H
#define FUNCTION_H

#include <boost/numeric/interval.hpp>

typedef boost::numeric::interval<long double> interval;

class Function
{
public:
    virtual long double evaluate(long double x) = 0;
    virtual interval evaluate(interval x) = 0;
    virtual ~Function() {};
};

#endif // FUNCTION_H
