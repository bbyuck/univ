#include <iostream>

using namespace std;

int main() {
	//i�� ����, j�� ����
	for (int i = 1; i <= 9; ++i) {
		cout << '#';
	}
	cout << '\n'; // ���� ���� # 9��

	for (int j = 2; j <= 5; ++j) { // 5�� ���� for��
		for (int i = 1; i <= 9; ++i) {
			if (i == 1 || i == 9) {// ���� �� #
				cout << '#';
			}
			else if (i + j >= 2 * j && i + j <= 10) {
				cout << '*';
			}
			else {
				cout << ' ';
			}
		}
		cout << '\n';
	}
	for (int j = 6; j <= 8; ++j) { // 6�� �Ʒ��� for��
		for (int i = 1; i <= 9; ++i) {
			if (i == 1 || i == 9) {
				cout << '#';
			}
			else if (i + j >= 10 && i + j <= 2 * j) {
				cout << '*';
			}
			else {
				cout << ' ';
			}
		}
		cout << '\n';
	}
	for (int i = 1; i <= 9; ++i) { // ���� �Ʒ��� # 9��
		cout << '#';
	}
	return 0;
}