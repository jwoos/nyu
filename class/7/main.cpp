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

// O(n^2)
template <typename T>
void selectionSort(vector<T>& v) {
	for (int i = 0; i < v.size(); i++) {
		int min = i;
		for (int j = i + 1; j < v.size(); j++) {
			if (v[j] < v[min]) {
				min = j;
			}
		}
		T temp = v[min];
		v[temp] = v[i];
		v[i] = temp;
	}
}

// O(n*log(n))
template <typename T>
void setSort(vector<T>& v) {
	multiset<T> s;
	for (T i : v) {
		s.insert(i); // O(log(n))
	}

	v.clear();
	while (!s.empty()) {
		v.push_back(s.pop());
	}
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

template <typename T>
void shellSort(vector<T>& v) {
	for (int gap = v.size() / 2; gap > 0; gap /= 2) {
		for (int i = gap; i < v.size(); i++) {
			T temp = v[i];
			int j;

			for (j = i; j >= gap && temp < v[j - gap]; j-= gap) {
				v[j] = v[j - gap];
			}

			v[j] = temp;
		}
	}
}

int main() {
	srand(time(nullptr));
	vector<int> v;
	Timer t;

	for (int i = 1; i < 11; i++) {
		for (int j = 0; j < i * 1000000; j++) {
			v.push_back(rand());
		}

		t.reset();

		shellSort(v);

		double elapsed = t.elapsed();
		cout << "v.size() = " << v.size() << " elapsed = " << elapsed << endl;
		v.clear();
	}

	for (int i = 1; i < 11; i++) {
		for (int j = 0; j < i * 1000000; j++) {
			v.push_back(rand());
		}

		t.reset();

		insertionSort(v);

		double elapsed = t.elapsed();
		cout << "v.size() = " << v.size() << " elapsed = " << elapsed << endl;
		v.clear();
	}

	for (int i = 1; i < 11; i++) {
		for (int j = 0; j < i * 1000000; j++) {
			v.push_back(rand());
		}

		t.reset();

		selectionSort(v);

		double elapsed = t.elapsed();
		cout << "v.size() = " << v.size() << " elapsed = " << elapsed << endl;
		v.clear();
	}
}
