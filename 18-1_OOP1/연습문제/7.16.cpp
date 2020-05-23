#include <iostream>
#include <ctime>
#include <random>
#include <array>

using namespace std;

int main() {
	srand(time(0));

	array<int, 11> frequency{ 0, };

	for (unsigned int count = 0; count < 36000000; ++count) { // 3600만번의 시뮬 for문
		unsigned int dice1 = 1 + rand() % 6;
		unsigned int dice2 = 1 + rand() % 6; // 두 개의 주사위

		switch (dice1 + dice2) {
		case 2: ++frequency[0];
			break;
		case 3: ++frequency[1];
			break;
		case 4: ++frequency[2];
			break;
		case 5: ++frequency[3];
			break;
		case 6: ++frequency[4];
			break;
		case 7: ++frequency[5];
			break;
		case 8: ++frequency[6];
			break;
		case 9: ++frequency[7];
			break;
		case 10: ++frequency[8];
			break;
		case 11: ++frequency[9];
			break;
		case 12: ++frequency[10];
			break;
		default:
			break;
		}
	}
	for (int fCount = 0; fCount < frequency.size(); ++fCount) {
		cout << fCount + 2 << (fCount + 2 >= 10 ? ": " : " : ") << frequency[fCount] << endl; // 각 눈금의 합이 나온 횟수 출력
	}
	return 0;
}