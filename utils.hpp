#ifndef ENCRYPTION_UTILS_H
#define ENCRYPTION_UTILS_H

#include <random>
#include <vector>
#include <map>
#include <set>

std::vector<unsigned int>* generateRandomNumber(int, int, int);

std::vector<unsigned int>* generateDistinctRandomNumbers(int, int, int);

std::map<char, unsigned int>* generateFrequencyMap();

#endif
