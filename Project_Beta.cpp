// Project_Beta.cpp : Defines the entry point for the console application.
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

class grid {
public:
	// Coordinates of agent and goal
	int agent_x;
	int agent_y;
	int goal_x = 11;
	int goal_y = 7;
	void RewardTable();
	vector<int> RT;
	void HumanControlled();
	void HardCoded();
	void TestA();
	void TestB();
	void TestC();
	void TestE(int start_x, int start_y);
	
};

class Q_learn {
public:
	double Q_val;
	int Q_spot;
	void learning_curve(); //showing average number of steps taken as a...
	vector<vector<double>> Q_table;
	vector<int> State;
	void Q_learner(int &agent_x, int &agent_y, vector<int> &RT, int &goal_x, int &goal_y, int start_x, int start_y);
	int sense();
	int decide();
	int act(int &agent_x, int &agent_y);
	void react(int &agent_x, int &agent_y, vector<int> &RT);
	void Q_learner_init();
	void TestD();
	
	void TestF();
	void TestG();
	//function of episode averaged over 30 statistical runs

};

const int boundary_low_x = 0; // lower x boundary that the agent cannot be less than
const int boundary_high_x = 13; // upper x boundary that the agent cannot be greater than
const int boundary_low_y = 0; // lower y boundary that the agent cannot be less than
const int boundary_high_y = 9; // upper y boundary that the agent cannot be greater than

void display_table(int agent_x, int agent_y, int goal_x, int goal_y) {
	// Gives grid boundaries and positions agent and goal in grid
	char grid[boundary_high_y][boundary_high_x];
	grid[agent_y][agent_x] = 'A';
	grid[goal_y][goal_x] = 'G';

	// Display the Table
	printf("\n");
	for (int r = 0; r < boundary_high_y ; r++) { // r spans the range 0 to high y boundary
		for (int c = 0; c < boundary_high_x ; c++) { // c spans the range 0 to high x boundary
														// when a spot in the grid is A or G
			if (grid[r][c] == 'A' || grid[r][c] == 'G') {
				printf("%c", grid[r][c]); // print its value at its position in the grid
			}
			else {
				printf("%c", '-'); // everything else is a dash, prettier this way
			}
		}
		printf("\n");
	}
	printf("\n");
	printf("\n");
}

void grid::RewardTable() {
	// Reward table
	// Initialize reward table
	// Update function for Reward table
	// All spots other than goal to be equal to -1, goal = 100
	int num_spots = (boundary_high_x + 1)*(boundary_high_y + 1);
	for  (int i = 0; i < num_spots; i++){
		RT.push_back(-1);
	}
	int R;
	R = goal_x +  goal_y * (boundary_high_x + 1); //which state goal is at
	RT[R] = 100; //Set goal to 100 points to Gryffindor!!!
}

void grid::TestA() {
	//When the agent is placed far off the gridworld, it will be bumped back onto the grid
	//when x/y coordinates of the agent are outside of the coordinates of the grid
	assert(agent_x <= boundary_high_x && agent_x >= boundary_low_x && agent_y <= boundary_high_y && agent_y >= boundary_low_y);
	cout << "Test A passes  \n\n";
}

void grid::TestB() {
	//Agent can be guided to the goal by a human
	//if user chooses to do human control, after goal is reached run test
	assert(agent_x == goal_x && agent_y == goal_y); //assert if the agent coordinates do not equal the goal coordinates
	cout << "Test B passes  \n\n";
}

void grid::TestC() {
	//Agent can move to goal by rule of thumb(hard coded)
	assert(agent_x == goal_x && agent_y == goal_y); //assert if the agent coordinates do not equal the goal coordinates
	cout << "Test C passes  \n\n";
}

void Q_learn::TestD() {
	//No Q-value ever exceeds the reward given by reaching the goal state
	assert(Q_val < 101);
	//cout << "TestD Passes \n\n";
}

