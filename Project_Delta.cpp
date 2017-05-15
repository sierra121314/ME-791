// Project_Delta.cpp : Defines the entry point for the console application.
//


//#include "stdafx.h"
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
neural_network NN;
#define PI 3.1415
#define LYRAND (double)rand()/RAND_MAX

int boundary_x_low = 0;
int boundary_y_low = 0;
int boundary_x_high = 1000;
int boundary_y_high = 1000;

////////////////////////////////////////////////////////////////////////////
///////////////////////////   Policies  ////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

class Policies {
public:
    //MR_1:  initialize a population of policies - associated with a fitness
    //fitness //MR_2::  distance for the entire policy, minimal
    //
    double fitness = 0;
    void init_policy(int num_weights); //initialize one policy
    vector<double> weights;
};

void Policies::init_policy(int num_weights) {
    for (int p = 0; p < num_weights; p++) {
        //cout << "Order " << p << endl;
        weights.push_back(p);
    }
    //By shuffling only after the first city, we ensure we start in the same place each time
    random_shuffle(weights.begin() + 1, weights.end());
    assert(*weights.begin() == 0);
    //check to see if the first city is the same and the order changes
    
    for (int i = 0; i < num_weights; i++) {
        //cout << "Shuffled index of policies  " << weights[i] << endl;
    }
}


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
    double starting_w;
    double beta;
    double v = 3; //velocity //set//
    double w = 0; //angular velocity
    double dt = 0.2; //time step //set//
    double theta; //radians
    double T = 5.0; //set//
    double u;
    void Init();
    void Simulation(ofstream& fout, int s, vector<Policies> population, double& fitness);
    void find_beta(); //thanks Bryant
    
    //Evolutionary EA;
};

void boat::Init() { //pass in NN and EA
    /// STARTING POSITION OF BOAT ///
    //start_boat_x = rand() % boundary_x_high;
    //start_boat_y = rand() % boundary_y_high;
    start_boat_x = 600;
    start_boat_y = 200;
    boat_x = start_boat_x;
    boat_y = start_boat_y;
    beta = 0;
    u = 0;
    /// ORIENTATION OF AGENT ///
    double theta_deg = rand() % 360; ///random degree orientation
    starting_theta = theta_deg * PI / 180; /// converts degrees to radians
    //starting_theta = 0;
    theta = starting_theta;
    
    /// ANGULAR SPEED OF AGENT ///
    starting_w = rand() % 6;
    //starting_w = 0;
    w = starting_w;
    
    /// GOAL POSITION ///
    //goal_x1 = rand() % boundary_x_high;
    //goal_y1 = rand() % (boundary_y_high-2);
    //goal_x2 = goal_x1;
    //goal_y2 = goal_y1 - 2;
    goal_x1 = 100; //testing
    goal_y1 = 10; //testing
    goal_x2 = 100; //testing
    goal_y2 = 30; //testing
    
}

