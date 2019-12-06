#include <iostream>
#include "polynom.h"
using namespace std;

void inputPolynom(Polynom& a, int _number)
{
	for (int i = 0; i < _number; i++) {
		cout << "Введите коэффициент и степень " << i + 1 << " монома: ";
		double coef;
		int exp;
		cin >> coef >> exp;
		a.insert(coef, exp);
	}
}

int main()
{
	setlocale(LC_ALL, "Russian");
start:
	try {
		cout << "Первый полином: " << endl;
		cout << "Введите количество мономов: ";
		int number_of_monoms1;
		cin >> number_of_monoms1;
		Polynom a;
		inputPolynom(a, number_of_monoms1);

		cout << "Второй полином: " << endl;
		cout << "Введите количество мономов: ";
		int number_of_monoms2;
		cin >> number_of_monoms2;
		Polynom b;
		inputPolynom(b, number_of_monoms2);
		cout << "A: " << a << endl;
		cout << "B: " << b << endl;
		cout << "A + B: " << a + b << endl;
		cout << "A - B: " << a - b << endl;
		cout << "A * B: " << a * b << endl;
		cout << "Введите значение X: ";
		int x;
		cin >> x;
		cout << "А при х = " << x << ": " << a.Calculate(x) << endl;
		cout << "B при х = " << x << ": " << b.Calculate(x) << endl;
		cout << endl;
	}
	catch (string s) {
		cout << s << endl;
	}
	cout << "Вернуться к вводу данных?" << endl;
	cout << " 1. Да" << endl;
	cout << " 2. Нет" << endl;
	int choice2;
	cin >> choice2;
	switch (choice2) {
	case 1:
		system("cls");
		goto start;
	default:
		return 0;
	}
}
