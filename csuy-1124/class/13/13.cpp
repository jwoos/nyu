#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class Person {
	// allows this method to access private attributes
	friend ostream& operator<<(ostream& output, const Person& person);
	friend bool operator==(const Person& personOne, const Person& personTwo);
	friend bool operator<(const Person& personOne, const Person& personTwo);
	public:
		Person(const string& name, int age) :name(name), age(age) {}

		void display() {
			cout << "Name: " << name << " Age: " << age << endl;
		}
		string getName() {
			return name;
		}

		int getAge() {
			return age;
		}

		operator bool() const {
			return name == "Elvis";
		}
	private:
		string name;
		int age;
};

ostream& operator<<(ostream& output, const Person& person) {
	output << "Name: " << person.name << " Age: " << person.age;
	return output;
}

bool operator==(const Person& personOne, const Person& personTwo) {
	//return &personOne == &personTwo;
	return personOne.name == personTwo.name;
}

bool operator<(const Person& personOne, const Person& personTwo) {
	//return &personOne == &personTwo;
	return personOne.name < personTwo.name;
}

bool operator<=(const Person& personOne, const Person& personTwo) {
	return personOne == personTwo || personOne < personTwo;
}

int main() {
	Person fred("Fred", 70);
	// what we want
	// cout << "The Person fred object: " << fred << endl;
	// what we have to use
	cout << "The Person fred object: ";
	fred.display();

	//operator<<(cout, fred);
	cout << fred << endl;

	Person george("George", 50);

	//operator==(fred, george);
	if (fred == george) {}
}
