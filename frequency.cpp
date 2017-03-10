#include "frequency.hpp"

std::map<char, uint32_t> calculateCharFrequency(const std::string& text) {
	std::map<char, uint32_t> freq;

	for (uint32_t i = 0; i < text.size(); i++) {
		char c = text[i];

		if (!freq[c]) {
			freq[c] = 1;
		} else {
			freq[c]++;
		}
	}

	return freq;
}

std::map<char, uint32_t> generateFrequencyMap() {
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

	return literal;
}

std::map<std::string, uint32_t> generateDigramFrequencyMap() {
	std::map<std::string, uint32_t> literal = {
		{" ", 0}
	};

	return literal;
}

