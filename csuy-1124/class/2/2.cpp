#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <vector>
using namespace std;

// Constant
const int aConstant = 42;

// Avoid global variables
// int n = 10;

void hello() {
	cout << "Hello World!" << endl;
}

int addOne(int val) {
	val++;
	return val;
}

int addOneByRef(int& val) {
	val++;
	return 0;
}

int main() {
	hello();

	int n = 10;
	cout << n << endl;
	n = addOne(n);
	cout << n << endl;
	addOneByRef(n);
	cout << n << endl;

	vector<int> aVector;

	aVector.push_back(10);
	aVector.push_back(15);
	aVector.push_back(20);

	for (size_t n = 0; n < aVector.size(); n++) {
		cout << aVector[n] << endl;
	}
	cout << endl;

	for (int item: aVector) {
		cout << item << endl;
	}
	cout << endl;

	return 0;
}
