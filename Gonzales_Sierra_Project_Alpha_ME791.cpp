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

using namespace std;

// Global Variable
int num_arms = 1;  //n
int num_plays = 1;

class MAB {
public:
	//payouts(i)are dictated by a normal distribution-N(mu,sigma)
	//randomly drawn mu and sigma values
	double mu; //mean
	double sig; //standard deviation
	int arm;
	void Randomize();
	void Monies();
	void update_arm_strength();
};

double generateGaussianNoise(mu, sig) {
	const double epsilon = std::numeric_limits <double>::minstd_rand();
	const 

}


void MAB::Randomize() {
	mu = (((double)rand() / RAND_MAX) - 0.5) * 50;
	sig = (((double)rand() / RAND_MAX) - 0.5) * 50;
};


void MAB::Monies() { //Reward


};

void MAB::update_arm_strength() { //updating the value of payout for each arm

}

void TestA() {
	//The average of many pulls from a single arm converges to that arm's mu value


};

void TestB() {
	//When one arge has mu and sigm values that make it clearly the best choice,
	//the action value learner will have the highest likelihood of choosing this arm after many pulls
};

int main()
{
	srand(time(NULL));


    return 0;
}

