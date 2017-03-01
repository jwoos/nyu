#include "utils.hpp"

std::vector<unsigned int>* generateRandomNumber(int lower, int upper, int amount) {
	std::mt19937 rng;
	std::random_device rd;

	rng.seed(rd());
	std::uniform_int_distribution<unsigned int> dist(lower, upper);

	std::vector<unsigned int>* v = new std::vector<unsigned int>();

	for (int i = 0; i < amount; i++) {
		unsigned int temp = dist(rng);
		v -> push_back(temp);
	}

	return v;
}

// Generate a list with the numbers 0 to amount
std::vector<unsigned int>* identityPermutation(int amount) {
	std::vector<unsigned int>* v = new std::vector<unsigned int>(amount);
	for(int i = 0; i < amount; i++) {
		(*v)[i] = i;
	}
	return v;
}

// Randomly shuffle the given list, using Knuth shuffles.
void shuffle(std::vector<unsigned int>* items) {
	std::mt19937 rng;
	std::random_device rd;

	rng.seed(rd());

	for(int i = 0; i < items->size() - 1; i++) {
		std::uniform_int_distribution<unsigned int> dist(i+1, items->size() - 1);
		int swapWith = dist(rng);
		std::swap((*items)[i], (*items)[swapWith]);
	}
}

std::map<char, unsigned int>* generateFrequencyMap() {
	std::map<char, unsigned int> literal = {
		{' ', 19},
		{'a', 7},
		{'b', 1},
		{'c', 2},
		{'d', 4},
		{'e', 10},
		{'f', 2},
		{'g', 2},
		{'h', 5},
		{'i', 6},
		{'j', 1},
		{'k', 1},
		{'l', 3},
		{'m', 2},
		{'n', 6},
		{'o', 6},
		{'p', 2},
		{'q', 1},
		{'r', 5},
		{'s', 5},
		{'t', 7},
		{'u', 2},
		{'v', 1},
		{'w', 2},
		{'x', 1},
		{'y', 2},
		{'z', 1}
	};

	std::map<char, unsigned int>* m = new std::map<char, unsigned int>(literal);

	return m;
}
