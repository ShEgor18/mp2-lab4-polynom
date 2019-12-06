#include "polynom.h"
#include <cmath>
#define eps 0.00000001



Monom::Monom(double _coef, int _pow)
{
	if (_pow > 999 || _pow < 0) {
		throw (string)"Ошибка степени!";
	}
	coef = _coef;
	pow = _pow;
	next = 0;
}

Monom::Monom(double _coef, int _pow, Monom* _next)
{
	coef = _coef;
	pow = _pow;
	next = _next;
}

Monom::Monom(const Monom& monom)
{
	coef = monom.coef;
	pow = monom.pow;
	next = monom.next;
}

bool Monom::operator==(const Monom& right)
{
	if (pow == right.pow && abs(coef - right.coef) < eps) return true;
	else return false;
}

Polynom::Polynom()
{
	size = 0;
	head = 0;
}

Polynom::Polynom(const Polynom& polynom) : Polynom()
{
	Monom* tmp = polynom.head;
	while (tmp != 0)
	{
		this->insert(tmp->coef, tmp->pow);
		tmp = tmp->next;
	}
	size = polynom.size;
}



Polynom::~Polynom()
{
	clear();
}

inline void Polynom::clear()
{
	while (size && head != 0) {
		pop_front();
	}
}

void Polynom::merge(const Polynom& pol)
{
	Polynom tmp;

	Monom* curr1 = (this)->head;
	Monom* curr2 = pol.head;

	while (curr1 != 0 && curr2 != 0) {
		if (curr1->pow <= curr2->pow) {
			Monom newMonom(*curr1);
			newMonom.next = 0;
			tmp.push_back(newMonom);
			curr1 = curr1->next;
		}
		else {
			Monom newMonom(*curr2);
			newMonom.next = 0;
			tmp.push_back(newMonom);
			curr2 = curr2->next;
		}
	}
	while (curr1 != 0) {
		Monom newMonom(*curr1);
		newMonom.next = 0;
		tmp.push_back(newMonom);
		curr1 = curr1->next;
	}
	while (curr2 != 0) {
		Monom newMonom(*curr2);
		newMonom.next = 0;
		tmp.push_back(newMonom);
		curr2 = curr2->next;
	}
	*this = tmp;

	tmp.head = 0;
	tmp.size = 0;
}

inline void Polynom::pop_front()
{
	Monom* tmp = head;
	head = head->next;
	delete tmp;
	size--;
}

inline void Polynom::push_front(Monom monom)
{
	head = new Monom(monom.coef, monom.pow, head);
	size++;
}

void Polynom::push_back(Monom monom)
{
	if (head == 0) {
		head = new Monom(monom);
	}
	else {
		Monom* curr = head;
		while (curr->next != 0) {
			curr = curr->next;
		}
		curr->next = new Monom(monom);
	}
	size++;
}

void Polynom::insert(Monom monom)
{
	if (head == 0 || head->pow > monom.pow) {
		push_front(monom);
		return;
	}

	Monom* curr = head;
	while (curr->next != 0 && curr->next->pow <= monom.pow && curr->pow <= monom.pow) {
		curr = curr->next;
	}
	if (curr->pow == monom.pow) {
		curr->coef += monom.coef;
		if (abs(curr->coef) < eps) {
			del(*curr);
		}
		return;
	}
	Monom* newObject = new Monom(monom);
	newObject->next = curr->next;
	curr->next = newObject;
	size++;
}

void Polynom::insert(double coef, int pow)
{
	Monom monom(coef, pow);
	if (head == 0 || head->pow > monom.pow) {
		push_front(monom);
		return;
	}

	Monom* curr = head;
	while (curr->next != 0 && curr->next->pow <= monom.pow && curr->pow <= monom.pow) {
		curr = curr->next;
	}
	if (curr->pow == monom.pow) {
		curr->coef += monom.coef;
		if (abs(curr->coef) < eps) {
			del(*curr);
		}
		return;
	}
	Monom* newObject = new Monom(monom);
	newObject->next = curr->next;
	curr->next = newObject;
	size++;
}

void Polynom::del(Monom monom)
{
	Monom* curr = head;
	if (curr->pow == monom.pow && abs(curr->coef - monom.coef) < eps) {
		pop_front();
		return;
	}
	while (curr->next != 0 && curr->next->pow != monom.pow) {
		curr = curr->next;
	}
	Monom* tmp = curr->next->next;
	delete curr->next;
	curr->next = tmp;
	size--;
}

bool Polynom::find(int pow)
{
	Monom* curr = head;
	while (curr != 0) {
		if (curr->pow == pow) {
			return true;
		}
		curr = curr->next;
	}
	return false;
}

Polynom Polynom::operator*(const double& val) const
{
	Polynom tmp;
	Monom* a = this->head;
	while (a != 0) {
		tmp.insert(a->coef, a->pow);
		a = a->next;
	}
	Monom* temp = tmp.head;
	while (temp != 0) {
		temp->coef = temp->coef * val;
		temp = temp->next;
	}
	return tmp;
}

const Polynom& Polynom::operator = (const Polynom& right)
{
	if (this->head != right.head) {
		clear();
		Monom* tmp = right.head;
		while (tmp != 0) {
			insert(tmp->coef, tmp->pow);
			tmp = tmp->next;
		}

	}
	return *this;
}

Polynom Polynom::operator + (const Polynom& right) const
{
	Polynom curr;
	Monom* thisHead = this->head;
	while (thisHead != 0) {
		curr.insert(thisHead->coef, thisHead->pow);
		thisHead = thisHead->next;
	}

	Monom* rightHead = right.head;
	while (rightHead != 0) {
		curr.insert(rightHead->coef, rightHead->pow);
		rightHead = rightHead->next;
	}
	return curr;
}

Polynom Polynom::operator * (const Polynom& right)
{
	Polynom curr;
	Monom* f = head;
	Monom* s = right.head;
	while (f != 0) {
		s = right.head;
		while (s != 0) 
		{
			double coef = s->coef * f->coef;
			int pow = s->pow + f->pow;
			curr.insert(coef, pow);
			s = s->next;
		}
		f = f->next;
	}
	return curr;
}

Polynom Polynom::operator-(Polynom& right)
{
	Polynom c = right * (-1.);
	return *this + c;
}

int Polynom::Calculate(int x)
{
	Monom* tmp = head;
	int res = 0;

	while (tmp != 0)
	{
		res += tmp->coef * pow(x,tmp->pow);
		tmp = tmp->next;
	}
	return res;
}

ostream& operator << (ostream& os, const Polynom& object)
{
	if (object.head == 0) {
		os << 0;
		return os;
	}
	Monom* temp = object.head;
	while (temp != 0)
	{
		if (temp->coef > 0) {
			os << temp->coef << " ";
		}
		else {
			os << "(" << temp->coef << ") ";
		}
		if (temp->pow != 0) {
			os << "* x^" << temp->pow << " ";
		}
		if (temp->next != 0) {
			os << "+ ";
		}
		temp = temp->next;
	}
	return os;
}
