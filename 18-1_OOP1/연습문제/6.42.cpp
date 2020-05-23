#include <iostream>
#include <cmath>


using namespace std;

double distance(double, double); // 함수 프로토타입

int main() {

	double x1 = 0;
	double y1 = 0;
	double x2 = 0;
	double y2 = 0; // 입력받을 변수 x1,y1,x2,y2 선언 및 초기화

	cout << "x1 입력 : ";
	cin >> x1;

	cout << "y1 입력 : ";
	cin >> y1;

	cout << "x2 입력 : ";
	cin >> x2;

	cout << "y2 입력 : ";
	cin >> y2; // 수 입력 prompt

	cout << "\n두 점 (x1, y1)과 (x2, y2) 사이의 거리 : " << distance(x2 - x1, y2 - y1); // 함수 호출 및 출력으로 함수 정상작동여부 확인

	return 0;
}

double distance(double dx, double dy) { // 두 점 사이의 거리 dx, dy 인수
	double distance; // 계산한 거리를 저장하고 반환할 변수

	distance = sqrt(pow(dx, 2) + pow(dy, 2)); // distance 정의

	return distance;
}