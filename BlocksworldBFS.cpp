#include <iostream>
#include <ifstream>
#include "State.h"

using namespace std;


State readInput(string fileName)
{
    

}


int main(int argc, char *argv[])
{
    if(argc != 2)
        cout << "Invalid arguments given" << endl;

    State initialState = readInput(argv[1]);
}