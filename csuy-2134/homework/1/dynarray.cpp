#include <iostream>

template <typename T>
DynArray<T>::DynArray() :_size(0), _capacity(0), bracketsUsed(false), data(nullptr) {}

template <typename T>
DynArray<T>::DynArray(const DynArray<T>& rhs) :_size(0), _capacity(0), bracketsUsed(false), data(nullptr) {
	*this = rhs;
}

template <typename T>
DynArray<T>& DynArray<T>::operator=(const DynArray<T>& rhs){
	if (this != &rhs) {
		_size = rhs._size;
		_capacity = rhs._capacity;
		bracketsUsed = rhs.bracketsUsed;

		delete [] data;

		data = new T [_capacity];

		for (size_t i = 0; i < _capacity; i++) {
			data[i] = rhs.data[i];
		}
	}
	return *this;
}

template <typename T>
DynArray<T>::~DynArray() {
	delete [] data;
}

template <typename T>
void DynArray<T>::push_back(T newData) {
	if (bracketsUsed) {
		std::cout << "Brackets have been used so you can't push_back" << std::endl;
		return;
	}

	if (_capacity == 0) {
		_capacity = 1;
		data = new T [_capacity];
	}

	if (_size == _capacity) {
		T* temp = data;

		data = new T [_capacity * 2];

		for (size_t i = 0; i < _capacity; i++) {
			data[i] = temp[i];
		}
		delete [] temp;
		_capacity *= 2;
	}

	data[_size] = newData;
	_size++;
}

template <typename T>
void DynArray<T>::pop_back() {
	_size--;
}

// TODO finish this
template <typename T>
void DynArray<T>::resize(size_t n) {
	if (n > _size) {
		if (n > _capacity) {
			// expand
		}
	} else if (n < _size) {
		_size = n;
	}
}

template <typename T>
size_t DynArray<T>::size() const {
	return _size;
}

template <typename T>
size_t DynArray<T>::capacity() const {
	return _capacity;
}

template <typename T>
T DynArray<T>::operator[](size_t index) const {
	bracketsUsed = true;
	return data[index];
}

template <typename T>
T& DynArray<T>::operator[](size_t index) {
	bracketsUsed = true;
	return data[index];
}
