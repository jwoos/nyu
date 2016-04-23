#include <cmath>
#include "Polynomial.h"

using namespace std;

struct Node {
	Node(int data=0, Node* next=nullptr) : data(data), next(next) {}

	int data;

	Node* next;
};

ostream& operator<<(ostream& os, const Polynomial& expression) {
	if (expression.coefficient == nullptr) {
		return os;
	}

	for (int i = expression.degree; i >= 0; i--) {
		Node* p = expression.coefficient;
		int position = 0;

		while (position != i) {
			position++;
			p = p -> next;
		}

		if (p -> data != 0) {
			// sign first
			if (i != expression.degree) {
				if (p -> data < 0) {
					os << '-';
				} else {
					os << '+';
				}
			} else {
				if (p -> data < 0) {
					os << '-';
				}
			}

			// then coefficient
			if ((p -> data != 1) || (abs(p -> data) == 1 && i == 0)) {
				os << abs(p -> data);
			}

			// then exponent
			if (i != 0) {
				if (i != 1) {
					os << "x^" << i;
				} else {
					os << 'x';
				}
			}
		}
	}

	return os;
}

bool operator==(const Polynomial& lhs, const Polynomial& rhs) {
	if (lhs.degree == rhs.degree) {
		Node* p = lhs.coefficient;
		Node* rhsP = rhs.coefficient;

		for (int i = 0; i <= lhs.degree; i++) {
			if (p -> data != rhsP -> data) {
				return false;
			}

			p = p -> next;
			rhsP = rhsP -> next;
		}
	} else {
		return false;
	}

	return true;
}

bool operator!=(const Polynomial& lhs, const Polynomial& rhs) {
	return !(lhs == rhs);
}

Polynomial& Polynomial::operator+=(const Polynomial& rhs) {
	Node* p = coefficient;
	Node* rhsP = rhs.coefficient;

	for (int i = 0; i <= rhs.degree; i++) {
		// add to current degree's coefficient
		if (i <= degree) {
			p -> data += (rhsP -> data);
		}

		// check if next coefficient does not exist for lhs and create one
		// there will never be a case where both are nulllptr as rhsP is looped around its degree
		// except at the very last index
		if (p -> next == nullptr && rhsP -> next != nullptr) {
			p -> next = new Node(rhsP -> next -> data);
		}

		// set to next
		p = p -> next;
		rhsP = rhsP -> next;
	}

	// fix degree
	if (degree < rhs.degree) {
		degree = rhs.degree;
	}

	return *this;
}

Polynomial operator+(const Polynomial& first, const Polynomial& second) {
	Polynomial aCopy = first;

	aCopy += second;

	return aCopy;
}

Polynomial::Polynomial() : coefficient(nullptr), degree(0) {}

Polynomial::Polynomial(const vector<int>& values) : coefficient(nullptr), degree(values.size() - 1) {
	coefficient = new Node(values[values.size() - 1]);
	Node* p = coefficient;

	for (int i = values.size() - 2; i >= 0; i--) {
		p -> next = new Node(values[i]);
		p = p -> next;
	}
}

Polynomial::Polynomial(const Polynomial& rhs) {
	degree = rhs.degree;
	coefficient = new Node(rhs.coefficient -> data);

	Node* p = coefficient;
	Node* rhsP = rhs.coefficient -> next;

	for (int i = 1; i <= degree; i ++) {
		p -> next = new Node(rhsP -> data);

		p = p -> next;
		rhsP = rhsP -> next;
	}
}

Polynomial& Polynomial::operator=(const Polynomial& rhs) {
	if (this != & rhs) {
		degree = rhs.degree;
		coefficient = new Node(rhs.coefficient -> data);

		Node* p = coefficient;
		Node* rhsP = rhs.coefficient -> next;

		for (int i = 1; i <= degree; i ++) {
			p -> next = new Node(rhsP -> data);

			p = p -> next;
			rhsP = rhsP -> next;
		}
	}

	return *this;
}

Polynomial::~Polynomial() {
	Node* p = coefficient;

	while (p != nullptr) {
		Node* temp = p;
		p = p -> next;
		delete temp;
	}
}

int Polynomial::evaluate(int x) const {
	int total = 0;
	Node* p = coefficient;

	for (int i = 0; i <= degree; i++) {
		total += pow(x, i) * (p -> data);
		p = p -> next;
	}

	return total;
}
