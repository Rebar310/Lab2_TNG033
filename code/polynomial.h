/*************************
 * Class Polynomial       *
 * TNG033: Lab 2          *
 **************************/

#pragma once

#include <iostream>

#include <vector>
#include <string>

#include "expression.h"

// Definerar Polynomial classen
class Polynomial : public Expression {

public:
    
    // Konstruktorer
    Polynomial(const std::vector<double>& coefficients); // Skapar ett polynom från en vektor av koefficienter
    Polynomial(double constant); // Konverteringskonstruktor
    Polynomial(const Polynomial& other); // Kopieringskonstruktor

    // Tilldelningsoperator
    Polynomial& operator=(const Polynomial& other);

    // Operatorer
    Polynomial& operator+=(const Polynomial& other); // Låter dig lägga till ett annat polynom till det aktuella polynomet.
    Polynomial& operator+=(double constant); // Låter dig lägga till en konstant till polynomet.
    friend Polynomial operator+(const Polynomial& lhs, const Polynomial& rhs); //Skapar ett nytt polynom som är summan av två andra polynom.
    friend Polynomial operator+(const Polynomial& lhs, double rhs); //Skapar ett nytt polynom där en konstant läggs till det första polynomet.
    friend Polynomial operator+(double lhs, const Polynomial& rhs); //Låter dig addera en konstant till ett polynom, där konstanten står till vänster.
    double operator[](std::size_t index) const; // Låter dig läsa koefficienten för ett visst index(plats) (dvs. termen för 𝑋^n).
    double& operator[](std::size_t index); // Låter dig ändra en koefficient för ett visst index.

    // Virtuella funktioner från Expression
    double operator()(double x) const override; // Beräkna polynomets värde vid x
    explicit operator std::string() const override; // Konvertera till std::string
    //explicit förhindrar oavsiktliga typkonverteringar till 
    // std::string.Du måste använda static_cast för att konvertera, vilket gör koden mer tydlig.
   
    Polynomial* clone() const override; // Den här funktionen skapar en exakt kopia av ett Polynomial-objekt.

    private:
    std::vector<double> coefficients; // Lagrar koefficienterna för polynomet
};


/*
 * std::vector should be used to store polinomial's coefficients
 */