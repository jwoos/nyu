#ifndef ENCRYPTION_DECRYPT_H
#define ENCRYPTION_DECRYPT_H

#include "utils.hpp"
#include "frequency.hpp"
#include "key.hpp"
#include "matrix.hpp"

class Decryptor {
	public:
	Decryptor(std::string&);
	void performOneRound();
	std::string decrypt();
	std::vector<char>* currentCandidateKey();
	std::string currentCandidatePlaintext();
	uint32_t currentScore();

	private:
	std::string& cipherText;
	EMatrix* e;
	DCipherMatrix* dc;
	DPlainMatrix* dp;
	std::map<char, uint32_t> frequencyMap;

	std::vector<char>* putativeKey;
};

#endif
