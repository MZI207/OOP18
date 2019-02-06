#include <iostream>
#include <vector>
using namespace std;

class PrintedMaterial {
	friend ostream& operator<<(ostream& os, const PrintedMaterial& rhs) {
		os << rhs.numberOfPages;
		return os;
	}
public:
	PrintedMaterial(unsigned val) : numberOfPages(val) {}
	//virtual void displayNumPages() const { cout << numberOfPages; }
	virtual void displayNumPages() const = 0;
protected:
private:
	unsigned numberOfPages;
};
void PrintedMaterial::displayNumPages() const { cout << numberOfPages; }

class Magazine : public PrintedMaterial {
public:
	Magazine(unsigned val) : PrintedMaterial(val) {}
	void displayNumPages() const { 
		cout << "Magazine Pages: ";
		PrintedMaterial::displayNumPages();
		cout << endl;
	}
protected:
private:
};

class Book : public PrintedMaterial {
public:
	Book(unsigned val): PrintedMaterial(val) {}
	void displayNumPages() const { 
		cout << "Book Pages: ";
		PrintedMaterial::displayNumPages();
		cout << endl;
	}
protected:
private:
};

class TextBook : public Book {
	/*
	friend ostream& operator<<(ostream& os, const TextBook& rhs) {
		os << "Number of Pages: " << PrintedMaterial::getNumOfPages();
		os << " Number of Index Pages" << numOfIndexPages;
		return os;
	}
	*/
public:
	TextBook(unsigned val, unsigned index) : Book(val), numOfIndexPages(index) {}
	void displayNumPages() const {
		cout << "TextBook Pages: ";
		PrintedMaterial::displayNumPages();
		cout << " Index Pages: " << numOfIndexPages << endl;
	}
protected:

private:
	unsigned numOfIndexPages;
};

class Novel : public Book {
public:
	Novel(unsigned val) : Book(val) {}
	void displayNumPages() const {
		cout << "Novel Pages: ";
		PrintedMaterial::displayNumPages();
		cout << endl;
	}
protected:
private:
};

void displayNumberOfPages(const PrintedMaterial& pm) {
	pm.displayNumPages();
}

// tester/modeler code
int main(){
	TextBook t(5430,23);
	Novel n(213);
	Magazine m(6);
	Book b(200);
	//PrintedMaterial pm = t;
	//pm.displayNumPages();

	PrintedMaterial* pmPtr = &t;
	pmPtr->displayNumPages();
	vector<PrintedMaterial*> pmPtrs;
	pmPtrs.push_back(&t);
	pmPtrs.push_back(&n);
	pmPtrs.push_back(&m);
	pmPtrs.push_back(&b);
	for (size_t i = 0; i < pmPtrs.size(); i++) {
		pmPtrs[i]->displayNumPages();
	}
}