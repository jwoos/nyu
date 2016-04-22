#include "Sequence.h"

using namespace std;

struct Node {
	Node(int data=0, Node* next=nullptr) : data(data), next(next) {}

	int data;

	Node* next;
};

Sequence::Sequence() : head(nullptr), current(nullptr) {}

void Sequence::reset() {
	current = head;
}

void Sequence::add(int data) {
	Node* p = new Node(data);
	if (head == nullptr) {
		head = p;
		current = head;
	}
	Node* temp = current -> next;
	current -> next = p;
	current = current -> next;
	current -> next = temp;
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
		if (current -> next != nullptr) {
			current = current -> next;
		} else {
			current = head;
		}
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
}

void Sequence::display(char delimiter, ostream& os) {
	Node* p = head;
	while (p != nullptr) {
		os << p -> data << delimiter;
		p = p -> next;
	}
	os << endl;
}
