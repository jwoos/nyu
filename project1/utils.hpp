#ifndef ENCRYPTION_UTILS_H
#define ENCRYPTION_UTILS_H

#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <map>
#include <random>
#include <set>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

class RNG {
	public:
		// uniform constructor
		RNG(uint32_t lo = 0, uint32_t hi = 10, const std::string& type = "uniform");
		// discrete constructor
		RNG(const std::vector<uint32_t>&, const std::string& type = "discrete");
		void setSeed(uint32_t);
		void setBounds(uint32_t, uint32_t);
		void setBounds(const std::vector<uint32_t>&);
		uint32_t getUpper() const;
		uint32_t getLower() const;
		uint32_t randomNumber();

	private:
		uint32_t lower;
		uint32_t upper;
		std::string distType;
		std::mt19937 generator;
		std::random_device rd;
		std::uniform_int_distribution<uint32_t> uniform;
		std::discrete_distribution<uint32_t> discrete;
};

std::vector<uint32_t>* identityPermutation(uint32_t);

void shuffle(std::vector<uint32_t>*);

void shuffle(std::vector<char>&);

std::map<char, uint32_t> generateIndexMap();

uint32_t getIndexForChar(char);

char getCharForIndex(uint32_t);

void flush();

std::vector<std::string> split(const std::string&, char);

std::vector<uint32_t> stringToUnsignedInt(const std::vector<std::string>&);

struct Permutation {
	std::vector<uint32_t> values;
	std::vector<int> directions;
	std::vector<uint32_t> positions;

	explicit Permutation(uint32_t size);
	int LargestMobile() const;
	bool Advance();
};

#endif