void boat::Simulation(ofstream &fout, int s, vector<Policies> population, double& fitness) {
    //pass in weights
    double y;
    double m;
    double b;
    double boat_x1;
    double boat_y1;
    double time;
    double distance;
    double distance_x;
    double distance_y;
    double stray;
    
    // INITIALIZE STARTING POSITIONS //
    boat_x = start_boat_x;
    boat_y = start_boat_y;
    w = starting_w;
    //cout << boat_x << "," << boat_y << endl;
    theta = starting_theta;
    distance = 0;
    /// CALCULATE THE STRAY FROM THE GOAL ///
    find_beta();
    stray = beta - theta;
    if (stray < 0) {
        stray += 2 * PI;
    }
    else if (stray > PI) {
        stray = 2 * PI - stray;
    }
    
    //cout << "before time step loop" << endl;
    for (int i = 0; i < 1000; i++) {
        //cout << "inside time step loop" << endl;
        // Get input vector for NN - x,y,w,theta
        vector<double> state;
        //state.push_back(cos(stray));
        state.push_back(sin(stray));
        state.push_back(boat_x);
        state.push_back(boat_y);
        //state.push_back(theta);
        NN.set_vector_input(state);
        //Give to NN
        
        //cout << boat_x << ',' << boat_y << endl;
        //cout << w << endl;
        /// GET VALUE OF U FROM NN
        NN.execute();
        //cout << "poop" << endl;
        u = NN.get_output(0)* PI / 180;
        cout << "u" << u << endl;
        
        /// CALCULATE X,Y,THETA,W ///
        boat_x1 = boat_x + v*cos(theta)*dt;
        boat_y1 = boat_y + v*sin(theta)*dt;
        theta = theta + w*dt;
        if (theta > (2 * PI)) {
            theta = theta - 2 * PI;
        }
        else if (theta < (-2 * PI)) {
            theta = theta + 2 * PI;
        }
        w = w + ((u - w)*dt) / T;
        
        /// CALCULATIONS FOR INTERCEPT ///
        m = (boat_y1 - boat_y) / (boat_x1 - boat_x); ///slope
        b = boat_y1 - m*boat_x1; /// y intercept
        y = m*goal_x1+b; ///equation of a line
        
        if (boat_x1 < boat_x) {		//If x1 is to the left of x2
            if (boat_x1 <= goal_x1 && boat_x >= goal_x2) {	//If they are on either side of the goal
                if (y >= goal_y1 && y <= goal_y2) {
                    distance = distance - 10;
                    break;
                }
            }
        }
        else {		//If x2 is to the left of x1
            if (boat_x <= goal_x1 && boat_x1 >= goal_x2) {	//If they are on either side of the goal
                if (y >= goal_y1 && y <= goal_y2) {
                    distance = distance - 10;
                    break;
                }
            }
        }
        
        //cout << "boat not close to goal" << endl;
        
        
        
        /// UPDATE NEW X,Y, VALUES ///
        boat_x = boat_x1; ///setting the new x value
        boat_y = boat_y1; ///setting the new y value
        fout << boat_x << ',' << boat_y << ',' << theta << ',' << w << endl;
        cout << boat_x << ',' << boat_y << ',' << theta << ',' << w << endl;
        
        /// CALCULATE THE STRAY FROM THE GOAL ///
        find_beta();
        stray = beta - theta;
        if (stray < 0) {
            stray += 2*PI;
        }
        else if (stray > PI) {
            stray = 2 * PI - stray;
        }
        
        
        /// CALCULATE DISTANCE TO GOAL ///
        distance_x = pow(goal_x1 - boat_x, 2);
        distance_y = pow(goal_y1 - boat_y, 2);
        //cout << "d_x   " << distance_x << '\t' << "d_y   " << distance_y << endl;
        distance = distance + sqrt(distance_x + distance_y);
        
        /// CONDITIONS TO QUIT THE LOOP ////
        assert(boat_x > boundary_x_low);
        assert(boat_y > boundary_y_low);
        assert(boat_x < boundary_x_high);
        assert(boat_y < boundary_y_high);
        if (boat_x < boundary_x_low || boat_x > boundary_x_high || boat_y < boundary_y_low || boat_y > boundary_y_high){
            distance = distance + 10000;
            break;
        }
        //cout << "boat within boundary" << endl;
        
        
        /// CALCULATIONS FOR TIME FOR FITNESS //
        //time =1; //just for now
        
    } //for loop
    
    ////////// EXITING COORDINATES ////////
    cout << s << "\t" << boat_x << ',' << boat_y << endl;
    
    /// CALCULATE THE FITNESS - uses distance and time // MR_4 //
    fitness = distance; //overall distance it took to get to the goal
    //cout << "fitness" << fitness << endl;
    //population[s].fitness = fabs(fitness);
}

void boat::find_beta() {
    beta = atan((boat_y - ((goal_y1 - goal_y2) / 2)) / (boat_x - goal_x1));
    if (boat_x > goal_x1) {
        beta += 180;
    }
    else if (boat_x<goal_x1 && boat_y >((goal_y1 + goal_y2) / 2)) {
        beta += 360;
    }
}


