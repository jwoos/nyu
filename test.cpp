#include "utils.hpp"
#include "encryption.hpp"

#include <iostream>
#include <set>
#include <vector>

using namespace std;

void testRNG() {
	vector<uint32_t>* v = generateRandomNumber(1, 100, 10);

	for (uint32_t i = 0; i < v -> size(); i++) {
		cout << (*v)[i] << endl;
	}

	delete v;
}

void testGenerateFrequencyMap() {
	map<char, uint32_t> m = generateFrequencyMap();

	for (map<char, uint32_t>::iterator it = m.begin(); it != m.end(); it++) {
		cout << it -> first << ": " << it -> second << endl;
	}
}

void testPermutations() {
	Permutation p(10);

	int count = 0;
	do {
		count++;
		for (auto i = p.values.begin(); i != p.values.end(); i++) {
			//cout << *i;
		}
		//cout << "; " << p.LargestMobile() << endl;
	} while(p.Advance());
	cout << "total: " << count << endl; // Expected: 3628800
}

void testRandomPermutations() {
	vector<uint32_t>* s = identityPermutation(10);
	shuffle(s);
	for (vector<uint32_t>::iterator i = s -> begin(); i != s -> end(); i++) {
		cout << *i << ';';
	}
	cout << endl;
}

void testEncrypt() {
	Encryptor enc;

	enc.printKeyMap();

	enc.encrypt("asd");
}

int main() {
	vector<uint32_t>* v = identityPermutation(115);
	for (vector<uint32_t>::iterator it = v -> begin(); it != v -> end(); it++) {
		cout << *it << ' ';
	}
	cout << endl;
}
