#include <iostream>
#include <vector>
#include <unordered_map>
#include "parser.h"

using namespace std;

// MODEL contains variables and their current assignment
typedef unordered_map<string, bool> MODEL;

void printModel(MODEL* model, vector<string> symbols)
{
  cout << "model: ";
  for(int i = 0; i < symbols.size(); i++)
  {
    cout << symbols[i] << "=";
    if(model->find(symbols[i]) == model->end())
      cout << "? ";
    else
    {
      if (model->at(symbols[i]))
        cout << "T ";
      else
        cout << "F ";
    }
  }
}

bool evalExpr(Expr* expr, MODEL* model)
{
  vector<Expr*> temp = expr->sub;
  vector<string> vars;
  vector<string> negVars;

  // identify vars in expr
  for(int i = 0; i < temp.size(); i++)
  {
    if(temp[i]->kind == ATOM && temp[i]->sym != "or" && temp[i]->sym != "not")
    {
      //cout << "detected var: " << temp[i]->toString() << endl;
      vars.push_back(temp[i]->toString());
    }
    else if (temp[i]->kind == LIST)
    {
      //cout << "detected negated var: " << temp[i]->sub[0]->toString() << endl;
      negVars.push_back(temp[i]->sub[0]->toString());
    }
  }

  // eval expr

  
  // expr is true
  // expr could be true
  // expr cant be true
  return false;
}

int numSatClauses()
{

}

bool DPLL(vector<Expr*> clauses, vector<string>* symbols, MODEL* model)
{
  
  // if all clauses are true then return true
  if (numSatClauses() == clauses.size())
    return true;
  // if any single clause is false then return false

  // else: (meaning nothing is false, but not everything is true yet)

  // choose symbol to try P
  // remove P from symbols
  // add P to model

  // return DPLL(clauses, symbols, model + P=true) || DPLL(clauses, symbols, model + P=false)
  
  return nullptr;
}

// TODO: support unit clause flag <-unit>
int main(int argc, char* argv[])
{

  try
  {
    // loading rules
    vector<Expr*> KB = load_kb("mapcolor.cnf");
    show_kb(KB);

    // obtain or hardcode symbols
    // MODEL* model = nullptr;
    // vector<string>* symbols;
    // MODEL* retModel = DPLL(KB, symbols, model);
    // if(retModel)
    // {
    //   cout << "model found!" << endl;
    // }
    // else
    // {
    //   cout << "no valid model found!" << endl;
    // }

    


  }
  catch(const std::exception& e)
  {
    std::cerr << e.what() << '\n';
  }
  

}
