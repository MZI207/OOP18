#include <iostream>
using namespace std;

class List {
	struct Node {
		Node() {}
		Node(int data) : data(data) {}
		Node* prior = nullptr;
		Node* next = nullptr;
		int data;
	};

	friend ostream& operator<<(ostream& os, const List& rhs) {
		Node* pos = rhs.head;
		while (pos != rhs.tail) {
			os << pos->data << " ";
			pos = pos->next;
		}
		if (rhs.tail) { os << pos->data << " "; }
		return os;
	}
public:
	List() {}
	void push_back(int data) {
		Node* holder = new Node(data);
		if (len) {
			holder->prior = tail;
			tail->next = holder;
			tail = holder;
		}
		else {
			head = holder;
			tail = holder;
		}
		len++;
	}
	int pop_back() {
		if (!len) { return 0; }
		int data = tail->data;
		Node* newTail = tail->prior;
		delete tail;
		tail = newTail;
		if (len != 1) { tail->next = nullptr; }
		len--;
		return data;
	}
	int front() {	return head->data;}
	int back() { return tail->data; }
	size_t size() const { return len; }
	void push_front(int data) {
		Node* holder = new Node(data);
		if (len) {
			holder->next = head;
			head->prior = holder;
			head = holder;
		}
		else {
			head = holder;
			tail = holder;
		}
		len++;
	}
	int pop_front() {
		if (!len) { return 0; }
		int data = head->data;
		Node* newHead = head->next;
		delete head;
		head = newHead;
		if (len != 1){ head->prior = nullptr; }
		else { head = nullptr; tail = nullptr; }
		len--;
		return data;
	}
	void clear() {
		while (head) {
			pop_front();
		}
	}
	int& operator[](int val) {
		int pos = 0;
		Node* nPos = head;
		while (val >= pos) {
			if (val == pos) {
				return nPos->data;
			}
			nPos = nPos->next;
			pos++;
		}
	}
	int operator[] (int val) const {
		int pos = 0;
		Node* nPos = head;
		while (val >= pos) {
			if (val == pos) {
				return nPos->data;
			}
			nPos = nPos->next;
			pos++;
		}
	}

	class Iterator {
	public:
		friend bool operator!=(const Iterator& lhs, const Iterator& rhs) {
			return lhs.where != rhs.where;
		}
		Iterator(Node* pos) : where(pos) {}
		Iterator& operator++() {
			where = where->next;
			return *this;
		}
		int& operator*() { return where->data; }
		friend class List;
	private:
		Node* where = nullptr;
	};

	Iterator begin() {
		Iterator result(head);
		return result;
	}

	Iterator begin() const { 
		Iterator result(head);
		return result;
	}

	Iterator end() const {
		if (tail && !tail->next) {
			Node* end = new Node();
			end->prior = tail;
			tail->next = end;
		}
		if (tail && tail->next) { return Iterator(tail->next); }
		return Iterator(tail);
	}

	Iterator end(){
		if (tail && !tail->next) {
			Node* end = new Node();
			end->prior = tail;
			tail->next = end;
		}
		if (tail && tail->next) { return Iterator(tail->next); }
		return Iterator(tail);
	}
	Iterator insert(Iterator pos, int data) {
		Node* holder = new Node(data);
		if (!pos.where) { head = holder; tail = holder; }
		//Just to make my life easier to read
		else if (pos.where == end().where) {
			tail->next = holder;
			holder->prior = tail;
			tail = holder; 
		}
		else if (!pos.where->prior) {
			head->prior = holder;
			holder->next = head;
			head = holder;
		}
		else {
			pos.where->next->prior = holder;
			pos.where->prior->next = holder;
		}
		len++;
		return Iterator(holder);
	}
	void erase(Iterator iter) {
		if (!len) { return; }
		else if (len == 1) { 
			head, tail = nullptr;
		}
		else if (iter.where == head) {head = iter.where->next; }
		else if (iter.where == tail) { tail = iter.where->prior; }
		else {
			iter.where->prior->next = iter.where->next;
			iter.where->next->prior = iter.where->prior;
		}
		delete iter.where;
		len--;
	}
private:
	size_t len = 0;
	Node* head = nullptr;
	Node* tail = nullptr;
};

void printListInfo(List& myList) {
	cout << "size: " << myList.size()
		<< ", front: " << myList.front()
		<< ", back(): " << myList.back()
		<< ", list: " << myList << endl;
}


int main() {
	// Task 1
	cout << "\n------Task One------\n";
	List myList;
	cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
	for (int i = 0; i < 10; ++i) {
		cout << "myList.push_back(" << i * i << ");\n";
		myList.push_back(i*i);
		printListInfo(myList);
	}
	cout << "===================\n";
	cout << "Remove the items with pop_back\n";
	while (myList.size()) {
		printListInfo(myList);
		myList.pop_back();
	}
	cout << "===================\n";
	// Task2
	cout << "\n------Task Two------\n";
	cout << "Fill empty list with push_front: i*i for i from 0 to 9\n";
	for (int i = 0; i < 10; ++i) {
		cout << "myList2.push_front(" << i * i << ");\n";
		myList.push_front(i*i);
		printListInfo(myList);
	}
	cout << "===================\n";
	cout << "Remove the items with pop_front\n";
	while (myList.size()) {
		printListInfo(myList);
		myList.pop_front();
	}
	cout << "===================\n";
	// Task3
	cout << "\n------Task Three------\n";
	cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
	for (int i = 0; i < 10; ++i) {
		myList.push_back(i*i);
	}
	printListInfo(myList);
	cout << "Now clear\n";
	myList.clear();
	cout << "Size: " << myList.size() << ", list: " << myList << endl;
	cout << "===================\n";
	// Task4
    cout << "\n------Task Four------\n";
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i)  myList.push_back(i*i);
    cout << "Display elements with op[]\n";
	for (size_t i = 0; i < myList.size(); ++i) {
		cout << myList[i] << ' ';
	}
	cout << endl;
    cout << "Add one to each element with op[]\n";
	for (size_t i = 0; i < myList.size(); ++i) { 
		myList[i] += 1; 
	}
    cout << "And print it out again with op[]\n";
    for (size_t i = 0; i < myList.size(); ++i) cout << myList[i] << ' ';
    cout << endl;
	// Task 5
	cout << "\n------Task Five------\n";
	cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
	myList.clear();
	for (int i = 0; i < 10; ++i)  myList.push_back(i*i);
	printListInfo(myList);
	cout << "Now display the elements in a ranged for\n";
	for (int x : myList) cout << x << ' ';
	cout << endl;
	cout << "And again using the iterator type directly:\n";
	for (List::Iterator iter = myList.begin(); iter != myList.end(); ++iter) {
		cout << *iter << ' ';
	}
	cout << endl;
	cout << "WOW!!! (I thought it was cool.)\n";
	// Task 6
	cout << "\n------Task Six------\n";
	cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
	myList.clear();
	for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
	printListInfo(myList);
	cout << "Filling an empty list with insert at begin(): "
		<< "i*i for i from 0 to 9\n";
	myList.clear();
	for (int i = 0; i < 10; ++i) myList.insert(myList.begin(), i*i);
	printListInfo(myList);
	// ***Need test for insert other than begin/end***
	cout << "===================\n";
	// Task 7
	cout << "\n------Task Seven------\n";
	cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
	myList.clear();
	for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
	cout << "Erasing the elements in the list, starting from the beginning\n";
	while (myList.size()) {
		printListInfo(myList);
		myList.erase( myList.begin() );
	}
	// ***Need test for erase other than begin/end***
	cout << "===================\n";


}