// Gonzales_Sierra_HW1_ME791.cpp : Defines the entry point for the console application.
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

#define max_cards 52; //any number of desks will always have 52 cards in each deck
#define max_c_suite 13; //every suite will only have 13 cards, Ace is zero

using namespace std;

//Global Variables
int num_decks = 2;

class card {
public:
	int card_num;
	int card_val = card_num%max_c_suite; //modulo opperator will get us the card value Ace-King every 13th card
	card(int);
	string print_card();
	//void export_card();
	static void TestA(vector<card>); //static means that it doesn't belong to any single card
	static void TestB(vector<card>);
};

card::card(int val) {
	card_num = val;
}

string card::print_card() {
	string s = "";
	if (card_val > 0 && card_val < 10) {
		s = s + to_string(card_val+1) + " "; //to_string allows the number to be printed to the text file

	}
	else if (card_val == 0) {
		s = s + "Ace" + " ";
	}

	else if (card_val == 10) {
		s = s + "Jack" + " ";
	}

	else if (card_val == 11) {
		s = s + "Queen" + " ";
	}

	else if (card_val == 12) {
		s = s + "King" + " ";
	}

	if (card_num < 13) {
		s = s + "of Diamonds" + "\n";
	}

	else if (card_num < 26) { //we know it is not less than 13 due to first if statement
		s = s + "of Hearts" + "\n";
	}
	else if (card_num < 39) { //we know it is not less than 26 due to first if statement
		s = s + "of Clubs" + "\n";
	}
	else  { //we know it is not less than 39 due to first if statement
		s = s + "of Spades" + "\n";
	}
	return s;
}

// Function called create_deck
vector<card> create_deck(){
	vector<card> decks; //all the decks together
	for (int d = 0; d < num_decks; d++) { // For loop to create n number of decks
		for (int c = 0; c < 52; c++) { // max_num_cards*n
			decks.push_back(card(c));
		}
	}
	return decks;
}



// Function called Shuffle
vector<card> shuffle_deck(vector<card> original_deck) { //going to shuffle the original deck
	vector<card> new_deck; //shuffled deck
	for (int s = 0; s < 52 * num_decks; s++) {
		int random_index = rand() % original_deck.size(); //generating a random number and bringing it down to zero and the deck size
		new_deck.push_back(original_deck.at(random_index));
		original_deck.erase(original_deck.begin() + random_index); //found at: http://www.cplusplus.com/reference/vector/vector/erase/
	}
	return new_deck;
}

void card::TestA(vector<card> V) {
	//When shuffling a single deck, no card is dulicated
	//bool single_repeat = false; //assuming no duplicates
	if (num_decks == 1) {
		for (int i = 0; i < 52; i++) {
			for (int j = i + 1; j < 52; j++) { // There are copies in the deck
				assert(V.at(i).card_val != V.at(j).card_val || V.at(i).card_num != V.at(j).card_num);  //if this is true, ignore assert
				//if (V.at(i).card_val == V.at(j).card_val && V.at(i).card_num == V.at(j).card_num) { //instead of .at(i), you can use [i]
				//	single_repeat = true;
				//}
				//else { //there are no copies in the deck
				//	single_repeat = false;
					
				//}
			}
		}
	}


}


void card::TestB(vector<card> V) {
	//Check the first card in the deck against the rest of the deck, there should be n amount of that first card
	int counter = 0;
	card temp_card = V.at(0); //copies the found card
	if (num_decks > 1) {
		for (int i = 0; i < num_decks*52; i++) {
			if (temp_card.card_val == V.at(i).card_val && temp_card.card_num == V.at(i).card_num) {
				counter++; //keeps track of the number of the first card
			}
			
		}
		assert(counter == num_decks);
	}
}


int main()
{
	//srand(time(NULL));
	//card test_card = card(35); //test to make sure 52 cards are labeled

	vector<card> decks = create_deck();

	decks = shuffle_deck(decks);
	//export suit and value of the shuffled deck to a text file
	ofstream fout;
	fout.open("card_suit_log.txt", ofstream::out | ofstream::trunc);
	fout << "important card stuff" << "\n";
	for (int i = 0; i < num_decks * 52; i++) {
		fout << decks.at(i).print_card() << "\n";
	}
	fout.close();

	//Tests
	card::TestA(decks);
	card::TestB(decks);

	int input;
	cin >> input; //So I can see the terminal before I close it


    return 0;
}

