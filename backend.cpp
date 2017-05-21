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

std::string Backend::floatSummary(long double solution) {
    std::stringstream out;
    out << std::scientific;
    out << std::setprecision(16);

    out << "Wynik:     " << solution << std::endl;

    long double y = function->evaluate(solution);
    out << "Wartość:   " << y << std::endl;
    out << std::endl;

    return out.str();
}

std::string Backend::intervalSummary(interval solution) {
    std::stringstream out;
    out << std::scientific;
    out << std::setprecision(16);

    int old_rounding = fegetround();

    fesetround(FE_DOWNWARD);
    out << "Wynik:     [" << solution.lower() << ", ";
    fesetround(FE_UPWARD);
    out << solution.upper() << "]" << std::endl;
    fesetround(FE_TONEAREST);
    out << "Środek:    " << median(solution) << std::endl;
    fesetround(FE_UPWARD);
    out << "Szerokość: " << width(solution) << std::endl;

    interval y = function->evaluate(solution);
    fesetround(FE_DOWNWARD);
    out << "Wartość:   [" << y.lower() << ", ";
    fesetround(FE_UPWARD);
    out << y.upper() << "]" << std::endl;
    out << std::endl;

    fesetround(old_rounding);

    return out.str();
}

void Backend::loadFunction(char filename[]) {
    Function *new_function;

    new_function = new SOFunction(filename);
    if (function != nullptr) {
        delete function;
    }

    function = new_function;
}

std::string Backend::solveFloatingPoint(const std::string &a_str, const std::string &b_str) {
    long double a, b, x;
    a = stringToFloat(a_str);
    b = stringToFloat(b_str);

    std::stringstream x_str;

    try {
        x = RegulaFalsi(a, b, function);
        x_str << "Regula falsi: " << std::endl << floatSummary(x);

        x = Secant(a, b, function);
        x_str << "Secant: " << std::endl << floatSummary(x);

        bool reached;
        x = Bisection(a, b, function, 1e-16, 100, reached);
        x_str << "Bisection: " << std::endl << floatSummary(x);
    } catch(int err) {
        if (err == WRONG_INTERVAL) {
            throw "Lewy koniec przedziału musi być mniejszy od prawego końca!";
        } else if (err == NO_REAL_ROOTS) {
            throw "Brak rozwiązań rzeczywistych w tym przedziale. Upewnij się, że f(a) * f(b) < 0";
        }
    }

    return x_str.str();
}

std::string Backend::solveInterval(const std::string &a_str, const std::string &b_str) {
    interval a, b, x;
    a = stringToInterval(a_str);
    b = stringToInterval(b_str);

    std::stringstream x_str;

    try {
        x = RegulaFalsi(a, b, function);
        x_str << "Regula falsi: " << std::endl << intervalSummary(x);

        x = Secant(a, b, function);
        x_str << "Secant: " << std::endl << intervalSummary(x);

        bool reached;
        x = Bisection(a, b, function, 1e-16, 100, reached);
        x_str << "Bisection: " << std::endl << intervalSummary(x);
    } catch(int err) {
        if (err == WRONG_INTERVAL) {
            throw "Lewy koniec przedziału musi być mniejszy od prawego końca!";
        } else if (err == NO_REAL_ROOTS) {
            throw "Brak rozwiązań rzeczywistych w tym przedziale. Upewnij się, że f(a) * f(b) < 0";
        }
    }

    return x_str.str();
}
