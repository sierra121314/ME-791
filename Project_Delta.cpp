// Project_Delta.cpp : Defines the entry point for the console application.
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
#include <math.h>
#include <limits>
#include <algorithm>

#include "LY_NN.h"

using namespace std;

#define PI 3.1415

int boundary_x_low = 0;
int boundary_y_low = 0;
int boundary_x_high = 100;
int boundary_y_high = 100;

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////   B   O   A   T   /////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
class boat {
public:
	double boat_x;
	double boat_y;
	double goal_x1;
	double goal_y1;
	double goal_x2;
	double goal_y2;
	double start_boat_x;
	double start_boat_y;
	double starting_theta;
	double  starting_w;
	double v = 3; //velocity //set//
	double w = 0; //angular velocity
	double dt = 0.2; //time step //set//
	double theta; //radians
	double T = 5.0; //set//
	double u = 0;
	double fitness;
	void Init();
	void Simulation(ofstream& fout, int n);
	neural_network NN;
	//Evolutionary EA;
};

void boat::Init() { //pass in NN and EA
	/// STARTING POSITION OF BOAT ///
	//start_boat_x = rand() % boundary_x_high;
	//start_boat_y = rand() % boundary_y_high;
	start_boat_x = 6;
	start_boat_y = 2;
	boat_x = start_boat_x;
	boat_y = start_boat_y;

	/// ORIENTATION OF AGENT ///
	double theta_deg = rand() % 360; ///random degree orientation
	starting_theta = theta_deg * PI / 180; /// converts degrees to radians
	//starting_theta = 0;
	theta = starting_theta;

	/// ANGULAR SPEED OF AGENT ///
	starting_w = rand() % 2*PI;
	//starting_w = 0;
	w = starting_w;

	/// GOAL POSITION ///
	//goal_x1 = rand() % boundary_x_high;
	//goal_y1 = rand() % (boundary_y_high-2);
	//goal_x2 = goal_x1;
	//goal_y2 = goal_y1 - 2;
	goal_x1 = 10; //testing
	goal_y1 = 1; //testing
	goal_x2 = 10; //testing
	goal_y2 = 3; //testing

}

void boat::Simulation(ofstream& fout, int s) {
	//pass in weights
	double y;
	double m;
	double b;
	double boat_x1;
	double boat_y1;
	double time;
	double distance;
	double distance_x;
	double distance_y;
	
	// INITIALIZE STARTING POSITIONS //
	boat_x = start_boat_x;
	boat_y = start_boat_y;
	w = starting_w;
	//cout << w << endl;
	theta = starting_theta;
	distance = 0;

	for (int i = 0; i < 1000; i++) {

		// Get input vector for NN - x,y,w,theta
		vector<double> state;
		state.push_back(boat_x);
		state.push_back(boat_y);
		NN.set_vector_input(state);
		//Give to NN
		
		cout << boat_x << ',' << boat_y << endl;

		// GET VALUE OF U FROM NN
		NN.execute();
		u = NN.get_output(0);

		/// CALCULATE X,Y,THETA,W ///
		boat_x1 = boat_x + v*cos(theta)*dt;
		boat_y1 = boat_y + v*sin(theta)*dt;
		theta = theta + w*dt; 
		w = w + (u - w)*dt / T; 
		
		/// CALCULATIONS FOR INTERCEPT ///
		m = (boat_y1 - boat_y) / (boat_x1 - boat_x); ///slope
		b = boat_y1 - m*boat_x1; /// y intercept
		y = m*goal_x1+b; ///equation of a line

		/// UPDATE NEW X,Y, VALUES ///
		boat_x = boat_x1; ///setting the new x value
		boat_y = boat_y1; ///setting the new y value
		fout << boat_x << ',' << boat_y << ',' << theta << ',' << w << endl;

		/// CALCULATE DISTANCE TO GOAL /// 
		distance_x = pow(goal_x1 - boat_x, 2);
		distance_y = pow(goal_y1 - boat_y, 2);
		cout << "d_x   " << distance_x << '\t' << "d_y   " << distance_y << endl;
		distance = distance + sqrt(distance_x + distance_y);

		/// CONDITIONS TO QUIT THE LOOP ////
		if (boat_x < boundary_x_low || boat_x > boundary_x_high || boat_y < boundary_y_low || boat_y > boundary_y_high) {
			break;
		}
		cout << "boat within boundary" << endl;
		
		if (boat_x1 < boat_x) {		//If x1 is to the left of x2
			if (boat_x1 <= goal_x1 && boat_x >= goal_x2) {	//If they are on either side of the goal
				if (y >= goal_y1 && y <= goal_y2) {
					break;
				}
			}
		}
		else {		//If x2 is to the left of x1
			if (boat_x <= goal_x1 && boat_x1 >= goal_x2) {	//If they are on either side of the goal
				if (y >= goal_y1 && y <= goal_y2) {
					break;
				}
			}
		}
		cout << "boat not close to goal" << endl;

		/// CALCULATIONS FOR TIME FOR FITNESS //
		time = dt*i;
		
	} //for loop

	////////// EXITING COORDINATES ////////
	cout << boat_x << ',' << boat_y << endl;

	/// CALCULATE THE FITNESS - uses distance and time // MR_4 //
	fitness = distance*time; //overall distance it took to get to the goal
	//cout << "fitness" << fitness << endl;
}

