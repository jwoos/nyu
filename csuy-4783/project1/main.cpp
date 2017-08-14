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
	if (argc < 3) {
		cout << "Usage: main <ACTION>" << endl;
		cout << "\tACTION: encrypt | decrypt" << endl;
		cout << "\tTYPE: 1 | 2" << endl;
		return 1;
	}

	string action = string(argv[1]);
	int type = stoi(string(argv[2]));

	if (!action.size()) {
		cout << "ACTION cannot be empty" << endl;
		return 1;
	}

	if (type != 1 && type != 2) {
		cout << "TYPE cannot be empty" << endl;
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

		cout << "CIPHERTEXT:" << endl;
		cout << enc.encrypt(text) << endl;
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
			flush();

			text = enc.encrypt(plaintext);
		}

		Decryptor d(text, 0);

		if (type == 1) {
			// test 1

			CPADecryptor cpaD(text);
			uint32_t index = cpaD.tentativePlaintextByIdentifier();

			if (index == 0) {
				// couldn't determine from identifiers
				cout << "Couldn't match by identifiers, falling back to bigram frequency analysis" << endl;
				std::vector<char>* originalKey = new std::vector<char>(*d.currentCandidateKey());

				uint32_t minScore = 100000;

				for (uint32_t i = 1; i < 6; i++) {
					std::cout << "Trying plaintext " << i << std::endl;
					Decryptor temp(text, i);
					temp.setKey(new std::vector<char>(*originalKey));
					uint32_t tempScore = temp.decryptBruteForce();

					if (tempScore < minScore) {
						minScore = tempScore;
						index = i;
					}
				}

				cout << index << endl;
			}

			if (index == 0) {
				RNG rng(1, 5, "uniform");
				index = rng.randomNumber();
			}


			cout << index << endl;
			cout << "PLAINTEXT: " << endl;
			cout << cpaD.getPlaintext(index) << endl;
		} else {
			// test 2
			d.decrypt();

			cout << "TEXT DECRYPTED WITH A SCORE OF " << d.currentScore() << " AND A HARD SCORE OF [" << d.currentScore(true) <<  "]: " << endl;
			cout << d.currentCandidatePlaintext() << endl;
		}
	} else {
		cout << "Invalid ACTION" << endl;
		return 1;
	}
}
