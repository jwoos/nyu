#include "dictionary.hpp"

using namespace std;

set<string> loadDictionary(string filename) {
	ifstream file(filename);
	string currentLine;
	set<string> allWords;
	while(getline(file, currentLine)) {
		allWords.insert(currentLine);
	}
	file.close();
	return allWords;
}

string randomWords(uint32_t numWords) {
	auto dictionary = loadDictionary("dictionary.txt");
	
	string output;
	RNG rng(0, dictionary.size() - 1, "uniform");
	for(uint32_t i = 0; i < numWords; i++) {
		auto it = dictionary.begin();
		advance(it, rng.randomNumber());
		output += *it;
		output += " ";
	}
	
	return output;
}