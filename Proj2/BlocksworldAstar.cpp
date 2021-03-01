#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>
#include <unordered_map>
#include <stdlib.h>
#include "State.h"
#include "HelperLib.h"
#include "Node.h"

#define MAX_ITERS 100000

using namespace std;

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
    //int blocks = stoi(tokens[1]); not being used
    //int moves = stoi(tokens[2]); not being used 

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

struct CompareScore
{
    bool operator()(const Node* lhs, const Node* rhs) const
    {
        return lhs->score > rhs->score;
    }
};

Node* aStarSearch(Node* startNode, State* goalState)
{
    int iter = 0;
    unsigned int maxQueueSize = 0;
    
    Node* node = startNode;

    if(node->goal_test(goalState))
    {
        cout << "success! iter=" << iter << ", depth=" << node->depth << ", max queue size=" << maxQueueSize << endl;
        return node;
    }

    priority_queue<Node*, vector<Node*>, CompareScore> frontier;
    //queue<Node*> frontier;
    frontier.push(node);
    cout << "frontier created and node added" << endl;
    unordered_map<string,Node*> reached;
    reached.insert(make_pair(node->hash(),node));
    cout << "reached created and node added" << endl;

    while(!frontier.empty())
    {
        node = frontier.top();
        frontier.pop();
        cout << "node popped depth " << node->depth << endl;
        //cout << "before children" << endl;
        vector<Node*> children = node->successors();
        //cout << "created children" << endl;

        for(Node* child : children)
        {
            if(iter > MAX_ITERS)
            {
                cout << "failed to solve problem: reached iteration limit of " << MAX_ITERS << endl;
                return nullptr;
            }
            
            iter++;

            if(child->goal_test(goalState))
            {
                cout << "success! iter=" << iter << ", depth=" << child->depth << ", max queue size=" << maxQueueSize << endl;
                return child;
            }
            
            if(reached[child->hash()] == 0 || child->depth < reached[child->hash()]->depth)
            {
                reached[child->hash()] = child;
                frontier.push(child);
                if(frontier.size() > maxQueueSize)
                    maxQueueSize = frontier.size();
            }
        }
    }

    cout << "Frontier is empty" << endl;
    return nullptr;
}


int main(int argc, char *argv[])
{
    if(argc != 2)
        cout << "Invalid arguments given" << endl;

    pair< vector<string>,vector<string> > vecPair = readInput(argv[1]);

    State* startState = new State(vecPair.first);
    State* goalState = new State(vecPair.second);

    Node* startNode = new Node(startState, goalState);

    Node* goalNode = aStarSearch(startNode, goalState);
    if(goalNode != nullptr)
        goalNode->print_path();
    else
        cout << "Goal node is null" << endl;

    delete startState;
    delete startNode;
    delete goalState;
    delete goalNode;
}