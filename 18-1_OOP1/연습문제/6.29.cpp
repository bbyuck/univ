#include <iostream>

using namespace std;

int primeNumber(int);


int main() {

	int primeCount = 0; // �Ҽ� ���� ������ ����

	for (int count = 2; count <= 10000; count++) { // 2���� 10000������ ������ �Է¹����� primeNumber�Լ����� ��ȯ���� ���� 0�̸� ������� �ʴ� for��
		if (primeNumber(count) != 0) {
			cout << primeNumber(count) << endl;
			primeCount++; // ���� �Ҽ��̸� �Ҽ� ���� �ϳ� ����
		}
	}

	cout << "\n�Ҽ� ����" << primeCount; // �Ҽ� ���� ���
	return 0;
}

int primeNumber(int num) { // �Է¹��� ������ �Ҽ����� �����ϰ� �Ҽ��̸� �Է¹��� ���� �״�� ��ȯ, �Ҽ��� �ƴϸ� 0�� ��ȯ�ϴ� �Լ�
	int primeNumber = num;

	for (unsigned int i = 2; i < primeNumber; i++) {
		if (primeNumber == 2) {
			return primeNumber;
		}
		else if (primeNumber % i == 0) {
			return 0;
		}
	}
	return primeNumber;
}