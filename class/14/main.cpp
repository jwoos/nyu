#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;
/*
 *
 *template <typename T>
 *class Queue {
 *    private:
 *        list<T> data;
 *    public:
 *        void push(const T& item) {
 *            data.push_back(item);
 *        }
 *
 *        T pop() {
 *            T temp = top();
 *            data.pop_front();
 *            return temp;
 *        }
 *
 *        T top() const {
 *            return *data.begin();
 *        }
 *
 *        bool isEmpty() const {
 *            return data.size() === 0;
 *        }
 *
 *        int size() const {
 *            return data.size();
 *        }
 *
 *        void clear() {
 *            data.clear();
 *        }
 *};
 *
 */

template <typename T>
class Queue {
	private:
		T* data;
		int start;
		int end;
		int capacity;
	public:
		Queue() : data(nullptr) {
			clear();
		}

		~Queue() {
			delete [] data;
		}

		Queue(const Queue<T>& rhs) : data(nullptr) {
			*this = rhs;
		}

		Queue<T>& operator=(const Queue<T>& rhs) {
			if (this == &rhs) {
				return *this;
			}

			int otherSize = rhs.size() + 1;
			delete [] data;
			data = new T[otherSize];

			int capacity = otherSize;
			int otherPtr = rhs.start;

			do {
				push(data[otherPtr++]);
				if (otherPtr == rhs.capacity) {
					otherPtr = 0;
				}
			} while (otherPtr != rhs.end);
		}

		void push(const T& item) {
			data[end++] = item;

			if (end == capacity) {
				end = 0;
			}

			if (end == start) {
				resize(capacity * 2);
			}
		}

		T pop() {
			T temp = top();
			if (start == end) {
				return temp;
			}

			if (start == capacity) {
				start = 0;
			}

			start++;
			return temp;
		}

		T top() const {
			return data[start];
		}

		bool isEmpty() const {
			return start == end;
		}

		int size() const {
			if (start <= end) {
				return end - start;
			}

			return (capacity - start) + end;
		}

		void clear() {
			delete [] data;

			capacity = 5;
			data = new T[capacity];
			start = 0;
			end = 0;
		}

		void resize(int newSize) {
			T* temp = new T[newSize];
			int tempPtr = 0;
			int dataPtr = start;

			do {
				temp[tempPtr++] = data[dataPtr++];

				if (dataPtr == capacity) {
					dataPtr = 0;
				}
			} while (dataPtr != end);

			start = 0;
			end = tempPtr;
			capacity = newSize;
			delete[] data;
			data = temp;
		}
};

int main() {
	Queue<int> q;
	for (int i = 0; i < 100; i++) {
		q.push(i);
		cout << "size: " << q.size() << endl;
	}

	while (!q.isEmpty()) {
		cout << "popped: " << q.pop() << " size: " << q.size() << endl;
	}
}
