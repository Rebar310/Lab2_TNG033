/*********************************************************
 * Class Logarithm member functions implementation        *
 * TNG033: Lab 2                                          *
 **********************************************************/

#include "logarithm.h"
#include "polynomial.h"

#include <cmath>
#include <sstream>
#include <iomanip>

// ADD implementation of the member functions for class Logarithm

// Standardkonstruktor för log_2(x)
Logarithm::Logarithm(): expression(new Polynomial(std::vector<double>{0.0, 1.0})), c1(0.0), c2(1.0), base(2) {}

// Konstruktor för generella logaritmer
Logarithm::Logarithm(const Expression& expr, double c1, double c2, int base)
    : expression(expr.clone()), c1(c1), c2(c2), base(base) {
    if (base <= 1) {
        throw std::invalid_argument("Base must be greater than 1");
    }
}


// Kopieringskonstruktor
Logarithm::Logarithm(const Logarithm& other)
    : expression(other.expression->clone()), c1(other.c1), c2(other.c2), base(other.base) {}


// Destruktor
Logarithm::~Logarithm() {
    if (expression != nullptr) {
        delete expression;
    }
}


// Tilldelningsoperator
Logarithm& Logarithm::operator=(const Logarithm& other) {
    if (this != &other) {

        if (expression != nullptr) {
            delete expression;
        }

        expression = other.expression->clone();
        c1 = other.c1;
        c2 = other.c2;
        base = other.base;
    }
    return *this;
}

// Ändra basen för logaritmen
void Logarithm::set_base(int new_base) {
    if (new_base <= 1) {
        throw std::invalid_argument("Base must be greater than 1");
    }
    base = new_base;
}

// Evaluerar logaritmen vid ett visst x
double Logarithm::operator()(double x) const {
    double inner_value = (*expression)(x); // Beräkna värdet av det inre uttrycket
    if (inner_value <= 0) {
        throw std::domain_error("Logarithm undefined for non-positive values");
    }
    return c1 + c2 * std::log(inner_value) / std::log(base);
}

// Konverterar logaritmen till std::string
Logarithm::operator std::string() const {
    std::ostringstream os;
    os << std::fixed << std::setprecision(2);
    std::string es = static_cast<std::string>(*expression);

    if (c2 >= 0) {
        os << c1 << " + " << c2 << " * Log_" << base << "( " << es << " )";
    }
    else {
        os << c1 << " - " << -c2 << " * Log_" << base << "( " << es << " )";
    }

    return os.str();
}


// Skapar en kopia av objektet
Logarithm* Logarithm::clone() const {
    return new Logarithm(*this);
}