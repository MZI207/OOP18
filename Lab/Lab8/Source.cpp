#include <string>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;
/*
	Mohammed Iqbal
	mzi207
	testRational.cpp
	CS2124
	Implement the class Rational, so that the following program works.
 */
class Rational {
	friend istream& operator>>(istream& is, Rational& rat) {
		is >> rat.numerator >> rat.denominator;
		rat.normalize();
		return is;
	}
	friend ostream& operator<<(ostream& os, const Rational& rat) {
		os << rat.numerator;
		if (rat.denominator != 1) { os << "/" << rat.denominator; }
		return os;
	}
public:
	Rational(int num = 0, int den = 1) : numerator(num), denominator(den) {
		if (den == 0) { cerr << "Division by zero Error" << endl; }
		if (num  != 0 || den != 1) { normalize(); }
	}
	void normalize() {
		int gcf = greatestCommonDivisor(numerator, denominator);
		if (gcf!= 1) {
			numerator = numerator / gcf;
			denominator = denominator / gcf;
		}
	}
	Rational& operator+=(const Rational& rhs) {
		int lcm = (denominator * rhs.denominator) / greatestCommonDivisor(denominator, rhs.denominator);
		int lhsFactor = lcm / denominator;
		int rhsFactor = lcm / rhs.denominator;
		denominator = lcm;
		numerator = (numerator * lhsFactor) + (rhs.numerator * rhsFactor);
		return *this;
	}
	int getNumerator() const { return numerator; }
	int getDenominator() const { return denominator; }
	Rational& operator++() {
		numerator += 1;
		return *this;
	}
	Rational operator++(int dummy) {
		Rational holder = *this;
		*this += 1;
		return holder;
	}
	explicit operator bool() const {
		return numerator;
	}
private:
	int greatestCommonDivisor(int x, int y) {
		while (y != 0) {
			int temp = x % y;
			x = y;
			y = temp;
		}
		return x;
	}
	int numerator;
	int denominator;
};
Rational operator+(const Rational& lhs, const Rational& rhs) {
	Rational holder;
	holder += lhs;
	holder += rhs;
	return holder;
}
bool operator==(const Rational& lhs, const Rational& rhs) {
	return lhs.getNumerator() == rhs.getNumerator() && lhs.getDenominator() == rhs.getDenominator();
}
bool operator!=(const Rational& lhs, const Rational& rhs) {
	return lhs.getNumerator() != rhs.getNumerator() && lhs.getDenominator() != rhs.getDenominator();

}
Rational& operator--(Rational& rhs) {
	rhs += -1;
	return rhs;
}
Rational operator--(Rational& rhs, int dummy) {
	Rational holder = rhs;
	rhs += -1;
	return holder;
}
bool operator<(const Rational& lhs, const Rational& rhs) {
	return float(lhs.getNumerator() / lhs.getDenominator()) < float(rhs.getNumerator() / rhs.getDenominator());
}
bool operator>(const Rational& lhs, const Rational& rhs) {
	return float(lhs.getNumerator() / lhs.getDenominator()) > float(rhs.getNumerator() / rhs.getDenominator());
}
bool operator<=(const Rational& lhs, const Rational& rhs) {
	return float(lhs.getNumerator() / lhs.getDenominator()) <= float(rhs.getNumerator() / rhs.getDenominator());
}
bool operator>=(const Rational& lhs, const Rational& rhs) {
	return float(lhs.getNumerator() / lhs.getDenominator()) >= float(rhs.getNumerator() / rhs.getDenominator());
}
 // If usingtime allows use  separate compilation, otherwise just define the class below
 //#include "Rational.h"


// If usingtime allows after using separate compilation, then wrap the class in a namespace.
//using namespace CS2124;

int main() {
	Rational twoThirds(2, 3);
	cout << twoThirds << endl;

	Rational a, b;
	cout << "Input two rational numbers.\n";
	cout << "a: ";
	cin >> a;
	cout << "b: ";
	cin >> b;
	Rational one(1);

	cout << "a = " << a << endl;
	cout << "b = " << b << endl;
	cout << "one = " << one << endl;
	
	cout << "a += b: " << (a += b) << endl;	// Implement as member
	cout << "a = " << a << endl;
	
	// Implement as non-member, but not a friend
	cout << "a + one: " << (a + one) << endl;
	cout << "a == one: " << boolalpha << (a == one) << endl;
	
	// How does this manage to work?
	// It does NOT require writing another == operator. 
	cout << "1 == one: " << boolalpha << (1 == one) << endl;
	
	// Do not implement as friend.
	cout << "a != one: " << boolalpha << (a != one) << endl;
	
	cout << "a = " << a << endl;
	cout << "++a = " << (++a) << endl;
	cout << "a = " << a << endl;
	cout << "a++ = " << (a++) << endl;
	cout << "a = " << a << endl;
	cout << "--a = " << (--a) << endl;
	cout << "a = " << a << endl;
	cout << "a-- = " << (a--) << endl;
	cout << "a = " << a << endl;

	cout << "++ ++a = " << (++ ++a) << endl;
	cout << "a = " << a << endl;
	cout << "-- --a = " << (-- --a) << endl;
	cout << "a = " << a << endl;
	
	cout << "a++ ++ = " << (a++ ++) << endl;
	cout << "a = " << a << endl;
	//
	// Even though the above example, (a++ ++), compiled, the
	// following shouldn't.
	// But some compiler vendors might let it...  Is your compiler
	// doing the right thing?
	// cout << "a-- -- = " << (a-- --) << endl;
	// cout << "a = " << a << endl;


	if (Rational(1)) {
		cout << "1 is true" << endl;
	}
	else {
		cout << "1 is false" << endl;
	}
	if (Rational(0)) {
		cout << "0 is true" << endl;
	}
	else {
		cout << "0 is false" << endl;
	}
}