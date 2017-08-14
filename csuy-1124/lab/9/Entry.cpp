#include "Directory.h"
#include "Entry.h"

using namespace std;

Entry::Entry(const string& aName, unsigned aRoom, unsigned aPhone, Position& aPosition) : name(aName), room(aRoom), phone(aPhone), pos(&aPosition) {}

string Entry::getName() const {
	return name;
}

unsigned Entry::getPhone() const {
	return phone;
}

ostream& operator<<(ostream& os, const Entry& e) {
	os << e.name << endl;
	os << e.room << endl;
	os << e.phone << endl;
	return os;
}
