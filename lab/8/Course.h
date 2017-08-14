#include <string>
#include <vector>

class Student;

class Course {
	public:
		Course(const std::string& name);

		int getStudentIndexFromVector(const std::string& name) const;

		std::string getName() const;

		void addStudent(Student* student);

		void removeStudent(const std::string& name);

		std::vector<Student*> getStudents() const;

		void display() const;
	private:
		std::vector<Student*> students;
		std::string name;
};
