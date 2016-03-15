#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Person {
	public:
		Person(const string& name) : name(name), alive(true) {}

		string getName() const {
			return name;
		}
	private:
		string name;
		bool alive;
};

class Noble : public Person {
	public:
		Noble(const string& name) : Person(name) {}

		virtual void battle(Noble& enemy) = 0;

		virtual float getStrength() const = 0;

		virtual void setStrength(float newStrength) = 0;
	private:
};

class Protector : public Person {
	public:
		Protector(const string& name, float strength) : Person(name), strength(strength), boss(nullptr) {}

		virtual void declareBattle() const = 0;

		Noble* getBoss() const {
			return boss;
		}

		void setBoss(Noble& aNoble) {
			boss = &aNoble;
		}

		virtual float getStrength() const = 0;

		virtual void setStrength(float newStrength) = 0;
	private:
		float strength;
		Noble* boss;
};

class PersonWithStrengthToFight : public Noble {
	public:
		PersonWithStrengthToFight(const string& name, float strength) : Noble(name), strength(strength) {}

		void setStrength(float newStrength) {
			strength = newStrength;
		}

		float getStrength() const {
			return strength;
		}

		void battle(Noble& enemy) {
		}
	private:
		float strength;
};

class Lord : public Noble {
	public:
		Lord(const string& name) : Noble(name) {}

		void battle(Noble*& enemy) {
			float selfTotalStrength;
			float enemyTotalStrength;
			float ratio;

			// get strength of the instance
			selfTotalStrength = getStrength();
			// strength of the enemy's instance
			enemyTotalStrength = enemy -> getStrength();

			cout << this -> getName() << " battles " << enemy -> getName() << endl;

			if (enemyTotalStrength == selfTotalStrength) {
				if (enemyTotalStrength == 0 && selfTotalStrength == 0) {
					cout << "Oh NO! They're both dead! Yuck!" << endl;
				} else {
					// ratio is set so that the loser is on the top always
					ratio = selfTotalStrength / enemyTotalStrength;
					setStrength(ratio);
					enemy -> setStrength(ratio);

					cout << "Mutual annihilation: " << this -> getName() << " and " << enemy -> getName() << " die at each other's hands" << endl;
				}
			} else if (selfTotalStrength > enemyTotalStrength) {
				if (enemyTotalStrength == 0) {
					cout << "He's dead, " << this -> getName() << endl;
				} else {
					ratio = enemyTotalStrength / selfTotalStrength;

					setStrength(ratio);
					enemy -> setStrength(1);

					cout << this -> getName() << " defeats " << enemy -> getName() << endl;
				}
			} else if (selfTotalStrength < enemyTotalStrength) {
				if (selfTotalStrength == 0) {
					cout << "He's dead, " << enemy -> getName() << endl;
				} else {
					ratio = selfTotalStrength / enemyTotalStrength;

					setStrength(1);
					enemy -> setStrength(ratio);

					cout << enemy -> getName() << " defeats " << this -> getName() << endl;
				}
			}

			cout << endl;
		}

		float getStrength() const {

			float totalStrength = 0;

			for (Protector* warriorPofloater : army) {
				totalStrength += warriorPofloater -> getStrength();
			}

			return totalStrength;
		}

		// sets the strength of each warrior based on the ratio
		void setStrength(float ratio) {
			for (Protector*& warriorPofloater : army) {
				float oldStrength = warriorPofloater -> getStrength();
				warriorPofloater -> setStrength(oldStrength - (oldStrength * ratio));
			}
		}
	private:
		vector<Protector*> army;
};

class Wizard : public Protector {
	public:
		Wizard(const string& name, float strength) : Protector(name, strength) {}

		void declareBattle() const {
			cout << "POOF!";
		}
	private:
};

class Warrior : public Protector {
	public:
		Warrior(const string& name, float strength) : Protector(name, strength) {}

		virtual void declareBattle() const {
			cout << " " << this -> getName() << " says: Take that in the name of my lord, " << this -> getBoss() -> getName() << endl;
		}
	private:
};

class Archer : public Warrior {
	public:
		Archer(const string& name, float strength) : Warrior(name, strength) {}

		void declarebattle() const {
			cout << "TWANG!";
			Protector::declareBattle();
		}
	private:
};

class Swordsman : public Warrior {
	public:
		Swordsman(const string& name, float strength) : Warrior(name, strength) {}

		void declarebattle() const {
			cout << "CLANG!";
			Protector::declareBattle();
		}
	private:
};

int main() {
	//Lord sam("Sam");
	//Archer samantha("Samantha", 200);
	//sam.hires(samantha);
	//Lord joe("Joe");
	//PersonWithStrengthToFight randy("Randolf the Elder", 250);
	//joe.battle(randy);
	//joe.battle(sam);
	//Lord janet("Janet");
	//Swordsman hardy("TuckTuckTheHardy", 100);
	//Swordsman stout("TuckTuckTheStout", 80);
	//janet.hires(hardy);
	//janet.hires(stout);
	//PersonWithStrengthToFight barclay("Barclay the Bold", 300);
	//janet.battle(barclay);
	//janet.hires(samantha);
	//Archer pethora("Pethora", 50);
	//Archer thora("Thorapleth", 60);
	//Wizard merlin("Merlin", 150);
	//janet.hires(pethora);
	//janet.hires(thora);
	//sam.hires(merlin);
	//janet.battle(barclay);
	//sam.battle(barclay);
	//joe.battle(barclay);
}
