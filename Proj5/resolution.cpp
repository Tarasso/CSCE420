#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <queue>
#include <cassert>
#include "parser.h"

using namespace std;

#define MAX_ITERS 10000

class ResPair {
public:
	int i, j;
	ResPair(int a, int b) {i=a; j=b;}
};


void getVars(Expr* ex, vector<string>* vars, vector<string>* negVars) {
	vector<Expr*> temp = ex->sub;
	// identify vars in expr
	for(unsigned int i = 0; i < temp.size(); i++) {
		if(temp[i]->kind == ATOM && temp[i]->sym != "or" && temp[i]->sym != "not") {
			vars->push_back(temp[i]->toString());
		}
		else if (temp[i]->kind == LIST) {
			negVars->push_back(temp[i]->sub[1]->toString());
		}
	}
}


Expr* resolve(Expr* clause1, Expr* clause2, string Prop) {
	bool posPropInClause1 = false;
	Expr* resolvent = parse("(or )");
	vector<string>* clause1Vars = new vector<string>();
	vector<string>* clause1negVars = new vector<string>();
	vector<string>* clause2Vars = new vector<string>();
	vector<string>* clause2negVars = new vector<string>();

	getVars(clause1, clause1Vars, clause1negVars);
	getVars(clause2, clause2Vars, clause2negVars);

	for(string s : *clause1Vars) {
		if(s == Prop) { 
			posPropInClause1 = true;
		}
	}

	// pos prop in clause 1, neg prop in clause 2
	if(posPropInClause1) {
		for(unsigned int i = 0; i < clause1->sub.size(); i++) {
			if(clause1->sub[i]->sym != Prop && clause1->sub[i]->sym != "or") {
				resolvent->sub.push_back(clause1->sub[i]);
			}
		}
		for(unsigned int i = 0; i < clause2->sub.size(); i++) {
			if(clause2->sub[i]->kind == ATOM && clause2->sub[i]->sym == "or")
				continue;
			if(clause2->sub[i]->kind == ATOM || clause2->sub[i]->sub[1]->sym != Prop) {
				resolvent->sub.push_back(clause2->sub[i]);
			}
		}
	}
	else { // neg prop in clause 1, pos prop in clause 2
		for(unsigned int i = 0; i < clause1->sub.size(); i++) {
			if(clause1->sub[i]->kind == ATOM && clause1->sub[i]->sym == "or")
				continue;
			if(clause1->sub[i]->kind == ATOM || clause1->sub[i]->sub[1]->sym != Prop) {
				resolvent->sub.push_back(clause1->sub[i]);
			}
		}
		for(unsigned int i = 0; i < clause2->sub.size(); i++) {
			if(clause2->sub[i]->sym != Prop && clause2->sub[i]->sym != "or") {
				resolvent->sub.push_back(clause2->sub[i]);
			}
		}
	}

	// factoring
	for(int i = resolvent->sub.size() - 1; i >= 0; i--) {
		for(int j = i - 1; j >= 0; j--) {
			if(Eq(resolvent->sub[i],resolvent->sub[j])) {
				cout << "found duplicate: " << resolvent->sub[i]->toString() << " , " << resolvent->sub[j]->toString() << endl;
				resolvent->sub.erase(resolvent->sub.begin() + j);
				cout << "erased dup" << endl;
			}
		}
	}

	return resolvent;
}


vector<string> matching_propositions(Expr* clause1, Expr* clause2) {
	vector<string> matching;
	vector<string>* clause1Vars = new vector<string>();
	vector<string>* clause1negVars = new vector<string>();
	vector<string>* clause2Vars = new vector<string>();
	vector<string>* clause2negVars = new vector<string>();

	getVars(clause1, clause1Vars, clause1negVars);
	getVars(clause2, clause2Vars, clause2negVars);

	for(string s1 : *clause1Vars) {
		for(string s2 : *clause2negVars) {
			if(s1 == s2) {
				matching.push_back(s1);
			}
		}
	}

	for(string s1 : *clause1negVars) {
		for(string s2 : *clause2Vars) {
			if(s1 == s2) {
				matching.push_back(s1);
			}
		}
	}
	
	return matching;
}


bool resolvable(Expr* clause1, Expr* clause2) {
	vector<string> matching = matching_propositions(clause1, clause2);
	if(!matching.empty())
		return true;
	else
		return false;
}


