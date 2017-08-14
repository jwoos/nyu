#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <vector>

using namespace std;

struct Word {
	string token;
	vector<int> position;
};

int main() {
	ifstream ifs("jabberwocky.txt");
	if (!ifs) {
		cerr << "Error" << endl;
		exit(1);
	}

	vector<Word> words;
	string token;
	int counter = 0;
	while (ifs >> token) {
		for (const Word& word : words) {
			if (token == word.token) {
				break;
			}
		}
		Word theWord;
		theWord.token = token;
		theWord.position.push_back(counter);
		counter++;
		words.push_back(theWord);
	}

	ifs.close();

	for (size_t i = 0; i < words.size(); i++) {
		cout << words[i].token << endl;
		for (size_t x = 0; x < words.size(); x++) {
			cout << words[i].position[x] << endl;
		}
	}
}
