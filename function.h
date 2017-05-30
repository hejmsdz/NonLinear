#ifndef FUNCTION_H
#define FUNCTION_H

#include <boost/numeric/interval.hpp>

typedef boost::numeric::interval<
    long double,
    boost::numeric::interval_lib::policies<
        boost::numeric::interval_lib::save_state< boost::numeric::interval_lib::rounded_transc_std<long double> >,
        boost::numeric::interval_lib::checking_no_empty<long double>
    >
> interval;

class Function
{
public:
    virtual long double evaluate(long double x) = 0;
    virtual interval evaluate(interval x) = 0;
    virtual ~Function() {};
};

#endif // FUNCTION_H
