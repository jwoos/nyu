#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Food {
	friend ostream& operator<<(ostream& os, const Food& rhs) {
		for (int i = 0; i < ingredientCount; i++) {
			os << ingredients[i] << " ";
		}
		return os;
	}

	private:
		int ingredientCount;
		string* ingredients;

	public:
		Food() : ingredientCount(0), ingredients(nullptr) {}

		virtual ~Food();

		Food& operator=(const Food& rhs) {
			if (this != &rhs) {
				ingredientCount = rhs.ingredientCount;
				delete [] ingredients;
				ingredients = new string[ingredientCount];
				for (int i = 0; i < ingredientCount; i++) {
					ingredients[i] = rhs.ingredients[i];
				}
			}

			return *this;
		}

		bool operator<(const Food& rhs) const {
			return (ingredientCount < rhs.ingredientCount);
		}
};

class Chocolate : public Food {
	
};
