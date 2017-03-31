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
	void starting_city(int city_x, int city_y); //function(starting) that the agent always starts in city #1
	void overall_distance(); //function that after each iteration the salesman adds the distance to a overall_distance which acts as fitness

};


//class Policies
//MR_1:  initialize a population of policies - associated with a fitness
//fitness //MR_2::  distance for the entire policy, minimal
//

void SalesGuy::starting_city(int city_x, int city_y) {
	SalesGuy_x = city_x;
	SalesGuy_y = city_y;
}

void city::city_init() {
	//randomly choose value for x, y coordinate
	city_x = rand() % max_grid_x;
	city_y = rand() % max_grid_y;
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
	G.starting_city(C.city_x, C.city_y);



	//loop
	//EA_Replicate
	//EA_Evaluate
	//EA_Downselect
    return 0;
}

