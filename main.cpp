/* Actual program to decrypt
 */

#include "utils.hpp"
#include "matrix.hpp"
#include "frequency.hpp"
#include "key.hpp"
#include "dictionary.hpp"
#include "encryption.hpp"
#include "decryption.hpp"

#include <iostream>

using namespace std;

int main(int argc, char** argv) {
	if (argc == 1) {
		cout << "Usage: main <ACTION>" << endl;
		cout << "\tACTION: encrypt | decrypt" << endl;

		return 1;
	}

	string action = string(argv[1]);

	if (!action.size()) {
		cout << "ACTION cannot be empty" << endl;
		return 1;
	}

	cout << "Enter the text to work on: ";

	string text;
	getline(cin, text);

	if (action == "encrypt") {
		if (!text.size()) {
			cout << "encrypt needs text" << endl;
			exit(1);
		}
		Encryptor enc;

		cout << "ENCRYPTING..." << endl;
		cout << "PLAIN TEXT:" << endl;
		cout << text << endl;

		enc.printKeyMap();

		enc.encrypt(text);
	} else if (action == "decrypt") {
		if (!text.size()) {
			cout << "Detected empty input, defaulting to generating and encrypting a text of length 500" << endl;
			string plaintext = randomWords(500);
			Encryptor enc;
			vector<char> realKey(106);

			for (uint32_t l = 0; l < 27; l++) {
				char c = getCharForIndex(l);
				auto s = enc.keyMap[c];

				for (auto it = s -> begin(); it != s -> end(); it++) {
					realKey[*it] = c;
				}
			}

			cout << "Generated text: " << endl;
			cout <<  plaintext << endl;
			cout << "With a key of: " << endl;
			for (char x : realKey) {
				if (x == ' ') {
					cout << '_' << ' ';
				} else {
					cout << x << ' ';
				}
			}
			flush();

			text = enc.encrypt(plaintext);
		}

		Decryptor d(text);
		d.decrypt();

		cout << "FINAL KEY: ";
		auto finalKey = *(d.currentCandidateKey());
		for (char x : finalKey) {
			if (x == ' ') {
				cout << '_' << ' ';
			} else {
				cout << x << ' ';
			}
		}
		flush();

		cout << "TEXT DECRYPTED WITH A SCORE OF " << d.currentScore() << ": " << endl;
		cout << d.currentCandidatePlaintext() << endl;
	} else {
		cout << "Invalid ACTION" << endl;
		return 1;
	}
}
