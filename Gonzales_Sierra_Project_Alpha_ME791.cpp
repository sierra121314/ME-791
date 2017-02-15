// Gonzales_Sierra_Project_Alpha_ME791.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <assert.h>
#include <random>
#include <fstream>
#include <numeric>
#include <time.h>
#include <cstdlib>
#include <cmath>
#include <limits>

using namespace std;

// Global Variable
int num_arms = 1;  //n
int num_plays = 1;
int epsilon = 0.1; //greedy value

class MAB {
public:
	//payouts(i)are dictated by a normal distribution-N(mu,sigma)
	//randomly drawn mu and sigma values
	double mu; //mean
	double sigma; //standard deviation
	
	MAB(); //creates a random mu and sigm //constructor
	double Pull(); //generate a number if you pull it
	
	};

class Q_learner {
public:
	Q_learner(); //constructor
	double alpha;
	vector<double> val; //value of each pull for an arm
	double epsilon;  //greedy value
	void Decide(vector<MAB>);
	
	
};

double MAB::Pull() { //creates normal distribution, weighted random number
	const double epsilon = std::numeric_limits<double>::min();
	const double two_pi = 2.0*3.14159265358979323846;

	static double z0, z1;
	static bool generate;
	generate = !generate;

	if (!generate)
		return z1 * sigma + mu;

	double u1, u2;
	do
	{
		u1 = rand() * (1.0 / RAND_MAX);
		u2 = rand() * (1.0 / RAND_MAX);
	} while (u1 <= epsilon);

	z0 = sqrt(-2.0 * log(u1)) * cos(two_pi * u2);
	z1 = sqrt(-2.0 * log(u1)) * sin(two_pi * u2);
	return z0 * sigma + mu;
}


void Q_learner::Decide(vector<MAB> M) {
	double N;
	//for loop with some if shit to determine if we want to do best value or random pull
	int j;
	for (int i = 0; i < num_plays; i++) { //Exploration vs Exploitation
		j = 0;
		double b = ((double)rand() / RAND_MAX);
		if (epsilon <= b) {
			// pulls randomly
			// chooses an arm at random that fits within the number of arms
			j = rand() % num_arms;
			
		}
		else {
			//try to find which arm has the highest reward
			
			for (int k = 0; k < num_arms; k++) {
				if (val[j] < val[k]) {
					j = k; //updates the value at j so that equals the highest value at k
				}
			}
		}

		N = M[j].Pull(); //pulls the decided arm
		val[j] = N*alpha + val[j]*(1 - alpha); //new value plus old val //updates value
	}

}


MAB::MAB() {
	mu = (((double)rand() / RAND_MAX) - 0.5) * 50; //mean somewhere between -25 and 25
	sigma = (((double)rand() / RAND_MAX) - 0.5) * 2;
};

Q_learner::Q_learner(){
	for (int i = 0; i < num_arms; i++) {
		val.push_back(0); // initializes each arm value as zero
	}
	alpha = 0.1;
}


void TestA() {
	//The average of many pulls from a single arm converges to that arm's mu value
	//for //all the values
		//take the mean

	//if //the mean is within a certain range of mu assert something
};

void TestB() {
	//When one arge has mu and sigm values that make it clearly the best choice,
	//the action value learner will have the highest likelihood of choosing this arm after many pulls
};

int main()
{
	srand(time(NULL));
	//make MABs
	//Make Q_learner
	MAB Multi_arm(); // picks numbers for normal distribution
	Q_learner Q();
	

	//Call decide
	Decide();
	//export data
	//make sure MAB is a list
	

	


    return 0;
}

