#include "decryption.hpp"

Decryptor::Decryptor(std::string& cipherText): cipherText(cipherText) {
	// Fill in our known quantities
	frequencyMap = generateFrequencyMap();
	// Generate an initial putative key
	putativeKey = new std::vector<char>(generateKey(frequencyMap));
	// Initialize and wire up our matrices
	e = new EMatrix(27, 27);
	dc = new DCipherMatrix(106, 106);
	dp = new DPlainMatrix(27, 27);
	dp->setKey(putativeKey);
	dp->setFrequencyMap(&frequencyMap);
	dp->setExpectedMatrix(e);
	dp->setCipherMatrix(dc);

	// Fill our matrices with the correct values
	dc->populateMatrix(cipherText);
	dp->populateMatrix();
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

void Decryptor::performOneRound() {
	uint32_t currentScore = dp->computeScore();
	// Understanding the boundary conditions of this is tricky, so:
	// i represents our "gap size",
	// j represents our first column,
	// so for each gap size (starting at adjacent letters)
	// we loop over each column that has a gap column to swap with
	for(uint32_t gapSize = 1; gapSize < 2; gapSize++) {
		for(uint32_t column = 0; column < 106 - gapSize; column++) {
			uint32_t swapWith = column + gapSize;
			// If the two letters of the key at j and j+i are the same,
			if((*putativeKey)[column] == (*putativeKey)[swapWith]) {
				continue;
			}
			dp->updateKey(column, swapWith);
			uint32_t newScore = dp->computeScore();
			// If we improved, use this new key as the putative key
			if(newScore <= currentScore) {
				// Swap the key as well
				currentScore = newScore;
			} else {
				// Otherwise, set our matrix back
				dp->updateKey(column, swapWith);

				if(currentScore != dp->computeScore()) {
					std::cout << std::endl;
					std::cout << "WARNING: " << std::endl;
					std::cout << "After swapping " << column << " and " << swapWith << " and swapping back, the score didn't return to normal." << std::endl;
					std::cout << "Should be: " << currentScore << ", but is " << dp->computeScore() << std::endl;
				}
			}
		}
		std::cout << std::endl;
	}
}