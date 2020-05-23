#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int main() {
	cout << fixed << setprecision(2);

	double principal{ 24.00 }; // 원금
	double rate{ 0.05 }; // 이율

	cout << "    Initial principal:  " << principal << endl;
	cout << "Initial Interest rate:   " << rate << endl;

	cout << "\nYear" << setw(43) << "Amount on deposit" << endl;
	for (rate = 0.05; rate <= 0.1; rate += 0.01) {
		for (unsigned int year{ 1 }; year <= 392; year++) { // 392년간 for문 시작
		
			double amount = principal * pow(1.0 + rate, year);

			cout << setw(4) << year << "(rate = " << rate << ")" << setw(30) << amount << endl;
		}
	} // 굉장히 큰 금액이지만 금액을 빼지않아야 한다는 가정이 깔려있어야 하므로 땅을 산 것은 올바른 투자였다.
	return 0;
}