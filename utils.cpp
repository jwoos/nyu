#include "utils.hpp"

// BEGIN: RNG
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
// END: RNG


// BEGIN: PERMUTATION
Permutation::Permutation(uint32_t size) : values(size), directions(size), positions(size) {
	for (uint32_t i = 0; i < size; i++) {
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
	if (destination == 0 || destination == (int)values.size() - 1) {
		directions[swap] = 0;
	}

	if (next >= 0 && next <= (int)values.size() - 1 && (int)values[next] > swap) {
		directions[swap] = 0;
	}

	// Reset all larger numbers to "moving" towards the element that just moved
	for (uint32_t i = swap + 1; i < values.size(); i++) {
		directions[i] = ((int)positions[i] < destination) ? 1 : -1;
	}

	return true;
}
// END: PERMUTATION

// Generate a list with the numbers 0 to amount
std::vector<uint32_t>* identityPermutation(uint32_t amount) {
	std::vector<uint32_t>* input = new std::vector<uint32_t>(amount);
	std::iota(input -> begin(), input -> end(), 0);
	return input;
}

// Randomly shuffle the given list, using Knuth shuffles.
void shuffle(std::vector<uint32_t>* items) {
	std::mt19937 rng;
	std::random_device rd;

	rng.seed(rd());

	for (uint32_t i = 0; i < items -> size() - 1; i++) {
		std::uniform_int_distribution<uint32_t> dist(i + 1, items -> size() - 1);
		uint32_t swapWith = dist(rng);
		std::swap((*items)[i], (*items)[swapWith]);
	}
}

std::map<char, uint32_t> generateIndexMap() {
	std::map<char, uint32_t> literal = {
		{'a', 0},
		{'b', 1},
		{'c', 2},
		{'d', 3},
		{'e', 4},
		{'f', 5},
		{'g', 6},
		{'h', 7},
		{'i', 8},
		{'j', 9},
		{'k', 10},
		{'l', 11},
		{'m', 12},
		{'n', 13},
		{'o', 14},
		{'p', 15},
		{'q', 16},
		{'r', 17},
		{'s', 18},
		{'t', 19},
		{'u', 20},
		{'v', 21},
		{'w', 22},
		{'x', 23},
		{'y', 24},
		{'z', 25},
		{' ', 26}
	};

	return literal;
}

void flush() {
	std::cout << std::endl;
}

std::vector<std::string> split(const std::string& input, char delimiter) {
	std::vector<std::string> output;

	std::stringstream ss;
	ss.str(input);
	std::string item;
	while (std::getline(ss, item, delimiter)) {
		output.push_back(item);
	}

	return output;
}

std::vector<uint32_t> stringToUnsignedInt(const std::vector<std::string>& input) {
	std::vector<uint32_t> v;

	for (std::vector<std::string>::const_iterator it = input.begin(); it != input.end(); it++) {
		v.push_back(std::stoul(*it, nullptr, 10));
	}

	return v;
}

uint32_t getIndexForChar(char x) {
	return x == ' ' ? 26 : (uint32_t)(x - 'a');
}

char getCharForIndex(uint32_t x) {
	return x == 26 ? ' ' : (x + 'a');
}