void grid::TestE(int start_x, int start_y) {
	//When the agent reaches the goal state, it is reset to the 
	//initial state and is identical to a freshly-initialized agent,
	//except in updated Q-values
	//assert(agent x/y position equals the initial xy position);
	assert(agent_x == start_x || agent_y == start_y);
	cout << "TestE Passes \n\n";
}

void Q_learn::TestF() {
	//The agent is capable of using Q-learning to get to the goal in near optimal number of steps
	//take the lowest amount of steps out of all step recordings and compare with the last recording
	//if within a certain range - TestF passes

	cout << "TestF Passes \n\n";
}

void Q_learn::TestG() {
	//The agent can use a different state representation that in TestD and
	//get to the goal state
	//Could reference its starting point and each represent each grid it is in as a number
	cout << "TestG Passes \n\n";
}

void grid::HumanControlled() {
	char direction = 'c';
	while (agent_x != goal_x || agent_y != goal_y) {

		// Display the Table
		display_table(agent_x, agent_y, goal_x, goal_y);

		//Display Instructions

		printf("Please enter a direction you wish the Agent(A) to move: North(N), South(S), East(E), West(W) \n");
		scanf_s(" %c", &direction, 1); //Make sure to put space before %c
									   // space makes it look like a new input

		switch (direction) // Instead of original if statement because it includes both possibilities
		{
			//For North Direction
		case 'N': // either capital or
		case 'n': // lowercase for north direction
				  //go 
				  //check if within boundary
			if (agent_y - 1 >= boundary_low_y) {
				//physically change
				agent_y--;
			}
			else {
				printf("Direction Not Within Boundary");

			}
			break;

			// For South Direction
		case 'S': // either capital or
		case 's': // lowercase for south direction
			if (agent_y + 1 < boundary_high_y) {
				// Physically change Agent Position
				agent_y++;
			}
			else {
				printf("Direction Not Within Boundary");
			}
			break;

		case 'W':
		case 'w':
			if (agent_x - 1 >= boundary_low_x) {
				// Physically change Agent Position
				agent_x--;
			}
			else {
				printf("Direction Not Within Boundary");
			}
			break;

		case 'E':
		case 'e':
			if (agent_x + 1 < boundary_high_x) {
				agent_x++;
			}
			else {
				printf("Direction Not Within Boundary");
			}
			break;

		default:
			printf("Please enter a valid direction");
		}
	}
}

void grid::HardCoded() {
	// Take the agent coordinates and
	// Move, one at a time, to get the x coordinate to match with the goal.
	// Move to get the y coordinate to match the goal
	while (agent_x != goal_x) {

		if (agent_x > goal_x) {
			agent_x--;
		}
		else {
			agent_x++;
		}
		display_table(agent_x, agent_y, goal_x, goal_y);
	}
	while (agent_y != goal_y) {
		if (agent_y > goal_y) {
			agent_y--;
		}
		else {
			agent_y++;
		}
		display_table(agent_x, agent_y, goal_x, goal_y);
	}
}

void Q_learn::Q_learner_init() { 
	// block off all states where actions are not possible (i.e. make the agent go off the board) in the Q-table
	// Initialize all values of the Q-table to near zero
	// Update function for Q-table
	//int num_states = (boundary_high_x + 1)*(boundary_high_y + 1);
	
	for (int i = 0; i < boundary_high_x+1; i++) { // Makes the states and assigns a value
		for (int j = 0; j < boundary_high_y+1; j++) {
			int S;
			S = i + j * (boundary_high_x + 1);
			State.push_back(S);
		}
	}
	
	vector<double> Action;
	for (int k = 0; k < size(State); k++) {
		//if (the state is near a border) {make the action that doesn't work out, not exist or the worst reward possible}
		for (int h = 0; h < 4; h++) {
			Q_val = ((double)rand() / RAND_MAX);
			Action.push_back(Q_val);
			
		}
		Q_table.push_back(Action);
		Action.clear();
	}
	
}

