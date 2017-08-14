#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class PSB {
	private:
		bool broken;
		vector<double> weights;

	public:
		PSB() : broken(false) {}

		double getTotalWeight() const {
			double total = 0;

			for (double weight : weights) {
				total += weight;
			}

			return total;
		}

		void addItem(double item) {
			if (getTotalWeight() <= 25) {
				weights.push_back(item);
				if (getTotalWeight() > 25) {
					broken = true;
					weights.clear();
				}
			}
		}

		void display() const {
			if (broken) {
				cout << "The bag is broken" << endl;
			} else {
				cout << "weights:";

				for (double weight : weights) {
					cout << ' ' << weight<< endl;
				}
				cout << '.' << endl;
			}
		}
};

void fillContents(ifstream& ifs, PSB& bag) {
	double content;
	while (ifs >> content) {
		bag.addItem(content);
	}
}

int main() {
}
