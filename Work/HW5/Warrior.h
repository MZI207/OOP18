#ifndef WARRIOR_H
#define WARRIOR_H
#include <string>
#include <vector>
#include <iostream>

namespace WarriorCraft {
	class Noble;
	class Warrior {
	public:
		//Output operator for the warrior
		friend std::ostream& operator<<(std::ostream& os, const Warrior& war);
		//Creates the war with his name and str
		Warrior(const std::string& warName, int warStr);
		//Returns the str of the warrior
		int getStr() const;
		//set str of the warrior
		void setStr(int newStr);
		//get name of the warrior
		std::string getName() const;
		//Get if its hired
		bool isHired() const;
		//sets employment
		void employment();
		bool setBoss(Noble* nob);
		void runaway();
	private:
		Noble* boss = nullptr;
		bool employeed = false;
		std::string name;
		int str;
	};
}
#endif // !WARRIOR_H

