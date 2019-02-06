#include <iostream>
#include <vector>
#include <fstream>
#include <list>
#include <string>
#include <algorithm>
#include <set>
#include <map>
using namespace std;
//Task 8
void printList(const list<int>& li) {
	cout << "Printing list via iterators in printList:" << endl;
	for (list<int>::const_iterator iter = li.begin();
		iter != li.end(); ++iter) {
		cout << *iter << " ";
	}
	cout << endl;
}
//Task 9 
void printListRanged(const list<int>& li) {
	cout << "Printing list via iterators in printListRanged:" << endl;
	for (const int x: li) {
		cout << x << " ";
	}
	cout << endl;
}
//Task 11
void printListSkip(const list<int>& li) {
	cout << "Printing list via iterators int printListSkip but skipping every other" << endl;
	for (auto iter = li.begin(); iter != li.end(); ++++iter) {
		cout << *iter << " ";
	}
	cout << endl;
}
//Task 12
list<int>::const_iterator find(const list<int>& li, int val) {
	for (list<int>::const_iterator iter = li.begin();
		iter != li.end(); ++iter) {
		if (*iter == val) {
			return iter;
		}
	}
	return li.end();
}
//Task 13
auto findAuto(const list<int>& li, int val) {
	for (auto iter = li.begin();
		iter != li.end(); ++iter) {
		if (*iter == val) {
			return iter;
		}
	}
	return li.end();
}
//Task 15
bool isEven(int val) { return val % 2 == 0; }
//Task 16
class isEvenClass {
public:
	isEvenClass(){}
	bool operator()(int val) const { return val % 2 == 0; }
private:

};

