#include <iostream>
#include <iomanip>

using namespace std;

int accumulator;
int memory[100];
int fatalErrorFlag = 0; // 치명적 오류 플래그

void displayMessage(); // 함수 프로토타입
void setOpCode(int);
void Simpletron();
void memoryInitialize();

int main() {
	
	Simpletron();

	return 0;
}

void displayMessage() {
	cout << "*** Welcome to Simpletron! ***";
	cout << "\n\n*** Please enter your program one instruction ***";
	cout << "\n*** (or data word) at a time. I will type the ***";
	cout << "\n*** location number and a question mark (?).  ***";
	cout << "\n*** You then type the word for that location. ***";
	cout << "\n*** Type the sentinel -99999 to stop entering ***";
	cout << "\n*** your program. ***\n\n";
}

void setOpCode(int ir) { // op code 작동 설정
	int operationCode; // op code;
	int operand; // 피연산자

	operationCode = ir / 100; // 앞 두자리
	operand = ir % 100; // 뒷 두자리


	switch (operationCode) {
		// 입력 읽기
	case 10: // op code 10 read
		cout << "숫자를 입력 : ";
		cin >> memory[operand];
		memory[operand] = memory[operand];
		if (memory[operand] > 9999 || memory[operand] < -9999) { // 누산기 오버플로우
			fatalErrorFlag = 2;
			break;
		}
		break;
	case 11: // op code 11 write
		cout << operand << "위치에 저장되어 있는 값 : " << memory[operand] << endl;
		break;
		//저장 및 불러오기
	case 20: // op code 20 load
		accumulator = memory[operand];
		break;
	case 21: //op code store
		memory[operand] = accumulator;
		break;
		//계산
	case 30: // op code add
		memory[operand] += accumulator;
		accumulator = memory[operand];
		if (accumulator > 9999) {
			fatalErrorFlag = 2; //누산기 오버플로우
			break;
		}
		break;
	case 31: // op code subtract
		memory[operand] = accumulator - memory[operand];
		accumulator = memory[operand];
		if (accumulator < -9999) {
			fatalErrorFlag = 2; // 누산기 오버플로우
			break;
		}
		break;
	case 32: // op code divide
		if (accumulator == 0) {
			fatalErrorFlag = 1; // 나눗셈 에러 발생시 flag를 0으로
			break;
		}
		memory[operand] = memory[operand] / accumulator;
		accumulator = memory[operand];
		break;
	case 33: //op code multiply
		memory[operand] *= accumulator;
		accumulator = memory[operand];
		if (accumulator > 9999 || accumulator < -9999) {
			fatalErrorFlag = 2; // 누산기 오버플로우
			break;
		}
		break;
		// 이동제어
	case 40: //op code branch
		memory[operand] = operand;
		break;
	case 41: //op code branchneg
		if (accumulator < 0) {
			memory[operand] = operand;
		}
		break;
	case 42: //op code branchzero
		if (accumulator == 0) {
			memory[operand] = operand;
		}
		break;
	case 43: // op code halt
		cout << "*** Simpletron execution terminated ***\n" << endl;
		break;

	default:
		fatalErrorFlag = 3; // 정의되지 않은 op code 사용시 발생하는 에러
		break;
	}


}

void memoryInitialize() {
	for (int i = 0; i < 100; ++i) { // memory 위치 초기화
		memory[i] = 0;
	}
}


void Simpletron() {
	memoryInitialize(); // 메모리 초기화

	displayMessage(); // 프로그램 실행후 안내 prompt

	int instructionCounter = 0;
	int instructionRegister; // 명령어
	

	while (instructionCounter < 100) {
		cout << noshowpos;
		if (instructionCounter < 10) {
			cout << '0';
		}
		
		cout << instructionCounter << " ? ";
		cin >> instructionRegister;
		

		if (instructionRegister == -99999) {
			cout << "\n*** Program loading completed ***" << endl;
			cout << "*** Program execution begins ***" << endl;
			break; // instructorCounter 만큼 OpCode 연산을 for문으로 실행
		}
		
		if (instructionRegister < -9999 || instructionRegister > 9999) { // 잘못된 값 입력한 경우
			cout << "잘못된 수를 입력했습니다. 다시 입력하세요." << endl;
			continue;
		}
		
		memory[instructionCounter] = instructionRegister;
		setOpCode(instructionRegister);
		++instructionCounter;

		if (fatalErrorFlag == 1) { // 에러플래그가 1이면 0으로 나누어준 경우
			cout << "*** Attempt to divide by zero ***" << endl;
			cout << "*** Simpletron excution abnormally terminated ***" << endl;
			break;
		}
		if (fatalErrorFlag == 2) {
			cout << "*** 시뮬레이션 결과가 범위를 초과했습니다. ***";
			cout << "\n*** Simpletron이 비정상적으로 종료되었습니다. ***" << endl;
			break;
		}
		if (fatalErrorFlag == 3) {
			cout << "*** 정의되지 않은 OP Code를 입력했습니다. ***";
			cout << "\n*** OperationRegister 값만 메모리에 저장했습니다. ***" << endl;
			fatalErrorFlag = 0;
		}
	}
	int i = instructionCounter;
	
	
	
	cout << "\nREGISTERS: " << endl;
	
	
	cout << "accumulator" << setw(14) << accumulator << endl;
	
	cout << "instructionCounter" << setw(7) << i << endl;
	cout << "instruction Register" << setw(5) << memory[instructionCounter - 1] << endl;
	cout << "operationCode" << setw(12) << memory[instructionCounter - 1] / 100 << endl;
	cout << "operand" << setw(18) <<  memory[instructionCounter - 1] % 100 << endl;
	

	cout << "MEMORY:\n";

	cout << setw(9);
	for (int i = 0; i < 10; ++i) { // 표의 가로 index
		cout << i << setw(6);
	}
	cout << "\n";

	for (int row = 0; row < 10; ++row) {
		
		cout << noshowpos;
		if (row == 0) {
			cout << " ";
		}
		cout << (row * 10) << "  ";
		
		for (int column = 0; column < 10; column++) {
			cout << showpos;
			cout << setfill('0') << internal << setw(5);
			cout << memory[10 * row + column] << " ";
		}
		cout << endl;
		
	}

}