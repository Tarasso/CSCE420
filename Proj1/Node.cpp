using namespace std;

#ifndef NODE_CPP
#define NODE_CPP

#include "Node.h"
#include <iostream>

Node::Node(State* s)
{
    state = s;
    depth = 0;
    parent = nullptr;
}

Node::Node(State* s, int d, Node* p)
{
    state = s;
    depth = d;
    parent = p;
}


bool Node::goal_test(State* other)
{
    return state->match(other);
}


vector<Node*> Node::successors()
{
    vector<Node*> succNodes;
    vector<State*> succs = state->successors();
    for(int i = 0; i < succs.size(); i++)
    {
        Node* tempNode = new Node(succs[i], depth+1, this);
        succNodes.push_back(tempNode);
    }
    return succNodes;
}


string Node::hash()
{
    return state->hash();
}

int Node::print_path()
{
    if(parent != nullptr)
    {
        //cout << "inside if" << endl;
        parent->print_path();
        cout << "move " << depth << endl;
        state->print();
    }
    else
    {
        //cout << "inside else" << endl;
        cout << "move " << depth << endl;
        state->print();
    }
    
}



#endif