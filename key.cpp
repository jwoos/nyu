#include "key.hpp"

std::vector<char> generateKey(uint32_t size) {
	std::vector<char> v(size);
	RNG rng(0, 26);

	for (std::vector<char>::iterator it = v.begin(); it != v.end(); it++) {
		*it = getCharForIndex(rng.randomNumber());
	}

	return v;
}
