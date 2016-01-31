#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <vector>
using namespace std;

const char offset = 'a';
const int alphabetLength = 26;

char decryptChar(int shift, char encryptedChar) {
	// check if upper, space or punctuation
	if (isupper(encryptedChar) || isspace(encryptedChar) || ispunct(encryptedChar)) {
		return encryptedChar;
	} else {
		char temp = encryptedChar - offset - shift;
		// if it ends up negative, add the length of the alphabet to it to bring it around at the end
		if (temp < 0) {
			return temp + offset + alphabetLength;
		} else {
			return temp + offset;
		}
	}
}

void decryptString(int shift, string& encryptedString) {
	for (size_t index = 0; index < encryptedString.size(); index++) {
		// decrypt each character in a string and change the string in place
		encryptedString[index] = decryptChar(shift, encryptedString[index]);
	}
}

int main() {
	// open file
	ifstream fileToDecrypt("encrypted.txt");

	// check for error
	if (!fileToDecrypt) {
		cerr << "Could not open file." << endl;
		exit(1);
	}

	// get shift length
	string line;
	getline(fileToDecrypt, line);
	int shift = stoi(line);

	vector<string> decryptedVector;

	// iterate over each line, decrypt it, and push it  to decryptedVector
	while (getline(fileToDecrypt, line)) {
		decryptString(shift, line);
		decryptedVector.push_back(line);
	}

	fileToDecrypt.close();

	// iterate backwards and print each line
	// I used int for index rather than size_t as the latter is unsigned and would never become negative
	for (int index = decryptedVector.size() - 1; index >= 0; index--) {
		cout << decryptedVector[index] << endl;
	}
}
