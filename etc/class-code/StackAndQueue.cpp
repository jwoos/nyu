#include <iostream>
#include <list>
#include <fstream>

using namespace std;

template <class T>
class Queue{
	T* data;
	int start;
	int end;
	int capacity;
	void resize(int newsize);
public:
	Queue() :data(nullptr){ clear(); }
	~Queue(){ delete[] data; }
	Queue(const Queue<T>& rhs) :data(nullptr){ *this = rhs; }
	T top() const { return data[start]; }
	bool isEmpty() const{ return start == end; }
	T pop();
	int size()const;
	void clear();
	void push(const T& item);

	Queue<T>& operator=(const Queue<T>& rhs);
};
template <class T>
Queue<T>& Queue<T>::operator=(const Queue<T>& rhs){
	if (this == &rhs)
		return *this;
	int otherSize = rhs.size() + 1;
	delete[] data;
	data = new T[otherSize];
	capacity = otherSize;
	int otherptr = rhs.start;
	do{
		push(rhs.data[otherptr++]);
		if (otherptr == rhs.capacity)
			otherptr = 0;
	} while (otherptr != rhs.end);
}
template <class T>
void Queue<T>::resize(int newsize){
	T* temp = new T[newsize];
	int tempptr = 0;
	int dataptr = start;
	do{
		temp[tempptr++] = data[dataptr++];
		if (dataptr == capacity)
			dataptr = 0;
	} while (dataptr != end);
	start = 0;
	end = tempptr;
	capacity = newsize;
	delete[] data;
	data=temp;
}
template <class T>
void Queue<T>::push(const T& item){
	data[end++] = item;
	if (end == capacity)
		end = 0;
	if (end == start)
		resize(capacity * 2);
}

template <class T>
void Queue<T>::clear(){
	delete[] data;
	capacity = 5;
	data = new T[capacity];
	start=0;
	end=0;
}
template <class T>
int Queue<T>::size()const{
	if (start <= end)
		return end - start;
	return (capacity - start) + (end);
}

template <class T>
T Queue<T>::pop(){
	T temp = top();
	if (isEmpty())
		return temp;
	start++;
	if (start == capacity)
		start = 0;
	return temp;
}

/*template <class T>
class Queue{
	list<T> data;
public:
	void push(const T& item){ data.push_back(item); }
	T pop();
	T top() const{ return *data.begin(); }
	bool isEmpty()const { return data.size() == 0; }
	int size() const{ return data.size(); }
	void clear(){ data.clear(); }
};
template <class T>
T Queue<T>::pop(){
	T temp = top();
	data.pop_front();
	return temp;
}*/
template <class T>
class Stack{
	list<T> data;
public:
	void push(const T& item) { data.push_front(item); }
	T pop();
	T top() const{ return *data.begin(); }
	bool isEmpty()const { return data.size() == 0; }
	int size() const{ return data.size(); }
	void clear(){ data.clear(); }
};

template <class T>
T Stack<T>::pop(){
	T retval = top();
	data.pop_front();
	return retval;
}

int main(){
	Queue<char> q;
	for (int i = 0; i < 26; i++)
		q.push('A' + i);
	for (int i = 0; i < q.size() / 2; i++)
		q.pop();
	for (int i = 0; i < 26; i++)
		q.push('A' + i);
	Queue<char> q2(q);
	while (!q2.isEmpty())
		cout << q2.pop() << endl;
	/*Stack<char> s;
	for (int i = 0; i < 10; i++)
		s.push('A' + i);

	while (!s.isEmpty())
		cout << s.pop() << endl;*/
	/*
	Stack<char> items;
	ifstream inFile("StackAndQueue.cpp");
	char temp;
	while (inFile >> temp){
		if (temp == '{' || temp == '(' || temp == '['){
			items.push(temp);
		}
		else if (temp == '\''){ //skip the character
			inFile >> temp;
			if (temp == '\\')
				inFile >> temp >> temp;
			else
				inFile >> temp;
		}
		else if (temp == '\"'){
			do{
				inFile >> temp;
				if (temp == '\\'){
					inFile >> temp;
					if (temp == '\"')
						inFile >> temp;
				}
			} while (temp != '\"');
		}
		else if (temp == '\\'){
			inFile >> temp;
		}
		else if (temp == '}'){
			if (items.top() == '{'){
				cout << "Matched {}" << endl;
				items.pop();
			}
			else{
				cout << "SYNTAX ERROR, mismatched {}" << endl;
				return 0;
			}
		}
		else if (temp == ')'){
			if (items.top() == '('){
				cout << "Matched ()" << endl;
				items.pop();
			}
			else{
				cout << "SYNTAX ERROR, mismatched ()" << endl;
				return 0;
			}
		}

		else if (temp == ']'){
			if (items.top() == '['){
				cout << "Matched []" << endl;
				items.pop();
			}
			else{
				cout << "SYNTAX ERROR, mismatched []" << endl;
				return 0;
			}
		}
	}
	if (items.isEmpty()){
		cout << "Parsing complete." << endl;
	}
	else
		cout << "PARSING ERROR, mismatched " << items.top() << " at end of file!" << endl;
*/
}