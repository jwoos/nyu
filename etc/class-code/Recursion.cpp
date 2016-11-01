#include <iostream>

using namespace std;

int gcd(int a, int b){
	if (b == 0)
		return a;
	return gcd(b,a%b);
}

int factorial(int n){
	if (n == 0)
		return 1;
	return n*factorial(n - 1);
}

bool isPalindrome(char* c, int size){
	if (size <= 1)
		return true;
	return c[0] == c[size - 1] && isPalindrome(c + 1, size - 2);
}