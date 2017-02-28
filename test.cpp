#include "utils.hpp"
#include "encryption.hpp"

#include <iostream>
#include <set>
#include <vector>

using namespace std;

void testRNG() {
	vector<unsigned int>* v = generateRandomNumber(1, 100, 10);

	for (unsigned int i = 0; i < v -> size(); i++) {
		cout << (*v)[i] << endl;
	}

	delete v;
}

void testDistinctRNG() {
	vector<unsigned int>* s = generateDistinctRandomNumbers(0, 115, 115);

	for (vector<unsigned int>::iterator i = s -> begin(); i != s -> end(); i++) {
		cout << *i << endl;
	}
}

void testGenerateFrequencyMap() {
	map<char, unsigned int>* m = generateFrequencyMap();

	for (map<char, unsigned int>::iterator it = m -> begin(); it != m -> end(); it++) {
		cout << it -> first << ": " << it -> second << endl;
	}
}

int main() {
	testDistinctRNG();
}
