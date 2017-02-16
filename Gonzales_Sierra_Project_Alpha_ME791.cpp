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
int num_arms = 2;  //n
int num_plays = 100;
double epsilon = 0.1; //greedy value

class MAB {
public:
	//payouts(i)are dictated by a normal distribution-N(mu,sigma)
	//randomly drawn mu and sigma values
	double mu; //mean
	double sigma; //standard deviation
	
	void Init(); //creates a random mu and sigm //constructor
	double Pull(); //generate a number if you pull it
	
	};

class Q_learner { 
public:
	Q_learner(); //constructor
	double alpha;
	vector<double> val; //value of each pull for an arm
	double Decide(vector<MAB>);
	void TestB(vector<MAB>);
	void Learning_Curve(vector<MAB>);
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


double Q_learner::Decide(vector<MAB> M) { //Help from Bryant Clouse and Honi Ahmadiam-Tehrani
	double N;
	//for loop with some if sh** to determine if we want to do best value or random pull
	int j;
	//export data
	ofstream fout;
	fout.open("value_log.csv", ofstream::out | ofstream::trunc);
	fout << "Rewards per play" << "\n";
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
		for (int i = 0; i < num_arms; i++) {
			fout << i << "," << val[i] << "\n";
		}
	}
	fout.close();
	
}


void MAB::Init() { //Initializer
	mu = (((double)rand() / RAND_MAX) - 0.5) * 50; //mean somewhere between -25 and 25
	sigma = (((double)rand() / RAND_MAX) - 0.5) * 2;
};

Q_learner::Q_learner(){ //initializer
	for (int i = 0; i < num_arms; i++) {
		val.push_back(0); // initializes each arm value as zero
	}
	alpha = 0.1;
}


void Q_learner::Learning_Curve(vector<MAB> M) {
	//The average of many pulls from a single arm converges to that arm's mu value
	double x;
	double R;
	R = 0;
	//M.Init();
	ofstream fout;
	fout.open("Learning_Curve.csv", ofstream::out | ofstream::trunc);
	fout << "Pulls per Average Reward for 30 statitical runs" << "\n";
	for (int j = 0; j < 30; j++) { //30 statistical runs
		fout << "Test " << j << "\n";
		for (int k = 1; k < num_plays; k++) {
			
			x = Decide(M);
			R = R*(k - 1) + x; // takes the old reward and multiplies it with the last number of pulls then adds the new reward 
			fout << k << "," << R << "\n";
		}
		fout << "\t";
		//call decide
		
	}
	
	
	fout.close();
	
};

void TestA() {
	//The average of many pulls from a single arm converges to that arm's mu value
	//want to see if the final value/reward is close to the mean 
	MAB H; //Single arm
	double x;
	double R;
	x = 0;
	R = 0;
	H.Init();
	ofstream fout;
	fout.open("TestA.csv", ofstream::out | ofstream::trunc);
	fout << "Comparing last value with mean of that arm" << "\n";
	for (int i = 1; i < 3000; i++) { //more the better
		x=H.Pull();

		R = x*0.1 + R * (1 - 0.1);
		fout << i << "," << R << "\n";
	}
	cout << "Comparing mean and Last reward"<< "\t" << H.mu << "\t";
	cout << R << "\n";
	
	assert(abs(R) < 1.05*abs(H.mu) && abs(R) > 0.95*abs(H.mu));
	
	fout.close();
	//if //the mean is within a certain range of mu assert something

}


void Q_learner::TestB(vector<MAB> M) {
	//When one arge has mu and sigm values that make it clearly the best choice,
	//the action value learner will have the highest likelihood of choosing this arm after many pulls
	double N;
	//for loop with some if sh** to determine if we want to do best value or random pull
	int j;
	//export data
	ofstream fout;
	fout.open("value_log.csv", ofstream::out | ofstream::trunc);
	fout << "Rewards per play" << "\n";
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
		val[j] = N*alpha + val[j] * (1 - alpha); //new value plus old val //updates value
		for (int i = 0; i < num_arms; i++) {
			fout << i << "," << val[i] << "\n";
		}
	}
	fout.close();
	

};

int main()
{
	srand(time(NULL));
	vector<MAB> M;
	double val;
	
	for (int i = 0; i < num_arms; i++) { //make MABs
		//create arm
		MAB arm; // picks numbers for normal distribution
		//set its mean and std dev
		arm.Init(); //run the function for the object arm
		// push it into vector M
		M.push_back(arm); // put that arm into the vector M

	}
	
	//Make Q_learner
	Q_learner Q_learn;
	//Call decide
	Q_learn.Decide(M); // vector M which is the created arms, and plugs them into the Q-learner

	Q_learn.Learning_Curve(M);
	TestA();
	Q_learn.TestB(M);
	
	int input;
	cin >> input;

    return 0;
}
