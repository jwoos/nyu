#include <iostream>

using namespace std;

template <class T>
class LList;

template <class T>
class LListItr;

template <class T>
class LListNode{
	T data;
	LListNode<T> *next, *prev;
public:
	LListNode(const T& newdata = T(), LListNode<T>* newprev = nullptr, LListNode<T>* newnext = nullptr) :
		data(newdata), next(newnext), prev(newprev){}
	friend class LList < T > ;
	friend class LListItr < T > ;
};

template <class T>
class LListItr{
	LListNode<T>* ptr;
public:
	LListItr(LListNode<T>* newptr = nullptr) :ptr(newptr){}
	bool operator==(const LListItr<T>& rhs)const { return ptr == rhs.ptr; }
	bool operator!=(const LListItr<T>& rhs)const { return ptr != rhs.ptr; }
	T operator*()const { return ptr->data; }
	T& operator*(){ return ptr->data; }
	LListItr<T>& operator++();
	LListItr<T>& operator--();
	LListItr<T> operator--(int);
	LListItr<T> operator++(int);
	friend class LList < T > ;
};

template <class T>
LListItr<T>& LListItr<T>::operator++(){
	if (ptr->next == nullptr)
		return *this;
	ptr = ptr->next;
	return *this;
}
template <class T>
LListItr<T> LListItr<T>::operator++(int){
	LListItr<T> temp = *this;
	if (ptr->next == nullptr)
		return *this;
	ptr = ptr->next;
	return temp;
}
template <class T>
LListItr<T>& LListItr<T>::operator--(){
	if (ptr->prev == nullptr)
		return *this;
	ptr = ptr->prev;
	return *this;
}
template <class T>
LListItr<T> LListItr<T>::operator--(int){
	LListItr<T> temp = *this;
	if (ptr->prev == nullptr)
		return *this;
	ptr = ptr->prev;
	return temp;
}

template <class T>
class LList{
	LListNode<T> *head, *tail;
	int numOfElements;
public:
	LList();
	virtual ~LList();
	LList(const LList<T>& rhs);
	LList<T>& operator=(const LList<T>& rhs);
	LListItr<T> begin(){ return head->next; }
	LListItr<T> end() { return tail; }
	int size() const { return numOfElements; }
	bool isEmpty() const{ return head->next == tail; }
	void insertAfter(LListItr<T> itr, const T& item);
	void insertBefore(LListItr<T> itr, const T& item);
	T remove(LListItr<T> itr);

	void push_back(const T& item){ insertBefore(tail, item); }
	void push_front(const T& item){ insertAfter(head, item); }
	T pop_back(){ return remove(tail->prev); }
	T pop_front(){ return remove(begin());}
	void clear(){while (!isEmpty()) pop_front();}
};

template <class T>
T LList<T>::remove(LListItr<T> itr){
	if (itr.ptr->next == nullptr || itr.ptr->prev == nullptr)
		return T();
	T retval = itr.ptr->data;
	LListNode<T>* temp = itr.ptr;
	numOfElements--;
	temp->next->prev = temp->prev;
	temp->prev->next = temp->next;
	delete temp;
	itr.ptr = tail;
	return retval;
}

template<class T>
void LList<T>::insertBefore(LListItr<T> itr, const T& item){
	if (itr.ptr->prev == nullptr)
		return;
	insertAfter(--itr, item);
}

template <class T>
void LList<T>::insertAfter(LListItr<T> itr, const T& item){
	if (itr.ptr->next == nullptr)
		return;
	numOfElements++;
	LListNode<T>* temp = new LListNode<T>(item);
	temp->next = itr.ptr->next;
	temp->prev = itr.ptr;
	itr.ptr->next = temp;
	temp->next->prev = temp;
	//itr.ptr->next = itr.ptr->next->prev = new LListNode<T>(item, itr.ptr, itr.ptr->next);

}
template <class T>
LList<T>::LList(){
	numOfElements = 0;
	head = new LListNode < T > ;
	head->next = tail = new LListNode<T>(T(), head);
	/*tail = new LListNode < T > ;
	head->next = tail;
	tail->prev = head;*/
}
template <class T>
LList<T>::~LList(){
	clear();
	delete head;
	delete tail;
}

template <class T>
LList<T>::LList(const LList<T>& rhs){
	numOfElements = 0;
	head = new LListNode < T > ;
	head->next = tail = new LListNode<T>(T(), head);
	*this = rhs;
}

template <class T>
LList<T>& LList<T>::operator=(const LList<T>& rhs){
	if (this == &rhs)
		return *this;
	clear();
	for (LListItr<T> i = rhs.head->next; i != rhs.tail; i++)
		push_back(*i);
	return *this;
}

int main(){
	LList<int> l;
	for (int i = 0; i < 20; i++)
		l.push_back(i);
	LList<int> l2(l);
	while (!l2.isEmpty())
		cout << l2.pop_front() << endl;
}