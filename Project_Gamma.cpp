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

// min_grid_x = 0
// min_grid_y = 0
// max_grid_x = 100
// max_grid_y = 100

//class city //represents 1 city
class city {
public:
	int city_x;
	int city_y;
	void boundary_test_c();
};


//class SalesGuy
class SalesGuy {
public:
	int SalesGuy_x;
	int SalesGuy_y;
	int distance;
	void starting_city(); //function(starting) that the agent always starts in city #1
	void overall_distance(); //function that after each iteration the salesman adds the distance to a overall_distance which acts as fitness

};



//class Policies
//MR_1:  initialize a population of policies - associated with a fitness
//fitness //MR_2::  distance for the entire policy, minimal
//

//Function - EA_Replicate
// Takes

//Function - EA_Evaluate - 


//Function - EA_Downselect
//Binary Tournament - Take 

int main()
{
	//establish a vector of cities
	//starting_city


	//loop
	//EA_Replicate
	//EA_Evaluate
	//EA_Downselect
    return 0;
}

