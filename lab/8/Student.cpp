#include <iostream>

#include "Student.h"
#include "Course.h"

using namespace std;

Student::Student(const string& name) : name(name) {}

int Student::getCourseIndexFromVector(const string& courseName) const {
	int courseIndex;

	for (int i = 0; i < courses.size(); i++) {
		if (courses[i] -> getName() == courseName) {
			courseIndex = i;
		}
	}

	return courseIndex;
}

string Student::getName() const {
	return name;
}

void Student::setName(const string& newName) {
	name = newName;
}

void Student::addCourse(Course* course) {
	courses.push_back(course);
}

vector<Course*> Student::getCourses() const {
	return courses;
}

void Student::display() const {
	cout << "STUDENT | Name: " << name << endl;
}
