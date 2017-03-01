#include "utils.hpp"
#include "encryption.hpp"

int main(int argc, char** argv) {
	// TODO check if encrypt or decrypt
	map<char, set<unsigned int>*>* m = generateKeys();

	for (map<char, set<unsigned int>*>::iterator it = m -> begin(); it != m -> end(); it++) {
		char ch = it -> first;
		set<unsigned int>* s = it -> second;

		cout << "CHAR: " << ch << endl;
		for (set<unsigned int>::iterator inner = s -> begin(); inner != s -> end(); inner++) {
			cout << *inner << ", ";
		}
		cout << endl << endl;
	}

	encrypt(m, "asd");
}
