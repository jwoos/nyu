#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

// abstract class
class Shape {
	public:
		Shape(int x, int y) : x(x), y(y) {}

		void move(int x, int y) {
			this -> x = x;
			this -> y = y;
		}

		/*
		 *virtual void draw() {
		 *    cout << "Default stuff..." << endl;
		 *}
		 */

		// pure virtual method aka abstract method
		virtual void draw() const = 0;

		//void commonDrawingCode() const {}
	private:
		int x;
		int y;
};

// allows defining a function outside of the class and the method
void Shape::draw() const {
	// useful common code
}

class Triangle : public Shape {
	public:
		Triangle(int x, int y) : Shape(x, y) {}

		virtual void draw() const {
			//commonDrawingCode();
			Shape::draw();
			// stuff to print a triangle
		}
};

class Circle : public Shape {
	public:
		Circle(int x, int y) : Shape(x, y) {}

		virtual void draw() const {
			// stuff to print a circle
			//commonDrawingCode();
			Shape::draw();
		}
};

int main() {
	Triangle aTriangle(10, 10);
	aTriangle.draw();
	Circle aCircle(10, 10);
	aCircle.draw();
}
