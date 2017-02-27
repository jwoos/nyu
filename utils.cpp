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
