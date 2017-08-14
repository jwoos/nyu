#include "Sequence.h"

using namespace std;

struct Node {
	Node(int data=0, Node* next=nullptr) : data(data), next(next) {}

	int data;

	Node* next;
};

Sequence::Sequence() : head(nullptr), current(nullptr) {}

Sequence::Sequence(const Sequence& rhs) {
	if (rhs.head != nullptr) {
		head = new Node(rhs.head -> data);
		current = head;

		Node* p = rhs.head -> next;

		while (p != nullptr) {
			add(p -> data);
			p = p -> next;
		}
	} else {
		head = nullptr;
		current = nullptr;
	}
}

Sequence& Sequence::operator=(const Sequence& rhs) {
	if (this != &rhs) {
		head = new Node(rhs.head -> data);
		current = head;

		Node* p = rhs.head;

		while (p != nullptr) {
			add(p -> data);
			p = p -> next;
		}
	}

	return *this;
}

Sequence::~Sequence() {
	Node* p = head;

	while (p != nullptr) {
		Node* temp = p;
		delete temp;
		p = p -> next;
	}
}

void Sequence::reset() {
	current = head;
}

void Sequence::add(int data) {
	if (current == nullptr) {
		Node* p = new Node(data, head);
		head = p;
		current = head;
	} else {
		Node* p = new Node(data);

		Node* temp = current -> next;
		current -> next = p;
		current = current -> next;
		current -> next = temp;
	}
}

void Sequence::remove() {
	if (current == nullptr) {
		return;
	}

	Node* p = head;
	while (p -> next != current) {
		p = p -> next;
	}

	Node* temp = current -> next;
	p -> next = temp;
	delete current;
	current = temp;
}

int Sequence::data() {
	if (current != nullptr) {
		return current -> data;
	}
}

void Sequence::next() {
	if (current != nullptr) {
		current = current -> next;
	}
}

bool Sequence::valid() {
	return current != nullptr;
}

void Sequence::clear() {
	Node* p = head;
	while (p != nullptr) {
		Node* temp = p;
		delete temp;
		p = p -> next;
	}
	head = nullptr;
}

void Sequence::display(char delimiter, ostream& os) {
	Node* p = head;
	while (p != nullptr) {
		os << p -> data << delimiter;
		p = p -> next;
	}
	os << endl;
}
