#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <vector>

using namespace std;

class Base {

};

class Derived :public Base {
	public:
		void purr() {}
};

int main() {
	Base base;
	Derived der;

	// slicing problem
	base = der;
	// compilation error
	// der = base;

	Base* bp;
	Derived* dp;

	bp = &base;
	bp = &der;
	// base class doesn't have a purr method
	//bp -> purr();

	dp = &der;
	// can't set parent as child
	//dp = &base;
}
