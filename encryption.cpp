#include "encryption.hpp"

using namespace std;

map<char, set<unsigned int>*>* generateKeys() {
	map<char, set<unsigned int>*>* m = new map<char, set<unsigned int>*>();
	map<char, unsigned int>* frequencyMap = generateFrequencyMap();
	vector<unsigned int>* randoms = identityPermutation(115);
	shuffle(randoms);

	for (map<char, unsigned int>::iterator it = frequencyMap -> begin(); it != frequencyMap -> end(); it++) {
		char ch = it -> first;
		set<unsigned int>* s = new set<unsigned int>();

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

string* encrypt(map<char, set<unsigned int>*>* keyMap, string plaintext) {
	string ciphertext;

	for (unsigned int i = 0; i < plaintext.size(); i++) {
		char ch = plaintext[i];
		map<char, set<unsigned int>*>::iterator it = keyMap -> find(ch);
		set<unsigned int>* keys = it -> second;
		vector<unsigned int>* rn = generateRandomNumber(0, keys -> size(), 1);
		unsigned int index = (*rn)[0];
		delete rn;

		set<unsigned int>::iterator begin = keys -> begin();

		for (unsigned int i = 0; i < index; i++) {
			begin++;
		}
		ciphertext += to_string(*begin) + ',';
	}

	cout << ciphertext << endl;
}
