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

void testGenerateFrequencyMap() {
	map<char, unsigned int>* m = generateFrequencyMap();

	for (map<char, unsigned int>::iterator it = m -> begin(); it != m -> end(); it++) {
		cout << it -> first << ": " << it -> second << endl;
	}
}

void testRandomPermutations() {
	vector<unsigned int>* s = identityPermutation(10);
	shuffle(s);
	for (vector<unsigned int>::iterator i = s -> begin(); i != s -> end(); i++) {
		cout << *i << ';';
	}
	cout << endl;
}

int main() {
	testRandomPermutations();
}
