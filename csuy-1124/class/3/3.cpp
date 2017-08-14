#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <vector>
// imported my file
#include <player.h>
using namespace std;

// function prototype
// what's the use of having a copy, pass by reference
void displayPlayer(const Player& somebody);
void displayAllPlayer(const Player& somebody);
// void dummy(const Player& somebody);

int main() {
	Player bob;
	cout << sizeof(bob) << endl;

	/* cout << bob.height << endl; */
	bob.weight = 10;
	/* cout << bob.weight << endl; */

	/* displayPlayer(bob); */

	vector<Player> players;
	players.push_back(bob);
	displayPlayer(players[0]);
	// push_back makes a copy rather than passing by reference
	bob.height = 42;
	displayPlayer(players[0]);

	// reference the vector's element to actually change it
	players[0].height = 42;
	displayPlayer(players[0]);

	ifstream playerStream("players.txt");

	if (!playerStream) {
		cerr << "Couldn't open file" << endl;
		exit(1);
	}

	int theWeight;
	double theHeight;
	// read file to add players to vector
	while (playerStream >> theHeight >> theWeight) {
		Player aPlayer;
		aPlayer.height = theHeight;
		aPlayer.weight = theWeight;

		players.push_back(aPlayer);
	}
	// remember to free up resources when done
	playerStream.close();

	// ranged for
	for (size_t index = 0; index < players.size(); index++) {
		displayPlayer(players[index]);
	}

	// for aPlayer in players
	for (const Player& aPlayer : players) {
		displayPlayer(aPlayer);
	}
}

// passing by reference allows it to get changed
// setting it as constant makes it not able to change
void displayPlayer(const Player& somebody) {
	cout << "height: " << somebody.height << endl;
	cout << "weight: " << somebody.weight << endl;
};

void displayAllPlayers(const vector<Player>& players) {
	for(const Player& aPlayer : players) {
		displayPlayer(aPlayer);
	}
};

void fillVectorOfPlayers(ifstream& ifs, vector<Player>& players) {
}

// this will not work as you can't set a const when the inside function is pass by reference
/* void dummy(const Player& thePlayer) { */
/* 	displayPlayer(thePlayer) */
/* }; */
