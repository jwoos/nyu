#include <iostream>
#include <vector>
#include <set>
#include <ctime>
#include <algorithm>
#include <functional>

using namespace std;

template <class T>
void selectionSort(vector<T>& v){
	for (int i = 0; i < v.size(); i++){
		int min = i;
		for (int j = i + 1; j < v.size(); j++)
			if (v[j] < v[min])
				min = j;
		T temp = v[min];
		v[min] = v[i];
		v[i] = temp;
	}
}

template <class T>
void insertionSort(vector<T>& v){
	for (int i = 1; i < v.size(); i++){
		T temp = v[i];
		int j = i;
		for (; j > 0 && temp < v[j - 1]; j--){
			v[j] = v[j - 1];
		}
		v[j] = temp;
	}
}

template <class T>
void insertionSort(vector<T>& v, int start, int end){
	for (int i = start; i <= end; i++){
		T temp = v[i];
		int j = i;
		for (; j > start && temp < v[j - 1]; j--){
			v[j] = v[j - 1];
		}
		v[j] = temp;
	}
}

template <class T>
void shellSort(vector<T>& v){
	for (int gap = v.size() / 2; gap > 0; gap /= 2){
		for (int i = gap; i < v.size(); i++){
			T temp = v[i];
			int j = i;
			for (; j >= gap&& temp < v[j - gap]; j -= gap)
				v[j] = v[j - gap];
			v[j] = temp;
		}
	}
}

template <class T>
void setSort(vector<T>& v){ //O(N log N)
	multiset<T> s;
	for (T i : v)
		s.insert(i); //O(log N)
	v.clear();
	while (!s.empty())
		v.push_back(s.pop());
}

class Timer{
	double start;
public:
	Timer(){ start = clock(); }
	void reset(){ start = clock(); }
	double elapsed()const { return (clock() - start) / CLOCKS_PER_SEC; }
};
template<class T>
void printArr(vector<T>& v){
	for (T i : v)
		cout << i << ",";
}
const int MIN_SIZE = 4;
template <class T>
void quicksort(vector<T>& v, int start, int end){
	if (start + MIN_SIZE > end)
		insertionSort(v, start, end);
	else{
		int middle = (start + end) / 2;
		if (v[middle] < v[start])
			swap(v[middle], v[start]);
		if (v[end] < v[start])
			swap(v[end], v[start]);
		if (v[end] < v[middle])
			swap(v[end], v[middle]);

		T pivot = v[middle];
		swap(v[middle], v[end - 1]); //move the pivot out of the way, for now
		int i = start;
		int j = end - 1;

		while (true){
			while (v[++i] < pivot){}
			while (pivot < v[--j]){}
			if (i < j)
				swap(v[i], v[j]);
			else
				break;
		}
		swap(v[i], v[end - 1]); //Restore the pivot to its final position!
		//cout << "QS:P=" << pivot << ";S=" << start << ";E="<<end<< " "; //DEBUG
		//printArr(v); //DEBUG
		//cout << endl; //debug
		quicksort(v, start, i - 1);
		quicksort(v, i + 1, end);
	}
}
template <class T>
void quicksort(vector<T>& v){
	quicksort(v, 0, v.size()-1);
}

template <class T>
void merge(vector<T>& v, vector<T>& temp, int leftstart, int leftend, int rightend){
	int rightstart = leftend + 1;
	int tempstart = leftstart;
	int temppos = leftstart;
	while (leftstart <= leftend && rightstart <= rightend){
		if (v[leftstart] < v[rightstart])
			temp[temppos++] = v[leftstart++];
		else
			temp[temppos++] = v[rightstart++];
	}
	while (leftstart <= leftend)
		temp[temppos++] = v[leftstart++];
	while (rightstart <= rightend)
		temp[temppos++] = v[rightstart++];

	for (; tempstart <= rightend; tempstart++)
		v[tempstart] = temp[tempstart];
}


template <class T>
void mergeSort(vector<T>& v, vector<T>& temp, int start, int end){
	if (start >= end)
		return;
	int mid = (start + end) / 2;
	mergeSort(v, temp, start, mid);
	mergeSort(v, temp, mid + 1, end);
	merge(v, temp, start, mid, end);
}

template <class T>
void mergeSort(vector<T>& v){//O(N log N)
	vector<T> temp;
	temp.resize(v.size());
	mergeSort(v, temp, 0, v.size() - 1);//call the real function
}
class Person{
public:
	string name;
	int age;
	double weight;
};

class lessThanOnName{
public:
	bool operator()(const Person& lhs, const Person& rhs)const {
		return lhs.name < rhs.name;
	}
};
template <class T, class Comparator>
void insertionSort(vector<T>& v, int start, int end, Comparator c){
	for (int i = start; i <= end; i++){
		T temp = v[i];
		int j = i;
		for (; j > start && c(temp, v[j - 1]); j--){
			v[j] = v[j - 1];
		}
		v[j] = temp;
	}
}
template <class T, class Comparator>
void quicksort(vector<T>& v, int start, int end, Comparator c){
	if (start + MIN_SIZE > end)
		insertionSort(v, start, end, c);
	else{
		int middle = (start + end) / 2;
		if (c(v[middle],v[start]))
			swap(v[middle], v[start]);
		if (c(v[end],v[start]))
			swap(v[end], v[start]);
		if (c(v[end],v[middle]))
			swap(v[end], v[middle]);

		T pivot = v[middle];
		swap(v[middle], v[end - 1]); //move the pivot out of the way, for now
		int i = start;
		int j = end - 1;

		while (true){
			while (c(v[++i],pivot)){}
			while (c(pivot,v[--j])){}
			if (i < j)
				swap(v[i], v[j]);
			else
				break;
		}
		swap(v[i], v[end - 1]); //Restore the pivot to its final position!
		//cout << "QS:P=" << pivot << ";S=" << start << ";E="<<end<< " "; //DEBUG
		//printArr(v); //DEBUG
		//cout << endl; //debug
		quicksort(v, start, i - 1);
		quicksort(v, i + 1, end);
	}
}
template <class T,class Comparator>
void quicksort(vector<T>& v,Comparator c){
	quicksort(v, 0, v.size() - 1,c);
}

int main(){
	srand(time(NULL));
	vector<int> v;

	/*for (int i = 0; i < 20; i++)
		v.push_back(rand() % 100);
	quicksort(v,0,19);
	cout << "QS: AFTER :     ";
	printArr(v);
	cout << endl;*/
	
	double elapsed;
	Timer t;
	for (int i = 0; i < 10; i++){
		v.clear();
		for (int j = 0; j < (i+1)*1000000; j++)
			v.push_back(rand());
		t.reset();
		quicksort(v);
		elapsed = t.elapsed();
		cout << "V.size=" << v.size() << " sorting took " << elapsed << "seconds" << endl;

	}
	
}