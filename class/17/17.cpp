#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class Vector {
	public:
		Vector() : _size(0), _capacity(0), data(nullptr) {}

		~Vector() {
			delete [] data;
		}

		Vector(const Vector& rhs) {
			data = new int[rhs._capacity];
			_size = rhs._size;
			_capacity = rhs._capacity;

			for (size_t i = 0; i < _size; i++) {
				data[i] = rhs.data[i];
			}
		}

		size_t size() const {
			return _size;
		}

		void clear() {
			_size = 0;
		}

		void pop_back() {
			_size--;
		};

		void push_back(int val) {
			if (_capacity == 0) {
				data = new int[1];
				_capacity = 1;
			}

			if (_size == _capacity) {
				int* oldData = data;
				data = new int[_capacity * 2];
				for (size_t i = 0; i < _size; i++) {
					data[i] = oldData[i];
				}
				delete [] oldData;
				_capacity *= 2;
			}
			data[_size] = val;
			_size++;
		}

		// required to be a member function
		int operator[](size_t index) const {
			return data[index];
		}

		int& operator[](int newInt) {
			return data[newInt];
		}

		Vector& operator=(const Vector& rhs) {
			// check for self assignment
			if (this != &rhs) {
				delete [] data;

				data = new int[rhs._capacity];
				_size = rhs._size;
				_capacity = rhs._capacity;

				for (size_t i = 0; i < _size; i++) {
					data[i] = rhs.data[i];
				}
			}
			return *this;
		}
	private:
		size_t _size;
		size_t _capacity;
		int* data;
};

int main() {

}
