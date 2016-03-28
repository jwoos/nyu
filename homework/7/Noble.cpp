#include "Warrior.h"
#include "Noble.h"

using namespace std;

namespace WarriorCraft {
	Noble::Noble(const string& name) : name(name) {}

	ostream& operator<<(ostream& output, const Noble& noble) {
		output << noble.name << " has an army of " << noble.army.size() << endl;

		for (int i = 0; i < noble.army.size(); i++) {
			output << "\t" << noble.army[i] -> getName() << ": " << noble.army[i] -> getStrength() << endl;
		}

		return output;
	}

	string Noble::getName() const {
		return name;
	}

	void Noble::hire(Warrior& aWarrior) {
		army.push_back(&aWarrior);

		if (aWarrior.getNoble() == nullptr) {
			aWarrior.setNoble(this);
		} else {
			cout << "The warrior already has a noble!" << endl;
		}
	}

	void Noble::fire(Warrior& aWarrior) {
		int check = removeWarrior(aWarrior);

		if (check != -1) {
			cout << aWarrior.getName() << ", you're fired -- " << name << endl;
		}
	}

	float Noble::getArmyStrength() const {
		float totalStrength = 0;

		for (Warrior* warriorPointer : army) {
			totalStrength += warriorPointer -> getStrength();
		}

		return totalStrength;
	}

	void Noble::setArmyStrength(float ratio) {
		for (Warrior*& warriorPointer : army) {
			float oldStrength = warriorPointer -> getStrength();
			warriorPointer -> setStrength(oldStrength - (oldStrength * ratio));
		}
	}
	void Noble::battle(Noble& enemy) {
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

	int Noble::removeWarrior(Warrior& aWarrior) {
		int warriorIndex = -1;

		for (int index = 0; index < army.size(); index++) {
			if (army[index] -> getName() == aWarrior.getName()) {
				warriorIndex = index;
			}
		}

		if (warriorIndex == -1) {
			cout << "Warrior not found!" << endl;
		} else {
			army[warriorIndex] = army[army.size() - 1];
			army.pop_back();
			aWarrior.setNoble(nullptr);
		}

		return warriorIndex;
	}
};
