#include "Polynomial.h"

using namespace std;

struct Node {
	Node(int data=0, Node* next=nullptr) : data(data), next(next) {}

	int data;

	Node* next;
};

ostream& operator<<(ostream& os, const Polynomial& expression) {
	for (int i = expression.degree; i >= 0; i--) {
		Node* p = expression.coefficient;
		int position = 0;

		while (position != i) {
			position++;
			p = p -> next;
		}

		if (p -> data != 0) {
			if (i != 0) {
				if (i == 1)  {
					if (p -> data < 0) {
						os << "-x";
					} else {
						os << "x";
					}
				} else if (i == expression.degree) {
					os << p -> data << "x^" << i;
				} else {
					os << showpos << p -> data << noshowpos << "x^" << i;
				}
			} else {
				os << showpos << p -> data << noshowpos;
			}
		}
	}

	return os;
}

Polynomial::Polynomial(const vector<int>& values) : coefficient(nullptr), degree(values.size() - 1) {
	coefficient = new Node(values[values.size() - 1]);
	Node* p = coefficient;

	for (int i = values.size() - 2; i >= 0; i--) {
		p -> next = new Node(values[i]);
		p = p -> next;
	}
}
