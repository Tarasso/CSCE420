#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include "parser.h"

using namespace std;

// contains variables and their current assignment
typedef unordered_map<string, bool> MODEL;
// used to determine whether an expr is T/F or could possibly be T depending on missing var
enum Eval { FALSE, TRUE, MAYBE};
bool useUnitClause = true;
int dpllCalls = 0;

void printModel(MODEL* model, vector<string> symbols)
{
  for(unsigned int i = 0; i < symbols.size(); i++)
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

Eval evalExpr(Expr* expr, MODEL* model)
{
  vector<Expr*> temp = expr->sub;
  vector<string> vars;
  vector<string> negVars;

  // identify vars in expr
  for(unsigned int i = 0; i < temp.size(); i++)
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
  Eval isConsistent = FALSE;
  bool hasUnassignedVar = false;

  // expr true if any var is true
  for(string var : vars)
  {
    if(model->find(var) == model->end())
      hasUnassignedVar = true;
    else if(model->at(var) == true)
      isConsistent = TRUE;
  }
    
  // expr is true of any negated var is false
  for(string negVar : negVars)
  {
    if(model->find(negVar) == model->end())
      hasUnassignedVar = true;
    else if(model->at(negVar) == false)
      isConsistent = TRUE;
  }
    
  if(isConsistent == FALSE && hasUnassignedVar)
    isConsistent = MAYBE; // could possibly be true but is not currently

  return isConsistent;
}

unsigned int numSatClauses(vector<Expr*> clauses, MODEL* model)
{
  unsigned int satClauses = 0;
  for(Expr* ex : clauses)
  {
    if(evalExpr(ex, model) == TRUE)
      satClauses++;
  }
  return satClauses;
}

bool containsFalseClause(vector<Expr*> clauses, MODEL* model)
{
  for(Expr* ex : clauses)
  {
    if(evalExpr(ex, model) == FALSE)
      return true;
  }
  return false;
}

MODEL* deepCopy(MODEL* oldModel)
{
  MODEL* newModel = new MODEL();
  for(auto it : *oldModel)
    newModel->insert(it);

  return newModel;
}

pair<string, Eval> identifyUnitVar(Expr* expr, vector<string> symbols, MODEL* model)
{
  if(evalExpr(expr, model) != MAYBE)
    return make_pair("",FALSE);
  
  // cout << "clause is a maybe" << endl;

  vector<Expr*> temp = expr->sub;
  vector<string> vars;
  vector<string> negVars;

  // identify vars in expr
  for(unsigned int i = 0; i < temp.size(); i++)
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
  // Eval isConsistent = FALSE;
  // bool hasUnassignedVar = false;

  unsigned int unassignedVars = 0;
  string unitVarName = "";
  Eval unitVarValue = FALSE;

  // identify any positive unassigned variables
  for(string var : vars)
  {
    if(model->find(var) == model->end())
    {
      // hasUnassignedVar = true;
      unassignedVars++;
      unitVarName = var;
      unitVarValue = TRUE;
    }
  }
    
  // identify any negative unassigned variables
  for(string negVar : negVars)
  {
    if(model->find(negVar) == model->end())
    {
      // hasUnassignedVar = true;
      unassignedVars++;
      unitVarName = negVar;
      unitVarValue = FALSE;
    }
  }
    
  // cout << unassignedVars << "degrees of freedom" << endl;

  // a single unassigned var means a unit clause
  if(unassignedVars == 1)
    return make_pair(unitVarName, unitVarValue);
  else
    return make_pair("",FALSE);
}

pair<string, Eval> getNextSymbol(vector<Expr*> clauses, vector<string> symbols, MODEL* model)
{
  if(useUnitClause)
  {
    // check each clause in KB
    for(unsigned int i = 0; i < clauses.size(); i++)
    {
      // return forced assignment
      pair<string,Eval> ret = identifyUnitVar(clauses[i], symbols, model);
      if(ret.first != "")
        return ret;
    }
  }
  
  // below grabs next unassigned variable
  
  for(unsigned int i = 0; i < symbols.size(); i++)
    {
      // if symbol is not current in the model
      if(model->find(symbols.at(i)) == model->end())
        return make_pair(symbols.at(i), MAYBE);
    }

  // error checking, should not get to here
  cout << "there is prob something wrong" << endl;
  return make_pair("",MAYBE);
}

MODEL* DPLL(vector<Expr*> clauses, vector<string> symbols, MODEL* model)
{
  ++dpllCalls;
  // printing documentation
  printModel(model, symbols);
  cout << "num clauses satisfied: " << numSatClauses(clauses, model) << " out of " << clauses.size() << endl;
  
  // if all clauses are true then return true
  if (numSatClauses(clauses, model) == clauses.size())
    return model;
  // if any single clause is false then return false
  if (containsFalseClause(clauses, model))
  {
    cout << "back-tracking..." << endl;
    return nullptr;
  }

  // choose symbol to try
  // NOTE: Eval=TRUE/FALSE is "forced", Eval=MAYBE is "trying"
  pair<string,Eval> newSymbol = getNextSymbol(clauses, symbols, model);

  MODEL* newModel0 = deepCopy(model);
  MODEL* newModel1 = deepCopy(model);

  // handles forcing variables
  if(newSymbol.second != MAYBE)
  {
    if(newSymbol.second == TRUE)
    {
      cout << "forcing " << newSymbol.first << "=1" << endl << endl;
      newModel1->insert(make_pair(newSymbol.first,true));
      return DPLL(clauses, symbols, newModel1);
    }
    else if (newSymbol.second == FALSE)
    {
      cout << "forcing " << newSymbol.first << "=0" << endl << endl;
      newModel0->insert(make_pair(newSymbol.first,false));
      return DPLL(clauses, symbols, newModel0);
    }
    
  }
  // handles trying variables
  else
  {
    newModel0->insert(make_pair(newSymbol.first,false));
    newModel1->insert(make_pair(newSymbol.first,true));

    cout << "trying " << newSymbol.first << "=0" << endl << endl;
    MODEL* ret0 = DPLL(clauses, symbols, newModel0);

    if(ret0 != nullptr)
      return ret0;
    
    cout << "trying " << newSymbol.first << "=1" << endl << endl;
    MODEL* ret1 = DPLL(clauses, symbols, newModel1);

    return ret1;
  }

  // shouldnt get here but to remove warning
  return nullptr;
}

// assumes that KB is written in CNF using "()"", "or", "not", and symbols only
vector<string> getSymbols(vector<Expr*> KB)
{
  MODEL model;
  //int count = 0;
  vector<string> symbols;

  for(unsigned int i = 0; i < KB.size(); i++)
  {
    vector<string> tokens = tokenize(KB[i]->toString());
    for(unsigned int j = 0; j < tokens.size(); j++)
    {
      if(tokens[j] != "(" && tokens[j] != ")" && tokens[j] != "or" && tokens[j] != "not")
      {
        if(model.find(tokens[j]) == model.end())
        {
          model.insert(make_pair(tokens[j],true));
          //cout << ++count << ". " << tokens[j] << endl;
          symbols.push_back(tokens[j]);
        }
      }
    }
  }
  return symbols;
}

int main(int argc, char* argv[])
{
  if(argc != 2 && argc != 3)
  {
    cout << "Incorrect input arguments: must use form ./dpll <*.cnf> <optional: -unit>" << endl;
    exit(1);
  }
  if(argc == 3)
  {
    string flag = argv[2];
    if(flag == "-unit")
      useUnitClause = false;
  }

  try
  {
    // load KB
    vector<Expr*> KB = load_kb(argv[1]);
    // print KB
    show_kb(KB);
    cout << endl << endl;
    // obtain all symbols in KB
    vector<string> symbols = getSymbols(KB);
    // begin with empty model
    MODEL* model = new MODEL();
    // run DPLL
    MODEL* finalModel = DPLL(KB, symbols, model);
    // print results
    if(finalModel != nullptr)
    {
      cout << "\nsuccess!" << endl;
      cout << "number of DPLL calls = " << dpllCalls;
      if(useUnitClause)
        cout << "(WITH unit-clause heuristic)" << endl;
      else
        cout << "(WITHOUT unit-clause heuristic)" << endl;

      cout << "here is a model: " << endl;
      printModel(finalModel, symbols);
    }
    else
    {
      cout << "failure!" << endl;
      cout << "number of DPLL calls = " << dpllCalls << endl;
      cout << "model is unsatisfiable" << endl;
      
    }

  }
  catch(const std::exception& e)
  {
    std::cerr << e.what() << '\n';
  }
  

}
