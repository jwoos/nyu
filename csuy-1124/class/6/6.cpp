#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>

using namespace std;

class Date {
    public:
        Date(int month, int day, int year) :month(month), day(day), year(year) {}

        void display() const {
            cout << month << '/' << day << '/' << year << endl;
        }
    private:
        int month, day, year;
};

class Person {
    public:
        Person(const string& theName) :name(theName) {}
    private:
		string name;
};

int main() {
    Date date(10, 1, 1997);
}
