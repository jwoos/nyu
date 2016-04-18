#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

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

void listRemoveEnd(Node*& head) {
	if (head == nullptr) {
		return;
	} else if (head -> next == nullptr) {
		delete head;
		head = nullptr;
		return;
	}

	Node* p = head;
	while (p -> next -> next != nullptr) {
		p = p -> next;
	}
	delete p -> next;
	p -> next = nullptr;
}

Node* listDuplicate(Node* head) {
	if (head == nullptr) {
		return nullptr;
	}

	Node* otherHead = new Node(head -> data);
	Node* p = head -> next;
	Node* otherP = otherHead;

	while (p != nullptr) {
		otherP -> next = new Node(p -> data);
		otherP = otherP -> next;
		p = p -> next;
	}

	return otherHead;
}

// recursion
Node* listDuplicate2(Node* head) {
	if (head == nullptr) {
		return nullptr;
	}

	//Node* copyOfTheRest = mystery(head -> next);
	Node* copyOfTheRest = listDuplicate2(head -> next);
	return new Node(head -> data, copyOfTheRest);
}

void listDisplayReverse(Node* head) {
	if (head == nullptr) {
		return;
	}

	listDisplayReverse(head -> next);
	cout << head -> data << ' ';
}

int main() {
    // linked list
    Node* list = nullptr;
	listAddToEnd(list, 17);
	listAddToEnd(list, 42);
	listDisplay(list);
	cout << listFindEnd(list) << endl;

	Node* dupe = listDuplicate(list);
	Node* dupe2 = listDuplicate2(list);

	listDisplay(dupe);
	cout << listFindEnd(dupe) << endl;

	listDisplay(dupe2);
	cout << listFindEnd(dupe2) << endl;

	listDisplayReverse(list);
    //list = new Node(17);
    //listAddToEnd(list, 42);
}
