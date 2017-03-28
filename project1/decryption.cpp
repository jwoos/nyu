#include "decryption.hpp"

// BEGIN DECRYPTOR
Decryptor::Decryptor(std::string& cipherText, uint32_t index): cipherText(cipherText) {
	// Fill in our known quantities
	frequencyMap = generateFrequencyMap();
	e = new EMatrix(27, 27);
	std::vector<std::string> splitVector = split(cipherText, ',');

	if (index == 0) {
		e -> populateMatrix(generateEnglishWordsDigramFrequencyMap(), splitVector.size());
		dictionary = loadDictionary("other/dictionary.txt");
	} else {
		e -> populateMatrix(generateTestOneDigramFrequencyMatrix(index), 1);
		dictionary = loadDictionary("other/" + std::to_string(index) + ".txt");
	}

	// Initialize and wire up our matrices
	dc = new DCipherMatrix(106, 106);
	dc -> populateMatrix(cipherText);
	dp = new DPlainMatrix(27, 27);
	dp -> setFrequencyMap(&frequencyMap);
	dp -> setExpectedMatrix(e);
	dp -> setCipherMatrix(dc);
	initialKey();

	bestKey = new std::vector<char>(*putativeKey);
	bestScore = this -> currentScore();
}

struct FreqComparator {
	FreqComparator(std::map<uint32_t, uint32_t> m): freq(m) {}
	std::map<uint32_t, uint32_t> freq;
	bool operator() (int i, int j) {
		return freq[i] > freq[j];
	}
};

void Decryptor::randomizeKey() {
	delete putativeKey;
	putativeKey = new std::vector<char>(generateKey(frequencyMap));
	dp -> setKey(putativeKey);
}

void Decryptor::initialKey() {
	// Greedily grab letters so we start with a "pretty good" key
	std::string descendingLetterFreq(" eatinohrsdlcfgmpuwybjkqvxz");
	auto symbols = identityPermutation(106);
	shuffle(symbols);
	std::vector<std::string> splitVector = split(cipherText, ',');
	std::vector<uint32_t> numVector = stringToUnsignedInt(splitVector);
	auto symbolFreq = calculateSymbolFrequency(numVector);
	FreqComparator comp(symbolFreq);
	//std::sort(symbols->begin(), symbols->end(), comp);

	float symbolTotal = 0.0f;
	for(auto it = symbols -> begin(); it != symbols -> end(); it++) {
		symbolTotal += symbolFreq[*it];
	}

	// For each letter, grab the largest until either our freq exceeds, or our
	putativeKey = new std::vector<char>(106);

	for (uint32_t i = 0; i < 106; i++) {
		(*putativeKey)[i] = '*';
	}

	for (auto letter = descendingLetterFreq.begin(); letter != descendingLetterFreq.end(); letter++) {
		uint32_t count = 0;
		uint32_t targetCount = frequencyMap[*letter];
		float remainingPercentage = targetCount / 106.0f;

		while (count != targetCount) {
			auto closestSymbol = symbols -> end();
			auto closestScore = 1.0f;

			auto currentSymbol = symbols -> begin();
			while (currentSymbol != symbols -> end()) {
				if ((*putativeKey)[*currentSymbol] != '*') {
					currentSymbol++; continue;
				}

				auto currentPercentage = symbolFreq[*currentSymbol] / symbolTotal;
				auto currentScore = std::abs(remainingPercentage - currentPercentage);

				if (currentScore < closestScore) {
					closestScore = currentScore;
					closestSymbol = currentSymbol;
				}

				currentSymbol++;
			}

			if (closestSymbol != symbols -> end()) {
				(*putativeKey)[*closestSymbol] = *letter;
				remainingPercentage -= closestScore;
				count++;
			}
		}
	}

	dp -> setKey(putativeKey);
}

std::vector<char>* Decryptor::currentCandidateKey() {
	return putativeKey;
}

std::string Decryptor::currentCandidatePlaintext() {
	std::string plaintext;
	std::vector<std::string> tokens = split(cipherText, ',');

	for(uint32_t i = 0; i < tokens.size(); i++) {
		uint32_t index = std::stoi(tokens[i]);
		plaintext += (*putativeKey)[index];
	}

	return plaintext;
}

uint32_t Decryptor::currentScore(bool countWords) {
	uint32_t nonWordLetters = 0;
	if (countWords) {
		std::string plaintext = this -> currentCandidatePlaintext();
		std::vector<std::string> tokens = split(plaintext, ' ');
		for (uint32_t i = 0; i < tokens.size(); i++) {
			if (dictionary.find(tokens[i]) == dictionary.end()) {
				nonWordLetters += 2 * tokens[i].length();
			}
		}
	}
	return dp -> computeScore() + nonWordLetters;
}


void Decryptor::printKey() {
	for (char x : *putativeKey) {
		if (x == ' ') {
			x = '_';
		}

		std::cout << x;
	}
	std::cout << std::endl;
}

void Decryptor::setKey(std::vector<char>* k) {
	delete putativeKey;
	putativeKey = k;
	dp -> setKey(putativeKey);
}

