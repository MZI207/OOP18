#ifndef COURSE_H
#define COURSE_H
#include <string>
#include <vector>
#include <iostream>
namespace BrooklynPoly {
	class Student;
	class Course {
		friend std::ostream& operator<<(std::ostream& os, const Course& rhs);
	public:
		// Course methods needed by Registrar
		Course(const std::string& courseName);
		const std::string& getName() const;
		bool addStudent(Student* stud);
		void removeStudentsFromCourse(Student* stud);
		void removeAllStudents();
	private:
		std::string name;
		std::vector<Student*> students;
	};
}
#endif // !COURSE_H
