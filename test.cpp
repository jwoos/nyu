/* Test file
 * Test out functions here
 */

#include "utils.hpp"
#include "encryption.hpp"

#include <iostream>
#include <set>
#include <vector>

using namespace std;

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

	string a = "l";

	enc.encrypt(a);
}

void testMatrix() {
	vector<char> k = {'c', 'g', 'a', 'h', 'b', 'a', 'f', 'b', 'e', 'd'};
	map<char, uint32_t> fm = generateFrequencyMap();
	DCipherMatrix dCipher(10, 10);
	dCipher.populateMatrix("0,9,4,9,8,2,4,9,5,0,7,2,9,8,5,2,2,8,6,1,0,7,2,3,0,9,3,9,8,2,4,8,0,5,9,0,1,0,7,6,8,6,1,0,7,6,4,4,8,5,2,0,7");
	dCipher.printMatrix();
	flush();

	DPlainMatrix dPlain(8, 8);
	dPlain.setKey(&k);
	dPlain.setCipherMatrix(&dCipher);
	dPlain.setFrequencyMap(&fm);
	dPlain.populateMatrix();
	dPlain.printMatrix();
	flush();

	dPlain.updateKey(2, 9);
	dPlain.updateMatrix(2, 9);
	dPlain.printMatrix();
	flush();
}

void testCalculateCharFrequency() {
	map<char, uint32_t> freq = calculateCharFrequency("asd");

	for (map<char, uint32_t>::iterator it = freq.begin(); it != freq.end(); it++) {
		cout << "CHAR: " << it -> first << " COUNT: " << it -> second << endl;
	}
}

void testGenerateKey() {
	vector<char> v = generateKey(115);

	for (char x : v) {
		if (x == ' ') {
			x = '!';
		}

		cout << x << ' ';
	}
	flush();
}

int main() {
	testGenerateKey();
}
