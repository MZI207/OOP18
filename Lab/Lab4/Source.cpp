#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

struct Tile {
	bool isVisible; 
	bool isBomb;
	int number;
};

class Minesweeper {
public:
	Minesweeper() {

	}

private:
	vector<vector<Tile>> mines;
};

int main() {

	return 0;
}