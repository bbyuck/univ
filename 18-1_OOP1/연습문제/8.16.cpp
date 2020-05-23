#include <iostream>
#include <iomanip>

using namespace std;

int accumulator;
int memory[100];
int fatalErrorFlag = 0; // ġ���� ���� �÷���

void displayMessage(); // �Լ� ������Ÿ��
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

void setOpCode(int ir) { // op code �۵� ����
	int operationCode; // op code;
	int operand; // �ǿ�����

	operationCode = ir / 100; // �� ���ڸ�
	operand = ir % 100; // �� ���ڸ�


	switch (operationCode) {
		// �Է� �б�
	case 10: // op code 10 read
		cout << "���ڸ� �Է� : ";
		cin >> memory[operand];
		memory[operand] = memory[operand];
		if (memory[operand] > 9999 || memory[operand] < -9999) { // ����� �����÷ο�
			fatalErrorFlag = 2;
			break;
		}
		break;
	case 11: // op code 11 write
		cout << operand << "��ġ�� ����Ǿ� �ִ� �� : " << memory[operand] << endl;
		break;
		//���� �� �ҷ�����
	case 20: // op code 20 load
		accumulator = memory[operand];
		break;
	case 21: //op code store
		memory[operand] = accumulator;
		break;
		//���
	case 30: // op code add
		memory[operand] += accumulator;
		accumulator = memory[operand];
		if (accumulator > 9999) {
			fatalErrorFlag = 2; //����� �����÷ο�
			break;
		}
		break;
	case 31: // op code subtract
		memory[operand] = accumulator - memory[operand];
		accumulator = memory[operand];
		if (accumulator < -9999) {
			fatalErrorFlag = 2; // ����� �����÷ο�
			break;
		}
		break;
	case 32: // op code divide
		if (accumulator == 0) {
			fatalErrorFlag = 1; // ������ ���� �߻��� flag�� 0����
			break;
		}
		memory[operand] = memory[operand] / accumulator;
		accumulator = memory[operand];
		break;
	case 33: //op code multiply
		memory[operand] *= accumulator;
		accumulator = memory[operand];
		if (accumulator > 9999 || accumulator < -9999) {
			fatalErrorFlag = 2; // ����� �����÷ο�
			break;
		}
		break;
		// �̵�����
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
		fatalErrorFlag = 3; // ���ǵ��� ���� op code ���� �߻��ϴ� ����
		break;
	}


}

void memoryInitialize() {
	for (int i = 0; i < 100; ++i) { // memory ��ġ �ʱ�ȭ
		memory[i] = 0;
	}
}


void Simpletron() {
	memoryInitialize(); // �޸� �ʱ�ȭ

	displayMessage(); // ���α׷� ������ �ȳ� prompt

	int instructionCounter = 0;
	int instructionRegister; // ��ɾ�
	

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
			break; // instructorCounter ��ŭ OpCode ������ for������ ����
		}
		
		if (instructionRegister < -9999 || instructionRegister > 9999) { // �߸��� �� �Է��� ���
			cout << "�߸��� ���� �Է��߽��ϴ�. �ٽ� �Է��ϼ���." << endl;
			continue;
		}
		
		memory[instructionCounter] = instructionRegister;
		setOpCode(instructionRegister);
		++instructionCounter;

		if (fatalErrorFlag == 1) { // �����÷��װ� 1�̸� 0���� �������� ���
			cout << "*** Attempt to divide by zero ***" << endl;
			cout << "*** Simpletron excution abnormally terminated ***" << endl;
			break;
		}
		if (fatalErrorFlag == 2) {
			cout << "*** �ùķ��̼� ����� ������ �ʰ��߽��ϴ�. ***";
			cout << "\n*** Simpletron�� ������������ ����Ǿ����ϴ�. ***" << endl;
			break;
		}
		if (fatalErrorFlag == 3) {
			cout << "*** ���ǵ��� ���� OP Code�� �Է��߽��ϴ�. ***";
			cout << "\n*** OperationRegister ���� �޸𸮿� �����߽��ϴ�. ***" << endl;
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
	for (int i = 0; i < 10; ++i) { // ǥ�� ���� index
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