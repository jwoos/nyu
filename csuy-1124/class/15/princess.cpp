#include <iostream>

#include "princess.h"
#include "frogprince.h"

using namespace std;

void Princess::display() const {
	cout << "Princess: " << name << " Spouse: ";
	if (spouse == nullptr) {
		cout << "None" << endl;
	} else {
		cout << spouse -> getName() << endl;
	}
}

void Princess::marries(FrogPrince& betrothed) {
	spouse = &betrothed;
	betrothed.setSpouse(this);
}

Princess::Princess(const string& name) : name(name), spouse(nullptr) {}

void Princess::setSpouse(FrogPrince* fp) {
	spouse = fp;
}
