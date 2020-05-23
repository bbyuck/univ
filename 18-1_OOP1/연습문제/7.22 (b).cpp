#include <iostream>
#include <array>
#include <ctime>
#include <iomanip>
#include <string>


using namespace std;

array<array<int, 8>, 8> chessBoard{ 0, }; // ü���� 8X8 �迭

array<array<int, 8>, 8> heuristicBoard{ 0, };



array<int, 8> horizontal{ 2, 1, -1, -2, -2, -1, 1, 2 }; // �����̵� 1���� �迭 [8] 
array<int, 8> vertical{ -1, -2, -2, -1, 1, 2, 2, 1 }; // �����̵� 1���� �迭 [8]

int currentRow = 0;
int currentColumn = 0;

int flag = 1; // Knight's tour�� ���������� ���ƴ��� �ƴ��� üũ�� flag ���� ���� 0�̸� 64���� ��� ���� ����

void printBoard(array<array<int, 8>, 8> board) { // 8X8 ü������ ����Լ�
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
	

	if (i < 0) { // ����Ʈ�� ü���� ������ ������
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

void BoardHeuristic() { // (c)�� heuristic board�� ��������� �Լ�
	
	int accessibility;


	for (currentRow = 0; currentRow < chessBoard.size(); currentRow++) {
		
		for (currentColumn = 0; currentColumn < chessBoard[currentRow].size(); currentColumn++) {
			accessibility = 0;
			
			for (int moveNumber = 0; moveNumber < vertical.size(); moveNumber++){
				if (MovingCheck (currentRow + vertical[moveNumber], currentColumn + horizontal[moveNumber]) == 1) { // (x, y)
					accessibility++; // (0, 0) ~ (7, 7) ������ ������ ���� 8���� �̵��� �����ϰ� �̵������� ���� ������ ������ ������
				}
			}
			chessBoard[currentRow][currentColumn] = accessibility; // chessBoard�� �� ĭ���� �̵������� ĭ�� ������ �Է�
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

int FindRoot() {  // 1, 5���� ��� ���׸� ������?
	int lowest = 8; // 8�� accessibility�� ���� ū accessibility
	int lowestMoveNum = 0;

	
	chessBoard[currentRow][currentColumn] = 10; // ������ ĭ�� heuristic �ִ�ġ���� ū 10���� ������ ���̻� �̵����� ���ϰ���.
	
	for (int i = 0; i < chessBoard.size(); ++i) {
		for (int j = 0; j < chessBoard[i].size(); ++j) {
			lowestMoveNum = 0; // ��� ������ ����
			for (int moveNumber = 0; moveNumber < vertical.size(); moveNumber++) { // �� ĭ���� ��� ��η� ���� ���� ���� ���� ĭ���� �̵��ϴ��� Ȯ��
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

	 // ���� ĭ���� �̵��� moveNumber ��ȯ.
}
void KnightTourFreq() {

	

	for (int i = 0; i < heuristicBoard.size(); i++) {
		for (int j = 0; j < heuristicBoard[i].size(); j++) {
			heuristicBoard[i][j] = 0;
		}
	} // ������ Ƚ�� ���ϴ� �Լ����� �̿� �� �ʱ�ȭ

	BoardHeuristic(); // �������� �˰��� ����� ���� chessBoard �ʱ�ȭ

	cout << "Knight�� � ĭ�� ���������� ���� ���θ� ����մϴ�. (���������� 1, ���������� 0���� ���)\n" << endl;
	cout << "�� : ";
	cin >> currentRow;
	cout << "�� : ";
	cin >> currentColumn;

	int frequency = 1;// ĭ �湮Ƚ��


	for (int moveCount = 1; moveCount <= 64; moveCount++) { // 64���� ī��Ʈ

		

		int rootcount = FindRoot();
		heuristicBoard[currentRow][currentColumn] += frequency;// �̵��� ĭ���� heuristicBoard�� ���
		currentRow += vertical[rootcount]; // FindRoot()�Լ��� ���� ã�� �������� ��Ʈ�� ���� Knight�� �̵���Ŵ
		currentColumn += horizontal[rootcount];


		if (moveCount <= 64) {
			if (MovingCheck(currentRow, currentColumn) == 0) {
				cout << "(" << currentRow - vertical[rootcount] << ", " << currentColumn - horizontal[rootcount] << ") ���� tour ����\n" << endl;
				break;
			}
		}
	}

	printRoot();

}

void KnightTourRoot() {

	BoardHeuristic(); // �������� �˰��� ����� ���� chessBoard �ʱ�ȭ

	cout << "��θ� Ž���մϴ�.\n" << endl;
	cout << "�� : ";
	cin >> currentRow;
	cout << "�� : ";
	cin >> currentColumn;

	int frequency = 1;// ĭ �湮Ƚ��


	for (int moveCount = 1; moveCount <= 64; moveCount++) { // 64���� ī��Ʈ


		int rootcount = FindRoot();
		heuristicBoard[currentRow][currentColumn] = moveCount;// �̵��� ĭ���� heuristicBoard�� ���
		currentRow += vertical[rootcount]; // FindRoot()�Լ��� ���� ã�� �������� ��Ʈ�� ���� Knight�� �̵���Ŵ
		currentColumn += horizontal[rootcount];


		if (moveCount <= 64) {
			if (MovingCheck(currentRow, currentColumn) == 0) {
				cout << "(" << currentRow - vertical[rootcount] << ", " << currentColumn - horizontal[rootcount] << ") ���� tour ����\n" << endl;
				break;
			}
		}
	}

	printRoot();
}






int main() {
	
	KnightTourRoot(); // KnightTour�� ��θ� ã�� �Լ�
	
	
	cout << endl;
	
	
	KnightTourFreq(); // Knight�� ������ ĭ���� 1 �� ǥ���� �Լ�
	

}