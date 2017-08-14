#include <cstdlib>
#include <iostream>

#include "Polynomial.h"

using namespace std;

int main() {
	Polynomial x({-1, -2, -3});
	cout << x << endl;

	Polynomial y({1, 1, 2, 3});
	cout << y << endl;
}
