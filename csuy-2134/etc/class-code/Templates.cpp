#include <iostream>
#include <ctime>
#include <string>
#include <cmath>

using namespace std;

template <class T>
class SortedArray{
	T* data;
	int capacity;
	int numOfElements;
public:
	SortedArray() :capacity(5), numOfElements(0){ data = new T[capacity]; }
	SortedArray(const SortedArray<T>& rhs) :capacity(5), numOfElements(0),
		data(nullptr){ *this = rhs; }
	virtual ~SortedArray(){ delete[] data; }
	SortedArray<T>& operator=(const SortedArray<T>& rhs);
	T& operator[](int index){ return data[index]; }
	T operator[](int index)const{ return data[index]; }
	void push(const T& newdata);
	void resize(int newsize);
	int find(const T& toFind)const;
	void pop(const T& toRemove);
	int size()const{ return numOfElements; }
};
template <class T>
void SortedArray<T>::pop(const T& toRemove){
	int index = find(toRemove);
	if (index != -1){
		for (int i = index; i < numOfElements - 1; i++)
			data[i] = data[i + 1];
		numOfElements--;
	}

}
template <class T>
int SortedArray<T>::find(const T& toFind) const{
	int start = 0;
	int end = numOfElements-1;
	int middle = (start + end) / 2;
	while (start <= end && data[middle] != toFind){
		if (data[middle] < toFind)
			start = middle + 1;
		else
			end = middle - 1;
		middle = (start + end) / 2;
	}
	if (data[middle] == toFind)
		return middle;
	return -1;
}
template <class T>
void SortedArray<T>::resize(int newsize){
	T* temp = new T[newsize];
	if (newsize < numOfElements)
		numOfElements = newsize;
	for (int i = 0; i < numOfElements; i++)
		temp[i] = data[i];
	delete[] data;
	data = temp;
	capacity = newsize;
}
template <class T>
void SortedArray<T>::push(const T& newdata){
	if (numOfElements == capacity)
		resize(numOfElements * 2);
	int i = numOfElements;
	for (; i>0 && data[i - 1] > newdata; i--)
		data[i] = data[i - 1];
	data[i] = newdata;
	numOfElements++;
}

template <class T>
SortedArray<T>& SortedArray<T>::operator=(const SortedArray<T>& rhs){
	if (this == &rhs)
		return *this;
	delete[] data;
	capacity = rhs.numOfElements;
	numOfElements = rhs.numOfElements;
	data = new T[capacity];
	for (int i = 0; i < numOfElements; i++)
		data[i] = rhs.data[i];
	return *this;
}

class Elephant{};
ostream& operator<<(ostream& outs, const Elephant& rhs){
	outs << "ELEPHANT!";
	return outs;
}

template <class T> //template <typename T>
void mySwap(T& a, T& b){
	T temp = a;
	a = b;
	b = temp;
}
template <class T>
void printArr(T* arr, int size){
	for (int i = 0; i < size; i++)
		cout << "arr["<<i<<"]="<<arr[i] << endl;
}

template <class T>
void mySort(T* arr, int size){
	for (int i = 0; i < size; i++){
		int minIndex = findIndexOfMin(arr, size, i);
		mySwap(arr[i], arr[minIndex ]);
	}
}

template <class T>
int findIndexOfMin(T* arr, int size, int start=0){
	int minIndex = start;
	for (int i = start + 1; i < size; i++)
		if (arr[i] < arr[minIndex])
			minIndex = i;
	return minIndex;
}

int main(){
	int x(100), y(50);
	cout << "X=" << x << "\tY=" << y << endl;
	cout << "swapping" << endl;
	mySwap(x, y);
	cout << "X=" << x << "\tY=" << y << endl;

	int size = 26;
	char * arr = new char[size];
	for (int i = 0; i < size; i++)
		arr[i] = 'A' +i;
	printArr(arr, size);

	int stringSize = 5;
	string* sarr = new string[stringSize];
	sarr[0] = "Daniel";
	sarr[1] = "John";
	sarr[2] = "James";
	sarr[3] = "Gloria";
	sarr[4] = "Betty";

	mySort(sarr, stringSize);
	srand(time(NULL));
	int* iarr = new int[size];
	for (int i = 0; i < size; i++)
		iarr[i] = rand() % 1000;
	mySort(iarr, size);
	//printArr(iarr, size);

	SortedArray<int> s;
	for (int i = 0; i < 20; i++)
		s.push(rand() % 1000);
	for (int i = 0; i < s.size(); i++)
		cout << "s[" << i << "]=" << s[i] << endl;
}

/*void mySwap(int& a, int& b){
	int temp = a;
	a = b;
	b = temp;
}

void mySwap(char& a, char& b){
	char temp = a;
	a = b;
	b = temp;
}

void mySwap(Elephant& a, Elephant& b){
	Elephant temp = a;
	a = b;
	b = temp;
}*/