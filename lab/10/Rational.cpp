#include <cstdlib>

#include "Rational.h"

using namespace std;

namespace CS1124 {
	Rational::Rational() = default;

	Rational::Rational(int anInt) : numerator(anInt), denominator(1) {}

	void Rational::commonDenominator(const Rational& other) {
		int newNumerator = getNumerator() * other.getDenominator();
		int newDenominator = getDenominator() * other.getDenominator();

		setNumerator(newNumerator);
		setDenominator(newDenominator);
	}

	int Rational::greatestCommonDivisor(int x, int y) {
		while (y != 0) {
			int temp = x % y;
			x = y;
			y = temp;
		}

		return x;
	}

	void Rational::normalize() {
		if (numerator < 0 && denominator < 0) {
			numerator *= -1;
			denominator *= -1;
		}

		int divisor = greatestCommonDivisor(numerator, denominator);

		numerator /= divisor;
		denominator /= divisor;
	}

	int Rational::getNumerator() const {
		return numerator;
	}

	int Rational::getDenominator() const {
		return denominator;
	}

	void Rational::setNumerator(int newNumerator) {
		numerator = newNumerator;
	}

	void Rational::setDenominator(int newDenominator) {
		denominator = newDenominator;
	}

	ostream& operator<<(ostream& os, const Rational& rhs) {
		Rational rhsCopy(rhs);
		rhsCopy.normalize();
		os << rhsCopy.numerator << '/' << rhsCopy.denominator;
		return os;
	}

	istream& operator>>(istream& input, Rational& rhs) {
		char temp;
		input >> rhs.numerator >> temp >> rhs.denominator;
		if (rhs.denominator == 0) {
			cout << "Error!" << endl;
			exit(1);
		}
		return input;
	}

	Rational& Rational::operator+=(const Rational& rhs) {
		Rational rhsCopy(rhs);
		Rational thisCopy(*this);
		commonDenominator(rhs);
		rhsCopy.commonDenominator(thisCopy);

		numerator += rhsCopy.numerator;

		//normalize();
		return *this;
	}

	Rational& Rational::operator++() {
		numerator += denominator;
		return *this;
	}

	Rational Rational::operator++(int dummy) {
		Rational result(*this);
		numerator += denominator;
		return result;
	}

	Rational& Rational::operator--() {
		numerator -= denominator;
		return *this;
	}

	Rational Rational::operator--(int dummy) {
		Rational result(*this);
		numerator -= denominator;
		return result;
	}

	Rational operator+(const Rational& lhs, const Rational& rhs) {
		Rational temp(lhs);
		temp += rhs;
		return temp;
	}

	bool operator==(const Rational& lhs, const Rational& rhs) {
		Rational lhsCopy(lhs);
		Rational rhsCopy(rhs);

		lhsCopy.commonDenominator(rhs);
		rhsCopy.commonDenominator(lhs);

		if (lhsCopy.getNumerator() == rhsCopy.getNumerator()) {
			return true;
		}
		return false;
	}

	bool operator!=(const Rational& lhs, const Rational& rhs) {
		return !(lhs == rhs);
	}
}
