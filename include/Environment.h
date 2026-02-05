#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <vector>
using std::vector;

class Environment
{

protected:
    struct patch
    {
        double 
            nutrientLevel = 0,          // amount of nutrient in a patch    
            acetateLevel = 0;           // amount of acetate in a patch

        patch();

    };

    vector<vector<vector<patch>>> locale; // main 3d distribution of patches

    vector<vector<vector<patch>>> buffer; 
		// a static buffer value to store a copy of the locale
    vector<int> ranges; 

    double CO2Level = 0.0f;
    long double totalNutrientLevel = 0.0f; 
    long double totalAcetateLevel = 0.0f;
    double temporalResolution = 1.0f;         // units - seconds
    double diffusionConstant = 1.0f;


public:

    // Initialiser
    Environment( int randomiseType = 0, vector<int> = {50,50,50},
                 double nutrientValue = 1.0f, double acetateValue = 0.0f, 
                 double tempres = 1.0f);


    // Mutators
    void updateNutrient(const vector<int>& location, double nutrientChange);
    // In src/Environment.cpp

    void updateAcetate(const vector<int>& location, double acetateChange);
    void updateCO2(double CO2Increase);
    void updateTemporalResolution(const double tempresNew);
    void diffuse();


    // Accessors
    // returns size of Environment
    vector<int> getSize() const;
    // nutrient level of patch
    double getNutrientLevel(const vector<int>& ) const;
    // nutrient level of entire environment
    double getNutrientLevel() const;
    // nutrient level of patch
    double getAcetateLevel(const vector<int>& ) const;
    // nutrient level of whole environment
    double getAcetateLevel() const;
    double getCO2Level();
    double getTemporalResolution();
    // In include/Environment.h
    // In include/Environment.h
    double consumeNutrient(const vector<int>& pos, double amount);
};

#endif
