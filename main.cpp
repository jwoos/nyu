#include "utils.hpp"
#include "encryption.hpp"

int main(int argc, char** argv) {
	// TODO check if encrypt or decrypt
	map<char, set<uint32_t>*>* m = generateKeys();

	for (map<char, set<uint32_t>*>::iterator it = m -> begin(); it != m -> end(); it++) {
		char ch = it -> first;
		set<uint32_t>* s = it -> second;

		cout << "CHAR: " << ch << endl;
		for (set<uint32_t>::iterator inner = s -> begin(); inner != s -> end(); inner++) {
			cout << *inner << ", ";
		}
		cout << endl << endl;
	}

	encrypt(m, "asd");
}
