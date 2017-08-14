#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <vector>

using namespace std;

class Person {
	public:
		Person(const string& name) :name(name), spouse(nullptr) {}

		void display(ostream& os = cout) const {
			cout << "Name: " << name << endl;
			cout << "Is married? " << endl;
			if (spouse != nullptr) {
				os << "Yes!" << "spouse name: " << spouse -> name << endl;
			} else {
				os << "No!" << endl;
			}

			cout << endl;
		}

		void marries(Person& betrothed) {
			spouse = &betrothed;
			betrothed.spouse = this;
		}

	private:
		string name;
		Person* spouse;
};

class Organism {
	public:
		void eat() {

		}

		// enable polymorphism
		// in order to allow polymorphism, the object in question has to be passed by reference and not by value
		// if passed by value, it'd just make a copy as the parent class
		virtual void display() const {
			cout << "Organism" << endl;
		}
};

// inherits from organism publicly
class Cat : public Organism {
	public:
	private:
};

class Slug : public Organism {
	public:
	private:
};

class Roach : public Organism {
	public:
		void display() const {
			cout << "Roach" << endl;
		}
	private:
};

// principle of substitutibility
// allows a function expecting a base class to take a subclass
void display(const Organism& anOrganism) {
	anOrganism.display();
}

void foo(const Person& fred) {
	//Person* p = &fred;
	const Person* p = &fred;
	p -> display();
}

int main() {
	int x = 10;
	// prevents  x from being changed
	const int* constPtr = &x;
	// prevents the pointer from being pointed at anything else
	int* const anotherPtr = &x;

	cout << constPtr << endl;
	cout << anotherPtr << endl;

	Organism anOrganism;
	anOrganism.display();
	display(anOrganism);

	Cat kitty;
	kitty.display();
	display(kitty);

	Roach roach;
	roach.display();
	// if a function is overridden, it'll use the parent method unless specified otherwise
	// if specified, it'll put off determining the type until runtime
	// polymorphism
	// the change has to be made on the parent class
	display(roach);


	// slicing problem when setting parent class variable to subclass object and when passing by value
}
