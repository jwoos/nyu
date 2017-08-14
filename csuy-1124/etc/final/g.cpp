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

template <class T>
void printContainer(const T& something) {
	for (auto iter = something.begin(); iter != something.end(); iter++) {
		cout << *iter << endl;
	}
}

bool isOdd(int n) {
	return n % 2 == 1;
}

int main() {
	vector<int> unsortedIntVector = {10, 2, 5, 1, 19, 52, 31, 129, 592, 1294105};
	vector<int> sortedIntVector = {1, 2, 3, 4, 5, 6};
	
	printStuff("unsorted");
	printContainer(unsortedIntVector);
	
	sort(unsortedIntVector.begin(), unsortedIntVector.end());
	
	printStuff("sorted");
	printContainer(unsortedIntVector);
	
	printStuff("find");
	vector<int>::iterator iter = find(unsortedIntVector.begin(), unsortedIntVector.end(), 10);
	cout << *iter << endl;
	
	printStuff("find not in vector");
	// returns unsortedIntVector.end if not found
	vector<int>::iterator notFound = find(unsortedIntVector.begin(), unsortedIntVector.end(), 10000);
	cout << boolalpha << (notFound == unsortedIntVector.end()) << endl;
	
	printStuff("find_if");
	vector<int>::iterator oddIter = find_if(unsortedIntVector.begin(), unsortedIntVector.end(), isOdd);
	cout << *oddIter << endl;
	
	printStuff("find_if lambda");
	vector<int>::iterator notFoundLambda = find_if(unsortedIntVector.begin(), unsortedIntVector.end(), [] (int n) {return n % 2 == 1;});
	cout << *notFoundLambda << endl;
}
