using namespace std;

#ifndef STATE_CPP
#define STATE_CPP

#include "State.h"
#include <iostream>


State::State(vector<string> s)
{
    bw = s;
}

void State::print() 
{
    for(int i = 0; i < bw.size(); i++)
    {
        cout << bw[i] << endl;
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
    vector<State*> succs;

    for(int oldRow = 0; oldRow < bw.size(); oldRow++)
    {
        // skip is oldRow is empty?
        
        for(int newRow = 0; newRow < bw.size(); newRow++)
        {
            if(oldRow == newRow)
                continue; // skip successor state that do not move letter??
            
            cout << oldRow << newRow << endl;

            vector<string> newBw;

            //constructs new vector
            for(int i = 0; i < bw.size(); i++)
            {
                if(i == oldRow)
                    newBw.push_back(bw[i].substr(0,bw.size()-1));
                else if (i == newRow)
                    newBw.push_back(bw[i]+bw[oldRow][bw[oldRow].size()-1]);
                else
                    newBw.push_back(bw[i]);
            }
            
            for(int i = 0; i < newBw.size(); i++)
            {
                cout << newBw[i] << endl;
            }
            cout << endl;
            
            State newState = newBw;
            succs.push_back(&newState);
        }
    }
    return succs;
}




#endif