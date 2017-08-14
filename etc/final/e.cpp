#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int monthsToRepayLoan(double loan, double annualInterest, int monthlyPayment) {
	if (loan <= 0) {
		return 0;
	}
	int months = 0;

	double newLoan = (loan * (annualInterest / 12) + loan) - monthlyPayment;
	months += monthsToRepayLoan(newLoan, annualInterest, monthlyPayment);
	months++;
	return months;
}

struct Node {
	Node(int data = 0, Node* next = nullptr) : data(data), next(next) {}

	int data;
	Node* next;
};

Node* insertSorted(Node*& head, int data) {
	Node* p = head;

	if (p == nullptr) {
		head = new Node(data);
		return head;
	} else {
		if (p -> next != nullptr) {
			if (p -> next -> next != nullptr) {
				while (data >= p -> next -> data && data <= p -> next -> next -> data) {
					p = p -> next;
				}
			} else {
				if (p -> next -> data <= data) {
					p = p -> next;
				}
			}
		}

		Node* temp = p -> next;
		p -> next = new Node(data, temp);
		return p -> next;
	}
}

class Byte {
	private:
		int bits[8];

	public:
		Byte() {
			for (int i = 0; i < 8; i++) {
				bits[i] = 0;
			}
		}

		Byte(int i) {

		}

		Byte& operator+=(const Byte& rhs);

		Byte& operator++();

		Byte operator++(int dummy);
};

Byte& Byte::operator+=(const Byte& rhs) {
	for (int i = 0; i < 8; i++) {
		bits[i] += rhs.bits[i];

		if (bits[i] >= 2 && i != 8) {
			bits[i + 1] += bits[i] / 2;
			bits[i] = bits[i] % 2;
		}

		return *this;
	}
}

Byte operator+(const Byte& lhs, const Byte& rhs) {
	Byte copy(lhs);
	copy += rhs;
	return copy;
}

Byte& Byte::operator++() {
	Byte one(1);
	*this += one;
	return *this;
}

Byte Byte::operator++(int dummy) {
	Byte copy(*this);
	++(*this);
	return copy;
}

int main() {
	cout << monthsToRepayLoan(1000, 0.12, 500) << endl;
}
