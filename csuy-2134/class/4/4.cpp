#include <cstdlib>
#include <iostream>
#include <ctime>
#include <algorithm>
#include <vector>
#include <string>
#include <list>
#include <set>
#include <map>

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

template <typename T>
void printList(const list<T>& l) {
	for (typename list<T>::const_iterator i = l.begin(); i != l.end(); i ++) {
		cout << *i << endl;
	}
}

void vectorStuff() {
	vector<int> v;
	Timer t;
	double elapsed;
	double previousTime;
	for (int i = 0; i < 10000000; i++) {
		t.reset();
		v.push_back(i);
		elapsed = t.elapsed();

		if (previousTime < elapsed) {
			cout << "size=" << v.size() << " | capacity=" << v.capacity() << " | currentTime=" << elapsed << endl;
			previousTime = elapsed;
		}
	}

	/*
	 *v.clear();
	 *cout << "size=" << v.size() << "    capacity=" << v.capacity() << endl;
	 */

	/*
	 *for (int i : v) {
	 *    cout << i << endl;
	 *}
	 */
}

void listStuff() {
	list<int> l;
	for (int i = 0; i < 100; i++) {
		l.push_back(i);
		l.push_front(i);
		cout << "size=" << l.size() << " | capacity=" << l.size() << endl;
	}

	for (list<int>::iterator i = l.begin(); i != l.end(); i++) {
		cout << *i << endl;
	}
}

void pairStuff() {
	pair<string, int> p;
	p.first = "NAME";
	p.second = 100;
	pair<pair<string, int>, pair<float, char>> p1;
	p1.first.first = "what";
	p1.first.second = 10;
	p1.second.first = 0.1;
	p1.second.second = 'c';
}

void setStuff() {
	set<int> s;

	for (int i = 0; i < 10000; i++) {
		s.insert(rand() % 1000);
		cout << s.size() << endl;
	}

	/*
	 *for (int i : s) {
	 *    cout << i << endl;
	 *}
	 */

	multiset<int> ms;
	for (int i = 0; i < 10000; i++) {
		ms.insert(rand() % 1000);
		//cout << ms.size() << endl;
	}

	for (int i : ms) {
		cout << i << endl;
	}
}

void mapStuff() {
	map<string, int> m;
	m.insert(pair<string, int>("Daniel", 100));
	m.insert(pair<string, int>("Al", 90));

	for (map<string, int>::iterator i = m.begin(); i != m.end(); i++) {
		cout << "first=" << i -> first << " | second=" << i -> second << endl;
	}

	cout << "m[\"Daniel\"] = " << m["Daniel"] << endl;
	m["Steve"] = 10;
	if (m.find("Billy") != m.end()) {
		cout << m["Billy"] << endl;
	}
}

int main() {
	srand(time(nullptr));

	mapStuff();
}
