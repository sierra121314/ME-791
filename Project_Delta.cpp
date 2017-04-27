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
using namespace std;

#define PI 3.1415

int boundary_x_low = 0;
int boundary_y_low = 0;
int boundary_x_high = 1000;
int boundary_y_high = 1000;

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
	double v = 3; //velocity //set//
	double w = 0; //angular velocity
	double dt = 0.2; //time step //set//
	double theta; //radians
	double T = 5.0; //set//
	double u = 0;
	void Init();
	void Simulation(ofstream& fout);
};

void boat::Init() {
	// Starting coordinates of agent
	//start_boat_x = rand() % boundary_x_high;
	//start_boat_y = rand() % boundary_y_high;
	start_boat_x = 6;
	start_boat_y = 2;
	boat_x = start_boat_x;
	boat_y = start_boat_y;

	//Orientation of Agent
	//double theta_deg = rand() % 360; //random degree orientation
	//theta = theta_deg * PI / 180; // converts degrees to radians
	theta = PI;

	// Angular Speed of Agent
	//w = rand() % 2*PI;
	w = 0;

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

void boat::Simulation(ofstream& fout) {
	double y;
	double m;
	double b;
	double boat_x1;
	double boat_y1;
	
	boat_x = start_boat_x;
	boat_y = start_boat_y;

	cout << boat_x << ',' << boat_y << endl;

		
	for (int i = 0; i < 10000; i++) {
		
		cout << boat_x << ',' << boat_y << endl;
		boat_x1 = boat_x + v*cos(theta)*dt;
		boat_y1 = boat_y + v*sin(theta)*dt;
		theta = theta + w*dt; 
		w = w + (u - w)*dt / T; 
		m = (boat_y1 - boat_y) / (boat_x1 - boat_x); //slope
		b = boat_y1 - m*boat_x1; // y intercept
		y = m*goal_x1+b; //equation of a line
		boat_x = boat_x1; //setting the new x value
		boat_y = boat_y1; //setting the new y value
		fout << boat_x << ',' << boat_y << ',' << theta << ',' << v << endl;
		/////// CONDITIONS TO QUIT THE LOOP ///////////
		if (boat_y <= goal_y2 && boat_y >= goal_y1 && boat_x <= (goal_x2 + .05*goal_x2) && boat_x >= (goal_x2 - .05*goal_x2)) {
			break;
		}
		cout << "boat not by goal" << endl;
		if (boat_x <= boundary_x_low || boat_x >= boundary_x_high || boat_y <= boundary_y_low || boat_y >= boundary_y_high) {
			break;
		}
		cout << "boat within boundary" << endl;
	} //for loop


	//////// MR_2 ///////////
	//assert(boat_y <= goal_y2 && boat_y >= goal_y1 && boat_x <= (goal_x2 + .05*goal_x2) && boat_x >= (goal_x2 - .05*goal_x2));
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




int main()
{
	int runs;
	runs = 1;
	
	boat B;

	//define starting position and goal position
	B.Init(); 

	////////// START SIMULATION ///////////////
	ofstream fout;
	fout.open("Movement.csv", ofstream::out | ofstream::trunc);
	fout << "Coordinates of Boat for each time step" << "\n";

	for (int r = 0; r < runs; r++)	{
		fout << "Run" << r << "\n";
		B.Simulation(fout);
		
	}
	fout.close();

	//loop simulation with NN
	

	//Graph coordinates of boat over dt
	//loop Run - x/y coordinates





	
	// 
	/*
	for (int i = 0; i <num_stat; stat++){//number of statistical runs
		//create vectors 
		//create all objects
		for (int j = 0; j < num_gen; gen++) { //number of generations
			
			for (int k = 0; k < num_sim; sim++) { //number of simulations

			}
		}
	}
	*/
	int input;
	cin >> input;
    return 0;
}

