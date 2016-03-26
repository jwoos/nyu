#include <string>
#include <vector>
#include <iostream>

class Student;
class Course;

namespace BrooklynPoly {
	class Registrar {
		friend std::ostream& operator<<(std::ostream& output, const Registrar& registrar);
		public:
			Registrar();

			void addCourse(const std::string& course);

			void cancelCourse(const std::string& course);

			void addStudent(const std::string& name);

			void enrollStudentInCourse(const std::string& student, const std::string& course);

			void printReport() const;

			int getCourseIndexFromVector(const std::string& courseName);

			int getStudentIndexFromVector(const std::string& courseName);

			void changeStudentName(const std::string& oldName, const std::string& newName);

			void dropStudentFromCourse(const std::string& student, const std::string& course);

			void removeStudent(const std::string& name);

			void purge();
		private:
			std::vector<Course*> courses;
			std::vector<Student*> students;
	};
}
