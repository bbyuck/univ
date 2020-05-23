#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

unsigned int rollDice();

int main() {

	int64_t bankBalance = 1000; // 1000�޷��� �ʱ�ȭ �������õ� ������ ������ ũ�Ⱑ Ŀ���� �����÷ο츦 �����ϱ�����
	int64_t wager; // ���ñݾ�

	while (bankBalance >= 0) {

		if (bankBalance == 0) {
			bankBalance = 1000;
		}

		cout << "\n���� �����ݾ� : $" << bankBalance << endl;
		cout << "\n������ �ݾ��� �Է��Ͻÿ�. : $";
		cin >> wager;
		

		if (wager > bankBalance) { // �����ݾ׺��� ���þ��� Ŭ ��� ���Է� prompt ����� ó������ �ٽ� loop ����
			cout << "������ �ݾ��� �ʹ� �����ϴ�. �ٽ� �Է��ϼ���." << endl;
			continue;
		}

		else if (wager < 0) {
			cout << "�߸� �Է��߽��ϴ�. �ٽ� �Է��ϼ���." << endl;
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
			bankBalance += wager; // �̱�� �����ݾ׿� ���ñݾ׸�ŭ �����ش�
			break;
		case 2:
		case 3:
		case 12:
			gameStatus = Status::LOST;
			bankBalance -= wager; // ���� �����ݾ׿��� ���ñݾ׸�ŭ ���ش�
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
				bankBalance += wager; //�̱�� �����ݾ׿� ���ñݾ׸�ŭ �����ش�
			}
			else {
				if (sumOfDice == 7) {
					gameStatus = Status::LOST;
					bankBalance -= wager; // ���� �����ݾ׿��� ���ñݾ׸�ŭ ���ش�
				}
			}
		}


		if (Status::WON == gameStatus) {
			cout << "Player wins" << endl;
		}
		else {
			cout << "Player loses" << endl;
		}

		if (bankBalance == 0) { // �Ļ�� ����� �޼���
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

		// ���� ���࿡ ���� chatter
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