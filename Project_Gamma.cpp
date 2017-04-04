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
	int fitness = 0;
	vector<int> policies; //vectors of integers of the index for each city
	void init_policy(vector<city> City_Wok); //initialize one policy

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
		//cout << "Order " << p << endl;
		policies.push_back(p);
	}
	//By shuffling only after the first city, we ensure we start in the same place each time
	random_shuffle(policies.begin() +1, policies.end()); //LR_5//

	//check to see if the first city is the same and the order changes
	/*
	for (int i = 0; i < size(City_Wok); i++) {
		cout << "Shuffled index of policies  " << index[i] << endl;
	}
	*/

}

vector<Policies> EA_Replicate(vector<Policies> Pop, vector<city> City_Wok) {
	//Take vector of policies and double it
	// Mutate the doubled policies slightly
	int R;
	int O;
	int S;
	int temp;
	vector<Policies> Gen;
	Gen = Pop; //Copies the old population 
	for (int i = 0; i < size(Pop); i++){
		R = rand() % (size(Pop) - 1);
		O = rand() % (size(City_Wok) - 1);
		S = rand() % (size(City_Wok) - 1);
		temp = Pop[R].policies[O];
		Pop[R].policies[O] = Pop[R].policies[S];
		Pop[R].policies[S] = temp;
		Gen.push_back(Pop[R]);
	}
	return Gen;
}


void EA_Evaluate(vector<Policies> Pop, vector<city> City_Wok, int city_x, int city_y) {
	//calculate the distance for each policy's combined cities
	// take the distance between the first and second city and add it to the distance between the second and the third city...
	
	for (int k = 0; k < size(Pop); k++) {
		int distance = 0;
		for (int i = 0; i < size(City_Wok) - 1; i++) {
			for (int j = 1; j < size(City_Wok); j++) {
				distance = sqrt((City_Wok[Pop[k].policies[j]].city_x - City_Wok[Pop[k].policies[i]].city_x) ^ 2 + (City_Wok[Pop[k].policies[j]].city_y - City_Wok[Pop[i].policies[i]].city_y) ^ 2) + distance;
			}
		}
		Pop[k].fitness = distance;
		assert(Pop[k].fitness != 0);
	}
	
	// take that combined distance and push it back to the end of a fitness vector that relates to each policy?

}


void EA_Downselect() { //Binary Tournament - Take 
	// take the fitness of one policy and compare it to another fitness of another policy at random.
	// whichever one has the lower fitness gets put into a new vector until size(population/2)

	//return that new vector
}


int main()
{
	srand(time(NULL));
	int num_cities = 10;
	vector<city> City_Wok; //I apologize for the Southpark reference
	vector<Policies> Pop;
	//establish a vector of cities
	city C;
	for (int c = 0; c < num_cities; c++) {	
		C.city_init();
		//cout << "City " << c << "   " << C.city_x << ", " << C.city_y << endl;
		City_Wok.push_back(C);
	}
	
	//starting_city
	SalesGuy G;
	G.starting_city(City_Wok[0]);
	cout << "Starting City   " << G.SalesGuy_x << "," << G.SalesGuy_y << endl;

	Policies Po;
	Po.init_policy(City_Wok);

	//loop
	EA_Replicate(Pop, City_Wok);

	EA_Evaluate(Pop, City_Wok, C.city_x, C.city_y);

	EA_Downselect();
	
    return 0;
}

