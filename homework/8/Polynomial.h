#include <vector>
#include <iostream>

struct Node;

class Polynomial {
	friend std::ostream& operator<<(std::ostream& os, const Polynomial& expression);

	public:
		Polynomial(const std::vector<int>& values);

	private:
		Node* coefficient;
		int degree;
};
