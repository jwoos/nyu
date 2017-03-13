/* Test file
 * Test out functions here
 */

#include "utils.hpp"
#include "matrix.hpp"
#include "frequency.hpp"
#include "key.hpp"
#include "encryption.hpp"
#include "decryption.hpp"
#include "dictionary.hpp"

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

std::string getPlaintext() {
	string a = randomWords(1000);
	return a;
}

void testEncrypt() {
	Encryptor enc;

	enc.printKeyMap();

	auto a = getPlaintext();

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
	dPlain.printMatrix();
	flush();
}

void testCalculateCharFrequency() {
	map<char, uint32_t> freq = calculateCharFrequency("asd");

	for (map<char, uint32_t>::iterator it = freq.begin(); it != freq.end(); it++) {
		cout << "CHAR: " << it -> first << " COUNT: " << it -> second << endl;
	}
}

void printKey(vector<char>* key) {
	for (char x : *key) {
		if (x == ' ') {
			x = '!';
		}

		cout << x;
	}
	cout << endl;
	flush();
}

void testGenerateKey() {
	vector<char> v = generateKey(105);
	printKey(&v);

	vector<char> b = generateKey(generateFrequencyMap());
	printKey(&b);
}


void fullTest() {
	std::string plaintext = getPlaintext();

	Encryptor enc;
	cout << "Real Key:" << endl;
	std::vector<char> realKey(106);
	for(uint32_t l = 0; l < 27; l++) {
		char c = getCharForIndex(l);
		auto set = enc.keyMap[c];
		for(auto it = set->begin(); it != set->end(); it++) {
			realKey[*it] = c;
		}
	}
	printKey(&realKey);
	std::string ciphertext = enc.encrypt(plaintext);

	Decryptor d(ciphertext);
/*
	cout << "Actual Plain: " << plaintext.substr(0, 100) << endl;
	cout << "Before Plain: " << d.currentCandidatePlaintext().substr(0, 100) << endl;
	cout << "Before Score: " << d.currentScore() << endl;
	for(uint32_t i = 0; i < 1000; i++) {
		d.performOneRound();
		
		cout << "Actual Plain: " << plaintext.substr(0, 100) << endl;
		cout << "During Plain: " << d.currentCandidatePlaintext().substr(0, 100) << endl;
		cout << "During Score: " << d.currentScore() << endl;
	}*/

	d.decrypt();

	cout << "Actual Plain: " << plaintext.substr(0, 100) << endl;
	cout << "After Plain:  " << d.currentCandidatePlaintext().substr(0, 100) << endl;
	cout << "After Score:  " << d.currentScore() << endl;
	cout << "(Hard Score): " << d.currentScore(true) << endl;

	auto finalKey = d.currentCandidateKey();
	cout << "Final Key:" << endl;
	printKey(finalKey);

	uint32_t differences = 0;
	for(uint32_t i = 0; i < finalKey->size(); i++) {
		if(realKey[i] != (*finalKey)[i]) {
			differences++;
		}
	}
	cout << "Number of key differences: " << differences << endl;
}

void computeThreshold() {
	auto freqMap = generateFrequencyMap();
	float total = 0;
	uint32_t min = 5000;
	uint32_t max = 0;
	for(uint32_t i = 1; i < 1000; i++) {
		std::string plaintext = randomWords(500);
		Encryptor enc;
		std::string ciphertext = enc.encrypt(plaintext);

		EMatrix e(27, 27);
		std::vector<std::string> splitVector = split(ciphertext, ',');
		e.populateMatrix(generateEnglishWordsDigramFrequencyMap(), splitVector.size());

		std::vector<char> key(106);
		for(uint32_t l = 0; l < 27; l++) {
			char c = getCharForIndex(l);
			auto set = enc.keyMap[c];
			for(auto it = set->begin(); it != set->end(); it++) {
				key[*it] = c;
			}
		}
		DCipherMatrix dc(106, 106);
		dc.populateMatrix(ciphertext);
		DPlainMatrix dp(27,27);
		dp.setFrequencyMap(&freqMap);
		dp.setExpectedMatrix(&e);
		dp.setCipherMatrix(&dc);
		dp.setKey(&key);
		uint32_t score = dp.computeScore();
		total += score;
		if(score > max) {
			max = score;
		}
		if(score < min) {
			min = score;
		}
		std::cout << min << " < " << total / i << " < " << max << std::endl;
	}
}

void testSwapping() {
	auto freqMap = generateFrequencyMap();
	for(uint32_t j = 0; j < 50; j++) {
		// Fixed key for easy debugging
		Encryptor enc;

		std::string plaintext = randomWords(500);
		std::string ciphertext = enc.encrypt(plaintext);

		std::vector<char> safeKey(106);
		for(uint32_t l = 0; l < 27; l++) {
			char c = getCharForIndex(l);
			auto set = enc.keyMap[c];
			for(auto it = set->begin(); it != set->end(); it++) {
				safeKey[*it] = c;
			}
		}

		EMatrix e(27, 27);
		std::vector<std::string> splitVector = split(ciphertext, ',');
		e.populateMatrix(generateEnglishWordsDigramFrequencyMap(), splitVector.size());

		std::vector<char> swapKey(safeKey);
		DCipherMatrix dc(106, 106);
		dc.populateMatrix(ciphertext);
		DPlainMatrix dpSafe(27,27);
		dpSafe.setFrequencyMap(&freqMap);
		dpSafe.setCipherMatrix(&dc);
		dpSafe.setKey(&safeKey);

		DPlainMatrix dpSwap(27,27);
		dpSwap.setFrequencyMap(&freqMap);
		dpSwap.setCipherMatrix(&dc);
		dpSwap.setKey(&swapKey);

		RNG rng(0, 105);
		bool spoiled = false;
		uint32_t maxIterations = 1000;
		uint32_t i = 0;
		for(i = 0; i < maxIterations; i++) {
			uint32_t x = rng.randomNumber();
			uint32_t y = rng.randomNumber();
			dpSafe.safeUpdateKey(x, y);
			dpSwap.updateKey(x, y);
			if(dpSafe.countDifferences(dpSwap) > 0) {
				spoiled = true;
				break;
			}
		}
		if(spoiled) {
			std::cout << "DIFFERENCES FOUND!!  After " << i << " iterations." << std::endl;
			dpSafe.printDifferences(dpSwap);
		} else {
			std::cout << "Still pristine after " << maxIterations << " iterations!" << std::endl;
		}
	}
}

int main() {
	fullTest();
}
