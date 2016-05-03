#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <climits>

using namespace std;

class Number {
	friend ostream& operator<<(ostream& os, const Number& rhs) {
		os << rhs.whole << '.' << rhs.decimal;
		return os;
	}
	
	public:
		Number(int whole = 0, int decimal = 0) : whole(whole), decimal(decimal) {}

		Number& operator+=(const Number& rhs) {
			whole += rhs.whole;
			decimal += rhs.decimal;
			return *this;
		}
		
		// preincrement
		Number& operator++() {
			whole++;
			return *this;
		}
		
		// postincrement
		Number operator++(int dummy) {
			Number result(*this);
			whole++;
			return result;
		}

	private:
		int whole;
		int decimal;
};

Number operator+(const Number& lhs, const Number& rhs) {
	Number temp(lhs);
	temp += rhs;
	return temp;
}


void printShit(int n) {
	if (n == 1) {
		cout << n << ' ';
		return;
	}
	
	cout << n << ' ';
	printShit(n - 1);
}

//Print x of one character followed by x of another character aaabbb x = 3, char 1 = a, char 2 = b
void printMoreShit(int x, char uno, char dos) {
	if (x < 1) {
		return;
	} else {
		cout << uno;
		printMoreShit(x - 1, uno, dos);
		cout << dos;
	}
}

//Print n to 1 followed by 1 to n
void printEvenMoreShit(int n) {
	if (n == 1) {
		cout << n << ' ';
		return;
	}
	
	cout << n << ' ';
	printEvenMoreShit(n - 1);
	cout << n << ' ';
}

int main() {
	Number a(1, 2); // 1.2
	Number b(2, 3); // 2.3
	cout << a << endl;
	cout << b << endl;
	a += b; // a.operator+=(b)
	cout << a << endl;
	cout << ++b << endl;
	cout << b++ << endl;
	
	printShit(120);
	
	printMoreShit(3, 'a', 'b');
	cout << endl;
	
	printEvenMoreShit(100);
	cout << endl;
}