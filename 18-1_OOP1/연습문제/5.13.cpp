#include <iostream>
#include <iomanip>

using namespace std;

int main() {
	long long int factorial = 1; // long ������ Ÿ�����δ� 20!�� ǥ���� �� ���� long long���� ��ü

	cout << "n" << setw(3) << "��" << setw(12) << "n!" << setw(12) << "��" << endl; // ui
	cout << "--�----------------------��" << endl; // ǥ ui
	for (unsigned int n = 1;n <= 20; n++) { // for�� �̿�
		factorial = n * factorial;
		if (n >= 10) {
			cout << n << setw(2) << "��" << setw(21) << factorial << " ��" << endl;
			cout << "--�----------------------��" << endl;
		}
		else if (n < 10) {
			cout << n << setw(3) << "��" << setw(21) << factorial << " ��" << endl;
			cout << "--�----------------------��" << endl;
		}
	}
	// 100! �� ��� �ڸ����� �ʹ� Ŀ �޸𸮿� �Ҵ�Ǵ� ������ Ÿ���� ũ�⺸�� Ŀ�� ��ǻ�ͷ� ����ϱ� ��ƴ�.
	return 0;
}