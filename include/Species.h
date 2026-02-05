#ifndef SPECIES_H
#define SPECIES_H

#include <vector>
#include "Environment.h"
using std::vector;

class Bacterium
{
private:
    unsigned long int bacteriaID = 0;

protected:
    static double temporalResolution; 
    bool alive = 1;
    
    // --- CRITICAL FIXES FOR GROWTH CURVE ---
    double 
        minEnergy = 0,
        maxEnergy = 1000.0f,        // Cap increased so they can store more fat
        
        // 1. LOWER METABOLISM (Was 50.0 -> Now 2.0)
        // This stops them from dying instantly. They can now survive 100+ steps without food.
        livingEnergy = 2.0f,
        
        // 2. EASIER REPRODUCTION (Was 300.0 -> Now 150.0)
        // They will multiply much faster now.
        reproductionEnergy = 150.0f,
        
        acidicLimit = 20.0f,
        proximity = 3.0f,
        
        // 3. BETTER EATING (Was 10.0 -> Now 20.0)
        // Each bite of food is twice as nutritious.
        energyPerNutrient = 20.0f,  
        
        CO2PerEnergy = 10.0f,
        rateOfConsumption = 1.0f,
        movementSpeed = 1.0f;

    vector<int> position = {0,0,0};
    double energy = 0.0f;
    double getAcetateNearby(Environment* surroundings) const;

public:
    int type = 0;
    Bacterium();
    Bacterium(const vector<int>& pos, double const energy_lvl = 300.0f);
    
    void setID(unsigned long int);
    unsigned long int getID();

    void move( Environment* );
    void eat( Environment* );
    void reproduce( Environment* , Bacterium& );
    void live( Environment* , Bacterium& );
    void die();
    void adapt( Environment* );
    
    static void updateTemporalResolution(const double tempresNew);
    static double getTemporalResolution();

    double getEnergy();
    bool canLive( Environment* ) const;
    bool isAlive() const;
    bool operator==(const Bacterium&) const;
    vector<int> getPosition() const { return position; }
};

#endif