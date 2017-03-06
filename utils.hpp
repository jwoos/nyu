#ifndef ENCRYPTION_UTILS_H
#define ENCRYPTION_UTILS_H

#include <iostream>
#include <random>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <utility>

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

class DigramFreqMatrix {
	public:
		explicit DigramFreqMatrix(uint32_t, uint32_t);
		void swapRow(uint32_t, uint32_t);
		void swapColumn(uint32_t, uint32_t);
		std::vector<uint32_t> getRow(uint32_t);
		std::vector<uint32_t> getColumn(uint32_t);
		void clearMatrix();
		void printMatrix();
		uint32_t size();

		std::vector<uint32_t>& operator[](const uint32_t index);

	protected:
		std::vector<std::vector<uint32_t>> matrix;
		uint32_t rows;
		uint32_t columns;

	private:
};

class EMatrix : public DigramFreqMatrix {
	public:
		explicit EMatrix(uint32_t, uint32_t);
};

class DCipherMatrix : public DigramFreqMatrix {
	public:
		explicit DCipherMatrix(uint32_t, uint32_t);
		void populateMatrix(const std::string&);
};

class DPlainMatrix : public DigramFreqMatrix {
	public:
		explicit DPlainMatrix(uint32_t, uint32_t);
		void updateMatrix(uint32_t, uint32_t);
		void updateKey(uint32_t, uint32_t);
		uint32_t computeScore();
		int getFrequencyForChar(char);
		void populateMatrix();
		void setKey(std::vector<char>*);
		void setFrequencyMap(std::map<char, uint32_t>*);
		void setCipherMatrix(DCipherMatrix*);
		void setExpectedMatrix(EMatrix*);

	private:
		std::vector<char>* key;
		std::map<char, uint32_t>* frequencyMap;
		std::map<char, uint32_t>* indexMap;
		DCipherMatrix* cipherMatrix;
		EMatrix* expectedMatrix;
};

std::vector<uint32_t>* identityPermutation(uint32_t);
void shuffle(std::vector<uint32_t>*);

std::map<char, uint32_t> generateFrequencyMap();

std::map<char, uint32_t> generateIndexMap();

std::map<char, uint32_t> calculateCharFrequency(const std::string&);

uint32_t getIndexForChar(char);

char getCharForIndex(uint32_t);

void flush();

std::vector<std::string> split(const std::string&, char);

std::vector<uint32_t> stringToUnsignedInt(const std::vector<std::string>&);

std::vector<char> generateKey(uint32_t);

struct Permutation {
	std::vector<uint32_t> values;
	std::vector<int> directions;
	std::vector<uint32_t> positions;

	explicit Permutation(uint32_t size);
	int LargestMobile() const;
	bool Advance();
};

#endif
