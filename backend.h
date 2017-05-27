#ifndef BACKEND_H
#define BACKEND_H

#include <string>
#include "function.h"
#include "solutionsummaries.h"

class Backend
{
    Function *function = nullptr;

    struct SingleFloatSummary floatSummary(long double solution);
    struct SingleIntervalSummary intervalSummary(interval solution);
public:
    Backend();
    ~Backend();

    int decimals = 16;

    static std::string intervalToString(interval x, int decimals = 16);
    static long double stringToFloat(const std::string &value);
    static interval stringToInterval(const std::string &value, char separator = ':');

    void loadFunction(char filename[]);
    struct FloatSummary solveFloatingPoint(const std::string &a, const std::string &b);
    struct IntervalSummary solveInterval(const std::string &a, const std::string &b);
};

#endif // BACKEND_H
