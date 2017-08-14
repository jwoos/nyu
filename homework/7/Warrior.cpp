#include <iostream>

#include "Warrior.h"
#include "Noble.h"

using namespace std;

namespace WarriorCraft {
	Warrior::Warrior(const string& name, int strength) : name(name), strength(strength), noble(nullptr) {}

	string Warrior::getName() const {
		return name;
	}

	int Warrior::getStrength() const {
		return strength;
	}

	void Warrior::setStrength(int newStrength) {
		strength = newStrength;
	}

	void Warrior::runaway() {
		cout << name << " flees in terror, abandoning his lord, " << noble -> getName() << endl;
		noble -> removeWarrior(*this);
	}

	void Warrior::setNoble(Noble* noblePointer) {
		noble = noblePointer;
	}

	Noble* Warrior::getNoble() const {
		return noble;
	}
};

