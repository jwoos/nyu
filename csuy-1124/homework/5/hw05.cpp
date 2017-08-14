#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <fstream>

using namespace std;

// forward declaration
class Noble;
class Warrior;

class Warrior {
	public:
		Warrior(const string& name, int strength) :name(name), strength(strength) {}

		void setStrength(int newStrength) {
			strength = newStrength;
		}

		int getStrength() const {
			return strength;
		}

		string getName() const {
			return name;
		}

		void display() const {
			cout << name << ": " << strength << endl;
		}

	private:
		string name;
		int strength;
};

class Noble {
	public:
		Noble(const string& name) :name(name)  {}

		void battle(Noble& enemy) {
			float selfTotalStrength;
			float enemyTotalStrength;
			float ratio;

			// get strength of the instance
			selfTotalStrength = getArmyStrength();
			// strength of the enemy's instance
			enemyTotalStrength = enemy.getArmyStrength();

			cout << name << " battles " << enemy.getName() << endl;

			if (enemyTotalStrength == selfTotalStrength) {
				if (enemyTotalStrength == 0 && selfTotalStrength == 0) {
					cout << "Oh NO! They're both dead! Yuck!" << endl;
				} else {
					// ratio is set so that the loser is on the top always
					ratio = selfTotalStrength / enemyTotalStrength;
					setArmyStrength(ratio);
					enemy.setArmyStrength(ratio);

					cout << "Mutual annihilation: " << name << " and " << enemy.getName() << " die at each other's hands" << endl;
				}
			} else if (selfTotalStrength > enemyTotalStrength) {
				if (enemyTotalStrength == 0) {
					cout << "He's dead, " << name << endl;
				} else {
					ratio = enemyTotalStrength / selfTotalStrength;

					setArmyStrength(ratio);
					enemy.setArmyStrength(1);

					cout << name << " defeats " << enemy.getName() << endl;
				}
			} else if (selfTotalStrength < enemyTotalStrength) {
				if (selfTotalStrength == 0) {
					cout << "He's dead, " << enemy.getName() << endl;
				} else {
					ratio = selfTotalStrength / enemyTotalStrength;

					setArmyStrength(1);
					enemy.setArmyStrength(ratio);

					cout << enemy.getName() << " defeats " << name << endl;
				}
			}

			cout << endl;
		}

		void hire(Warrior& aWarrior) {
			army.push_back(&aWarrior);
		}

		void fire(Warrior& aWarrior) {
			size_t warriorIndex;

			for (size_t index = 0; index < army.size(); index++) {
				if (army[index] -> getName() == aWarrior.getName()) {
					warriorIndex = index;
				}
			}

			cout << aWarrior.getName() << ", you're fired -- " << name << endl;

			army[warriorIndex] = army[army.size() - 1];
			army.pop_back();
		}

		void display() const {
			cout << name << " has an army of " << army.size() << endl;
			for (Warrior* warriorPointer : army) {
				cout << "\t";
				warriorPointer -> display();
			}
			cout << endl;
		}

		// name getter
		string getName() const {
			return name;
		}

		// iterate over army and add them to return total strength
		float getArmyStrength() const {
			float totalStrength = 0;

			for (Warrior* warriorPointer : army) {
				totalStrength += warriorPointer -> getStrength();
			}

			return totalStrength;
		}

		// sets the strength of each warrior based on the ratio
		void setArmyStrength(float ratio) {
			for (Warrior*& warriorPointer : army) {
				float oldStrength = warriorPointer -> getStrength();
				warriorPointer -> setStrength(oldStrength - (oldStrength * ratio));
			}
		}

		vector<Warrior*> getArmy() const {
			return army;
		}

	private:
		vector<Warrior*> army;
		string name;
};

// function prototypes
void status(vector<Noble*>& nobles, vector<Warrior*>& warriors);
void clear(vector<Noble*>& nobles, vector<Warrior*>& warriors);
void addNoble(vector<Noble*>& nobles, const string& name);
void addWarrior(vector<Warrior*>& warriors, const string& name, int strength);
void hire(vector<Noble*>& nobles, vector<Warrior*>& warriors, const string& nobleName, const string& warriorName);
void fire(vector<Noble*>& nobles, vector<Warrior*>& warriors, const string& nobleName, const string& warriorName);
void battle(vector<Noble*>& nobles, const string& nobleOne, const string& nobleTwo);

