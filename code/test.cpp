/******************************************************
 * Test program for the expressions hierarchy          *
 * TNG033: Lab 2                                       *
 *******************************************************/

#include <iostream>
#include <vector>
#include <cassert>

#include "polynomial.h"
#include "logarithm.h"

int main() {
    /*****************************************************
     * TEST PHASE 0                                       *
     * Polynomial: conversion constructor                 *
     *              operator std::string()                *
     *              operator<<                            *
     ******************************************************/
    std::cout << "TEST PHASE 0: Polynomial - conversion constructor, conversion to std::string, "
                 "and operator<<\n";

    {
        Polynomial p1{6.6};  // conversion constructor: convert a double to a Polynomial

        // Test
        std::cout << "p1 = " << p1 << "\n";
        assert(std::string{p1} == std::string{"6.60"});

        Polynomial p2{0};

        // Test
        std::cout << "p2 = " << p2 << "\n";
        assert(std::string{p2} == std::string{"0.00"});
    }

    assert(Expression::get_count_expressions() == 0);

    /*****************************************************
     * TEST PHASE 1                                       *
     * Polynomial: constructors                           *
     *             operator std::string()                 *
     *             operator<<                             *
     ******************************************************/
    std::cout << "\nTEST PHASE 1: Polynomial - constructors, conversion to std::string, "
                 "and operator<<\n";

    {
        std::vector<double> v1{2.2, 4.4, -2.0, 5.0};
        const Polynomial p1{v1};  // create a polynomial of degree 3

        // Test
        std::cout << "p1 = " << p1 << "\n";
        assert(std::string{p1} == std::string{"2.20 + 4.40 * X^1 - 2.00 * X^2 + 5.00 * X^3"});
    }

    assert(Expression::get_count_expressions() == 0);

    /*****************************************************
     * TEST PHASE 2                                       *
     * Polynomial: operator[]                             *
     ******************************************************/
    std::cout << "\nTEST PHASE 2: Polynomial::operator[]\n";

    {
        std::vector<double> v1{2.2, 4.4, -2.0, 5.0};
        Polynomial p1{v1};  // create a polynomial of degree 3

        p1[2] = -8;
        // Test
        assert(std::string{p1} == std::string{"2.20 + 4.40 * X^1 - 8.00 * X^2 + 5.00 * X^3"});

        //**********************************************
        const Polynomial p2{v1};
        //p2[3] = -4.4; // should not compile because
        
        // Detta blir error då vi jobbar med ett const objekt
        // i funktionen operator[] så kommer index = 3 och coefficients.size() vara 4 därav kommer denna 
        // funktionen vilja expandera vektorn, detta vilket inte går då det är const polynom
        //*********************************************

        assert(Expression::get_count_expressions() == 2);
        assert(p2[2] == -2.0);
    }

    assert(Expression::get_count_expressions() == 0);

    /*****************************************************
     * TEST PHASE 3                                       *
     * Polynomial: copy constructor                       *
     ******************************************************/
    std::cout << "\nTEST PHASE 3: Polynomial - copy constructor\n";

    {
        std::vector<double> v1{2.2, 4.4, -2.0, 5.0};
        Polynomial p1{v1};  // create a polynomial of degree 3

        Polynomial p2{p1};  // copy constructor

        assert(Expression::get_count_expressions() == 2);

        p1[2] = 0.0;  // should not modify p2

        // Test
        assert((std::string{p2} == std::string{"2.20 + 4.40 * X^1 - 2.00 * X^2 + 5.00 * X^3"}));
    }

    assert(Expression::get_count_expressions() == 0);

    /*****************************************************
     * TEST PHASE 4                                       *
     * Polynomial: assignment operator                    *
     ******************************************************/
    std::cout << "\nTEST PHASE 4: Polynomial - assignment operator\n";

    {
        std::vector<double> v1{2.2, 4.4, -2.0, 5.0};
        Polynomial p1{v1};  // create a polynomial of degree 3

        p1 = p1;  // self-assignment
        // Test
        assert(Expression::get_count_expressions() == 1);
        assert(std::string{p1} == std::string{"2.20 + 4.40 * X^1 - 2.00 * X^2 + 5.00 * X^3"});

        std::vector<double> v2{-1, 0, 1};
        Polynomial p2{v2};

        Polynomial p3{6.6};

        p3 = p2 = p1;
        // Test
        assert(Expression::get_count_expressions() == 3);
        assert(std::string{p2} == std::string{"2.20 + 4.40 * X^1 - 2.00 * X^2 + 5.00 * X^3"});
        assert(std::string{p3} == std::string{"2.20 + 4.40 * X^1 - 2.00 * X^2 + 5.00 * X^3"});

        p1[1] = -999.0;  // should not modify neither p2 nor p3

        // Test
        assert(std::string{p2} == std::string{"2.20 + 4.40 * X^1 - 2.00 * X^2 + 5.00 * X^3"});
        assert(std::string{p3} == std::string{"2.20 + 4.40 * X^1 - 2.00 * X^2 + 5.00 * X^3"});
        // But, p1 is modified
        assert(std::string{p1} == std::string{"2.20 - 999.00 * X^1 - 2.00 * X^2 + 5.00 * X^3"});
    }

    assert(Expression::get_count_expressions() == 0);

    /*****************************************************
     * TEST PHASE 5                                       *
     * Polynomial: operator()                             *
     ******************************************************/
    std::cout << "\nTEST PHASE 5: Polynomial::operator()\n";

    {
        std::vector<double> v1{-1, 0, 1};
        Polynomial p1{v1};

        assert(p1(1) == 0.0);

        std::vector<double> v2{2.2, 4.4, 2.0, 5.0};
        const Polynomial p2{v2};  // create a polynomial of degree 3

        // Test
        assert(std::format("{:.2f}", p2(3.3)) == "218.19");
    }

    assert(Expression::get_count_expressions() == 0);

    /*****************************************************
     * TEST PHASE 6                                       *
     * Polynomial: isRoot                                 *
     ******************************************************/
    std::cout << "\nTEST PHASE 6: Polynomial::isRoot\n";

    {
        std::vector<double> v1{-1, 0, 1};
        Polynomial p1{v1};

        assert(p1.isRoot(1));

        std::vector<double> v2{2.2, 4.4, 2.0, 5.0};
        const Polynomial p2{v2};

        assert(p2.isRoot(1) == false);
    }

    assert(Expression::get_count_expressions() == 0);

    /*****************************************************
     * TEST PHASE 7                                       *
     * Polynomial: P1 += P2                                  *
     ******************************************************/
    std::cout << "\nTEST PHASE 7: P1 += P2\n";

    {
        std::vector<double> v1{2.2, 4.4, 2.0, 5.0};
        Polynomial p1{v1};  // create a polynomial of degree 3

        std::vector<double> v2{-1, 0, 1};
        Polynomial p2{v2};  // create a polynomial of degree 2

        p1 += p2;

        // Test
        assert(Expression::get_count_expressions() == 2);
        assert(std::string{p1} == std::string{"1.20 + 4.40 * X^1 + 3.00 * X^2 + 5.00 * X^3"});

        p2 += p1;

        // Test
        assert(Expression::get_count_expressions() == 2);
        assert(std::string{p2} == std::string{"0.20 + 4.40 * X^1 + 4.00 * X^2 + 5.00 * X^3"});
    }

    assert(Expression::get_count_expressions() == 0);

    /*****************************************************
     * TEST PHASE 8                                       *
     * Polynomial: P1+P2                                  *
     ******************************************************/
    std::cout << "\nTEST PHASE 8: P1 + P2\n";

    {
        std::vector<double> v1{2.2, 4.4, 2.0, 5.0};
        const Polynomial p1{v1};  // create a polynomial of degree 3

        std::vector<double> v2{2.2, 4.4, 2.0};
        const Polynomial p2{v2};  // create a polynomial of degree 2

        std::vector<double> v3{-1, 0, 1};
        Polynomial p3{v3};  // create a polynomial of degree 2

        // Test
        assert(std::string{p1 + p2} == std::string{"4.40 + 8.80 * X^1 + 4.00 * X^2 + 5.00 * X^3"});

        Polynomial p4 = p1 + p2 + p3;

        // Test
        assert(Expression::get_count_expressions() == 4);
        assert(std::string{p4} == std::string{"3.40 + 8.80 * X^1 + 5.00 * X^2 + 5.00 * X^3"});
    }

    assert(Expression::get_count_expressions() == 0);

    /*****************************************************
     * TEST PHASE 9                                       *
     * Polynomial: p += k, k+P and P+k                    *
     ******************************************************/
    std::cout << "\nTEST PHASE 9: p += k, k+P and P+k\n";

    {
        std::vector<double> v1{4.40, 8.80, 4.00, 5.00};
        Polynomial p1{v1};  // create a polynomial of degree 3

        p1 += 2.0;

        // Test
        assert(std::string{p1} == std::string{"6.40 + 8.80 * X^1 + 4.00 * X^2 + 5.00 * X^3"});

        p1 = 0.0 + p1 + 3.3;

        // Test
        assert(Expression::get_count_expressions() == 1);
        assert(std::string{p1} == std::string{"9.70 + 8.80 * X^1 + 4.00 * X^2 + 5.00 * X^3"});

        std::vector<double> v2{1.2, 4.4, 2.0, 0.0, 3.1, 6.6};
        const Polynomial p2{v2};  // create a polynomial of degree 5

        p1 += (0.0 + p2);

        // Test
        assert(Expression::get_count_expressions() == 2);
        assert(
            std::string{p1} ==
            std::string{"10.90 + 13.20 * X^1 + 6.00 * X^2 + 5.00 * X^3 + 3.10 * X^4 + 6.60 * X^5"});
    }

    assert(Expression::get_count_expressions() == 0);

    /******************************************************
     * TEST PHASE 10                                       *
     * Logarithm: constructors                             *
     *            operator std::string()                   *
     *            set_base                                 *
     *            operator<<                               *
     *******************************************************/
    std::cout
        << "\nTEST PHASE 10: Logarithm - constructors, conversion to std::string, set_base, and "
           "operator<<\n";

    {
        Logarithm l1;  // default constructor
        std::cout << l1 << "\n";

        // Test
        assert(Expression::get_count_expressions() == 2);

        assert(std::string{l1} == std::string{"0.00 + 1.00 * Log_2( 0.00 + 1.00 * X^1 )"});

        std::vector<double> v2{-1, 0, 1};
        Polynomial p2{v2};  // create a polynomial of degree 2

        Logarithm l2{p2, 2, -3, 10};

        p2[1] = -999.0;  // should not modify  l2

        // Test
        assert(Expression::get_count_expressions() == 5);

        //Kollar efter bugg 
        std::string l2string = std::string{ l2 };

        assert(std::string{l2} ==
               std::string{"2.00 - 3.00 * Log_10( -1.00 + 0.00 * X^1 + 1.00 * X^2 )"});

        Logarithm l3{l1, 1, 2, 10};

        assert(Expression::get_count_expressions() == 8);

        l1.set_base(3);  // should not modify l3

        // Test
        assert(std::string{l3} ==
               std::string{"1.00 + 2.00 * Log_10( 0.00 + 1.00 * Log_2( 0.00 + 1.00 * X^1 ) )"});
    }

    assert(Expression::get_count_expressions() == 0);

    /*****************************************************
     * TEST PHASE 11                                      *
     * Logarithm: copy constructor                        *
     ******************************************************/
    std::cout << "\nTEST PHASE 11: Logarithm - copy constructor\n";

    {
        Logarithm l1;  // default constructor
        assert(Expression::get_count_expressions() == 2);

        Logarithm* ptr_l2 = new Logarithm{l1, 1, 2, 10};
        assert(Expression::get_count_expressions() == 5);

        Logarithm l3{*ptr_l2};  // copy constructor
        assert(Expression::get_count_expressions() == 8);

        delete ptr_l2;  // should not affect l3
        ptr_l2 = nullptr;

        // Test
        assert(std::string{l3} ==
               std::string("1.00 + 2.00 * Log_10( 0.00 + 1.00 * Log_2( 0.00 + 1.00 * X^1 ) )"));
    }

    assert(Expression::get_count_expressions() == 0);

    /*****************************************************
     * TEST PHASE 12                                      *
     * Logarithm: isRoot                                  *
     ******************************************************/
    std::cout << "\nTEST PHASE 12: isRoot\n";

    {
        const Logarithm l1;
        assert(Expression::get_count_expressions() == 2);
        assert(l1.isRoot(1));

        std::vector<double> v2{-1, 0, 1};
        Polynomial p2{v2};  // create a polynomial of degree 2

        Logarithm l2{p2, 2, 3, 10};
        assert(Expression::get_count_expressions() == 5);
        assert(l2.isRoot(2) == false);
    }

    assert(Expression::get_count_expressions() == 0);

    /*****************************************************
     * TEST PHASE 13                                       *
     * Logarithm: operator()                              *
     ******************************************************/
    std::cout << "\nTEST PHASE 13: Logarithm::operator()\n";

    {
        const Logarithm l1;
        assert(Expression::get_count_expressions() == 2);
        assert(l1(1) == 0.0);

        std::vector<double> v2{-1, 0, 1};
        Polynomial p2{v2};  // create a polynomial of degree 2

        Logarithm l2{p2, 2, 3, 10};
        assert(Expression::get_count_expressions() == 5);
        assert(l2(2) >= 3.4313);
    }

    assert(Expression::get_count_expressions() == 0);

    /*****************************************************
     * TEST PHASE 14                                      *
     * Logarithm: assignment operator                     *
     ******************************************************/
    std::cout << "\nTEST PHASE 14: Logarithm - assignment operator\n";

    {
        Logarithm l0;
        assert(Expression::get_count_expressions() == 2);

        std::vector<double> v1{-1, 0, 1};
        Polynomial p1{v1};  // create a polynomial of degree 2

        Logarithm* ptr_l1 = new Logarithm{p1, 1, 1, 2};
        assert(Expression::get_count_expressions() == 5);

        l0 = *ptr_l1;
        assert(Expression::get_count_expressions() == 5);

        delete ptr_l1;  // shoudld not affect l0
        ptr_l1 = nullptr;
        assert(Expression::get_count_expressions() == 3);

        // Test
        assert(std::string{l0} == std::string("1.00 + 1.00 * Log_2( -1.00 + 0.00 * X^1 + 1.00 * X^2 )"));
    }

    assert(Expression::get_count_expressions() == 0);

    /*****************************************************
     * TEST PHASE 15                                      *
     * Expressions: polymorphism                          *
     ******************************************************/
    std::cout << "\nTEST PHASE 15:  Expressions - polymorphism\n";

    {
        std::vector<Expression*> V{new Logarithm{}, new Polynomial{std::vector<double>{-1, 0, 1}}};
        assert(Expression::get_count_expressions() == 3);

        for (auto e : V) {
            assert(e->isRoot(1));
            delete e;
        }
    }

    assert(Expression::get_count_expressions() == 0);

    /*****************************************************
     * TEST PHASE 16                                      *
     * Expression: assignment                             *
     ******************************************************/
     std::cout << "\nTEST PHASE 16:  Expression::operator=\n";

    {
        /*
        std::vector<double> v1{-1, 0, 1};
        Expression* e1 = new Polynomial{v1};      // Skapar ett nytt polynom objekt av vektor v1 (utnyttjar polymorfism)

        Expression* e2 = new Logarithm{};         // Skapar ett nytt Logaritm objekt utan att sätta in någon vektor.

        *e1 = *e2; //<-- should not compile!!    // / Försöker tilldela innehållet i det objekt som `e2` pekar på till objektet som `e1` pekar på.
        */

         // Detta blir kompileringsfel då dessa är från två helt olika klasser 
         // och det har inte implementerats någon operator = som ska kunna klara av detta
    }

    std::cout << "\nSuccess!!\n";
}
