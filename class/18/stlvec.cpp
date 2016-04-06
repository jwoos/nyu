#include <vector>
#include <iostream>
using namespace std;

int main() {

    vector<int> v;
    cout << "Initial vector:\n";
    cout << "Size: " << v.size() << ", Capacity: " << v.capacity() << endl;
    cout << "Vector after each push_back from 0 to 9:\n";
    for (int i = 0; i < 10; ++i) {
        v.push_back(i);
        cout << "Size: " << v.size() << ", Capacity: " << v.capacity() << endl;
    }
    v.clear();
    cout << "Vector after clear:\n";
    cout << "Size: " << v.size() << ", Capacity: " << v.capacity() << endl;
}

