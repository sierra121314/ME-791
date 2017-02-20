// SG_HW_2.cpp : Defines the entry point for the console application.
//

#include <iostream> 
#include <stdio.h>
#include "stdafx.h"
using namespace std;

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
	for (int r = 0; r < boundary_high_y + 1; r++) { // r spans the range 0 to high y boundary
		for (int c = 0; c < boundary_high_x + 1; c++) { // c spans the range 0 to high x boundary
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


int main()
{
	//User input 
	//int mode;
	//cout << "What mode would you like to try?   /n";
	//http://www.cplusplus.com/forum/beginner/80005/
//	do {
		//cout << "Enter 1 for a Human Controlled gridworld or 2 for a Hard-coded grid world. /n";
			//cin >> mode;
		//	if (mode <1 || mode >2)
	//}
	



	// Coordinates of agent and goal
	int agent_x = 2;
	int agent_y = 2;
	int goal_x = 11;
	int goal_y = 7;

	char direction = 'c';
	printf("Welcome to Quidditch");

	while (agent_x != goal_x || agent_y != goal_y) {

		// Display the Table
		display_table(agent_x, agent_y, goal_x, goal_y);

		//Display Instructions

		printf("Please enter a direction you wish the Agent(A) to move: North(N), South(S), East(E), West(W)");
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
			if (agent_y + 1 <= boundary_high_y) {
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
			if (agent_x + 1 <= boundary_high_x) {
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
	printf("Congrats! You caught the Golden Snitch!  \n\n");
	//system("pause");
	//press any key to continue
	return 0;
}