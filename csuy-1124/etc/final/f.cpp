#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>

using namespace std;

// STL - standard template library

void printStuff(string stuff) {
	cout << stuff << endl;
}

void printWithIterator(const list<int>& aList) {
	/*
	 * for (list<int>::iterator iter = aList.begin(); iter != aList.end(); iter++) {
	 *	   cout << *iter << endl;
	 *  }
	 */
	
	for (list<int>::const_iterator iter = aList.begin(); iter != aList.end(); iter++) {
		cout << *iter << endl;
	}
}

template <class T>
void printWithIteratorTemplated(const T& something) {
	for (auto iter = something.begin(); iter != something.end(); iter++) {
		cout << *iter << endl;
	}
}


int main() {
	vector<int> noStuffInHere;
	vector<int> stuffInHere = {1, 2, 3, 4, 5};
	vector<string> stringVector = {"a", "b", "c"};
	
	// by index
	printStuff("vector normal for");
	for (size_t i = 0; i < stringVector.size(); i++) {
		cout << stringVector[i] << endl;
	}
	
	// ranged for
	printStuff("vector ranged for");
	for (string x : stringVector) {
		cout << x << endl;
	}
	
	// container<CLASS>::iterator
	printStuff("vector iterator for");
	for (vector<string>::iterator iter = stringVector.begin(); iter != stringVector.end(); iter++) {
	    cout << *iter << endl;
	}
	
	list<int> intList = {1, 2, 3, 4, 5};
	
	printStuff("list ranged for");
	for (int x : intList) {
		cout << x << endl;
	}
	
	printStuff("list iterator for");
	for (list<int>::iterator iter = intList.begin(); iter != intList.end(); iter++){
	    cout << *iter << endl;
	}
	
	printStuff("list function iterator");
	printWithIterator(intList);
	
	printStuff("vector templated function");
	printWithIteratorTemplated(stuffInHere);
}
