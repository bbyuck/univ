#include <iostream>

using namespace std;

int main() {
	//a는 가로 b는 세로
	for (int a = 1; a <= 10; ++a) {
		for (int b = 1; b <= 10; ++b) {
			if (a >= b) {
				cout << '*';
			}
			else {
				cout << ' ';
			}
		}//(a for문)
		for (int b = 10; b >= 1; --b) {
			if (a <= b) {
				cout << '*';
			}
			else {
				cout << ' ';
			}
		}//(b for문)
		for (int b = 1; b <= 10; ++b) {
			if (a <= b) {
				cout << '*';
			}
			else {
				cout << ' ';
			}
		}//(c for문)
		for (int b = 10; b >= 1; --b) {
			if (a < b) {
				cout << ' ';
			}
			else {
				cout << '*';
			}
		}//(d for문)
		cout << '\n';
	}//총괄 for문

	return 0;
}