#include "Directory.h"
#include "Entry.h"

using namespace std;

Directory::Directory() : capacity(2), size(0), entries(new Entry*[2]) {
	for (size_t i = 0; i < capacity; i++) {
		entries[i] = nullptr;
	}
}

Directory::~Directory() {
	cout << "Destructor" << endl;
	for (size_t i = 0; i < size; i++) {
		delete entries[i];
	}
	delete [] entries;
}

Directory::Directory(const Directory& rhs) {
	cout << "Copy constructor" << endl;
	entries = new Entry*[rhs.capacity];
	size = rhs.size;
	capacity = rhs.capacity;

	for (size_t i = 0; i < size; i++) {
		entries[i] = new Entry(*rhs.entries[i]);
	}
}

Directory& Directory::operator=(const Directory& rhs) {
	cout << "Assignment operator" << endl;
	if (this != &rhs) {
		for (size_t i = 0; i < size; i++) {
			delete entries[i];
		}
		delete [] entries;

		entries = new Entry*[rhs.capacity];
		size = rhs.size;
		capacity = rhs.capacity;

		for (size_t i = 0; i < size; i++) {
			entries[i] = new Entry(*rhs.entries[i]);
		}
	}
	return *this;
}

void Directory::add(const string& name, unsigned room, unsigned ph, Position& pos) {
	if(size == capacity) {
		Entry** oldData = entries;
		entries = new Entry*[capacity *= 2];
		for (size_t i = 0; i < size; i++) {
			entries[i] = oldData[i];
		}
		delete [] oldData;
	}
	entries[size++] = new Entry(name, room, ph, pos);
}

ostream& operator<<(std::ostream& os, const Directory& dir) {
	for (size_t i = 0; i < dir.size; i++) {
		os << *dir.entries[i] << endl;
	}
	return os;
}

unsigned Directory::operator[](const string& name) {
	for (size_t index = 0; index < size; index++) {
		if (entries[index] -> getName() == name) {
			return entries[index] -> getPhone();
		}
	}
	return 0;
}
