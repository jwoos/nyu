#include <string>
#include <vector>

class Course;

class Student {
	public:
		Student(const std::string& name);

		int getCourseIndexFromVector(const std::string& name) const;

		std::string getName() const;

		void setName(const std::string& newName);

		void addCourse(Course* course);

		void removeCourse(const std::string& course);

		std::vector<Course*> getCourses() const;

		void clearCourse();

		void display() const;
	private:
		std::vector<Course*> courses;
		std::string name;
};
