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
	void Init();
	void Simulation(ofstream& fout, int n);
	neural_network NN;
	Evolutionary EA;
};

void boat::Init() { //pass in NN and EA
	// STARTING POSITION OF BOAT //
	//start_boat_x = rand() % boundary_x_high;
	//start_boat_y = rand() % boundary_y_high;
	start_boat_x = 6;
	start_boat_y = 2;
	boat_x = start_boat_x;
	boat_y = start_boat_y;

	//Orientation of Agent
	//double theta_deg = rand() % 360; //random degree orientation
	//starting_theta = theta_deg * PI / 180; // converts degrees to radians
	starting_theta = 0;
	theta = starting_theta;

	// Angular Speed of Agent
	//starting_w = rand() % 2*PI;
	starting_w = 0;
	w = starting_w;

	// Goal coordinates
	//goal_x1 = rand() % boundary_x_high;
	//goal_y1 = rand() % (boundary_y_high-2);
	//goal_x2 = goal_x1;
	//goal_y2 = goal_y1 - 2;
	goal_x1 = 10; //testing
	goal_y1 = 1; //testing
	goal_x2 = 10; //testing
	goal_y2 = 3; //testing

}

void boat::Simulation(ofstream& fout, int n) {
	//pass in weights
	double y;
	double m;
	double b;
	double boat_x1;
	double boat_y1;
	double boat_x_at_y;
	
	// intialize starting positions
	boat_x = start_boat_x;
	boat_y = start_boat_y;
	w = starting_w;
	theta = starting_theta;

	for (int i = 0; i < 10000; i++) {

		// Get input vector for NN - x,y,w,theta
		//Give to NN
		
		cout << boat_x << ',' << boat_y << endl;
		// GET VALUE OF U FROM NN

		// CALCULATE X,Y,THETA,W //
		boat_x1 = boat_x + v*cos(theta)*dt;
		boat_y1 = boat_y + v*sin(theta)*dt;
		theta = theta + w*dt; 
		w = w + (u - w)*dt / T; 

		// CALCULATIONS FOR INTERCEPT //
		m = (boat_y1 - boat_y) / (boat_x1 - boat_x); //slope
		b = boat_y1 - m*boat_x1; // y intercept
		y = m*goal_x1+b; //equation of a line

		// UPDATE NEW X,Y, VALUES
		boat_x = boat_x1; //setting the new x value
		boat_y = boat_y1; //setting the new y value
		fout << boat_x << ',' << boat_y << ',' << theta << ',' << w << endl;

		// CALCULATE DISTANCE TO GOAL //

		/////// CONDITIONS TO QUIT THE LOOP ///////////
		if (boat_x < boundary_x_low || boat_x > boundary_x_high || boat_y < boundary_y_low || boat_y > boundary_y_high) {
			break;
		}
		cout << "boat within boundary" << endl;
		/////// REPLACE THIS WITH WHAT BRYANT WENT OVER
		if (boat_y <= goal_y2 && boat_y >= goal_y1 && boat_x <= (goal_x2 + .05*goal_x2) && boat_x >= (goal_x2 - .05*goal_x2)) {
			break;
		}
		///////////////
		cout << "boat not close to goal" << endl;
		

	} //for loop

	////////// EXITING COORDINATES ////////
	cout << boat_x << ',' << boat_y << endl;
	// CALCULATE THE FITNESS - uses distance and time
	
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
	int generations;
	runs = 1;
	
	Evolutionary EA;
	boat B;

	//define starting position and goal position
	B.Init(); 

	////////// START SIMULATION ///////////////
	ofstream fout;
	///////// MR_3 ////////////
	fout.open("Movement.csv", ofstream::out | ofstream::trunc);
	fout << "Coordinates of Boat for each time step" << "\n";

	for (int g = 0; g < generations; g++)	{
		for (int n = 0; n < EA.weights.size(); n++) {
			fout << "Run" << n << "\n";
			B.Simulation(fout,n);

		}
		// UPDATE EA WITH FITNESS
		// EA - DOWNSELECT WITH GIVEN FITNESS
		// EA - MUTATE and repopulate WEIGHTS
		
		
	}
	//////// MR_2 ///////////
	assert(B.boat_y <= B.goal_y2 && B.boat_y >= B.goal_y1 && B.boat_x <= (B.goal_x2 + .05*B.goal_x2) && B.boat_x >= (B.goal_x2 - .05*B.goal_x2));
	cout << "Boat passed through goal" << endl;

	fout.close();

	
	int input;
	cin >> input;
    return 0;
}

