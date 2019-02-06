#include "Student.h"
#include "Course.h"
namespace BrooklynPoly {
	std::ostream& operator<<(std::ostream & os, const Student & rhs) {
		os << rhs.name;
		return os;
	}
	Student::Student(const std::string& name) : name(name), courses(0) {}
	const std::string& Student::getName() const { return name; }
	bool Student::addCourse(Course* course) {
		bool inClass = false;
		for (size_t i = 0; i < courses.size(); i++) {
			if (courses[i] == course) {
				inClass = true;
			}
		}
		if (!inClass) {
			courses.push_back(course);
			return true;
		}
		return false;
	}
	
	void Student::removedFromCourse(Course* course) {
		bool inCourse = false;
		size_t pos = 0;
		for (size_t i = 0; i < courses.size(); i++) {
			if (courses[i] == course) {
				inCourse = true;
				pos = i;
			}
		}
		if (inCourse) {
			for (size_t i = pos + 1; i < courses.size(); i++) {
				courses[i - 1] = courses[i];
			}
			courses.pop_back();
			course->removeStudentsFromCourse(this);
		}
	}
}