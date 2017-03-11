#include "encryption.hpp"

Encryptor::Encryptor() : rng(0, 10, "uniform"), keyMap(generateKeys()) {}

std::map<char, std::set<uint32_t>*> Encryptor::generateKeys() {
	std::map<char, std::set<uint32_t>*> m;
	std::map<char, uint32_t> frequencyMap = generateFrequencyMap();
	std::vector<uint32_t>* randoms = identityPermutation(115);
	shuffle(randoms);

	for (std::map<char, uint32_t>::iterator it = frequencyMap.begin(); it != frequencyMap.end(); it++) {
		char ch = it -> first;
		std::set<uint32_t>* s = new std::set<uint32_t>();

		for (uint32_t i = 0; i <  it -> second; i++) {
			s -> insert((*randoms)[randoms -> size() - 1]);
			randoms -> pop_back();
		}

		m.insert(make_pair(ch, s));
	}

	delete randoms;

	return m;
}

std::string Encryptor::encrypt(std::string& plaintext) {
	std::string ciphertext;

	for (uint32_t i = 0; i < plaintext.size(); i++) {
		char ch = plaintext[i];
		std::map<char, std::set<uint32_t>*>::iterator it = keyMap.find(ch);
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

	return ciphertext;
}

void Encryptor::printKeyMap() const {
	std::cout << "Key Map:" << std::endl;
	for (std::map<char, std::set<uint32_t>*>::const_iterator it = keyMap.begin(); it != keyMap.end(); it++) {
		char ch = it -> first;
		std::set<uint32_t>* s = it -> second;

		std::cout << '\t' << ch << ": ";

		for (std::set<uint32_t>::iterator inner = s -> begin(); inner != s -> end(); inner++) {
			std::cout << *inner << ", ";
		}

		std::cout << std::endl;
	}
	std::cout << std::endl;
}
