#include <iostream>
#include <array>

using namespace std;

const size_t rowSize = 2; // 2X3 배열을 선언하기 위한 전역변수
const size_t columnSize = 3;

int main() {
	array<array<int, columnSize>, rowSize> t{ 1,2,3,4,5,6 }; // 2X3 배열 t 선언(a), 및 모든 elemnents들 0으로 초기화(h)`
		for (size_t j = 0; j <= t.size(); ++j) {
			cout << t[0][j] << " "; // 0행의 elements들 출력
		}
		cout << endl;
}
