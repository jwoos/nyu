#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Parent {
	public:
    	virtual void display() const {
			cout << "Parent\n";
		}
	private:
};

class Child : public Parent {
	public:
    	void display() const {
			cout << "Child\n";
		}
	private:
};

class GrandChild : public Child {
	public:
    	void display() const {
			cout << "GrandChild\n";
		}
	private:
};

void func(Parent& base) {
    cout << "func(Parent)\n";
    base.display();
}

void func(Child& derived) {
    cout << "func(Child)\n";
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

    cout << "==============" << endl;
    otherFunc(par);
    otherFunc(child);
    otherFunc(gc);
}
