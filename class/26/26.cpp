#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>

using namespace std;

// O(2^n)
int fibonacciR(int n) {
	if (n <= 2) {
		return 1;
	}
	return fibonacciR(n - 2) + fibonacciR(n -1);
}

 /*
  * collections
  * - vector
  * - list
  * - set
  *   - unordered set
  * - map
  *
  * iterator
  *
  * algorithm
  *
  */

char* where = find(char* start, char* stop, char target) {
	for (char* p = start; p  != stopl; p++) {
		if (target == *p) P
			return p;
	}
}

int main() {
	char array[] = "Bjarne Stroustrup";
	int len = 17;

	// address one past the array
	vector<char> vc(array, array + len); // half open range [start, stop)

	list<char> lc(array, array + len);

	for (size_t i = 0; i < vc.size(); i++) {
		cout << vc[i];
	}
	cout << endl;

	sort(array, array + len);

	for (char x : lc) {
		cout << x;
	}
	cout << endl;

	//for (iterator iter = lc.begin(); iter != lc.end(); iter.next()) {
	for (list<char>::iterator iter = lc.begin(); iter != lc.end(); iter++) {
		cout << *iter;
	}
	cout << endl;

	sort(vc.begin(), vc.end());

	for (size_t i = 0; i < vc.size(); i++) {
		cout << vc[i];
	}
	cout << endl;

	char* where = find(array, array + len, 'p');
	cout << (void*)where << endl;

	list<char>::iterator otherWhere = find(lc.begin(), lc.end(), 'p');

	if (otherWhere == lc.end()) {
		cout << "Could not find i";
	}
	cout << endl;

	auto x = 17;
}
