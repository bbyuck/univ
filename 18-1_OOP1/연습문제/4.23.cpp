#include <iostream>

using namespace std;

int main() {
	int x = 0; // �������� ���� ���� x, y ���� �� �ʱ�ȭ
	int y = 0;

	cout << "Enter the number 'x' : "; // prompt
	cin >> x;
	cout << "Enter the number 'y' : ";
	cin >> y;

	cout << endl;

	if (x > 5) { // ������ �䱸�� brace {} ��ġ
		if (y > 5) {
			cout << "x and y are > 5";
		}
		else { // �������� ������ �ʾ����� ���� if���� ���Ե� else ��.
			cout << "x is > 5 but y is <=5";
		}
	}
	else {
		cout << "x is <=5";
	}
}