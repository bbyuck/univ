#include <iostream>
#include <cmath>

using namespace std;

int quotient(int a, int b) { // (a) 몫을 계산하고 반환하는 함수
	int quotient = a / b;
	return quotient;
}

int remainder(int a, int b) { //(b) 나머지를 계산하고 반환하는 함수
	int remainder = a % b;
	return remainder;
}

void displayInt(int num) { // 계산을 통해 구한 숫자를 입력하면 문제조건에 따라 출력할 void형 함수, 여기서는 몫과 나머지를 입력할 것
	int displayNum = num;

	if (displayNum / 10 == 0) { // 입력한 숫자가 한자리 수 일 때
		cout << displayNum;
	}
	else if (displayNum / 100 == 0) { // 입력한 숫자가 두자리 수 일 때
		cout << displayNum / 10 << "  " << displayNum % 10; // 
	}
	else if (displayNum / 1000 == 0) { // 입력한 숫자가 세자리 수 일 때
		cout << displayNum / 100 << "  " << (displayNum % 100) / 10 << "  " << displayNum % 10;
	}
	else if (displayNum / 10000 == 0) { // 입력한 숫자가 네자리 수 일 때
		cout << displayNum / 1000 << "  " << (displayNum % 1000) / 100 << "  " << (displayNum % 100) / 10 << "  " << displayNum % 10;
	}
	else { // 입력한 숫자가 다섯자리 수 일 때
		cout << displayNum / 10000 << "  " << (displayNum % 10000) / 1000 << "  " << (displayNum % 1000) / 100 << "  " << (displayNum % 100) / 10 << "  " << displayNum % 10;
	}
}


int main(){
	int a = 0;
	int b = 0;

	cout << "1에서 32767 사이의 정수 a를 입력하세요. ";
	cin >> a;
	
	while (a < 1 || a > 32767) {
		cout << "잘못된 정수를 입력했습니다. 다시 입력하세요. ";
		cin >> a;
	}
	
	
	cout << "1에서 32767 사이의 정수 b를 입력하세요. ";
	cin >> b;
	
	while (b < 1 || b > 32767) {
		cout << "잘못된 정수를 입력했습니다. 다시 입력하세요. ";
		cin >> b;
	}

	cout << "몫     : "; // 몫 출력
	displayInt(quotient(a, b));
	cout << endl;
	
	cout << "나머지 : "; // 나머지 출력
	displayInt(remainder(a, b));
	cout << endl;
	return 0;
}