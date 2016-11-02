#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Cafeteria_account {
	public:
		Cafeteria_account() {}

		Cafeteria_account(string newName, int newId, double newAmount) : name(newName), id(newId), amount(newAmount) {}

		string getName() const {
			return name;
		}

		int getId() const {
			return id;
		}

		double getAmount() const {
			return amount;
		}

	private:
		string name;
		int id;
		double amount;
};

ostream& operator<<(ostream& os, const Cafeteria_account& acc) {
	os << acc.getName() << " (" << acc.getId() << "): " << acc.getAmount();
	return os;
}

template <typename T>
void printAccounts(const vector<T>& vec) {
	for (T item : vec) {
		cout << item << endl;
	}
}

template <typename T, typename C>
void mergeSort(vector<T>& vec, C comparator) {
	vector<T> temp;
	temp.resize(vec.size());

	mergeSort(vec, temp, comparator, 0, (int)vec.size() - 1);
}

template <typename T, typename C>
void mergeSort(vector<T>& vec, vector<T>& temp, C comparator, int start, int end) {
	if (start >= end) {
		return;
	}

	int middle = (start + end) / 2;
	mergeSort(vec, temp, comparator, start, middle);
	mergeSort(vec, temp, comparator, middle + 1, end);

	merge(vec, temp, comparator, start, middle, end);
}

template <typename T, typename C>
void merge(vector<T>& vec, vector<T>& temp, C comparator, int leftStart, int leftEnd, int rightEnd) {
	int rightStart = leftEnd + 1;
	int tempStart = leftStart;
	int index = leftStart;

	while (leftStart <= leftEnd && rightStart <= rightEnd) {
		if (comparator(vec[leftStart], vec[rightStart])) {
			temp[index] = vec[leftStart];
			leftStart++;
		} else {
			temp[index] = vec[rightStart];
			rightStart++;
		}

		index++;
	}

	while (leftStart <= leftEnd) {
		temp[index] = vec[leftStart];
		index++;
		leftStart++;
	}

	while (rightStart <= rightEnd) {
		temp[index] = vec[rightStart];
		index++;
		rightStart++;
	}

	while (tempStart <= rightEnd) {
		vec[tempStart] = temp[tempStart];
		tempStart++;
	}
}

class LessThanOnName {
	public:
		bool operator()(Cafeteria_account& lhs, Cafeteria_account& rhs) {
			return lhs.getName() < rhs.getName();
		}
};

class GreaterThanOnName {
	public:
		bool operator()(Cafeteria_account& lhs, Cafeteria_account& rhs) {
			return lhs.getName() > rhs.getName();
		}
};

class LessThanOnId {
	public:
		bool operator()(const Cafeteria_account& lhs, const Cafeteria_account& rhs) const {
			return lhs.getId() < rhs.getId();
		}
};

class GreaterThanOnId {
	public:
		bool operator()(const Cafeteria_account& lhs, const Cafeteria_account& rhs) const {
			return lhs.getId() > rhs.getId();
		}
};

class LessThanOnAmount {
	public:
		bool operator()(const Cafeteria_account& lhs, const Cafeteria_account& rhs) const {
			return lhs.getAmount() < rhs.getAmount();
		}
};

class GreaterThanOnAmount {
	public:
		bool operator()(const Cafeteria_account& lhs, const Cafeteria_account& rhs) const {
			return lhs.getAmount() > rhs.getAmount();
		}
};

int main() {
	ifstream ifs;
	ifs.open("data.txt");

	if (!ifs) {
		cout << "Error opening file!" << endl;
		exit(1);
	}

	string name;
	int id;
	double amount;

	vector<Cafeteria_account> accounts;

	while (ifs >> name >> id >> amount) {
		accounts.push_back(Cafeteria_account(name, id, amount));
	}

	cout << "unsorted" << endl;
	printAccounts(accounts);
	cout << endl;

	cout << "sorted by name" << endl;
	cout << "===ascending===" << endl;
	mergeSort(accounts, LessThanOnName());
	printAccounts(accounts);
	cout << "===descending===" << endl;
	mergeSort(accounts, GreaterThanOnName());
	printAccounts(accounts);
	cout << endl;

	cout << "sorted by id" << endl;
	cout << "===ascending===" << endl;
	mergeSort(accounts, LessThanOnId());
	printAccounts(accounts);
	cout << "===descending===" << endl;
	mergeSort(accounts, GreaterThanOnId());
	printAccounts(accounts);
	cout << endl;

	cout << "sorted by amount" << endl;
	cout << "===ascending===" << endl;
	mergeSort(accounts, LessThanOnAmount());
	printAccounts(accounts);
	cout << "===descending===" << endl;
	mergeSort(accounts, GreaterThanOnAmount());
	printAccounts(accounts);
	cout << endl;
}
