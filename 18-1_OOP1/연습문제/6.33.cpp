#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int flip(); // �Լ� ������Ÿ��

int main() { // �����Լ�
	int Heads = 0; // 0
	int Tails = 0; // 1
	srand((time(0)));

	for (unsigned int count = 0; count < 100; count++) {
		
		switch (flip()) { // heads �� tails ���� �ϳ��� �߰����ִ� switch��
		case 0 : cout << "Heads" << endl;
			Heads++;
			break;
		
		case 1 : cout << "Tails" << endl;
			Tails++;
			break;
		
		default :
			break;
		}
	}
	cout << "\nHeads : " << Heads << endl;
	cout << "Tails : " << Tails << endl;
	return 0;
}

int flip() {
	
	int coin =  rand() % 2;

	return coin;
	}