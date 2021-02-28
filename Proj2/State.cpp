using namespace std;

#ifndef STATE_CPP
#define STATE_CPP

#include "State.h"
#include "HelperLib.h"
#include <iostream>
#include <typeinfo>
#include <string>
#include <vector>
#include <sstream>


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
    // number of blocks out of place
    unsigned int blocksOutOfPlace = 0;

    string goalEncoded = goal->hash();
    string currEncoded = this->hash();

    vector<string> goalStateEncodedSplit = split(goal->hash(), ';');
    vector<string> currStateEncodedSplit = split(this->hash(), ';');

    for(unsigned int i = 0; i < currStateEncodedSplit.size(); i++)
    {
        if(currStateEncodedSplit[i] != "")
        {
            for(unsigned int j = 0; j < currStateEncodedSplit[i].size(); j++)
            {
                if(goalStateEncodedSplit[i] == "")
                    blocksOutOfPlace++;
                else if(currStateEncodedSplit[i][j] != goalStateEncodedSplit[i][j])
                    blocksOutOfPlace++;
            }
        }
    }
    
    return blocksOutOfPlace;
}


#endif