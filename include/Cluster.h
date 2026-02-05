#ifndef CLUSTER_H
#define CLUSTER_H

#include "Environment.h"
#include "Species.h"
#include <string>

class Cluster : public Environment, protected Bacterium
{

protected:
    // A vector of bacterium which contains all alive members
    vector<Bacterium> alive = {};
    // A vector of bacterium which contains all dead members
    vector<Bacterium> dead = {};

    // values containing total values of bacteria
    unsigned long int totalBacteria = 0;
    unsigned long int totalAliveBacteria = 0;
    unsigned long int totalDeadBacteria = 0;
    
    // Accessors 
    std::pair<bool, unsigned long int> isPresent( Bacterium );
    
    // Mutators - functions to edit the members of the cluster
    // add - registers the bacterium into the cluster
    void add( Bacterium* );
    void omit( Bacterium* );

    void step();


public:

    // initializer
    Cluster(int numBacteria = 100, int randomiseType = 1, 
            double EnergyLevel = 300.0f);

    void updateTemporalResolution(double tempRes);

    // runs as long as all the bacteria does not die
    void run(std::string filename);
    // runs uptil a particular time speciefied or until all bacteia die
    void run(std::string filename, double time);  

};


#endif
