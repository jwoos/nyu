#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class Pet {
	public:
		Pet(const string& name) :name(name) {}

		virtual void display() const {
			cout << "Pet: " << name << endl;
		}
	protected:
		string getName() const {
			return name;
		}
	private:
		string name;
};

class Cat : public Pet {
	public:
		Cat(const string& name) :Pet(name) {}

		void display() const {
			cout << "Cat: ";
			//Pet::display();
			display();
		}
	private:
};

class Dog : public Pet {
	public:
		Dog(const string& name) :Pet(name) {}
	private:
};

int main() {
	Cat felix("Felix");
	// protected doesn't allow this
	// cout << felix.getName();
	felix.display();

	Dog fido("Fido");
}
