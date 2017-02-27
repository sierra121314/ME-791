// SG_HW_2.cpp : Defines the entry point for the console application.
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
using namespace std;

class grid {
public:
	// Coordinates of agent and goal
	int agent_x;
	int agent_y;
	int goal_x = 11;
	int goal_y = 7;
	void HumanControlled();
	void HardCoded();
	void TestA();
	void TestB();
	void TestC();
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

int main()
{
	grid g;
	g.agent_x = 0; //Initialize
	g.agent_y = 0;
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
	
	int mode;
	cout << "What mode would you like to try?   \n";
	//http://www.cplusplus.com/forum/beginner/80005/
	do {
		cout << "Enter 1 for a Human Controlled gridworld or 2 for a Hard-coded grid world. \n";
			cin >> mode;
			if (mode < 1 || mode >2)
				cout << "Only two modes available...\n\n";
	} while (mode < 1 || mode >2); 
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
	//eventually
	//else //ie Q-learner {}
	
	printf("\nCongrats! You caught the Golden Snitch!  \n\n");
	
	//press any key to continue
	system("PAUSE");
	//close program
	return 0;
}