#include <iostream>

#include "frogprince.h"
#include "princess.h"

using namespace std;

FrogPrince::FrogPrince(const string& name) : name(name), spouse(nullptr) {}

void FrogPrince::display() const {
	cout << "Frog: " << name << endl;
}
string FrogPrince::getName() const {
	return name;
}

void FrogPrince::marries(Princess& betrothed) {
	spouse = &betrothed;
	betrothed.setSpouse(this);
}

void FrogPrince::setSpouse(Princess* p) {
	spouse = p;
}
