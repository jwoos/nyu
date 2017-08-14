#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

template <typename T>
class BST;

template <typename T>
class BSTNode {
	public:
		BSTNode(const T& newData = T(), BSTNode<T>* newParent = nullptr, BSTNode<T>* newLeft = nullptr, BSTNode<T>* newRight = nullptr) : data(newData), left(newLeft), right(newRight), parent(newParent) {}

	private:
		T data;
		BSTNode<T>* left;
		BSTNode<T>* right;
		BSTNode<T>* parent;
};

template <typename T>
class BST {
	public:
		BST() : root(nullptr) {}

		~BST() {
			clear();
		}

		BST(const BST& rhs) : root(nullptr) {
			*this = rhs;
		}

		bool isEmpty() const {
			return root == nullptr;
		}

		BST<T>& operator=(const BST& rhs) {
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

			queue<BSTNode<T>*> q;
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
				root = new BSTNode<T>(newData);
			} else {
				BSTNode<T>* temp = root;
				BSTNode<T>* previous = root;

				while (temp != nullptr) {
					previous = temp;
					if (temp -> data > newData) {
						temp = temp -> left;
					} else {
						temp = temp -> right;
					}
				}

				if (previous -> data > newData) {
					previous -> left = new BSTNode<T>(newData, previous);
				} else {
					previous -> right = new BSTNode<T>(newData, previous);
				}
			}
		}

		void remove(const T& data) {
			BSTNode<T>* toRemove = find(data);

			remove(toRemove);
		}

		BSTNode<T>* find(const T& data) {
			BSTNode<T>* temp = root;
			BSTNode<T>* previous = root;

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


	private:
		BSTNode<T>* root;

		void printPreOrder(BSTNode<T>* start) {
			if (start != nullptr) {
				cout << start -> data << ", ";
				printPreOrder(start -> left);
				printPreOrder(start -> right);
			}
		}

		void printInOrder(BSTNode<T>* start) {
			if (start != nullptr) {
				printInOrder(start -> left);
				cout << start -> data << ", ";
				printInOrder(start -> right);
			}
		}

		void printPostOrder(BSTNode<T>* start) {
			if (start != nullptr) {
				printPostOrder(start -> left);
				printPostOrder(start -> right);
				cout << start -> data << ", ";
			}
		}

		void printLevelOrder(BSTNode<T>* start) {
			if (start == nullptr) {
				return;
			}

			queue<BSTNode<T>*> q;
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

		BSTNode<T>* recursiveCopy(BSTNode<T>* rhs) {
			if (rhs.isEmpty()) {
				return nullptr;
			}

			BSTNode<T>* temp = new BSTNode<T>(rhs -> data, nullptr, recursiveCopy(rhs -> left), recursiveCopy(rhs -> right));

			if (temp -> left != nullptr) {
				temp -> left -> parent = temp;
			}

			if (temp -> right != nullptr) {
				temp -> right -> parent = temp;
			}

			return temp;
		}

		void remove(BSTNode<T>* toRemove) {
			if (toRemove == nullptr) {
				return;
			}

			BSTNode<T>* parent = toRemove -> parent;

			if (toRemove -> left == nullptr && toRemove -> right == nullptr) {
				if (parent == nullptr) {
					root = nullptr;
					delete toRemove;
				} else {
					if (parent -> left == toRemove) {
						parent -> left = nullptr;
					} else {
						parent -> right = nullptr;
					}

					delete toRemove;
				}
			} else if (toRemove -> left == nullptr) {
				BSTNode<T>* removeChild = toRemove -> right;
				toRemove -> data = toRemove -> right -> data;
				toRemove -> left = toRemove -> right -> left;

				if (toRemove -> left != nullptr) {
					toRemove -> left -> parent = toRemove;
				}

				toRemove -> right = toRemove -> right -> right;

				if (toRemove -> right != nullptr) {
					toRemove -> right -> parent = toRemove;
				}

				delete removeChild;
			} else if (toRemove -> right == nullptr) {
				BSTNode<T>* removeChild = toRemove -> left;
				toRemove -> data = toRemove -> left -> data;
				toRemove -> right = toRemove -> left -> right;

				if (toRemove -> right != nullptr) {
					toRemove -> right -> parent = toRemove;
				}

				toRemove -> left = toRemove -> left -> left;

				if (toRemove -> left != nullptr) {
					toRemove -> left -> parent = toRemove;
				}

				delete removeChild;
			} else {
				BSTNode<T>* temp = toRemove -> right;

				while (temp != nullptr) {
					temp = temp -> left;
				}

				toRemove -> data = temp -> data;
				remove(temp);
			}
		}
};

int main() {}
