#include "Random.h"
#include <cstdlib>    // For rand() and srand()
#include <ctime>      // For time()

RandomGenerator::RandomGenerator()
{
    // Seed the random number generator with the current time
    unsigned int seed = static_cast<unsigned int>(time(nullptr));
    srand(seed);
    mt.seed(seed); // Mersenne Twister engine
}


// Method to generate a random double in the range [min, max]
double RandomGenerator::Double(double min, double max)
{
    double fraction = static_cast<double>(rand()) / RAND_MAX;
    return min + fraction * (max - min);
}


// Overloaded method to generate a random number from 0 to max 
double RandomGenerator::Double(double max)
{
    double fraction = static_cast<double>(rand()) / RAND_MAX;
    return fraction * max;
}


// Method to generate a random integer in the range [min, max]
int RandomGenerator::Int(int min, int max)
{
    return min + rand() % (max - min + 1);
}


// Overloaded method to generate a random number from 0 to max
int RandomGenerator::Int(int max)
{
    return rand() % (max + 1);
}

// Method to generate a random double in the range [min, max]
double RandomGenerator::DoubleMT(double min, double max) 
{
    uniform_real_distribution<double> distribution(min, max);
    return distribution(mt);
}


// Overloaded method to generate a random number from 0 to max 
double RandomGenerator::DoubleMT(double max) 
{
    uniform_real_distribution<double> distribution(0.0f, max);
    return distribution(mt);
}


// Method to generate a random integer in the range [min, max]
int RandomGenerator::IntMT(int min, int max) 
{
    uniform_int_distribution<int> distribution(min, max);
    return distribution(mt);
}


// Overloaded method to generate a random number from 0 to max
int RandomGenerator::IntMT(int max) 
{
    uniform_int_distribution<int> distribution(0, max);
    return distribution(mt);
}
