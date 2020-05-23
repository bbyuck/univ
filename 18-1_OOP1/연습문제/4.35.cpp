// 4장 Exercise 4.31번  소문제 a, b, c 를 하나의 클래스에 작성했습니다.

#include <iostream>

using namespace std;

class Math {

public:
	Math(unsigned int i, unsigned int f, unsigned int c, unsigned int ec, double exp, double t, double expM, double m, double mt, double x) { // 생성자
		integer = i; // 문제 a에서 사용되는변수
		factorial = f;
		counter = 1;
		ecounter = 1;//문제 b에서 사용되는 변수
		exponential = exp;
		total = t;
		exponentialM = expM; // 문제 c에서 사용되는 변수
		multi = m;
		multitotal = mt;
		variable = x; // 문제 c의 x
	}

	void setInteger(unsigned int i) {
		integer = i;
	}
	void setCounter(int c) {
		c = 1;
		counter = c;
	}
	void setFactorial(unsigned int i, unsigned f, unsigned int c) { // a답 팩토리얼을 구하는 함수
		f = i;
		while (c < i) {
			f = f * (i - c);
			c++;
		}
		factorial = f;
	}
	void setEcounter(unsigned int ec) {
		ecounter = 1;
	}

	void setExponential(unsigned int i, unsigned int ec, unsigned int c, double exp, double t) { // main함수에서 i값을 입력하면 i에 따른 exponential의 근사치를 구하는 함수
		exp = 1;                         // 1/n! =  1/n * 1/(n-1)... * 1/2 * 1/1 임을 이용.
		c = i;
		while (c >= 1) {
			ec = c;
			while (ec >= 1) {
				t = t * 1 / ec;
				ec--;
			}
			exp = exp + t;
			c--;
			t = 1;
		}
		exponential = exp;
	}

	void setExponentialM(unsigned int i, unsigned int ec, unsigned int c, double exp, double t, double expM, double m, double mt, double x) {
				//x^n과 n!을 따로 분리해서 계산후 곱연산으로 x^n/n! 일반항을 만들어준다.
		c = i;
		expM = 1;
		while (c >= 1) {
			m = 1;
			ec = c;
			while (ec >= 1) {
				t = t * 1 / ec;
				m = m * x;
				ec--;
			}
			mt = m * t; // x^n * 1/n!
			expM = expM + mt;
			c--;
			t = 1;
		}
		exponentialM = expM;
	}

	unsigned int getFactorial() {
		return factorial;
	}
	double getExponential() {
		return exponential;
	}
	double getExponentialM() {
		return exponentialM;
	}

private:
	unsigned int integer;
	unsigned int factorial;
	unsigned int counter;
	unsigned int ecounter;
	double exponential; // e변수
	double total;
	double exponentialM; // e^x 변수
	double multi;
	double multitotal;
	double variable; // x값
};

int main() {
	unsigned int integer = 0;
	unsigned int factorial = 0;
	unsigned int counter = 1;
	unsigned int ecounter = 1;
	double exponential = 1;
	double total = 1;
	double exponentialM = 0; // e^x 변수
	double multi = 1;
	double multitotal = 1;
	double variable = 0; // x값

	Math Factorial(integer, factorial, counter, exponential, ecounter, total, exponentialM, multi, multitotal, variable); // 객체생성


	cout << "i를 입력하시오 :"; // a, b prompt
	cin >> integer;
	cout << "e의 지수 x를 입력하시오 :"; // c prompt
	cin >> variable;
	Factorial.setInteger(integer);
	Factorial.setFactorial(integer, factorial, counter);
	Factorial.setCounter(counter);
	Factorial.setExponential(integer, ecounter, counter, exponential, total);
	Factorial.setExponentialM(integer, ecounter, counter, exponential, total, exponentialM, multi, multitotal, variable);
	cout << integer << "! = " << Factorial.getFactorial() << endl; // 팩토리얼 출력
	cout << "e의 근사치 : " << Factorial.getExponential() << endl;
	cout << "e^x의 근사치 : " << Factorial.getExponentialM() << endl;
}