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

////////////////////////////////////////////////////////////////////////////
///////////////////////////   Policies  ////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

class Policies {
public:
	//MR_1:  initialize a population of policies - associated with a fitness
	//fitness //MR_2::  distance for the entire policy, minimal
	//
	int fitness = 0;
	vector<int> policies; //vectors of integers of the index for each city
	void init_policy(int num_weights); //initialize one policy

};

void Policies::init_policy(int num_weights) {
	for (int p = 0; p < num_weights; p++) {
		//cout << "Order " << p << endl;
		policies.push_back(p);
	}
	//By shuffling only after the first city, we ensure we start in the same place each time
	random_shuffle(policies.begin() + 1, policies.end()); //LR_5//
	assert(*policies.begin() == 0); //LR_5
									//check to see if the first city is the same and the order changes

	for (int i = 0; i < num_weights; i++) {
		//cout << "Shuffled index of policies  " << policies[i] << endl;
	}
}


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
	void Simulation(ofstream& fout, int s, vector<Policies> population);
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

void boat::Simulation(ofstream &fout, int s, vector<Policies> population) {
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
	//population[s].fitness = fabs(fitness);
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
vector<Policies> EA_Replicate(vector<Policies> Pop, vector<city> City_Wok) {
	//Take vector of policies and double it
	// Mutate the doubled policies slightly
	int R;
	int O;
	int S;
	int temp;
	vector<Policies> Gen;
	Gen = Pop; //Copies the old population 
	for (int i = 0; i < size(Pop); i++) {
		R = rand() % (size(Pop) - 1);
		O = rand() % (size(City_Wok) - 2) + 1;
		S = rand() % (size(City_Wok) - 2) + 1;
		while (O == S) {
			S = rand() % (size(City_Wok) - 2) + 1;
		}
		temp = Pop[R].policies[O];
		Pop[R].policies[O] = Pop[R].policies[S];
		Pop[R].policies[S] = temp;
		Gen.push_back(Pop[R]);
		//assert(Gen[R].policies != Pop[R].policies); //LR_4
	}
	return Gen;
}

vector<Policies> EA_Evaluate(vector<Policies> Pop, vector<city> City_Wok, int city_x, int city_y, int num_cities) {
	//calculate the distance for each policy's combined cities
	// take the distance between the first and second city and add it to the distance between the second and the third city...

	for (int k = 0; k < size(Pop); k++) {
		int distance = 0;
		Pop[k].fitness = 0;
		int distance_1 = 0;
		for (int i = 0; i < size(City_Wok) - 2; i++) {
			distance_1 = distance;
			distance = sqrt(pow(City_Wok[Pop[k].policies[i + 1]].city_x - City_Wok[Pop[k].policies[i]].city_x, 2) + pow(City_Wok[Pop[k].policies[i++]].city_y - City_Wok[Pop[i].policies[i]].city_y, 2)) + distance;
			assert(distance != distance_1); //LR_7
											//cout << distance << endl;		
		}
		Pop[k].fitness = distance;
		cout << Pop[k].fitness << endl;
		assert(distance >= num_cities); //LR_8
		assert(Pop[k].fitness != 0); //MR_2 & MR_3
	}
	for (int x = 0; x < size(Pop); x++) {
		for (int y = 0; y < size(City_Wok); y++) {
			for (int z = y + 1; z < size(City_Wok); z++) {
				assert(Pop[x].policies[y] != Pop[x].policies[z]); //LR_6
			}
		}
	}
	return Pop;
}

vector<Policies> EA_Downselect(vector<Policies> Pop) { //Binary Tournament - Take 
													   // take the fitness of one policy and compare it to another fitness of another policy at random.
													   // whichever one has the lower fitness gets put into a new vector until size(population/2)
	vector<Policies> Pop_new;
	for (int i = 0; i < size(Pop) / 2; i++) {
		int R;
		int S;
		R = rand() % (size(Pop) - 1);
		S = rand() % (size(Pop) - 1);
		if (Pop[R].fitness < Pop[S].fitness) {
			Pop_new.push_back(Pop[R]);
		}
		else {
			Pop_new.push_back(Pop[S]);
		}
	}
	assert(size(Pop_new) == size(Pop) / 2); //MR_4
											//return that new vector

	return Pop_new;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////

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
	vector<Policies> population;
	for (int p = 0; p < pop_size; p++) {
		Policies A;
		A.init_policy(NN.get_number_of_weights());
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
			
			B.Simulation(fout,s,population);

		}	
		// UPDATE EA WITH FITNESS
		// EA - DOWNSELECT WITH GIVEN FITNESS
		//population = EA_downselect();
		// EA - MUTATE and repopulate WEIGHTS
		//population = EA_replicate();
		
	}
	fout.close();

	//////// MR_2 ///////////
	//assert(B.boat_y <= B.goal_y2 && B.boat_y >= B.goal_y1 && B.boat_x <= (B.goal_x2 + .05*B.goal_x2) && B.boat_x >= (B.goal_x2 - .05*B.goal_x2));
	//cout << "Boat passed through goal" << endl;

	//sort(population.begin(), population.end(), less_than_key());
	
	int input;
	cin >> input;
    return 0;
}

