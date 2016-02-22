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

int main() {
	ifstream ifs("people.txt");
	if (!ifs) {
		exit(1);
	}
	vector<Person*> poly;
	vector<Person*> brooklyn;

	string name;
	while (ifs >> name) {
		// use the heap as the local variable would use the same memory for each iteration
		// using the heap allows it to have a different address each time
		Person* personPointer = new Person(name);
		poly.push_back(personPointer);
	}

	for (Person* personPointer : poly) {
		cout << personPointer << endl;
		personPointer -> display();
	}

	double* dp = new double(3.14);
	*dp = 2.718;
	// doing the below would create a memory leak as the address to the original variable is lost but it would still remain instantiated
	//dp = new double(0.25);
	// however doing a delete would clear it the address
	// the address remains assigned to the variable
	delete dp;
	cout << dp << endl;


	for (Person*& pp : poly) {
		delete pp;
		pp = nullptr;
	}
	poly.clear();
}
