#include <iostream>
#include <cstdlib>

#include "combination-lock.h"

using namespace std;

CombinationLock::CombinationLock(int one, int two, int three) : combination(new int[3]), state(false) {
	combination[0] = one;
	combination[1] = two;
	combination[2] = three;
}

CombinationLock::CombinationLock(int* data) : combination(new int[3]), state(false) {
	for (int i = 0; i < 3; i++) {
		combination[i] = data[i];
	}
}

CombinationLock::~CombinationLock() {
	delete [] combination;
}

void CombinationLock::open(int* combinationArr) {
	for (int i = 0; i < 3; i++) {
		if (combinationArr[i] != combination[i]) {
			std::cout << "Wrong combination. Aborting..." << endl;
			return;
		}
	}

	state = true;
	cout << "Unlocked" << endl;
}

void CombinationLock::changeCombo(int* combinationArr, int* newCombination) {
	for (int i = 0; i < 3; i++) {
		if (combinationArr[i] != combination[i]) {
			std::cout << "Wrong combination. Aborting..." << endl;
			return;
		}
	}

	for (int i = 0; i < 3; i++) {
		combination[i] = newCombination[i];
	}

	cout << "Combination changed" << endl;
}