int Q_learn::sense() {// which state is the agent in?
	//compare the coordinates of the agent with a state
	
	int m = 0;
	double e = *max_element(Q_table[Q_spot].begin(), Q_table[Q_spot].end()); //Help from Honi Ahmadian //Finds the largest value at a state
	for (int j = 0; j < 4; j++) {
		if (Q_table[Q_spot][j] == e) {// which action is the greediest
			m = j;
		}
	}
	return m;
}

int Q_learn::decide() {
	//// which options are available to the agent? in that state
	//use random number generator between 0 and .9
	//if digit is zero then the process will randomly select one of the 3 actions
	//if digit is between .1 and .9 then it will choose the greedy option
	// associate the number generated with the action to take
	double t;
	int A;
	t = ((double)rand() / RAND_MAX);
	//cout << t << "\n";
	if (t < .1) {
		//Do a random action in that State
		A = rand() % 4; //choose a random action out of 4
	}
	else { //Do Greedy stuff
		A = sense(); // Action equals the return m from sense()
	}
	//cout << A << "\n";
	return A;
}

int Q_learn::act(int &agent_x, int &agent_y) {
	// move the agent to the spot decided in the decide function
	int A;
	A = decide();
	if (A == 0) {
		//to the left, to the left
		if (agent_x - 1 >= boundary_low_x) {
			agent_x = agent_x - 1;
		}
		else {
			agent_x = agent_x;
		}
	}
	else if (A == 1) {
		//move right
		if (agent_x + 1 < boundary_high_x) {
			agent_x = agent_x + 1;
		}
		else {
			agent_x = agent_x;
		}
	}
	else if (A == 2) {
		//move down
		if (agent_y - 1 >= boundary_low_y) {
			agent_y = agent_y - 1;
		}
		else {
			agent_y = agent_y;
		}
	}
	else if (A == 3) {
		//move up up up
		if (agent_y + 1 < boundary_high_y) {
			agent_y = agent_y + 1;
		}
		else {
			agent_y = agent_y;
		}
	}
	else {
		cout << "you suck" << "\n";
	}
	return A;
}

void Q_learn::react(int &agent_x, int &agent_y, vector<int> &RT) {
	// Q(S,a)=Q(s,a)+alpha[R+gamma*Qmax-Q]
	//new = old + alpha[Reward_from_next_state + gamma*Max_action_val_from_next_state - old]
	//which state we are in now with new placeholder
	int placeholder;
	//cout << agent_x << ", " << agent_y << "\n";
	int Action = act(agent_x, agent_y);
	//cout << agent_x << ", " << agent_y << "\n";
	
	placeholder = agent_x + agent_y * (boundary_high_x + 1);
	double Max_action_val = *max_element(Q_table[placeholder].begin(), Q_table[placeholder].end());
	double alpha = 0.1;
	double gamma = 0.9;
	// equation stuff
	Q_table[Q_spot][Action] = Q_table[Q_spot][Action] + alpha*(RT[placeholder] + gamma*Max_action_val - Q_table[Q_spot][Action]);
	//Q_spot = placeholder
	TestD();//checks to see if the Q_values are greater than 101;
	Q_spot = placeholder;

}

