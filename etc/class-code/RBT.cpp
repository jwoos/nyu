#include <iostream>
#include <queue>
#include <ctime>
//Good visualization: https://www.cs.usfca.edu/~galles/visualization/RedBlack.html
using namespace std;

template <class T>
class RBT;

template <class T>
class RBTNode{
	bool isBlack;
	T data;
	RBTNode<T> *parent, *left, *right;
public:
	RBTNode(const T& newdata = T(), RBTNode<T>* newparent = nullptr, RBTNode<T>* newleft = nullptr, RBTNode<T>* newright = nullptr, bool newIsBlack=false) :
		data(newdata), parent(newparent), left(newleft), right(newright),isBlack(newIsBlack){}

	friend class RBT < T >;
};


template <class T>
class RBT{
	RBTNode<T>* root;
	void printPreOrder(RBTNode<T>* start);
	void printInOrder(RBTNode<T>* start);
	void printPostOrder(RBTNode<T>* start);
	void printLevelOrder(RBTNode<T>* start);
	void remove(RBTNode<T>* toRemove);
	RBTNode<T>* recursiveCopy(RBTNode<T>* rhs);
	void doRotation(RBTNode<T>* start);
	void singleCCR(RBTNode<T>* start);
	void singleCR(RBTNode<T>* start);
	void doubleCCR(RBTNode<T>* start);
	void doubleCR(RBTNode<T>* start);
	bool isBlack(RBTNode<T>* node){ return node == nullptr ? true : node->isBlack; }
	void recolor(RBTNode<T>* node);
	bool isLeftChild(RBTNode<T>* node){ return node == node->parent->left; }
public:
	RBT() :root(nullptr){}
	virtual ~RBT(){ clear(); }
	RBT(const RBT<T>& rhs) : root(nullptr){ *this = rhs; }
	void printPreOrder(){ printPreOrder(root); cout << endl; }
	void printInOrder(){ printInOrder(root); cout << endl; }
	void printPostOrder(){ printPostOrder(root); cout << endl; }
	void printLevelOrder(){ printLevelOrder(root); cout << endl; }
	void remove(const T& data){ remove(find(data)); }
	bool isEmpty() const{ return root == nullptr; }

	RBT<T>& operator=(const RBT<T>& rhs);
	void clear();
	void insert(const T& data);
	RBTNode<T>* find(const T& data);
};
template <class T>
void RBT<T>::singleCCR(RBTNode<T>* node){
	RBTNode<T>* start = node->parent->parent;
	RBTNode<T>* child = start->right;
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
	child->isBlack = true;
	node->isBlack = false;
	start->isBlack = false;
}
template <class T>
void RBT<T>::singleCR(RBTNode<T>* node){
	RBTNode<T>* start = node->parent->parent;
	RBTNode<T>* child = start->left;
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
	child->isBlack = true;
	node->isBlack = false;
	start->isBlack = false;
}
template <class T>
void RBT<T>::doubleCCR(RBTNode<T>* node){
	RBTNode<T>* start = node->parent->parent;
	singleCR(start->right);
	singleCCR(start);
/*	node->isBlack = true;
	if (node->left != nullptr)
		node->left->isBlack = false;
	if (node->right != nullptr)
		node->right->isBlack = false;
*/
}
template <class T>
void RBT<T>::doubleCR(RBTNode<T>* node){
	RBTNode<T>* start = node->parent->parent;
	singleCCR(start->left);
	singleCR(start);
/*	node->isBlack = true;
	if (node->left != nullptr)
		node->left->isBlack = false;
	if (node->right != nullptr)
		node->right->isBlack = false;
*/
}
template <class T>
void RBT<T>::doRotation(RBTNode<T>* node){
	bool nodeIsLeftChild = isLeftChild(node);
	bool parentIsLeftChild = isLeftChild(node->parent);
	if (nodeIsLeftChild && parentIsLeftChild)
		singleCR(node);
	else if (!nodeIsLeftChild && parentIsLeftChild)
		doubleCR(node);
	else if (!nodeIsLeftChild && !parentIsLeftChild)
		singleCCR(node);
	else
		doubleCCR(node);
}

