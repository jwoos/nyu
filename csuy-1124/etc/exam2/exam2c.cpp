#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

class Vector {
	public:
		Vector() :_size(0), _capacity(0), data(nullptr) {}

		Vector(const Vector& rhs) {
			_size = rhs._size;
			_capacity = rhs._capacity;

			delete [] data;

			data = new int [_capacity];

			for (size_t i = 0; i < _capacity; i++) {
				data[i] = rhs.data[i];
			}
		}

		Vector& operator=(const Vector& rhs) {
			if (this != &rhs) {
				_size = rhs._size;
				_capacity = rhs._capacity;

				delete [] data;

				data = new int [_capacity];

				for (size_t i = 0; i < _capacity; i++) {
					data[i] = rhs.data[i];
				}
			}
			return *this;
		}

		~Vector() {
			delete [] data;
		}

		void push_back(int newInt) {
			if (_capacity == 0) {
				_capacity = 1;
				data = new int [_capacity];
			}
			if (_size == _capacity) {
				int* temp = data;

				data = new int [_capacity * 2];

				for (size_t i = 0; i < _capacity; i++) {
					data[i] = temp[i];
				}
				delete [] temp;
				_capacity *= 2;
			}

			data[_size] = newInt;
			_size++;
		}

		void clear() {
			_size = 0;
		}

		size_t size() const {
			return _size;
		}

		void pop_back() {
			_size--;
		}

		int operator[](size_t index) const {
			return data[index];
		}

		int& operator[](size_t index) {
			return data[index];
		}
	private:
		size_t _size;
		size_t _capacity;
		int* data;
};

int main() {
	Vector aVector;
	cout << aVector.size() << endl;
	aVector.push_back(1);
	aVector.push_back(1);
	aVector.push_back(1);
	aVector.push_back(1);
	aVector.push_back(1);
	aVector.push_back(1);
	aVector.push_back(1);
	cout << aVector.size() << endl;
	cout << aVector[0] << endl;
}
