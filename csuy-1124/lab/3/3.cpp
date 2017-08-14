// Name: Junwoo Shin
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cstdlib>
using namespace std;

class Sandwich {
	public:
		Sandwich(int tomato = 2, int cheese = 1, float mustard = 0.05, float mayo = 1.0, int bread = 2) :bread(bread), cheese(cheese), mayo(mayo), tomato(tomato), mustard(mustard) {}

		void display() const {
			cout << "Bread: " << bread << endl;
			cout << "Cheese: " << cheese << endl;
			cout << "Mayo: " << mayo << endl;
			cout << "Tomato: " << tomato << endl;
			cout << "Mustard: " << mustard << endl;
		}

		int getBread() const {
			return bread;
		}

		void setCheese(int cheeseCount) {
			cheese = cheeseCount;
		}

		int getCheese() const {
			return cheese;
		}

		void setMayo(float mayoCount) {
			mayo = mayoCount;
		}

		float getMayo() const {
			return mayo;
		}

		void setTomato(int tomatoCount) {
			tomato = tomatoCount;
		}

		int getTomato() const {
			cout << tomato << endl;
			return tomato;
		}

		void setMustard(float mustardCount) {
			mustard = mustardCount;
		}

		float getMustard() const {
			return mustard;
		}

	private:
		const int bread;
		int cheese;
		float mayo;
		int tomato;
		float mustard;
};

class Truck {
	public:
		void checkBeforeLeaving() {
			for (size_t index = 0; index < sandwichCollection.size(); index++) {
				sandwichCollection[index].display();
				cout << endl;
			}
		}

		void insertSandwich(Sandwich& aSandwich) {
			sandwichCollection.push_back(aSandwich);
		}

	private:
		vector<Sandwich> sandwichCollection;
};

int main() {
	Truck deliveryTruck;

	Sandwich firstSandwich;
	deliveryTruck.insertSandwich(firstSandwich);

	Sandwich secondSandwich;
	secondSandwich.setMustard(0);
	deliveryTruck.insertSandwich(secondSandwich);

	Sandwich thirdSandwich(2, 3);
	deliveryTruck.insertSandwich(thirdSandwich);

	Sandwich fourthSandwich;
	deliveryTruck.insertSandwich(fourthSandwich);

	deliveryTruck.checkBeforeLeaving();
};
