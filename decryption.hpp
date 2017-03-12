#ifndef ENCRYPTION_DECRYPT_H
#define ENCRYPTION_DECRYPT_H

#include "utils.hpp"
#include "frequency.hpp"
#include "key.hpp"
#include "matrix.hpp"
#include "dictionary.hpp"

class Decryptor {
	public:
	Decryptor(std::string&);
	void performOneRound();
	void decrypt();
	std::vector<char>* currentCandidateKey();
	std::string currentCandidatePlaintext();
	uint32_t currentScore();
	void initialKey();
	void randomizeKey();
	void printKey();

	private:
	std::string& cipherText;
	EMatrix* e;
	DCipherMatrix* dc;
	DPlainMatrix* dp;
	std::map<char, uint32_t> frequencyMap;

	std::vector<char>* putativeKey;
	std::vector<char>* bestKey;
	uint32_t bestScore;
};

#endif
