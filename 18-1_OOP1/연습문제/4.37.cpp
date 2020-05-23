//4장 Exercise 4.37 하나의 클래스 Encrypt에 암호화 함수와 해독함수 모두를 코딩했습니다.
//입력받은 정수의 각 자리수에 대한 변수를 3개씩 잡았습니다. ex) th(input), xth(암호화), rth(해독)

#include <iostream>

using namespace std;

class Encrypt {
public:
	Encrypt(int i, int th, int t, int h, int u, int xth, int xh, int xt, int xu, int k, int rth, int rh, int rt, int ru) { // 생성자
		integer = i;

		thousand = th;
		hundred = h;
		ten = t;
		units = u;

		xthousand = xth;
		xhundred = xh;
		xten = xt;
		xunits = xu;

		rthousand = rth;
		rhundred = rh;
		rten = rt;
		runits = ru;

		key = k;
	}
	void setInteger(int i) {
		integer = i;
	}

	void setThousand(int i, int th) {
		th = i / 1000;
		thousand = th;
	}
	void setHundred(int i, int h) {
		h = (i % 1000) / 100;
		hundred = h;
	}
	void setTen(int i, int u, int t) {
		t = (i % 100) / 10;
		ten = t;
	}
	void setUnits(int i, int u) {
		u = i % 10;
		units = u;
	}

	// 암호화 단계 1 함수 

	void setXThousand(int xth, int th) {
		xth = (thousand + 7) % 10;
		xthousand = xth;
	}
	void setXHundred(int xh, int h) {
		xh = (hundred + 7) % 10;
		xhundred = xh;
	}
	void setXTen(int xt, int t) {
		xt = (ten + 7) % 10;
		xten = xt;
	}
	void setXUnits(int xu, int u) {
		xu = (units + 7) % 10;
		xunits = xu;
	}

	// 암호화 단계 2 함수

	void setChange1(int xth, int xt, int k) { // 첫번째 숫자랑 세번째 숫자 바꾸기
		k = xthousand;
		xthousand = xten;
		xten = k;
	}
	void setChange2(int xh, int xu, int k) { // 두번째 숫자랑 네번째 숫자 바꾸기
		k = xhundred;
		xhundred = xunits;
		xunits = k;
	}


	//해독 1단계

	void setRThousand(int rth, int th) { // 각 자리수는 모두 한자리수 이므로 +10 - 7 을 한 후 10으로 나눈 나머지가 암호화 이전의 수이다.
		rth = (thousand + 3) % 10;
		rthousand = rth;
	}
	void setRHundred(int rh, int h) {
		rh = (hundred + 3) % 10;
		rhundred = rh;
	}
	void setRTen(int rt, int t) {
		rt = (ten + 3) % 10;
		rten = rt;
	}
	void setRUnits(int ru, int u) {
		ru = (units + 3) % 10;
		runits = ru;
	}
	

	void setEncrypt() { // 출력만을 돕는 void 타입 set 함수 ( 4자리 정수를 모두 묶어서 출력할 경우 천의자리 숫자가 0인 경우 세자리 수로 출력이 된다. 따라서 숫자들을 따로 끊어서 출력)
		cout << xthousand << xhundred << xten << xunits;
	}

	void setSolution() { // 암호를 만드는것과 동일하게 중간변수 k를 이용해 자릿수에 할당된 수를 아예 바꾸어 줄 수도 있지만 출력순서만 바꾸어 숫자를 조합하는 방법도 있다.
		cout << rten << runits << rthousand << rhundred;
	}

private:
	int integer; // 입력받을 수 i

	int thousand; // 입력받은 4자리 정수의 각자리 수 멤버변수
	int hundred;
	int ten;
	int units;

	int	xthousand; // 암호화된 수를 저장할 멤버변수
	int xhundred;
	int xten;
	int xunits;

	int rthousand; // 암호 해독한 수를 저장할 변수
	int rhundred;
	int rten;
	int runits;

	int key; // 암호화 중간값 저장해 암호화 돕는 멤버변수
};

int main() {
	int integer = 0; // 입력받을 수 i

	int thousand = 0; // 입력받은 4자리 정수의 각자리 수 멤버변수
	int hundred = 0;
	int ten = 0;
	int units = 0;

	int	xthousand = 0; // 암호화된 수를 저장할 멤버변수
	int xhundred = 0;
	int xten = 0;
	int xunits = 0;

	int rthousand = 0; // 암호 해독한 수를 저장할 변수
	int rhundred = 0;
	int rten = 0;
	int runits = 0;

	int key = 0; // 암호화 중간값 저장해 암호화 돕는 멤버변수

	Encrypt make(integer, thousand, hundred, ten, units, xthousand, xhundred, xten, xunits, key, rthousand, rhundred, rten, runits);

	cout << "전송할 4자리 정수를 입력하시오 : "; // prompt
	cin >> integer;  // user input
	make.setInteger(integer);
	make.setThousand(integer, thousand);
	make.setHundred(integer, hundred);
	make.setTen(integer, units, ten);
	make.setUnits(integer, units);
	make.setXThousand(xthousand, thousand);
	make.setXHundred(xhundred, hundred);
	make.setXTen(xten, ten);
	make.setXUnits(xunits, units);
	make.setChange1(xthousand, xthousand, key);
	make.setChange2(xhundred, xunits, key);

	cout << endl;
	cout << "암호화된 정수는 : ";
	make.setEncrypt();
	cout << " 입니다.";

	// 윗쪽이 암호화 문제
	// 아랫쪽이 해독 문제

	cout << endl << endl;
	cout << "해독할 4자리 정수를 입력하시오 : ";
	cin >> integer;
	make.setInteger(integer);
	make.setThousand(integer, thousand);
	make.setHundred(integer, hundred);
	make.setTen(integer, units, ten);
	make.setUnits(integer, units);
	make.setRThousand(rthousand, xthousand);
	make.setRHundred(rhundred, xhundred);
	make.setRTen(rten, xten);
	make.setRUnits(runits, xunits);
	
	cout << endl;
	cout << "해독된 정수는 : ";
	make.setSolution();
	cout << " 입니다.";
}