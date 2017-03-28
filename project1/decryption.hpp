#ifndef ENCRYPTION_DECRYPT_H
#define ENCRYPTION_DECRYPT_H

#include "utils.hpp"
#include "frequency.hpp"
#include "key.hpp"
#include "matrix.hpp"
#include "dictionary.hpp"
#include "text.hpp"

class Decryptor {
	public:
		Decryptor(std::string&, uint32_t);
		void performOneRound(bool countWords = false);
		void decrypt();
		uint32_t decryptBruteForce();
		std::vector<char>* currentCandidateKey();
		std::string currentCandidatePlaintext();
		uint32_t currentScore(bool countWords = false);
		void initialKey();
		void randomizeKey();
		void printKey();
		void setKey(std::vector<char>*);

	private:
		std::string& cipherText;
		EMatrix* e;
		DCipherMatrix* dc;
		DPlainMatrix* dp;
		std::map<char, uint32_t> frequencyMap;

		std::vector<char>* putativeKey;
		std::vector<char>* bestKey;
		uint32_t bestScore;

		std::set<std::string> dictionary;
};

class CPADecryptor {
	public:
		CPADecryptor(const std::string&);
		uint32_t tentativePlaintextByIdentifier();
		std::string getPlaintext(uint32_t);
		std::map<char, std::vector<uint32_t>> getIdentifier(uint32_t);

	private:
		std::vector<char> potentialKey;
		std::vector<std::string> possiblePlaintexts;
		std::vector<std::map<char, std::vector<uint32_t>>> identifiers;
		std::vector<std::string> ciphertext;
};

#endif
