//hw01.cpp
//Mohammed Iqbal 

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

//A warrior has a name and strength
struct Warrior {
	string name;
	int str;
};

//printVector prints the vectors size first then the warriors name and then strength
void printVector(const vector<Warrior>& war) {
	cout << "There are: " << war.size() << " warriors" << endl;
	for (size_t i = 0; i < war.size(); i++) {
		cout << "Warrior: " << war[i].name << ", strength: " << war[i].str << endl;
	}
}

//findWarriors finds the warrior and returns the position they are in
int findWarrior(const vector<Warrior>& war, const string& name) {
	for (size_t i = 0; i < war.size(); i++) {
		if (war[i].name == name) {
			return i;
		}
	}
}

//battle takes the vector of warriors and the position of the warriors and battles them producing different results
void battle(vector<Warrior>& war, const int& war1, const int& war2) {
	cout << war[war1].name << " battles " << war[war2].name << endl;
	if (war[war1].str == 0 && war[war2].str == 0){ //If they are both dead
		cout << "Oh, NO! They're both dead! Yuck!" << endl;
	}
	else if (war[war1].str == 0) { //If warrior 1 is dead
		cout << "He's dead, " << war[war2].name << endl;
	}
	else if (war[war2].str == 0) { //If warrior 2 is dead
		cout << "He's dead, " << war[war1].name << endl;
	}
	else if (war[war1].str > war[war2].str) { // If warrior 1 is stronger
		war[war1].str = war[war1].str - war[war2].str;
		war[war2].str = 0;
		cout << war[war1].name << " defeats " << war[war2].name << endl;
	}
	else if (war[war1].str < war[war2].str) { //If warrior 2 is stronger
		war[war2].str = war[war2].str - war[war1].str;
		war[war1].str = 0;
		cout << war[war2].name << " defeats " << war[war1].name << endl;
	}
	else { //If they have equal strengths
		war[war1].str = 0;
		war[war2].str = 0;
		cout << "Mutual Annihilation: " << war[war1].name << " and " 
			<< war[war2].name << " die at each other's hands" << endl;
	}
}

int main() {
	vector<Warrior> warriors; //Fills vector full of Warriors
	ifstream myFile("warriors.txt"); // Checks if warriors is a file
	if (!myFile) {
		cerr << "Could not open warriors.txt" << endl;
		exit(1);
	}
	// Initializing variables that are created to either fill warriors or battle
	string command;
	string name;
	int strength;
	string war1;
	string war2;
	//Does the 3 commands 
	while (myFile >> command) {
		//The command Status prints the vector
		if (command == "Status") { 
			printVector(warriors);
		}
		//The command Warrior creates an instance of a Warrior and adds him on to the vector
		if (command == "Warrior") { 
			myFile >> name >> strength;
			Warrior newWarrior;
			newWarrior.name = name;
			newWarrior.str = strength;
			warriors.push_back(newWarrior);
		}
		//The command Battle takes two warrior names and finds them to fight each other
		if (command == "Battle") {
			myFile >> war1 >> war2;  
			int war1pos = findWarrior(warriors, war1); //Finds the position of the first warrior
			int war2pos = findWarrior(warriors, war2); //Finds the position of the second warrior
			battle(warriors, war1pos, war2pos); //Makes the two warriors fight each other
		}
	}
	myFile.close();
	return 0;
}