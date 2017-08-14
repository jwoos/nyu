#include <iostream>
#include <vector>
#include <ctime>

using namespace std;

template <class T>
class PQueue{
	vector<T> data;
	void percolateUp(int pos); //used for push
	void percolateDown(int pos); //used for pop
	void swap(int posA, int posB);
public:
	PQueue(){ clear(); }
	void clear(){ data.resize(1); }
	T top() const { return data[1]; }
	T pop();
	void push(T newval);
	bool isEmpty() const{ return data.size() == 1; }
	void printTree()const{
		for (int i : data)
			cout << i << ",";
		cout << endl;
	}
};

template <class T>
void PQueue<T>::swap(int posA, int posB){
	T temp = data[posA];
	data[posA] = data[posB];
	data[posB] = temp;
}

template <class T>
void PQueue<T>::push(T newVal){
	data.push_back(newVal);
	percolateUp(data.size() - 1);
}

template <class T>
void PQueue<T>::percolateUp(int pos){
	if (pos == 1)
		return;
	if (data[pos] < data[pos / 2]){
		swap(pos, pos / 2);
		percolateUp(pos / 2);
	}
}

template <class T>
T PQueue<T>::pop(){
	T retval = top();
	if (!isEmpty()){
		data[1] = data[data.size() - 1];
		data.pop_back();
		percolateDown(1);
	}
	return retval;
}

template <class T>
void PQueue<T>::percolateDown(int pos){
	if (pos == data.size())//nothing left on this tree
		return;
	if ((pos * 2) >= data.size())//This node has no children
		return;
	if ((pos * 2) == (data.size() - 1)){
		if (data[pos] >= data[pos * 2])
			swap(pos, pos * 2);
		return;
	}
	//the node has two children
	if (data[pos * 2] < data[pos] || data[pos * 2 + 1] < data[pos]){ //we have to swap
		if (data[pos * 2] <= data[pos * 2 + 1]){
			swap(pos, pos * 2);
			percolateDown(pos * 2);
		}
		else{
			swap(pos, pos * 2 + 1);
			percolateDown(pos * 2 + 1);
		}
	}
}

int main(){
	PQueue<int> pq;
	srand(time(NULL));
	for (int i = 0; i < 10; i++)
		pq.push(rand() % 100);
	pq.printTree();
	while (!pq.isEmpty()){
		cout << pq.pop() << endl;
		pq.printTree();
	}
}