bool validateClause(Expr* clause) {
	if(clause->kind != LIST || clause->sub[0]->sym != "or") // doesnt follow (or <literal>) format
		return false;
	vector<Expr*> sub = clause->sub;
	for(Expr* e : sub) {
		if(e->kind == LIST && e->sub[0]->sym != "not") // invalid literal
			return false;
		else if(e->kind == LIST && e->sub[0]->sym == "not") // valid neg literal
			continue;
		else if(e->kind == ATOM) // valid pos literal
			continue;
	}
	
	vector<string>* vars = new vector<string>();
	vector<string>* negVars = new vector<string>();
	getVars(clause, vars, negVars);

	for(string s1 : *vars) {
		for(string s2 : *negVars) {
			if(s1 == s2) {
				return false; // var is both pos and neg in same clause :(
			}
		}
	}

	return true;
}


bool contains(vector<Expr*> KB, Expr* clause) {
	for(Expr* e : KB) {
		if(Eq(e,clause))
			return true;
	}
	return false;
}

bool resolution(vector<Expr*> KB, Expr* negatedQuery, string origQuery) {
	KB.push_back(negatedQuery);
	show_kb(KB);
	cout << endl << endl;
	for(Expr* e : KB) {
		if(!validateClause(e)) {
			cout << "invalid clause: " << e->toString() << endl;
			exit(-1);
		}
	}
	queue<ResPair> Q;
	for(unsigned int i = 0; i < KB.size(); i++) {
		for(unsigned int j = i + 1; j < KB.size(); j++) {
			if(resolvable(KB[i],KB[j])) {
				ResPair temp(i,j);
				Q.push(temp);
			}
			// vector<string> matching = matching_propositions(KB[i],KB[j]);
			// if(matching.empty())
			// 	continue;
			// cout << "matching between " << i << " " << j << ": ";
			// for(string s : matching) {
			// 	cout << s << " ";
			// }
			// cout << endl;
		}
	}
	int iter = -1;
	while(!Q.empty() && iter++ < MAX_ITERS) {
		cout << "iteration=" << iter << ", clauses=" << KB.size() << endl;
		ResPair curr = Q.front();
		Q.pop();
		vector<string> props = matching_propositions(KB[curr.i],KB[curr.j]);
		for(string P : props) {
			cout << "resolving clauses " << curr.i << " and " << curr.j << ": ";
			cout << KB[curr.i]->toString() << " , " << KB[curr.j]->toString() << endl;
			Expr* resolvent = resolve(KB[curr.i],KB[curr.j],P);
			cout << "resolvent = " << resolvent->toString() << endl;
			if(resolvent->toString() == "(or )") {
				cout << "success! derived empty clause, so " << origQuery << " is entailed" << endl; 
				return true;
			}
			if(validateClause(resolvent) == false || contains(KB, resolvent)) {
				continue;
			}
			for(unsigned int i = 0; i < KB.size(); i++) {
				if(resolvable(KB[i],resolvent)) {
					ResPair temp(i,KB.size()); // KB.size() SHOULD represent the clause number of the resolvent that is about to get pushed to KB
					Q.push(temp);
				}
			}
			KB.push_back(resolvent);
			cout << KB.size() - 1 << ". " << KB[KB.size() - 1]->toString() << endl;
		}

	}
	return false;
}

int main(int argc, char* argv[]) {
	if(argc != 3 && argc != 4) {
		cout << "Incorrect input arguments: must use form ./resolution <*.cnf> <query> <optional: -n flag denoting negated query>" << endl;
		exit(1);
	}

	try {
		vector<Expr*> KB = load_kb(argv[1]);
		// add negated query (prob include additional flag)
		Expr* negatedQuery;
		// case 1: negated var: "(not C2Y)"
		if(argc == 4 && strcmp(argv[3],"-n") == 0) {
			negatedQuery = parse(argv[2]);
			negatedQuery->sub[0]->sym = "or";
		}
		// case 2: single var ex: C2W or safe22
		else if(argc == 3) {
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

		// Expr* test1 = parse("(or A (not B) E C D)");
		// Expr* test2 = parse("(or E (not A) D)");

		// resolve(test1, test2, "A");
		// resolve(test2, test1, "A");
		bool result = resolution(KB,negatedQuery,argv[2]);
		if(!result) {
			cout << "failure" << endl;
		}

	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
}
