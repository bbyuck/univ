#include <iostream>
#include <array>
#include <iomanip>
using namespace std;

const size_t rowSize = 2; // 2X3 배열을 선언하기 위한 전역변수
const size_t columnSize = 3;

int main() {
	array<array<int, columnSize>, rowSize> t{ 1,2,3,4,5,6 }; // 2X3 배열 t 선언(a), 및 모든 elemnents들 0으로 초기화(h)

	cout << setw(5);
	for (int i = 0; i <= t.size(); ++i) {
		cout << i << "열" << "   ";
	}
	cout << endl;
	for (size_t i = 0; i < t.size(); ++i) {
		cout << i << "행: ";
		for (size_t j = 0; j < t[i].size(); ++j) {
			cout << t[i][j] << "     ";
		}
		cout << endl;
	}
}