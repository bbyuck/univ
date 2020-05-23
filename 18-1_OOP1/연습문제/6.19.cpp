#include <iostream>
#include <cmath>
#include <iomanip>


using namespace std;

double hypotenuse(double Side1, double Side2) { // hypotenuse 함수
	double hypotenuse;
	double k;
	
	k = pow(Side1, 2) + pow(Side2, 2); // 변수 k에 주어진 삼각형의 두 변의 제곱합을 입력
	hypotenuse = sqrt(k); // k의 제곱근을 한 것이 빗변의 길이

	return hypotenuse;
}

int main() {
	

	cout << "Triangle" << setw(9) << "Side 1" << setw(9) << "Side 2" << setw(13) << "Hypotenuse" << endl;

	cout << 1 << setw(13) << "3.0" << setw(9) << "4.0" << setw(7) << hypotenuse(3.0, 4.0) << endl; // hypotenuse 함수 구동테스트
	cout << 2 << setw(13) << "5.0" << setw(10) << "12.0" << setw(7) << hypotenuse(5.0, 12.0) << endl;
	cout << 3 << setw(13) << "8.0" << setw(10) << "15.0" << setw(7) << hypotenuse(8.0, 15.0) << endl;

	return 0;
}