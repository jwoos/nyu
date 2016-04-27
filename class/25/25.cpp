#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

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

void towers(int n, char start, char target, char spare) {
	if (n == 0) {
		return;
	}

	towers(n - 1, start, spare, target);
	cout << "Move disk: " << n << " from spindle: " << start << " to spindle: " << target << endl;
	towers(n - 1, spare, target, start);
}

// O(log(n))
int binarySearch(int* arr, int search, int low, int high) {
	// can't deal with int overflow
	//int middle = (high + low) / 2;
	int middle = (low + (high + low)) / 2;
	if (high < low) {
		return -1;
	}

	if (arr[middle] == search) {
		return middle;
	} else if (search < arr[middle]) {
		return binarySearch(arr, search, low, middle - 1);
	} else if (search > arr[middle]) {
		return binarySearch(arr, search, middle + 1, high);
	}
}

// 2^n - 1
// with an int 32 returns -1 as an int is only 32 bits
// long is 32 bits
int towersCount(int n, char start, char target, char spare) {
	if (n == 0) {
		return 0;
	}
	int count = 0;

	count += towersCount(n - 1, start, spare, target);
	count++;
	count += towersCount(n - 1, spare, target, start);

	return count;
}

int fibonacci(int n) {
	if (n < 2) {
		return 1;
	}

	return fibonacci(n -1) + fibonacci(n - 2);
}

int fibonacciLoop(int n) {
	int total = 1;

	return total;
}

int main() {
	//towers(4, 'A', 'C', 'B');
	cout << towersCount(10, 'A', 'C', 'B') << endl;

	//int arr[] = {35, 1, 3, 13, 21, 5, 2};
	int arr[] = {1, 2, 3, 5, 13, 21, 35};
	cout << binarySearch(arr, 7, 0, 6) << endl;
};
