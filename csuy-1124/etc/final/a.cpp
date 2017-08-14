#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Pizza {
	private:
		double cheese;
		double sauce;
		double dough;
		int percent;

	public:
		Pizza(double cheese = 33, double sauce = 33, double dough = 33) : cheese(cheese), sauce(sauce), dough(dough), percent(100) {}

		virtual void eat(int eaten) {
			percent -= eaten;
		}
};

class CircularPizza : public Pizza {
	public:
		CircularPizza() : Pizza(30, 40, 30) {}

		void eat(int eaten) {
			Pizza::eat(eaten);
			cout << "Fold this pizza in half and eat from pointy end." << endl;
		}
};

int main() {
	vector<Pizza*> pizzas;
	pizzas.push_back(new Pizza());
	pizzas.push_back(new CircularPizza());
	pizzas.push_back(new CircularPizza());

	for (Pizza* aPie: pizzas) {
		aPie -> eat(10);
	}

	for (Pizza* pizzaPointer : pizzas) {
		delete pizzaPointer;
	}

	pizzas.clear();
}
