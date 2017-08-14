#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <vector>

using namespace std;

// struct defaults to public
/*
 *struct Person {
 *     // Constructor
 *     // No return type!!!
 *     // initializes name with theName rather than initializing it as empty and setting it
 *     Person(const string& theName) :name(theName) {
 *     }
 *     // shows that it doesn't modify
 *     // needs const flag
 *     void display() const {
 *         cout << "Person: " << name << endl;
 *     };
 *
 *     // this doesn't work
 *     void setName(const string& theName) {
 *         name = theName;
 *     };
 *
 *     // private
 *     // everything below this is private until change back to public
 *     private:
 *         string name;
 * };
 */

// class defaults to private
class Person {
	string name;

	// everything below this is public
	public:
		// default constructor
		Person() {}; // same as Person() :name("") {}

		// Constructor
		// No return type!!!
		// initializes name with theName rather than initializing it as empty and setting it
		Person(const string& theName) :name(theName) {
		}
		// shows that it doesn't modify
		// needs const flag
		void display() const {
			cout << "Person: " << name << endl;
		};

		// this doesn't work
		void setName(const string& theName) {
			name = theName;
		};
};

void displayPerson(const Person& aPerson) {
	// CONSTANT, need to guarantee that it won't change
	aPerson.display();
};

int main() {
	/* Person john; */
	Person john("john");
	/* john.setName("john"); */
	displayPerson(john);
};
