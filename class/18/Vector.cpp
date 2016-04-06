/*
  Vector Class
  Demonstrates:
     Good example of copy control
     Dynamic arrays and pointer arithmetic
     Square bracket operator
     Implementation of an important data structure
  Sec 
 */
#include <iostream>
using namespace std;

class Vector {
public:
    Vector() : theSize(0), theCapacity(0), data(nullptr) {}

    // Copy control
    ~Vector() { delete [] data; }  // destructor

    Vector(const Vector& rhs) {
        data = new int[rhs.theCapcity];
        theSize = rhs.theSize;
        theCapacity = rhs.theCapacity;
        for (size_t i = 0; i < theSize; ++i) {
            data[i] = rhs.data[i];
        }
    }

    Vector& operator=(const Vector& rhs) {
        if (this != &rhs) {
            delete [] data;

            data = new int[rhs.theCapcity];
            theSize = rhs.theSize;
            theCapacity = rhs.theCapacity;
            for (size_t i = 0; i < theSize; ++i) {
                data[i] = rhs.data[i];
            }
        }
        return *this;
    }

    void push_back(int val) {
        if (theCapacity == 0) {
            data = new int[1];
            theCapacity = 1;
        }
        if (theSize == theCapacity) {
            int* oldData = data;
            data = new int[2*theSize];
            for (size_t i = 0; i < theSize; ++i) {
                data[i] = oldData[i];
            }
            delete [] oldData;
            theCapacity *= 2;
        }
        data[theSize] = val;
        ++theSize;
    }

    size_t size() const { return theSize; }
    void clear() { theSize = 0; }
    void pop_back() { --theSize; }

    // Square brackets?
    int operator[](size_t index) const { return data[index]; }
    int& operator[](size_t index) { return data[index]; }
private:
    size_t theSize;
    size_t theCapacity;
    int* data;
};


int main() {

    Vector v;  // Not templated.  Our Vector class can only hold ints.
    // v.push_back(17);
    // v.push_back(42);
    // v.push_back(6);
    // v.push_back(28);

    // Vector v2(v);
    // Vector v3;
    // v3 = v;

    // for (size_t i = 0; i < v.size(); ++i)
    //     cout << v[i] << endl;
    // v[0] = 100;

}

