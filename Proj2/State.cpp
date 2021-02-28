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
    //cout << "before loop" << endl;
    // for(unsigned int i = 0; i < currEncoded.size(); i++)
    // {
    //     // adds one to blocksOutOfPlace for each block in the current state that does not align with the goal state
    //     if(currEncoded[i] != ';' && currEncoded[i] != goalEncoded[i])
    //         blocksOutOfPlace++;
    // }
    //cout << "after loop" << endl;

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

    cout << "curr: \"" << this->hash() << "\"" << endl;
    cout << "goal: \"" << goal->hash() << "\"" << endl;
    cout << "blocks out of place " << blocksOutOfPlace << endl;
    
    // cout << "current: ";
    // for(string s : currStateEncodedSplit)
    //     cout << "\"" << s << "\" ";
    // cout << endl << "goal: ";
    // for(string s : goalStateEncodedSplit)
    //     cout << "\"" << s << "\" ";
    // cout << endl;
    
    // cout << "made it here" << endl;
    // // each stack in current state
    // for(unsigned int i = 0; i < currStateEncodedSplit.size(); i++)
    // {
    //     cout << "i = " << i << endl;
    //     // if the stack is empty in current and goal, just keep moving
    //     if(goalStateEncodedSplit[i] == "" && currStateEncodedSplit[i] == "")
    //     {
    //         cout << "made it here" << endl;
    //         continue;
    //     }
    //     cout << "why am i here????" << endl;
                
        
    //     // each letter in each stack
    //     for(unsigned int j = 0; j < currStateEncodedSplit[i].size(); j++)
    //     {
    //         cout << "j = " << j << endl;
    //         cout << "current: " << currStateEncodedSplit[i] << endl;
    //         cout << "goal: " << goalStateEncodedSplit[i] << endl;
    //         // handle empty string issues
    //         if((goalStateEncodedSplit[i] != "" && currStateEncodedSplit[i] == "")
    //         || (goalStateEncodedSplit[i] == "" && currStateEncodedSplit[i] != ""))
    //             blocksOutOfPlace++;
    //         // check if in same location
    //         else if(goalStateEncodedSplit[i][j] != (currStateEncodedSplit[i][j]))
    //             blocksOutOfPlace++;
    //     }
    // }
    
    return blocksOutOfPlace;
}


#endif