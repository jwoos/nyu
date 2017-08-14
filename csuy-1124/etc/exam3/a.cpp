#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class B {
	public:
		B() {
			cout << 3;
		}

		~B() {
			cout << 4;
		}
};

class A {
	public:
		A() {
			cout << 1;
		}

		~A() {
			cout << 2;
		}
	private:
		B b;
};

class C {
	public:
		C() {
			cout << 5;
		}

		~C() {
			cout << 6;
		}
	private:
		A a;
};

int main () {
	C c;
}
