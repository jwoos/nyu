#include <map>
#include <set>

#include "encryption.hpp"
#include "utils.hpp"

using namespace std;

map<char, unsigned int*> generateKeys() {
	map<char, set<unsigned int>*>* m = new map<char, set<unsigned int>*>();
	map<char, unsigned int>* frequencyMap = generateFrequencyMap();
	set<unsigned int> used;
}

int main() {}
