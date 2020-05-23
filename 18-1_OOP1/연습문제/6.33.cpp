#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int flip(); // 함수 프로토타입

int main() { // 메인함수
	int Heads = 0; // 0
	int Tails = 0; // 1
	srand((time(0)));

	for (unsigned int count = 0; count < 100; count++) {
		
		switch (flip()) { // heads 와 tails 각각 하나씩 추가해주는 switch문
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