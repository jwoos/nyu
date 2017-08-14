#include <string>

class FrogPrince;

class Princess {
	public:
		Princess(const std::string& name);

		void display() const;

		void marries(FrogPrince& betrothed);

		void setSpouse(FrogPrince* fp);
	private:
		std::string name;
		FrogPrince* spouse;
};
