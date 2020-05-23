#include <iostream>
#include <array>
#include <ctime>
#include <iomanip>
#include <string>


using namespace std;

array<array<int, 8>, 8> chessBoard{ 0, }; // 체스판 8X8 배열

array<array<int, 8>, 8> heuristicBoard{ 0, };



array<int, 8> horizontal{ 2, 1, -1, -2, -2, -1, 1, 2 }; // 가로이동 1차원 배열 [8] 
array<int, 8> vertical{ -1, -2, -2, -1, 1, 2, 2, 1 }; // 세로이동 1차원 배열 [8]

int currentRow = 0;
int currentColumn = 0;

int flag = 1; // Knight's tour를 정상적으로 마쳤는지 아닌지 체크할 flag 변수 만약 0이면 64까지 모두 돌지 못함

void printBoard(array<array<int, 8>, 8> board) { // 8X8 체스보드 출력함수
	for (int row = 0; row < chessBoard.size(); ++row) {
		for (int column = 0; column < chessBoard[row].size(); ++column) {
			cout << " " << chessBoard[row][column] << "  ";
		}
		cout << endl << endl;
	}
}

bool MovingCheck(int r, int c) { 
	
	int i = r;
	int j = c;
	

	if (i < 0) { // 나이트가 체스판 밖으로 나가면
		return false;
	}
	else if (j < 0) {
		return false;
	}
	else if (i > 7) {
		return false;
	}
	else if (j > 7) {
		return false;
	}
	return true;
}

void BoardHeuristic() { // (c)의 heuristic board를 만들기위한 함수
	
	int accessibility;


	for (currentRow = 0; currentRow < chessBoard.size(); currentRow++) {
		
		for (currentColumn = 0; currentColumn < chessBoard[currentRow].size(); currentColumn++) {
			accessibility = 0;
			
			for (int moveNumber = 0; moveNumber < vertical.size(); moveNumber++){
				if (MovingCheck (currentRow + vertical[moveNumber], currentColumn + horizontal[moveNumber]) == 1) { // (x, y)
					accessibility++; // (0, 0) ~ (7, 7) 까지의 점에서 각각 8번의 이동을 실행하고 이동가능한 점의 갯수를 각점에 더해줌
				}
			}
			chessBoard[currentRow][currentColumn] = accessibility; // chessBoard에 각 칸에서 이동가능한 칸의 갯수를 입력
		}
	}

}
void printRoot() {
	for (int i = 0; i < heuristicBoard.size(); ++i) {
		for (int j = 0; j < heuristicBoard[i].size(); ++j) {
			cout << heuristicBoard[i][j] << setw(5);
		}
		cout << "\n" << endl;
	}
}

int FindRoot() {  // 1, 5에서 어떻게 버그를 잡을까?
	int lowest = 8; // 8의 accessibility가 가장 큰 accessibility
	int lowestMoveNum = 0;

	
	chessBoard[currentRow][currentColumn] = 10; // 지나온 칸은 heuristic 최대치보다 큰 10으로 설정해 더이상 이동하지 못하게함.
	
	for (int i = 0; i < chessBoard.size(); ++i) {
		for (int j = 0; j < chessBoard[i].size(); ++j) {
			lowestMoveNum = 0; // 경로 리턴할 변수
			for (int moveNumber = 0; moveNumber < vertical.size(); moveNumber++) { // 각 칸마다 어느 경로로 가야 가장 작은 수의 칸으로 이동하는지 확인
				if (MovingCheck(currentRow + vertical[moveNumber], currentColumn + horizontal[moveNumber]) == 1) { // (x, y)
					if (lowest >= chessBoard[currentRow + vertical[moveNumber]][currentColumn + horizontal[moveNumber]]) {
						lowest = chessBoard[currentRow + vertical[moveNumber]][currentColumn + horizontal[moveNumber]];
						lowestMoveNum = moveNumber;
					}
				}
			}
			return lowestMoveNum;
		}
	}

	 // 다음 칸으로 이동할 moveNumber 반환.
}
void KnightTourFreq() {

	

	for (int i = 0; i < heuristicBoard.size(); i++) {
		for (int j = 0; j < heuristicBoard[i].size(); j++) {
			heuristicBoard[i][j] = 0;
		}
	} // 지나간 횟수 구하는 함수에서 이용 후 초기화

	BoardHeuristic(); // 경험적인 알고리즘 사용을 위해 chessBoard 초기화

	cout << "Knight가 어떤 칸을 지났는지에 대한 여부를 출력합니다. (지나갔으면 1, 안지났으면 0으로 출력)\n" << endl;
	cout << "행 : ";
	cin >> currentRow;
	cout << "열 : ";
	cin >> currentColumn;

	int frequency = 1;// 칸 방문횟수


	for (int moveCount = 1; moveCount <= 64; moveCount++) { // 64번의 카운트

		

		int rootcount = FindRoot();
		heuristicBoard[currentRow][currentColumn] += frequency;// 이동한 칸마다 heuristicBoard에 기록
		currentRow += vertical[rootcount]; // FindRoot()함수를 통해 찾은 경험적인 루트를 따라 Knight를 이동시킴
		currentColumn += horizontal[rootcount];


		if (moveCount <= 64) {
			if (MovingCheck(currentRow, currentColumn) == 0) {
				cout << "(" << currentRow - vertical[rootcount] << ", " << currentColumn - horizontal[rootcount] << ") 에서 tour 종료\n" << endl;
				break;
			}
		}
	}

	printRoot();

}

void KnightTourRoot() {

	BoardHeuristic(); // 경험적인 알고리즘 사용을 위해 chessBoard 초기화

	cout << "경로를 탐색합니다.\n" << endl;
	cout << "행 : ";
	cin >> currentRow;
	cout << "열 : ";
	cin >> currentColumn;

	int frequency = 1;// 칸 방문횟수


	for (int moveCount = 1; moveCount <= 64; moveCount++) { // 64번의 카운트


		int rootcount = FindRoot();
		heuristicBoard[currentRow][currentColumn] = moveCount;// 이동한 칸마다 heuristicBoard에 기록
		currentRow += vertical[rootcount]; // FindRoot()함수를 통해 찾은 경험적인 루트를 따라 Knight를 이동시킴
		currentColumn += horizontal[rootcount];


		if (moveCount <= 64) {
			if (MovingCheck(currentRow, currentColumn) == 0) {
				cout << "(" << currentRow - vertical[rootcount] << ", " << currentColumn - horizontal[rootcount] << ") 에서 tour 종료\n" << endl;
				break;
			}
		}
	}

	printRoot();
}






int main() {
	
	KnightTourRoot(); // KnightTour의 경로를 찾는 함수
	
	
	cout << endl;
	
	
	KnightTourFreq(); // Knight가 지나간 칸들을 1 로 표현한 함수
	

}