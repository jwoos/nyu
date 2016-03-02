#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <vector>

using namespace std;

class Parent {
	public:
		virtual void display() const {
			cout << "Parent" << endl;
		}
};

class Child : public Parent {
	public:
		void display() const {
			cout << "Child" << endl;
		}
};

class GrandChild : public Child {
	public:
		void display() const {
			cout << "GrandChild" << endl;
		}
};

void func(Parent& base) {
	cout << "func(Parent)" << endl;
	base.display();
}

void func(Child& derived) {
	cout << "func(Child)" << endl;
	derived.display();
}

void otherFunc(Parent& base) {
	func(base);
}

int main() {
	Child child;
	Parent par;
	GrandChild gc;

	func(par);
	func(child);
	func(gc);

	cout << "=====================" << endl;

	otherFunc(par);
	otherFunc(child);
	otherFunc(gc);
}
