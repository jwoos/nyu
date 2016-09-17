/*
 * name: Junwoo Shin
 * class: Section E
 * compiler: g++-6 (Ubuntu 6.2.0-3ubuntu11~16.04) 6.2.0 20160901
 * commands: g++-6 -Wall -g -std=c++14 -c combination-lock.cpp -o combination-lock.o
 *           g++-6 -Wall -g -std=c++14 1.cpp combination-lock.o -o 1.out
 */

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

#include "combination-lock.h"
#include "dynarray.h"

using namespace std;

void testCombinationLock() {
	CombinationLock lock(1, 2, 3);

	int combo[] = {1, 2, 4};
	lock.open(combo);

	combo[2] = 3;
	lock.open(combo);

	int newCombo[] = {1, 4, 9};

	lock.changeCombo(combo, newCombo);
	lock.open(combo);

	lock.open(newCombo);

	// copying is not allowed
	//CombinationLock newLock(lock);
}

void testDynArray() {
	DynArray<int> intDynArray;

	size_t prevCapacity = 0;
	for (int i = 0; i < 100; i++) {
		intDynArray.push_back(i);
		if (intDynArray.size() > prevCapacity) {
			prevCapacity = intDynArray.capacity();
			cout << "size=" << intDynArray.size() << " | capacity=" << prevCapacity << endl;
		}
	}
	cout << "original: " << "size=" << intDynArray.size() << " | capacity=" << intDynArray.capacity() << endl;

	for (int i = 0; i < 5; i ++) {
		cout << intDynArray[i] << ' ';
	}
	cout << endl;

	intDynArray.push_back(100);

	DynArray<int> copyIntDynArray(intDynArray);

	for (int i = 0; i < 5; i ++) {
		cout << copyIntDynArray[i] << ' ';
	}
	cout << endl;
	cout << "copy: " << "size=" << copyIntDynArray.size() << " | capacity=" << copyIntDynArray.capacity() << endl;

	copyIntDynArray.push_back(1);
	copyIntDynArray[0] = 10000;
	cout << copyIntDynArray[0] << endl;

	DynArray<char> charDynArray;

	for (int i = 0; i < 26; i++) {
		charDynArray.push_back('A' + i);
	}

	for (int i = 0; i < charDynArray.size(); i ++) {
		cout << charDynArray[i];
	}
	cout << endl;

	charDynArray.pop_back();

	for (int i = 0; i < charDynArray.size(); i ++) {
		cout << charDynArray[i];
	}
	cout << endl;

	charDynArray.resize(1);
	for (int i = 0; i < charDynArray.size(); i ++) {
		cout << charDynArray[i];
	}
	cout << endl;
}

double totalPrice(map<int, double> priceMap, vector<int> items) {
	double total;

	for (int id : items) {
		total += priceMap[id];
	}

	return total;
}

int main() {
	map<int, double> priceMap;

	ifstream file;
	file.open("HW1data.txt");

	if (!file) {
		cout << "Error opening file" << endl;
		exit(1);
	}

	int id;
	double price;

	while(file >> id >> price) {
		cout << "priceMap[" << id << "] = " << price << endl;
		priceMap[id] = price;
	}

	file.close();

	vector<int> items = {1, 99, 47, 22};

	cout << "totalPrice = " << totalPrice(priceMap, items) << endl;
}
