#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

// a person has a name and can be alive or dead
// universal methods and attributes
class Person {
	public:
		Person(const string& name) : name(name), alive(true) {}

		virtual float getStrength() const = 0;

		virtual void setStrength(float newStrength) = 0;

		string getName() const {
			return name;
		}

		bool live() const {
			return alive;
		}

		void die() {
			alive = false;
		}
	private:
		string name;
		bool alive;
};

// nobles inherit from person
class Noble : public Person {
	public:
		Noble(const string& name) : Person(name) {}

		virtual void battle(Noble& enemy) = 0;

		// actual battle method was split up to allow reuse in derived classes
		void declareBattle(Noble*& enemy) {
			cout << this -> getName() << " battles " << enemy -> getName() << endl;
		}

		// battling and deciding strength/death
		virtual void engageInBattle(Noble*& enemy) {
			string selfName = this -> getName();
			string enemyName = enemy -> getName();

			float selfTotalStrength = getStrength();
			float enemyTotalStrength = enemy -> getStrength();

			bool selfAlive = this -> live();
			bool enemyAlive = enemy -> live();

			if (enemyTotalStrength == selfTotalStrength) {
				if (!enemyAlive && !selfAlive) {
					cout << "Oh NO! They're both dead! Yuck!" << endl;
				} else {
					// since both Lords and PersonWithStrengthToFight have setStrength() and getStrength() that does their own thing I don't have to worry about the difference in their sources of strength or how differences are calculated here
					setStrength(enemyTotalStrength);
					enemy -> setStrength(selfTotalStrength);

					cout << "Mutual annihilation: " << selfName << " and " << enemyName << " die at each other's hands" << endl;
				}
			} else if (selfTotalStrength > enemyTotalStrength) {
				if (!enemyAlive) {
					cout << "He's dead, " << selfName << endl;
				} else {
					setStrength(enemyTotalStrength);
					enemy -> setStrength(selfTotalStrength);
					enemy -> die();

					cout << selfName << " defeats " << enemyName << endl;
				}
			} else if (selfTotalStrength < enemyTotalStrength) {
				if (!selfAlive) {
					cout << "He's dead, " << enemyName << endl;
				} else {
					setStrength(enemyTotalStrength);
					enemy -> setStrength(selfTotalStrength);
					this -> die();

					cout << enemyName << " defeats " << selfName << endl;
				}
			}

			cout << endl;
		}
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

		float getStrength() const {
			return strength;
		};

		void setStrength(float newStrength) {
			strength = newStrength;
		};
	private:
		float strength;
		Noble* boss;
};

class PersonWithStrengthToFight : public Noble {
	public:
		PersonWithStrengthToFight(const string& name, float strength) : Noble(name), strength(strength) {}

		void setStrength(float enemyStrength) {
			if (enemyStrength > strength || enemyStrength == strength) {
				strength = 0;
			} else if (enemyStrength < strength) {
				strength -= enemyStrength;
			}
		}

		float getStrength() const {
			return strength;
		}

		// making use of parent methods
		void battle(Noble& enemy) {
			Noble* enemyP = &enemy;

			// normal battle
			declareBattle(enemyP);
			engageInBattle(enemyP);
		}
	private:
		float strength;
};

class Lord : public Noble {
	public:
		Lord(const string& name) : Noble(name) {}

		float getStrength() const {
			float totalStrength = 0;

			for (Protector* warriorPofloater : army) {
				totalStrength += warriorPofloater -> getStrength();
			}

			return totalStrength;
		}

		// sets the strength of each warrior based on the ratio
		void setStrength(float enemyStrength) {
			float ratio;

			if (enemyStrength > getStrength() || enemyStrength == getStrength()) {
				ratio = 1;
			} else if (enemyStrength < getStrength()) {
				ratio = enemyStrength / getStrength();
			}

			for (Protector*& warriorPointer : army) {
				float oldStrength = warriorPointer -> getStrength();
				warriorPointer -> setStrength(oldStrength - (oldStrength * ratio));
			}
		}

		void hires(Protector& aProtector) {
			if (aProtector.getBoss() == nullptr && this -> live() && aProtector.live()) {
				aProtector.setBoss(*this);
				army.push_back(&aProtector);
			}
		}

		void fires(Protector& aProtector) {
			size_t protectorIndex;

			for (size_t index = 0; index < army.size(); index++) {
				if (army[index] -> getName() == aProtector.getName()) {
					protectorIndex = index;
					break;
				}
			}

			cout << aProtector.getName() << " , you're fired -- " << this -> getName() << endl;

			army[protectorIndex] = army[army.size() - 1];
			army.pop_back();
		}

		void battle(Noble& enemy) {
			// battle but it also declares battle for each protector in between
			Noble* enemyP = &enemy;
			declareBattle(enemyP);

			if (this -> live()) {
				for (size_t i = 0; i < army.size(); i++) {
					if (army[i] -> live()) {
						army[i] -> declareBattle();
					}
				}
			}

			engageInBattle(enemyP);
		}

		void engageInBattle(Noble*& enemy) {
			Noble::engageInBattle(enemy);

			bool selfAlive = this -> live();
			bool enemyAlive = enemy -> live();

			float selfTotalStrength = getStrength();
			float enemyTotalStrength = enemy -> getStrength();

			if (enemyTotalStrength == selfTotalStrength) {
				if (enemyAlive && selfAlive) {
					for (size_t i = 0; i < army.size(); i++) {
						army[i] -> die();
					}
				}
			} else if (selfTotalStrength < enemyTotalStrength) {
				if (selfAlive) {
					for (size_t i = 0; i < army.size(); i++) {
						army[i] -> die();
					}
				}
			}
		}
	private:
		vector<Protector*> army;
};

class Wizard : public Protector {
	public:
		Wizard(const string& name, float strength) : Protector(name, strength) {}

		void declareBattle() const {
			cout << "POOF!" << endl;
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

		void declareBattle() const {
			cout << "TWANG!";
			Warrior::declareBattle();
		}
	private:
};

class Swordsman : public Warrior {
	public:
		Swordsman(const string& name, float strength) : Warrior(name, strength) {}

		void declareBattle() const {
			cout << "CLANG!";
			Warrior::declareBattle();
		}
	private:
};

int main() {
	Lord sam("Sam");
	Archer samantha("Samantha", 200);
	sam.hires(samantha);
	Lord joe("Joe");
	PersonWithStrengthToFight randy("Randolf the Elder", 250);
	joe.battle(randy);
	joe.battle(sam);
	Lord janet("Janet");
	Swordsman hardy("TuckTuckTheHardy", 100);
	Swordsman stout("TuckTuckTheStout", 80);
	janet.hires(hardy);
	janet.hires(stout);
	PersonWithStrengthToFight barclay("Barclay the Bold", 300);
	janet.battle(barclay);
	janet.hires(samantha);
	Archer pethora("Pethora", 50);
	Archer thora("Thorapleth", 60);
	Wizard merlin("Merlin", 150);
	janet.hires(pethora);
	janet.hires(thora);
	sam.hires(merlin);
	janet.battle(barclay);
	sam.battle(barclay);
	joe.battle(barclay);
}
