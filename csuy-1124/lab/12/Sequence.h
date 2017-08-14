#include <iostream>

struct Node;

class Sequence {
	public:
		Sequence();

		Sequence(const Sequence& rhs);

		Sequence& operator=(const Sequence& rhs);

		~Sequence();

		void reset();

		void add(int data);

		void remove();

		int data();

		void next();

		bool valid();

		void clear();

		void display(char delimiter=' ', std::ostream& os=std::cout);

	private:
		Node* head;
		Node* current;
};
