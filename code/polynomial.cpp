/*********************************************************
 * Class Polynomial member functions implementation       *
 * TNG033: Lab 2                                          *
 **********************************************************/

#include "polynomial.h"

// ADD implementation of the member functions for class Polynomial

#include <sstream>
#include <cmath>
#include <iomanip>

// Konstruktor från en vektor av koefficienter
Polynomial::Polynomial(const std::vector<double>& coefficients) : coefficients(coefficients) {}

// Konverteringskonstruktor för en konstant
Polynomial::Polynomial(double constant) : coefficients{ constant } {}

// Kopieringskonstruktor
Polynomial::Polynomial(const Polynomial& other) : coefficients(other.coefficients) {}

// Tilldelningsoperator
Polynomial& Polynomial::operator=(const Polynomial& other) {
    if (this != &other) {
        coefficients = other.coefficients;
    }
    return *this;
}

// Addition och tilldelning med ett annat polynom
Polynomial& Polynomial::operator+=(const Polynomial& other) {
    std::size_t maxSize = std::max(coefficients.size(), other.coefficients.size());
    coefficients.resize(maxSize, 0.0);

    for (std::size_t i = 0; i < other.coefficients.size(); ++i) {
        coefficients[i] += other.coefficients[i];
    }

    return *this;
}

// Addition och tilldelning med en konstant
Polynomial& Polynomial::operator+=(double constant) {
    if (coefficients.empty()) {
        coefficients.push_back(constant);
    }
    else {
        coefficients[0] += constant;
    }
    return *this;
}

// Addition av två polynom
Polynomial operator+(const Polynomial& lhs, const Polynomial& rhs) {
    Polynomial result(lhs);
    result += rhs;
    return result;
}

// Addition av ett polynom och en konstant
Polynomial operator+(const Polynomial& lhs, double rhs) {
    Polynomial result(lhs);
    result += rhs;
    return result;
}

Polynomial operator+(double lhs, const Polynomial& rhs) {
    return rhs + lhs;
}

// Subscript-operatorer
double Polynomial::operator[](std::size_t index) const {
    if (index < coefficients.size()) {
        return coefficients[index];
    }
    return 0.0;
}

// Används för att komma åt eller ändra en specifik koefficient i polynomet baserat på ett index.
double& Polynomial::operator[](std::size_t index) {
    if (index >= coefficients.size()) {
        coefficients.resize(index + 1, 0.0);
    }
    return coefficients[index];
}

// Evaluerar polynomet för ett specifikt x
double Polynomial::operator()(double x) const {
    double result = 0.0;
    double power = 1.0;

    for (double coeff : coefficients) {
        result += coeff * power;
        power *= x;
    }

    return result;
}

// Konvertering till std::string
Polynomial::operator std::string() const {
    std::ostringstream os; // Skapar en ström för att bygga upp en sträng bit för bit
    os << std::fixed << std::setprecision(2); // Ställer in formatet för flyttal till fast decimal och två decimaler

    bool is_first_term = true; // Håller reda på om det är första termen i polynomet för att hantera "+"-tecknet korrekt

    // Loopar igenom alla koefficienter i vektorn
    for (std::size_t i = 0; i < coefficients.size(); ++i) {
         
        // Om det inte är första termen, lägg till " + " eller " - " beroende på koefficientens tecken
            if (!is_first_term) {
                os << (coefficients[i] >= 0 ? " + " : " - "); // Lägg till " + " för positiva och " - " för negativa koefficienter
            }
            else if (coefficients[i] < 0) {
                os << "-";  // Första termen: lägg till "-" om koefficienten är negativ
            }

            // Extrahera och bearbeta koefficienten
            double c = coefficients[i]; // Originalkoefficient
            double absc = std::abs(coefficients[i]);  // Absolutvärde av koefficienten för att hantera negativa tecken separat

            os << std::abs(coefficients[i]); // Absolutvärde för att hantera "-" separat

            if (i > 0) {
                os << " * X^" << i; // Lägg till "X^n" endast för termer med exponent > 0
            }

            is_first_term = false; // Markera att första termen har bearbetats
        
    }

    // Om alla koefficienter är noll, returnera "0.00"
    if (is_first_term) {
        os << "0.00";
    }
    
    return os.str();
}

// Klona objektet
Polynomial* Polynomial::clone() const {
    return new Polynomial(*this);
}