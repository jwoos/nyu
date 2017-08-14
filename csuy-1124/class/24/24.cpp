#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void recursiveFunction() {
	recursiveFunction(); // infinite loop
}

// memory space of O(n)
int factorial(int n) {
	if (n == 0) {
		return 1;
	}

	return n * factorial(n - 1);
}

// memory space of O(1)
int factorial_loop(int n) {
	int total = 1;
	for (int x = 1; x <= n; x++) {
		total *= x;
	}

	return total;
}

bool isPalindrome(const char* array, int len) {
	if (len <= 1) {
		return true;
	}

	if (array[0] == array[len - 1]) {
		return isPalindrome(array + 1, len - 2);
	} else {
		return false;
	}
}

void printDigits(int n) {
	if (n <= 9) {
		cout << n << ' ';
	} else {
		printDigits(n / 10);
		cout << n % 10 << ' ';
	}
}

void printBits(int n) {
	if (n < 2) {
		cout << n << ' ';
	} else {
		printBits(n / 2);
		cout << n % 2 << ' ';
	}
}

// binary tree
struct TreeNode {
	int data;
	TreeNode* left;
	TreeNode* right;
};

int treeSum(TreeNode* root) {
	if (root == nullptr) {
		return 0;
	}
	return root -> data + treeSum(root -> left) + treeSum(root -> right);
}

int main() {
	printDigits(1000);
	cout << endl;
	printBits(1213123);
}
