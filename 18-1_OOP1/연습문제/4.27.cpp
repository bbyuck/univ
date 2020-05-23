// 두 가지 방식으로 코딩했습니다. 하단에 /**/ 주석처리 하였습니다.

#include <iostream>

using namespace std;

class Palindromes { // 회문 클래스 선언

public:

	Palindromes(int a, int b, int c, int d, int n) { // 생성자

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
	int getPalindromes() { // 회문인지 체크하는 함수, 입력받은 수 Number가 회문일경우 1을 반환, 회문이 아니면 0을 반환한다.
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
	int tenthousands;  // 멤버변수
	int thousand;
	int ten;
	int units;
	int Number;
};

int main() {
	int tenthousands = 0;  // 멤버변수, 100의 자리 수는 회문에 영향을 줄 수 없다 (5자리수에서)
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


/* get함수로 값을 불러와 set함수에 값을 넣고 계산한 것 무거워짐.
#include <iostream>

using namespace std;

class Palindromes { // 회문 클래스 선언

public:
Palindromes(int a, int b, int c, int d,int n) { // 생성자
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
int getPalindromes() { // 회문인지 체크하는 함수, 입력받은 수 Number가 회문일경우 1을 반환, 회문이 아니면 0을 반환한다.
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
int tenthousands;  // 멤버변수
int thousand;
int ten;
int units;
int Number;
};

int main() {
int tenthousands = 0;  // 멤버변수, 100의 자리 수는 회문에 영향을 줄 수 없다 (5자리수에서)
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
