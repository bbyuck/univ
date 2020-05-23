#include <iostream>

using namespace std;

int main() {
	unsigned int count;


	for (count = 1; count !=5; ++count) { // break 문의 사용 없이 루프를 나오기 위해서는 count가 5가 아닐동안만 루프를 돌 수 있게 조건을 설정한다.
		
		cout << count << " ";
	}
	cout << "\nBroke out of loop at count = " << count << endl;
	
}