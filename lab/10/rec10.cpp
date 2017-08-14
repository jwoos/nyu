/*
	testRational.cpp
	CS1124
	Implement the class Rational, so that the following program works.
 */

#include <iostream>
#include "Rational.h"

using namespace std;
using namespace CS1124;

int main() {
	Rational a, b;
	cout << "Input two rational numbers.\n";
	cout << "a: ";
	cin >> a;
	cout << "b: ";
	cin >> b;

	Rational one = 1;

	cout << "a = " << a << endl;
	cout << "b = " << b << endl;
	cout << "one = " << one << endl;
	cout << "a += b: " << (a += b) << endl;	// Implement as member
	cout << "a = " << a << endl;
	cout << "a + one: " << (a + one) << endl;	// Implement as non-member, but not a friend
	cout << "a == one: " << boolalpha << (a == one) << endl;
	cout << "1 == one: " << boolalpha << (1 == one) << endl;  // How does this work?
	cout << "a != one: " << boolalpha << (a != one) << endl;  // Do not implement as friend.

	cout << endl;

	cout << "a = " << a << endl;
	cout << "++a = " << (++a) << endl;
	cout << "a = " << a << endl;
	cout << "a++ = " << (a++) << endl;
	cout << "a = " << a << endl;
	cout << "--a = " << (--a) << endl;
	cout << "a = " << a << endl;
	cout << "a-- = " << (a--) << endl;
	cout << "a = " << a << endl;

	cout << endl;

	Rational c, d;
	cout << "Input two rational numbers.\n";
	cout << "c: ";
	cin >> c;
	cout << "d: ";
	cin >> d;

	cout << "c = " << c << endl;
	cout << "d = " << d << endl;
	cout << "c < d: " << boolalpha << (c < d) << endl;
	cout << "c <= d: " << boolalpha << (c <= d) << endl;
	cout << "c > d: " << boolalpha << (c > d) << endl;
	cout << "c >= d: " << boolalpha << (c >= d) << endl;
}
