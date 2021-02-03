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
        int depth;
        Node* parent;

        Node(State* s);
        Node(State* s, int d, Node* p);
        bool goal_test(State* other);
        vector<Node*> successors();
        string hash();
        int print_path();

};


#endif