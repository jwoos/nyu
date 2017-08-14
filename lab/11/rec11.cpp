#include <cstdlib>
#include <iostream>

using namespace std;

struct Node {
	Node(int data = 0, Node* link = nullptr) : data(data), link(link) {}

	int data;

	Node* link;
};

void listDisplay(Node* head) {
    Node* p = head;
    while (p != nullptr) {
        cout << p -> data << ' ';
        p = p -> link;
    }
    cout << endl;
}

void listInsertHead(int entry, Node*& headPtr) {
	headPtr = new Node(entry, headPtr);
}

void listSplice(Node* before, Node* head) {
	Node* after = before -> link;

	before -> link = head;

	while (head -> link != nullptr) {
		head = head -> link;
	}

	head -> link = after;
}

Node* listSearch(Node* mainList, Node* searchList) {
	Node* originalSearch = searchList;
	int length = 1;

	Node* counter = searchList;
	while (counter -> link != nullptr) {
		length++;
		counter = counter -> link;
	}

	while (mainList != nullptr) {
		int matched = 0;
		Node* original = mainList;
		Node* toTest = mainList;

		searchList = originalSearch;
		while (searchList != nullptr) {
			if (toTest == nullptr) {
				return nullptr;
			}
			if (toTest -> data == searchList -> data) {
				matched++;
				searchList = searchList -> link;
				toTest = toTest -> link;

				if (matched == length) {
					return mainList;
				}
			} else {
				break;
			}
		}

		mainList = original -> link;
	}

	return nullptr;
}

int main() {
	cout << "Part One: " << endl << endl;

	Node L1d(1);
	Node L1c(9, &L1d);
	Node L1b(7, &L1c);
	Node L1a(5, &L1b);

	cout << "L1: ";
	listDisplay(&L1a);

	Node L2c(2);
	Node L2b(3, &L2c);
	Node L2a(6, &L2b);

	cout << "L2: ";
	listDisplay(&L2a);

	cout << "Target: ";
	listDisplay(&L1b);

	listSplice(&L1b, &L2a);

	cout << "L1: ";
	listDisplay(&L1a);

	cout << "L2: ";
	listDisplay(&L2a);

	cout << endl << "=====================" << endl << endl;

	cout << "Part Two: " << endl;

	Node targetI(6);
	Node targetH(5, &targetI);
	Node targetG(4, &targetH);
	Node targetF(2, &targetG);
	Node targetE(3, &targetF);
	Node targetD(2, &targetE);
	Node targetC(3, &targetD);
	Node targetB(2, &targetC);
	Node targetA(1, &targetB);

	cout << "Target: ";
	listDisplay(&targetA);

	Node match1(1);

	cout << "Attempt Match: ";
	listDisplay(&match1);
	listDisplay(listSearch(&targetA, &match1));
	cout << endl;

	Node match2b(9);
	Node match2a(3, &match2b);
	cout << "Attempt Match: ";
	listDisplay(&match2a);
	if (listSearch(&targetA, &match2a) == nullptr) {
		cout << "Failed to match!";
	} else {
		listDisplay(listSearch(&targetA, &match2a));
	}
	cout << endl;

	Node match3d(6);
	Node match3c(5, &match3d);
	Node match3b(4, &match3c);
	Node match3a(2, &match3b);
	cout << "Attempt Match: ";
	listDisplay(&match3a);
	if (listSearch(&targetA, &match3a) == nullptr) {
		cout << "Failed to match!";
	} else {
		listDisplay(listSearch(&targetA, &match3a));
	}
	cout << endl;

	Node match4d(4);
	Node match4c(2, &match4d);
	Node match4b(3, &match4c);
	Node match4a(2, &match4b);
	cout << "Attempt Match: ";
	listDisplay(&match4a);
	if (listSearch(&targetA, &match4a) == nullptr) {
		cout << "Failed to match!";
	} else {
		listDisplay(listSearch(&targetA, &match4a));
	}
	cout << endl;

	Node match5c(7);
	Node match5b(6, &match5c);
	Node match5a(5, &match5b);
	cout << "Attempt Match: ";
	listDisplay(&match5a);
	if (listSearch(&targetA, &match5a) == nullptr) {
		cout << "Failed to match!";
	} else {
		listDisplay(listSearch(&targetA, &match5a));
	}
	cout << endl;
}
