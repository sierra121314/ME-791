// Project_Gamma.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
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

const int min_grid_x = 0;
const int min_grid_y = 0;
const int max_grid_x = 100;
const int max_grid_y = 100;

//class city //represents 1 city
class city {
public:
	int city_x;
	int city_y;
	void boundary_test_c();
	void city_init(); //randomly choose value for x, y coordinate

};


//class SalesGuy
class SalesGuy {
public:
	int SalesGuy_x;
	int SalesGuy_y;
	int distance;
	void starting_city(city C); //function(starting) that the agent always starts in city #1
	void overall_distance(); //function that after each iteration the salesman adds the distance to a overall_distance which acts as fitness

};


class Policies {
public:
	//MR_1:  initialize a population of policies - associated with a fitness
	//fitness //MR_2::  distance for the entire policy, minimal
	//
	int fitness;
	vector<int> policies; //vectors of integers of the index for each city
	void init_policy(); //initialize one policy

};


void SalesGuy::starting_city(city C) {
	SalesGuy_x = C.city_x;
	SalesGuy_y = C.city_y;
}

void city::city_init() {
	//randomly choose value for x, y coordinate
	city_x = rand() % max_grid_x;
	city_y = rand() % max_grid_y;
}

void Policies::init_policy(vector<city> City_Wok) {
	for (int p = 0; p < size(City_Wok); p++) {
		cout << p << endl;
	}

}

//Function - EA_Replicate
// Takes

//Function - EA_Evaluate - 


//Function - EA_Downselect
//Binary Tournament - Take 

int main()
{
	srand(time(NULL));
	int num_cities = 10;
	vector<city> City_Wok; //I apologize for the Southpark reference
	//establish a vector of cities
	city C;
	for (int c = 0; c < num_cities; c++) {	
		C.city_init();
		cout << "City " << c << "   " << C.city_x << ", " << C.city_y << endl;
		City_Wok.push_back(C);
	}
	
	//starting_city
	SalesGuy G;
	G.starting_city(City_Wok[0]);
	cout << "Starting City   " << G.SalesGuy_x << "," << G.SalesGuy_y << endl;

	Policies Po;
	Po.init_policy(City_Wok);

	//loop
	//EA_Replicate
	//EA_Evaluate
	//EA_Downselect
    return 0;
}

