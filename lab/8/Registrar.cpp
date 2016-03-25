#include "Registrar.h"
#include "Student.h"
#include "Course.h"

using namespace std;

Registrar::Registrar() {}

void Registrar::addCourse(const string& course) {
	Course* aCourse = new Course(course);
	courses.push_back(aCourse);
}

void Registrar::cancelCourse(const string& course) {
	int courseIndex = getCourseIndexFromVector(course);

	delete courses[courseIndex];

	courses[courseIndex] = courses[courses.size() - 1];
	courses.pop_back();
}

void Registrar::addStudent(const string& name) {
	Student* aStudent = new Student(name);
	students.push_back(aStudent);
}

void Registrar::enrollStudentInCourse(const string& student, const string& course) {
	int studentIndex = getStudentIndexFromVector(student);
	int courseIndex = getCourseIndexFromVector(course);

	if ((studentIndex == -1) || (courseIndex == -1)) {
		return;
	}

	students[studentIndex] -> addCourse(courses[courseIndex]);
	courses[courseIndex] -> addStudent(students[studentIndex]);
}

void Registrar::printReport() const {
	for (int i = 0; i < courses.size(); i++) {
		courses[i] -> display();
	}
}

int Registrar::getCourseIndexFromVector(const string& courseName) {
	int courseIndex = -1;

	for (int i = 0; i < courses.size(); i++) {
		if (courses[i] -> getName() == courseName) {
			courseIndex = i;
		}
	}

	return courseIndex;
}

int Registrar::getStudentIndexFromVector(const string& studentName) {
	int studentIndex = -1;

	for (int i = 0; i < students.size(); i++) {
		if (students[i] -> getName() == studentName) {
			studentIndex = i;
		}
	}

	return studentIndex;
}

void Registrar::changeStudentName(const string& oldName, const string& newName) {
	int studentIndex = getStudentIndexFromVector(oldName);

	students[studentIndex] -> setName(newName);
}

/*
 *void Registrar::dropStudentFromCourse(const string& studentName, const string& courseName) {
 *    int studentIndex = getStudentIndexFromVector(studentName);
 *    int courseIndex = getCourseIndexFromVector(courseName);
 *}
 */

void Registrar::purge() {
	for (int i = 0; i < students.size(); i++) {
		delete students[i];
	}
	students.clear();

	for (int i = 0; i < courses.size(); i++) {
		delete courses[i];
	}
	courses.clear();
}

ostream& operator<<(ostream& output, vector<Course*> courses) {
	for (int i = 0; i < courses.size(); i++) {
		output << courses[i] -> getName() << endl;
	}

	return output;
}
