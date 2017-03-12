#include "decryption.hpp"

Decryptor::Decryptor(std::string& cipherText): cipherText(cipherText) {
	// Fill in our known quantities
	frequencyMap = generateFrequencyMap();
	e = new EMatrix(27, 27);
	std::vector<std::string> splitVector = split(cipherText, ',');
	e->populateMatrix(generateEnglishWordsDigramFrequencyMap(), splitVector.size());

	// Initialize and wire up our matrices
	dc = new DCipherMatrix(106, 106);
	dc->populateMatrix(cipherText);
	dp = new DPlainMatrix(27, 27);
	dp->setFrequencyMap(&frequencyMap);
	dp->setExpectedMatrix(e);
	dp->setCipherMatrix(dc);
	initialKey();

	bestKey = new std::vector<char>(*putativeKey);
	bestScore = this->currentScore();
}

struct FreqComparator {
	FreqComparator(std::map<uint32_t, uint32_t> map): freq(map) {}
	std::map<uint32_t, uint32_t> freq;
	bool operator() (int i, int j) {
		return freq[i] > freq[j];
	}
};

void Decryptor::randomizeKey() {
	delete putativeKey;
	putativeKey = new std::vector<char>(generateKey(frequencyMap));
	dp->setKey(putativeKey);
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
	for(auto it = symbols->begin(); it != symbols->end(); it++) {
		symbolTotal += symbolFreq[*it];
	}

	// For each letter, grab the largest until either our freq exceeds, or our 
	putativeKey = new std::vector<char>(106);
	for(uint32_t i = 0; i < 106; i++) { (*putativeKey)[i] = '*'; }
	for(auto letter = descendingLetterFreq.begin(); letter != descendingLetterFreq.end(); letter++) {
		uint32_t count = 0, targetCount = frequencyMap[*letter];
		float remainingPercentage = targetCount / 106.0f;
		while(count != targetCount) {
			auto closestSymbol = symbols->end();
			auto closestScore = 1.0f;

			auto currentSymbol = symbols->begin();
			while(currentSymbol != symbols->end()) {
				if((*putativeKey)[*currentSymbol] != '*') { currentSymbol++; continue; }

				auto currentPercentage = symbolFreq[*currentSymbol] / symbolTotal;
				auto currentScore = std::abs(remainingPercentage - currentPercentage);

				if(currentScore < closestScore) {
					closestScore = currentScore;
					closestSymbol = currentSymbol;
				}
				currentSymbol++;
			}

			if(closestSymbol != symbols->end()) {
				(*putativeKey)[*closestSymbol] = *letter;
				remainingPercentage -= closestScore;
				count++;
			}
		}
	}

	dp->setKey(putativeKey);
}

std::vector<char>* Decryptor::currentCandidateKey() {
	return putativeKey;
}

std::string Decryptor::currentCandidatePlaintext() {
	std::string plaintext;
	std::vector<std::string> tokens = split(cipherText, ',');
	for(uint32_t i = 0; i < tokens.size(); i++) {
		uint32_t index = std::stoi(tokens[i]);
		char c = (*putativeKey)[index];
		plaintext += c;
	}
	return plaintext;
}

uint32_t Decryptor::currentScore() {
	return dp->computeScore();
}

void Decryptor::printKey() {
	for (char x : *putativeKey) {
		if (x == ' ') {
			x = '!';
		}

		std::cout << x;
	}
	std::cout << std::endl;
}

void Decryptor::decrypt() {
	uint32_t rounds = 15;
	for(uint32_t i = 0; i < rounds; i++) {
		std::cout << "Rounds remaining: " << rounds - i << std::endl;
		performOneRound();
		uint32_t score = currentScore();
		if(score < bestScore) {
			bestScore = score;
			delete bestKey;
			bestKey = new std::vector<char>(*putativeKey);
			std::cout << "Better key found, with score " << bestScore << std::endl;
			printKey();
		}
		randomizeKey();
	}
	delete putativeKey;
	putativeKey = bestKey;
	dp->setKey(putativeKey);
}

void Decryptor::performOneRound() {
	// Understanding the boundary conditions of this is tricky, so:
	// The outer loop is a "gap size",
	// The inner loop is each column we might swap with a later one,
	// so for each gap size (starting with adjacent letters)
	// we loop over each column that has a gap column to swap with
	bool swaps = false;
	do {
		swaps = false;
		uint32_t currentScore = dp->computeScore();
		for(uint32_t gapSize = 1; gapSize < 106; gapSize++) {
			for(uint32_t column = 0; column < 106 - gapSize; column++) {
				uint32_t swapWith = column + gapSize;
				// If the two letters of the key at j and j+i are the same,
				char columnLetter = (*putativeKey)[column];
				char swapLetter = (*putativeKey)[swapWith];
				if(columnLetter == swapLetter) {
					continue;
				}
				dp->updateKey(column, swapWith);
				uint32_t newScore = dp->computeScore();
				// If we improved, use this new key as the putative key
				if(newScore < currentScore) {
					// Keep!
					currentScore = newScore;
					swaps = true;
				} else {
					// Otherwise, set our matrix back
					dp->updateKey(column, swapWith);
				}
			}
		}
	} while(swaps);
}