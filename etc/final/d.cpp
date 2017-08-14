#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class Base {
	private:
		int* ptr;

	public:
		Base() : ptr(new int(0)) {}

		Base(const Base& rhs) : ptr (new int(*rhs.ptr)) {}

		Base& operator=(const Base& rhs) {
			if (this != & rhs) {
				*ptr = *rhs.ptr;
			}

			return *this;
		}

		~Base() {
			delete ptr;
		}
};

class Derived : public Base {
	private:
		double *dPtr;

	public:
		Derived() : dPtr(new double(0)) {}

		~Derived() {
			delete dPtr;
		}

		Derived& operator=(const Derived& rhs) {
			if (this != &rhs) {
				Base::operator=(rhs);
				*dPtr = *rhs.dPtr;
			}

			return *this;
		}

		Derived(const Derived& rhs) : Base(rhs), dPtr(new double(*rhs.dPtr)) {};
};

int main() {

}
