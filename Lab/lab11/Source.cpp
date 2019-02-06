#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
using namespace std;

/*
  functions for use with CS2124 rec11
  -jbs
*/

// Node to be used a part of linked list
struct Node {
	Node(int data = 0, Node* next = nullptr) : data(data), next(next) {}
	int data;
	Node* next;
};

// listInsertHead: adds a data item to the beginning of a [possibly empty] list
void listInsertHead(Node*& headPtr, int entry) {
	headPtr = new Node(entry, headPtr);
}

// listClear: frees up all the nodes in a list
void listClear(Node*& headPtr) {
	while (headPtr) {
		Node* next = headPtr->next;
		delete headPtr;
		headPtr = next;
	}
}

// listBuild: constructs a list from a vector of data items. Note that
// you can use a curly-braced sequence.
// This may be useful for setting up test cases. Feel free to use it
// or not as you like. 
// Example of using would be:
//    Node* myList = listBuild({1, 4, 9, 16}); // builds a list of: 1 4 9 16
Node* listBuild(const vector<int>& vals) {
	Node* result = nullptr;
	for (size_t index = vals.size(); index > 0; --index) {
		listInsertHead(result, vals[index - 1]);
	}
	return result;
}

void splice(Node* other, Node* pos) {
	Node* tail = pos->next;
	pos->next = other;
	while (other->next) {
		other = other->next;
	}
	other->next = tail;
}

Node* isSublist(Node* subL,Node* list) {
	Node* const subHead = subL;
	Node* result = nullptr;
	Node* prev = list;
	while (list->next) {
		if (!subL) { return result; }
		else if (subL->data == list->data && !result) {
			result = list;
			prev = list;
			subL = subL->next;
		}
		else if (subL->data == list->data && result) { 
			subL = subL->next; 
			prev = list;
		}
		else if (subL->data != list->data && result) { 
			list = prev;
			subL = subHead; 
			result = nullptr;
		}
		list = list->next;
	}
	return result;
}

Node* sharedListBruteForce(Node* l1, Node* l2) {
	Node* l2OG = l2;
	while (!l1) {
		while (!l2) {
			if (l1 == l2) { return l1; }
			l2 = l2->next;
		}
		l2 = l2OG;
		l1 = l1->next;
	}
	return nullptr;
}

Node* sharedListUsingSet(Node*& l1, Node*& l2) {
	unordered_set<Node*> data;
	while (l1) {
		data.insert(l1);
		l1 = l1->next;
	}
	while (l2) {
		if (data.find(l2) != data.end()) { return l2; }
		l2 = l2->next;
	}
	return nullptr;
}
void printNodes(Node*& node) {
	const Node* holder = node;
	while (holder) {
		cout << holder->data << " ";
		holder = holder->next;
	}
	cout << endl;
}



int main() {
	//Task 1
	vector<int> a;
	a.push_back(5);
	a.push_back(7);
	a.push_back(9);
	a.push_back(1);
	Node* mainNode = listBuild(a);

	vector<int> b;
	b.push_back(6);
	b.push_back(3);
	b.push_back(2);
	Node* node2 = listBuild(b);

	Node* mainNode7 = mainNode->next;
	printNodes(mainNode);
	printNodes(node2);
	splice(node2 , mainNode7);
	printNodes(mainNode);
	printNodes(node2);

	//Task 2
	cout << "Task 2" << endl << endl;
	listClear(mainNode);
	vector<int> c;
	c.push_back(1);
	c.push_back(2);
	c.push_back(3);
	c.push_back(4);
	c.push_back(5);
	c.push_back(6);
	mainNode = listBuild(c);
	cout << "Target: ";
	printNodes(mainNode);
	cout << endl;

	cout << "Attempt match:";
	vector<int> testV1;
	testV1.push_back(1);
	Node* test1 = listBuild(testV1);
	printNodes(test1);
	printNodes(mainNode);
	Node* result1 = isSublist(test1, mainNode);
	if (!result1) { cout << "Failled to match" << endl; }
	else { cout << endl; }

	cout << "Attempt match:";
	vector<int> testV2;
	testV2.push_back(3);
	testV2.push_back(9);
	Node* test2 = listBuild(testV2);
	printNodes(test2);
	printNodes(mainNode);
	Node* result2 = isSublist(test2, mainNode);
	if (!result2) { cout << "Failled to match" << endl; }
	else { cout << endl; }

	cout << endl << "Attempt match:";
	vector<int> testV3;
	testV3.push_back(2);
	testV3.push_back(3);
	Node* test3 = listBuild(testV3);
	printNodes(test3);
	listClear(mainNode);
	b.clear();
	b.push_back(2);
	b.push_back(3);
	b.push_back(2);
	b.push_back(3);
	b.push_back(2);
	b.push_back(4);
	b.push_back(5);
	b.push_back(6);
	mainNode = listBuild(b);
	printNodes(mainNode);
	Node* result3 = isSublist(test3, mainNode);
	if (!result3) { cout << "Failled to match" << endl; }
	else { cout << endl; }

	//Task 3
	cout << "Task 3" << endl << endl;
	vector<int> nums;
	nums.push_back(1);
	nums.push_back(2);
	nums.push_back(3);
	nums.push_back(4);
	nums.push_back(5);

	vector<int> nums2;
	Node* numNode1 = listBuild(nums);
	Node* numNode2 = numNode1->next->next->next;
	printNodes(numNode1);
	printNodes(numNode2);
	Node* result = sharedListBruteForce(numNode1, numNode2);
	printNodes(result);
	cout << "That brute force worked" << endl;
	cout << "How about a set" << endl << endl;
	printNodes(numNode1);
	
	Node* resultSet = sharedListUsingSet(numNode1, numNode2);
	printNodes(resultSet);

	return 0;
}