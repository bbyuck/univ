#include <iostream>

using namespace std;

class Smallest {

public:
	Smallest(int x, int s, int c) { // ������
		num = x;
		smallest = s;
		counter = c;
	} // Smallest ���ȣ ��

	void setNum(int x) {
		num = x;
	}
	void setCounter(int c) {
		counter = c;
	}
	void setSmallest(int x, int s, int c) {
		if (c == 1) {
			smallest = num;
		}
		else if (smallest <= num) {
			smallest = smallest;
		}
		else {
			smallest = num;
		}
	}	// ���� ������ set�Լ��� ������ ���� �ʿ� �����Ƿ� ������ Ÿ���� void��

	int getSmallest() {
		return smallest;
	}


private:
	int num; // ������� �Է¹��� ��, ���� ���� ���� ������ ����
	int smallest;
	int counter;
};

int main() {
	int num = 0;
	int smallest = 0;
	int ncounter = 0; // �Է¹��� ������ ����
	int counter = 1;
	cout << "�Է��� ������ ������ �Է��ϼ���" << endl; // prompt
	cin >> ncounter; //

	Smallest integer(num, smallest, counter);

	while (counter <= ncounter) {
		cout << "������ �Է��ϼ��� ";
		cin >> num;
		integer.setNum(num);
		integer.setSmallest(num, smallest, counter);
		++counter;
		integer.setCounter(counter);
	}
	cout << "���� ���� ������ " << integer.getSmallest() << "�Դϴ�.";

	return 0;
}