#include <iostream>
#include <string>
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
				cout << "Yes!" << endl;
				// need to do dereference first since accessor has a higher priority than dereference
				cout << "spouse name: " << (*spouse).name << endl;
				// operator to do the above
				cout << "spouse name: " << spouse -> name << endl;
			} else {
				cout << "No!" << endl;
			}
		}

		void marries(Person& betrothed) {
			spouse = &betrothed;
			// pointed to self
			betrothed.spouse = this;

			cout << spouse << endl;
			cout << this << endl;
		}

	private:
		string name;
		Person* spouse;
		//Person& spouse;
};

int main() {
	Person john("John");
	Person mary("Mary");
	john.display();
	mary.display();

	john.marries(mary);

	john.display();

	cout << endl;

	int x = 17;
	cout << "x: " << x << endl;
	// get address in memory | address-of operator
	cout << "&x: " << &x << endl;

	cout << endl;

	// int pointer
	int* xAddress = &x;
	cout << "xAddress: " << xAddress << endl;
	// get the value it's pointing to | dereference operator
	cout << "*xAddress: " << *xAddress << endl;

	cout << endl;

	// setting using a pointer
	*xAddress = 10;
	cout << "*xAddress: " << *xAddress << endl;
	cout << "x: " << x << endl;
}
