#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int main() {
	cout << fixed << setprecision(2);

	double principal{ 24.00 }; // ����
	double rate{ 0.05 }; // ����

	cout << "    Initial principal:  " << principal << endl;
	cout << "Initial Interest rate:   " << rate << endl;

	cout << "\nYear" << setw(43) << "Amount on deposit" << endl;
	for (rate = 0.05; rate <= 0.1; rate += 0.01) {
		for (unsigned int year{ 1 }; year <= 392; year++) { // 392�Ⱓ for�� ����
		
			double amount = principal * pow(1.0 + rate, year);

			cout << setw(4) << year << "(rate = " << rate << ")" << setw(30) << amount << endl;
		}
	} // ������ ū �ݾ������� �ݾ��� �����ʾƾ� �Ѵٴ� ������ ����־�� �ϹǷ� ���� �� ���� �ùٸ� ���ڿ���.
	return 0;
}