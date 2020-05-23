// �� ���� ������� �ڵ��߽��ϴ�. �ϴܿ� /**/ �ּ�ó�� �Ͽ����ϴ�.

#include <iostream>

using namespace std;

class Palindromes { // ȸ�� Ŭ���� ����

public:

	Palindromes(int a, int b, int c, int d, int n) { // ������

		tenthousands = a;
		thousand = b;
		ten = c;
		units = d;
		Number = n;
	}

	void setNumber(int n) {
		Number = n;
	}
	void setTenThousands(int a, int n) {
		tenthousands = Number / 10000;
	}
	void setThousand(int b, int n, int a) {
		thousand = (Number / 1000) - tenthousands * 10;
	}

	void setTen(int c, int n) {
		ten = (Number % 100 - Number % 10) / 10;
	}
	void setUnits(int d, int n) {
		units = Number % 10;
	}

	int getTenThousands() {
		return tenthousands;
	}
	int	getThousands() {
		return thousand;
	}
	int getTen() {
		return ten;
	}
	int getUnits() {
		return units;
	}
	int getNumber() {
		return Number;
	}
	int getPalindromes() { // ȸ������ üũ�ϴ� �Լ�, �Է¹��� �� Number�� ȸ���ϰ�� 1�� ��ȯ, ȸ���� �ƴϸ� 0�� ��ȯ�Ѵ�.
		if (tenthousands == units) {
			if (thousand == ten) {
				return 1;
			}
			else {
				return 0;
			}
		}
		else {
			return 0;
		}
	}

private:
	int tenthousands;  // �������
	int thousand;
	int ten;
	int units;
	int Number;
};

int main() {
	int tenthousands = 0;  // �������, 100�� �ڸ� ���� ȸ���� ������ �� �� ���� (5�ڸ�������)
	int thousand = 0;
	int ten = 0;
	int units = 0;
	int Number = 0;

	Palindromes digit(tenthousands, thousand, ten, units, Number);

	while (true) {
		cout << "Enter five-digit integer (if you want to end, enter -1) : ";
		cin >> Number;
		if (Number == -1)
			break;

		digit.setNumber(Number);
		digit.setTenThousands(tenthousands, Number);
		digit.setThousand(thousand, Number, tenthousands);
		digit.setTen(ten, Number);
		digit.setUnits(units, Number);
		if (digit.getPalindromes() == 1) {
			cout << "The integer is Palindromes!" << endl;
		}
		else {
			cout << "The integer is not Palindromes." << endl;
		}
		cout << endl;
	}
}


/* get�Լ��� ���� �ҷ��� set�Լ��� ���� �ְ� ����� �� ���ſ���.
#include <iostream>

using namespace std;

class Palindromes { // ȸ�� Ŭ���� ����

public:
Palindromes(int a, int b, int c, int d,int n) { // ������
tenthousands = a;
thousand = b;
ten = c;
units = d;
Number = n;
}
void setNumber(int n) {
Number = n;
}
void setTenThousands(int a) {
tenthousands = getNumber() / 10000;
}
void setThousand(int b) {
thousand = (getNumber() / 1000) - getTenThousands() * 10;
}

void setTen(int c) {
ten = (getNumber() % 100 - getNumber() % 10) / 10;
}
void setUnits(int d) {
units = getNumber() % 10;
}

int getTenThousands() {
return tenthousands;
}
int	getThousands() {
return thousand;
}
int getTen() {
return ten;
}
int getUnits() {
return units;
}
int getNumber() {
return Number;
}
int getPalindromes() { // ȸ������ üũ�ϴ� �Լ�, �Է¹��� �� Number�� ȸ���ϰ�� 1�� ��ȯ, ȸ���� �ƴϸ� 0�� ��ȯ�Ѵ�.
if (tenthousands == units) {
if (thousand == ten) {
return 1;
}
else {
return 0;
}
}
else {
return 0;
}
}


private:
int tenthousands;  // �������
int thousand;
int ten;
int units;
int Number;
};

int main() {
int tenthousands = 0;  // �������, 100�� �ڸ� ���� ȸ���� ������ �� �� ���� (5�ڸ�������)
int thousand = 0;
int ten = 0;
int units = 0;
int Number = 0;

Palindromes digit(tenthousands, thousand, ten, units, Number);

while (true) {
cout << "Enter five-digit integer (if you want to end, enter -1) : ";
cin >> Number;
if (Number == -1)
break;
digit.setNumber(Number);
digit.setTenThousands(tenthousands);
digit.setThousand(thousand);
digit.setTen(ten);
digit.setUnits(units);
if (digit.getPalindromes() == 1) {
cout << "The integer is Palindromes!" << endl;
}
else {
cout << "The integer is not Palindromes." << endl;
}
cout << endl;
}
}
*/
