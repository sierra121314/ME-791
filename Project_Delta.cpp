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
	double v = 0.3;
	double w = 0;
	double dt = 0.2;
	double theta;
	double T = 5.0;
	double u;
	void Init();
	void Simulation();
};

void boat::Init() {
	// Starting coordinates of agent
	//start_boat_x = rand() % boundary_x_high;
	//start_boat_y = rand() % boundary_y_high;
	start_boat_x = 1;
	start_boat_y = 2;
	boat_x = start_boat_x;
	boat_y = start_boat_y;

	//Orientation of Agent
	//double theta_deg = rand() % 360; //random degree orientation
	//theta = theta_deg * PI / 180; // converts degrees to radians
	theta = 0;

	// Angular Speed of Agent
	w = rand() % 2*PI;

	// Goal coordinates
	//goal_x1 = rand() % boundary_x_high;
	//goal_y1 = rand() % (boundary_y_high-2);
	//goal_x2 = goal_x1;
	//goal_y2 = goal_y1 - 2;
	goal_x1 = 5; //testing
	goal_y1 = 1; //testing
	goal_x2 = 5; //testing
	goal_y2 = 3; //testing

}

void boat::Simulation() {
	double y;
	double m;
	double b;
	double boat_x1;
	double boat_y1;
	Init(); //define starting position and goal position

	cout << boat_y << ',' << boat_x << endl;

	// while agent is in bounds or the agent finds the goal
	while (boat_x > boundary_x_low && boat_x < boundary_x_high && boat_y > boundary_y_low && boat_y < boundary_y_high) {
		if (boat_y <= goal_y2 && boat_y >= goal_y1){
			//Always starts boat in same position
			boat_x = start_boat_x;
			boat_y = start_boat_y;
			for (int i = 0; i < 5; i++) {
				boat_x1 = boat_x + v*sin(theta)*dt;
				cout << boat_y << endl;
				boat_y1 = boat_y + v*cos(theta)*dt;
				theta = theta + w*dt;
				w = w + (u - w)*dt / T;
				m = (boat_y1 - boat_y) / (boat_x1 - boat_x);
				b = boat_y1 - m*boat_x1;
				y = m*goal_x1+b;
				boat_x = boat_x1;
				boat_y = boat_y1;
			} //for loop
		}
		
	} //while loop
	
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
	runs = 10;
	// starting positions
	boat B;
	for (int r = 0; r < runs; r++)	{
		B.Simulation();

	}


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

