#include "Course.h"
#include "Student.h"
namespace BrooklynPoly {
	//Course
	std::ostream& operator<<(std::ostream& os, const Course& rhs) {
		os << rhs.name << " ";
		return os;
	}
	Course::Course(const std::string& courseName) : name(courseName), students(0) {}
	const std::string& Course::getName() const { return name; }
	bool Course::addStudent(Student* stud) {
		bool inClass = false;
		for (size_t i = 0; i < students.size(); i++) {
			if (students[i] == stud) {
				inClass = true;
			}
		}
		if (!inClass) {
			students.push_back(stud);
			return true;
		}
		return false;
	}
	void Course::removeStudentsFromCourse(Student* stud) {
		bool inCourse = false;
		size_t pos = 0;
		for (size_t i = 0; i < students.size(); i++) {
			if (students[i] == stud) {
				inCourse = true;
				pos = i;
			}
		}
		if (inCourse) {
			for (size_t i = pos + 1; i < students.size(); i++) {
				students[i - 1] = students[i];
			}
			students.pop_back();
			stud->removedFromCourse(this);
		}
	}
	void Course::removeAllStudents() {
		for (size_t i = 0; i < students.size(); i++) {
			removeStudentsFromCourse(students[i]);
		}
	}
}