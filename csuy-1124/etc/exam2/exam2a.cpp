#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Cookie {
    friend ostream& operator<<(ostream& os, const Cookie& rhs);
    
    public:
        Cookie(int size, const string& name) : size(size), name(name) {}
        
        Cookie& operator+=(const Cookie& rhs) {
            size += rhs.size;
            name += ' ' + rhs.name;
            return *this;
        }
    private:
        int size;
        string name;
};

ostream& operator<<(ostream& os, const Cookie& rhs) {
    os << "Name: " << rhs.name << " Size: " << rhs.size;
    return os;
}

int main() {
    /* 
     * unary operator -> member
     * binary operator (leaves them unchanged) -> non-member
     * binary (changes one) -> member
     * The binary arithmetic operators (+ - * / %) don't need to be friends as 
     * they are normally implemented using the corresponding compound operator 
     * (+= -= *= /= %=).
     */
     Cookie aCookie(10, "Delight");
     cout << aCookie << endl;
     
     Cookie anotherCookie(20, "Turkish");
     anotherCookie += aCookie;
     
     cout << anotherCookie << endl;
}