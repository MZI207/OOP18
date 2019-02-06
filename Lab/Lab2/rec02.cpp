#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

//Class for hydrocarbons consisting of 3 variables
struct Hydrocarbon {
	vector<string> name;
	int carbonAtoms;
	int hydrogenAtoms;
};

//Opens the file and keeps asking for a file until one works
void openFile(ifstream& myFile) {
	string fileName;
	bool validFile = false;
	while (!validFile) {
		cout << "Insert file name" << endl;
		cin >> fileName;
		myFile.open(fileName);
		if (!myFile) {
			cout << "Invalid file name" << endl;
			myFile.clear();
		}
		else {
			validFile = true;
		}
	}
}

//Prints the vector
void printVector(const vector<Hydrocarbon>& hydro) {
	for (size_t i = 0; i < hydro.size(); i++) {
		cout << "C" << hydro[i].carbonAtoms << "H" << hydro[i].hydrogenAtoms << " ";
		for (size_t j = 0; j < hydro[i].name.size(); j++) {
			cout << hydro[i].name[j] << ", ";
		}
		cout << endl;
	}
	cout << endl;
}


//Fills a vector with hydrocarbons
void fillVector(ifstream& myFile, vector<Hydrocarbon>& hydro) {
	string name;
	int carbons;
	int hydrogen;
	char c;
	char h;
	while (myFile >> name >> c >> carbons >> h >> hydrogen) {
		Hydrocarbon element;
		bool added = false;
		int pos = 0;
		//Checks if a similar cXhY has been put in
		while ((!added) && (pos < hydro.size())) {
			if (hydro[pos].carbonAtoms == carbons && hydro[pos].hydrogenAtoms == hydrogen) {
				hydro[pos].name.push_back(name);
				added = true;
			}
			pos += 1;
		}
		
		if (!added) {
			element.name.push_back(name);
			element.carbonAtoms = carbons;
			element.hydrogenAtoms = hydrogen;
			hydro.push_back(element);
		}
	}
}

//Sorts a vector of hydrocarbons using the amount of carbons it has or by hydrogen (if they carbons are equal)
void sortVector(vector<Hydrocarbon>& hydro) {
	for (int x = 0; x < hydro.size(); x++) {
		for (int i = 0; i < hydro.size(); i++) {
			int min_index = i;
			for (int j = i + 1; j < hydro.size(); j++) {
				if (hydro[j].carbonAtoms < hydro[i].carbonAtoms) {
					min_index = j;
				}
				else if (hydro[j].carbonAtoms == hydro[i].carbonAtoms && hydro[j].hydrogenAtoms < hydro[i].hydrogenAtoms) {
					min_index = j;
				}
			}
			Hydrocarbon holder = hydro[i];
			hydro[i] = hydro[min_index];
			hydro[min_index] = holder;
		}
	}
}


int main() {
	vector<Hydrocarbon> hydrocarbons;
	ifstream myFile;
	openFile(myFile);
	fillVector(myFile, hydrocarbons);
	printVector(hydrocarbons);
	cout << endl;
	sortVector(hydrocarbons);
	printVector(hydrocarbons);
	myFile.close();
	return 0;
}