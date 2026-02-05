#ifndef CLUSTER_H
#define CLUSTER_H

#include "Environment.h"
#include "Species.h"
#include <string>
#include <vector>
#include <utility> 

class Cluster : public Environment
{
protected:
    std::vector<Bacterium> alive;
    std::vector<Bacterium> dead;

    unsigned long int totalBacteria = 0;
    unsigned long int totalAliveBacteria = 0;
    unsigned long int totalDeadBacteria = 0;
    
    std::pair<bool, unsigned long int> isPresent(const Bacterium& b);
    void add(Bacterium* b);
    void omit(Bacterium* b);
    void step();

public:
    Cluster(int numBacteria = 100, int randomiseType = 1, double EnergyLevel = 300.0f);

    void updateTemporalResolution(double tempRes);
    void run(std::string filename);
};

#endif