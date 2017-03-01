#ifndef ENCRYPTION_UTILS_H
#define ENCRYPTION_UTILS_H

#include <random>
#include <vector>
#include <map>
#include <set>

std::vector<unsigned int>* generateRandomNumber(int, int, int);

std::vector<unsigned int>* identityPermutation(int);
void shuffle(std::vector<unsigned int>*);

std::map<char, unsigned int>* generateFrequencyMap();

struct Permutation 
{
	std::vector<unsigned int> values;
	std::vector<int> directions;
	std::vector<unsigned int> positions;

	explicit Permutation(int size);
	int LargestMobile() const;
	bool Advance();
};

#endif
