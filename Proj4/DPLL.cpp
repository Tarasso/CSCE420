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

string getNextSymbol(vector<string> symbols, MODEL* model)
{
  for(unsigned int i = 0; i < symbols.size(); i++)
    {
      // if symbol is not current in the model
      if(model->find(symbols.at(i)) == model->end())
        return symbols.at(i);
    }

  cout << "there is prob something wrong" << endl;
  return "";
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
  string newSymbol = getNextSymbol(symbols, model);

  MODEL* newModel0 = deepCopy(model);
  newModel0->insert(make_pair(newSymbol,false));
  MODEL* newModel1 = deepCopy(model);
  newModel1->insert(make_pair(newSymbol,true));

  cout << "trying " << newSymbol << "=0" << endl << endl;
  DPLL(clauses, symbols, newModel0);
  cout << "trying " << newSymbol << "=1" << endl << endl;
  DPLL(clauses, symbols, newModel1);

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
      cout << "success!" << endl;
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
      cout << "model is unsatisfiable" << endl;
    }


    // obtain or hardcode symbols
    // MODEL* model = new MODEL();
    // vector<string> symbols;
    // symbols.push_back("WAR");
    // symbols.push_back("WAG");
    // symbols.push_back("WAB");
    // symbols.push_back("QR");
    // symbols.push_back("QG");
    // symbols.push_back("QB");
    // model->insert(make_pair("WAR",true));
    // model->insert(make_pair("WAG",false));
    // model->insert(make_pair("WAB",false));
    // printModel(model, symbols);

    

    // Expr* s1 = parse("(or WAR WAG WAB)");
    // cout << "consistent: " << evalExpr(s1,model) << endl;
    // Expr* s2 = parse("(or not(WAR) WAG WAB)");
    // cout << "consistent: " << evalExpr(s2,model) << endl;
    // Expr* s3 = parse("(or not(WAR) not(WAG) not(WAB))");
    // cout << "consistent: " << evalExpr(s3,model) << endl;
    // Expr* s4 = parse("(or QR WAG WAB)");
    // cout << "consistent: " << evalExpr(s4,model) << endl;


    // MODEL* model1 = new MODEL();
    // model1->insert(make_pair("NSWB",false));
    // model1->insert(make_pair("NSWG",false));
    // model1->insert(make_pair("NSWR",true));
    // model1->insert(make_pair("NTB",false));
    // model1->insert(make_pair("NTG",false));
    // model1->insert(make_pair("NTR",true));
    // model1->insert(make_pair("QB",true));
    // model1->insert(make_pair("QG",false));
    // model1->insert(make_pair("QR",false));
    // model1->insert(make_pair("SAB",false));
    // model1->insert(make_pair("SAG",true));
    // model1->insert(make_pair("SAR",false));
    // model1->insert(make_pair("TB",true));
    // model1->insert(make_pair("TG",false));
    // model1->insert(make_pair("TR",false));
    // model1->insert(make_pair("VB",true));
    // model1->insert(make_pair("VG",false));
    // model1->insert(make_pair("VR",false));
    // model1->insert(make_pair("WAB",true));
    // model1->insert(make_pair("WAG",false));
    // model1->insert(make_pair("WAR",false));
    

    // cout << "num clauses sat: " << numSatClauses(KB, model1) << endl;
    // cout << "contains false clause: " << containsFalseClause(KB, model1) << endl;

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
