#include <string>
#include <iostream>

namespace CS1124 {
	class Rational {
		friend std::ostream& operator<<(std::ostream& os, const Rational& rhs);
		friend std::istream& operator>>(std::istream& input, Rational& rhs);

		public:
			Rational();

			Rational(int anInt);

			int greatestCommonDivisor(int x, int y);

			void commonDenominator(const Rational& other);

			void normalize();

			int getDenominator() const;

			int getNumerator() const;

			void setDenominator(int newDenominator);

			void setNumerator(int newNumerator);

			Rational& operator+=(const Rational& rhs);

			Rational& operator++();

			Rational operator++(int dummy);

			Rational& operator--();

			Rational operator--(int dummy);

		private:
			int numerator;
			int denominator;
	};

	bool operator==(const Rational& lhs, const Rational& rhs);

	bool operator!=(const Rational& lhs, const Rational& rhs);

	Rational operator+(const Rational& lhs, const Rational& rhs);

	bool operator<(const Rational& lhs, const Rational& rhs);

	bool operator<=(const Rational& lhs, const Rational& rhs);

	bool operator>(const Rational& lhs, const Rational& rhs);

	bool operator>=(const Rational& lhs, const Rational& rhs);
}

