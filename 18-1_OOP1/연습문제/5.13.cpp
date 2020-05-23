#include <iostream>
#include <iomanip>

using namespace std;

int main() {
	long long int factorial = 1; // long 데이터 타입으로는 20!을 표기할 수 없음 long long으로 대체

	cout << "n" << setw(3) << "ㅣ" << setw(12) << "n!" << setw(12) << "ㅣ" << endl; // ui
	cout << "--十----------------------ㅣ" << endl; // 표 ui
	for (unsigned int n = 1;n <= 20; n++) { // for문 이용
		factorial = n * factorial;
		if (n >= 10) {
			cout << n << setw(2) << "ㅣ" << setw(21) << factorial << " ㅣ" << endl;
			cout << "--十----------------------ㅣ" << endl;
		}
		else if (n < 10) {
			cout << n << setw(3) << "ㅣ" << setw(21) << factorial << " ㅣ" << endl;
			cout << "--十----------------------ㅣ" << endl;
		}
	}
	// 100! 의 경우 자릿수가 너무 커 메모리에 할당되는 데이터 타입의 크기보다 커져 컴퓨터로 계산하기 어렵다.
	return 0;
}