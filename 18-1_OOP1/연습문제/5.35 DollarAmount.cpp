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
	d1.add(d2); // add 멤버함수 호출
	cout << d1.toString() << "\n";

	cout << "After subtracting d2 (" << d2.toString() << ") from d1 (" << d1.toString() << "), d1 = ";
	d1.subtract(d2);
	cout << d1.toString() << "\n";

	cout << "After subtracting d1 (" << d1.toString() << ") from d2 (" << d2.toString() << "), d2 = ";
	d2.subtract(d1);
	cout << d2.toString() << "\n"; // 멤버함수 기능 test

	cout << "Enter integer interest rate and divisor. For example:\n" // prompt 및 예시 UI
		<< "for     2%, enter:    2 100\n"
		<< "for   2.3%, enter:   23 1000\n"
		<< "for  2.37%, enter:  237 10000\n"
		<< "for 2.375%, enter: 2375 100000\n ";


	int rate; // rate 변수선언
	int divisor; // divisor 변수선언
	cin >> rate >> divisor;

	double ratepercent{ static_cast<double>(rate) / divisor * 100 };

	cout << "\nInterest rate : " << ratepercent << (divisor == 100 ? ".0" : "") << "%"; // int형 변수 rate 대신 rate를 일시적으로 double형으로 캐스팅한 후 
	//그 값을 저장해 줄 변수 ratepercent를 double형으로 선언 및 초기화후 출력을 해준다. 단 divisor가 100일 경우 한자리 정수.0 꼴을 만들어주어야 하므로 조건문을 통해 .0을 추가로 출력해준다.

	DollarAmount balance{ 100000 }; // 초기 예금액 1000.00$ 객체 생성
	cout << "\nInitial balance: " << balance.toString() << endl;

	cout << "\nYear" << setw(20) << "Amount on deposit" << endl;

	for (unsigned int year{ 1 }; year <= 10; year++) { // 1년부터 10년간 for 반복문
		balance.addInterest(rate, divisor); // balance 객체(초기예금액)객체에 있는 amount 변수를 addInterest 멤버함수를 호출해 계산

		cout << setw(4) << year << setw(20) << balance.toString() << endl;
	}


}