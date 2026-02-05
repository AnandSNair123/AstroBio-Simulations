#include <cstdlib>
#include <string>
#include <iostream>
#include "Cluster.h"
using namespace std;

int main()
{
    // Output filename
    string filename = "trial1.csv";

    // Initialising environment and running simulations
    Cluster cottonBed(100);             // initial number of bacteria
    cottonBed.run(filename);    // inputs -name of output file

    // Calling python script to plot graph
    string command = "../utils/plot.py " + filename;
    int return_code = system(command.c_str());
    if (return_code != 0){
        cout << "Python Code failed with exit code : " << return_code;
        return return_code + 10;
    }

    return 0;
}
