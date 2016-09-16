#include <iostream>
#include <cstdlib>

#include "combination-lock.h"

using namespace std;

CombinationLock::CombinationLock(int * combinationArr) : combination(nullptr), state(false) {
	for (int i = 0; i < 3; i++) {
		combination[i] = combinationArr[i];
	}
}

CombinationLock::CombinationLock(const CombinationLock& original) {
	cout << "You cannot copy a combination lock!" << endl;
	exit(1);
}

CombinationLock::~CombinationLock() {
	delete [] combination;
}

void CombinationLock::open(int* combinationArr) {
	for (int i = 0; i < 3; i++) {
		if (combinationArr[i] != combination[i]) {
			std::cout << "Wrong combination! Aborting..." << endl;
			return;
		}
	}

	state = true;
}

void CombinationLock::changeCombo(int* combinationArr, int* newCombination) {
	for (int i = 0; i < 3; i++) {
		if (combinationArr[i] != combination[i]) {
			std::cout << "Wrong combination! Aborting..." << endl;
			return;
		}
	}
}
