#include <iostream>

using namespace std;

int main() {
	//i가 가로, j가 세로
	for (int i = 1; i <= 9; ++i) {
		cout << '#';
	}
	cout << '\n'; // 제일 윗줄 # 9개

	for (int j = 2; j <= 5; ++j) { // 5행 위쪽 for문
		for (int i = 1; i <= 9; ++i) {
			if (i == 1 || i == 9) {// 양쪽 끝 #
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
	for (int j = 6; j <= 8; ++j) { // 6행 아랫쪽 for문
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
	for (int i = 1; i <= 9; ++i) { // 가장 아랫줄 # 9개
		cout << '#';
	}
	return 0;
}