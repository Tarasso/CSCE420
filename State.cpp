using namespace std;

#ifndef STATE_CPP
#define STATE_CPP

#include "State.hpp"
#include <iostream>


State::State(vector<string> s)
{
    bw = s;
}

void State::print() 
{
    for(string s : bw)
    {
        cout << s << endl;
    }
}

bool State::match(State* other)
{
    for(int i = 0; i < bw.size(); i++)
    {
        if(this->bw[i] != other->bw[i])
            return false;
    }

    return true;
}

string State::hash()
{
    string ret = "";
    for(int i = 0; i < bw.size(); i++)
    {
        ret += bw[i];
        if(i != bw.size()-1)
            ret += ";";
    }
    return ret;
}

//TODO create function
vector<State*> State::successors()
{
    
}




#endif