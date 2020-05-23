#include <iostream>
#include <iomanip>

using namespace std;

int main() {
	int x = 2; // 항의 초기 개수 2
	double m = 3;
	double pi = 0;
	for (double n = 1; pi < 3.14159; n += 4, m += 4) {
		pi = pi + 4 / n - 4 / m;
		x += 2; // 항이 두 개 씩 늘어남 , m 과 n에 관하여 하나씩
	}
	cout << pi << endl;
	cout << x; //  3.14159의 근사치를 뽑아내기 위해서는 376852개의 항이 필요

	return 0;
}