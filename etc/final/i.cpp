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

template <typename T>
void printContainers(const T& container) {
	for (typename T::const_iterator iter = container.begin(); iter != container.end(); iter++) {
		cout << *iter << ' ';
	}
	cout << endl;
}

template <typename T>
void printContainers2(const T& container) {
	for (auto x : container) {
		cout << x << ' ';
	}
	cout << endl;
}

int main() {
	list<int> intList = {1, 2, 3, 4, 5};
	printStuff("iterator for template");
	printContainers(intList);
	printStuff("ranged for template");
	printContainers2(intList);
	
	list<string> unsortedStringList = {"b", "c", "a", "h", "A", "w", "u", "B"};
	printStuff("unsorted string list");
	printContainers(unsortedStringList);
	
	unsortedStringList.sort();
	printStuff("sorted string list");
	printContainers(unsortedStringList);
	
	vector<int> intVector = {43, 123, 734, 213, 534, 1, 3, 5, 8, 10, 23, 64, 76, 192};
	printStuff("unsorted int vector");
	printContainers(intVector);
	
	sort(intVector.begin(), intVector.end());
	printStuff("sorted int vector");
	printContainers(intVector);
}