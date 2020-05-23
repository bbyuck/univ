#include <iostream>
#include <array>

using namespace std;

const size_t rowSize = 2; // 2X3 배열을 선언하기 위한 전역변수
const size_t columnSize = 3;

int main() {
	array<array<int, columnSize>, rowSize> t{ 1,2,3,4,5,6 }; // 2X3 배열 t 선언(a), 및 모든 elemnents들 0으로 초기화(h)

	int lowestNum = t[0][0]; // 가장 작은 수를 저장할 변수를 선언하고 2X3 배열 t 의 첫번째 수를 가장작은수로 초기화

	for (size_t i = 0; i < t.size(); ++i) {
		for (size_t j = 0; j < t[i].size(); ++j) {
			if (lowestNum > t[i][j]) {
				lowestNum = t[i][j];
			}
		}
	}
	cout << "가장 작은 수는 " << lowestNum << endl; // 가장 작은 수 출력
}