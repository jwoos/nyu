#include <iostream>

#include "Course.h"
#include "Student.h"

using namespace std;

Course::Course(const string& name) : name(name) {}

string Course::getName() const {
	return name;
}

int Course::getStudentIndexFromVector(const string& studentName) const {
	int studentIndex;

	for (int i = 0; i < students.size(); i++) {
		if (students[i] -> getName() == studentName) {
			studentIndex = i;
		}
	}

	return studentIndex;
}

void Course::addStudent(Student* student) {
	students.push_back(student);
}

void Course::removeStudent(const string& student) {
	int studentIndex = getStudentIndexFromVector(student);
}

vector<Student*> Course::getStudents() const {
	return students;
};

void Course::display() const {
	cout << "COURSE | Name: " << name << endl;
	for (int i = 0; i < students.size(); i++) {
		cout << "\t";
		students[i] -> display();
	}
}
