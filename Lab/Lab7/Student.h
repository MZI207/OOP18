#ifndef STUDENT_H
#define STUDENT_H
#include <string>
#include <iostream>
#include <vector>
namespace BrooklynPoly {
	class Course;
	class Student {
		friend std::ostream& operator<<(std::ostream& os, const Student& rhs);
	public:
		// Student methods needed by Registrar
		Student(const std::string& name);
		const std::string& getName() const;
		bool addCourse(Course* course);

		// Student method needed by Course
		void removedFromCourse(Course* course);

	private:
		std::string name;
		std::vector<Course*> courses;
	};

}
#endif // !STUDENT_H
