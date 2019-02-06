#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

class Warrior {
	//prints out the warrior using << 
	friend ostream& operator<< (ostream& os, const Warrior& war) {
		os <<  "Warrior: " << war.name << ", weapon:  " << war.weapon;
		return os;
	}

	//findWarriors finds the warrior and returns the position they are in
	friend int findWarrior(const vector<Warrior>& war, const string& name) {
		for (size_t i = 0; i < war.size(); i++) {
			if (war[i].name == name) {
				return i;
			}
		}
	}
	
	//The weapon class consisting of the weapon's name and the weapons strength
	class Weapon {
		//Prints out the weapon using the <<
		friend ostream& operator<<(ostream& os, const Weapon& weapon) {
			os << weapon.name << ", " << weapon.str;
			return os;
		}

	public:
		Weapon(const int& weaponStr, const string& weaponName) : str(weaponStr), name(weaponName) {}
		
		//Gets the weapon str
		const int getStr() const { return str; }
		//Set the weapons str
		void setStr(const int& newStr) { str = newStr; }
	private:
		int str;
		string name;
	};

public:

	//The warrior class the makes a weapon using the weaponName and strength of the weapon as well as giving the warrior a name
	Warrior(const string& personName, const string& weaponName, const int& str) : name(personName), weapon(str, weaponName){}

	//Battle takes two warriors and makes them lose one of their str and gives multiple messages depending on what happened
	void battle(Warrior& opponent) {
		const int warStr = weapon.getStr(); // To prevent its str from being changed this way
		const int opponentStr = opponent.weapon.getStr(); //To prevent its str from being changed this way
		cout << name << " battles " << opponent.name << endl;
		if (warStr == 0 && opponentStr == 0) { //If they are both dead
			cout << "Oh, NO! They're both dead! Yuck!" << endl;
		}
		else if (warStr == 0) { //If warrior 1 is dead
			cout << "He's dead, " << opponent.name << endl;
		}
		else if (opponentStr == 0) { //If warrior 2 is dead
			cout << "He's dead, " << name << endl;
		}
		else if (warStr > opponentStr) { // If warrior 1 is stronger
			weapon.setStr(warStr - opponentStr);
			opponent.weapon.setStr(0);
			cout << name << " defeats " << opponent.name << endl;
		}
		else if (warStr < opponentStr) { //If warrior 2 is stronger
			opponent.weapon.setStr(opponentStr - warStr);
			weapon.setStr(0);
			cout << opponent.name << " defeats " << name << endl;
		}
		else { //If they have equal strengths
			weapon.setStr(0);
			opponent.weapon.setStr(0);
			cout << "Mutual Annihilation: " << name << " and " << opponent.name << " die at each other's hands" << endl;
		}
	}
private:
	string name;
	Weapon weapon;
};

//Prints the status of the warriors as long with the weapons
void status(const vector<Warrior>& war) {
	cout << "There are: " << war.size() << " warriors" << endl;
	for (size_t i = 0; i < war.size(); i++) {
		cout << war[i] << endl;
	}
}

int main() {
	vector<Warrior> warriors; //Fills vector full of Warriors
	ifstream myFile("warriors.txt"); // Checks if warriors is a file
	if (!myFile) {
		cerr << "Could not open warriors.txt" << endl;
		exit(1);
	}
	// Initializing variables that are created to fill warriors
	string command, name, weaponName, war1, war2;
	int strength;
	while (myFile >> command) {
		//The command Status prints the vector
		if (command == "Status") {
			status(warriors);
		}
		//The command Warrior creates an instance of a Warrior and adds him on to the vector
		if (command == "Warrior") {
			myFile >> name >> weaponName>> strength;
			Warrior newWarrior(name, weaponName, strength);
			warriors.push_back(newWarrior);
		}
		//The command Battle finds the warriors in the vector and makes them fight using the battle method
		if (command == "Battle") {
			myFile >> war1 >> war2;
			int warrior1 = findWarrior(warriors, war1); //finds position of warriors
			int challenger = findWarrior(warriors, war2); 
			warriors[warrior1].battle(warriors[challenger]);
		}
	}
	return 0;
}