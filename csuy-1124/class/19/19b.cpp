#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Complex {
	friend ostream& operator<<(ostream& os, const Complex& rhs) {
		// When the showpos format flag is set, a plus sign (+) precedes every non-negative numerical value inserted into the stream (including zeros)
		// it's sticky and must be unset using noshowpos
		os << rhs.real << showpos << rhs.imaginary << "i" << noshowpos;
		return os;
	}

	//let one function do both
	//friend Complex operator+(const Complex& lhs, const Complex& rhs);

	public:
		Complex(double real = 0, double imag = 0) : real(real), imaginary(imag) {}

		Complex& operator+=(const Complex& rhs) {
			real += rhs.real;
			imaginary += rhs.imaginary;
			return *this;
		}

		Complex& operator++() {
			real++;
			return *this;
		}

		// doesn't need a parameter name
		Complex operator++(int dummy) {
			// make a copy
			Complex result(*this);
			++real;
			return result;
		}

	private:
		double real, imaginary;
};

//NEVER PASS A REFERNCE OR POINTER TO A LOCAL
Complex operator+(const Complex& lhs, const Complex& rhs) {
	//return Complex(lhs.real + rhs.real, lhs.imaginary + rhs.imaginary);
	//make a copy explicitly or just pass by value
	Complex temp(lhs);
	temp += rhs;
	return temp;
}

int main() {
	Complex c1;
	Complex c2(17);
	Complex c3(3, -5);
	cout << "c1: " << c1 << endl;
	cout << "c2: " << c2 << endl;
	cout << "c3: " << c3 << endl;

	//assuming it's not a member
	//for binary make it nonmember
	//c1 = operator+(c2, c3);
	c1 = c2 + c3;
	cout << "c1: " << c1 << endl;

	//make it member
	//assginemnt MUST be member
	//c1 += c2;
	//c1.operator+=(c2);
	c1 += c2;
	cout << "c1: " << c1 << endl;

	//???????????
	//WHY THIS WORK
	//implicit conversion
	cout << "c1 + 5: " << (c1 + 5) << endl;

	// if it's a unary operator, make it a member
	// do the increment, return the increment
	cout << "++c1: " << ++c1 << endl;
	// do the increment, but return the original value
	cout << "c1++: " << c1++ << endl;
}
