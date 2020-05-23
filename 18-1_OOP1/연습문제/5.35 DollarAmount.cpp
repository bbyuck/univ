#include <iostream>
#include <string>
#include <iomanip>
#include "DollarAmount.h"
#include <cmath>
using namespace std;

int main() {
	DollarAmount d1{ 12345 };
	DollarAmount d2{ 1576 };

	cout << "After adding d2 (" << d2.toString() << ") into d1 (" << d1.toString() << "), d1 = ";
	d1.add(d2); // add ����Լ� ȣ��
	cout << d1.toString() << "\n";

	cout << "After subtracting d2 (" << d2.toString() << ") from d1 (" << d1.toString() << "), d1 = ";
	d1.subtract(d2);
	cout << d1.toString() << "\n";

	cout << "After subtracting d1 (" << d1.toString() << ") from d2 (" << d2.toString() << "), d2 = ";
	d2.subtract(d1);
	cout << d2.toString() << "\n"; // ����Լ� ��� test

	cout << "Enter integer interest rate and divisor. For example:\n" // prompt �� ���� UI
		<< "for     2%, enter:    2 100\n"
		<< "for   2.3%, enter:   23 1000\n"
		<< "for  2.37%, enter:  237 10000\n"
		<< "for 2.375%, enter: 2375 100000\n ";


	int rate; // rate ��������
	int divisor; // divisor ��������
	cin >> rate >> divisor;

	double ratepercent{ static_cast<double>(rate) / divisor * 100 };

	cout << "\nInterest rate : " << ratepercent << (divisor == 100 ? ".0" : "") << "%"; // int�� ���� rate ��� rate�� �Ͻ������� double������ ĳ������ �� 
	//�� ���� ������ �� ���� ratepercent�� double������ ���� �� �ʱ�ȭ�� ����� ���ش�. �� divisor�� 100�� ��� ���ڸ� ����.0 ���� ������־�� �ϹǷ� ���ǹ��� ���� .0�� �߰��� ������ش�.

	DollarAmount balance{ 100000 }; // �ʱ� ���ݾ� 1000.00$ ��ü ����
	cout << "\nInitial balance: " << balance.toString() << endl;

	cout << "\nYear" << setw(20) << "Amount on deposit" << endl;

	for (unsigned int year{ 1 }; year <= 10; year++) { // 1����� 10�Ⱓ for �ݺ���
		balance.addInterest(rate, divisor); // balance ��ü(�ʱ⿹�ݾ�)��ü�� �ִ� amount ������ addInterest ����Լ��� ȣ���� ���

		cout << setw(4) << year << setw(20) << balance.toString() << endl;
	}


}