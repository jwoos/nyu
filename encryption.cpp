#include "encryption.hpp"

std::map<char, std::set<uint32_t>*>* generateKeys() {
	std::map<char, std::set<uint32_t>*>* m = new std::map<char, std::set<uint32_t>*>();
	std::map<char, uint32_t>* frequencyMap = generateFrequencyMap();
	std::vector<uint32_t>* randoms = identityPermutation(115);
	shuffle(randoms);

	for (std::map<char, uint32_t>::iterator it = frequencyMap -> begin(); it != frequencyMap -> end(); it++) {
		char ch = it -> first;
		std::set<uint32_t>* s = new std::set<uint32_t>();

		for (int i = 0; i <  it -> second; i++) {
			s -> insert((*randoms)[randoms -> size() - 1]);
			randoms -> pop_back();
		}

		m -> insert(make_pair(ch, s));
	}

	delete randoms;
	delete frequencyMap;

	return m;
}

std::string* encrypt(std::map<char, std::set<uint32_t>*>* keyMap, std::string plaintext) {
	std::string* cipherPointer = new std::string();
	std::string ciphertext = *cipherPointer;
	RNG rng(0, 10);

	for (uint32_t i = 0; i < plaintext.size(); i++) {
		char ch = plaintext[i];
		std::map<char, std::set<uint32_t>*>::iterator it = keyMap -> find(ch);
		std::set<uint32_t>* keys = it -> second;

		rng.setBounds(0, keys -> size());
		uint32_t index = rng.randomNumber();

		std::set<uint32_t>::iterator begin = keys -> begin();

		for (uint32_t i = 0; i < index; i++) {
			begin++;
		}

		ciphertext += std::to_string(*begin) + ',';
	}

	std::cout << ciphertext << std::endl;

	return cipherPointer;
}
