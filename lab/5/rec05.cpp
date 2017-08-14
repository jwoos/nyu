/*
 *Name: Junwoo Shin
 *Course: CS-UY 11124
 *Section:
 *ID: N10644753
 */

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cstdlib>
using namespace std;

// forward declaration
class Student;
class LabWorker;
class Section;
class TimeSlot;

class Student {
	public:
		Student(string& name) :name(name), grades(10, -1) {}

		void addGrade(int grade, unsigned int week) {
			// to account for the fact that the index starts at 0
			int adjustedWeek = week;
			grades[adjustedWeek] = grade;
		}

		void display() const {
			cout << "Student: " << name << "; Grades: ";
			for (int grade : grades) {
				cout << grade << " ";
			}
			cout << endl;
		}

		string getName() const {
			return name;
		}

		vector<int> getGrades() const {
			return grades;
		}
	private:
		string name;
		vector<int> grades;
};

class TimeSlot {
	public:
		TimeSlot(string& day, unsigned int hour) :day(day), hour(hour) {}

		void display() const {
			if (hour > 12) {
				int normalized = hour - 12;
				cout << day << " " << normalized << "PM" << endl;
			} else {
				cout << day << " " << hour << "AM" << endl;
			}
		}
	private:
		string day;
		unsigned int hour;
};

class Section {
	public:
		Section(string name, string day, unsigned int hour) :name(name), sectionTime(day, hour), labWorker(nullptr) {}

		void addStudent(string& name) {
			Student* aStudent = new Student(name);
			students.push_back(aStudent);
		}

		void loadStudentsFromFile(const string& fileName) {
			ifstream studentFile(fileName);
			if (!studentFile) {
				cout << "Error!" << endl;
				exit(1);
			}

			string name;
			while (studentFile >> name) {
				addStudent(name);
			}
		}

		vector<Student*> getStudents() const {
			return students;
		}

		void display() {
			cout << "Section: " << name <<  "; ";
			sectionTime.display();
			for (Student*& studentPointer : students) {
				studentPointer -> display();
			}
			cout << endl;
		}

		void reset() {
			for (Student*& studentPointer : students) {
				delete studentPointer;
			}

			students.clear();
		}

		string getName() const {
			return name;
		}
	private:
		string name;
		TimeSlot sectionTime;
		LabWorker* labWorker;
		vector<Student*> students;
};

class LabWorker {
	public:
		LabWorker(string name) :name(name), section(nullptr) {}

		void addGrade(const string& student, int grade, unsigned int week) {
			vector<Student*> students = section -> getStudents();
			for (Student*& studentPointer : students) {
				if (studentPointer -> getName() == student) {
					studentPointer -> addGrade(grade, week);
				}
			}
		}

		void displayGrades() const {
			cout << name << " has ";
			section -> display();
		}

		void addSection(Section& aSection) {
			section = &aSection;
		}

		void displayAverageForWeek(unsigned int week) const {
			float total = 0;
			float count = 0;
			vector<Student*> students = section -> getStudents();
			for (Student* studentPointer : students) {
				count++;
				vector<int> grades = studentPointer -> getGrades();
				total += grades[week];
				cout << grades[week];
			}
			float average = total / count;
			cout << "Average for " << section -> getName() << " for week " << week << " is: " << average << endl;
			cout << endl;
		}
	private:
		string name;
		Section* section;
};

int main() {
   LabWorker moe("Moe");
   LabWorker jane("Jane");

   Section secA2("A2" , "Tuesday", 16);
   secA2.loadStudentsFromFile("A2.txt");
   /*
    *secA2.addStudent("John");
    *secA2.addStudent("George");
    *secA2.addStudent("Paul");
    *secA2.addStudent("Ringo");
	*/

   cout << "test A2" << endl;
   secA2.display();
   moe.addSection(secA2);
   moe.displayGrades();

   Section secB3("B3", "Thursday", 11);
   secB3.loadStudentsFromFile("B3.txt");
   /*
    *secB3.addStudent("Thorin");
    *secB3.addStudent("Dwalin");
    *secB3.addStudent("Balin");
    *secB3.addStudent("Kili");
    *secB3.addStudent("Fili");
    *secB3.addStudent("Dori");
    *secB3.addStudent("Nori");
    *secB3.addStudent("Ori");
    *secB3.addStudent("Oin");
    *secB3.addStudent("Gloin");
    *secB3.addStudent("Bifur");
    *secB3.addStudent("Bofur");
    *secB3.addStudent("Bombur");
	*/

   cout << "test B3" << endl;
   secB3.display();
   jane.addSection( secB3 );
   jane.displayGrades();

   cout << "Modeling week: 1" << endl;
   moe.addGrade("John", 7, 1);
   moe.addGrade("Paul", 9, 1);
   moe.addGrade("George", 7, 1);
   moe.addGrade("Ringo", 7, 1);
   cout << "End of week one" << endl;
   moe.displayGrades();
   moe.displayAverageForWeek(1);

   cout << "Modeling week: 2" << endl;
   moe.addGrade("John", 5, 2);
   moe.addGrade("Paul", 10, 2);
   moe.addGrade("Ringo", 0, 2);
   cout << "End of week two" << endl;
   moe.displayGrades();
   moe.displayAverageForWeek(2);

   cout << "testing reset()" << endl;
   secA2.reset();
   secA2.display();
   moe.displayGrades();
}
