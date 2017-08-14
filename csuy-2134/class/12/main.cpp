#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>
#include <set>

using namespace std;

// O(n)
int sum(vector<int>& v) {
	if (v.size() == 0) {
		return 0;
	}

	int item = v[v.size() - 1];
	v.pop_back();
	return item + sum(v);
}

// O(2^n)
int fib(int n) {
	if (n < 2) {
		return 1;
	}

	return fib(n - 1) + fib(n - 2);
}

int gcd(int a, int b) {
	if (b == 0) {
		return a;
	}

	return gcd(b, a % b);
}

int factorial(int n) {
	if (n == 0) {
		return 1;
	}

	return n * factorial(n - 1);
}

bool isPalindrome(char* c, int size) {
	if (size <= 1) {
		return true;
	}

	return c[0] == c[size - 1] && isPalindrome(c + 1, size - 2);
}

int main() {}
