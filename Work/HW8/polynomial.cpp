/*
polynomial.cpp
Mohammed Iqbal
N11252745
mzi207
12/5/18
*/
#include <iostream>
#include <vector>
#include <cmath>
#include "polynomial.h"

using namespace std;
//Node Construnctor (takes a int and sets the data)
Polynomial::Node::Node(int val) : data(val) {}
//Polynomial takes a vector of ints (if none given, sets the vector
//as {0}) and creates a List filled with values
Polynomial::Polynomial(vector<int> coeff) : degree(coeff.size() - 1) {
	Node* pos = nullptr;
	Node* head = nullptr;
	for (int x : coeff) {
		if (pos) {
			pos->prev = new Node(x);
			pos->prev->next = pos;
			pos = pos->prev;
		}
		else {
			pos = new Node(x);
		}
		head = pos;
	}
	this->coeff = new Node();
	this->coeff->next = head;
	head->prev = this->coeff;
}
//Copy Constructor, creates a deep copy of the values in rhs
Polynomial::Polynomial(const Polynomial& rhs) {
	coeff = new Node();
	Node* pos = coeff;
	Node* posRhs = rhs.coeff->next;
	while (posRhs) {
		if (posRhs == rhs.coeff->next) { degree = 0; }
		else { degree++; }
		pos->next = new Node(posRhs->data);
		pos->next->prev = pos;
		pos = pos->next;
		posRhs = posRhs->next;
	}
}
//Destructor deletes everything within the list
Polynomial::~Polynomial() {
	Node* pos = coeff;
	while (pos) {
		pos = coeff->next;
		delete coeff;
		coeff = pos;
	}
	delete coeff;
}
//Assignment operator does the destructor + copy constructor
Polynomial Polynomial::operator=(const Polynomial& rhs) {
	Node* pos = coeff;
	while (pos) {
		pos = coeff->next;
		delete coeff;
		coeff = pos;
	}
	delete coeff;
	coeff = new Node();
	pos = coeff;
	Node* posRhs = rhs.coeff->next;
	while (posRhs) {
		if (posRhs == rhs.coeff->next) { degree = 0; }
		else { degree++; }
		pos->next = new Node(posRhs->data);
		pos->next->prev = pos;
		pos = pos->next;
		posRhs = posRhs->next;
	}
	return *this;
}
//Output operator (displays)
ostream& operator<<(ostream& os, const Polynomial& rhs) {
	Polynomial::Node* pos = rhs.coeff;
	//Gets to the last position first then goes backwards to have it in
	//decreasing exponent order
	while (pos->next) {
		pos = pos->next;
	}
	int degree = rhs.degree;
	while (pos != rhs.coeff) {
		//if there is a zero it is skipped (except when there are no coeff and constant = 0)
		if (pos->data || !rhs.degree) {
			//Just in case there is zero at the tail end 
			if (pos == rhs.coeff->next) { os << pos->data; }
			//Fixes the exponent over here
			else if (degree == 1) { os << pos->data << "x" << " + "; }
			else { os << pos->data << "x^" << degree << " + "; }
		}
		pos = pos->prev;
		degree--;
	}
	return os;
}
//operator+(Polynomial) adds the values together and returns a brand new Polynomial
Polynomial Polynomial::operator+(const Polynomial& rhs) {
	Polynomial result = *this;
	Node* posRhs = rhs.coeff->next;
	Node* pos = result.coeff->next;
	while(posRhs){
		pos->data += posRhs->data;
		if (!pos->next && posRhs->next) { 
			pos->next = new Node(); 
			pos->next->prev = pos;
			pos->next->data = 0;
		}
		pos = pos->next;
		posRhs = posRhs->next;
	}
	return result;
}
//operator+= adds the original value with the right hand side
Polynomial Polynomial::operator+=(const Polynomial& rhs){
	*this = *this + rhs;
	return *this;
}

Polynomial operator+(const Polynomial& lhs, const Polynomial& rhs) {
	Polynomial result = lhs;
	result = result + rhs;
	return result;
}
//operator== checks if they equal and returns true if they are
bool Polynomial::operator==(const Polynomial& rhs) const {
	Node* pos = coeff->next;
	Node* posRhs = rhs.coeff->next;
	while (pos) {
		if (!posRhs) { return false; }
		else if (pos->data != posRhs->data) { return false; }
		pos = pos->next;
		posRhs = posRhs->next;
	}
	return true;
}
//operator!= checks if they are not equal and returns false if they are equal
bool Polynomial::operator!=(const Polynomial& rhs) const {
	return !(*this == rhs);
}
//Evaluate takes a double and substitutes it within the polynomial 
int Polynomial::evaluate(double val) const {
	Node* pos = coeff->next;
	double result = 0;
	int expo = 0;
	while (pos) {
		if (pos == coeff->next) { result += pos->data; }//Adds the constant
		else {
			//pow is the exponent function as C++ doesn't have a default one
			result += pos->data * pow(val, expo);
		}
		pos = pos->next;
		expo++;
	}
	return result;
}
