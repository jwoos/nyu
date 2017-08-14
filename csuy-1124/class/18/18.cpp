#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Base {
	public:
		Base() {
			cout << "Base()" << endl;
		}

		Base(const Base& rhs) {
			cout << "Base(const Base& rhs)" << endl;
		}

		virtual ~Base() {
			cout << "~Base()" << endl;
		}

		Base& operator=(const Base& rhs) {
			cout << "=Base& rhs" << endl;
			return *this;
		}
	private:
};

class Derived : public Base {
	public:
		Derived() {
			cout << "Derived()" << endl;
		}

		~Derived() {
			cout << "~Derived()" << endl;
		}

		Derived& operator=(const Derived& rhs) {
			cout << "=Derived& rhs" << endl;
			Base::operator=(rhs);
			mem = rhs.mem;
			return *this;
		}

		Derived(const Derived& rhs) : Base(rhs), mem(rhs.mem) {
			cout << "Derived(const Derived& rhs)" << endl;
		}
	private:
};

int main() {
	Derived der;
	Derived der2(der);
}
