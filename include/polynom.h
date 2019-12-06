#pragma once
#include <iostream>

using namespace std;

struct Monom {
	double coef;
	int pow;
	Monom* next;

	Monom() { coef = 0; pow = 0; next = nullptr; }
	Monom(double _coef, int _pow);
	Monom(double _coef, int _pow, Monom* _next);
	Monom(const Monom& monom);

	bool operator==(const Monom& right);
};


class Polynom {
private:
	Monom* head;
	int size;
public:
	Polynom();
	Polynom(const Polynom& polynom);
	~Polynom();

	int getSize() { return size; }
	void clear();
	void insert(Monom monom);
	void insert(double coef, int pow);

	void merge(const Polynom& polynom);
	void pop_front();
	void push_front(Monom monom);
	void push_back(Monom monom);
	void del(Monom monom);
	bool find(int pow);

	int Calculate(int x);
	Polynom operator+(const Polynom& right) const;
	Polynom operator-(Polynom& right);
	Polynom operator*(const Polynom& right);
	Polynom operator*(const double& val) const;
	const Polynom& operator = (const Polynom& right);

	friend ostream& operator << (ostream& os, const Polynom& object);
};