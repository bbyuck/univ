#include <iostream>

using namespace std;

int main() {
	for (int n = 1; n <= 10; n++) { // for�� �ȿ� loop iteration�� ���/ 1.�������� 2.�����ʱ�ȭ 3.�������� 4.�������� �Է� / n�� ���ο�
		int a = 1; // ������
		while (a <= n) {
			cout << '*';
			a++;
		}
		cout << '\n';
	}


	return 0;
}