#include "dictionary.hpp"

std::set<std::string> loadDictionary(std::string filename) {
	std::ifstream file(filename);
	std::string currentLine;
	std::set<std::string> allWords;
	while(getline(file, currentLine)) {
		allWords.insert(currentLine);
	}
	file.close();
	return allWords;
}

std::string randomWords(uint32_t numWords) {
	auto dictionary = loadDictionary("dictionary.txt");

	std::string output;
	RNG rng(0, dictionary.size() - 1, "uniform");
	for(uint32_t i = 0; i < numWords; i++) {
		auto it = dictionary.begin();
		advance(it, rng.randomNumber());
		output += *it;
		output += " ";
	}

	return output;
}

std::set<std::string> loadWords(uint32_t index) {
	switch (index) {
		case 0: {
			return 
		}
	}
}
