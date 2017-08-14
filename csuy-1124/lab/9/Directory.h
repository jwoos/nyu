#include <string>
#include <iostream>

class Position;
class Entry;

class Directory {
	public:
		Directory();

		~Directory();

		Directory(const Directory& rhs);

		Directory& operator=(const Directory& rhs);

		unsigned operator[](const std::string& name);

		void add(const std::string& name, unsigned room, unsigned ph, Position& pos);

		friend std::ostream& operator<<(std::ostream& os, const Directory& dir);
	private:
		size_t capacity;
		size_t size;
		Entry** entries;
};