//Task 19
auto ourFind(const list<int>::iterator& start, 
	const list<int>::iterator& end, int val) {
	cout << "Our find method, finding " << val << endl;
	for (auto iter = start; iter != end; ++iter) {
		if (*iter == val) { return iter; }
	}
	return end;
}
//Task20
template <class T>
auto ourFind(const T& start, const T& end, int val) {
	cout << "Our template find method, finding " << val << endl;
	for (auto iter = start; iter != end; ++iter) {
		if (*iter == val) { return iter; }
	}
	return end;
}
int main() {
	//Task 1
	vector<int> vectInt = { 0,10,6,4,8,2 };
	cout << "Vector of Ints:" << endl;
	for (int x : vectInt) {
		cout << x << " ";
	}
	cout << endl;
	//Task 2
	list<int> listInt(vectInt.begin(), vectInt.end());
	cout << "List of Ints: "<< endl;
	for (int x : listInt) {
		cout << x << " ";
	}
	cout << endl;
	//Task 3
	cout << "Sorting vector of Ints: " << endl;
	sort(vectInt.begin(), vectInt.end());
	for (int x : vectInt) {
		cout << x << " ";
	}
	cout << endl;
	
	listInt.sort();
	cout << "Sorting List of Ints: " << endl;
	for (int x : listInt) {
		cout << x << " ";
	}
	cout << endl;
	//Task 4
	cout << "Looping over every other element in Vector of Ints:" << endl;
	for (size_t i = 0; i < vectInt.size(); i+=2) {
		cout << vectInt[i] << " ";
	}
	cout << endl;
	//Task 5
	/*Doesn't compile
	cout << "Looping over every other element in Vector of Ints:";
	for (size_t i = 0; i < listInt.size(); i+=2) {
		cout << listInt[i] << " ";
	}
	*/
	//Task 6
	cout << "Looping over every other element in Vector of Ints " << 
		"but with iterators:" << endl;
	//Using auto would be easier but its says not to :/
	for (vector<int>::iterator iter = vectInt.begin(); 
		iter != vectInt.end(); iter += 2) {
		cout << *iter << " ";
	}
	cout << endl;
	//Task 7
	cout << "Looping over every other element in List of Ints " <<
		"but with iterators:" << endl;
	for (list<int>::iterator iter = listInt.begin();
		iter != listInt.end(); ++++iter) {
		cout << *iter << " ";
	}
	cout << endl;
	//Task 8
	listInt.sort();
	cout << "Sorting List of Ints: " << endl;
	for (int x : listInt) {
		cout << x << " ";
	}
	cout << endl;
	//Task 9
	printList(listInt);
	//Task 10
	printListRanged(listInt);
	//Task 11
	printListSkip(listInt);
	//Task 12
	//Should work
	cout << "Finding the iterator containing 2 in listInt using find" << endl;
	cout << *find(listInt, 2) << endl;
	//Shouldn't work
	cout << "Finding the iterator containing 3 in listInt using find" << endl;
	//cout << *find(listInt, 3) << endl;
	cout << "returns last item in listInt" << endl;

	//Task 13
	cout << "Finding the iterator containing 2 in listInt using findAuto" << endl;
	cout << *findAuto(listInt, 2) << endl;
	//Shouldn't work
	cout << "Finding the iterator containing 3 in listInt using findAuto" << endl;
	//cout << *find(listInt, 3) << endl;
	cout << "returns last item in listInt" << endl;

	//Task 14
	cout << "Finding 2 usng the find func given by STL" << endl;
	cout << *find(listInt.begin(), listInt.end(), 2) << endl;

	//Task 15
	cout << "Finding the first even number in the vector" << endl;
	cout << *find_if(vectInt.begin(), vectInt.end(), isEven) << endl;

	cout << "Finding the first even number in the list" << endl;
	cout << *find_if(listInt.begin(), listInt.end(), isEven) << endl;
	//Task 16
	cout << boolalpha;
	isEvenClass isEvenFunctor;
	cout << *find_if(listInt.begin(), listInt.end(), isEvenFunctor) << endl;
	//Task 17
	int x = [] (list<int>::iterator start, list<int>::iterator end) -> int {
		for (auto iter = start; iter != end; ++iter) {
			if (isEven(*iter)) {
				return *iter;
			}
		}
		return *end;
	}(listInt.begin(), listInt.end());
	cout << "Finding the first even number in the list using lambda" << endl;
	cout << x << endl;
	//Task 18
	int arr[6];
	copy(vectInt.begin(), vectInt.end(), arr);
	cout << "Printing arr" << endl;
	for (size_t i = 0; i < 6; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
	cout << "Finding 2 in the array" << endl;
	cout << *find(arr, arr + 6, 2) << endl;
	
	//Task 19
	cout << *ourFind(listInt.begin(), listInt.end(), 2) <<  endl;
	// Task 20
	cout << *ourFind(vectInt.begin(), vectInt.end(), 2) << endl;
	//Task 21
	ifstream myFile("pooh-nopunc.txt");
	if (!myFile) { 
		cerr << "File Not found";
		exit(1);
	}
	vector<string> words;
	string word;
	while (myFile >> word) {
		if (find(words.begin(), words.end(), word) == words.end()) {
			words.push_back(word);
		}
	}
	cout << "Words size: " << words.size() << endl << "Words content:" << endl;
	for (size_t i = 0; i < words.size(); i++) {
		cout << words[i] << " ";
	}
	cout << endl;
	myFile.close();
	//Task 22
	set<string> sWords;
	ifstream setmyFile("pooh-nopunc.txt");
	if (!setmyFile) {
		cerr << "File Not found";
		exit(1);
	}
	while (setmyFile >> word) {
		if (sWords.find(word) == sWords.end()) {
			sWords.insert(word);
		}
	}
	cout << "Set Words size: " << words.size() << endl << "Set Words content:" << endl;
	for (const string& x: sWords){
		cout << x << " ";
	}
	cout << endl;
	setmyFile.close();
	//Task 23
	map<string, vector<int>> wordMap;
	ifstream mapWordsFile("pooh-nopunc.txt");
	if (!mapWordsFile) {
		cerr << "File Not found";
		exit(1);
	}
	int pos = 0;
	while (mapWordsFile >> word) {
		wordMap[word];
		wordMap[word].push_back(pos);
		pos++;
	}
	cout << "Word Map contents:" << endl;
	for (const auto& p : wordMap) {
		cout << p.first << ":";
		for (size_t i = 0; i < p.second.size(); i++) {
			cout << p.second[i] << " ";
		}
		cout << endl;
	}
	mapWordsFile.close();
	return 0;
}