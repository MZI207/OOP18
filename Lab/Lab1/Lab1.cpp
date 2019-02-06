#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

//vStringToString converts a vector of Strings into a String. Used primarily to see whats in the file right away.
void printvString(vector<string> vString) {
	string holder = "";
	for (int i = 0; i < vString.size(); i++) {
		cout << vString[i] + "\n";
	}
}

//Reading a file and converting it into a vector of strings
vector<string> readFile(string fileName) {
	ifstream ifs(fileName);
	vector<string> cTile;
	if (!ifs) {
		cerr << "Could not open this file. \n";
		exit(1);
	}
	string line;
	while (getline(ifs, line)) {
		cTile.push_back(line);
	}
	ifs.close();
	return cTile;
}

//CountAliveNeighbors returns the amount of alive neighbors near an area based on 8 neighbors 
//Neighbors vary depending on location, Situation have been checked with neighbors
int countAliveNeighbors(vector<string> vString, int xcor, int ycor) {
	int count = 0;
	if (xcor < vString.size() && vString[xcor + 1][ycor] == '*') {
		count++;
	}
	if (xcor < vString.size() && ycor != 0 && vString[xcor + 1][ycor - 1] == '*') {
		count++;
	}
	if (xcor < vString.size() && ycor < vString[0].size() && vString[xcor + 1][ycor + 1] == '*') {
		count++;
	}
	if (ycor != 0 && vString[xcor][ycor - 1] == '*') {
		count++;
	}
	if (ycor < vString[xcor].size() && vString[xcor][ycor + 1] == '*') {
		count++;
	}
	if (xcor != 0 && vString[xcor - 1][ycor] == '*') {
		count++;
	}
	if (xcor != 0 && ycor < vString[xcor].size() && vString[xcor - 1][ycor + 1] == '*') {
		count++;
	}
	if (xcor != 0 && ycor != 0 && vString[xcor - 1][ycor - 1] == '*') {
		count++;
	}
	return count;
}

//doOneGen does one Generation of Conways Game of Life
vector<string> doOneGen(vector<string> cTile) {
	vector<string> newCTile; 
	for (int i = 0; i < cTile.size(); i++) {
		newCTile.push_back(cTile[i]);
	}
	for (int i = 0; i < cTile.size() - 1; i++) {
		for (int j = 0; j < cTile[i].size() - 1; j++) {
			if ((countAliveNeighbors(cTile, i, j) < 2 || countAliveNeighbors(cTile, i, j) > 3) && cTile[i][j] == '*') {
				newCTile[i][j] = '-';
			}
			if (cTile[i][j] == '-' && countAliveNeighbors(cTile, i, j) == 3){
				newCTile[i][j] = '*';
			}
		}
	}
	return newCTile;
}

/*int main() {
	vector<string> conwaysGame = readFile("life.txt"); // Reads the file and becomes a Vstring
	cout << "Initial World" << endl;
	printvString(conwaysGame);
	//Generation 1
	cout << "Generation 1:" << endl;
	conwaysGame = doOneGen(conwaysGame);
	printvString(conwaysGame);
	//Generation 2
	cout << "Generation 2:" << endl;
	conwaysGame = doOneGen(conwaysGame);
	printvString(conwaysGame);
	//Generation 3
	cout << "Generation 3:" << endl;
	conwaysGame = doOneGen(conwaysGame);
	printvString(conwaysGame);
	//Generation 4
	cout << "Generation 4:" << endl;
	conwaysGame = doOneGen(conwaysGame);
	printvString(conwaysGame);
	//Generation 5
	cout << "Generation 5:" << endl;
	conwaysGame = doOneGen(conwaysGame);
	printvString(conwaysGame);
	//Generation 6
	cout << "Generation 6:" << endl;
	conwaysGame = doOneGen(conwaysGame);
	printvString(conwaysGame);
	//Generation 7
	cout << "Generation 7:" << endl;
	conwaysGame = doOneGen(conwaysGame);
	printvString(conwaysGame);
	//Generation 8
	cout << "Generation 8:" << endl;
	conwaysGame = doOneGen(conwaysGame);
	printvString(conwaysGame);
	//Generation 9 
	cout << "Generation 9:" << endl;
	conwaysGame = doOneGen(conwaysGame);
	printvString(conwaysGame);
	//Generation 10
	cout << "Generation 10:" << endl;
	conwaysGame = doOneGen(conwaysGame);
	printvString(conwaysGame);

	return 0;
}*/