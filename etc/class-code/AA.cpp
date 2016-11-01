#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int func1(vector<int>& v, int item){
	for (int i = 0; i < v.size(); i++)
		if (item == v[i]) //controlling line of code
			return i;
	return -1;
}

int func2(vector<int>& v, int item){
	int a = 0;
	int b = v.size() - 1;
	int c = (b + a) / 2;
	while (a <= b){
		if (item == v[c]) //controlling line of code
			return c;
		else if (item < v[c])
			b = c - 1;
		else
			a = c + 1;
		c = (b + a) / 2;
	}
	return -1;
}

void func3(vector<int>& v){
	for (int i = 0; i < v.size(); i++){
		int a = i;
		for (int j = i + 1; j < v.size(); j++)
			if (v[j] < v[a]) //controlling line of code
				a = j;
		int b = v[a];
		v[a] = v[i];
		v[i] = b;
	}
}

void func4(vector<int>& v){
	for (int i = 0; i < v.size(); i++)
		cout << v[i] << endl;
	int b = 0;
	for (int i = 1; i < v.size(); i++)
		if (v[i] < v[b])
			b = i;
	cout << v[b] << endl;
}

int func5(int n){
	int a = 0;
	while (n > 0){
		a += n % 10;
		n /= 10;
	}
	return a;
}

void func6(vector<int>& v){
	for (int i = 0; i < v.size(); i++)
		for (int j = 0; j < v.size(); j++)
			cout << v[i] << "," << v[j] << endl;
}

void func7(vector<int>& v){
	for (int i = 0; i < v.size(); i++)
		for (int j = 0; j < v.size(); j++)
			if (i == j)
				for (int k = 0; k < v.size(); k++)
					cout << v[i] << "," << v[j] << "," << v[k] << endl; //CLOC
}

void func8(vector<int>& v){
	for (int i = 0; i < v.size(); i += 2)
		cout << v[i] << endl;
}

class Point{
public:
	int x;
	int y;
	Point(int newx = 0, int newy = 0) :x(newx), y(newy){}
};

double distance(Point a, Point b){
	return sqrt(((a.x - b.x)*(a.x - b.x)) + ((a.y - b.y)*(a.y - b.y)));
}
double closestToOrigin(vector<Point>& vp){ //O(N)
	Point origin;
	double min = distance(vp[0], vp[1]);
	for (int i = 0; i < vp.size(); i++){
		double dist = distance(vp[i], origin);
		if (dist < min)
			min = dist;
	}
	return min;
}

double closestPairOfPoints(vector<Point>& vp){//O(N^2)
	double min = distance(vp[0], vp[1]);
	for (int i = 0; i < vp.size(); i++)
		for (int j = i + 1; j < vp.size(); j++){
			double dist = distance(vp[i], vp[j]);
			if (dist < min)
				min = dist;
		}
	return min;
}

bool colinearPoints(vector<Point>& vp){ //O(N^3)

}










