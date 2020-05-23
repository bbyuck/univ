#include <iostream>
#include <iomanip>
#include <string>
#include "DollarAmount.h"

using namespace std;

int main() {
	DollarAmount d1{ 12345 };
	DollarAmount d2{ 1576 };

	cout << "After adding d2 (" << d2.toString() << ") into d1 (" << d1.toString() << "), d1 = ";
	d1.add(d2);
	cout << d1.toString() << "\n";

	cout << "After subtracting d2 (" << d2.toString() << ") from d1 (" << d1.toString() << "), d1 = ";
	d1.subtract(d2);
	cout << d1.toString() << "\n";

	cout << "Enter integer interest rate and divisor. For example: \n" // prompt
		<< "for     2%, enter:    2 100\n"
		<< "for   2.3%, enter:   23 1000\n"
		<< "for  2.37%, enter:  237 10000\n"
		<< "for 2.375%, enter: 2375 100000\n ";
	int rate;
	int divisor;
	cin >> rate >> divisor; // input rate, divisor

	DollarAmount balance{ 100000 };
	cout << "\nInitial balance: " << balance.toString() << endl;

	cout << "\nYear" << setw(20) << "Amount on deposit" << endl;

	for (unsigned int year{ 1 }; year <= 10; year++) {

		balance.addInterest(rate, divisor);

		cout << setw(4) << year << setw(20) << balance.toString() << endl;
	}

	//5.31 Divide함수 테스트
	divisor = 7; // divisor에 임의로 나누어 줄 수 7을 할당
	cout << "\n\nAfter dividing d1 (" << d1.toString() << ") with (" << divisor << "), d1 = ";
	d1.divide(divisor);
	cout << d1.toString() << "\n과제부분\n\n";
}