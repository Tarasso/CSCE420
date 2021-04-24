#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include "parser.h"

using namespace std;

#define MAX_ITERS = 10000

class ResPair {
public:
	int i, j;
	ResPair(int a, int b) {i=a; j=b;}
};

Expr* Resolve(Expr* clause1, Expr* clause2, string Prop) {
	/*
	This is a propositional Rule of Inference (like in Project 3),
	which should be able to handle clauses with an arbitrary number of
	literals. Cancel out instances of “Prop” or “(not Prop)”, collect
	the remaining literals between the two clauses, and make a new clause
	out of them (an Expr* starting with ‘or’). You should also do ‘factoring’
	by removing repeated literals from the resolvent (as described in the book).
	*/
	return nullptr;
}

vector<string> matching_propositions(Expr* clause1, Expr* clause2) {
	/* return a list of all proposition symbols (as strings) that appear as a
	 positive literal on one of the clauses and a negative literal in the other
	*/
	vector<string> temp;
	return temp;
}

bool Resolvable(Expr* clause1, Expr* clause2) {
	//do two clauses have a literal in common with opposite sign?
	return false;
}

bool validateClause(Expr* clause) {
	/*
	clauses must be of the form “(or <literal>*)” where literals as either
	propositional symbols (positive literal, i.e. <prop>), or “(not <prop>)”
	as negative literals (see below). Also, the same proposition cannot appear
	as both a positive and negative literal in the same clause.
	*/
	return false;
}

bool resolution(vector<string> KB, string query) {
	
}

int main(int argc, char* argv[]) {
	if(argc != 3 && argc != 4)
	{
		cout << "Incorrect input arguments: must use form ./resolution <*.cnf> <query> <optional: -n flag denoting negated query>" << endl;
		exit(1);
	}

	try
	{
		// load kb
		vector<Expr*> KB = load_kb(argv[1]);

		// add negated query (prob include additional flag)
		Expr* negatedQuery;
		// case 1: negated var: "(not C2Y)"
		if(argc == 4 && strcmp(argv[3],"-n") == 0)
		{
			negatedQuery = parse(argv[2]);
			negatedQuery->sub[0]->sym = "or";
			
		}
		// case 2: single var ex: C2W or safe22
		else if(argc == 3)
		{
			string query(argv[2]);
			if(query.find(" ") != string::npos) {
				cout << "Please make sure to use the -n flag if the query is negated" << endl;
				exit(1);
			}
			string s = "(or (not " + query + "))";
			negatedQuery = parse(s);
		}
		// else something is wrong wiht input
		else {
			cout << "Error in adding negated error" << endl;
			exit(1);
		}
		KB.push_back(negatedQuery);

		// VALIDATE CLAUSES???

		// print KB
		show_kb(KB);
    	cout << endl << endl;
		

		// run search

		// output

	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	
}
