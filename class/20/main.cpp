#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <cmath>

using namespace std;

template <typename T>
class RBT;

template <typename T>
class RBGNode {
	public:
		RBGNode(const T& newData = T(), RBGNode<T>* newParent = nullptr, RBGNode<T>* newLeft = nullptr, RBGNode<T>* newRight = nullptr, bool black) : data(newData), parent(newParent), left(newLeft), right(newRight), isBlack(black) {}

	private:
		bool isBlack;
		T data;
		RBGNode<T>* parent;
		RBGNode<T>* left;
		RBGNode<T>* right;

	friend RBT<T>;
};

template <typename T>
class RBT {};

int main() {}
