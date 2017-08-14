#include <string>
#include <iostream>

class Position;

class Entry {
	public:
		Entry(const std::string& aName, unsigned aRoom, unsigned aPhone, Position& aPosition);

		std::string getName() const;

		unsigned getPhone() const;

		friend std::ostream& operator<<(std::ostream& os, const Entry& e);
	private:
		std::string name;
		unsigned room;
		unsigned phone;
		Position* pos;
};