//////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////   EVOLUTIONARY ALGORITHM  ////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
vector<Policies> EA_Replicate(vector<Policies> population, int num_weights) {
    //Take vector of policies and double it
    // Mutate the doubled policies slightly
    int R;
    int O;
    
    
    int n = num_weights/4; //number of mutations
    
    vector<Policies> Gen;
    Gen = population; //Copies the old population
    for (int i = 0; i < population.size()/2; i++) {
        R = rand() % (population.size());
        for (int x; x < n; n++) {
            O = rand() % num_weights;
            population[R].weights[O] = population[R].weights[O] + LYRAND / 10 - LYRAND / 10;
            
        }
        
        Gen.push_back(population[R]);
        //assert(Gen[R].weights != Pop[R].weights); //LR_4
    }
    return Gen;
}


vector<Policies> EA_Downselect(vector<Policies> population) { //Binary Tournament - Take
    // take the fitness of one policy and compare it to another fitness of another policy at random.
    // whichever one has the lower fitness gets put into a new vector until size(population/2)
    vector<Policies> Pop_new;
    for (int i = 0; i < population.size() / 2; i++) {
        int R;
        int S;
        R = rand() % (population.size() - 1);
        S = rand() % (population.size() - 1);
        if (population[R].fitness < population[S].fitness) {
            Pop_new.push_back(population[R]);
        }
        else {
            Pop_new.push_back(population[S]);
        }
    }
    assert(Pop_new.size() == population.size() / 2); //MR_4
    //return that new vector
    
    return Pop_new;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    
    int MAX_GENERATIONS = 5;
    int pop_size = 10;
    srand(time(NULL));
    
    //Evolutionary EA;
    int num_weights = 0;
    
    /// SET UP NEURAL NETWORK ///
    
    NN.setup(3, 5, 1); ///3 input, 5 hidden, 1 output (Bias units hidden from user)
    
    //for stray
    NN.set_in_min_max(-1.2,1.2);
    //NN.set_in_min_max(-1.2, 1.2);
    
    /// FOR X-VALUES
    NN.set_in_min_max(0.0, boundary_x_high); /// limits of input for normalization
    /// FOR Y-VALUES
    NN.set_in_min_max(0.0, boundary_y_high); /// limits of input for normalization
    /// FOR THETA
    //NN.set_in_min_max(0.0, 6.28);
    /// FOR U
    NN.set_out_min_max(-15.0, 15.0); /// limits of outputs for normalization
    
    //NN.set_vector_input(vi); /// vector of inputs
    num_weights = NN.get_number_of_weights();
    
    /// DEFINE STARTING POSITION AND GOAL POSITION ///
    boat B;
    B.Init();
    
    /// INITIALIZE POLICIES ///
    vector<Policies> population;
    for (int p = 0; p < pop_size; p++) {
        Policies A;
        A.init_policy(num_weights);
        population.push_back(A);
    }
    assert(population.size() == pop_size);
    
    ////////// START SIMULATION ///////////////
    ofstream fout;
    /// MR_3 ///
    fout.open("Movement.csv", ofstream::out | ofstream::trunc);
    fout << "Coordinates of Boat for each time step" << "\n";
    
    for (int g = 0; g < MAX_GENERATIONS; g++)	{
        
        for (int s = 0; s < population.size(); s++) {
            fout << "Sim" << s << "\n";
            cout << population.size() << endl;
            NN.set_weights(population.at(s).weights, true);
            
            B.Simulation(fout,s,population,population.at(s).fitness);
            //cout << num_weights << endl;
            
            // UPDATE EA WITH FITNESS
            
            /// EA - MUTATE and repopulate WEIGHTS
            population = EA_Replicate(population, num_weights);
            /// EA - DOWNSELECT WITH GIVEN FITNESS
            population = EA_Downselect(population);
        }
        
    }
    fout.close();
    
    //////// MR_2 ///////////
    //assert(B.boat_y <= B.goal_y2 && B.boat_y >= B.goal_y1 && B.boat_x <= (B.goal_x2 + .05*B.goal_x2) && B.boat_x >= (B.goal_x2 - .05*B.goal_x2));
    //cout << "Boat passed through goal" << endl;
    
    //sort(population.begin(), population.end(), less_than_key());
    
    int input;
    cin >> input;
    return 0;
}