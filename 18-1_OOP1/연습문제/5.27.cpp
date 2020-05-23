#include <iostream>

using namespace std;

int main() {
	for (unsigned int count{ 1 }; count <= 10; count++) {
		if (count == 5) {
			++count; // continue문이 루프 초기로 돌리는 제어문이므로 루프조건을 강제로 입력하면 continue문과 동일한 효과가 나타난다.
		}
		cout << count << " ";
	}
	cout << "\nUsed continue to skip printing 5" << endl;	
}