#include <cstdlib>
#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <ctime>

using namespace std;

class Timer {
	public:
		Timer() {
			start = clock();
		}

		double elapsed() const {
			return (clock() - start) / CLOCKS_PER_SEC;
		}

		void reset() {
			start = clock();
		}
	private:
		double start;
};

template <typename T>
void merge(vector<T>& v, vector<T>& temp, int leftStart, int leftEnd, int rightEnd) {
	int rightStart = leftEnd + 1;
	int tempStart = leftStart;
	int tempPosition = leftStart;

	while (leftStart <= leftEnd && rightStart <= rightEnd) {
		if (v[leftStart] < v[rightStart]) {
			temp[tempPosition++] = v[leftStart++];
		} else {
			temp[tempPosition++] = v[rightStart++];
		}
	}

	while (leftStart <= leftEnd) {
		temp[tempPosition++] = v[leftStart++];
	}

	while (rightStart <= rightEnd) {
		temp[tempPosition++] = v[rightStart++];
	}

	for (; tempStart <= rightEnd; tempStart++) {
		v[tempStart] = temp[tempStart];
	}
}

template <typename T>
void mergeSort(vector<T>& v, vector<T>& temp, int start, int end) {
	if (start >= end) {
		return;
	}

	int mid = (start + end) / 2;
	mergeSort(v, temp, start, mid);
	mergeSort(v, temp, mid + 1, end);
}

// O(n*log(n))
template <typename T>
void mergeSort(vector<T>& v) {
	vector<T> temp;
	temp.resize(v.size());
	mergeSort(v, temp, 0, v.size() - 1);
}

template <typename T>
void insertionSort(vector<T>& v) {
	for (int i = 1; i < v.size(); i++) {
		T temp = v[i];

		int j = i;
		for (j = i; j > 0 && v[j] < v[j - 1]; j--) {
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
}

template <typename T>
void quickSort() {}

int main() {
	srand(time(nullptr));
	vector<int> v;
	Timer t;
}
