#include <iostream>
#include <fstream>
#include "State.h"

using namespace std;


State readInput(string fileName)
{
    ifstream file;
    file.open(fileName);
    if(!file.is_open())
        cout << "Error opening file" << endl;

    

}


int main(int argc, char *argv[])
{
    if(argc != 2)
        cout << "Invalid arguments given" << endl;

    State initialState = readInput(argv[1]);
}