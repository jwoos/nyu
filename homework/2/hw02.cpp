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
void addWarriors(vector<string> wordsInLine, vector<Warrior>& warriorsVector);
void status(const vector<Warrior>& warriorsVector);
void battle(vector<string> wordsInLine, vector<Warrior>& warriorsVector);
void battleStatus(Warrior& warriorOne, Warrior& warriorTwo);

int main() {
	ifstream warriorsFile("warriors.txt");
	if (!warriorsFile) {
		cerr << "Couldn't open file" << endl;
		exit(1);
	}

	vector<Warrior> warriorsVector;
	string line;

	// loop over each line and depending on the first word, choose an action
	while (getline(warriorsFile, line)) {
		vector<string> wordsInLine = getWords(line);
		if (wordsInLine[0] == "Warrior") {
			addWarriors(wordsInLine, warriorsVector);
		} else if (wordsInLine[0] == "Battle") {
			battle(wordsInLine, warriorsVector);
			cout << endl;
		} else if (wordsInLine[0] == "Status"){
			status(warriorsVector);
			cout << endl;
		}
	}
}

// function to return a list of words on the line
vector<string> getWords(const string& line) {
	vector<string> wordsList;
	string aWord = "";
	for (size_t index = 0; index < line.size(); index++) {
		if (isspace(line[index]) || index == line.size() - 1) {
			wordsList.push_back(aWord);
			aWord = "";
		} else {
			aWord += line[index];
		}
	}

	return wordsList;
}

// add warriors to a vector
void addWarriors(vector<string> wordsInLine, vector<Warrior>& warriorsVector) {
	Warrior aWarrior;
	aWarrior.name = wordsInLine[1];
	aWarrior.strength = stoi(wordsInLine[2]);
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
void battle(vector<string> wordsInLine, vector<Warrior>& warriorsVector) {
	int warriorOneIndex;
	int warriorTwoIndex;
	for (size_t index = 0; index < warriorsVector.size(); index++) {
		if (warriorsVector[index].name == wordsInLine[1]) {
			warriorOneIndex = index;
		} else if (warriorsVector[index].name == wordsInLine[2]) {
			warriorTwoIndex = index;
		}
	}
	battleStatus(warriorsVector[warriorOneIndex], warriorsVector[warriorTwoIndex]);
}

void battleStatus(Warrior& warriorOne, Warrior& warriorTwo) {
	cout << warriorOne.name << " battles " << warriorTwo.name << endl;
	if (warriorOne.strength == warriorTwo.strength) {
		warriorOne.strength = 0;
		warriorTwo.strength = 0;
		cout << warriorOne.name << " and " << warriorTwo.name << " have tied" << endl;
	} else if (warriorOne.strength > warriorTwo.strength) {
		warriorOne.strength -= warriorTwo.strength;
		warriorTwo.strength = 0;
		cout << warriorOne.name << " defeated " << warriorTwo.name << endl;
	} else  if (warriorOne.strength < warriorTwo.strength) {
		warriorTwo.strength -= warriorOne.strength;
		warriorOne.strength = 0;
	}
}

