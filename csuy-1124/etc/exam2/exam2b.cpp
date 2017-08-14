#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

class Person {
	friend ostream& operator<<(ostream& os, const Person& rhs);
	public:
		Person(const string& name, int capacity) : name(name), anArr(nullptr), capacity(capacity) {
			cout << "Person()" << endl;
			anArr = new int [capacity];

			for (int i = 0; i < capacity; i++) {
				anArr[i] = i;
			}
		}

		Person(const Person& rhs) {
			cout << "Person(const Person& rhs)" << endl;
			name = rhs.name;
			capacity = rhs.capacity;
			anArr = new int [capacity];

			for (int i = 0; i < capacity; i++) {
				anArr[i] = rhs.anArr[i];
			}
		}

		Person& operator=(const Person& rhs) {
			delete [] anArr;

			name = rhs.name;
			capacity = rhs.capacity;
			anArr = new int [capacity];

			for (int i = 0; i < capacity; i++) {
				anArr[i] = rhs.anArr[i];
			}
		}

		~Person() {
			cout << "~Person()" << endl;
			delete [] anArr;
		}
	private:
		string name;
		int* anArr;
		int capacity;
};

class Child : public Person {
	public:
		Child(const string& name, int capacity) : Person(name, capacity) {
			cout << "Child()" << endl;
		}

		Child(const Child& rhs) : Person(rhs) {
			cout << "Child(const Child& rhs)" << endl;
		}

		~Child() {
			cout << "~Child()" << endl;
		}
};

ostream& operator<<(ostream& os, const Person& rhs) {
	os << "Name: " << rhs.name << ' ' << "Capacity: " << rhs.capacity << " Data:";

	for (int i = 0; i < rhs.capacity; i++) {
		os << ' ' << rhs.anArr[i] << ',';
	}

	return os;
}

int main() {
/*
 *    Person john("John", 10);
 *    cout << john << endl;
 *    cout << &john << endl;
 *    Person johnClone(john);
 *    cout << johnClone << endl;
 *    cout << &johnClone << endl;
 *
 *    cout << endl;
 */

	Child johnChild("John", 5);
	cout << johnChild << endl;
	Child johnChildClone(johnChild);
	cout << johnChildClone << endl;

	cout << endl;
}