template <class T>
void RBT<T>::remove(RBTNode<T>* toRemove){
	if (toRemove == nullptr)
		return;
	RBTNode<T>* parent = toRemove->parent;
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
		RBTNode<T>* rightChild = toRemove->right;
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
		RBTNode<T>* leftChild = toRemove->left;
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
		RBTNode<T>* temp = toRemove->right;
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
RBTNode<T>* RBT<T>::recursiveCopy(RBTNode<T>* rhs){
	if (rhs == nullptr)
		return nullptr;
	RBTNode<T>* temp = new RBTNode<T>(rhs->data, nullptr,
		recursiveCopy(rhs->left), recursiveCopy(rhs->right),rhs->isBlack);
	if (temp->left != nullptr)
		temp->left->parent = temp;
	if (temp->right != nullptr)
		temp->right->parent = temp;
	return temp;
}

template <class T>
RBT<T>& RBT<T>::operator=(const RBT<T>& rhs){
	if (this == &rhs)
		return *this;
	clear();
	root = recursiveCopy(rhs.root);
	return *this;
}
template <class T>
void RBT<T>::clear(){
	if (root == nullptr)
		return;
	queue<RBTNode<T>*> q;
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
RBTNode<T>* RBT<T>::find(const T& data){
	RBTNode<T>* temp = root;
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
void RBT<T>::recolor(RBTNode<T>* node){
	node->isBlack = false;
	node->left->isBlack = true;
	node->right->isBlack = true;
	if (node->parent == nullptr)
		root->isBlack = true;
	else if (!node->parent->isBlack)
		doRotation(node);
}
template <class T>
void RBT<T>::insert(const T& data){
	if (isEmpty()){
		root = new RBTNode<T>(data);
		root->isBlack = true;
	}
	else{
		RBTNode<T>* temp = root;
		RBTNode<T>* prev = root;
		while (temp != nullptr){
			bool leftIsBlack = isBlack(temp->left);
			bool rightIsBlack = isBlack(temp->right);
			if (temp->isBlack && !leftIsBlack && !rightIsBlack)
				recolor(temp);
			prev = temp;
			if (temp->data > data)
				temp = temp->left;
			else
				temp = temp->right;
		}
		RBTNode<T>* newNode = new RBTNode<T>(data, prev);
		if (prev->data > data)
			prev->left = newNode;
		else
			prev->right = newNode;
		if (!isBlack(prev))
			doRotation(newNode);

	}
}

template <class T>
void RBT<T>::printPreOrder(RBTNode<T>* start){
	if (start != nullptr){
		cout << start->data << ", ";
		printPreOrder(start->left);
		printPreOrder(start->right);
	}
}

template <class T>
void RBT<T>::printInOrder(RBTNode<T>* start){
	if (start != nullptr){
		printInOrder(start->left);
		cout << start->data << ", ";
		printInOrder(start->right);
	}
}
template <class T>
void RBT<T>::printPostOrder(RBTNode<T>* start){
	if (start != nullptr){
		printPostOrder(start->left);
		printPostOrder(start->right);
		cout << start->data << ", ";
	}
}

template <class T>
void RBT<T>::printLevelOrder(RBTNode<T>* start){
	if (start == nullptr)
		return;
	queue<RBTNode<T>*> q;
	q.push(start);
	while (!q.empty()){
		cout << q.front()->data << "(";
		if (q.front()->isBlack)
			cout << "B";
		else
			cout << "R";
		cout<< "), ";
		if (q.front()->left != nullptr)
			q.push(q.front()->left);
		if (q.front()->right != nullptr)
			q.push(q.front()->right);
		q.pop();
	}
}


int main(){
	RBT<int> t;

	srand(time(NULL));
	for (int i = 0; i < 10; i++){
		//int val = rand() % 100;
		int val = i;
		t.insert(val);
		cout << val << endl;
	}
	RBT<int> t2 = t;
	cout << "IN ORDER: ";
	t2.printInOrder();
	cout << "PRE ORDER: ";
	t2.printPreOrder();
	cout << "POST ORDER: ";
	t2.printPostOrder();
	cout << "LEVEL ORDER: ";
	t2.printLevelOrder();

/*	t2.remove(0);
	t2.remove(2);
	cout << "IN Order : ";
	t2.printInOrder();
	cout << "PRE ORDER: ";
	t2.printPreOrder();
	cout << "POST ORDER: ";
	t2.printPostOrder();
	cout << "LEVEL ORDER: ";
	t2.printLevelOrder();
	*/
}