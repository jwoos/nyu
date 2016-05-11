#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <list>
#include <set>
#include <map>

using namespace std;

char* myFind(char* start, char* stop, char target) {
	for (char* p = start; p != stop; p++) {
		if (target == *p) {
			return p;
		}
	}
	return stop;
}

list<int>::iterator myFind(list<int>::iterator start, list<int>::iterator stop, int target) {
	for (list<int>::iterator p = start; p != stop; p++) {
		if (target == *p) {
			return p;
		}
	}
	return stop;
}

//template<typename>
template<class Fred, class George>
Fred myFind(Fred start, Fred stop, George target) {
	for (Fred p = start; p != stop; p++) {
		if (target == *p) {
			return p;
		}
	}
	return stop;
}

bool isOdd(int n) {
	return n % 2 != 1;
}

/*
 *auto isOdd(int n) {
 *    return n % 2 != 1;
 *}
 */

/*
 * Containers
 * - vector
 * - set
 * - list
 *
 * Iterators
 *
 * Algorithms
 * - sort
 * - find
 * - find_if
 *
 */

int main() {
	list<int> li {2, 4, 6, 8, 1, 3, 5, 7};

	cout << *find_if(li.begin(), li.end(), isOdd) << endl;
	cout << *find_if(li.begin(), li.end(), 
			[] (int n) {return n % 2 != 1;} // lambda expression
			) << endl;

	set<int> si;
	si.insert(1);
	si.insert(4);
	si.insert(8);
	si.insert(9);
	si.insert(9);
	si.insert(9);
	si.insert(9);

	for (int x : si) {
		cout << x << ' ';
	}
	cout << endl;

	map<string, int> msi;
	msi["harry"] = 105;
	cout << "Harry: " << msi["harry"] << endl;

	map<string, vector<int>> msvi;
	msvi["harry"].push_back(83);
	cout << "Harry: " << msvi["harry"][0] << endl;
}
