#include <iostream>

using namespace std;

int tripleByValue(int);
void tripleByReference(int&); // �Լ� ������Ÿ��

int main() {
	int count = 0;
	
	cout << "count ���� �Է��Ͻÿ� : "; // prompt
	cin >> count;

	cout << "\nPass-by-Value : " << tripleByValue(count) << endl;
	cout << "Pass-by-Value�� ���� ��ȯ�� �Լ����� " << tripleByValue(count) << "������ main�� ���� ���� count �� ������ " << count << " �̴�." << endl;
	
	cout << "\n\nPass-by-Reference : ";
	tripleByReference(count);
	cout << count; // Pass-by-Reference�� ���� ����� main������ ���� count ���

	cout << "\nPass-by-Reference�� ���� count�� �ּҿ� �Ҵ�� ���� ��ȯ�Ͽ� " << count << " (��)�� ��ȯ�Ǿ���."<< endl;

	return 0;
}

int tripleByValue(int x) { // ���� �ҷ��� 3�� ���� ���� ����
	return x *= 3; 
}
void tripleByReference(int &xRef) {
	xRef *= 3;
}