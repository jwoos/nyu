#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstdlib>

using namespace std;

class Polygon {
	public:
		Polygon(int sides) :sides(sides) {}

		virtual void display() const = 0;

		// pure virtual method
		// causes the class to be abstract and thus impossible to instantiate by itself
		virtual int getArea() const = 0;
	private:
		int sides;
};

class Triangle : public Polygon {
	public:
		Triangle(int sides) :Polygon(sides) {}

		void display() const {
			cout << "Triangle" << endl;
		}

		int getArea() const {
			return 0;
		}
	private:
};

class Rectangle : public Polygon {
	public:
	private:
};

int main() {
	// for loop
	/*
	 *for (int i = 0; i < 10; i++) {
	 *	  cout << i << endl;
	 *}
	 */

	//Polygon aPolygon(5);
	Triangle aTriangle(3);

	//aPolygon.display();
	aTriangle.display();

	// slicing problem
	// the child class is stripped, leaving only the parent
	//Polygon bPolygon = aTriangle;
	//bPolygon.display();

	/*
	 * Compilation error; can't set a base class variable to a child class instance
	 *
	 * Triangle bTriangle = aPolygon;
	 * bTriangle.display();
	 *
	 */

	// this allows the child class to use the parent's methods if the virtual is set
	//Polygon* aPolygonPointer = &aTriangle;
	//aPolygonPointer -> display();

	vector<string*> stringVector;

	// this results in the same address being pushed back
	for (int i = 0; i < 10; i++) {
		string aString("hello");
		stringVector.push_back(&aString);
	}

	for (string* stringPointer : stringVector) {
		cout << stringPointer << endl;
	}

	vector<string*> anotherStringVector;

	// this creates it on the heap
	for (int i = 0; i < 10; i++) {
		string* aString = new string("hello" + to_string(i));
		anotherStringVector.push_back(aString);
	}

	for (string* stringPointer : anotherStringVector) {
		cout << stringPointer << endl;
		cout << *stringPointer << endl;
		// remember to delete the value!
		delete stringPointer;
		stringPointer = nullptr;
	}

	anotherStringVector.clear();
	cout << anotherStringVector.size() << endl;
}
