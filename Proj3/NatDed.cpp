#include "parser.h"
#include <iostream>

using namespace std;

#ifndef NATDED_CPP
#define NATDED_CPP

// ex: P->Q, P returns Q
// ex: (P^Q)->R, (P^Q) returns R
Expr* ModusPonens(Expr* s1, Expr* s2)
{
    if(s1->kind == ATOM)
        throw RuleApplicationError("first arg should be of type list");
    
    if(s1->sub.at(0)->sym == "implies" && Eq(s1->sub.at(1), s2))
        return s1->sub.at(2);
    else
        return nullptr;
}

Expr* ImplicationElimination(Expr* s1, Expr* s2)
{
    return nullptr;
}

Expr* AndElimination(Expr* s1, Expr* s2)
{
    return nullptr;
}

Expr* AndIntroduction(Expr* s1, Expr* s2)
{
    return nullptr;
}

Expr* OrIntroduction(Expr* s1, Expr* s2)
{
    return nullptr;
}

Expr* DoubleNegationElimination(Expr* s1, Expr* s2) // 1 or 2 args???
{
    return nullptr;
}

Expr* Resolution(Expr* s1, Expr* s2)
{
    return nullptr;
}

Expr* DeMorgans(Expr* s1, Expr* s2)
{
    return nullptr;
}

#endif