#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
using namespace std;

int main() {
	std::cout << "hello world!\n";
	cout << "hello world!\n";
	// return 0;
	char c = 'x';

	string s = "This is a string";

	if (c == 'q') {
		cout << "Yup!\n";
	} else if (c == 'x') {
		cout << "Not a q!\n";
		cout << "It's an x!\n";
	} else {
		cout << "nope\n";
	}

	// while loop
	int x = 0;
	while (x < 10) {
		cout << x << "\n";
		cout << x << endl;
		x++;
	}

	// for loop
	for (int y = 0; y < 10; y++) {
		cout << y << endl;
	}

	//
	int z = 0;
	do {
		cout << z << endl;
		z++;
	} while (z < 10);

	// I/O
	// method one
	ifstream ifs;
	ifs.open("a_file");
	// method two
	ifstream ifs2("a_file");

	if (!ifs) {
		cout << "error" << endl;
		exit(1);
	}

	string word;
	while (ifs >> word) {
		cout << word << endl;
	}
}
