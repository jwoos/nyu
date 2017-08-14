#include <string>

class Princess;

class FrogPrince {
	public:
		FrogPrince(const std::string& name);

		void display() const;

		std::string getName() const;

		void marries(Princess& betrothed);

		void setSpouse(Princess* p);
	private:
		std::string name;
		Princess* spouse;
};
