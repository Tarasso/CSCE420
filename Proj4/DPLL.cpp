#include <iostream>
#include <vector>
#include "parser.h"

using namespace std;

int main(int argc, char* argv[])
{
  cout << "howdy world" << endl;
  Expr* s1 = parse("(or A B C)");
  vector<Expr*> temp = s1->sub;
  for(int i = 0; i < temp.size(); i++)
  {
    cout << "type: " << to_string(temp[i]->kind) << endl;
    cout << temp[i]->toString() << endl;
  }
}
