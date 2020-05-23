#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <vector>
#include <string>
using namespace std;

int main() {
	fstream outFile{ "phoneNumber.dat", ios::out };

	const vector<char> two{ 'A', 'B', 'C' };
	const vector<char> three{ 'D', 'E', 'F' };
	const vector<char> four{ 'G', 'H', 'I' };
	const vector<char> five{ 'J', 'K', 'L' };
	const vector<char> six{ 'M', 'N', 'O' };
	const vector<char> seven{ 'P', 'Q', 'R', 'S' };
	const vector<char> eight{ 'T', 'U', 'V' };
	const vector<char> nine{ 'W', 'X', 'Y', 'Z' };

	vector <vector<char>> numbers{ two, three, four, five, six, seven, eight, nine };

	string phoneNumber;
	char positionFlag[7];
	int positionKey[7];

	while (phoneNumber.size() != 7) {
		cout << "Phone number (7자리 , 0, 1 제외) 입력 : " << endl;
		cin >> phoneNumber;
	}

	for (int i = 0; i < 7; i++) {
		positionFlag[i] = phoneNumber.at(i);
		positionKey[i] = static_cast<int>(positionFlag[i]) - 50; // 입력받은 수 ASCII
	}

	for (int i1 = 0; i1 < (positionKey[0] == 5 || positionKey[0] == 7 ? 4 : 3); i1++) { // 번호들
		for (int i2 = 0; i2 < (positionKey[1] == 5 || positionKey[1] == 7 ? 4 : 3); i2++) {
			for (int i3 = 0; i3 < (positionKey[2] == 5 || positionKey[2] == 7 ? 4 : 3); i3++) {
				for (int i4 = 0; i4 < (positionKey[3] == 5 || positionKey[3] == 7 ? 4 : 3); i4++) {
					for (int i5 = 0; i5 < (positionKey[4] == 5 || positionKey[4] == 7 ? 4 : 3); i5++) {
						for (int i6 = 0; i6 < (positionKey[5] == 5 || positionKey[5] == 7 ? 4 : 3); i6++) {
							for (int i7 = 0; i7 < (positionKey[6] == 5 || positionKey[6] == 7 ? 4 : 3); i7++) {
								outFile << numbers[positionKey[0]][i1]
									<< numbers[positionKey[1]][i2]
									<< numbers[positionKey[2]][i3]
									<< numbers[positionKey[3]][i4]
									<< numbers[positionKey[4]][i5]
									<< numbers[positionKey[5]][i6]
									<< numbers[positionKey[6]][i7] << ' ';
							}
						}
					}
				}
			}
		}
	}
}