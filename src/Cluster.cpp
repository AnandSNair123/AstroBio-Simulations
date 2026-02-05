#include <iostream>
#include <fstream>
#include <stdexcept>
#include <iomanip>
#include <string>
using namespace std;

#include "Cluster.h"
#include "Random.h"

Cluster::Cluster(int numBacteria, int randomiseType, double energyValue){
    RandomGenerator ranGen;

    switch (randomiseType)
    {
        case 1:
            for (int i = 0; i < numBacteria; ++i){
                vector<int> randomPosition = { ranGen.Int(0, ranges[0]), 
                                               ranGen.Int(0, ranges[1]), 
                                               ranGen.Int(0, ranges[2]) };
                double randomEnergy = ranGen.Double(0, energyValue);
                
                Bacterium* individual = new Bacterium(randomPosition, randomEnergy);
                add(individual);
            }
        default:
            break;
    }
}

pair<bool, unsigned long int> Cluster::isPresent(Bacterium individual){
    for (unsigned long int i = 0; i < alive.size(); i++)
        if (alive[i] == individual)
            return {true, i};
    return {false, 0};
}

void Cluster::add(Bacterium* individual){
    totalBacteria++;
    totalAliveBacteria++;

    if ( individual->getID() == 0 )
        individual->setID( totalBacteria );
    else 
        cout << "Warning : stray bacteria added to cluster" << endl;
    alive.push_back( *individual );
}

void Cluster::omit(Bacterium* individual){
    pair<bool, unsigned long int> isPresentValue = isPresent(*individual);

    if (!isPresentValue.first)
        throw runtime_error("Value not found in the vector");
    else{
        dead.push_back(alive[isPresentValue.second]);
        totalDeadBacteria++;
        alive.erase(alive.begin() + isPresentValue.second);
        totalAliveBacteria--;
    }
}

void Cluster::step(){
    Bacterium* offspring = new Bacterium();
    vector<Bacterium> newMembers;
    vector<Bacterium> deadMembers;
    bool aliveBefore;

    for (Bacterium& individual : alive){
        aliveBefore = individual.isAlive();
        individual.live(static_cast<Environment*>(this), *offspring);

        if (offspring->isAlive() == 1){
            newMembers.push_back(*offspring);
            offspring = new Bacterium();
        }

        if (aliveBefore && !individual.isAlive()){
            deadMembers.push_back(individual);
        }
    }

    diffuse(); 

    for (Bacterium& individual : newMembers)
        add(&individual);
    for (Bacterium& individual : deadMembers)
        omit(&individual);

    delete offspring; 
}

void Cluster::updateTemporalResolution(double newResolution){
    Environment::updateTemporalResolution(newResolution);
    Bacterium::updateTemporalResolution(newResolution);
}

void Cluster::run(string filename){
    string mainFile = "../results/" + filename;
    ofstream file(mainFile);

    string visFile = "../results/vis_data.csv";
    ofstream vfile(visFile);

    if (!file.is_open() || !vfile.is_open()){
        throw runtime_error("Could not open files for writing.");
    }

    file << "TimeElapsed,AliveBacteria,TotalBacteria,NetCO2,TotalNutrient,TotalAcetate\n";

    unsigned long int timeStep = 0;
    double timeElapsed = 0.0f;
    double tempres = Bacterium::getTemporalResolution();
    
    const int visFrequency = 5; 
    const double maxTime = 2000.0;

    cout << "\033[2J"; 

    while (totalAliveBacteria > 0 && timeElapsed < maxTime){
        step(); 
        timeStep++;
        timeElapsed = timeStep * tempres;

        double currentCO2 = getCO2Level();
        double currentNutrient = getNutrientLevel();
        double currentAcetate = getAcetateLevel();
        file << timeElapsed << "," << totalAliveBacteria << "," << totalBacteria << "," 
             << currentCO2 << "," << currentNutrient << "," << currentAcetate << "\n";

        if (timeStep % visFrequency == 0) {
            int zSlice = 25;
            for(int x=0; x<ranges[0]; x++) {
                for(int y=0; y<ranges[1]; y++) {
                    double nut = locale[x][y][zSlice].nutrientLevel;
                    double ace = locale[x][y][zSlice].acetateLevel;
                    
                    if(nut > 1.0) vfile << timeStep << ",0," << x << "," << y << "," << nut << "\n";
                    if(ace > 1.0) vfile << timeStep << ",1," << x << "," << y << "," << ace << "\n";
                }
            }
            for (Bacterium& b : alive) {
                vector<int> pos = b.getPosition(); 
                vfile << timeStep << ",2," << pos[0] << "," << pos[1] << ",1\n";
            }
            for (Bacterium& b : dead) {
                vector<int> pos = b.getPosition();
                vfile << timeStep << ",3," << pos[0] << "," << pos[1] << ",1\n";
            }
        }
        
        cout << "\033[H";
        cout << "Simulation Data:\n================\n";
        cout << fixed << setprecision(2);
        cout << "Time Elapsed   : " << timeElapsed << " / " << maxTime << "\n";
        cout << "Alive Bacteria : " << totalAliveBacteria << "\n";
        cout << "Total Bacteria : " << alive.size()+dead.size() << "\n";
        cout << "Net CO2 Level  : " << currentCO2 << "\n";
        cout << "Total Nutrient : " << currentNutrient << "\n";
        cout << "Total Acetate  : " << currentAcetate << "\n";
        cout << flush;
    }

    file.close();
    vfile.close();
}
