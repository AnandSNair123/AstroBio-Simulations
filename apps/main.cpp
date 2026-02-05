#include <cstdlib>
#include <string>
#include <iostream>
#include "Cluster.h"

using namespace std;

int main()
{
    string filename = "trial1.csv";

    cout << "Initializing Base Simulation..." << endl;
    
    // Start with 1000 bacteria (Clean Slate)
    Cluster cottonBed(1000);             
    
    cottonBed.run(filename);    

    string command = "python ../utils/plot.py " + filename;
    int return_code = system(command.c_str());
    
    return 0;
}