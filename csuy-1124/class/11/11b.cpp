#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <vector>

using namespace std;

class Base {
	public:
		virtual void whereAmI() {
			cout << "Base" << endl;
		}
};

class Derived :public Base {
	public:
		// allows for easier debugging
		// marks that the method overrides the parent class
		void whereAmI() override {
			cout << "Derived" << endl;
		}
};

void foo(Base& thing) {
	thing.whereAmI();
}

int main() {
	Base base;
	foo(base);
	Derived der;
	foo(der);
}