void Decryptor::decrypt() {
	uint32_t rounds = 20;

	for (uint32_t i = 0; i < rounds; i++) {
		std::cout << "Rounds remaining: " << rounds - i << std::endl;
		performOneRound();
		uint32_t score = currentScore();

		if (score < bestScore) {
			bestScore = score;
			delete bestKey;
			bestKey = new std::vector<char>(*putativeKey);
			std::cout << "Better key found, with score " << bestScore << std::endl;
			printKey();
		}

		// If we converged super early, we can just do the final hill climb
		if (bestScore < 75) {
			std::cout << "Converged early, skipping to the final hill climb." << std::endl;
			break;
		}

		randomizeKey();
	}

	delete putativeKey;
	putativeKey = bestKey;
	dp -> setKey(putativeKey);

	std::cout << "Doing a final hill climb with hard scoring turned on." << std::endl;
	for (uint32_t i = 0; i < 2; i++) {
		std::cout << "Current hard score: " << currentScore(true) << std::endl;
		performOneRound(true);
	}
}

uint32_t Decryptor::decryptBruteForce() {
	uint32_t rounds = 5;

	for (uint32_t i = 0; i < rounds; i++) {
		std::cout << "Rounds remaining: " << rounds - i << std::endl;
		performOneRound();
		uint32_t score = currentScore();

		if (score < bestScore) {
			bestScore = score;
			delete bestKey;
			bestKey = new std::vector<char>(*putativeKey);
			std::cout << "Better key found, with score " << bestScore << std::endl;
			printKey();
		}

		// If we converged super early, we can just do the final hill climb
		if (bestScore < 75) {
			std::cout << "Converged early, skipping to the final hill climb." << std::endl;

			break;
		}

		randomizeKey();
	}

	delete putativeKey;
	putativeKey = bestKey;
	dp -> setKey(putativeKey);
	std::cout << "Doing a final hill climb with hard scoring turned on." << std::endl;
	std::cout << "Current hard score: " << currentScore(true) << std::endl;
	performOneRound(true);

	return currentScore(true);
}

void Decryptor::performOneRound(bool countWords) {
	// Understanding the boundary conditions of this is tricky, so:
	// The outer loop is a "gap size",
	// The inner loop is each column we might swap with a later one,
	// so for each gap size (starting with adjacent letters)
	// we loop over each column that has a gap column to swap with
	bool swaps = false;
	do {
		swaps = false;
		uint32_t currentScore = this -> currentScore(countWords);

		for (uint32_t i = 0; i < 106; i++) {
			for (uint32_t j = 0; j < 106; j++) {
				if (i == j) {
					continue;
				}

				dp -> updateKey(i, j);
				uint32_t newScore = this -> currentScore(countWords);

				// If we improved, use this new key as the putative key
				if (newScore < currentScore) {
					// Keep!
					currentScore = newScore;
					swaps = true;
				} else {
					// Otherwise, set our matrix back
					dp -> updateKey(i, j);
				}
			}
		}

		for (uint32_t gapSize = 1; gapSize < 105; gapSize++) {
			for (uint32_t column = 0; column < 106 - gapSize; column++) {
				uint32_t swapWith = column + gapSize;

				dp -> updateKey(column, swapWith);
				uint32_t newScore = this -> currentScore(countWords);

				// If we improved, use this new key as the putative key
				if (newScore < currentScore) {
					// Keep!
					currentScore = newScore;
					swaps = true;
				} else {
					// Otherwise, set our matrix back
					dp -> updateKey(column, swapWith);
				}
			}
		}

		for (uint32_t gapSize = 1; gapSize < 105; gapSize++) {
			for (uint32_t column = 105 - gapSize; column > 0; column--) {
				uint32_t swapWith = column + gapSize;

				dp -> updateKey(column, swapWith);
				uint32_t newScore = this -> currentScore(countWords);

				// If we improved, use this new key as the putative key
				if (newScore < currentScore) {
					// Keep!
					currentScore = newScore;
					swaps = true;
				} else {
					// Otherwise, set our matrix back
					dp -> updateKey(column, swapWith);
				}
			}
		}
	} while(swaps);
}
// END DECRYPTOR

// BEGIN CPADECRYPTOR
CPADecryptor::CPADecryptor(const std::string& ct) : potentialKey(106) {
	ciphertext = split(ct, ',');

	for (uint32_t i = 1; i < 6; i++) {
		possiblePlaintexts.push_back(testOnePlaintext(i));

		identifiers.push_back(getIdentifiers(i));
	}
}

uint32_t CPADecryptor::tentativePlaintextByIdentifier() {
	uint32_t current = 0;
	std::map<char, std::vector<uint32_t>> currentIdentifier;

	for (uint32_t i = 1; i < 6; i++) {
		current = i;
		currentIdentifier = getIdentifiers(i);

		for (auto it = currentIdentifier.begin(); it != currentIdentifier.end(); it++) {
			bool cont = true;
			std::vector<uint32_t> indices = it -> second;

			for (uint32_t j = 0; j < indices.size() - 1; j++) {
				if (ciphertext[indices[j]] != ciphertext[indices[j + 1]]) {
					cont = false;
					break;
				}
			}

			if (!cont) {
				break;
			}

			return current;
		}
	}

	return 0;
}

std::string CPADecryptor::getPlaintext(uint32_t index) {
	return possiblePlaintexts[index];
}

std::map<char, std::vector<uint32_t>> CPADecryptor::getIdentifier(uint32_t index) {
	return identifiers[index];
}

// END CPADECRYPTOR
