#include <iostream>

using namespace std;

int main() {

	int a = 1;  // a�� ���� , b�� ���� �ݺ����� �̿��� �������� �� �ʱ�ȭ
	int b;

	while (a <= 8) { // �������� ���� 8�� ��� ���氡��
		b = 1;
		if (a % 2 == 1) { // Ȧ�� ���̸�
			while (b <= 8) {
				cout << "* "; // �������� �־��� output statement
				b++; // ���ο� �ϳ��� ���������� �̵� (�����̽��� �� ĭ ����̶� ��ĭ�̵�)
			}
			cout << endl;
		}
		else if (a % 2 == 0) { // ¦�� ���̸�
			cout << ' '; // �� ĭ �鿩����, �������� �־��� output statement
			while (b <= 8) {
				cout << "* ";
				b++;
			}
			cout << endl;
		}
		a++;// ���ο� ��� ��� �� ���������� �Ѿ
	}

	return 0;
}