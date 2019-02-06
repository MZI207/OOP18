///Mohammed Iqbal
///HW03

#include <vector>
#include <iostream>
#include <string>
using namespace std;

class Warrior {
public:
	//Output operator for the warrior
	friend ostream& operator<<(ostream& os, const Warrior war) {
		os << war.name << ": " << war.str << endl;
		return os;
	}
	//Creates the war with his name and str
	Warrior(const string& warName, int warStr): name(warName), str(warStr){}
	//Returns the str of the warrior
	int getStr() const { return str; }
	//Returns the name of the warrior
	void setStr(int newStr) { str = newStr; }
	string getName() const { return name; }
	//Gets if it is employeed
	bool isHired() const {return employeed;}
	//Sets employeed to the opposite of what it is now
	void employment() { employeed = !employeed; }
private:
	bool employeed = false;
	string name;
	int str;
};
class Noble {
public:
	//Creates the noble with his name
	Noble(const string& nobleName): name(nobleName){}
	//Displays the noble and his warriors
	void display() const {
		cout << name << " has an army of " << warriors.size() << ":" << endl;
		for (size_t i = 0; i < warriors.size(); i++) {
			cout << "\t" << *warriors[i];
		}
	}
	//Hires warriors, returns false if the guy cant be hired due to restrictions
	bool hire(Warrior& war) {
		if (!war.isHired() && !isDead) {
			war.employment();
			warriors.push_back(&war);
			return true;
		}
		return false;
	}
	//Fire warriors, returns false if the warrior is not there and fails to remove the guy
	bool fire(Warrior& war){
		bool isRemoved = false;
		for (size_t i = 0; !isDead && i < warriors.size(); i++) {
			if (isRemoved) {
				warriors[i - 1] = warriors[i];
			}
			if (&war == warriors[i]) {
				warriors[i]->employment();
				isRemoved = true;
				cout << warriors[i]->getName() << ", you're fired! -- " << name << endl;
			}
		}
		if (isRemoved) { 
			warriors.pop_back();
			return true;
		}
		return false;
	}
	
	//battles nobles depending on the scenario
	void battle(Noble& challenger) {
		int thisStr = 0;//This Nobles str
		for (size_t i = 0; i < warriors.size(); i++) {
			thisStr = thisStr + warriors[i]->getStr();
		}
		int cStr = 0;//Challenger's str
		for (size_t i = 0; i < challenger.warriors.size(); i++) {
			cStr = cStr + challenger.warriors[i]->getStr();
		}
		cout << name << " battles " << challenger.name << endl;
		if (thisStr == 0 && cStr == 0) { //If they are both dead
			cout << "Oh, NO! They're both dead! Yuck!" << endl;
		}
		
		else if (isDead) { //If thisNoble is dead
			cout << "He's dead, " << challenger.name << endl;
		}
		else if (challenger.isDead) { //If cNoble is dead
			cout << "He's dead, " << name << endl;
		}
		
		else if (thisStr > cStr) { // If thisNoble is stronger
			for (size_t i = 0; i < warriors.size(); i++) {
				warriors[i]->setStr(warriors[i]->getStr() * (float(1) - (float(cStr) / float(thisStr))));
			}
			for (size_t i = 0; i < challenger.warriors.size(); i++) {
				challenger.warriors[i]->setStr(0);
			}
			challenger.isDead = true;
			cout << name << " defeats " << challenger.name << endl;
		}
		else if (thisStr < cStr) { //If challenger is stronger
			for (size_t i = 0; i < challenger.warriors.size(); i++) {
				challenger.warriors[i]->setStr(challenger.warriors[i]->getStr() * (float(1) - (float(thisStr) / float(cStr))));
			}
			for (size_t i = 0; i < warriors.size(); i++) {
				warriors[i]->setStr(0);
			}
			isDead = true;
			cout << challenger.name << " defeats " << name << endl;
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
			cout << "Mutual Annihilation: " << name << " and " << challenger.name << " die at each other's hands" << endl;
		}
	}
private:
	bool isDead = false;
	string name;
	vector<Warrior*> warriors;
};

int main() {
	Noble art("King Arthur");
	Noble lance("Lancelot du Lac");
	Noble jim("Jim");
	Noble linus("Linus Torvalds");
	Noble billie("Bill Gates");

	Warrior cheetah("Tarzan", 10);
	Warrior wizard("Merlin", 15);
	Warrior theGovernator("Conan", 12);
	Warrior nimoy("Spock", 15);
	Warrior lawless("Xena", 20);
	Warrior mrGreen("Hulk", 8);
	Warrior dylan("Hercules", 3);

	jim.hire(nimoy);
	lance.hire(theGovernator);
	art.hire(wizard);
	lance.hire(dylan);
	linus.hire(lawless);
	billie.hire(mrGreen);
	art.hire(cheetah);

	jim.display();
	lance.display();
	art.display();
	linus.display();
	billie.display();

	art.fire(cheetah);
	art.display();

	art.battle(lance);
	jim.battle(lance);
	linus.battle(billie);
	billie.battle(lance);
	return 0;
}