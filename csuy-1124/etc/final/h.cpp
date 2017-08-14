#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>

using namespace std;

void printStuff(string stuff) {
	cout << stuff << endl;
}

void printIntVector(const vector<int>& aVector) {
	for (int x : aVector) {
		cout << x << endl;
	}
}

class AType {
	public:
		AType(int x) : dataMember(x) {}
		
		AType(string x) : dataMember2(x) {}
		
	private:
		int dataMember;
		string dataMember2;
};

int main() {
	AType anObj(10);
	AType stringObj("string");
	
	// constructors
	printStuff("Default constructor");
	vector<int> defaultVector;
	printIntVector(defaultVector);
	
	// vector<int> curlyConstructor {1, 2, 3, 4, 5, 6, 7};
	printStuff("Braces constructor");
	vector<int> curlyConstructor = {1, 2, 3, 4, 5, 6, 7};
	printIntVector(curlyConstructor);
	
	printStuff("Iterator constructor");
	vector<int> iteratorConstructor(curlyConstructor.begin(), curlyConstructor.end());
	printIntVector(iteratorConstructor);
	
	printStuff("Copy constructor");
	vector<int> copyConstructor(curlyConstructor);
	printIntVector(copyConstructor);
	
	printStuff("Default constructor");
	vector<int> defaultValueConstructor(10, 10);
	printIntVector(defaultValueConstructor);
	
	printStuff("List constructor");
	list<int> copyFromVector(iteratorConstructor.begin(), iteratorConstructor.end());
	for (int x : copyFromVector) {
		cout << x << endl;
	}
}