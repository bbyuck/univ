#include <iostream>

using namespace std;

int main() {
	for (int n = 1; n <= 10; n++) { // for�� �ȿ� loop iteration�� ���/ 1.�������� 2.�����ʱ�ȭ 3.�������� 4.�������� �Է� / n�� ���ο�
		int a = 10; // ������
		while (a > n) {
			cout << ' ';
			--a;
		}
		while (a <= n) {
			cout << '*';
			--a;
			if (a <= 0) { // a �� 0������ �۾����� �Ѵ� (10 to 0)
				break;
			}
		}
		cout << '\n';

	}

	return 0;
}