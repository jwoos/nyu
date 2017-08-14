#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <list>

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

// O(n^3)
int mcss(vector<int>& v) {
	int max = 0;

	for (int i = 0; i < v.size(); i++) {
		for (int j = i; j < v.size(); j++) {
			int sum = 0;

			for (int k = i; k <= j) {
				sum += v[k]; // CLoC
			}

			if (sum > max) {
				max = sum;
			}
		}
	}

	return max;
}

// O(n^2)
int mcss2(vector<int>& v) {
	int max = 0;

	for (int i = 0; i < v.size(); i++) {
		int sum = 0;

		for (int j = i; j < v.size(); j++) {
			sum += v[j];

			if (sum > max) {
				max = sum;
			}
		}
	}

	return max;
}

// O(n)
int mcss3() {
	int max = 0;
	int sum = 0;

	for (int i = 0; i < v.size(); i++) {
		sum += v[i];
		if (sum > max) {
			max = sum;
		}

		if (sum < 0) {
			sum = 0;
		}
	}

	return max;
}

void func7(vector<int>& v) {}

double fib(int n) {
	if (n > 1) {
		return fib(n - 1) + fib(n - 2);
	}
	return 1;
}

int main() {
	Timer t;
}
