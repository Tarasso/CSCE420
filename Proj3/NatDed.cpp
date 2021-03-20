#include "parser.h"
#include <iostream>

using namespace std;

#ifndef NATDED_CPP
#define NATDED_CPP

// ex: (P^Q)->R, (P^Q) returns R
// requires s1 to be the implies statement
Expr* ModusPonens(Expr* s1, Expr* s2)
{
    if(s1->kind == ATOM)
        throw RuleApplicationError("first expression should be of type list");
    
    if(s1->sub.at(0)->sym == "implies" && Eq(s1->sub.at(1), s2))
        return new Expr(s1->sub.at(2));
    else
        return nullptr;
}

// ex: A->B returns ~AvB
Expr* ImplicationElimination(Expr* s1)
{
    if(s1->kind == ATOM)
        throw RuleApplicationError("expression should be of type list");
    
    if(s1->sub.at(0)->sym == "implies")
    {
        Expr* lhs = s1->sub.at(1);
        Expr* notLhs = parse("(not " + lhs->toString() + ")");
        // cout << "notLhs " << notLhs->toString() << endl;
        Expr* rhs = s1->sub.at(2);
        return parse("(and " + notLhs->toString() + " " + rhs->toString() + ")");
    }
        
    else
        return nullptr;
}

// ex: A^B returns A
Expr* AndElimination(Expr* s1)
{
    if(s1->kind == ATOM)
        throw RuleApplicationError("expression should be of type list");
    
    if(s1->sub.at(0)->sym == "and")
        return new Expr(s1->sub.at(1));
    else
        return nullptr;
}

// ex: A,B returns A^B
Expr* AndIntroduction(Expr* s1, Expr* s2)
{
    return parse("(and " + s1->toString() + " " + s2->toString() + ")");
}

// ex: A,B returns AvB
Expr* OrIntroduction(Expr* s1, Expr* s2)
{
    return parse("(or " + s1->toString() + " " + s2->toString() + ")");
}

// ex: ~~A returns A
Expr* DoubleNegationElimination(Expr* s1)
{
    if(s1->kind == ATOM)
        throw RuleApplicationError("expression should be of type list");
    
    if(s1->sub.at(0)->sym == "not" && s1->sub.at(1)->sub.at(0)->sym == "not")
        return new Expr(s1->sub.at(1)->sub.at(1)->toString());
    else
        return nullptr;
}


// ex: AvB, ~AvC returns BvC
// requires matching literal to be on lhs of each expr
Expr* Resolution(Expr* s1, Expr* s2)
{
    if(s1->kind == ATOM || s2->kind == ATOM)
        throw RuleApplicationError("expression should be of type list");

    if(("(not " + s1->sub.at(1)->toString() + ")") == s2->sub.at(1)->toString())
        return parse("(or " + s1->sub.at(2)->toString() + " " + s2->sub.at(2)->toString() + ")");
    else
    {
        cout << "returning null" << endl;
        return nullptr;
    }
}

// ex: ~(A^B) returns ~Av~B
// ex: ~(AvB) returns ~A^~B
Expr* DeMorgans(Expr* s1)
{
    if(s1->kind == ATOM)
        throw RuleApplicationError("expression should be of type list");
    
    if(s1->sub.at(0)->sym == "not") // check if nots of each other
    {
        if(s1->sub.at(1)->sub.at(0)->sym == "and")
            return parse("(or ( not " + s1->sub.at(1)->sub.at(1)->toString() + ") (not " + s1->sub.at(1)->sub.at(2)->toString() + "))");
        if(s1->sub.at(1)->sub.at(0)->sym == "or")
            return parse("(and ( not " + s1->sub.at(1)->sub.at(1)->toString() + ") (not " + s1->sub.at(1)->sub.at(2)->toString() + "))");
        else
            throw RuleApplicationError("improper demorgans format expr given");
    }
    else
        return nullptr;
}

#endif