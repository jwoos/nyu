#include <cstdlib>
#include <vector>
#include <iostream>
#include <string>

#include "Sequence.h"

using namespace std;

int main() {
	Sequence s;
	for (int i = 0; i < 6; ++i) {
		s.add(i);
	}

	s.display();
	cout << "==========" << endl;
	s.reset();
	for (int i = 0; i < 3; ++i) {
		s.next();
	}
	s.add(42);
	s.display();
	cout << "==========" << endl;
	s.reset();
	for (int i = 0; i < 2; ++i) {
		s.next();
	}
	s.remove();
	s.display();
	cout << "==========" << endl;
	s.clear();
	s.display();
	cout << "==========" << endl;
}
