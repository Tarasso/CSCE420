using namespace std;

#ifndef STATE_CPP
#define STATE_CPP

#include "State.h"
#include <iostream>
#include <typeinfo>


State::State(vector<string> s)
{
    bw= vector<string>(s);
}

void State::print() 
{
    for(unsigned int i = 0; i < bw.size(); i++)
    {
        cout << bw[i] << endl;
    }
    cout << "<<<<<<<<<<" << endl;
}

bool State::match(State* other)
{
    for(unsigned int i = 0; i < bw.size(); i++)
    {
        if(this->bw[i] != other->bw[i])
            return false;
    }

    return true;
}

string State::hash()
{
    string ret = "";
    for(unsigned int i = 0; i < bw.size(); i++)
    {
        ret += bw[i];
        if(i != bw.size()-1)
        {
            ret += ';';
        }
    }
    return ret;
}


vector<State*> State::successors()
{
    vector<State*> succs;

    for(unsigned int oldRow = 0; oldRow < bw.size(); oldRow++)
    {
        // no block to move
        if(bw[oldRow] == "")
            continue;
        
        for(unsigned int newRow = 0; newRow < bw.size(); newRow++)
        {
            if(oldRow == newRow)
                continue; // skip moving block from and to same row
            
            vector<string> newBw;

            //constructs new vector for new state
            for(unsigned int i = 0; i < bw.size(); i++)
            {
                if(i == oldRow)
                {
                    if(bw[i].size() == 1)
                    {
                        newBw.push_back("");
                    }
                    else
                        newBw.push_back(bw[i].substr(0,bw[i].size()-1));
                }
                    
                else if (i == newRow)
                {
                    newBw.push_back(bw[i]+bw[oldRow][bw[oldRow].size()-1]);
                }
                    
                else
                {
                    newBw.push_back(bw[i]);
                }
                    
            }
            
            State* newState = new State(newBw);
            succs.push_back(newState);
        }
    }
    return succs;
}

float State::heuristic(State* goal)
{
    return 0.0;
}


#endif