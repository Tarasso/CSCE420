#include "parser.h"

#ifndef NATDED_H
#define NATDED_H

using namespace std;

Expr* ModusPonens(Expr* s1, Expr* s2);
Expr* ImplicationElimination(Expr* s1);
Expr* AndElimination(Expr* s1, Expr* s2);
Expr* AndIntroduction(Expr* s1, Expr* s2);
Expr* OrIntroduction(Expr* s1, Expr* s2);
Expr* DoubleNegationElimination(Expr* s1, Expr* s2);
Expr* Resolution(Expr* s1, Expr* s2);
Expr* DeMorgans(Expr* s1, Expr* s2);


#endif
