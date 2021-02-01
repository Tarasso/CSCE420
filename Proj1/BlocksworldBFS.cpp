#include <iostream>
#include <fstream>
#include <sstream>
#include "State.h"

using namespace std;

vector<string> split(string s, char c)
{
  istringstream ss(s);
  string token;
  vector<string> tokens;
  while(getline(ss,token,c))
    tokens.push_back(token);
  return tokens;
}


pair< vector<string>,vector<string> > readInput(string fileName)
{
    ifstream file;
    file.open(fileName);

    if(!file.is_open())
        cout << "Error opening file" << endl;

    string line;
    getline(file, line);
    vector<string> tokens = split(line, ' ');
    int stacks = stoi(tokens[0]);
    int blocks = stoi(tokens[1]);
    int moves = stoi(tokens[2]);

    vector<string> startStateVec;
    vector<string> goalStateVec;

    getline(file,line); //skips the line of >>>>
    for(int i = 0; i < stacks; i++)
    {
        getline(file,line);
        startStateVec.push_back(line);
    }

    getline(file,line); //skips the line of >>>>
    for(int i = 0; i < stacks; i++)
    {
        getline(file,line);
        goalStateVec.push_back(line);
    }

    return make_pair(startStateVec,goalStateVec);
}


int main(int argc, char *argv[])
{
    if(argc != 2)
        cout << "Invalid arguments given" << endl;

    pair< vector<string>,vector<string> > vecPair = readInput(argv[1]);
    State startState = vecPair.first;
    State goalState = vecPair.second;

    cout << "Start:" << startState.hash() << endl;
    cout << "Goal:" << goalState.hash() << endl;

    cout << startState.match(&goalState) << endl;
    cout << startState.match(&startState) << endl;

    cout << "Start:" << endl;
    startState.print();
    cout << "---" << endl;
    cout << "Goal:" << endl;
    goalState.print();
    cout << "---" << endl;

    vector<State*> succs = startState.successors();
    for(int i = 0; i < succs.size(); i++)
    {
        cout << "State " << i << endl;
        succs[i]->print();
    }
}