#include "Registrar.h"
#include "Student.h"
#include "Course.h"

using namespace std;

namespace BrooklynPoly {
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

		if (studentIndex != -1) {
			students[studentIndex] -> setName(newName);
		}
	}

	void Registrar::dropStudentFromCourse(const string& studentName, const string& courseName) {
		int studentIndex = getStudentIndexFromVector(studentName);
		int courseIndex = getCourseIndexFromVector(courseName);

		if (studentIndex != -1 && courseIndex != -1) {
			students[studentIndex] -> removeCourse(courseName);
			courses[courseIndex] -> removeStudent(studentName);
		}
	}

	void Registrar::removeStudent(const string& name) {
		int studentIndex = getStudentIndexFromVector(name);

		if (studentIndex != -1) {
			vector<Course*> studentCourses = students[studentIndex] -> getCourses();

			for (int i = 0; i < studentCourses.size(); i++) {
				studentCourses[i] -> removeStudent(name);
			}

			students[studentIndex] -> clearCourse();
		}
	}

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

	ostream& operator<<(ostream& output, const Registrar& registrar) {
		output << "Courses" << endl;
		output << "------------------------------" << endl;

		for (int i = 0; i < registrar.courses.size(); i++) {
			output << registrar.courses[i] -> getName() << endl;
			output << "\tEnrolled Students:" << endl;
			vector<Student*> courseStudents = registrar.courses[i] -> getStudents();
			for (int j = 0; j < courseStudents.size(); j++) {
				output << "\t" << courseStudents[j] -> getName() << endl;
			}
		}

		output << endl;

		output << "Students" << endl;
		output << "------------------------------" << endl;

		for (int i = 0; i < registrar.students.size(); i++) {
			output << registrar.students[i] -> getName() << endl;
		}

		return output;
	}
}
