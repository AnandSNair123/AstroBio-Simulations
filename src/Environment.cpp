#include "Environment.h"
#include <stdexcept>
#include "Random.h"
#include <iostream> 

using namespace std;

Environment::patch::patch() {}

Environment::Environment(int x, int y, int z) {
    if (x <= 0 || y <= 0 || z <= 0) throw invalid_argument("Dimensions must be positive.");
    ranges = {x, y, z};
    locale.resize(x);
    for (int i = 0; i < x; ++i) {
        locale[i].resize(y);
        for (int j = 0; j < y; ++j) {
            locale[i][j].resize(z);
            for (int k = 0; k < z; ++k) {
                // High Food Reserve to last 5 mins
                locale[i][j][k].nutrientLevel = 5000.0; 
                locale[i][j][k].acetateLevel = 0.0;
                
                // Rich Zones
                if (i % 50 == 0 && j % 50 == 0) locale[i][j][k].nutrientLevel = 20000.0;
                
                totalNutrientLevel += locale[i][j][k].nutrientLevel;
            }
        }
    }
}

Environment::Environment(int randomiseType, vector<int> rangesValue,
                         double nutrientValue, double acetateValue, double tempres){
  if (rangesValue.size() != 3) throw invalid_argument("Error: rangesValue must be 3-element.");
  ranges = rangesValue;
  locale.resize(ranges[0], vector<vector<patch>>(ranges[1], vector<patch>(ranges[2])));
  temporalResolution = tempres;
}

bool Environment::checkBounds(int x, int y, int z) {
    return (x >= 0 && x < ranges[0] && y >= 0 && y < ranges[1] && z >= 0 && z < ranges[2]);
}

void Environment::updateNutrient(const vector<int>& position, double nutrientChange){
  if (checkBounds(position[0], position[1], position[2])){
      locale[position[0]][position[1]][position[2]].nutrientLevel += nutrientChange;
  }
}

void Environment::updateAcetate(const vector<int>& location, double acetateChange) {
    if (checkBounds(location[0], location[1], location[2])) {
        locale[location[0]][location[1]][location[2]].acetateLevel += acetateChange;
    }
}

void Environment::updateCO2(double CO2Increase){ CO2Level += CO2Increase; }
void Environment::updateTemporalResolution(const double tempResNew){ temporalResolution = tempResNew; }
vector<int> Environment::getSize() const{ return ranges; }

double Environment::getNutrientLevel(const vector<int>& position) const{
  if (position.size() >= 3) {
      int i = position[0], j = position[1], k = position[2];
      if (i >= 0 && i < ranges[0] && j >= 0 && j < ranges[1] && k >= 0 && k < ranges[2])
          return locale[i][j][k].nutrientLevel;
  }
  return 0.0f; 
}

double Environment::getNutrientLevel() const{ return totalNutrientLevel; }

double Environment::getAcetateLevel(const vector<int>& position) const{
  if (position.size() >= 3) {
      int i = position[0], j = position[1], k = position[2];
      if (i >= 0 && i < ranges[0] && j >= 0 && j < ranges[1] && k >= 0 && k < ranges[2])
          return locale[i][j][k].acetateLevel;
  }
  return 0.0f;
}

double Environment::getAcetateLevel() const{ return totalAcetateLevel; }
double Environment::getCO2Level(){ return CO2Level; }
double Environment::getTemporalResolution(){ return temporalResolution; }

// --- CLEAN DIFFUSE: STANDARD PHYSICS ---
void Environment::diffuse(){
    auto nextLocale = locale;
    double calculatedTotalNutrient = 0.0;
    double calculatedTotalAcetate = 0.0;

    int dx[] = {1, -1, 0, 0, 0, 0};
    int dy[] = {0, 0, 1, -1, 0, 0};
    int dz[] = {0, 0, 0, 0, 1, -1};

    for (int i = 0; i < ranges[0]; ++i) {
        for (int j = 0; j < ranges[1]; ++j) {
            for (int k = 0; k < ranges[2]; ++k) {

                double neighborNutrients = 0.0;
                double neighborAcetate = 0.0;
                int validNeighbors = 0;

                for (int d = 0; d < 6; d++) {
                    int nx = i + dx[d]; 
                    int ny = j + dy[d];
                    int nz = k + dz[d];

                    if (checkBounds(nx, ny, nz)) {
                        neighborNutrients += locale[nx][ny][nz].nutrientLevel;
                        neighborAcetate += locale[nx][ny][nz].acetateLevel;
                        validNeighbors++;
                    }
                }

                if (validNeighbors > 0) {
                    double avgNutrient = neighborNutrients / validNeighbors;
                    double avgAcetate = neighborAcetate / validNeighbors;
                    double diffRate = 0.15; 

                    // Standard Diffusion Logic
                    nextLocale[i][j][k].nutrientLevel += diffRate * (avgNutrient - locale[i][j][k].nutrientLevel);
                    nextLocale[i][j][k].acetateLevel += diffRate * (avgAcetate - locale[i][j][k].acetateLevel);
                }
                
                calculatedTotalNutrient += nextLocale[i][j][k].nutrientLevel;
                calculatedTotalAcetate += nextLocale[i][j][k].acetateLevel;
            }
        }
    }
    locale = nextLocale;
    totalNutrientLevel = calculatedTotalNutrient;
    totalAcetateLevel = calculatedTotalAcetate;
}

double Environment::consumeNutrient(const vector<int>& pos, double amount) {
    if (!checkBounds(pos[0], pos[1], pos[2])) return 0.0;
    double& currentLevel = locale[pos[0]][pos[1]][pos[2]].nutrientLevel;
    double actualConsumed = (currentLevel >= amount) ? amount : currentLevel;
    currentLevel -= actualConsumed;
    return actualConsumed;
}