#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <vector>
using namespace std;

struct Warrior {
	string name;
	int strength;
};

vector<string> getWords(const string& line);
void addWarriors(const string& name, int strength, vector<Warrior>& warriorsVector);
void status(const vector<Warrior>& warriorsVector);
void battle(string& warriorOneName, string& warriorTwoName, vector<Warrior>& warriorsVector);
void battleStatus(Warrior& warriorOne, Warrior& warriorTwo);
void newLine();

int main() {
	ifstream warriorsFile("warriors.txt");
	if (!warriorsFile) {
		cerr << "Couldn't open file" << endl;
		exit(1);
	}

	vector<Warrior> warriorsVector;
	string word;
	string warriorOneName;
	string warriorTwoName;
	string name;
	int strength;

	// loop over each line and depending on the first word, choose an action
	while (warriorsFile >> word) {
		if (word == "Status") {
			status(warriorsVector);
			newLine();
		} else if (word == "Warrior") {
			warriorsFile >> name >> strength;
			addWarriors(name, strength, warriorsVector);
			newLine();
		} else if (word == "Battle") {
			warriorsFile >> warriorOneName >> warriorTwoName;
			battle(warriorOneName, warriorTwoName, warriorsVector);
			newLine();
		}
	}
}

// add warriors to a vector
void addWarriors(const string& name, int strength, vector<Warrior>& warriorsVector) {
	Warrior aWarrior;
	aWarrior.name = name;
	aWarrior.strength = strength;
	warriorsVector.push_back(aWarrior);
}

// print status of the warriors in the vector
void status(const vector<Warrior>& warriorsVector) {
	size_t vectorSize = warriorsVector.size();
	cout << "There are: " << vectorSize << " warriors" << endl;
	for (size_t index = 0; index < vectorSize; index++) {
		cout << "Warrior: " << warriorsVector[index].name << ", strength: " << warriorsVector[index].strength << endl;
	}
}

// battle
void battle(string& warriorOneName, string& warriorTwoName, vector<Warrior>& warriorsVector) {
	int warriorOneIndex;
	int warriorTwoIndex;
	for (size_t index = 0; index < warriorsVector.size(); index++) {
		if (warriorsVector[index].name == warriorOneName) {
			warriorOneIndex = index;
		} else if (warriorsVector[index].name == warriorTwoName) {
			warriorTwoIndex = index;
		}
	}
	battleStatus(warriorsVector[warriorOneIndex], warriorsVector[warriorTwoIndex]);
}

void battleStatus(Warrior& warriorOne, Warrior& warriorTwo) {
	cout << warriorOne.name << " battles " << warriorTwo.name << endl;
	if (warriorOne.strength == 0 && warriorTwo.strength == 0) {
		cout << "Oh NO! They're both dead! Yuck!" << endl;
	} else if (warriorOne.strength == warriorTwo.strength) {
		warriorOne.strength = 0;
		warriorTwo.strength = 0;
		cout << "Mutual annhilation: " << warriorOne.name << " and " << warriorTwo.name << " die at each other's hands" << endl;
	} else if (warriorOne.strength > warriorTwo.strength) {
		if (warriorTwo.strength == 0) {
			cout << "He's dead, " << warriorOne.name << endl;
		} else {
			warriorOne.strength -= warriorTwo.strength;
			warriorTwo.strength = 0;
			cout << warriorOne.name << " defeats " << warriorTwo.name << endl;
		}
	} else  if (warriorOne.strength < warriorTwo.strength) {
		if (warriorOne.strength == 0) {
			cout << "He's dead, " << warriorTwo.name << endl;
		} else {
			warriorTwo.strength -= warriorOne.strength;
			warriorOne.strength = 0;
			cout << warriorTwo.name << " defeats " << warriorOne.name << endl;
		}
	}
}

void newLine() {
	cout << endl;
}
