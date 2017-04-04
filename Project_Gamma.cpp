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
	assert(*policies.begin() == 0); //LR_5
	//check to see if the first city is the same and the order changes
	
	for (int i = 0; i < size(City_Wok); i++) {
		cout << "Shuffled index of policies  " << policies[i] << endl;
	}
	

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
			distance = sqrt(pow(City_Wok[Pop[k].policies[i+1]].city_x - City_Wok[Pop[k].policies[i]].city_x, 2) + pow(City_Wok[Pop[k].policies[i++]].city_y - City_Wok[Pop[i].policies[i]].city_y, 2)) + distance;
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
			for (int z = y+1; z < size(City_Wok); z++){
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
	for (int i = 0; i < size(Pop)/2; i++) {
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


int main()
{
	srand(time(NULL));
	int num_cities = 10;
	vector<city> City_Wok; //I apologize for the Southpark reference
	vector<Policies> Pop;
	int Population = 100;
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

	
	for (int pp = 0; pp < Population/2; pp++) {
		Policies Po;
		Po.init_policy(City_Wok);
		Pop.push_back(Po);
	}
	assert(size(Pop) == Population/2); //MR_1
	
	ofstream fout;
	fout.clear();
	fout.open("Learning_Curve.csv", ofstream::out | ofstream::trunc);
	//loop
	for (int t = 0; t < 100; t++){
		Pop = EA_Replicate(Pop, City_Wok);
		assert(size(Pop) == Population); // MR_5
		Pop = EA_Evaluate(Pop, City_Wok, C.city_x, C.city_y, num_cities);
		Pop = EA_Downselect(Pop);
		fout << "\nGeneration" << "," << t;
		for (int b = 0; b < size(Pop); b++) {
			fout << "," << Pop[b].fitness;
		}
	}
	
    return 0;
}

