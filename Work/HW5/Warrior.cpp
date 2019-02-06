#include "Warrior.h"
#include "Noble.h"

namespace WarriorCraft {
	Warrior::Warrior(const std::string& warName, int warStr) : name(warName), str(warStr) {}
	std::ostream& WarriorCraft::operator<<(std::ostream& os, const Warrior& war){
		os << war.name << ": " << war.str << std::endl;
		return os;
	}
	int Warrior::getStr() const { return str; }
	void Warrior::setStr(int newStr) { str = newStr; }
	std::string Warrior::getName() const { return name; }
	bool Warrior::isHired() const { return employeed; }
	void Warrior::employment() { 
		employeed = !employeed;
	}
	bool Warrior::setBoss(Noble* nob){
		if (!employeed) {
			boss = nob;
			return true;
		}
		return false;
	}
	void Warrior::runaway() {
		if (!employeed) {
			std::cout << name << " is unable to runaway, as he is not employeed" << std::endl;
		}
		else {
			std::cout << name << " flees in terror, abandoning his lord, " << boss->getName() << std::endl;
			boss->removeWarrior(this);
			boss = nullptr;
		}

	}
}