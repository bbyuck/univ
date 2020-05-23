#include <iostream> // 전처리기
#include <iomanip>
#include <string>
#include "DollarAmount.h"


using namespace std;

int main() {
	DollarAmount d1( 123, 45);
	DollarAmount d2( 15, 76);

	cout << setprecision(2) << fixed;

	cout << "Adding d1 into d2 : ";
	d2.add(d1);
	cout << d2.toString();

	cout << "\nSubtracting d2 from d1 : ";
	d1.subtract(d2);
	cout << d1.toString();

	cout << "\n\nEnter integer interest rate and divisor. For example: \n" // prompt
		<< "for     2%, enter:    2 100\n"
		<< "for   2.3%, enter:   23 1000\n"
		<< "for  2.37%, enter:  237 10000\n"
		<< "for 2.375%, enter: 2375 100000\n ";
	int rate;
	int divisor;
	cin >> rate >> divisor; // input rate, divisor

	DollarAmount balance{ 1000,00 };
	cout << "\nInitial balance: " << balance.toString() << endl;

	cout << "\nYear" << setw(20) << "Amount on deposit" << endl;

	for (unsigned int year{ 1 }; year <= 10; year++) {

		balance.addInterest(rate, divisor);

		
		cout << setw(4) << year << setw(20) << balance.toString() << endl;
	}

	//5.31 Divide함수 테스트
	divisor = 7;
	cout << "\n\nAfter dividing d1 (" << d1.toString() << ") with (" << divisor << "), d1 = ";
	d1.divide(divisor);
	cout << d1.toString() << "\n";
}
