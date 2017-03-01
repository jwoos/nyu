#include "utils.hpp"

RNG::RNG(uint32_t lo = 0, uint32_t hi = 10) : lower(lo), upper(hi) {
	// seed the generator with random device
	generator.seed(rd());

	// use initial range to generate a uniform distribution
	dist = std::uniform_int_distribution<uint32_t>(lower, upper);
}

void RNG::setSeed(uint32_t seed) {
	generator.seed(seed);
}

void RNG::setBounds(uint32_t lo, uint32_t hi) {
	lower = lo;
	upper = hi;

	// generate a new distribution based on bounds
	dist = std::uniform_int_distribution<uint32_t>(lower, upper);
}

uint32_t RNG::getUpper() const {
	return upper;
}

uint32_t RNG::getLower() const {
	return lower;
}

uint32_t RNG::randomNumber() {
	return dist(generator);
}

std::vector<uint32_t>* generateRandomNumber(int lower, int upper, int amount) {
	std::mt19937 rng;
	std::random_device rd;

	rng.seed(rd());
	std::uniform_int_distribution<uint32_t> dist(lower, upper);

	std::vector<uint32_t>* v = new std::vector<uint32_t>();

	for (int i = 0; i < amount; i++) {
		uint32_t temp = dist(rng);
		v -> push_back(temp);
	}

	return v;
}


Permutation::Permutation(int size) : values(size), directions(size), positions(size) {
	for (int i = 0; i < size; i++) {
		values[i] = i;
		positions[i] = i;
		directions[i] = (i == 0 ? 0 : -1);
	}
}

int Permutation::LargestMobile() const {
	for (int i = values.size() - 1; i >= 0; i--) {
		if (directions[i] != 0) {
			return i;
		}
	}
	return -1;
}

// Implemented from https://en.wikipedia.org/wiki/Steinhaus%E2%80%93Johnson%E2%80%93Trotter_algorithm
bool Permutation::Advance() {
	int swap = LargestMobile();
	if (swap < 0) return false;

	int direction = directions[swap];
	int position = positions[swap];
	int destination = position + direction;
	int next = destination + direction;

	// Move the largest "mobile" number in the appropriate direction
	std::swap(positions[values[position]], positions[values[destination]]);
	std::swap(values[position], values[destination]);

	// If we've hit a wall (first position, last position, or a bigger number)
	// this number stops moving
	if (destination == 0 || destination == values.size() - 1) {
		directions[swap] = 0;
	}
	if (next >= 0 && next <= values.size() - 1 && values[next] > swap) {
		directions[swap] = 0;
	}

	// Reset all larger numbers to "moving" towards the element that just moved
	for (int i = swap + 1; i < values.size(); i++) {
		directions[i] = (positions[i] < destination) ? 1 : -1;
	}

	return true;
}

// Generate a list with the numbers 0 to amount
std::vector<uint32_t>* identityPermutation(int amount) {
	std::vector<uint32_t>* v = new std::vector<uint32_t>(amount);
	for (int i = 0; i < amount; i++) {
		(*v)[i] = i;
	}
	return v;
}

// Randomly shuffle the given list, using Knuth shuffles.
void shuffle(std::vector<uint32_t>* items) {
	std::mt19937 rng;
	std::random_device rd;

	rng.seed(rd());

	for (int i = 0; i < items -> size() - 1; i++) {
		std::uniform_int_distribution<uint32_t> dist(i + 1, items -> size() - 1);
		int swapWith = dist(rng);
		std::swap((*items)[i], (*items)[swapWith]);
	}
}

std::map<char, uint32_t>* generateFrequencyMap() {
	std::map<char, uint32_t> literal = {
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

	std::map<char, uint32_t>* m = new std::map<char, uint32_t>(literal);

	return m;
}
