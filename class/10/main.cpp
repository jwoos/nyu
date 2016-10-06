#include <cstdlib>

#include <iostream>

#include <vector>
#include <string>

#include <algorithm>
#include <functional>
#include <utility>

using namespace std;

class Person {
	public:
		Person(string name, int age) : name(name), age(age) {}

		string name;
		int age;

};

ostream& operator<<(ostream& os, Person p) {
	os << '(' << p.name << ',' << p.age << ')';
	return os;
}

// function
bool lessAge(const Person& lhs, const Person& rhs) {
	return lhs.age < rhs.age;
}

// functor
class lessThanOnAge {
	public:
		bool operator()(const Person& lhs, const Person& rhs) {
			return lhs.age < rhs.age;
		}
};

// function
bool lessName(const Person& lhs, const Person& rhs) {
	return lhs.name < rhs.name;
}

// functor
class lessThanOnName {
	public:
		bool operator()(const Person& lhs, const Person& rhs) {
			return lhs.name < rhs.name;
		}
};

template <typename T, typename C>
void insertionSort(vector<T>& v, C comparator) {
	for (size_t i = 1; i < v.size(); i++) {
		T temp = v[i];
		int j = i;

		for (; j > 0 && comparator(temp, v[j]); j--) {
			v[j] = v[j - 1];
		}

		v[j] = temp;
	}
}

template <typename T>
void insertionSort(vector<T>&v, bool (*comparator)(const T&, const T&)) {
	for (size_t i = 1; i < v.size(); i++) {
		T temp = v[i];
		int j = i;

		for (; j > 0 && comparator(temp, v[j]); j--) {
			v[j] = v[j - 1];
		}

		v[j] = temp;
	}
}

class lessThanAge {
	public:
		bool operator()(const Person& lhs, int age) {
			return lhs.age < age;
		}
};

class lessThan21 {
	public:
		bool operator()(const Person& lhs) {
			return lhs.age < 21;
		}
};

template <typename T, typename C>
vector<T> getValues(vector<T> v, C comparator) {
	vector<T> temp;
	for (T x : v) {
		if (comparator(x)) {
			temp.push_back(x);
		}
	}

	return temp;
}

template <typename T>
void printVector(const vector<T> v) {
	for (T t : v) {
		cout << t << endl;
	}
}

int main() {
	vector<Person> v;

	v.push_back(Person("Daniel", 20));
	v.push_back(Person("David", 30));
	v.push_back(Person("Albert", 100));

	//insertionSort(v, lessThanOnAge());
	//insertionSort(v, &lessAge);
	sort(v.begin(), v.end(), lessThanOnAge());
	printVector(v);

	vector<Person> young = getValues(v, lessThan21());
	printVector(young);

	Person temp("", 100);

	//vector<Person> moreYoung = find_if(v.begin(), v.end(), bind2nd<lessThanAge>(lessThanAge(), 30));
}

