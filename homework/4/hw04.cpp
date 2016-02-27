#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>

using namespace std;

// forward declaration
class Noble;
class Warrior;

// class definition
class Warrior {
	public:
		Warrior(const string& name, int strength) :name(name), strength(strength), noble(nullptr) {}

		// getters and setters
		void setStrength(int newStrength) {
			strength = newStrength;
		}

		int getStrength() const {
			return strength;
		}

		string getName() const {
			return name;
		}

		void setNoble(Noble* noblePointer) {
			noble = noblePointer;
		}

	private:
		string name;
		int strength;
		Noble* noble;
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

			aWarrior.setNoble(this);
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
			aWarrior.setNoble(nullptr);
		}

		void display() const {
			cout << name << " has an army of " << army.size() << endl;
			for (Warrior* warriorPointer : army) {
				cout << "\t" << warriorPointer -> getName() << ": " << warriorPointer -> getStrength() << endl;
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

	private:
		vector<Warrior*> army;
		string name;
};

int main() {
	Noble art("King Arthur");
	Noble lance("Lancelot du Lac");
	Noble jim("Jim");
	Noble linus("Linus Torvalds");
	Noble billie("Bill Gates");

	Warrior cheetah("Tarzan", 10);
	Warrior wizard("Merlin", 15);
	Warrior theGovernator("Conan", 12);
	Warrior nimoy("Spock", 15);
	Warrior lawless("Xena", 20);
	Warrior mrGreen("Hulk", 8);
	Warrior dylan("Hercules", 3);

	jim.hire(nimoy);
	lance.hire(theGovernator);
	art.hire(wizard);
	lance.hire(dylan);
	linus.hire(lawless);
	billie.hire(mrGreen);
	art.hire(cheetah);

	jim.display();
	lance.display();
	art.display();
	linus.display();
	billie.display();

	art.fire(cheetah);
	art.display();

	art.battle(lance);
	jim.battle(lance);
	linus.battle(billie);
	billie.battle(lance);
}
