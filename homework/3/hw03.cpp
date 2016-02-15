#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <vector>
using namespace std;

// POD
struct Weapon {
	Weapon(string name, int strength) :name(name), strength(strength) {}
	string name;
	int strength;
};

class Warrior {
	public:
		// initializes a Weapon as well along with the Warrior itself
		Warrior(string name, string weaponName,int weaponStrength) :name(name), warriorWeapon(weaponName, weaponStrength) {}

		// access name from outside; getter
		string getName() const {
			return name;
		}

		// display name, weapon, and strength
		void status() const {
			cout << "Warrior: " << name << ", weapon: " << warriorWeapon.name << ", " << warriorWeapon.strength << endl;
		}

		// change weapon strength; setter
		void setWeaponStrength(int newStrength) {
			warriorWeapon.strength = newStrength;
		}

		// get weapon strength; getter
		int getWeaponStrength() const {
			return warriorWeapon.strength;
		}
	private:
		string name;
		Weapon warriorWeapon;
};

void addWarrior(vector<Warrior>& warriorsVector, const string& warriorName, const string& weaponName, int weaponStrength);
void battle(vector<Warrior>& warriorsVector, const string& warriorOneName, const string& warriorTwoName);
void battleStatus(Warrior& warriorOne, Warrior& warriorTwo);
void status(vector<Warrior>& warriorsVector);
void newLine();

int main() {
	ifstream warriorsFile("warriors.txt");
	if (!warriorsFile) {
		cerr << "Couldn't open file" << endl;
		exit(1);
	}

	vector<Warrior> warriorsVector;
	string command;

	while (warriorsFile >> command) {
		if (command == "Status") {
			status(warriorsVector);
			newLine();
		} else if (command == "Warrior") {
			string warriorName, weaponName;
			int weaponStrength;
			warriorsFile >> warriorName >> weaponName >> weaponStrength;
			addWarrior(warriorsVector, warriorName, weaponName, weaponStrength);
			newLine();
		} else if (command == "Battle") {
			string warriorOneName, warriorTwoName;
			warriorsFile >> warriorOneName >> warriorTwoName;
			battle(warriorsVector, warriorOneName, warriorTwoName);
			newLine();
		}
	}
}

void addWarrior(vector<Warrior>& warriorsVector, const string& warriorName, const string& weaponName, int weaponStrength) {
	// create a Warrior using the name, weapon name and weapon strength
	Warrior aWarrior(warriorName, weaponName, weaponStrength);

	warriorsVector.push_back(aWarrior);
}

void battle(vector<Warrior>& warriorsVector, const string& warriorOneName, const string& warriorTwoName) {
	size_t warriorOneIndex, warriorTwoIndex;

	// find the index of the specific warriors in the vector to use for battling
	for (size_t index = 0; index < warriorsVector.size(); index++) {
		if (warriorsVector[index].getName() == warriorOneName) {
			warriorOneIndex = index;
		} else if (warriorsVector[index].getName() == warriorTwoName) {
			warriorTwoIndex = index;
		}
	}

	battleStatus(warriorsVector[warriorOneIndex], warriorsVector[warriorTwoIndex]);
}

void battleStatus(Warrior& warriorOne, Warrior& warriorTwo) {
	string warriorOneName = warriorOne.getName();
	string warriorTwoName = warriorTwo.getName();
	int warriorOneStrength = warriorOne.getWeaponStrength();
	int warriorTwoStrength = warriorTwo.getWeaponStrength();

	cout << warriorOneName << " battles " << warriorTwoName << endl;

	if (warriorOneStrength == warriorTwoStrength) {
		if (warriorOneStrength == 0 && warriorTwoStrength == 0) {
			cout << "Oh NO! They're both dead! Yuck!" << endl;
		} else {
			warriorOne.setWeaponStrength(0);
			warriorTwo.setWeaponStrength(0);

			cout << "Mutual annihilation: " << warriorOneName << " and " << warriorTwoName << " die at each other's hands" << endl;
		}

	} else if (warriorOneStrength > warriorTwoStrength) {
		if (warriorTwoStrength == 0) {
			cout << "He's dead, " << warriorOneName << endl;
		} else {
			warriorOne.setWeaponStrength(warriorOneStrength - warriorTwoStrength);
			warriorTwo.setWeaponStrength(0);

			cout << warriorOneName << " defeats " << warriorTwoName << endl;
		}
	} else if (warriorOneStrength < warriorTwoStrength) {
		if (warriorOneStrength == 0) {
			cout << "He's dead, " << warriorTwoName << endl;
		} else {
			warriorTwo.setWeaponStrength(warriorTwoStrength - warriorOneStrength);
			warriorOne.setWeaponStrength(0);

			cout << warriorTwoName << " defeats " << warriorOneName << endl;
		}
	}
}

void status(vector<Warrior>& warriorsVector) {
	cout << "There are: " << warriorsVector.size() << " warriors" << endl;

	// use the status method to print everyone's status
	for (Warrior aWarrior : warriorsVector) {
		aWarrior.status();
	}
}

void newLine() {
	cout << endl;
}
