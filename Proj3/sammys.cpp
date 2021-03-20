#include <iostream>
#include "parser.h"
#include "NatDed.h"

using namespace std;

void testROI()
{
    try
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

        Expr* s11 = parse("(and A B)");
        Expr* s12 = parse("(or A B)");
        cout << Commute(s11)->toString() << endl;
        cout << Commute(s12)->toString() << endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}

int main(int argc, char* argv[])
{
    if(false)
        testROI();

    try
    {
        vector<Expr*> KB = load_kb("sammys.kb"); // 0-35

        // add initial observations
        KB.push_back(parse("O1Y")); // 36
        KB.push_back(parse("L1W")); // 37
        KB.push_back(parse("O2W")); // 38
        KB.push_back(parse("L2Y")); // 39
        KB.push_back(parse("O3Y")); // 40
        KB.push_back(parse("L3B")); // 41

        // show that box 3 contains yellow
        KB.push_back(ModusPonens(KB[11],KB[41]));
        KB.push_back(ModusPonens(KB[34],KB[40]));
        KB.push_back(Commute(KB[43]));
        KB.push_back(Resolution(KB[44],KB[42]));

        // show that box 1 contains both
        KB.push_back(ModusPonens(KB[4],KB[37]));
        KB.push_back(ModusPonens(KB[30],KB[36]));
        KB.push_back(ModusPonens(KB[27],KB[45]));
        KB.push_back(Commute(KB[48]));
        KB.push_back(AndElimination(KB[49]));
        KB.push_back(Resolution(KB[47],KB[50]));

        // show that box 2 must contain white
        KB.push_back(ModusPonens(KB[23],KB[51]));
        KB.push_back(AndElimination(KB[52]));
        KB.push_back(ModusPonens(KB[27],KB[45]));
        KB.push_back(AndElimination(KB[54]));
        KB.push_back(Resolution(KB[1],KB[55]));
        KB.push_back(Resolution(KB[56],KB[53]));

        show_kb(KB);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}