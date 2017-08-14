#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <cassert>

using namespace std;

class MyException {

};

void bar(int n) {
	if (n > 200) {
		throw MyException();
	}
}

void foo(int n) {
	assert(n <= 200);

	bar(n);
};

int main() {
	try {
		vector<int> v;
		v.push_back(17);
		cout << v[31] << endl;
		cout << v.at(31) << endl;
	} catch (int x) {
		cerr << "caught an int: " << x << endl;
	} catch (double d) {
		cerr << "caught a double: " << d << endl;
	} catch (out_of_range oor) {
		cerr << "caught oor" << endl;
	} catch (exception ex) {
		cerr << "caught ex" << endl;
	} catch (...) {
		cerr << "caught something..." << endl;
	}

	foo(300);

	cout << "main is ending" << endl;
}
