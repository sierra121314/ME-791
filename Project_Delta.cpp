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
#include <limits>
#include <algorithm>
using namespace std;

int boundary_x_low = 0;
int boundary_y_low = 0;
int boundary_x_high = 1000;
int boundary_y_high = 1000;

class boat {
public:
	int boat_x;
	int boat_y;
	int goal_x;
	int goal_y;
	double v = 0.3;
	double dt = 0.2;
	double T = 5.0;
	double u;
	void Init();
	void Simulation();
};

void boat::Init() {
	int start_boat_x = rand() % boundary_x_high;
	int start_boat_y = rand() % boundary_y_high;
	boat_x = start_boat_x;
	boat_y = start_boat_y;

	goal_x = rand() % boundary_x_high;
	goal_y = rand() % boundary_y_high;
}

void boat::Simulation() {

	//while the ship is still within boundaries
	while (boat_x > boundary_x_low && boat_x < boundary_x_high && boat_y > boundary_y_low && boat_y < boundary_y_high) { 
		Init();
		if (boat_x != goal_x && boat_y != goal_y) {
			for (int i = 0; i < 5; i++) {
				//boat_x = boat_x + v*sin(theta)*dt;
				//boat_y = boat_y = v*cos(theta)*dt;
				//theta[i+1] = theta[i] + w[i]*dt;
				//w = w + (u - w)*dt/T;
			} //for loop
		} //if loop
	} //while loop
	
}

int main()
{
	// starting positions
	// 
	for (int i = 0; i <num_stat; stat++){//number of statistical runs
		//create vectors 
		//create all objects
		for (int j = 0; j < num_gen; gen++) { //number of generations
			
			for (int k = 0; k < num_sim; sim++) { //number of simulations

			}
		}
	}
    return 0;
}

