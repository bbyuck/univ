#include <iostream>
#include <ctime>
#include <Windows.h>
#include <iomanip>

using namespace std;

void moveTortoise(int*); //함수 프로토타입 
void moveHare(int*);
int Race();
void displayMessage(int);
void setHprobability();
void setTprobability();



int Hprobability[100]; // 한 번 선언 후 계속해서 사용할 전역변수들
int Tprobability[100];

int Hare = 1;
int Tortoise = 1;

int* HarePtr = &Hare;
int* TortoisePtr = &Tortoise;

int main() {
	
	setHprobability();
	setTprobability();
	
	int record = Race();

	displayMessage(record);

	return 0;
}


void setHprobability() { // 토끼의 이동타입 확률배열을 초기화 해주는 함수
	
	for (int i = 0; i < 100; ++i) { // 각각 이동타입에 확률 결정
		if (i < 38) {
			Hprobability[i] = 0; // 38% 0이면 Sleep
		}
		else if (i < 54) {
			Hprobability[i] = 1; //16% 1이면 Big hop
		}
		else if (i < 70) {
			Hprobability[i] = 2; //16% 2이면 Big slip
		}
		else if (i < 90) {
			Hprobability[i] = 3; // 20% 3이면 Small hop
		}
		else {
			Hprobability[i] = 4; // 10% 4이면 Small slip
		}
	}
}
void setTprobability() { // 거북이의 이동타입 확률배열을 초기화 해주는 함수
	
	for (int i = 0; i < 100; ++i) { //각각 이동타입에 부여할 확률 결정
		if (i < 50) {
			Tprobability[i] = 0; // 50% probabilty 배열에 저장된 값중 0 이 나오면 Fast Plod
		}
		else if (i < 66) {
			Tprobability[i] = 1; // 16% 1이면 Slip
		}
		else {
			Tprobability[i] = 2; // 34% 2 이면 Slow Plod
		}
	}
}


void moveTortoise(int* t) {
	
	srand(static_cast<unsigned int>(time(0)));
	
	enum class TmoveType { FAST_PLOD, SLIP, SLOW_PLOD }; // 거북이의 이동타입

	TmoveType TortoiseMoving;
	
	int select = rand() % 100; // 이동확률을 구하기위해 0 ~ 99의 수 중 한가지를 rand 함수를 이용해 추출

	switch (Tprobability[select]) { // 각각의 거북이 무브타입을 결정
	case 0:
		TortoiseMoving = TmoveType::FAST_PLOD;
		break;
	case 1:
		TortoiseMoving = TmoveType::SLIP;
		break;
	case 2:
		TortoiseMoving = TmoveType::SLOW_PLOD;
		break;
	default:
		break;
	}
	// pass by reference로 거북이의 위치를 변경해준다. 트랙의 좌측끝이 1, 트랙의 우측끝이 70이라 설정하고 오른쪽으로 이동하면 + 왼쪽으로 이동하면 -
	if (TortoiseMoving == TmoveType::FAST_PLOD) {
		*t += 3;
	}
	else if (TortoiseMoving == TmoveType::SLIP) {
		*t -= 6;
	}
	else if (TortoiseMoving == TmoveType::SLOW_PLOD) {
		*t += 1;
	}

	if (*t > 70) { // 만약 70번 칸을 넘어가게 되면 70으로 바꾸어줌
		*t = 70;
	}
	if (*t < 1) { // 1번칸보다 작게 미끄러지면
		*t = 1;
	}
}

void moveHare(int *h) {
	
	srand(static_cast<unsigned int>(time(0)));

	enum class HmoveType { SLEEP, BIG_HOP, BIG_SLIP, SMALL_HOP, SMALL_SLIP }; // 토끼의 이동타입

	HmoveType HareMoving;

	

	int select = rand() % 100; // 이동확률을 구하기위해 0 ~ 99의 수 중 한가지를 rand 함수를 이용해 추출

	switch (Hprobability[select]) { // 각각의 토끼 무브타입을 결정
	case 0:
		HareMoving = HmoveType::SLEEP;
		break;
	case 1:
		HareMoving = HmoveType::BIG_HOP;
		break;
	case 2:
		HareMoving = HmoveType::BIG_SLIP;
		break;
	case 3:
		HareMoving = HmoveType::SMALL_HOP;
		break;
	case 4:
		HareMoving = HmoveType::SMALL_SLIP;
		break;
	default:
		break;
	}


	// pass by reference로 토끼의 위치를 변경해준다. 트랙의 좌측끝이 1, 트랙의 우측끝이 70이라 설정하고 오른쪽으로 이동하면 + 왼쪽으로 이동하면 -
	if (HareMoving == HmoveType::SLEEP){
		*h = *h;
	}
	else if(HareMoving == HmoveType::BIG_HOP){
		*h += 11; 
	}
	else if (HareMoving == HmoveType::BIG_SLIP) {
		*h -= 9;
	}
	else if (HareMoving == HmoveType::SMALL_HOP) {
		*h += 1;
	}
	else if (HareMoving == HmoveType::SMALL_SLIP) {
		*h -= 2;
	}

	if (*h > 70) { // 만약 70번 칸을 넘어가게 되면 70으로 바꾸어줌
		*h = 70;
	}
	if (*h < 1) { // 1번칸에서 미끄러지면
		*h = 1;
	}
}


int Race() {
	

	int square[70]; // 70개의 스퀘어 경주판

	for (int i = 0; i < 70; ++i) {
		square[i] = i + 1; // 첫 칸은 1번칸
	}
	
	
	int graphicCount = 0; // 경주가 진행중임을 알 수 있게 해주는 그래프 그리는 도구
	
	cout << "경기가 시작됩니다." << endl;
	while (Hare != 70 && Tortoise != 70) { // 토끼와 거북이 둘 모두가 70번칸에 도착하지 못했을 때 루프를 통해 계속해서 토끼와 거북이 이동
		
		cout << "●";
		
		Sleep(100);

		moveHare(HarePtr);
		moveTortoise(TortoisePtr);

		graphicCount++;
		if (graphicCount % 10 == 0) {
			cout << endl;
		}
	}


	if (Hare == Tortoise) { // 토끼와 거북이 모두 70번 칸이면 0을 리턴
		return 0;
	}


	if (Hare == 70) { // 토끼가 70번 칸에 도착하면 1을 return
		return 1;
	}
	if (Tortoise == 70) { //거북이가 70번 칸에 도착하면 2를 return
		return 2;
	}

}
void displayMessage(int q) {
	switch (q) {
	case 0: 
		cout << "\n\n토끼와 거북이가 동시에 결승점에 도착했습니다!" << endl;
		break;
	case 1:
		cout << "\n\n토끼가 승리했습니다! 토끼가 당근과 양상추를 차지합니다." << endl;
		break;
	case 2:
		cout << "\n\n거북이가 승리했습니다! 거북이가 당근과 양상추를 차지합니다." << endl;
		break;
	}
}