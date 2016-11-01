#include <iostream>
#include <ctime>
#include <vector>
#include <string>
#include <algorithm> //for sort
#include <list>
#include <set>
#include <map>


using namespace std;

class Timer{
	double start;
public:
	Timer(){ start = clock(); }
	double elapsed()const{ return (clock() - start) / CLOCKS_PER_SEC; }
	void reset(){ start = clock(); }
};
template <class T>
void printList(const list<T>& l){
	for (list<T>::const_iterator i = l.begin(); i != l.end(); i++){
		cout << *i << endl;
	}
}

int main(){
	srand(time(NULL));

	map<string, int> m;
	m.insert(pair<string, int>("Daniel", 100));
	m.insert(pair<string, int>("Al", 99));
	m.insert(pair<string, int>("Joe", 20));
	m["Steve"] = 80;

	if (m.find("Billy") != m.end())
		cout << m["Billy"] << endl;

	for (map<string, int>::iterator i = m.begin(); i != m.end(); i++)
		cout << "First=" << i->first << " Second=" << i->second << endl;
	cout << "Second="<<m["Daniel"] << endl;

/*	multiset<int> s;
	for (int i = 0; i < 100; i++)
		s.insert(rand() % 1000);
	for (multiset<int>::iterator i = s.begin(); i != s.end(); i++)
		cout << *i << endl;

	cout << "Size=" << s.size() << endl;
	*/
/*	Timer t;
	double previousTime = 0;
	double elapsed = 0;
	for (unsigned int i = 0; i < 1000000000; i++){
		t.reset();
		s.insert(i);
		elapsed = t.elapsed();
		if (previousTime < elapsed){
			cout << "size=" << s.size()
				<< " Current time: "
				<< elapsed << endl;
			previousTime = elapsed;
		}
	}
	*/

//	for (int i : s)
//		cout << i << endl;

	/*
	list<int> l;
	for (int i = 0; i < 100; i++){
		l.push_front(i);
		//cout << "Size=" << l.size() << " capacity=" << l.size() << endl;
	}

	printList(l);

	pair<string, int> p1("Daniel",100);
	p1.first = "Daniel";
	p1.second = 100;
	pair<pair<string, int>, pair<float, char>> p2;
	p2.first.first = "Patrick";
	p2.first.second = 99;
	p2.second.first = 2.5;
	p2.second.second = 'A';
	*/

/*	vector<int> v;
	double elapsed=0;
	double previousTime = 0;
	Timer t;
	for (unsigned int i = 0; i < 1000000000; i++){
		t.reset();
		v.push_back(i);
		elapsed = t.elapsed();
		if (previousTime < elapsed){
			cout << "size=" << v.size() << " Capacity=" << v.capacity()
				<<" Current time: "
				<<elapsed<< endl;
			previousTime = elapsed;
		}
		//v.push_back(rand() % 1000);
		//cout << "size=" << v.size() << "\tCapacity=" << v.capacity() << endl;
	}
	sort(v.begin(), v.end());


	for (int i : v)
		cout << i << endl;
*/
}