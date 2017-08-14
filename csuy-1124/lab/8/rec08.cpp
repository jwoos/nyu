/*
 *
 * Junwoo Shin
 * Rec 08
 *
 */

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>

#include "Registrar.h"

using namespace std;
using namespace BrooklynPoly;

vector<string> split(const string& line);

int main() {
/*
 *    Registrar registrar;
 *
 *    cout << "No courses or students added yet" << endl;
 *    cout << registrar << endl;
 *    //registrar.printReport();
 *
 *    cout << "AddCourse CS101.001" << endl;
 *    registrar.addCourse("CS101.001");
 *    cout << registrar << endl;
 *    //registrar.printReport();
 *
 *    cout << "AddStudent FritzTheCat" << endl;
 *    registrar.addStudent("FritzTheCat");
 *    cout << registrar << endl;
 *    //registrar.printReport();
 *
 *    cout << "AddCourse CS102.001" << endl;
 *    registrar.addCourse("CS102.001");
 *    cout << registrar << endl;
 *    //registrar.printReport();
 *
 *    cout << "EnrollStudentInCourse FritzTheCat CS102.001" << endl;
 *    registrar.enrollStudentInCourse("FritzTheCat", "CS102.001");
 *    cout << "EnrollStudentInCourse FritzTheCat CS101.001" << endl;
 *    registrar.enrollStudentInCourse("FritzTheCat", "CS101.001");
 *    cout << registrar << endl;
 *    //registrar.printReport();
 *
 *    cout << "EnrollStudentInCourse Bullwinkle CS101.001" << endl;
 *    cout <<  "Should fail, i.e. do nothing, since Bullwinkle is not a student." << endl;
 *    registrar.enrollStudentInCourse("Bullwinkle", "CS101.001");
 *    cout << registrar << endl;
 *    //registrar.printReport();
 *
 *    cout << "CancelCourse CS102.001" << endl;
 *    registrar.cancelCourse("CS102.001");
 *    cout << registrar << endl;
 *    //registrar.printReport();
 *
 *    // [OPTIONAL - do later if time]
 *    cout << "ChangeStudentName FritzTheCat MightyMouse" << endl;
 *    registrar.changeStudentName("FritzTheCat", "MightyMouse");
 *    cout << registrar << endl;
 *    //registrar.printReport();
 *
 *    cout << "DropStudentFromCourse MightyMouse CS101.001" << endl;
 *    registrar.dropStudentFromCourse("MightyMouse", "CS101.001");
 *    cout << registrar << endl;
 *    //registrar.printReport();
 *
 *    cout << "RemoveStudent FritzTheCat" << endl;
 *    registrar.removeStudent("FritzTheCat");
 *    cout << registrar << endl;
 *    //registrar.printReport();
 *
 *    cout << "Purge for start of next semester" << endl;
 *    registrar.purge();
 *    cout << registrar << endl;
 *    //registrar.printReport();
 */

	Registrar registrar;

	ifstream inputFile("lab/8/transactions.txt");
	if (!inputFile) {
		cout << "Error with file" << endl;
		exit(1);
	}

	string line;
	while (getline(inputFile, line)) {
		vector<string> lineWords = split(line);
		string command = lineWords[0];
		cout << command << endl;
		if (command == "PrintReport") {
			cout << registrar << endl;
		} else if (command == "AddCourse") {
			if (lineWords.size() != 2) {
				cout << "Can't add course" << endl;
				cout << "Invalid number of arguments" << endl;
			} else {
				registrar.addCourse(lineWords[1]);
			}
		} else if (command == "AddStudent") {
			if (lineWords.size() != 2) {
				cout << "Can't add student" << endl;
				cout << "Invalid number of arguments" << endl;
			} else {
				registrar.addStudent(lineWords[1]);
			}
		} else if (command == "EnrollStudentInCourse") {
			if (lineWords.size() != 3) {
				cout << "Can't enroll student in course" << endl;
				cout << "Invalid number of arguments" << endl;
			} else {
				if (registrar.getCourseIndexFromVector(lineWords[2]) == -1) {
					cout << "Invalid course" << endl;
				} else if (registrar.getStudentIndexFromVector(lineWords[1]) == -1) {
					cout << "Invalid student" << endl;
				} else {
					registrar.enrollStudentInCourse(lineWords[1], lineWords[2]);
				}
			}
		} else if (command == "ChangeStudentName") {
			if (lineWords.size() != 3) {
				cout << "Can't change student name" << endl;
				cout << "Invalid number of arguments" << endl;
			} else {
				if (registrar.getStudentIndexFromVector(lineWords[1]) == -1) {
					cout << "Invalid student" << endl;
				} else {
					registrar.changeStudentName(lineWords[1], lineWords[2]);
				}
			}
		} else if (command == "CancelCourse") {
			if (lineWords.size() != 2) {
				cout << "Can't remove course" << endl;
				cout << "Invalid number of arguments" << endl;
			} else {
				if (registrar.getCourseIndexFromVector(lineWords[1]) == -1) {
					cout << "Invalid course" << endl;
				} else {
					registrar.cancelCourse(lineWords[1]);
				}
			}
		} else if (command == "DropStudentFromCourse") {
			if (lineWords.size() != 3) {
				cout << "Can't drop student from course" << endl;
				cout << "Invalid number of arguments" << endl;
			} else {
				if (registrar.getCourseIndexFromVector(lineWords[2]) == -1) {
					cout << "Invalid course" << endl;
				} else if (registrar.getStudentIndexFromVector(lineWords[1]) == -1) {
					cout << "Invalid student" << endl;
				} else {
					registrar.dropStudentFromCourse(lineWords[1], lineWords[2]);
				}
			}
		} else if (command == "RemoveStudent") {
			if (lineWords.size() != 2) {
				cout << "Can't remove student" << endl;
				cout << "Invalid number of arguments" << endl;
			} else {
				if (registrar.getStudentIndexFromVector(lineWords[1]) == -1) {
					cout << "Invalid student" << endl;
				} else {
					registrar.removeStudent(lineWords[1]);
				}
			}
		} else if (command == "Purge") {
			registrar.purge();
		}
		cout << "----------------------------------------------------------------------------" << endl;
	}
}

vector<string> split(const string& line) {
	vector<string> lineSplit;
	string temp = "";
	for (int i = 0; i <= line.size(); i++) {
		if (isspace(line[i]) || i == line.length()) {
			lineSplit.push_back(temp);
			temp = "";
		} else {
			temp += line[i];
		}
	}

	return lineSplit;
}
