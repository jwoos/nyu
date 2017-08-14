#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

// copy control

class Foo {
	public:
		Foo(int x) {
			p = new int(x);
		}

		// copy constructor
		// deep copy
		Foo(const Foo& rhs) {
			p = new int(*rhs.p);
		}

		Foo& operator=(const Foo& rhs) {
			// 0. check for self assignment
			if (this != &rhs) {
				// 1. free up the left hand side's resources
				delete p;
				// 2. allocate and copy
				p = new int(*rhs.p);
			}
			return *this;
		}

		void display() {
			cout << *p << endl;
		}

		void setValue(int val) {
			*p = val;
		}

		// destructor
		~Foo() {
			delete p;
		}
	private:
		int* p;
};

void doNothing(Foo anotherFoo) {
	anotherFoo.setValue(42);
}

void simpleFunc() {
	Foo aFoo(17);
	aFoo.display();
	// a copy of Foo is passed to doNothing()
	// the copy's pointer points to the same place
	// leaves the original pointer dangling as the destructor gets rid of it after doNothing()
	// this creates an issue at the end of simpleFunc as the contents of the memory already got deleted
	doNothing(aFoo);
	// at the end of this scope the destructor wil be called

	// below two are the same; uses copy constructor
	// Foo yaFoo(aFoo);
	Foo yaFoo = aFoo;

	// not using copy constructor
	Foo thirdFoo(6);
	aFoo = thirdFoo;
}

int main() {
	simpleFunc();
}
