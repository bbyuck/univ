#include <iostream>

using namespace std;

class contest { // contest Ŭ���� ����

public:
	contest(int n, int l, int c) { // ������
		number = n;
		largest = l;
		counter = c;
	}

	void setNumber(int n) {
		number = n;
	}
	void setLargest(int l) { // ���� ū �� �̴� setLargest �Լ�
		if (counter == 1) {
			largest = number;
		}
		else if (largest < number) {
			largest = number;
		}
		else largest = largest;
	}
	void setCounter(int c) {
		counter = c;
	}

	int getNumber() { // ���� ���Ͻ�ų get�Լ�
		return number;
	}
	int getLargest() {
		return largest;
	}

private:
	int number; // �������
	int largest;
	int counter;
};

int main() {
	int counter = 1; // �ݺ������� ī���ͷ� ���
	int number = 0;
	int largest = 0;

	contest input(number, largest, counter);

	while (counter <= 10) { // while �� ���ؼ� counter ������ 1 ~ 10 ���� �ݺ��� �� �ֵ��� ���� ����
		if (counter == 1) {
			cout << "Enter 1st number : "; // ù��° �� �Է��� �� �ִ� prompt�� 1st UI 
		}
		else if (counter == 2) { // �ι�° �� �Է��� �� �ִ� prompt�� 2nd UI
			cout << "Enter 2nd number : ";
		}
		else if (counter == 3) { // ����° �� �Է��� �� �ִ� prompt�� 3rd UI
			cout << "Enter 3rd number : ";
		}
		else { // 4�̻��� �� �ڿ��� th ����.
			cout << "Enter " << counter << "th number : ";
		}
		cin >> number;
		input.setNumber(number);
		input.setLargest(largest);
		counter++;
		input.setCounter(counter); // class �� counter�� ������ �����־� ù ��°�� �Է¹��� ���� �������� largest ������ ���� �� �� �ֵ��� ������. because largest�� 0���� �ʱ�ȭ�߱� ������ getLargest �Լ��� else if���� �ٷ� ������ �����϶� ���� ū���� 0���� ��µǴ� ���� ������ ����.
	}

	cout << endl;
	cout << "The largest of 10 numbers input : " << input.getLargest() << endl;

	return 0;
}