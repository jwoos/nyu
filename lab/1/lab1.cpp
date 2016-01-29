#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <stdlib.h>
using namespace std;

void countChars(int& currentCount, string currentLine) {
	for (size_t index = 0; index < currentLine.size(); index++) {
		/* cout << currentLine[index] << endl; */
		currentCount++;
	}
	// count newline
	currentCount++;
}

void countWords(int& currentCount, string currentLine) {
	for (size_t index = 0; index < currentLine.size(); index++) {
		if (currentLine[index] == ' ') {
			currentCount++;
		}
	}
	// count last word
	if (!(currentLine.size() == 0)) {
		currentCount++;
	}
}

int main() {
	ifstream fileToRead("jabberwocky.txt");

	fileToRead >> noskipws;

	int wordCount = 0;
	int charCount = 0;
	int lineCount = 0;

	if (!fileToRead) {
		cout << "Could not open file." << endl;
		exit(1);
	}

	string line;
	while (getline(fileToRead, line)) {
		cout << line << endl;
		countWords(wordCount, line);
		countChars(charCount, line);
		lineCount++;
	}

	fileToRead.close();

	cout << endl;
	cout << lineCount << " lines" << endl;
	cout << wordCount << " words" << endl;
	cout << charCount << " characters" << endl;
}
