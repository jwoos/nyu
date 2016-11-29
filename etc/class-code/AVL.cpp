#include <iostream>
#include <queue>
#include <ctime>

using namespace std;

template <class T>
class AVL;

template <class T>
class AVLNode{
	int height;
	T data;
	AVLNode<T> *parent, *left, *right;
public:
	AVLNode(const T& newdata = T(), AVLNode<T>* newparent = nullptr, AVLNode<T>* newleft = nullptr, AVLNode<T>* newright = nullptr) :
		data(newdata), parent(newparent), left(newleft), right(newright){
		calculateHeight();
	}

	void calculateHeight();

	friend class AVL < T >;
};

template <class T>
void AVLNode<T>::calculateHeight(){
	int leftHeight = -1;
	int rightHeight = -1;
	if (left != nullptr)
		leftHeight = left->height;
	if (right != nullptr)
		rightHeight = right->height;
	height = max(leftHeight, rightHeight) + 1;
}

template <class T>
class AVL{
	AVLNode<T>* root;
	void printPreOrder(AVLNode<T>* start);
	void printInOrder(AVLNode<T>* start);
	void printPostOrder(AVLNode<T>* start);
	void printLevelOrder(AVLNode<T>* start);
	void remove(AVLNode<T>* toRemove);
	AVLNode<T>* recursiveCopy(AVLNode<T>* rhs);
	int getHeight(AVLNode<T>* start);
	void doRotation(AVLNode<T>* start);
	void singleCCR(AVLNode<T>* start);
	void singleCR(AVLNode<T>* start);
	void doubleCCR(AVLNode<T>* start);
	void doubleCR(AVLNode<T>* start);
public:
	AVL() :root(nullptr){}
	virtual ~AVL(){ clear(); }
	AVL(const AVL<T>& rhs) : root(nullptr){ *this = rhs; }
	void printPreOrder(){ printPreOrder(root); cout << endl; }
	void printInOrder(){ printInOrder(root); cout << endl; }
	void printPostOrder(){ printPostOrder(root); cout << endl; }
	void printLevelOrder(){ printLevelOrder(root); cout << endl; }
	void remove(const T& data){ remove(find(data)); }
	bool isEmpty() const{ return root == nullptr; }

	AVL<T>& operator=(const AVL<T>& rhs);
	void clear();
	void insert(const T& data);
	AVLNode<T>* find(const T& data);
};
template <class T>
void AVL<T>::singleCCR(AVLNode<T>* start){
	AVLNode<T>* child = start->right;
	start->right = child->left;
	child->parent = start->parent;
	start->parent = child; 
	child->left = start;
	if (start->right != nullptr)
		start->right->parent = start;
	if (child->parent != nullptr){
		if (child->parent->left == start)
			child->parent->left = child;
		else
			child->parent->right = child;
	}
	else
		root = child;
	start->calculateHeight();
	child->calculateHeight();
}
template <class T>
void AVL<T>::singleCR(AVLNode<T>* start){
	AVLNode<T>* child = start->left;
	start->left = child->right;
	child->parent = start->parent;
	start->parent = child;
	child->right = start;
	if (start->left != nullptr)
		start->left->parent = start;
	if (child->parent != nullptr){
		if (child->parent->right == start)
			child->parent->right = child;
		else
			child->parent->left = child;
	}
	else
		root = child;
	start->calculateHeight();
	child->calculateHeight();
}
template <class T>
void AVL<T>::doubleCCR(AVLNode<T>* start){
	singleCR(start->right);
	singleCCR(start);
}
template <class T>
void AVL<T>::doubleCR(AVLNode<T>* start){
	singleCCR(start->left);
	singleCR(start);
}
template <class T>
void AVL<T>::doRotation(AVLNode<T>* start){
	int leftHeight = getHeight(start->left);
	int rightHeight = getHeight(start->right);
	if (rightHeight > leftHeight){
		int leftGCHeight = getHeight(start->right->left);
		int rightGCHeight = getHeight(start->right->right);
		if (rightGCHeight > leftGCHeight)
			singleCCR(start);
		else
			doubleCCR(start);
	}
	else{
		int leftGCHeight = getHeight(start->left->left);
		int rightGCHeight = getHeight(start->left->right);
		if (leftGCHeight > rightGCHeight)
			singleCR(start);
		else
			doubleCR(start);
	}
}
template <class T>
int AVL<T>::getHeight(AVLNode<T>* start){
	if (start == nullptr)
		return -1;
	return start->height;
}
template <class T>
void AVL<T>::remove(AVLNode<T>* toRemove){
	if (toRemove == nullptr)
		return;
	AVLNode<T>* parent = toRemove->parent;
	if (toRemove->left == nullptr && toRemove->right == nullptr){//no children
		if (toRemove == root)
			root = nullptr;
		else{
			if (toRemove == toRemove->parent->left)
				toRemove->parent->left = nullptr;
			else
				toRemove->parent->right = nullptr;
		}
		delete toRemove;
	}
	else if (toRemove->left == nullptr){//it has a right child
		AVLNode<T>* rightChild = toRemove->right;
		toRemove->data = rightChild->data;
		toRemove->left = rightChild->left;
		toRemove->right = rightChild->right;
		if (toRemove->left != nullptr)
			toRemove->left->parent = toRemove;
		if (toRemove->right != nullptr)
			toRemove->right->parent = toRemove;
		delete rightChild;
		toRemove->calculateHeight();
		parent = toRemove;
	}
	else if (toRemove->right == nullptr){//it has a left child
		AVLNode<T>* leftChild = toRemove->left;
		toRemove->data = leftChild->data;
		toRemove->right = leftChild->right;
		toRemove->left = leftChild->left;
		if (toRemove->right != nullptr)
			toRemove->right->parent = toRemove;
		if (toRemove->left != nullptr)
			toRemove->left->parent = toRemove;
		delete leftChild;
		toRemove->calculateHeight();
		parent = toRemove;
	}
	else {//two children
		AVLNode<T>* temp = toRemove->right;
		while (temp->left != nullptr)
			temp = temp->left;
		toRemove->data = temp->data;
		remove(temp);
		parent = toRemove;
	}
	while (parent != nullptr){
		int leftHeight = getHeight(parent->left);
		int rightHeight = getHeight(parent->right);
		if (abs(leftHeight - rightHeight) > 1)
			doRotation(parent);
		parent->calculateHeight();

		parent = parent->parent;
	}
}

