//Mohammed Iqbal
//mzi207
#include <string>
#include <vector>
#include <iostream>
using namespace std;

//Base class Noble
class Noble {
public:
	Noble(const string& name, int str = 0) :name(name), str(str) {}
	void battle(Noble& challenger) {
		int thisStr = str;//This Nobles str
		int cStr = challenger.str;//Challenger's str
		cout << name << " battles " << challenger.name << endl;
		if (thisStr == 0 && cStr == 0) { //If they are both dead
			cout << "Oh, NO! They're both dead! Yuck!" << endl;
		}

		else if (dead) { //If thisNoble is dead
			cout << "He's dead, " << challenger.name << endl;
		}
		else if (challenger.dead) { //If cNoble is dead
			cout << "He's dead, " << name << endl;
		}
		else if (thisStr > cStr) { // If thisNoble is stronger
			changeStr(cStr);
			challenger.changeStr(thisStr);
			challenger.dead = true;
			cout << name << " defeats " << challenger.name << endl;
		}
		else if (thisStr < cStr) {
			challenger.changeStr(thisStr);
			changeStr(cStr);
			dead = true;
			cout << challenger.name << " defeats " << name << endl;
		}
		else { //If they have equal strengths
			changeStr(0);
			challenger.changeStr(0);
			challenger.dead = true;
			dead = true;
			cout << "Mutual Annihilation: " << name << " and " << challenger.name << " die at each other's hands" << endl;
		}
	}
	string getName() const { return name; }
protected:
	virtual void changeStr(int val) = 0;
	bool isDead() const { return dead; }
	void addStr(int val) { str += val; }
	void setStr(int val) { str = val; }
	int getStr() const { return str; }
private:
	bool dead = false;
	string name;
	int str;
};
class Warrior {
public:
	Warrior(const string& name, int str):name(name), str(str) {}
	bool isDead() const { return !str; }
	void setStr(int val) { str = val; }
	int getStr() const { return str; }
	bool isHired() const { return boss; }
	void hire(Noble* nob) { boss = nob; }
	virtual void battleCry() const = 0;
protected:
	string getName() const { return name; }
	Noble* getBoss() const { return boss; }
private:
	Noble* boss = nullptr;
	string name;
	int str;
};

//Archer class derived from Warrior
class Archer : public Warrior {
public:
	Archer(const string& name, int str) : Warrior(name, str) {}
	void battleCry() const { cout << "TWANG! " << getName() << " says: Take that in the name of my lord, " << getBoss()->getName() << endl; }
private:

};

//Swordsman class derived from Warrior
class Swordsman : public Warrior {
public:
	Swordsman(const string& name, int str) : Warrior(name, str) {}
	void battleCry() const { cout << "CLANG! " << getName() << " says: Take that in the name of my lord, " << getBoss()->getName() << endl; }

private:

};

//Wizard class derived from Warrior
class Wizard : public Warrior {
public:
	Wizard(const string& name, int str) :Warrior(name, str) {}
	void battleCry() const { 
		cout << "POOF" << endl; 
	}

private:

};



//Lords derived from Nobles
class Lord :public Noble {
public:
	Lord(const string& name) : Noble(name), warriors(0) {}
	//Hires a Warrior ONLY TO THE LORDS
	bool hires(Warrior& war) {
		if (!isDead() && !war.isDead() && !war.isHired()) {
			warriors.push_back(&war);
			war.hire(this);
			addStr(war.getStr());
			return true;
		}
		return false;
	}
	void changeStr(int val) {
		for (size_t i = 0; i < warriors.size(); i++) {
			warriors[i]->battleCry();
		}
		if (getStr() < val) {setStr(0); }
		else {
			double ratio = float(1) - (float(getStr()) / float(val));
			for (size_t i = 0; i < warriors.size(); i++) {
				warriors[i]->setStr(warriors[i]->getStr() * ratio);
			}
			setStr(getStr() * ratio);
		}
	}
private:
	vector<Warrior*> warriors;
};

//PersonWithStrengthToFight derived from Nobles
class PersonWithStrengthToFight : public Noble {
public:
	PersonWithStrengthToFight(const string& name, int str):
		Noble(name, str){}
	void changeStr(int val) {
		if (getStr() < val) { setStr(0); }
		else { setStr(getStr() - val); }
	}
private:
};
int main() {
	Lord sam("Sam");
	Archer samantha("Samantha", 200);
	sam.hires(samantha);
	Lord joe("Joe");
	PersonWithStrengthToFight randy("Randolf the Elder", 250);
	joe.battle(randy);
	joe.battle(sam);
	
	Lord janet("Janet");
	Swordsman hardy("TuckTuckTheHardy", 100);
	Swordsman stout("TuckTuckTheStout", 80);
	janet.hires(hardy);
	janet.hires(stout);
	PersonWithStrengthToFight barclay("Barclay the Bold", 300);
	janet.battle(barclay);
	
	janet.hires(samantha);
	Archer pethora("Pethora", 50);
	Archer thora("Thorapleth", 60);
	Wizard merlin("Merlin", 150);
	janet.hires(pethora);
	janet.hires(thora);
	sam.hires(merlin);
	janet.battle(barclay);
	sam.battle(barclay);
	joe.battle(barclay);
	
	return 0;
}