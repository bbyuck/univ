#include <iostream>
#include <iomanip>

using namespace std;

int main() {
	int x = 2; // ���� �ʱ� ���� 2
	double m = 3;
	double pi = 0;
	for (double n = 1; pi < 3.14159; n += 4, m += 4) {
		pi = pi + 4 / n - 4 / m;
		x += 2; // ���� �� �� �� �þ , m �� n�� ���Ͽ� �ϳ���
	}
	cout << pi << endl;
	cout << x; //  3.14159�� �ٻ�ġ�� �̾Ƴ��� ���ؼ��� 376852���� ���� �ʿ�

	return 0;
}