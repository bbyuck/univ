#include <iostream>

using namespace std;

int main() {
	//a�� ���� b�� ����
	for (int a = 1; a <= 10; ++a) {
		for (int b = 1; b <= 10; ++b) {
			if (a >= b) {
				cout << '*';
			}
			else {
				cout << ' ';
			}
		}//(a for��)
		for (int b = 10; b >= 1; --b) {
			if (a <= b) {
				cout << '*';
			}
			else {
				cout << ' ';
			}
		}//(b for��)
		for (int b = 1; b <= 10; ++b) {
			if (a <= b) {
				cout << '*';
			}
			else {
				cout << ' ';
			}
		}//(c for��)
		for (int b = 10; b >= 1; --b) {
			if (a < b) {
				cout << ' ';
			}
			else {
				cout << '*';
			}
		}//(d for��)
		cout << '\n';
	}//�Ѱ� for��

	return 0;
}