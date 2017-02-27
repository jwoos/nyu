#include "utils.hpp"
#include "encryption.hpp"

#include <iostream>
#include <vector>

using namespace std;

int main() {
	vector<unsigned int> v;
	v = *generateRandomNumber(1, 100, 10);

	for (int i = 0; i < v.size(); i++) {
		cout << v[i] << endl;
	}
}
