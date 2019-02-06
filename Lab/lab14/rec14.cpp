#include <iostream>
#include <vector>
#include <list>
#include <stdexcept>
using namespace std;

struct Node {
	Node(int data = 0) :data(data) {}
	int data;
	Node* next = nullptr;
};
bool evenOnes(int bin) {
	if (bin == 0) { return true; }
	else if (bin == 1) { return false; }
	else if (bin % 2 == 1) {
		return !(evenOnes(bin / 2));
	}
	return evenOnes(bin / 2);
}

Node* sumofNodes(const Node* rhs, const Node* lhs) {
	if (!rhs && !lhs) { return nullptr; }
	else if (rhs && !lhs) { 
		Node* result = new Node(rhs->data); 
		result->next = sumofNodes(rhs->next, lhs);
		return result;
	}
	else if (!rhs && lhs) { 
		Node* result = new Node(lhs->data); 
		result->next = sumofNodes(rhs, lhs->next);
		return result;
	}
	else{
		Node* result = new Node(rhs->data + lhs->data);
		result->next = sumofNodes(rhs->next, lhs->next);
		return result;
	}
}
void printNodes(const Node* lhs) {
	const Node* pos = lhs;
	while (pos) {
		cout << pos->data << " ";
		pos = pos->next;
	}
}
struct TNode {
	TNode(int data = 0, TNode *left = nullptr, TNode *right = nullptr)
		: data(data), left(left), right(right) {}
	int data;
	TNode *left, *right;
};

int max(TNode* root) {
	if (!root) { throw out_of_range("Root is out of range/nullptr"); }
	int rhs, lhs;
	if (!root->right) { rhs = root->data; }
	else { rhs = max(root->right); }
	if (!root->left) {lhs = root->data;}
	else { lhs = max(root->left); }
	if (rhs < root->data) { rhs = root->data; }
	if (rhs > lhs) { return rhs; }
	return lhs;
}

bool palindrome(char* s, int size) {
	if (size <= 1 ) { return true; }
	if (*s != s[size - 1]) { return false; }
	return palindrome(s + 1, size - 2);
}

int towers(int disk, char start, char goal, char extra) {
	if (disk == 1) { return 1; }
	int val = 0;
	val += towers( disk - 1, start, extra, goal);
	val += towers(disk - 1, extra, start, goal);
	val += 1;
	return val;
}
void mystery(int n) {
	if (n > 1) {
		cout << 'a';
		mystery(n / 2);
		cout << 'b';
		mystery(n / 2);
	}
	cout << 'c';
}
int main() {
	//Task 1
	cout << boolalpha;
	cout << evenOnes(0) << endl;
	cout << evenOnes(1) << endl;
	cout << evenOnes(10) << endl;
	cout << evenOnes(11) << endl;
	cout << evenOnes(110) << endl;
	cout << evenOnes(101) << endl;
	cout << evenOnes(111) << endl;
	//Task 2
	Node* pointA = new Node(0);
	pointA->next  = new Node(1);
	pointA->next->next = new Node(3);

	Node* pointB = new Node(4);
	pointB->next = new Node(5);
	Node* result = sumofNodes(pointA, pointB);
	printNodes(result);
	cout << endl;
	//Task 3
	TNode a(1), b(2), c(4), d(8, &a, &b), e(16, &c), f(32, &d, &e);
	try {
		cout << max(&f) << endl;
	}
	catch(exception&){
		cerr << "Root is nullptr" << endl;
	}
	
	/*causes an exception
	TNode* l = nullptr;
	try {
		cout << max(l) << endl;
	}
	catch (exception&) {
		cerr << "Root is nullptr" << endl;
	}
	*/
	//Task 4
	char s[] = "racecar";
	if (palindrome(s, 7)) { cout << "yes" << endl; }
	//Task 5
	cout << towers(1, 'a', 'b', 'c') << endl;;
	cout << towers(2, 'a', 'b', 'c') << endl;
	cout << towers(3, 'a', 'b', 'c') << endl;
	cout << towers(4, 'a', 'b', 'c') << endl;
	//Task 6
	mystery(0); // c
	cout << endl;
	mystery(2); //  a c b c c
	cout << endl;
	mystery(3); // a c b c c
	cout << endl;
	mystery(5); // a (a c b c c) b (a c b c c) c 
	cout << endl;
	mystery(6); // a (a c b c c) b (a c b c c) 
	cout << endl;
	mystery(10); // a (a (a c b c c) b (a c b c c) c) b (a (a c b c c) b (a c b c c) c) c

	return 0;
}