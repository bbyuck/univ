#include <iostream>
#include <array>

using namespace std;

const size_t rowSize = 2; // 2X3 배열을 선언하기 위한 전역변수
const size_t columnSize = 3;

int main() {

	//(a)

	array<array<int, columnSize>, rowSize> t{ 1,2,3,4,5,6 }; // 2X3 배열 t 선언(a), 및 모든 elemnents들 0으로 초기화(h)
															 //루프 사용하지 않고 0 으로 초기화
															 
	for (int i = 0; i < t.size(); ++i) {//	(k)t의 elements를 직접 입력받아 배열을 초기화 하는 for문
		for (int j = 0; j < t[i].size(); ++j) {
			int num;
			cout << i << "행 " << j << "열에 저장할 수를 입력하세요.";
			cin >> num;
			t[i][j] = num;
		}
	}
	//출력을 통해 초기화가 되었는지 쉽게 확인
	for (int i = 0; i < t.size(); ++i) {
		for (int j = 0; j < t[i].size(); ++j) {
			cout << t[i][j] << " ";
		}
		cout << endl;
	}
}