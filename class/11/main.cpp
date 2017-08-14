#include <cstdlib>
#include <iostream>
#include <vector>
#include <set>
#include <string>

using namespace std;

class Person {
	public:
		void speak() const {
			cout << "hello" << endl;
		}
};

class Elephant {
	public:
		void makeSound() const {
			cout << "BOOOOV" << endl;
		}
};

class ElephantWrapper {};

template <typename T>
void sortUsingPointers(vector<T>& v) {
	vector<T*> vptr;

	for (T& t : v) {
		vptr.push_back(&t);
	}

	insertionSortPointers(vptr, 0, vptr.size() - 1);

	vector<T> temp;
	for (T* tptr : vptr) {
		temp.push_back(*tptr);
	}

	move(v, temp);
}

template <typename T>
void insertionSortPointers(vector<T>& v, int start, int end) {
	for (int i = start + 1; i <= end; i++) {
		T temp = v[i];

		int j = i;
		for (j = i; j > 0 && *temp < *v[j - 1]; j--) {
			v[j] = v[j - 1];
		}

		v[j] = temp;
	}
}

const int MIN_SIZE = 10;

template <typename T>
void quickSort(vector<T>& v, int start, int end) {
	if (start + MIN_SIZE > end) {
		insertionSort(v, start, end);
	}

	int middle = (start + end) / 2;
	if (v[middle] < v[start]) {
		swap(v[middle], v[start]);
	}
	if (v[end] < v[start]) {
		swap(v[end], v[start]);
	}
	if(v[end] < v[middle]) {
		swap(v[end], v[middle]);
	}

	T pivot = v[middle];
	swap(v[middle], v[end - 1]);
	int i = start;
	int j = end - 1;

	while (true) {
		while (v[++i] < pivot) {}

		while (pivot < v[--j]) {}

		if (i < j) {
			swap(v[i], v[j]);
		} else {
			break;
		}
	}

	swap(v[i], v[end - 1]);

	quickSort(v, start, i - 1);
	quickSort(v, i + 1, end);
}

template <typename T>
void quickSort(vector<T>& v) {
	quickSort(v, 0, v.size() - 1);
}

/*
 *template <typename T, typename Comparator>
 *void quickSort(vector<T>& v, Comparator c) {
 *    quickSort(v, 0, v.size() - 1, c);
 *}
 */

double recursivePower(int base, int expo) {
	if (expo == 0) {
		return 1;
	} else if (expo < 0) {
		return 1 / recursivePower(base, -expo);
	}

	return base * recursivePower(base, expo - 1);
}

int main() {

}

