#include <iostream>
#include <cmath>

using namespace std;

int quotient(int a, int b) { // (a) ���� ����ϰ� ��ȯ�ϴ� �Լ�
	int quotient = a / b;
	return quotient;
}

int remainder(int a, int b) { //(b) �������� ����ϰ� ��ȯ�ϴ� �Լ�
	int remainder = a % b;
	return remainder;
}

void displayInt(int num) { // ����� ���� ���� ���ڸ� �Է��ϸ� �������ǿ� ���� ����� void�� �Լ�, ���⼭�� ��� �������� �Է��� ��
	int displayNum = num;

	if (displayNum / 10 == 0) { // �Է��� ���ڰ� ���ڸ� �� �� ��
		cout << displayNum;
	}
	else if (displayNum / 100 == 0) { // �Է��� ���ڰ� ���ڸ� �� �� ��
		cout << displayNum / 10 << "  " << displayNum % 10; // 
	}
	else if (displayNum / 1000 == 0) { // �Է��� ���ڰ� ���ڸ� �� �� ��
		cout << displayNum / 100 << "  " << (displayNum % 100) / 10 << "  " << displayNum % 10;
	}
	else if (displayNum / 10000 == 0) { // �Է��� ���ڰ� ���ڸ� �� �� ��
		cout << displayNum / 1000 << "  " << (displayNum % 1000) / 100 << "  " << (displayNum % 100) / 10 << "  " << displayNum % 10;
	}
	else { // �Է��� ���ڰ� �ټ��ڸ� �� �� ��
		cout << displayNum / 10000 << "  " << (displayNum % 10000) / 1000 << "  " << (displayNum % 1000) / 100 << "  " << (displayNum % 100) / 10 << "  " << displayNum % 10;
	}
}


int main(){
	int a = 0;
	int b = 0;

	cout << "1���� 32767 ������ ���� a�� �Է��ϼ���. ";
	cin >> a;
	
	while (a < 1 || a > 32767) {
		cout << "�߸��� ������ �Է��߽��ϴ�. �ٽ� �Է��ϼ���. ";
		cin >> a;
	}
	
	
	cout << "1���� 32767 ������ ���� b�� �Է��ϼ���. ";
	cin >> b;
	
	while (b < 1 || b > 32767) {
		cout << "�߸��� ������ �Է��߽��ϴ�. �ٽ� �Է��ϼ���. ";
		cin >> b;
	}

	cout << "��     : "; // �� ���
	displayInt(quotient(a, b));
	cout << endl;
	
	cout << "������ : "; // ������ ���
	displayInt(remainder(a, b));
	cout << endl;
	return 0;
}