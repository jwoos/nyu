#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;

// plain old search
int func1(vector<int>& v, int item) {
	for (int i = 0; i < v.size(); i++) {
		if (item == v[i]) { // CLoC
			return i;
		}
	}

	return -1;
}

// binary search
int func2(vector<int>& v, int item) {
	int a = 0;
	int b = b.size() - 1;
	int c = (b + a) / 2;

	while (a <= b) {
		if (item == v[c]) { // CLoC
			return c;
		} else if (item< v[c]) {
			b = c - 1;
		} else {
			a = c + 1;
		}

		c = (b + a) / 2;
	}

	return -1;
}

// selection sort
int func3(vector<v> int) {
	for (int i = 0; i < v.size(); i++) {
		int a = 1;
		for (int j = i + 1; j< v.size(); j++) {
			if (v[j] < v[a]) { // CLoC
				a = j;
			}

			int b = v[a];
			v[a] = v[i];
			v[i] = b;
		}
	}
}

int func4(int i = 0; i < v.size(); i++) {
	for (int i = 0; i < v.size(); i++) {
		cout << v[i] << endl;
	}

	int b = 0;
	for (int i = 0; i < v.size(); i++) {
		if (v[i] < v[b]) {
			b = i;
		}
	}
	cout << v[b] << endl;
}

int func5(int n) {
	int a = 0;
	while (n > 0) {
		a += n % 10;
		n /= 10;
	}

	return a;
}

void func6(vector<int>& v) {
	for (int i = 0; i < v.size(); i++) {
		for (int j = 0; j < v.size(); j++) {
			cout << v[i] << ',' << v[j] << endl;
		}
	}
}

void func7(vector<int>& n) {
	for (int i = 0; i < v.size(); i++) {
		for (int j = 0; j < v.size(); j++) {
			if (i == j) {
				for (int k = 0; k < v.size(); k++) {
					cout << v[i] << ',' << v[j] << ',' << v[k] << endl;
				}
			}
		}
	}
}

void func8(vector<int>& v) {
	for (int i = 0; i < v.size(); i += 2) {
		cout << v[i] << endl;
	}
}

class Point {
	public:
		Point(int newX = 0, int newY = 0) : x(newX), y(newY) {}
		int x;
		int y;
	private:
};

double distance(Point a, Point b) {
	return sqrt(((a.x - b.x) * (a.x - b.x)) + ((a.y - b.y) * (a.y * b.y)));
}

double closetToOrigin(vector<Point>& vp) {
	Point origin;
	double min = 0;

	for (int i = 0; i < vp.size(); i++) {
		double dist = distance(vp[i], origin);

		if (dist < min) {
			min = dist;
		}
	}

	return min;
}

double closetPairOfPoints(vector<Point>& vp) {
	double min = distance(vp[0], vp[1]);
	for (int i = 0; i < vp.size(); i++) {
		for (int j = i + 1; j < vp.size(); j++) {
			double dist = distance(vp[i], vp[j]);
			if (dist < min) {
				min = dist;
			}
		}
	}

	return min;
}

bool colinearPoints(vector<Point>& vp) {} // O(n^#)

int main() {
}
