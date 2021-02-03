#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>
#include <unordered_map>
#include "State.h"
#include "Node.h"

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

    // for(int i = 0; i < goalStateVec.size(); i++)
    // {
    //     cout << goalStateVec[i] << endl;
    // }

    return make_pair(startStateVec,goalStateVec);
}

Node* BFS(Node* startNode, State* goalState)
{
    int iter = 0;
    int depth = 0;
    int maxQueueSize = 1;
    
    Node* node = startNode;

    if(node->goal_test(goalState))
        return node;
    
    queue<Node*> frontier;
    frontier.push(node);

    unordered_map<string,bool> reached;
    reached.insert(make_pair(node->hash(),true));

    while(!frontier.empty())
    {
        node = frontier.front();
        frontier.pop();

        vector<Node*> children = node->successors();

        for(Node* child : children)
        {
            iter++;

            if(child->goal_test(goalState))
            {
                cout << "success! iter=" << iter << ", depth=" << child->depth << ", max queue size=" << maxQueueSize << endl;
                return child;
            }
            
            if(reached[child->hash()] == false)
            {
                reached[child->hash()] = true;
                frontier.push(child);
                if(frontier.size() > maxQueueSize)
                    maxQueueSize = frontier.size();
            }
        }
    }

    return nullptr;
}


int main(int argc, char *argv[])
{
    if(argc != 2)
        cout << "Invalid arguments given" << endl;

    pair< vector<string>,vector<string> > vecPair = readInput(argv[1]);

    State* startState = new State(vecPair.first);
    State* goalState = new State(vecPair.second);

    Node* root = new Node(startState);

    Node* goalNode = BFS(root, goalState);

    if(goalState)
        goalNode->print_path();


    //root->state->print();
    //vector<Node*> nodes = root->successors();
    //cout << "here" << endl;
    // for(int i = 0; i < nodes.size(); i++)
    // {
    //     nodes[i]->print_path();
    //     cout << endl << endl << endl;
    // }

    // cout << "Start State:" << endl;
    // startState->print();
    // cout << "<<<<<<<<<<<<" << endl;

    // vector<State*> succs = startState->successors();
    // for(int i = 0; i < succs.size(); i++)
    // {
    //     cout << "State " << i << ": " << succs[i]->hash() << endl;
    // }


    // clearing memory
    // for(int i = 0; i < succs.size(); i++)
    // {
    //     delete succs[i];
    // }
    delete startState;
    delete goalState;
}