int main() {
	fstream inputFile("nobleWarriors.txt");
	if (!inputFile) {
		cout << "Couldn't read file" << endl;
		exit(1);
	}

	vector<Noble*> nobles;
	vector<Warrior*> unemployedWarriors;

	string command;
	while (inputFile >> command) {
		if (command == "Noble") {
			string name;
			inputFile >> name;

			addNoble(nobles, name);
		} else if (command == "Warrior") {
			string name;
			int strength;
			inputFile >> name >> strength;

			addWarrior(unemployedWarriors, name, strength);
		} else if (command == "Hire") {
			string nobleName;
			string warriorName;
			inputFile >> nobleName >> warriorName;

			hire(nobles, unemployedWarriors, nobleName, warriorName);
		} else if (command == "Fire") {
			string nobleName;
			string warriorName;
			inputFile >> nobleName >> warriorName;

			fire(nobles, unemployedWarriors, nobleName, warriorName);
		} else if (command == "Battle") {
			string nobleOne;
			string nobleTwo;
			inputFile >> nobleOne >> nobleTwo;

			battle(nobles, nobleOne, nobleTwo);
		} else if (command == "Status") {
			status(nobles, unemployedWarriors);
		} else if (command == "Clear") {
			clear(nobles, unemployedWarriors);
		} else {
			cout << "Invalid command!" << endl;
		}
	}

	inputFile.close();
}

void status(vector<Noble*>& nobles, vector<Warrior*>& warriors) {
	cout << "Status" << endl;
	cout << "======" << endl;
	cout << "Nobles:" << endl;
	if (nobles.size() != 0) {
		for (Noble* noblePointer : nobles) {
			noblePointer -> display();
		}
	} else {
		cout << "NONE" << endl;
	}

	cout << "Unemployed Warriors:" << endl;
	if (warriors.size() != 0) {
		for (Warrior* warriorPointer : warriors) {
			warriorPointer -> display();
		}
	} else {
		cout << "NONE" << endl;
	}
}

void clear(vector<Noble*>& nobles, vector<Warrior*>& warriors) {
	// delete all nobles
	if (nobles.size() > 0) {
		for (Noble*& noblePointer : nobles) {
			vector<Warrior*> army = noblePointer -> getArmy();
			// iterate over each warrior of a noble and delete it
			if (army.size() > 0) {
				for (Warrior* warriorPointer : army) {
					delete warriorPointer;
				}
			}
			delete noblePointer;
		}
	}

	// deletes all warriors who are not hired
	if (warriors.size() > 0) {
		for (Warrior*& warriorPointer : warriors) {
			delete warriorPointer;
		}
	}

	// clear vectors
	nobles.clear();
	warriors.clear();
}

void addNoble(vector<Noble*>& nobles, const string& name) {
	bool err = false;

	// if a noble exists with that name already, error out
	if (nobles.size() > 0) {
		for (Noble* noblePointer : nobles) {
			if (noblePointer -> getName() == name) {
				err = true;
				break;
			}
		}
	}

	if (err) {
		cout << "A noble with the name " << name << " already exists!" << endl;
		cout << "A new noble was not created" << endl;
	} else {
		// make noble
		nobles.push_back(new Noble(name));
	}
}

void addWarrior(vector<Warrior*>& warriors, const string& name, int strength) {
	bool err = false;

	if (warriors.size() > 0) {
		for (Warrior* warriorPointer : warriors) {
			// if a warrior exists with that name already, error out
			if (warriorPointer -> getName() == name) {
				err = true;
				break;
			}
		}
	}

	if (err) {
		cout << "A warrior with the name " << name << " already exists!" << endl;
		cout << "A new warrior was not created" << endl;
	} else {
		warriors.push_back(new Warrior(name, strength));
	}
}

