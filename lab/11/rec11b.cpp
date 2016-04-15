#include <cstdlib>
#include <iostream>

struct Node {
	Node(int data = 0, Node* link = nullptr) : data(data), link(link) {}

	int data;

	Node* link;
};

void listInsertHead(int entry, Node*& headPtr) {
	headPtr = new Node(entry, headPtr);
}

