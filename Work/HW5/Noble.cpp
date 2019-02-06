#include "Noble.h"
#include "Warrior.h"
namespace WarriorCraft {
	Noble::Noble(const std::string& nobleName) : name(nobleName) {}
	std::ostream& WarriorCraft::operator<<(std::ostream& os, const Noble& nob) {
		os << nob.name << " has an army of " << nob.warriors.size() << ":" << std::endl;
		for (size_t i = 0; i < nob.warriors.size(); i++) {
			os << "\t" << *nob.warriors[i];
		}
		return os;
	}
	bool Noble::hire(Warrior& war) {
		if (!war.isHired() && !isDead) {
			war.setBoss(this);
			war.employment();
			warriors.push_back(&war);
			return true;
		}
		return false;
	}
	std::string Noble::getName() const { return name; }
	void Noble::removeWarrior(Warrior* war) {
		bool isRemoved = false;
		for (size_t i = 0; !isDead && i < warriors.size(); i++) {
			if (isRemoved) {
				warriors[i - 1] = warriors[i];
			}
			if (war == warriors[i]) {
				warriors[i]->employment();
				isRemoved = true;
			}
		}
		if (isRemoved) { warriors.pop_back(); }
	}
	bool Noble::fire(Warrior& war) {
		bool isRemoved = false;
		for (size_t i = 0; !isDead && i < warriors.size(); i++) {
			if (isRemoved) {
				warriors[i - 1] = warriors[i];
			}
			if (&war == warriors[i]) {
				warriors[i]->employment();
				isRemoved = true;
				std::cout << warriors[i]->getName() << ", you're fired! -- " << name << std::endl;
			}
		}
		if (isRemoved) {
			warriors.pop_back();
			return true;
		}
		return false;
	}
	void Noble::battle(Noble& challenger) {
		int thisStr = 0;//This Nobles str
		for (size_t i = 0; i < warriors.size(); i++) {
			thisStr = thisStr + warriors[i]->getStr();
		}
		int cStr = 0;//Challenger's str
		for (size_t i = 0; i < challenger.warriors.size(); i++) {
			cStr = cStr + challenger.warriors[i]->getStr();
		}
		std::cout << name << " battles " << challenger.name << std::endl;
		if (thisStr == 0 && cStr == 0) { //If they are both dead
			std::cout << "Oh, NO! They're both dead! Yuck!" << std::endl;
		}

		else if (isDead) { //If thisNoble is dead
			std::cout << "He's dead, " << challenger.name << std::endl;
		}
		else if (challenger.isDead) { //If cNoble is dead
			std::cout << "He's dead, " << name << std::endl;
		}

		else if (thisStr > cStr) { // If thisNoble is stronger
			for (size_t i = 0; i < warriors.size(); i++) {
				warriors[i]->setStr(warriors[i]->getStr() * (float(1) - (float(cStr) / float(thisStr))));
			}
			for (size_t i = 0; i < challenger.warriors.size(); i++) {
				challenger.warriors[i]->setStr(0);
			}
			challenger.isDead = true;
			std::cout << name << " defeats " << challenger.name << std::endl;
		}
		else if (thisStr < cStr) { //If challenger is stronger
			for (size_t i = 0; i < challenger.warriors.size(); i++) {
				challenger.warriors[i]->setStr(challenger.warriors[i]->getStr() * (float(1) - (float(thisStr) / float(cStr))));
			}
			for (size_t i = 0; i < warriors.size(); i++) {
				warriors[i]->setStr(0);
			}
			isDead = true;
			std::cout << challenger.name << " defeats " << name << std::endl;
		}
		else { //If they have equal strengths
			for (size_t i = 0; i < warriors.size(); i++) {
				warriors[i]->setStr(0);
			}
			for (size_t i = 0; i < challenger.warriors.size(); i++) {
				challenger.warriors[i]->setStr(0);
			}
			challenger.isDead = true;
			isDead = true;
			std::cout << "Mutual Annihilation: " << name << " and " << challenger.name << " die at each other's hands" << std::endl;
		}
	}
}