void hire(vector<Noble*>& nobles, vector<Warrior*>& warriors, const string& nobleName, const string& warriorName) {
	int nobleIndex;
	int warriorIndex;
	// if either or both don't exist it'll error
	bool nobleError = true;
	bool warriorError = true;

	// find noble index
	if (nobles.size() > 0) {
		for (size_t i = 0; i < nobles.size(); i++) {
			if (nobles[i] -> getName() == nobleName) {
				nobleIndex = i;
				// found, so no error
				nobleError = false;
				break;
			}
		}
	}

	// find warrior index
	if (warriors.size() > 0) {
		for (size_t i = 0; i < warriors.size(); i++) {
			if (warriors[i] -> getName() == warriorName) {
				warriorIndex = i;
				// found, so no error
				warriorError = false;
				break;
			}
		}
	}

	if (nobleError && warriorError) {
		cout << "Noble with name " << nobleName << " does not exist!" << endl;
		cout << "Warrior with name " << warriorName << " does not exist!" << endl;
	} else if (warriorError) {
		cout << "Warrior with name " << warriorName << " does not exist!" << endl;
	} else if (nobleError) {
		cout << "Noble with name " << nobleName << " does not exist!" << endl;
	} else {
		nobles[nobleIndex] -> hire(*warriors[warriorIndex]);
		// get rid of the warrior from the unemployed vector
		warriors[warriorIndex] = warriors[warriors.size() - 1];
		warriors.pop_back();
	}
}

void fire(vector<Noble*>& nobles, vector<Warrior*>& warriors, const string& nobleName, const string& warriorName) {
	int warriorIndex;
	int nobleIndex;
	bool nobleError = true;
	bool warriorError = true;
	vector<Warrior*> army;

	// find noble index
	if (nobles.size() > 0) {
		for (size_t i = 0; i < nobles.size(); i++) {
			if (nobles[i] -> getName() == nobleName) {
				nobleIndex = i;
				// found, so no error
				nobleError = false;
				break;
			}
		}

		// get the noble's hired warriors
		army = nobles[nobleIndex] -> getArmy();
	}


	// find warrior index
	if (army.size() > 0) {
		for (size_t i = 0; i < army.size(); i++) {
			if (army[i] -> getName() == warriorName) {
				warriorIndex = i;
				// found, so no error
				warriorError = false;
				break;
			}
		}
	}

	if (nobleError && warriorError) {
		cout << "Noble with name " << nobleName << " does not exist!" << endl;
		cout << "Warrior with name " << warriorName << " does not exist!" << endl;
	} else if (warriorError) {
		cout << "Warrior with name " << warriorName << " does not exist!" << endl;
	} else if (nobleError) {
		cout << "Noble with name " << nobleName << " does not exist!" << endl;
	} else {
		// instead of changing class to accept pointers, just derefernce it
		nobles[nobleIndex] -> fire(*army[warriorIndex]);
		// add to unemployed
		warriors.push_back(army[warriorIndex]);
	}
}

void battle(vector<Noble*>& nobles, const string& nobleOne, const string& nobleTwo) {
	int nobleOneIndex;
	int nobleTwoIndex;
	bool nobleOneError = true;
	bool nobleTwoError = true;

	// find noble index
	// no break to allow it to find both
	if (nobles.size() > 0) {
		for (size_t i = 0; i < nobles.size(); i++) {
			if (nobles[i] -> getName() == nobleOne) {
				nobleOneIndex = i;
				// found, so no error
				nobleOneError = false;
			} else if (nobles[i] -> getName() == nobleTwo) {
				nobleTwoIndex = i;
				// found, so no error
				nobleTwoError = false;
			}
		}
	}

	if (nobleOneError && nobleTwoError) {
		cout << "Noble with name " << nobleOne << " does not exist!" << endl;
		cout << "Noble with name " << nobleTwo << " does not exist!" << endl;
	} else if (nobleOneError) {
		cout << "Noble with name " << nobleOne << " does not exist!" << endl;
	} else if (nobleTwoError) {
		cout << "Noble with name " << nobleTwo << " does not exist!" << endl;
	} else {
		nobles[nobleOneIndex] -> battle(*nobles[nobleTwoIndex]);
	}
}
