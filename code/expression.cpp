/*********************************************************
 * Class Expression member functions implementation       *
 * TNG033: Lab 2                                          *
 **********************************************************/

#include "expression.h"

// Initialize the counter of the total number of existing Expressions(instanser)
std::size_t Expression::count_expressions = 0;

// Used only for debug purposes
// Return number of existing Expressions
std::size_t Expression::get_count_expressions() {
    return Expression::count_expressions;
}

/* ************************* */

//Basklassen Expression ska representera en generell matematisk funktion av formen ??=??(??) där x
//är en variabel.Den är designad för att användas som grund för specifika typer av uttryck(t.ex.polynom och logaritmer).

// Eftersom de flesta funktionerna i Expression är virtuella och måste implementeras i subklasser (t.ex. Polynomial och Logarithm), 
// är det begränsat vad som behövs i basklassens implementation.

// Test kommentar