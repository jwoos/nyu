/*
 Recitation 09
 CS1124
 Junwoo Shin
 */

#include <cstdlib>
#include <string>
#include <iostream>

#include "Directory.h"
#include "Position.h"
#include "Entry.h"

using namespace std;

int main() {
	// Model as if there are these four kinds
	// of position in the problem:
	Position boss("Boss", 3141.59);
	Position pointyHair("Pointy Hair", 271.83);
	Position techie("Techie", 14142.13);
	Position peon("Peonissimo", 34.79);

	Directory d;
	d.add("Marilyn", 123, 4567, boss);
	cout << "Directory d2 = d;" << endl;
	cout << endl;

	Directory d2 = d;
	d2.add("Gallagher", 111, 2222, techie);
	Directory d3;
	cout << "d3 = d2;" << endl;
	cout << endl;
	d3 = d2;

	cout << "d" << endl;
	cout << d << endl;

	cout << "d2" << endl;
	cout << d2 << endl;

	cout << "d3" << endl;
	cout << d3 << endl;

	cout << "d[\"Marilyn\"]" << endl;
	cout << d["Marilyn"] << endl;
	cout << endl;
}
