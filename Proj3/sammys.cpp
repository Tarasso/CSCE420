#include <iostream>
#include "parser.h"
#include "NatDed.h"

using namespace std;

int main(int argc, char* argv[])
{
    Expr* s1 = parse("(implies (and P Q) R)");
    Expr* s2 = parse("(and P Q)");
    cout << s1->toString() << "," << s2->toString() << " derive " << ModusPonens(s1, s2)->toString() << endl;
}