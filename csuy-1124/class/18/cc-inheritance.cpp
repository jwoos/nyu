/*
    Copy Control with Inheritance
    Sec 
*/

#include <iostream>
using namespace std;

class Base {
public:
    Base() {
        cerr << "Base()\n";
    }
    explicit Base(const Base& rhs) {
        cerr << "Base(const Base&)\n";
    }
    virtual ~Base() {
        cerr << "~Base()\n";
    }
    Base& operator=(const Base& rhs) {
        cerr << "Base::operator=(const Base&)\n";
        return *this;
    }
};

class Member {
public:
    Member() {
        cerr << "Member()\n";
    }
    explicit Member(const Member& rhs) {
        cerr << "Member(const Member&)\n";
    }
    virtual ~Member() {
        cerr << "~Member()\n";
    }
    Member& operator=(const Member& rhs) {
        cerr << "Member::operator=(const Member&)\n";
        return *this;
    }
};

class Derived : public Base {
public:
    Derived() {
        cerr << "Derived()\n";
    }

    Derived(const Derived& rhs) : Base(rhs), mem(rhs.mem) {
        cerr << "Derived(const Derived&)\n";
    }

    Derived& operator=(const Derived& rhs) {

        //        *this Base::= rhs; // Not valid C++
        //        (*this).Base::operator=(rhs);  // Terribly ugly
        //this->Base::operator=(rhs);  // Not terribly ugly
        Base::operator=(rhs);  // Nice and simple (nice and short)

        mem = rhs.mem;

        cerr << "Derived::operator=(const Derived&)\n";
        return *this;
    }

    ~Derived() {
        cerr << "~Derived()\n";
    }
private:
    Member mem;
};

int main() {
    cerr << "Derived der;\n"
         << "------------\n";
    Derived der;
    cout << "===\n";
    cerr << "Derived der2(der);\n"
         << "------------------\n";
    Derived der2(der);
    cout << "===\n";
    cerr << "Derived der3 = der;\n"
         << "-------------------\n";
    Derived der3 = der;
    cout << "===\n";
    cerr << "der = der2;\n"
         << "-----------\n";
    der = der2;
    cout << "===\n";
    cerr << "Derived* p = new Derived();\n"
         << "delete p;\n"
         << "---------------------------\n";
    Derived* p = new Derived();
    delete p;
    cout << "===\n";
    cerr << "Base* pBase = new Derived();\n"
         << "delete pBase;\n"
         << "---------------------------\n";
    Base* pBase = new Derived();
    delete pBase;
    cout << "===\n";
}
