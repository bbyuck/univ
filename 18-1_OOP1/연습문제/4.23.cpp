#include <iostream>

using namespace std;

int main() {
	int x = 0; // 문제에서 사용된 변수 x, y 선언 및 초기화
	int y = 0;

	cout << "Enter the number 'x' : "; // prompt
	cin >> x;
	cout << "Enter the number 'y' : ";
	cin >> y;

	cout << endl;

	if (x > 5) { // 문제가 요구한 brace {} 위치
		if (y > 5) {
			cout << "x and y are > 5";
		}
		else { // 문제에선 나오지 않았지만 내부 if문에 포함된 else 문.
			cout << "x is > 5 but y is <=5";
		}
	}
	else {
		cout << "x is <=5";
	}
}