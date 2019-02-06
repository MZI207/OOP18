#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Student {
public:
	//Dislpays the student
	friend ostream& operator<< (ostream& os, const Student& stud) {
		os << "Name: " << stud.name << ", Grades: ";
		for (size_t i = 0; i < stud.grades.size(); i++) {
			os << stud.grades[i] << " ";
		}
		return os;
	}
	//Constructor
	Student(const string& thisname) : name(thisname), grades(14, -1) {}
	//Returns the name of the student
	string getName() const  {
		return name;
	}
	//Sets the grade of the student
	bool setGrade(int grade, int week) {
		grades[week -1] = grade;
		return true;
	}
private:
	string name;
	vector<int> grades;
};
//the Section of the class 
class Section {
public:
	//displays the section
	friend ostream& operator<< (ostream& os, const Section& sect) {
		os << "Section: " << sect.name << ", " << sect.time << endl << "Students: " << endl;
		if (sect.students.size() != 0) {
			for (size_t i = 0; i < sect.students.size(); i++) {
				os << *sect.students[i] << endl;
			}
		}
		else { os << "None"; }
		return os;
	}
	//Contains the time and day of the section
	class Time_Slot {
	public:
		friend ostream& operator<< (ostream& os, const Time_Slot& time) {
			os << "Time slot: [Day: " << time.day << ", Start time: ";
			if (time.hour > 12) {
				os << time.hour - 12 << "PM] ";
			}
			else { os << time.hour << "AM]"; }
			return os;
		}
		Time_Slot(const string& day, int hour) : day(day), hour(hour) {}
		
	private:
		string day;
		int hour;
	};
	//Creates the section with the name, day and hour
	Section(const string& name, const string& day, int hour) : name(name), time(day, hour) {}
	//Copy Constructor
	Section(Section& sect):time(sect.time), name(sect.name) {
		for (size_t i = 0; i < sect.students.size(); i++) {
			students.push_back(new Student(*sect.students[i]));
		}
	}
	//Destructor
	~Section() {
		for (size_t i = 0; i < students.size(); i++) {
			delete students[i];
		}
	}
	void reset() {
		for (size_t i = 0; i < students.size(); i++) {
			delete students[i];
		}
		students.clear();
	}
	//addStudent adds the student into the section
	bool addStudent(const string& studentName) {
		students.push_back(new Student(studentName));
		return true;
	}
	vector<Student*> getStudent() {
		return students;
	}
private:
	vector<Student*> students;
	string name;
	Time_Slot time;
};
//The TA
class LabWorker {
public:
	//Displays the Worker 
	friend ostream& operator<< (ostream& os, const LabWorker& worker) {
		os << worker.name;
		if (!worker.session) { os << " does not have a section"; }
		else { os << " has Section: " << *worker.session; }
		return os;
	}

	LabWorker(const string& thisname) : name(thisname) {}
	//Points to the new section
	bool addSection(Section& sect) {
		if (!session){ //Makes sure we dont remove pointing to a random section and causing a memory leak
			session = &sect;
			return true;
		}
		return false;
	}
	//Adds a grade to the student
	bool addGrade(const string studName, int grade,int week ) {
		vector<Student*> students = session->getStudent();
		for (size_t i = 0; students.size(); i++) {
			if (students[i]->getName() == studName) {
				students[i]->setGrade(grade, week);
				return true;
			}
		}
		return false;
	}
private:
	string name;
	Section* session = nullptr;
};
//Gotta make sure the copy doesnt effect this 
void doNothing(Section sect) {}

int main() {
	//Test 1
	cout << "Test 1: Defining a section\n";
	Section secA2("A2", "Tuesday", 16);
	cout << secA2 << endl;
	//Test 2
	cout << "\nTest 2: Adding students to a section\n";
	secA2.addStudent("John");
	secA2.addStudent("George");
	secA2.addStudent("Paul");
	secA2.addStudent("Ringo");
	cout << secA2 << endl;
	//Test 3
	cout << "\nTest 3: Defining a lab worker.\n";
	LabWorker moe("Moe");
	cout << moe << endl;
	//Test 4
	cout << "\nTest 4: Adding a section to a lab worker.\n";
	moe.addSection(secA2);
	cout << moe << endl;
	//Test 5
	cout << "\nTest 5: Adding a second section and lab worker.\n";
	LabWorker jane("Jane");
	Section secB3("B3", "Thursday", 11);
	secB3.addStudent("Thorin");
	secB3.addStudent("Dwalin");
	secB3.addStudent("Balin");
	secB3.addStudent("Kili");
	secB3.addStudent("Fili");
	secB3.addStudent("Dori");
	secB3.addStudent("Nori");
	secB3.addStudent("Ori");
	secB3.addStudent("Oin");
	secB3.addStudent("Gloin");
	secB3.addStudent("Bifur");
	secB3.addStudent("Bofur");
	secB3.addStudent("Bombur");
	jane.addSection(secB3);
	cout << jane << endl;
	//Test 6
	cout << "\nTest 6: Adding some grades for week one\n";
	moe.addGrade("John", 17, 1);
	moe.addGrade("Paul", 19, 1);
	moe.addGrade("George", 16, 1);
	moe.addGrade("Ringo", 7, 1);
	cout << moe << endl;
	//Test 7 
	cout << "\nTest 7: Adding some grades for week three (skipping week 2)\n";
	moe.addGrade("John", 15, 3);
	moe.addGrade("Paul", 20, 3);
	moe.addGrade("Ringo", 0, 3);
	moe.addGrade("George", 16, 3);
	cout << moe << endl;
	//Test 8
	cout << "\nTest 8: We're done (almost)! \nWhat should happen to all " << "those students (or rather their records?)\n";
	cout << "\nTest 9: Oh, IF you have covered copy constructors in lecture, "
		<< "then make sure the following call works properly, i.e. no memory leaks\n";
	//Test 9
	doNothing(secA2);
	cout << "Back from doNothing\n\n";
	return 0;
}