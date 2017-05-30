#include <boost/numeric/interval.hpp>
#include <cmath>

using namespace boost::numeric::interval_lib;
typedef boost::numeric::interval<
	long double,
	policies<
		save_state< rounded_transc_std<long double> >,
		checking_no_empty<long double>
	>
> interval;

extern "C" long double evalFloat(long double x);
extern "C" interval evalInterval(interval x);

