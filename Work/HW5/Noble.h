#ifndef NOBLE_H
#define NOBLE_H
#include <vector>
#include <iostream>
#include <string>

namespace WarriorCraft {
	class Warrior;
	class Noble {
	public:
		//Creates the noble with his name
		Noble(const std::string& nobleName);
		//Displays the noble and his warriors
		friend std::ostream& operator<<(std::ostream& os, const Noble& nob);
		//Hires warriors, returns false if the guy cant be hired due to restrictions
		bool hire(Warrior& war);
		//Fire warriors, returns false if the warrior is not there and fails to remove the guy
		bool fire(Warrior& war);
		void removeWarrior(Warrior* war);
		//battles nobles depending on the scenario
		void battle(Noble& challenger);
		std::string getName() const;
	private:
		bool isDead = false;
		std::string name;
		std::vector<Warrior*> warriors;
	};
}
#endif // !NOBLE_H

