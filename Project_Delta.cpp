// Project_Delta.cpp : Defines the entry point for the console application.
//

#define _USE_MATH_DEFINES

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

int boundary_x_low = 0;
int boundary_y_low = 0;
int boundary_x_high = 1000;
int boundary_y_high = 1000;

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////   B   O   A   T   /////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
class boat {
public:
	int boat_x;
	int boat_y;
	int goal_x;
	int goal_y;
	int start_boat_x;
	int start_boat_y;
	double v = 0.3;
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
	start_boat_y = 1;

	//Orientation of Agent
	int theta_deg = rand() % 360; //random degree orientation
	theta = theta_deg * M_PI / 180; // converts degrees to radians

	// Angular Speed of Agent?????

	// Goal coordinates
	//goal_x = rand() % boundary_x_high;
	//goal_y = rand() % boundary_y_high;
	goal_x = 1; //testing
	goal_y = 3; //testing

}

void boat::Simulation() {

	Init(); //define starting position and goal position

	// while agent is in bounds or the agent finds the goal
	while (boat_x > boundary_x_low && boat_x < boundary_x_high && boat_y > boundary_y_low && boat_y < boundary_y_high || boat_x == goal_x && boat_y == goal_y) {
		
		//Always starts boat in same position
		boat_x = start_boat_x; 
		boat_y = start_boat_y;
		for (int i = 0; i < 5; i++) {
			//boat_x = boat_x + v*sin(theta)*dt;
			cout << boat_y << endl;
			boat_y = boat_y + v*cos(theta)*dt;
				
			//theta[i+1] = theta[i] + w[i]*dt;
			//w = w + (u - w)*dt/T;
		} //for loop
	} //while loop
	
}

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////






int main()
{
	int runs;
	runs = 10;
	// starting positions
	boat B;
	for (int r = 0; r < runs; r++)	{
		B.Simulation();

	}
	
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

