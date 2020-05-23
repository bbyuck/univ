#include <iostream>
#include <ctime>
#include <Windows.h>
#include <iomanip>

using namespace std;

void moveTortoise(int*); //�Լ� ������Ÿ�� 
void moveHare(int*);
int Race();
void displayMessage(int);
void setHprobability();
void setTprobability();



int Hprobability[100]; // �� �� ���� �� ����ؼ� ����� ����������
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


void setHprobability() { // �䳢�� �̵�Ÿ�� Ȯ���迭�� �ʱ�ȭ ���ִ� �Լ�
	
	for (int i = 0; i < 100; ++i) { // ���� �̵�Ÿ�Կ� Ȯ�� ����
		if (i < 38) {
			Hprobability[i] = 0; // 38% 0�̸� Sleep
		}
		else if (i < 54) {
			Hprobability[i] = 1; //16% 1�̸� Big hop
		}
		else if (i < 70) {
			Hprobability[i] = 2; //16% 2�̸� Big slip
		}
		else if (i < 90) {
			Hprobability[i] = 3; // 20% 3�̸� Small hop
		}
		else {
			Hprobability[i] = 4; // 10% 4�̸� Small slip
		}
	}
}
void setTprobability() { // �ź����� �̵�Ÿ�� Ȯ���迭�� �ʱ�ȭ ���ִ� �Լ�
	
	for (int i = 0; i < 100; ++i) { //���� �̵�Ÿ�Կ� �ο��� Ȯ�� ����
		if (i < 50) {
			Tprobability[i] = 0; // 50% probabilty �迭�� ����� ���� 0 �� ������ Fast Plod
		}
		else if (i < 66) {
			Tprobability[i] = 1; // 16% 1�̸� Slip
		}
		else {
			Tprobability[i] = 2; // 34% 2 �̸� Slow Plod
		}
	}
}


void moveTortoise(int* t) {
	
	srand(static_cast<unsigned int>(time(0)));
	
	enum class TmoveType { FAST_PLOD, SLIP, SLOW_PLOD }; // �ź����� �̵�Ÿ��

	TmoveType TortoiseMoving;
	
	int select = rand() % 100; // �̵�Ȯ���� ���ϱ����� 0 ~ 99�� �� �� �Ѱ����� rand �Լ��� �̿��� ����

	switch (Tprobability[select]) { // ������ �ź��� ����Ÿ���� ����
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
	// pass by reference�� �ź����� ��ġ�� �������ش�. Ʈ���� �������� 1, Ʈ���� �������� 70�̶� �����ϰ� ���������� �̵��ϸ� + �������� �̵��ϸ� -
	if (TortoiseMoving == TmoveType::FAST_PLOD) {
		*t += 3;
	}
	else if (TortoiseMoving == TmoveType::SLIP) {
		*t -= 6;
	}
	else if (TortoiseMoving == TmoveType::SLOW_PLOD) {
		*t += 1;
	}

	if (*t > 70) { // ���� 70�� ĭ�� �Ѿ�� �Ǹ� 70���� �ٲپ���
		*t = 70;
	}
	if (*t < 1) { // 1��ĭ���� �۰� �̲�������
		*t = 1;
	}
}

void moveHare(int *h) {
	
	srand(static_cast<unsigned int>(time(0)));

	enum class HmoveType { SLEEP, BIG_HOP, BIG_SLIP, SMALL_HOP, SMALL_SLIP }; // �䳢�� �̵�Ÿ��

	HmoveType HareMoving;

	

	int select = rand() % 100; // �̵�Ȯ���� ���ϱ����� 0 ~ 99�� �� �� �Ѱ����� rand �Լ��� �̿��� ����

	switch (Hprobability[select]) { // ������ �䳢 ����Ÿ���� ����
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


	// pass by reference�� �䳢�� ��ġ�� �������ش�. Ʈ���� �������� 1, Ʈ���� �������� 70�̶� �����ϰ� ���������� �̵��ϸ� + �������� �̵��ϸ� -
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

	if (*h > 70) { // ���� 70�� ĭ�� �Ѿ�� �Ǹ� 70���� �ٲپ���
		*h = 70;
	}
	if (*h < 1) { // 1��ĭ���� �̲�������
		*h = 1;
	}
}


int Race() {
	

	int square[70]; // 70���� ������ ������

	for (int i = 0; i < 70; ++i) {
		square[i] = i + 1; // ù ĭ�� 1��ĭ
	}
	
	
	int graphicCount = 0; // ���ְ� ���������� �� �� �ְ� ���ִ� �׷��� �׸��� ����
	
	cout << "��Ⱑ ���۵˴ϴ�." << endl;
	while (Hare != 70 && Tortoise != 70) { // �䳢�� �ź��� �� ��ΰ� 70��ĭ�� �������� ������ �� ������ ���� ����ؼ� �䳢�� �ź��� �̵�
		
		cout << "��";
		
		Sleep(100);

		moveHare(HarePtr);
		moveTortoise(TortoisePtr);

		graphicCount++;
		if (graphicCount % 10 == 0) {
			cout << endl;
		}
	}


	if (Hare == Tortoise) { // �䳢�� �ź��� ��� 70�� ĭ�̸� 0�� ����
		return 0;
	}


	if (Hare == 70) { // �䳢�� 70�� ĭ�� �����ϸ� 1�� return
		return 1;
	}
	if (Tortoise == 70) { //�ź��̰� 70�� ĭ�� �����ϸ� 2�� return
		return 2;
	}

}
void displayMessage(int q) {
	switch (q) {
	case 0: 
		cout << "\n\n�䳢�� �ź��̰� ���ÿ� ������� �����߽��ϴ�!" << endl;
		break;
	case 1:
		cout << "\n\n�䳢�� �¸��߽��ϴ�! �䳢�� ��ٰ� ����߸� �����մϴ�." << endl;
		break;
	case 2:
		cout << "\n\n�ź��̰� �¸��߽��ϴ�! �ź��̰� ��ٰ� ����߸� �����մϴ�." << endl;
		break;
	}
}