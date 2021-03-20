#include <iostream>
#include "parser.h"
#include "NatDed.h"

using namespace std;

int main(int argc, char* argv[])
{
    Expr* s1 = parse("(implies (and P Q) R)");
    Expr* s2 = parse("(and P Q)");
    cout << s1->toString() << "," << s2->toString() << " derive " << ModusPonens(s1, s2)->toString() << endl;

    Expr* s3 = parse("(implies A B)");
    cout << ImplicationElimination(s3)->toString() << endl;

    cout << AndElimination(s2)->toString() << endl;

    Expr* s4 = parse("A");
    Expr* s5 = parse("B");

    cout << AndIntroduction(s4,s5)->toString() << endl;
    cout << OrIntroduction(s4,s5)->toString() << endl;
    
    Expr* s6 = parse("(not (not A))");
    cout << DoubleNegationElimination(s6)->toString() << endl;

    Expr* s7 = parse("(not (and A B))");
    Expr* s8 = parse("(not (or A B))");
    cout << DeMorgans(s7)->toString() << endl;
    cout << DeMorgans(s8)->toString() << endl;

    Expr* s9 = parse("(or (and A B) B)");
    Expr* s10 = parse("(or (not (and A B)) C)");
    cout << Resolution(s9,s10)->toString() << endl;
}