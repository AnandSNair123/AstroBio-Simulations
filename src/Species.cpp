#include <cmath>
#include <stdexcept>
#include <algorithm> 
#include "Species.h"
#include "Random.h"

using namespace std;

double Bacterium::temporalResolution = 1.0f;
RandomGenerator ranGen;

void Bacterium::setID(unsigned long int id){ bacteriaID = id; }
unsigned long int Bacterium::getID(){ return bacteriaID; }
void Bacterium::updateTemporalResolution(double resolution) { temporalResolution = resolution; }
double Bacterium::getTemporalResolution() { return temporalResolution; }

double Bacterium::getAcetateNearby(Environment* env) const {
    double totalAcetate = 0.0f;
    const vector<int> size = env->getSize();
    for (int x = max(0, position[0] - (int)proximity);
         x <= min(size[0] - 1, position[0] + (int)proximity); ++x)
      for (int y = max(0, position[1] - (int)proximity);
           y <= min(size[1] - 1, position[1] + (int)proximity); ++y)
        for (int z = max(0, position[2] - (int)proximity);
             z <= min(size[2] - 1, position[2] + (int)proximity); ++z)
        {
            double distance = sqrt(pow(x - position[0], 2) + pow(y - position[1], 2) + pow(z - position[2], 2));
            if (distance <= proximity) totalAcetate += env->getAcetateLevel({x, y, z});
        }
    return totalAcetate;
}

Bacterium::Bacterium(){ energy = 0.0f; alive = 0; updateTemporalResolution( 1.0f ); }
Bacterium::Bacterium( const vector<int>& pos, double const energy_lvl){
    alive = 1; position = pos; energy = ranGen.Double(energy_lvl);
}
bool Bacterium::operator==(const Bacterium& other) const{ return bacteriaID == other.bacteriaID; }

// --- CLEAN REPRODUCE: CLONING ONLY ---
void Bacterium::reproduce( Environment* surroundings , Bacterium& offspring)
{
    if (energy > reproductionEnergy) {
        // Perfect Clone: No Mutation Logic here anymore.
        offspring = Bacterium(position, energy / 2.0);
        offspring.type = this->type; 
        offspring.livingEnergy = this->livingEnergy;
        offspring.acidicLimit = this->acidicLimit;

        energy /= 2.0;
    } else {
        offspring = Bacterium();
    }
}

void Bacterium::eat(Environment* surroundings) {
    double totalConsumed = 0.0;
    double centerRate = rateOfConsumption * 0.5;
    totalConsumed += surroundings->consumeNutrient(position, centerRate);

    double neighborRate = (rateOfConsumption * 0.5) / 6.0;
    int dx[] = {1, -1, 0, 0, 0, 0};
    int dy[] = {0, 0, 1, -1, 0, 0};
    int dz[] = {0, 0, 0, 0, 1, -1};

    for (int i = 0; i < 6; i++) {
        vector<int> neighborPos = { position[0] + dx[i], position[1] + dy[i], position[2] + dz[i] };
        totalConsumed += surroundings->consumeNutrient(neighborPos, neighborRate);
    }
    energy += totalConsumed * energyPerNutrient;
}

void Bacterium::move(Environment* surroundings){
    const int range = movementSpeed;
    position[0] += ranGen.Int(-range, range);
    position[1] += ranGen.Int(-range, range);
    position[2] += ranGen.Int(-range, range);

    vector<int> limits = surroundings->getSize();
    const int max_x = limits[0]; const int max_y = limits[1]; const int max_z = limits[2];

    if (position[0] < 0) position[0] = -position[0];
    else if (position[0] >= max_x) position[0] = max_x - 1 - (position[0] - max_x);
    if (position[1] < 0) position[1] = -position[1];
    else if (position[1] >= max_y) position[1] = max_y - 1 - (position[1] - max_y);
    if (position[2] < 0) position[2] = -position[2];
    else if (position[2] >= max_z) position[2] = max_z - 1 - (position[2] - max_z);
}

void Bacterium::die(){ alive = 0; }
void Bacterium::adapt( Environment* surroundings ){};
double Bacterium::getEnergy(){ return energy; }

bool Bacterium::canLive(Environment* surroundings) const {
    if (energy <= minEnergy) return 0;
    if (getAcetateNearby(surroundings) > acidicLimit) return 0; 
    return 1;
}

bool Bacterium::isAlive() const{ return alive; }

void Bacterium::live(Environment* surroundings, Bacterium& offspring) {
    move(surroundings);
    eat(surroundings);
    reproduce(surroundings, offspring);
    
    // Standard Metabolism
    energy -= (livingEnergy * 0.05); 
    
    surroundings->updateCO2(livingEnergy * CO2PerEnergy);
    surroundings->updateAcetate(position, 5.0); // Release waste
    
    if (!canLive(surroundings)) die();
}