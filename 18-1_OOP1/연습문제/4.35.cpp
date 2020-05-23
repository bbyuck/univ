// 4�� Exercise 4.31��  �ҹ��� a, b, c �� �ϳ��� Ŭ������ �ۼ��߽��ϴ�.

#include <iostream>

using namespace std;

class Math {

public:
	Math(unsigned int i, unsigned int f, unsigned int c, unsigned int ec, double exp, double t, double expM, double m, double mt, double x) { // ������
		integer = i; // ���� a���� ���Ǵº���
		factorial = f;
		counter = 1;
		ecounter = 1;//���� b���� ���Ǵ� ����
		exponential = exp;
		total = t;
		exponentialM = expM; // ���� c���� ���Ǵ� ����
		multi = m;
		multitotal = mt;
		variable = x; // ���� c�� x
	}

	void setInteger(unsigned int i) {
		integer = i;
	}
	void setCounter(int c) {
		c = 1;
		counter = c;
	}
	void setFactorial(unsigned int i, unsigned f, unsigned int c) { // a�� ���丮���� ���ϴ� �Լ�
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

	void setExponential(unsigned int i, unsigned int ec, unsigned int c, double exp, double t) { // main�Լ����� i���� �Է��ϸ� i�� ���� exponential�� �ٻ�ġ�� ���ϴ� �Լ�
		exp = 1;                         // 1/n! =  1/n * 1/(n-1)... * 1/2 * 1/1 ���� �̿�.
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
				//x^n�� n!�� ���� �и��ؼ� ����� ���������� x^n/n! �Ϲ����� ������ش�.
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
	double exponential; // e����
	double total;
	double exponentialM; // e^x ����
	double multi;
	double multitotal;
	double variable; // x��
};

int main() {
	unsigned int integer = 0;
	unsigned int factorial = 0;
	unsigned int counter = 1;
	unsigned int ecounter = 1;
	double exponential = 1;
	double total = 1;
	double exponentialM = 0; // e^x ����
	double multi = 1;
	double multitotal = 1;
	double variable = 0; // x��

	Math Factorial(integer, factorial, counter, exponential, ecounter, total, exponentialM, multi, multitotal, variable); // ��ü����


	cout << "i�� �Է��Ͻÿ� :"; // a, b prompt
	cin >> integer;
	cout << "e�� ���� x�� �Է��Ͻÿ� :"; // c prompt
	cin >> variable;
	Factorial.setInteger(integer);
	Factorial.setFactorial(integer, factorial, counter);
	Factorial.setCounter(counter);
	Factorial.setExponential(integer, ecounter, counter, exponential, total);
	Factorial.setExponentialM(integer, ecounter, counter, exponential, total, exponentialM, multi, multitotal, variable);
	cout << integer << "! = " << Factorial.getFactorial() << endl; // ���丮�� ���
	cout << "e�� �ٻ�ġ : " << Factorial.getExponential() << endl;
	cout << "e^x�� �ٻ�ġ : " << Factorial.getExponentialM() << endl;
}