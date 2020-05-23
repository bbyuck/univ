#include <iostream>

using namespace std;

int main() {
	for (int n = 1; n <= 10; n++) { // for문 안에 loop iteration의 요소/ 1.변수선언 2.변수초기화 3.루프조건 4.변수증감 입력 / n은 세로열
		int a = 1; // 가로행
		while (a < n) {
			cout << ' ';
			++a; 
			if (n > 10) { // n이 10을 넘어가면 18번 째 줄에 의해 항상 a가 n보다 작으므로 무한루프를 나오기 위해 break문 사용
				break;
			}
		}
		while (a >= n) {
			cout << '*';
			++a;
			if (a > 10) { // a가 10을 넘어가면 항상 n보다 커서 무한루프이므로 break문 사용
				break;
			}
		}
		cout << '\n';
		
	}


	return 0;
}