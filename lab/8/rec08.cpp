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

int main() {
	Registrar registrar;

    cout << "No courses or students added yet" << endl;
    //cout << registrar << endl;  // or registrar.printReport()
	registrar.printReport();

    cout << "AddCourse CS101.001" << endl;
    registrar.addCourse("CS101.001");
    //cout << registrar << endl;  // or registrar.printReport()
	registrar.printReport();

    cout << "AddStudent FritzTheCat" << endl;
    registrar.addStudent("FritzTheCat");
    //cout << registrar << endl;  // or registrar.printReport()
	registrar.printReport();

    cout << "AddCourse CS102.001" << endl;
    registrar.addCourse("CS102.001");
    //cout << registrar << endl;  // or registrar.printReport()
	registrar.printReport();

    cout << "EnrollStudentInCourse FritzTheCat CS102.001" << endl;
    registrar.enrollStudentInCourse("FritzTheCat", "CS102.001");
    cout << "EnrollStudentInCourse FritzTheCat CS101.001" << endl;
    registrar.enrollStudentInCourse("FritzTheCat", "CS101.001");
    //cout << registrar << endl;  // or registrar.printReport()
	registrar.printReport();

    cout << "EnrollStudentInCourse Bullwinkle CS101.001" << endl;
    cout <<  "Should fail, i.e. do nothing, since Bullwinkle is not a student." << endl;
    registrar.enrollStudentInCourse("Bullwinkle", "CS101.001");
    //cout << registrar << endl;  // or registrar.printReport()
	registrar.printReport();

    cout << "CancelCourse CS102.001" << endl;
    registrar.cancelCourse("CS102.001");
    //cout << registrar << endl;  // or registrar.printReport()
	registrar.printReport();

    /*
    // [OPTIONAL - do later if time]
    cout << "ChangeStudentName FritzTheCat MightyMouse" << endl;
    registrar.changeStudentName("FritzTheCat", "MightyMouse");
    cout << registrar << endl;  // or registrar.printReport()

    cout << "DropStudentFromCourse MightyMouse CS101.001" << endl;
    registrar.dropStudentFromCourse("MightyMouse", "CS101.001");
    cout << registrar << endl;  // or registrar.printReport()

    cout << "RemoveStudent FritzTheCat" << endl;
    registrar.removeStudent("FritzTheCat");
    cout << registrar << endl;  // or registrar.printReport()
    */

    cout << "Purge for start of next semester" << endl;
    registrar.purge();
    //cout << registrar << endl;  // or registrar.printReport()
	registrar.printReport();
}
