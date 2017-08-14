#include <string>

class Position {
	public:
		Position(const std::string& aTitle, double aSalary);

		std::string getTitle() const;

		double getSalary() const;

		void changeSalaryTo(double d);
	private:
		std::string title;
		double salary;
};
