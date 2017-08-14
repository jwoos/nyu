#include <cstdlib>
#include <iostream>
#include <string>
#include <cmath>
#include <ctime>

using namespace std;

class Elephant {};
ostream& operator<<(ostream& out, const Elephant& rhs) {
	out << "ELEPHANT";
	return out;
}

template <class T>
class SortedArray {
	private:
		T* data;
		int capacity;
		int numOfElements;
	public:
		SortedArray() : capacity(5), numOfElements(0) {
			data = new T[capacity];
		}

		SortedArray(const SortedArray& rhs) : capacity(5), numOfElements(5), data(nullptr) {
			*this = rhs;
		}

		virtual ~SortedArray() {
			delete [] data;
		}

		SortedArray& operator=(const SortedArray& rhs);

		void push(const T& newData);

		void pop(const T& toRemove);

		int find(const T& toFind) const;

		void resize(int newSize);

		T& operator[](int index) {
			return data[index];
		}

		T operator[](int index) const {
			return data[index];
		}
};

template<class T>
SortedArray<T>& SortedArray<T>::operator=(const SortedArray<T>& rhs) {
	if (this == &rhs) {
		return *this;
	}
	delete [] data;
	capacity = rhs.numOfElements;
	data = new T[capacity];
	for (int i = 0; i < numOfElements; i++) {
		data[i] = rhs.data[i];
	}

	return *this;
}

template<class T>
void SortedArray<T>::push(const T& newData) {
	if (numOfElements == capacity) {
		resize(numOfElements * 2);
	}
	int i = numOfElements;
	for (;data[i - 1] > newData; i--) {
		data[i] = data[i - 1];
	}

	data[i] = newData;
	numOfElements++;
}

template<class T>
void SortedArray<T>::resize(int newSize) {
	T* temp = new T[newSize];
	if (newSize < numOfElements) {
		numOfElements = newSize;
	}

	for (int i = 0; i < numOfElements; i++) {
		temp[i] = data[i];
	}

	delete [] data;
	data = temp;
	capacity = newSize;
}

template<class T>
int SortedArray<T>::find(const T& toFind) const {
	int start = 0;
	int end = numOfElements;
	int middle = (start + end ) / 2;
	while (start <= end && data[middle] != toFind) {
		if (data[middle] > toFind) {
			start = middle - 1;
		} else {
			end = middle - 1;
		}

		middle = (start + end) / 2;
	}

	if (data[middle] == toFind) {
		return middle;
	}

	return -1;
}

/*
 *template<class T>
 *void SortedArray<T>::pop(const T& toRemove) {
 *    int index = find(toRemove);
 *    if (index != -1) {
 *        for (int i = 0; i < numOfElements - 1)
 *    }
 *}
 */

template <class T> // template <typename T>
void swapVal(T& a, T& b) {
	T temp = a;
	a = b;
	b = temp;
}

template <class T>
void printArr(T* arr, int size) {
	for (int i = 0; i < size; i++) {
		cout << "arr[" << i << "] = " << arr[i] << endl;
	}
}

template <class T>
int findIndexOfMin(T* arr, int size, int start=0) {
	int minIndex = 0;
	for (int i = start + 1; i < size; i++) {
		if (arr[i] < arr[minIndex]) {
			minIndex = i;
		}
	}
	return minIndex;
}

template <class T>
void sortArr(T* arr, int size) {
	for (int i = 0; i < size; i++) {
		int indexOfMin = findIndexOfMin(arr, size, i);
		swap(arr[i], arr[indexOfMin]);
	}
}

int main() {
	int x(500), y(50);
	cout << "x = " << x << endl;
	cout << "y = " << y << endl;
	swapVal(x, y);
	cout << "x = " << x << endl;
	cout << "y = " << y << endl;

	int* arr = new int[20];
	for (int i = 0; i < 20; i++) {
		arr[i] = i * 2;
	}
	printArr(arr, 20);

	char* charArr = new char[26];
	for (int i = 0; i < 26; i++) {
		arr[i] = 'A' + i;
	}
	printArr(charArr, 26);

	string *sArr = new string[5];
	sArr[0] = "Daniel";
	sArr[1] = "John";
	sArr[2] = "James";
	sArr[3] = "Gloria";
	sArr[4] = "Betty";
	sortArr(sArr, 5);

	srand(time(nullptr));
	for (int i = 0; i < 26; i++) {
		arr[i] = rand() % 1000;
	}
	sortArr(arr, 26);

	SortedArray<int> s;
	for (int i = 0; i < 20; i++) {
		s.push(rand() % 1000);
	}
}
