#include <iostream>
#include <queue>
#include <ctime>

using namespace std;

template <class T>
class BST;

template <class T>
class BSTNode{
	T data;
	BSTNode<T> *left, *right, *parent;
public:
	BSTNode(const T& newdata = T(), BSTNode<T>* newparent = nullptr, BSTNode<T>* newleft = nullptr, BSTNode<T>* newright = nullptr) :
		data(newdata), parent(newparent), left(newleft), right(newright){}

	friend class BST < T > ;
};

template <class T>
class BST{
	BSTNode<T>* root;
	void printPreOrder(BSTNode<T>* start);
	void printInOrder(BSTNode<T>* start);
	void printPostOrder(BSTNode<T>* start);
	void printLevelOrder(BSTNode<T>* start);
	BSTNode<T>* recursiveCopy(BSTNode<T>* rhs);
	void remove(BSTNode<T>* toRemove);
public:
	BST(){ root = nullptr; }
	~BST(){ clear(); }
	BST(const BST& rhs) :root(nullptr){ *this = rhs; }
	bool isEmpty() const{ return root == nullptr; }
	void printPreOrder(){ printPreOrder(root); cout << endl; }
	void printInOrder(){ printInOrder(root); cout << endl; }
	void printPostOrder(){ printPostOrder(root); cout << endl; }
	void printLevelOrder(){ printLevelOrder(root); cout << endl; }

	BST<T>& operator=(const BST<T>& rhs);
	void clear();
	void insert(const T& data);
	void remove(const T& data){ remove(find(data)); }
	BSTNode<T>* find(const T& data) const;
	
};
template <class T>
void BST<T>::remove(BSTNode<T>* toRemove){
	if (toRemove == nullptr)
		return;
	BSTNode<T>* parent = toRemove->parent;
	if (toRemove->left == nullptr && toRemove->right == nullptr){ //leaf node
		if (parent == nullptr){ //last node on the tree
			root = nullptr;
			delete toRemove;
		}
		else{
			if (parent->left == toRemove)
				parent->left = nullptr;
			else
				parent->right = nullptr;
			delete toRemove;
		}
	}
	else if (toRemove->left == nullptr){//has a right child!!!
		BSTNode<T>* removeChild = toRemove->right;
		toRemove->data = toRemove->right->data;
		toRemove->left = toRemove->right->left;
		if (toRemove->left != nullptr)
			toRemove->left->parent = toRemove;
		toRemove->right = toRemove->right->right;
		if (toRemove->right != nullptr)
			toRemove->right->parent = toRemove;
		delete removeChild;
	}
	else if (toRemove->right == nullptr){//has a left child!!!
		BSTNode<T>* removeChild = toRemove->left;
		toRemove->data = toRemove->left->data;
		toRemove->right = toRemove->left->right;
		if (toRemove->right != nullptr)
			toRemove->right->parent = toRemove;
		toRemove->left = toRemove->left->left;
		if (toRemove->left != nullptr)
			toRemove->left->parent = toRemove;
		delete removeChild;
	}
	else{ //ugh... it has two children!!!
		BSTNode<T>* temp = toRemove->right;
		while (temp->left != nullptr)
			temp = temp->left;
		toRemove->data = temp->data;
		remove(temp);
	}

}
template <class T>
BST<T>& BST<T>::operator=(const BST<T>& rhs){
	if (this == &rhs)
		return *this;
	clear();
	root = recursiveCopy(rhs.root);
	return *this;
}
template <class T>
BSTNode<T>* BST<T>::recursiveCopy(BSTNode<T>* rhs){
	if (rhs == nullptr)
		return nullptr;
	BSTNode<T>* temp = new BSTNode<T>(rhs->data, nullptr,
		recursiveCopy(rhs->left), recursiveCopy(rhs->right));
	if (temp->left != nullptr)
		temp->left->parent = temp;
	if (temp->right != nullptr)
		temp->right->parent = temp;
	return temp;
}
template <class T>
void BST<T>::clear(){
	if (root == nullptr)
		return;
	queue<BSTNode<T>*> q;
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
BSTNode<T>* BST<T>::find(const T& data) const{
	BSTNode<T>* temp = root;
	while (temp != nullptr){
		if (temp->data == data)
			return temp;
		else if (temp->data > data)
			temp = temp->left;
		else
			temp = temp->right;
	}
	return temp;
}
template <class T>
void BST<T>::insert(const T& newdata){
	if (isEmpty()){
		root = new BSTNode<T>(newdata);
	}
	else{
		BSTNode<T>* temp = root;
		BSTNode<T>* prev = root;
		while (temp != nullptr){
			prev = temp;
			if (temp->data > newdata)
				temp = temp->left;
			else
				temp = temp->right;
		}
		if (prev->data > newdata) //left insertion
			prev->left = new BSTNode<T>(newdata, prev);
		else
			prev->right = new BSTNode<T>(newdata, prev);
		
	}
}
template <class T>
void BST<T>::printPreOrder(BSTNode<T>* start){
	if (start != nullptr){
		cout << start->data << ", ";
		printPreOrder(start->left);
		printPreOrder(start->right);
	}
}
template <class T>
void BST<T>::printInOrder(BSTNode<T>* start){
	if (start != nullptr){
		printInOrder(start->left);
		cout << start->data << ", ";
		printInOrder(start->right);
	}
}
template <class T>
void BST<T>::printPostOrder(BSTNode<T>* start){
	if (start != nullptr){
		printPostOrder(start->left);
		printPostOrder(start->right);
		cout << start->data << ", ";
	}
}
template <class T>
void BST<T>::printLevelOrder(BSTNode<T>* start){
	if (start == nullptr)
		return;
	queue<BSTNode<T>*> q;
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
