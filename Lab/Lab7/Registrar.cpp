#include "Registrar.h"
#include "Course.h"
#include "Student.h"
namespace BrooklynPoly {
	std::ostream& operator<<(std::ostream& os, const Registrar& rhs) {
		os << "Registrar's Report" << std::endl << "Courses: ";
		if (rhs.courses.size() == 0) { os << "None"; }
		for (size_t i = 0; i < rhs.courses.size(); i++) {
			os << *rhs.courses[i];
		}
		os << std::endl << "Students: ";
		if (rhs.students.size() == 0) { os << "None"; }
		for (size_t i = 0; i < rhs.students.size(); i++) {
			os << *rhs.students[i] << " ";
		}
		os << std::endl;
		return os;
	}
	Registrar::Registrar() : students(0), courses(0) {}
	bool Registrar::addCourse(const std::string& name) {
		bool inReg = false;
		for (size_t i = 0; i < courses.size(); i++) {
			if (courses[i]->getName() == name) {
				inReg = true;
			}
		}
		if (inReg) { return false; }
		Course* newCourse = new Course(name);
		courses.push_back(newCourse);
		return true;
	}
	bool Registrar::addStudent(const std::string& name) {
		bool inReg = false;
		for (size_t i = 0; i < students.size(); i++) {
			if (students[i]->getName() == name) {
				inReg = true;
			}
		}
		if (inReg) { return false; }
		Student* newStudent = new Student(name);
		students.push_back(newStudent);
		return true;
	}
	bool Registrar::enrollStudentInCourse(const std::string& studentName, const std::string& courseName) {
		Student* stud = nullptr;
		Course* course = nullptr;
		for (size_t i = 0; i < students.size(); i++) {
			if (students[i]->getName() == studentName) {
				stud = students[i];
			}
		}
		for (size_t i = 0; i < courses.size(); i++) {
			if (courses[i]->getName() == courseName) {
				course = courses[i];
			}
		}
		if (stud == nullptr || course == nullptr) { 
			std::cout << "Course or Student unavaiable" << std::endl;  
			return false; 
		}
		stud->addCourse(course);
		course->addStudent(stud);
		return true;
	}
	bool Registrar::cancelCourse(const std::string& courseName) {
		bool inReg = false;
		Course* holder = nullptr;
		for (size_t i = 0; i < courses.size(); i++) {
			if (inReg) {
				courses[i - 1] = courses[i];
			}
			if (courses[i]->getName() == courseName) {
				inReg = true;
				holder = courses[i];
			}
		}
		if (!inReg) { 
			std::cout << "Course not in Registrar" << std::endl;
			return false;
		}
		courses.pop_back();
		holder->removeAllStudents();
		delete holder;
		return true;
	}
	void Registrar::purge() {
		for (size_t i = 0; i < courses.size(); i++) {
			delete courses[i];
		}
		for (size_t i = 0; i < students.size(); i++) {
			delete students[i];
		}
		courses.clear();
		students.clear();
	}
	size_t Registrar::findStudent(const std::string& name) const {
		for (size_t i = 0; i < students.size(); i++) {
			if (students[i]->getName() == name) { return i; }
		}
		return students.size();
	}
	size_t Registrar::findCourse(const std::string& name) const {
		for (size_t i = 0; i < courses.size(); i++) {
			if (courses[i]->getName() == name) { return i; }
		}
		return courses.size();
	}
}