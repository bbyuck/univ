#include <iostream>
#include <iomanip>

using namespace std;


int calculateCharges(double time) {
	int charges = 20; // 초기 요금 20.00$

	if (time > 3) {
		charges += 5 * (static_cast<int>(time) - 3); // 시간 내림
	}
	if (charges >= 50) { // 요금의 최대치는 50 달러
		charges = 50;
	}
	return charges;
}

int main() {
	double time[3] = { 0, 1, 2 }; // 배열을 통해 time을 입력받음
	

	for (int count = 0; count <= 2; count++) { // 시간 time을 입력받는 for문
		cout << count + 1 << "번 고객의 주차 시간을 입력하세요.";
		cin >> time[count];
	
		if (time[count] > 24) { // 24시간까지 가능
			cout << "\n 주차 시간은 24시간을 넘길 수 없습니다. 다시 입력하세요." << endl;
			count--;
			continue;
		}
	}

	cout << "\nCar" << setw(12) << "Hours" << setw(15) << "Charges" << endl; // 표 UI

	for (int count = 0; count <= 2; count++) { // 각 차의 시간과 요금을 표 UI로 출력
		cout << count +1 << setw(14) << time[count] << setw(10) << "$" << calculateCharges(time[count]) << ".00" << endl; 
	}
	
	int totalCharges = 0; // 요금의 총합 저장하고 출력할 변수 선언 및 0으로 초기화
	
	for (int count = 0; count <= 2; count++) { // 요금의 총합을 calculateCharges()함수를 이용해 계산
		totalCharges += calculateCharges(time[count]);
	}
	
	double totalTime = time[0] + time[1] + time[2]; // 시간의 총합 변수 선언 및 정의

	cout << "ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ" << endl;
	cout << "total : " << setw(7) << totalTime << setw(10) << "$" << totalCharges << ".00" << endl; // total 값들 출력


	return 0;
}

