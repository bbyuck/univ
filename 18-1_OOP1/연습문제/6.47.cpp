#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

unsigned int rollDice();

int main() {

	int64_t bankBalance = 1000; // 1000달러로 초기화 돈과관련된 변수는 데이터 크기가 커야함 오버플로우를 방지하기위해
	int64_t wager; // 베팅금액

	while (bankBalance >= 0) {

		if (bankBalance == 0) {
			bankBalance = 1000;
		}

		cout << "\n현재 보유금액 : $" << bankBalance << endl;
		cout << "\n베팅할 금액을 입력하시오. : $";
		cin >> wager;
		

		if (wager > bankBalance) { // 보유금액보다 베팅액이 클 경우 재입력 prompt 출력후 처음부터 다시 loop 시작
			cout << "보유한 금액이 너무 적습니다. 다시 입력하세요." << endl;
			continue;
		}

		else if (wager < 0) {
			cout << "잘못 입력했습니다. 다시 입력하세요." << endl;
			wager = bankBalance;
			continue;
		}

		enum class Status { CONTINUE, WON, LOST };

		srand(static_cast<unsigned int>(time(0)));

		unsigned int myPoint{ 0 };
		Status gameStatus;

		unsigned int sumOfDice{ rollDice() };

		switch (sumOfDice) {
		case 7:
		case 11:
			gameStatus = Status::WON;
			bankBalance += wager; // 이기면 보유금액에 베팅금액만큼 더해준다
			break;
		case 2:
		case 3:
		case 12:
			gameStatus = Status::LOST;
			bankBalance -= wager; // 지면 보유금액에서 베팅금액만큼 빼준다
			break;
		default:
			gameStatus = Status::CONTINUE;
			myPoint = sumOfDice;
			cout << "Point is " << myPoint << endl;
			break;
		}

		while (Status::CONTINUE == gameStatus) {
			sumOfDice = rollDice();

			if (sumOfDice == myPoint) {
				gameStatus = Status::WON;
				bankBalance += wager; //이기면 보유금액에 베팅금액만큼 더해준다
			}
			else {
				if (sumOfDice == 7) {
					gameStatus = Status::LOST;
					bankBalance -= wager; // 지면 보유금액에서 베팅금액만큼 빼준다
				}
			}
		}


		if (Status::WON == gameStatus) {
			cout << "Player wins" << endl;
		}
		else {
			cout << "Player loses" << endl;
		}

		if (bankBalance == 0) { // 파산시 출력할 메세지
			cout << "\n#######Sorry, You busted!#######" << endl;
		}

		if (bankBalance == 0) {
			cout << "One more game? (y/n)" << endl;
			char cont;
			cin >> cont;
			if (cont == 121) {
				continue;
			}
			
			else if (cont == 110) {
				break;
			}
		}

		// 게임 진행에 따른 chatter
		if (bankBalance <= 200) {
			if (bankBalance == 0) {
				break;
			}
			cout << "\n###Oh, you're going for broke, huh?###" << endl;
		}
		
		if (bankBalance >= 2000) {
			cout << "\n###You're up big. Now's the time to cash in your chips!###" << endl;
		}
	}
	return 0;
}

unsigned int rollDice() {
	int die1{ 1 + rand() % 6 };
	int die2{ 1 + rand() % 6 };
	int sum{ die1 + die2 };

	cout << "Player rolled " << die1 << " + " << die2 << " = " << sum << endl;
	return sum;
}