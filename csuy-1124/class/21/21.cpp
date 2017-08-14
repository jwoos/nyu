#include <cstdlib>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

struct Node {
    Node (int data = 0, Node* next = nullptr) : data(data), next(next) {}

    int data;
    Node* next;
};

void listDisplay(Node* head) {
    Node* p = head;
    while (p != nullptr) {
        cout << p -> data << ' ';
        p = p -> next;
    }
    cout << endl;
}

int listSize(Node* head) {
    Node* p = head;
    int counter = 0;
    while (p != nullptr) {
        counter++;
        p = p -> next;
    }

    return counter;
}

Node* listFindEnd(Node* head) {
	Node* p = head;
	if (head !=nullptr) {
		while (p -> next != nullptr) {
			p = p -> next;
		}
	}

    return p;
}

void listAddToEnd(Node*& head, int data) {
	if (head == nullptr) {
		head = new Node(data);
	} else {
		Node* theEnd = listFindEnd(head);
		theEnd -> next = new Node(data);
	}
	cout << endl;
}

void listAddHead(Node*& head, int data) {
	/*
	 *Node* p = new Node(data);
	 *p -> next = head -> next;
	 *head = p;
	 */

	head = new Node(data, head);
}

// can't pass in nullptr
void listAdd(Node* prior, int data) {
	prior -> next = new Node(data, prior -> next);
}

void listRemoveHead(Node*& head) {
	if (head == nullptr) {
		return;
	}
	Node* p = head;
	head = head -> next;
	delete p;
}

void listRemove(Node* prior) {
	Node* after = prior -> next -> next;
	delete prior -> next;
	prior -> next = after;
}

int main() {
    // linked list
    Node* list = nullptr;
	listAddToEnd(list, 17);
	listAddToEnd(list, 42);
	listDisplay(list);
	cout << listFindEnd(list) << endl;
    //list = new Node(17);
    //listAddToEnd(list, 42);
}
