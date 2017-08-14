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

		bool marries(Person& betrothed) {
			if (spouse == nullptr) {
				spouse = &betrothed;
				betrothed.spouse = this;
				return true;
			}
			return false;
		}

	private:
		string name;
		Person* spouse;
};

class Pet {
	public:
		Pet(const string& name) :name(name) {}

		virtual void display() const {
			cout << "Pet" << endl;
		}
	private:
		string name;
};

// inherits from organism publicly
class Cat : public Pet {
	public:
		Cat(const string& name) :Pet(name) {}
	private:
};

class Slug : public Pet {
	public:
	private:
};

class Roach : public Pet {
	public:
		void display() const {
			cout << "Roach" << endl;
		}
	private:
};

int main() {
	Pet aPet();
	Cat kitty("Felix");
	Roach roach;
	Slug sluggo;

	vector<Pet> menagerie;
	menagerie.push_back(aPet);
	menagerie.push_back(kitty);
	menagerie.push_back(roach);
	menagerie.push_back(sluggo);

	for (Pet organism : menagerie) {
		organism.display();
	}
	// the above will experience another slicing problem

	cout << endl;

	vector<Pet*> menageriePointer;
	menageriePointer.push_back(&aPet);
	menageriePointer.push_back(&kitty);
	menageriePointer.push_back(&roach);
	menageriePointer.push_back(&sluggo);

	for (Pet* organismPointer : menageriePointer) {
		organismPointer -> display();
	}
}
