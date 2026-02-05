#include <iostream>
#include <fstream>
#include <stdexcept>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm> 

using namespace std;

#include "Cluster.h"
#include "Random.h"

// 200x200x50 Grid
Cluster::Cluster(int numBacteria, int randomiseType, double energyValue) 
    : Environment(200, 200, 50) {
    
    RandomGenerator ranGen;
    cout << "Spawning " << numBacteria << " initial bacteria..." << endl;

    switch (randomiseType)
    {
        case 1:
            for (int i = 0; i < numBacteria; ++i){
                vector<int> randomPosition = { 
                    ranGen.Int(0, ranges[0]), 
                    ranGen.Int(0, ranges[1]), 
                    ranGen.Int(0, ranges[2]) 
                };
                
                double randomEnergy = ranGen.Double(250.0, 300.0);
                
                Bacterium* individual = new Bacterium(randomPosition, randomEnergy);
                add(individual);
                delete individual; 
            }
        default:
            break;
    }
}

pair<bool, unsigned long int> Cluster::isPresent(const Bacterium& individual){
    for (unsigned long int i = 0; i < alive.size(); i++)
        if (alive[i] == individual)
            return {true, i};
    return {false, 0};
}

void Cluster::add(Bacterium* individual){
    totalBacteria++;
    totalAliveBacteria++;
    if ( individual->getID() == 0 ) individual->setID( totalBacteria );
    alive.push_back( *individual );
}

void Cluster::omit(Bacterium* individual){
    pair<bool, unsigned long int> isPresentValue = isPresent(*individual);
    if (isPresentValue.first) {
        dead.push_back(alive[isPresentValue.second]);
        totalDeadBacteria++;
        alive.erase(alive.begin() + isPresentValue.second);
        totalAliveBacteria--;
    }
}

void Cluster::step(){} 

void Cluster::updateTemporalResolution(double newResolution){
    Environment::updateTemporalResolution(newResolution);
    Bacterium::updateTemporalResolution(newResolution);
}

void Cluster::run(string filename){
    string mainFile = "../results/" + filename;
    ofstream file(mainFile);
    if (!file.is_open()) throw runtime_error("Could not open file.");

    file << "TimeElapsed,AliveBacteria,TotalBacteria,NetCO2,TotalNutrient,TotalAcetate,"
         << "Normal,Type++,Type+-,Type-+,Type--\n";

    unsigned long int timeStep = 0;
    double timeElapsed = 0.0f;
    double tempres = Bacterium::getTemporalResolution();
    
    const double maxTime = 5000.0; 

    cout << "\033[2J"; 

    while (alive.size() > 0 && timeElapsed < maxTime){
        
        vector<Bacterium> newMembers;
        
        auto it = alive.begin();
        while (it != alive.end()) {
            if (!it->isAlive()) {
                dead.push_back(*it); 
                totalDeadBacteria++;
                totalAliveBacteria--;
                it = alive.erase(it); 
            } else {
                Bacterium offspring;
                it->live(static_cast<Environment*>(this), offspring);
                if (offspring.isAlive()) {
                    newMembers.push_back(offspring);
                }
                ++it;
            }
        }

        for (Bacterium& baby : newMembers) add(&baby);

        diffuse();

        timeStep++;
        timeElapsed = timeStep * tempres; 

        int countNormal = 0, countPP = 0, countPM = 0, countMP = 0, countMM = 0;
        for (const Bacterium& b : alive) {
            if (b.isAlive()) {
                switch (b.type) {
                    case 0: countNormal++; break;
                    case 1: countPP++; break;
                    case 2: countPM++; break;
                    case 3: countMP++; break;
                    case 4: countMM++; break;
                    default: countNormal++; break; 
                }
            }
        }

        double currentNutrient = getNutrientLevel();
        double currentAcetate = getAcetateLevel();
        double currentCO2 = getCO2Level();
        
        file << timeElapsed << "," << alive.size() << "," << totalBacteria << "," 
             << currentCO2 << "," << (long)currentNutrient << "," << (long)currentAcetate << ","
             << countNormal << "," << countPP << "," << countPM << "," 
             << countMP << "," << countMM << "\n";

        if (timeStep % 100 == 0) {
            cout << "\033[H";
            cout << "GROWTH SIMULATION: [ " << timeElapsed << " / " << maxTime << " ]\n";
            cout << "Alive          : " << alive.size() << " (Should be increasing)\n";
            cout << "Nutrients      : " << (long)currentNutrient << "\n";
            cout << "Acetate        : " << (long)currentAcetate << "\n";
            cout << flush;
        }
    }
    file.close();

}
