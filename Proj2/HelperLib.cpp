using namespace std;

#ifndef HELPERLIB_CPP
#define HELPERLIB_CPP

#include <vector>
#include <string>
#include <sstream>

vector<string> split(string s, char c)
{
  bool delimAtEnd = false;
  istringstream ss(s);
  string token;
  if(s.find_last_of(c)==s.size()-1)
    delimAtEnd = true;
  vector<string> tokens;
  while(getline(ss,token,c))
    tokens.push_back(token);
  if(delimAtEnd)
    tokens.push_back("");
  return tokens;
}

#endif