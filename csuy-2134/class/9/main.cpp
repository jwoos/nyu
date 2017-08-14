#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

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
void insertionSort(vector<T>& v, int start, int end) {
	for (int i = start + 1; i <= end; i++) {
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

class Person {
	public:
		string name;
		int age;
		double weight;
	private:
};

class LessThanOnName {
	public:
		bool operator()(const Person& lhs, const Person& rhs) const {
			return lhs.name < rhs.name;
		}
};

template <typename T, typename Comparator>
void quickSort(vector<T>& v, Comparator c) {
	quickSort(v, 0, v.size() - 1, c);
}

int main() {
	srand(time(nullptr));
	Timer t;
	vector<int> v;

	for (int i = 1; i < 11; i++) {
		for (int j = 0; j < i * 1000000; j++) {
			v.push_back(rand());
		}

		t.reset();

		quickSort(v);

		double elapsed = t.elapsed();
		cout << "v.size() = " << v.size() << " elapsed = " << elapsed << endl;
		v.clear();
	}
}
