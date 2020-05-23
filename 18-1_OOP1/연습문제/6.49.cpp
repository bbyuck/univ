#include <iostream>

using namespace std;

int tripleByValue(int);
void tripleByReference(int&); // 함수 프로토타입

int main() {
	int count = 0;
	
	cout << "count 값을 입력하시오 : "; // prompt
	cin >> count;

	cout << "\nPass-by-Value : " << tripleByValue(count) << endl;
	cout << "Pass-by-Value에 의해 반환된 함수값은 " << tripleByValue(count) << "이지만 main문 안의 변수 count 는 여전히 " << count << " 이다." << endl;
	
	cout << "\n\nPass-by-Reference : ";
	tripleByReference(count);
	cout << count; // Pass-by-Reference에 의해 변경된 main문내의 변수 count 출력

	cout << "\nPass-by-Reference에 의해 count의 주소에 할당된 값을 변환하여 " << count << " (으)로 변환되었다."<< endl;

	return 0;
}

int tripleByValue(int x) { // 값을 불러와 3을 곱한 값을 리턴
	return x *= 3; 
}
void tripleByReference(int &xRef) {
	xRef *= 3;
}