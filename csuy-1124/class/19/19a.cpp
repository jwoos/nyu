#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Foo {
	public:
		// default constructor
		// after ANY constructor is specificed the system does not provide a default constructor and must be specified
		Foo() = default;
		// don't allow copying
		Foo(const Foo& rhs) = delete;
};

int main() {

}
