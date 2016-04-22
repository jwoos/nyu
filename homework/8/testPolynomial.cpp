#include "Polynomial.h"
#include <iostream>
#include <vector>

using namespace std;

void doNothing(Polynomial temp) {}

int main() {
	//test constructor
	Polynomial p1({17});
	Polynomial p2({1, 2});
	Polynomial p3({-1, 5});
	Polynomial p4({5, 4, 3, 2, 1});

	cout << "p1: " << p1 << endl;
	cout << "p2: " << p2 << endl;
	cout << "p3: " << p3 << endl;
	cout << "p4: " << p4 << endl;
	/*
	 *cout << "p2 + p3: " << (p2+p3) << endl;
	 *cout << "p2 + p4: " << (p2+p4) << endl;
	 *cout << "p4 + p2: " << (p4+p2) << endl;
	 */


	//test copy constructor - the statement below uses the copy constructor
	//to initialize poly3 with the same values as poly4
/*
 *    Polynomial p5(p4);
 *    p5 += p3;
 *    cout << "Polynomial p5(p4);\n"
 *         << "p5 += p3;\n";
 *
 *    cout << "p4: " << p4 << endl;
 *    cout << "p5: " << p5 << endl;
 *
 *    cout << "Calling doNothing(p5)\n";
 *    doNothing(p5);
 *    cout << "p5: " << p5 << endl;
 */

	//tests the assignment operator
	/*
	 *Polynomial p6;
	 *cout << "p6: " << p6 << endl;
	 *cout << boolalpha;	// Causes bools true and false to be printed that way.
	 *cout << "(p4 == p6) is " << (p4 == p6) << endl;
	 *p6 = p4;
	 *cout << "p6: " << p6 << endl;
	 *cout << boolalpha;
	 *cout << "(p4 == p6) is " << (p4 == p6) << endl;
	 */

	//test the evaluaton
/*
 *    int x = 5;
 *    cout << "Evaluating p1 at " << x << " yields: " << p1.evaluate(5) << endl;
 *    cout << "Evaluating p2 at " << x << " yields: " << p2.evaluate(5) << endl;
 *
 *    Polynomial p7({3, 2, 1}); // 3x^2 + 2x + 1
 *    cout << "p7: " << p7 << endl;
 *    cout << "Evaluating p7 at " << x << " yields: " << p7.evaluate(5) << endl;
 *
 *    cout << boolalpha;
 *    cout << "(p1 == p2) is " << (p1 == p2) << endl;
 *    cout << "(p1 != p2) is " << (p1 != p2) << endl;
 */
}


