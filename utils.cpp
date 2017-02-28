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

std::vector<unsigned int>* generateDistinctRandomNumbers(int lower, int upper, int amount) {
	std::mt19937 rng;
	std::random_device rd;

	rng.seed(rd());
	std::uniform_int_distribution<unsigned int> dist(lower, upper);

	std::set<unsigned int> s;
	std::vector<unsigned int>* v = new std::vector<unsigned int>();

	while (s.size() < amount) {
		unsigned int temp = dist(rng);

		if (!s.count(temp)) {
			s.insert(temp);
			v -> push_back(temp);
		}
	}

	return v;

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
