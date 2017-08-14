#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class Food {
	private:
		int ingredientCount;
		string* ingredients;

	friend ostream& operator<<(ostream& os, const Food& rhs) {
		for (int i = 0; i < rhs.ingredientCount; i++) {
			os << rhs.ingredients[i] << ' ';
		}
		return os;
	}

	public:
		Food() : ingredientCount(0), ingredients(nullptr) {}

		Food(const Food& rhs) {
			ingredientCount = rhs.ingredientCount;
			cout << ingredients << endl;
			delete [] ingredients;
			ingredients = new string [ingredientCount];

			for (int i = 0; i < ingredientCount; i++) {
				ingredients[i] = rhs.ingredients[i];
			}
		}

		virtual ~Food() {
			delete [] ingredients;
		};

		Food& operator=(const Food& rhs) {
			if (this != &rhs) {
				ingredientCount = rhs.ingredientCount;
				delete [] ingredients;
				ingredients = new string [ingredientCount];

				for (int i = 0; i < ingredientCount; i++) {
					ingredients[i] = rhs.ingredients[i];
				}
			}

			return *this;
		}

		bool operator<(const Food& rhs) const {
			return (ingredientCount < rhs.ingredientCount);
		}

		void addIngredient(const string& anIngredient) {
			string* temp = ingredients;
			ingredients = new string [++ingredientCount];

			for (int i = 0; i < ingredientCount - 1; i++) {
				ingredients[i] = temp[i];
			}

			delete [] temp;

			ingredients[ingredientCount - 1] = anIngredient;
		}
};

class Chocolate : public Food {
	private:
		int* cocoa;

	public:
		Chocolate(int cocoaPercent = 50) : cocoa(new int(cocoaPercent)) {
			addIngredient("cocoa");
		}

		Chocolate(const Chocolate& rhs) : Food(rhs) {
			delete cocoa;
			cocoa = new int(*(rhs.cocoa));
		}

		~Chocolate() {
			delete cocoa;
		}
};

int main() {
	Food quioche;
	quioche.addIngredient("cheese");
	quioche.addIngredient("milk");
	quioche.addIngredient("flour");
	cout << quioche << endl;

	/*
	 *Food otherQuioche;
	 *cout << otherQuioche << endl;
	 */

	Food foodCopy = quioche;

	Chocolate choco;
	Chocolate choco2(30);
	cout << choco << endl;
	cout << choco2 << endl;

	//Chocolate copy(choco);
	//cout << copy << endl;
}
