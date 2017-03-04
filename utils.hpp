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

class Matrix {
	public:
		explicit Matrix(uint32_t, uint32_t);
		void swapRow(uint32_t, uint32_t);
		void swapColumn(uint32_t, uint32_t);
		void printMatrix();
		void increment(uint32_t, uint32_t);
		virtual void populateMatrix(const std::string&) = 0;

	protected:
		std::vector<std::vector<uint32_t>> matrix;

	private:
		uint32_t rows;
		uint32_t columns;
};

class DigramFreqMatrix : public Matrix {
	public:
		explicit DigramFreqMatrix(uint32_t, uint32_t);
		void populateMatrix(const std::string&);
};

std::vector<uint32_t>* identityPermutation(int);
void shuffle(std::vector<uint32_t>*);

std::map<char, uint32_t> generateFrequencyMap();

std::map<char, uint32_t> calculateCharFrequency(const std::string&);

void flush();

std::vector<std::string> split(const std::string&, char);

std::vector<uint32_t> stringToUnsignedInt(const std::vector<std::string>&);

struct Permutation {
	std::vector<uint32_t> values;
	std::vector<int> directions;
	std::vector<uint32_t> positions;

	explicit Permutation(int size);
	int LargestMobile() const;
	bool Advance();
};

#endif
