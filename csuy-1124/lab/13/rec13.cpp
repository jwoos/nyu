#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>
#include <climits>

using namespace std;

// Linked list
struct Node {
	Node(int data, Node* next=nullptr) : data(data), next(next) {}

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
}

// Tree
struct TNode {
  TNode(int data = 0, TNode *left = nullptr, TNode *right = nullptr) : data(data), left(left), right(right) {}

  int data;
  TNode *left, *right;
};

TNode* treeAdd(TNode* root, int x=0, char direction='r') {
	if (direction == 'l') {
		root -> left = new TNode(x);
		return root -> left;
	} else {
		root -> right = new TNode(x);
		return root -> right;
	}
}

// lab function prototypes
void displayBinary(int n);
Node* sumList(Node* a, Node* b);
int max(TNode* root);
int sumCString(char* cstring);
int binarySearch(char* arr, char search, int low, int high);
void f(int n);

int main() {
	// test displayBinary
	cout << "displayBinary" << endl;
	displayBinary(1);
	cout << endl;
	displayBinary(2);
	cout << endl;
	displayBinary(3);
	cout << endl;
	displayBinary(1024);
	cout << endl;
	cout << "----------------------------------" << endl;

	// test sumList
	cout << "sumList" << endl;
	Node* a = new Node(1);
	listAddToEnd(a, 2);
	listAddToEnd(a, 3);
	listAddToEnd(a, 4);
	listAddToEnd(a, 5);
	listDisplay(a);

	Node* b = new Node(6);
	listAddToEnd(b, 7);
	listAddToEnd(b, 8);
	listAddToEnd(b, 9);
	listAddToEnd(b, 10);
	listDisplay(b);

	Node* c = sumList(a, b);
	listDisplay(c);
	cout << "----------------------------------" << endl;

	// test max
	cout << "max" << endl;
	TNode* root = new TNode(10);
	TNode* r = treeAdd(root, 20, 'r');
	treeAdd(r, 30, 'r');
	TNode* l = treeAdd(root, 20, 'l');
	treeAdd(l, 40, 'l');

	cout << max(root) << endl;
	cout << "----------------------------------" << endl;

	// test sumCString
	cout << "sumCString" << endl;
	char aString[] = "ABCD";
	cout << sumCString(aString) << endl;
	cout << "----------------------------------" << endl;

	// test binarySearch
	cout << "binarySearch" << endl;
	char anotherString[] = "abcdefghijklmnopqrstuvwxyz";
	cout << binarySearch(anotherString, 'j', 0, 25) << endl;
	cout << "----------------------------------" << endl;

	// test f
	cout << "f" << endl;
	/*
	 *f(1);
	 *cout << endl;
	 *f(2);
	 *cout << endl;
	 *f(4);
	 *cout << endl;
	 *f(8);
	 *cout << endl;
	 *f(16);
	 *cout << endl;
	 */
	f(5);
	cout << endl;
	cout << "----------------------------------" << endl;
}

// lab functions
void displayBinary(int x) {
	if (x < 2) {
		cout << x << ' ';
	} else {
		displayBinary(x / 2);
		cout << x % 2 << ' ';
	}
}

Node* sumList(Node* a, Node* b) {
	if (a -> next == nullptr) {
		return new Node(a -> data + b -> data);
		cout << "last" << endl;
	} else {
		Node* next = sumList(a -> next, b -> next);
		return new Node(a -> data + b -> data, next);
	}
}

int max(TNode* root) {
	int right = -1;
	int left = -1;

	if (root == nullptr) {
		return INT_MIN;
	}

	int current = root -> data;

	right = max(root -> right);
	left = max(root -> left);

	if (right < current && left < current) {
		return current;
	} else {
		if (right > left) {
			return right;
		} else {
			return left;
		}
	}
}

int sumCString(char* cstring) {
	int total = 0;

	if (cstring[0] == '\0') {
		return 0;
	}

	total += sumCString(cstring + 1);
	total += int(cstring[0]);
	return total;
}

int binarySearch(char* arr, char search, int low, int high) {
	int mid = (high + low) / 2;
	if (high < low) {
		return -1;
	}

	if (arr[mid] == search) {
		return mid;
	} else if (search < arr[mid]) {
		return binarySearch(arr, search, low, mid -1);
	} else if (search > arr[mid]) {
		return binarySearch(arr, search, mid + 1, high);
	}
}

void f(int n) {
	if (n > 1) {
		cout << 'a';
		f(n/2);
		cout << 'b';
		f(n/2);
	}
	cout << 'c';
}
