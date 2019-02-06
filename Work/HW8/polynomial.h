#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H
/*
polynomial.h
Mohammed Iqbal
N11252745
mzi207
12/5/18
*/
#include <iostream>
#include <vector>
class Polynomial {
	friend std::ostream& operator<<(std::ostream& os, const Polynomial& rhs);
	struct Node {
		Node() {}
		Node(int val);
		int data;
		Node* prev = nullptr;
		Node* next = nullptr;
	};
public:
	Polynomial(std::vector<int> data = {0});
	~Polynomial();
	Polynomial(const Polynomial& rhs);
	Polynomial operator+(const Polynomial& rhs);
	Polynomial operator=(const Polynomial& rhs);
	Polynomial operator+=(const Polynomial& rhs);
	bool operator==(const Polynomial& rhs) const;
	bool operator!=(const Polynomial& rhs) const;
	int evaluate(double val) const;
private:
	Node* coeff;
	int degree;
};
Polynomial operator+(const Polynomial& lhs, const Polynomial& rhs);
#endif // !POLYNOMIAL_H
