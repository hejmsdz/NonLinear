#ifndef SOLUTIONSUMMARIES_H
#define SOLUTIONSUMMARIES_H

#include <string>

struct SingleIntervalSummary {
    std::string x, median, width, y;
};

struct SingleFloatSummary {
    std::string x, y;
};

struct IntervalSummary {
    SingleIntervalSummary bisection, regulafalsi, secant;
};

struct FloatSummary {
    SingleFloatSummary bisection, regulafalsi, secant;
};

#endif // SOLUTIONSUMMARIES_H