template <class T>
AVLNode<T>* AVL<T>::recursiveCopy(AVLNode<T>* rhs){
	if (rhs == nullptr)
		return nullptr;
	AVLNode<T>* temp = new AVLNode<T>(rhs->data, nullptr,
		recursiveCopy(rhs->left), recursiveCopy(rhs->right));
	if (temp->left != nullptr)
		temp->left->parent = temp;
	if (temp->right != nullptr)
		temp->right->parent = temp;
	return temp;
}

template <class T>
AVL<T>& AVL<T>::operator=(const AVL<T>& rhs){
	if (this == &rhs)
		return *this;
	clear();
	root = recursiveCopy(rhs.root);
	return *this;
}
template <class T>
void AVL<T>::clear(){
	if (root == nullptr)
		return;
	queue<AVLNode<T>*> q;
	q.push(root);
	root = nullptr;
	while (!q.empty()){
		if (q.front()->left != nullptr)
			q.push(q.front()->left);
		if (q.front()->right != nullptr)
			q.push(q.front()->right);
		delete q.front();
		q.pop();
	}
}

template <class T>
AVLNode<T>* AVL<T>::find(const T& data){
	AVLNode<T>* temp = root;
	while (temp != nullptr){
		if (temp->data == data)
			return temp;
		else if (temp->data > data)
			temp = temp->left;
		else
			temp = temp->right;
	}
	return nullptr;
}

template <class T>
void AVL<T>::insert(const T& data){
	if (isEmpty())
		root = new AVLNode<T>(data);
	else{
		AVLNode<T>* temp = root;
		AVLNode<T>* prev = root;
		while (temp != nullptr){
			prev = temp;
			if (temp->data > data)
				temp = temp->left;
			else
				temp = temp->right;
		}
		if (prev->data > data)
			prev->left = new AVLNode<T>(data, prev);
		else
			prev->right = new AVLNode<T>(data, prev);
		
		for (temp = prev; temp != nullptr; temp = temp->parent){
			int leftHeight = getHeight(temp->left);
			int rightHeight = getHeight(temp->right);
			if (abs(leftHeight - rightHeight) > 1)
				doRotation(temp);
			temp->calculateHeight();
		}
		
	}
}

template <class T>
void AVL<T>::printPreOrder(AVLNode<T>* start){
	if (start != nullptr){
		cout << start->data << ", ";
		printPreOrder(start->left);
		printPreOrder(start->right);
	}
}

template <class T>
void AVL<T>::printInOrder(AVLNode<T>* start){
	if (start != nullptr){
		printInOrder(start->left);
		cout << start->data << ", ";
		printInOrder(start->right);
	}
}
template <class T>
void AVL<T>::printPostOrder(AVLNode<T>* start){
	if (start != nullptr){
		printPostOrder(start->left);
		printPostOrder(start->right);
		cout << start->data << ", ";
	}
}

template <class T>
void AVL<T>::printLevelOrder(AVLNode<T>* start){
	if (start == nullptr)
		return;
	queue<AVLNode<T>*> q;
	q.push(start);
	while (!q.empty()){
		cout << q.front()->data << ", ";
		if (q.front()->left != nullptr)
			q.push(q.front()->left);
		if (q.front()->right != nullptr)
			q.push(q.front()->right);
		q.pop();
	}
}


int main(){
	AVL<int> t;

	srand(time(NULL));
	for (int i = 0; i < 10; i++){
		//int val = rand() % 100;
		int val = i;
		t.insert(val);
		cout << val << endl;
	}
	AVL<int> t2 = t;
	cout << "IN ORDER: ";
	t2.printInOrder();
	cout << "PRE ORDER: ";
	t2.printPreOrder();
	cout << "POST ORDER: ";
	t2.printPostOrder();
	cout << "LEVEL ORDER: ";
	t2.printLevelOrder();

	t2.remove(0);
	t2.remove(2);
	cout << "IN Order : ";
	t2.printInOrder();
	cout << "PRE ORDER: ";
	t2.printPreOrder();
	cout << "POST ORDER: ";
	t2.printPostOrder();
	cout << "LEVEL ORDER: ";
	t2.printLevelOrder();
}