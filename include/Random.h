#include <vector>
#include <random>

#ifndef RANDOM_H
#define RANDOM_H


using namespace std;


class RandomGenerator {
public:
    // Constructor initializes the random number generator
    RandomGenerator();
    // Method to generate a random double in the range [min, max]
    double Double(double , double );
    // Overloaded method to generate a random number from 0 to max 
    double Double(double max);

	// Method to generate a random integer in the range [min, max]
    int Int(int , int ); 
    // Overloaded method to generate a random number from 0 to max
    int Int(int max);
 
    // These functions use mercenne twister
    // Method to generate a random double in the range [min, max]
    double DoubleMT(double , double );
    // Overloaded method to generate a random number from 0 to max
    double DoubleMT(double max);
    
    // Method to generate a random integer in the range [min, max]
    int IntMT(int , int ); 
    // Overloaded method to generate a random number from 0 to max
    int IntMT(int max);
	    
	vector<vector<vector<double>>> generate3DVector
	    (vector<int> dim, int, int );


private:
    mt19937 mt; // Mersenne Twister engine
};

#endif
