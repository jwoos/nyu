/* Actual program to decrypt
 */

#include "utils.hpp"
#include "matrix.hpp"
#include "frequency.hpp"
#include "key.hpp"
#include "encryption.hpp"

#include <iostream>

using namespace std;

int main(int argc, char** argv) {
	if (argc == 1) {
		cout << "Usage: main <ACTION> <TEXT>" << endl;
		cout << "\tACTION: encrypt | decrypt" << endl;
		cout << "\tTEXT: text to work with enclosed in quotations" << endl;

		return 1;
	}

	string action = string(argv[1]);
	string text = string(argv[2]);

	if (!action.size()) {
		cout << "ACTION cannot be empty" << endl;
		return 1;
	}

	if (!text.size()) {
		cout << "TEXT cannot be empty" << endl;
		return 1;
	}

	if (action == "encrypt") {
		Encryptor enc;

		cout << "ENCRYPTING..." << endl;
		cout << "PLAIN TEXT:" << endl;
		cout << text << endl;

		enc.printKeyMap();

		enc.encrypt(text);
	} else if (action == "decrypt") {
		if (!text.size()) {
			cout << "TEXT cannot be empty" << endl;
			return 1;
		}

		map<char, uint32_t> fm = generateFrequencyMap();
		vector<char> key = generateKey();

		// Generate and populate cipher matrix
		DCipherMatrix dCipher(106, 106);
		dCipher.populateMatrix(text);

		DPlainMatrix dPlain(27, 27);
		dPlain.setKey(&key);
		dPlain.setCipherMatrix(&dCipher);
		dPlain.setFrequencyMap(&fm);
		dPlain.populateMatrix();
	} else {
		cout << "Invalid ACTION" << endl;
		return 1;
	}
}
