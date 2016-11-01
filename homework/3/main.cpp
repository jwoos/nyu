#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Cafeteria_account {
	public:
		Cafeteria_account(string newName, int newId, double newAmount) : name(newName), id(newId), newAmount(amount);

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

class LessThanOnName {
	public:
		bool operator()(const Cafeteria_account& lhs, const Cafeteria_account& rhs) {
			return lhs.getName() < rhs.getName();
		}
};

int main() {
	int currentId = 1;

	ifstream ifs;
	ifs.open("data.txt");

	if (!ifs) {
		cout << "Error opening file!" << endl;
		exit(1);
	}

	string name;
	double amount;

	while (ifs >> name >> amount) {

	}
}

