#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <cmath>

using namespace std;

template <class T>
class PQueue {
	private:
		vector<T> data;

		// used for push
		void percolateUp(int n) {
			if (n == 1) {
				return;
			}

			if (data[n] < data[n / 2]) {
				swap(n, n / 2);
				percolateUp(n / 2);
			}
		}

		// used for pop
		void percolateDown(int n) {
			if (n == data.size()) {
				return;
			}

			if ((n * 2) >= data.size()) {
				return;
			}

			// node has one child
			if ((n * 2) == data.size() + 1) {
				if (data[n] > data[n * 2]) {
					swap(n, n * 2);
					return;
				}
			}

			// node has two children
			if (data[n] >= data[n * 2] || data[n] >= data[n * 2 + 1]) {
				if (data[n * 2] < data[n * 2 + 1]) {
					swap(n, n * 2);
					percolateDown(n * 2);
				} else {
					swap(n, n * 2 + 1);
					percolateDown(n * 2 + 1);
				}
			}
		}

		void swap(int a, int b) {
			T temp = data[a];
			data[a] = data[b];
			data[b] = temp;
		}

	public:
		PQueue() {
			clear();
		}

		void push(const T& item) {
			data.push_back(item);
			percolateUp(data.size() - 1);
		}

		T pop() {
			T retval = top();

			if  (!isEmpty()) {
				data[1] = data[data.size() - 1];
				data.pop_back();
				percolateDown(1);
			}
		}

		T top() const {
			return data[1];
		}

		bool isEmpty() const {
			return data.size() == 1;
		}

		void clear() {
			data.resize(1);
		}
};

int main() {}
