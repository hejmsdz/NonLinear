#include "backend.h"
#include "sofunction.h"
#include "solvers/regulafalsi.h"
#include "solvers/secant.h"
#include "solvers/bisection.h"
#include <iomanip>

Backend::Backend() {

}

Backend::~Backend() {
    delete function;
}

void Backend::loadFunction(char filename[]) {
    Function *new_function;

    new_function = new SOFunction(filename);
    if (function != nullptr) {
        delete function;
    }

    function = new_function;
}

std::string Backend::solveFloatingPoint(std::string &a_str, std::string &b_str) {
    if ((a_str+b_str).find("bla") != std::string::npos) {
        throw "Nie tym razem, panie profesorze ;)";
    }

    long double a, b;
    try {
        a = std::stold(a_str);
        b = std::stold(b_str);
    } catch (std::invalid_argument &error) {
        throw "Nie udało się zinterpretować wpisanych danych jako liczbę!";
    }

    long double x;
    std::stringstream x_str;

    try {
        bool reached;
        x = FloatingPoint::Bisection(a, b, function, 1e-16, 100, reached);
        x_str << std::scientific;
        x_str << std::setprecision(16) << x;
    } catch(int err) {
        if (err == WRONG_INTERVAL) {
            throw "Lewy koniec przedziału musi być mniejszy od prawego końca!";
        } else if (err == NO_REAL_ROOTS) {
            throw "Brak rozwiązań rzeczywistych w tym przedziale. Upewnij się, że f(a) * f(b) < 0";
        }
    }

    return x_str.str();
}
