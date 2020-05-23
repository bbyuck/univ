// �ﰢ���� �� ���� �־� ������ ���� ū ������ ���� ������ �� ���� �պ��� �۾ƾ� �Ѵ�.

#include <iostream>


using namespace std;

class Triangle { // contest Ŭ���� ����

public:
	Triangle(double n, double l, double t) { // ������
		number = n;
		largest = l;
		total = t;
	}

	void setNumber(double n) {
		number = n;
	}
	void setTotal(double t) {
		total = total + number;
	}
	void setLargest(double l) { // ���� ū �� �̴� setLargest �Լ�
		if (largest == 0) {
			largest = number;
		}
		else if (largest < number) {
			largest = number;
		}
		else largest = largest;
	}
	double getNumber() { // ���� ���Ͻ�ų get�Լ�
		return number;
	}
	double getLargest() {
		return largest;
	}
	double getDetermine() {
		if (total - largest > largest) { //{�˰���} �ﰢ�� �� ���� ��(total) - ���� �� ���� ����(largest)�� �� ���� = [���� �� ���� ������ ��] >���� �� ���� ����(largest)
			return 1; // �ﰢ���� ������ �Ǹ� 1�� ��ȯ
		}
		else {
			return 0;
		}
	}

private:
	double number; // �������
	double largest;
	double total; // �ﰢ�� �� ���� ��
};

int main() {
	double number = 0;
	double largest = 0;
	double total = 0;


	Triangle Determine(number, largest, total);
	int counter = 1;

	while (counter <= 3) { // while���� ���� total, largest �� ���
		cout << "Enter nonzero values : "; // prompt
		cin >> number;
		Determine.setNumber(number);
		Determine.setLargest(largest);
		Determine.setTotal(total);
		counter++;
	}
	if (Determine.getDetermine() == 1) { // �ﰢ���� ������ �� ������
		cout << "These three values can form a triangle.";
	}
	else { // ������
		cout << "These three values can't form a triangle.";
	}
}