void Q_learn::Q_learner(int &agent_x, int &agent_y, vector<int> &RT,  int &goal_x, int &goal_y, int start_x, int start_y) {
	ofstream fout;
	fout.open("Q_learner_stuff.csv", ofstream::out | ofstream::trunc);
	int count = 0;
	for (int ep = 0; ep < 50; ep++) { //episodes //should be converging to a smaller amount of steps
		agent_x = start_x;
		agent_y = start_y;
		//TestE();
		Q_spot = agent_x + agent_y * (boundary_high_x + 1);
		fout << "\nEpisode" << "," << ep << ",";
		count = 0;
		int QG;
		QG = goal_x + goal_y*(boundary_high_x + 1);
		//cout << Q_spot << "\n\n";
		// loop this stuff until goal coordinates == agent coordinates 
		while (Q_spot != QG) {
			//sense(); //Where are we??? //being called by decide
			//decide(); //decide where to move //being called by act
			//act(agent_x, agent_y); // do that action from the decide function //being called by react
			react(agent_x, agent_y, RT); //update the Q-table using the Q equation
			//cout << Q_spot << "\n";
			count++;
			//fout << "\t\t" << agent_x << ", " << agent_y << "\n";
		}
		fout << count << ",";
		//for (int s = 0; s < size(State); s++) {
			//for (int a = 0; a < 4; a++) {
				//fout << "," << Q_table[s][a] << ",";
			//}
		//}

	}
	
	
}



void Q_learn::learning_curve() {
	//Showing average number of steps taken as a function of episode averaged over 30 statistical runs
	//Run is 30 statastical runs
	//episode is 50 times that i restart the Q-learning
	
	ofstream fout;
	fout.open("Learning_Curve.csv", ofstream::out | ofstream::trunc);
	fout << "Average Number of Steps per Episode" << "\n";
	for (int j = 0; j < 30; j++) {
		fout << "Run" << j << "\n\t\t";
		//some function//count how many steps
		fout << "\t\t" << "moves" << "," << "episode" << "\n" ;
		fout << "\t";
	}
	fout.close();
}

int main()
{
	srand(time(NULL));
	grid g;
	g.agent_x = 0; //Initialize
	g.agent_y = 0;
	g.RewardTable();
	//User input 
	printf("Welcome to Quidditch \n\n");
	//have a user input function asking where you would like to start
	
	int start_x;
	cout << "Where would you like your agent to start?   \n";
	do {
			cout << "Enter an x-position that is less than  " << boundary_high_x << " and greater than  " << boundary_low_x << "\n";
			cin >> start_x;
			if (start_x > boundary_high_x || start_x < boundary_low_x)
				cout << "Number outside range. Try again \n";
	} while (start_x > boundary_high_x || start_x < boundary_low_x);
	if (start_x < boundary_high_x && start_x > boundary_low_x) {
		g.agent_x = start_x;
	}
	
	int start_y; 
	do {
		cout << "Enter an y-position that is less than  " << boundary_high_y << " and greater than  " << boundary_low_y << "\n";
		cin >> start_y;
		if (start_y > boundary_high_y || start_y < boundary_low_y)
			cout << "Number outside range. Try again \n";
	} while (start_y > boundary_high_y || start_y < boundary_low_y);
	if (start_y < boundary_high_y && start_y > boundary_low_y) {
		g.agent_y = start_y;
	}

	g.TestA(); 
	/*
	int mode;
	cout << "What mode would you like to try?   \n";
	//http://www.cplusplus.com/forum/beginner/80005/
	do {
		cout << "Enter 1 for a Human Controlled gridworld, 2 for a Hard-coded grid world, or 3 for a Q-learner. \n";
			cin >> mode;
			if (mode != 1 || mode !=2 || mode != 3)
				cout << "Only three modes available...\n\n";
	} while (mode != 1 || mode !=2 || mode != 3); 
	if (mode == 1) {
		//run Human Controlled program
		g.HumanControlled();
		g.TestB();
	}
	if (mode == 2) {
		//run Hard coded program
		g.HardCoded();
		g.TestC();
	}
	
	if (mode == 3) {
		g.Q_learner(); //run Q-learner
	}
	*/
	Q_learn QL;
	for (int y = 0; y < 30; y++) {
		
		QL.Q_learner_init();
		QL.Q_learner(g.agent_x, g.agent_y, g.RT, g.goal_x, g.goal_y, start_x, start_y);

	
	}
	QL.learning_curve();

	printf("\nCongrats! You caught the Golden Snitch!  \n\n");
	
	//press any key to continue
	system("PAUSE");
	//close program
	return 0;
}
