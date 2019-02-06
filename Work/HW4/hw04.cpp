/*
Mohammed Iqbal
N11252745
mzi207
10/15/2018
*/
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

class Warrior {
	//Output operator for the warrior
	friend ostream& operator<<(ostream& os, const Warrior war) {
		os << war.name << ": " << war.str;
		return os;
	}
public:
	//Creates the war with his name and str
	Warrior(const string& warName, int warStr) : name(warName), str(warStr) {}
	//Returns the str of the warrior
	int getStr() const { return str; }
	//Returns the name of the warrior
	void setStr(int newStr) { str = newStr; }
	string getName() const { return name; }
	//Gets if it is employeed
	bool isHired() const { return employeed; }
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
	Noble(const string& nobleName) : name(nobleName) {}
	//Displays the noble and his warriors
	void display() const {
		cout << name << " has an army of " << warriors.size() << ":" << endl;
		for (size_t i = 0; i < warriors.size(); i++) {
			cout << "\t" << *warriors[i]<<endl;
		}
	}
	string getName() const { return name; }
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
	bool fire(Warrior& war) {
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
//Prints out the status of the Warriors and Nobles
void status(const vector<Warrior*>& war, const vector<Noble*>& nob) {
	cout << "Status" << endl << "=====" << endl <<"Nobles:" << endl;
	for (size_t i = 0; i < nob.size(); i++) {
		nob[i]->display();
	}
	if (nob.size() == 0) { cout << "NONE" << endl; }
	cout << "Unemployed Warriors" << endl;
	bool allEmployed = true;
	for (size_t i = 0; i < war.size(); i++) {
		if (!war[i]->isHired()) {
			cout << *war[i] << endl;
			allEmployed = false;
		}
	}
	if (allEmployed) {
		cout << "NONE" << endl;
	}
	cout << endl;//Just to make it easier to read
}
//Finds the noble using its name, returns nullptr if not found
Noble* findNoble(const vector<Noble*>& noble, const string& nobName) {
	for (size_t i = 0; i < noble.size(); i++) {
		if (noble[i]->getName() == nobName) { return noble[i]; }
	}
	return nullptr;
}
//Find the warrior using its name, returns nullptr if not found
Warrior* findWarrior(const vector<Warrior*>& war, const string& warName) {
	for (size_t i = 0; i < war.size(); i++) {
		if (war[i]->getName() == warName) { return war[i]; }
	}
	return nullptr;
}

int main() {
	ifstream myFile("nobleWarriors.txt"); // Checks if nobleWarriors is a file
	if (!myFile) {
		cerr << "Could not open nobleWarriors.txt" << endl;
		exit(1);
	}
	vector<Warrior*> warriors;
	vector<Noble*> nobles;
	string command, name, warriorName, nobleName, challenger;
	int str;
	while (myFile >> command) {
		//The command Status prints the vector
		if (command == "Status") {
			status(warriors, nobles);
		}
		//The command Warrior creates an instance of a Warrior and adds him on to the vector
		else if (command == "Warrior") {
			myFile >> name >> str;
			Warrior *newWarrior = new Warrior(name, str);
			warriors.push_back(newWarrior);
		}
		//The command Noble creates a noble on the heap and adds it into the vector
		else if (command == "Noble") {
			myFile >> name;
			Noble *newNoble = new Noble(name);
			nobles.push_back(newNoble);
		}
		//Given a Noble and a warrior it will use that nobles hire method (could fail if Warrior is hired already)
		else if (command == "Hire") {
			//Find that noble and use its hire method
			myFile >> nobleName >> warriorName;
			Noble* nob = findNoble(nobles, nobleName);
			Warrior* war = findWarrior(warriors, warriorName);
			nob->hire(*war);
		}
		//Given a noble and a warrior it will use that noble's Fire method (could fail if not apart of that noble)
		else if (command == "Fire") {
			//Find that noble and use its fire method
			myFile >> nobleName >> warriorName;
			Noble* nob = findNoble(nobles, nobleName);
			Warrior* war = findWarrior(warriors, warriorName);
			nob->fire(*war);
		}
		//The command Battle takes two warrior names and finds them to fight each other
		else if (command == "Battle") {
			myFile >> nobleName >> challenger;
			Noble* nob = findNoble(nobles, nobleName);
			Noble* nob2 = findNoble(nobles, challenger);
			nob->battle(*nob2);
		}
		else if (command == "Clear") { //Cleans the space on the heap and clears the vector
			for (size_t i = 0; i < warriors.size(); i++) {
				delete warriors[i];
			}
			for (size_t i = 0; i < nobles.size(); i++) {
				delete nobles[i];
			}
			warriors.clear();
			nobles.clear();
		}
	}
	//Free up the space on the heap after its done
	for (size_t i = 0; i < warriors.size(); i++) {
		delete warriors[i];
	}
	for (size_t i = 0; i < nobles.size(); i++) {
		delete warriors[i];
	}
	warriors.clear();
	nobles.clear();
	myFile.close();
	return 0;
}