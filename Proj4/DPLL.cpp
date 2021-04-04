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
    cout << symbols.at(i) << "=";
    if(model->find(symbols.at(i)) == model->end())
      cout << "? ";
    else
    {
      if (model->at(symbols.at(i)))
        cout << "T ";
      else
        cout << "F ";
    }
  }
  cout << endl;
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

bool containsFalseClause()
{

}

MODEL* DPLL(vector<Expr*> clauses, vector<string> symbols, MODEL* model)
{
  // printing documentation
  printModel(model, symbols);
  cout << "num clauses satisfied: " << numSatClauses() << "out of " << clauses.size() << endl;
  
  // if all clauses are true then return true
  if (numSatClauses() == clauses.size())
    return model;
  // if any single clause is false then return false
  if (containsFalseClause())
    return nullptr;

  // else: (meaning nothing is false, but not everything is true yet)



  // choose symbol to try P
  // remove P from symbols
  // add P to model

  // return DPLL(clauses, symbols, model + P=true) || DPLL(clauses, symbols, model + P=false)
  
  return nullptr;
}

// assumes that KB is written in CNF using "()"", "or", "not", and symbols only
void getSymbols(vector<Expr*> KB)
{
  MODEL model;
  int count = 0;
  for(int i = 0; i < KB.size(); i++)
  {
    vector<string> tokens = tokenize(KB[i]->toString());
    for(int j = 0; j < tokens.size(); j++)
    {
      if(tokens[j] != "(" && tokens[j] != ")" && tokens[j] != "or" && tokens[j] != "not")
      {
        if(model.find(tokens[j]) == model.end())
        {
          model.insert(make_pair(tokens[j],true));
          cout << ++count << ". " << tokens[j] << endl;
        }
      }
    }
  }
  


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
    MODEL* model = new MODEL();
    vector<string> symbols;
    symbols.push_back("WAR");
    symbols.push_back("WAG");
    symbols.push_back("WAB");
    symbols.push_back("QR");
    symbols.push_back("QG");
    symbols.push_back("QB");
    model->insert(make_pair("WAR",true));
    model->insert(make_pair("WAG",false));
    model->insert(make_pair("WAB",false));
    printModel(model, symbols);

    getSymbols(KB);

    // vector<string> temp = tokenize(KB[0]->toString());
    // for(string s : temp)
    //   cout << s << endl;


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
