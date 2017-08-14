#include "key.hpp"

std::vector<char> generateKey(uint32_t size) {
	std::vector<char> v(size);
	RNG rng(0, 26, "uniform");

	for (std::vector<char>::iterator it = v.begin(); it != v.end(); it++) {
		*it = getCharForIndex(rng.randomNumber());
	}

	return v;
}

std::vector<char> generateKey(const std::map<char, uint32_t>& fm) {
	std::vector<char> v;

	uint32_t cnt;

	for (std::map<char, uint32_t>::const_iterator it = fm.begin(); it != fm.end(); it++) {
		cnt = it -> second;

		for (uint32_t i = 0; i < cnt; i++) {
			v.push_back(it -> first);
		}
	}

	shuffle(v);

	return v;
}
