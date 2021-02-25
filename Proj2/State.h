using namespace std;

#ifndef STATE_H
#define STATE_H

#include <vector>
#include <string>


class State
{   
    public:
        vector<string> bw;
        State(vector<string> s);
        void print();
        bool match(State* other);
        string hash();
        vector<State*> successors();
        float heuristic(State* goal);
};


#endif