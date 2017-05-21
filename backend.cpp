#include "backend.h"
#include "sofunction.h"
#include <boost/multiprecision/cpp_dec_float.hpp>
#include "solvers/regulafalsi.h"
#include "solvers/secant.h"
#include "solvers/bisection.h"
#include <iomanip>
#include <fenv.h>

Backend::Backend() {

}

Backend::~Backend() {
    delete function;
}

long double Backend::stringToFloat(const std::string &value) {
    if (value.find("bla") != std::string::npos) {
        throw "Nie tym razem, panie profesorze ;)";
    }

    try {
        return std::stold(value);
    } catch (std::invalid_argument &error) {
        throw "Nie udało się zinterpretować wpisanych danych jako liczbę!";
    }
}

interval Backend::stringToInterval(const std::string &value, char separator) {
    size_t split_pos = value.find(separator);
    std::string left_str, right_str;
    boost::multiprecision::cpp_dec_float_50 left_mp, right_mp;
    long double left, right;

    if (split_pos == std::string::npos) {
        left_str = right_str = value;
    } else {
        // przedział
        left_str = value.substr(0, split_pos);
        right_str = value.substr(split_pos + 1);
    }

    try {
        left_mp.assign(left_str);
        right_mp.assign(right_str);
    } catch (std::runtime_error &error) {
        throw "Nie udało się zinterpretować wpisanych danych jako liczbę!";
    }

    int old_rounding = fegetround();
    fesetround(FE_DOWNWARD);
    left = left_mp.convert_to<long double>();
    fesetround(FE_UPWARD);
    right = right_mp.convert_to<long double>();
    fesetround(old_rounding);

    return interval(left, right);
}

struct SingleFloatSummary Backend::floatSummary(long double solution) {
    struct SingleFloatSummary out;

    std::stringstream str;
    str << std::scientific;
    str << std::setprecision(16);

    str << solution;
    out.x = str.str();
    str.str(std::string());

    long double y = function->evaluate(solution);
    str << y;
    out.y = str.str();
    str.str(std::string());

    return out;
}

struct SingleIntervalSummary Backend::intervalSummary(interval solution) {
    struct SingleIntervalSummary out;

    std::stringstream str;
    str << std::scientific;
    str << std::setprecision(16);

    int old_rounding = fegetround();

    fesetround(FE_DOWNWARD);
    str << "[" << solution.lower() << ", ";
    fesetround(FE_UPWARD);
    str << solution.upper() << "]";
    out.x = str.str();
    str.str(std::string());

    fesetround(FE_TONEAREST);
    str << median(solution);
    out.median = str.str();
    str.str(std::string());

    fesetround(FE_UPWARD);
    str << width(solution);
    out.width = str.str();
    str.str(std::string());

    interval y = function->evaluate(solution);
    fesetround(FE_DOWNWARD);
    str << "[" << y.lower() << ", ";
    fesetround(FE_UPWARD);
    str << y.upper() << "]";
    out.y = str.str();
    str.str(std::string());

    fesetround(old_rounding);

    return out;
}

void Backend::loadFunction(char filename[]) {
    Function *new_function;

    new_function = new SOFunction(filename);
    if (function != nullptr) {
        delete function;
    }

    function = new_function;
}

struct FloatSummary Backend::solveFloatingPoint(const std::string &a_str, const std::string &b_str) {
    long double a, b, x;
    a = stringToFloat(a_str);
    b = stringToFloat(b_str);

   struct FloatSummary out;

    try {
        x = RegulaFalsi(a, b, function);
        out.regulafalsi = floatSummary(x);

        x = Secant(a, b, function);
        out.secant = floatSummary(x);

        bool reached;
        x = Bisection(a, b, function, 1e-16, 100, reached);
        out.bisection = floatSummary(x);
    } catch(int err) {
        if (err == WRONG_INTERVAL) {
            throw "Lewy koniec przedziału musi być mniejszy od prawego końca!";
        } else if (err == NO_REAL_ROOTS) {
            throw "Brak rozwiązań rzeczywistych w tym przedziale. Upewnij się, że f(a) * f(b) < 0";
        }
    }

    return out;
}

struct IntervalSummary Backend::solveInterval(const std::string &a_str, const std::string &b_str) {
    interval a, b, x;
    a = stringToInterval(a_str);
    b = stringToInterval(b_str);

    struct IntervalSummary out;

    try {
        x = RegulaFalsi(a, b, function);
        out.regulafalsi = intervalSummary(x);

        x = Secant(a, b, function);
        out.secant = intervalSummary(x);

        bool reached;
        x = Bisection(a, b, function, 1e-16, 100, reached);
        out.bisection = intervalSummary(x);
    } catch(int err) {
        if (err == WRONG_INTERVAL) {
            throw "Lewy koniec przedziału musi być mniejszy od prawego końca!";
        } else if (err == NO_REAL_ROOTS) {
            throw "Brak rozwiązań rzeczywistych w tym przedziale. Upewnij się, że f(a) * f(b) < 0";
        }
    }

    return out;
}
