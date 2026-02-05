#include "Environment.h"
#include <stdexcept>
#include "Random.h"
using namespace std;

Environment::patch::patch() {}


Environment::Environment(int randomiseType, vector<int> rangesValue,
                         double nutrientValue, double acetateValue,
                         double tempres){
  if (rangesValue.size() != 3)
    throw invalid_argument("Error: rangesValue must be a 3-element vector.");

  ranges = rangesValue;

  locale.resize(ranges[0], vector<vector<patch>>(ranges[1],
                vector<patch>(ranges[2])));

  RandomGenerator rangen;

  switch (randomiseType){
    case 0:
      for (int i = 0; i < ranges[0]; i++)
       for (int j = 0; j < ranges[1]; j++)
        for (int k = 0; k < ranges[2]; k++)
        {
          locale[i][j][k].nutrientLevel = nutrientValue;
          totalNutrientLevel += locale[i][j][k].nutrientLevel;
          locale[i][j][k].acetateLevel = acetateValue;
          totalAcetateLevel += locale[i][j][k].acetateLevel;
        }
      break;

    case 1:
      for (int i = 0; i < ranges[0]; i++)
       for (int j = 0; j < ranges[1]; j++)
        for (int k = 0; k < ranges[2]; k++){
          locale[i][j][k].nutrientLevel =
            rangen.Double(0.0f, nutrientValue);
          totalNutrientLevel += locale[i][j][k].nutrientLevel;
          locale[i][j][k].acetateLevel =
            rangen.Double(0.0f, acetateValue);
          totalAcetateLevel += locale[i][j][k].acetateLevel;
        }
      break;

    default:
      throw invalid_argument("Error: Unknown randomiseType.");
  }

  temporalResolution = tempres;
}


void Environment::updateNutrient(const vector<int>& position,
                                 double nutrientChange){
  int i = position[0], j = position[1], k = position[2];

  if (i >= 0 && i < ranges[0] && 
    j >= 0 && j < ranges[1] && 
    k >= 0 && k < ranges[2]){
      locale[i][j][k].nutrientLevel += nutrientChange;
      totalNutrientLevel += nutrientChange;
  }
}
void Environment::updateAcetate(const vector<int>& location, double acetateChange) {
  
    if (location[0] < 0 || location[0] >= ranges[0] ||
        location[1] < 0 || location[1] >= ranges[1] ||
        location[2] < 0 || location[2] >= ranges[2]) {
        return; 
    }

    locale[location[0]][location[1]][location[2]].acetateLevel += acetateChange;
    totalAcetateLevel += acetateChange;
}

void Environment::updateCO2(double CO2Increase){
  CO2Level += CO2Increase;
}

void Environment::updateTemporalResolution(const double tempResNew){
  temporalResolution = tempResNew;
}

vector<int> Environment::getSize() const{
  vector<int> range = {ranges[0], ranges[1], ranges[2]};
  return range;
}

double Environment::getNutrientLevel(const vector<int>& position) const{

  int i = position[0], j = position[1], k = position[2];

  if (
      i >= 0 && i < ranges[0] && 
      j >= 0 && j < ranges[1] && 
      k >= 0 && k < ranges[2]
  ){
      return locale[i][j][k].nutrientLevel;  
  }

  return 0.0f;
}


double Environment::getNutrientLevel() const{
  return totalNutrientLevel;
}


double Environment::getAcetateLevel(const vector<int>& position) const{

  int i = position[0], j = position[1], k = position[2];

  if (i >= 0 && i < ranges[0] && 
      j >= 0 && j < ranges[1] && 
      k >= 0 && k < ranges[2])
  if (i >= 0 && i < ranges[0] && j >= 0 &&
    j < ranges[1] && k >= 0 && k < ranges[2])
  {
    return locale[i][j][k].acetateLevel;
  }

    return 0.0f;
}


double Environment::getAcetateLevel() const{
  return totalAcetateLevel;
}


double Environment::getCO2Level(){
  return CO2Level;
}

double Environment::getTemporalResolution(){
  return temporalResolution;
}



void Environment::diffuse(){
    auto nextLocale = locale;

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

                    if (nx >= 0 && nx < ranges[0] &&
                        ny >= 0 && ny < ranges[1] &&
                        nz >= 0 && nz < ranges[2]) {

                        neighborNutrients += locale[nx][ny][nz].nutrientLevel;
                        neighborAcetate += locale[nx][ny][nz].acetateLevel;
                        validNeighbors++;
                    }
                }

                if (validNeighbors > 0) {
                    double avgNutrient = neighborNutrients / validNeighbors;
                    double avgAcetate = neighborAcetate / validNeighbors;

                    // Diffusion Rate: How fast stuff spreads (0.1 = 10% per step)
                    double diffRate = 0.1;

                    // Apply Diffusion to Nutrients (High -> Low)
                    nextLocale[i][j][k].nutrientLevel += diffRate * (avgNutrient - locale[i][j][k].nutrientLevel);

                    // Apply Diffusion AND Decay to Acetate
                    // Decay Rate: 0.98 means 2% disappears naturally every step
                    double decayedAcetate = locale[i][j][k].acetateLevel * 0.98;
                    nextLocale[i][j][k].acetateLevel = decayedAcetate + diffRate * (avgAcetate - decayedAcetate);
                }
            }
        }
    }

    locale = nextLocale;
}


double Environment::consumeNutrient(const vector<int>& pos, double amount) {
    if (pos[0] < 0 || pos[0] >= ranges[0] ||
        pos[1] < 0 || pos[1] >= ranges[1] ||
        pos[2] < 0 || pos[2] >= ranges[2]) {
        return 0.0;
    }

    double& currentLevel = locale[pos[0]][pos[1]][pos[2]].nutrientLevel;
    
    double actualConsumed = (currentLevel >= amount) ? amount : currentLevel;

    currentLevel -= actualConsumed;
    totalNutrientLevel -= actualConsumed;

    return actualConsumed;
}
