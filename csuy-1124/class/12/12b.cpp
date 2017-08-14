#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Base {
	public:
		Base() {
			this -> foo();
		}

		virtual void foo() const {
			cout << "Base" << endl;
		}
};

class Derived : public Base {
	public:
		// in a constructor polymorphism is off
		Derived(int n) : x(n) {}

		void foo() const {
			cout << "Derived: x == " << x << endl;
		}

	private:
		int x;
};

int main() {
	Base base();
	Derived derived(10);
}
