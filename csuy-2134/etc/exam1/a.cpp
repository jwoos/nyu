#include <cstdlib>

#include <iostream>

#include <vector>
#include <set>
#include <algorithm>
#include <functional>
#include <utility>

using namespace std;

class Foo {
	public:
		// constructor
		Foo(int data) : data(new int(data)) {}

		// destructor
		virtual ~Foo() {
			delete data;
		}

		// copy constructor
		Foo(const Foo& rhs) : data(nullptr) {
			cout << "copy constructor" << endl;

			*this = rhs;
		}

		// move constructor
		Foo(Foo&& rhs) : data(rhs.data) {
			rhs.data = nullptr;
		}

		Foo& operator=(const Foo& rhs) {
			cout << "copy assignment" << endl;

			if (this != &rhs) {
				delete data;

				data = new int(*rhs.data);
			}

			return *this;
		}

		Foo& operator=(Foo&& rhs) {
			swap(data, rhs.data);
			return *this;
		}

	private:
		int* data;
};

/*
 * sum = 0;
 * for( i = 0; i < n; ++i )
 *   ++sum;
 *
 * O(n)
 */
int sum1(int n) {
	int sum = 0;

	for (int i = 0; i < n; i++) {
		sum++;
	}

	return sum;
}

/*
 * sum = 0;
 * for( i = 0; i < n; ++i )
 *   for( j = 0; j < n * n; ++j )
 *     ++sum;
 *
 * O(n^3)
 */
int sum3(int n) {
	int sum = 0;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n * n; j++) {
			sum++;
		}
	}

	return sum;
}

int main() {
	/*
	 *Foo a(10);
	 *Foo b = a;
	 *Foo c(10);
	 *c = a;
	 */

	for (int i = 0; i < 50; i++) {
		cout << sum3(i) << endl;
	}
}
