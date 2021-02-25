using namespace std;

#ifndef NODE_H
#define NODE_H

#include "State.h"
#include <vector>
// #include <string>


class Node
{   
    public:
        State* state;
        State* goalState;
        int depth;
        Node* parent;
        float score;

        Node(State* s, State* gs);
        Node(State* s, int d, Node* p, State* gs);
        bool goal_test(State* other);
        vector<Node*> successors();
        string hash();
        int print_path();

};


#endif