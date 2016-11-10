#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <cmath>

using namespace std;

template <typename T>
class AVL;

template <typename T>
class AVLNode {
	public:
		AVLNode(const T& newData = T(), AVLNode<T>* newParent = nullptr, AVLNode<T>* newLeft = nullptr, AVLNode<T>* newRight = nullptr) : data(newData), parent(newParent), left(newLeft), right(newRight) {}

		void calculateHeight() {
			int leftHeight = -1;
			int rightHeight = -1;

			if (left != nullptr) {
				leftHeight = left -> height;
			}

			if (right != nullptr) {
				rightHeight = right -> height;
			}

			height = max(leftHeight, rightHeight) + 1;
		}

	private:
		int height;
		T data;
		AVLNode<T>* parent;
		AVLNode<T>* left;
		AVLNode<T>* right;

	friend AVL<T>;
};

template <typename T>
class AVL {
	private:
		AVLNode<T>* root;

		void printPreOrder(AVLNode<T>* start) {
			if (start != nullptr) {
				cout << start -> data << ", ";
				printPreOrder(start -> left);
				printPreOrder(start -> right);
			}
		}

		void printInOrder(AVLNode<T>* start) {
			if (start != nullptr) {
				printInOrder(start -> left);
				cout << start -> data << ", ";
				printInOrder(start -> right);
			}
		}

		void printPostOrder(AVLNode<T>* start) {
			if (start != nullptr) {
				printPostOrder(start -> left);
				printPostOrder(start -> right);
				cout << start -> data << ", ";
			}
		}

		void printLevelOrder(AVLNode<T>* start) {
			if (start == nullptr) {
				return;
			}

			queue<AVLNode<T>*> q;
			q.push(start);

			while (!q.empty()) {
				cout << q.front() -> data << ", ";

				if (q.front() -> left != nullptr) {
					q.push(q.front() -> left);
				}

				if (q.front() -> right != nullptr) {
					q.push(q.front() -> right);
				}

				q.pop();
			}
		}

		AVLNode<T>* recursiveCopy(AVLNode<T>* rhs) {
			if (rhs.isEmpty()) {
				return nullptr;
			}

			AVLNode<T>* temp = new AVLNode<T>(rhs -> data, nullptr, recursiveCopy(rhs -> left), recursiveCopy(rhs -> right));

			if (temp -> left != nullptr) {
				temp -> left -> parent = temp;
			}

			if (temp -> right != nullptr) {
				temp -> right -> parent = temp;
			}

			return temp;
		}

		int getHeight(AVLNode<T>* start) {
			if (start == nullptr) {
				return -1;
			}

			return start -> height;
		}

		void doRotation(AVLNode<T>* start) {
			int leftHeight = getHeight(start -> left);
			int rightHeight = getHeight(start -> right);

			if (rightHeight > leftHeight) {
				int leftGCHeight = getHeight(start -> right -> left);
				int rightGCHeight = getHeight(start -> right -> right);

				if (rightGCHeight > leftGCHeight) {
					singleCCR(start);
				} else {
					doubleCCR(start);
				}
			} else {
				int leftGCHeight = getHeight(start -> left -> left);
				int rightGCHeight = getHeight(start -> left -> right);

				if (leftGCHeight > rightGCHeight) {
					singleCCR(start);
				} else {
					doubleCCR(start);
				}
			}
		}

		void singleCCR(AVLNode<T>* start) {
			AVLNode<T>* child = start -> right;
			start -> right = child -> left;
			child -> parent = start -> parent;

			if (start -> right != nullptr) {
				start -> right -> parent = start;
			}

			child -> left = start;
			start -> parent = child;

			if (child -> parent != nullptr) {
				if (child -> parent -> left == start) {
					child -> parent -> left = child;
				} else {
					child -> parent -> right = start;
				}
			}

			start -> calculateHeight();
			child -> calculateHeight();
		}

		void singleCR(AVLNode<T>* start) {
			AVLNode<T>* child = start -> left;
			start -> left = child -> right;
			child -> parent = start -> parent;

			if (start -> left != nullptr) {
				start -> left -> parent = start;
			}

			child -> right = start;
			start -> parent = child;

			if (child -> parent != nullptr) {
				if (child -> parent -> right == start) {
					child -> parent -> right = child;
				} else {
					child -> parent -> left = start;
				}
			}

			start -> calculateHeight();
			child -> calculateHeight();
		}

		void doubleCCR(AVLNode<T>* start) {
			singleCR(start -> right);
			singleCCR(start);
		}

		void doubleCR(AVLNode<T>* start) {
			singleCCR(start -> left);
			singleCR(start);
		}

	public:
		AVL() : root(nullptr) {}

		virtual ~AVL() {
			clear();
		}

		AVL(const AVL& rhs) : root(nullptr) {
			*this = rhs;
		}

		bool isEmpty() const {
			return root == nullptr;
		}

		AVL<T>& operator=(const AVL& rhs) {
			if (this == &rhs) {
				return *this;
			}

			clear();

			root = recursiveCopy(rhs.root);

			return *this;
		}

		void clear() {
			if (isEmpty()) {
				return;
			}

			queue<AVLNode<T>*> q;
			q.push(root);
			root = nullptr;

			while (!q.empty()) {
				if (q.front() -> left != nullptr) {
					q.push(q.front() -> left);
				}

				if (q.front() -> right != nullptr) {
					q.push(q.front() -> right);
				}

				delete q.front();
				q.pop();
			}
		}

		void insert(const T& newData) {
			if (isEmpty()) {
				root = new AVLNode<T>(newData);
			} else {
				AVLNode<T>* temp = root;
				AVLNode<T>* previous = root;

				while (temp != nullptr) {
					previous = temp;
					if (temp -> data > newData) {
						temp = temp -> left;
					} else {
						temp = temp -> right;
					}
				}

				if (previous -> data > newData) {
					previous -> left = new AVLNode<T>(newData, previous);
				} else {
					previous -> right = new AVLNode<T>(newData, previous);
				}

				temp = previous;
				while (temp != nullptr) {
					int leftHeight = getHeight(temp -> left);
					int rightHeight = getHeight(temp -> right);

					if (abs(leftHeight - rightHeight) > 1) {
						doRotation(temp);
					}

					temp -> calculateHeight();
					temp = temp -> parent;
				}
			}
		}

		void remove(const T& data) {
			AVLNode<T>* toRemove = find(data);

			remove(toRemove);
		}

		AVLNode<T>* find(const T& data) {
			AVLNode<T>* temp = root;
			AVLNode<T>* previous = root;

			while (temp != nullptr) {
				if (temp -> data == data) {
					return temp;
				}

				if (temp -> data > data) {
					temp = temp -> left;
				} else {
					temp = temp -> right;
				}
			}

			return temp;
		}

		void printPreOrder() {
			printPreOrder(root);
			cout << endl;
		}

		void printInOrder() {
			printInOrder(root);
			cout << endl;
		}

		void printPostOrder() {
			printPostOrder(root);
			cout << endl;
		}

		void printLevelOrder () {
			printLevelOrder(root);
			cout << endl;
		}
};

int main() {
	AVL<int> t;
	srand(time(nullptr));

	for (int i = 0; i < 10; i++) {
		//t.insert(rand() % 100);
		t.insert(i * 10);
	}

	cout << "pre order: ";
	t.printPreOrder();

	cout << "in order: ";
	t.printInOrder();

	cout << "post order: ";
	t.printPostOrder();

	cout << "level order: ";
	t.printLevelOrder();
}
