#include <iostream>

using namespace std;

int main() {
	for (int n = 1; n <= 10; n++) { // for�� �ȿ� loop iteration�� ���/ 1.�������� 2.�����ʱ�ȭ 3.�������� 4.�������� �Է� / n�� ���ο�
		int a = 1; // ������
		while (a < n) {
			cout << ' ';
			++a; 
			if (n > 10) { // n�� 10�� �Ѿ�� 18�� ° �ٿ� ���� �׻� a�� n���� �����Ƿ� ���ѷ����� ������ ���� break�� ���
				break;
			}
		}
		while (a >= n) {
			cout << '*';
			++a;
			if (a > 10) { // a�� 10�� �Ѿ�� �׻� n���� Ŀ�� ���ѷ����̹Ƿ� break�� ���
				break;
			}
		}
		cout << '\n';
		
	}


	return 0;
}