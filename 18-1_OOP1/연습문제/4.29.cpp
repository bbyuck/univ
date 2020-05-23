#include <iostream>

using namespace std;

int main() {

	int a = 1;  // a가 세로 , b가 가로 반복문에 이용할 변수선언 및 초기화
	int b;

	while (a <= 8) { // 문제에는 세로 8줄 출력 변경가능
		b = 1;
		if (a % 2 == 1) { // 홀수 행이면
			while (b <= 8) {
				cout << "* "; // 문제에서 주어진 output statement
				b++; // 가로열 하나씩 오른쪽으로 이동 (스페이스바 한 칸 출력이라 두칸이동)
			}
			cout << endl;
		}
		else if (a % 2 == 0) { // 짝수 행이면
			cout << ' '; // 한 칸 들여쓰기, 문제에서 주어진 output statement
			while (b <= 8) {
				cout << "* ";
				b++;
			}
			cout << endl;
		}
		a++;// 가로열 모두 출력 후 다음행으로 넘어감
	}

	return 0;
}