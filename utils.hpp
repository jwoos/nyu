#ifndef ENCRYPTION_UTILS_H
#define ENCRYPTION_UTILS_H

#include <iostream>
#include <random>
#include <vector>
#include <map>
#include <set>
#include <string>

class RNG {
	public:
		RNG(uint32_t, uint32_t);
		void setSeed(uint32_t);
		void setBounds(uint32_t, uint32_t);
		uint32_t getUpper() const;
		uint32_t getLower() const;
		uint32_t randomNumber();

	private:
		uint32_t lower;
		uint32_t upper;
		std::mt19937 generator;
		std::random_device rd;
		std::uniform_int_distribution<uint32_t> dist;
};

std::vector<uint32_t>* generateRandomNumber(int, int, int);

std::vector<uint32_t>* identityPermutation(int);
void shuffle(std::vector<uint32_t>*);

std::map<char, uint32_t> generateFrequencyMap();

std::map<char, uint32_t> calculateCharFrequency(const std::string&);

void flush();

struct Permutation {
	std::vector<uint32_t> values;
	std::vector<int> directions;
	std::vector<uint32_t> positions;

	explicit Permutation(int size);
	int LargestMobile() const;
	bool Advance();
};

#endif
