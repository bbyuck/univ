#include <iostream>

using namespace std;

int primeNumber(int);


int main() {

	int primeCount = 0; // 소수 갯수 저장할 변수

	for (int count = 2; count <= 10000; count++) { // 2부터 10000까지의 정수를 입력받으며 primeNumber함수에서 반환받은 값이 0이면 출력하지 않는 for문
		if (primeNumber(count) != 0) {
			cout << primeNumber(count) << endl;
			primeCount++; // 수가 소수이면 소수 갯수 하나 증가
		}
	}

	cout << "\n소수 갯수" << primeCount; // 소수 갯수 출력
	return 0;
}

int primeNumber(int num) { // 입력받은 정수가 소수임을 판정하고 소수이면 입력받은 수를 그대로 반환, 소수가 아니면 0을 반환하는 함수
	int primeNumber = num;

	for (unsigned int i = 2; i < primeNumber; i++) {
		if (primeNumber == 2) {
			return primeNumber;
		}
		else if (primeNumber % i == 0) {
			return 0;
		}
	}
	return primeNumber;
}