//////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////   N E U R A L      N E T W O R K  ////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
class NN {
public:
	double Neural_Network(double u);

};


double NN::Neural_Network(double u) { //returns control signal to the simulation
	//calculates based on the weights given to it based on the EA
	return u;
}


//////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////   EVOLUTIONARY ALGORITHM  ////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
class Evolutionary {
public:

	vector <vector<double>> weights;
};

int main()
{
	
	int MAX_GENERATIONS = 300;
	int pop_size = 100;
	srand(time(NULL));

	//Evolutionary EA;
	
	/// SET UP NEURAL NETWORK ///
	neural_network NN;
	vector<double> vi;
	vector<double> weights; 
	NN.setup(1, 5, 1); ///1 input, 5 hidden, 1 output (Bias units hidden from user)

	NN.set_in_min_max(0.0, 5.0); /// limits of input for normalization
	NN.set_out_min_max(-5.0, 30.0); /// limits of outputs for normalization
	NN.set_vector_input(vi); /// vector of inputs


	/// DEFINE STARTING POSITION AND GOAL POSITION ///
	boat B;
	B.Init(); 

	/// INITIALIZE POLICIES ///
	vector<policy> population;
	for (int p = 0; p < pop_size; p++) {
		policy A;
		A.init(NN.get_number_of_weights());
		population.push_back(A);
	}
	assert(population.size() == pop_size);

	////////// START SIMULATION ///////////////
	ofstream fout;
	/// MR_3 ///
	fout.open("Movement.csv", ofstream::out | ofstream::trunc);
	fout << "Coordinates of Boat for each time step" << "\n";

	for (int g = 0; g < MAX_GENERATIONS; g++)	{
		//for (int n = 0; n < EA.weights.size(); n++) {
		for (int s = 0; s < 15; s++) {
			fout << "Sim" << s << "\n";
			NN.set_weights(population.at(s).weights, true);
			
			B.Simulation(fout,s);

		}	
		// UPDATE EA WITH FITNESS
		// EA - DOWNSELECT WITH GIVEN FITNESS
		// EA - MUTATE and repopulate WEIGHTS
		
		
	}
	//////// MR_2 ///////////
	//assert(B.boat_y <= B.goal_y2 && B.boat_y >= B.goal_y1 && B.boat_x <= (B.goal_x2 + .05*B.goal_x2) && B.boat_x >= (B.goal_x2 - .05*B.goal_x2));
	cout << "Boat passed through goal" << endl;

	fout.close();

	
	int input;
	cin >> input;
    return 0;
}

