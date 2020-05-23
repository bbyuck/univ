#include <iostream>

using namespace std;

int main() {
	for (int n = 1; n <= 10; n++) { // for문 안에 loop iteration의 요소/ 1.변수선언 2.변수초기화 3.루프조건 4.변수증감 입력 / n은 세로열
		int a = 10; // 가로행
		while (a > n) {
			cout << ' ';
			--a;
		}
		while (a <= n) {
			cout << '*';
			--a;
			if (a <= 0) { // a 는 0까지만 작아져야 한다 (10 to 0)
				break;
			}
		}
		cout << '\n';

	}

	return 0;
}