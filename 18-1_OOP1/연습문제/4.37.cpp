//4�� Exercise 4.37 �ϳ��� Ŭ���� Encrypt�� ��ȣȭ �Լ��� �ص��Լ� ��θ� �ڵ��߽��ϴ�.
//�Է¹��� ������ �� �ڸ����� ���� ������ 3���� ��ҽ��ϴ�. ex) th(input), xth(��ȣȭ), rth(�ص�)

#include <iostream>

using namespace std;

class Encrypt {
public:
	Encrypt(int i, int th, int t, int h, int u, int xth, int xh, int xt, int xu, int k, int rth, int rh, int rt, int ru) { // ������
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

	// ��ȣȭ �ܰ� 1 �Լ� 

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

	// ��ȣȭ �ܰ� 2 �Լ�

	void setChange1(int xth, int xt, int k) { // ù��° ���ڶ� ����° ���� �ٲٱ�
		k = xthousand;
		xthousand = xten;
		xten = k;
	}
	void setChange2(int xh, int xu, int k) { // �ι�° ���ڶ� �׹�° ���� �ٲٱ�
		k = xhundred;
		xhundred = xunits;
		xunits = k;
	}


	//�ص� 1�ܰ�

	void setRThousand(int rth, int th) { // �� �ڸ����� ��� ���ڸ��� �̹Ƿ� +10 - 7 �� �� �� 10���� ���� �������� ��ȣȭ ������ ���̴�.
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
	

	void setEncrypt() { // ��¸��� ���� void Ÿ�� set �Լ� ( 4�ڸ� ������ ��� ��� ����� ��� õ���ڸ� ���ڰ� 0�� ��� ���ڸ� ���� ����� �ȴ�. ���� ���ڵ��� ���� ��� ���)
		cout << xthousand << xhundred << xten << xunits;
	}

	void setSolution() { // ��ȣ�� ����°Ͱ� �����ϰ� �߰����� k�� �̿��� �ڸ����� �Ҵ�� ���� �ƿ� �ٲپ� �� ���� ������ ��¼����� �ٲپ� ���ڸ� �����ϴ� ����� �ִ�.
		cout << rten << runits << rthousand << rhundred;
	}

private:
	int integer; // �Է¹��� �� i

	int thousand; // �Է¹��� 4�ڸ� ������ ���ڸ� �� �������
	int hundred;
	int ten;
	int units;

	int	xthousand; // ��ȣȭ�� ���� ������ �������
	int xhundred;
	int xten;
	int xunits;

	int rthousand; // ��ȣ �ص��� ���� ������ ����
	int rhundred;
	int rten;
	int runits;

	int key; // ��ȣȭ �߰��� ������ ��ȣȭ ���� �������
};

int main() {
	int integer = 0; // �Է¹��� �� i

	int thousand = 0; // �Է¹��� 4�ڸ� ������ ���ڸ� �� �������
	int hundred = 0;
	int ten = 0;
	int units = 0;

	int	xthousand = 0; // ��ȣȭ�� ���� ������ �������
	int xhundred = 0;
	int xten = 0;
	int xunits = 0;

	int rthousand = 0; // ��ȣ �ص��� ���� ������ ����
	int rhundred = 0;
	int rten = 0;
	int runits = 0;

	int key = 0; // ��ȣȭ �߰��� ������ ��ȣȭ ���� �������

	Encrypt make(integer, thousand, hundred, ten, units, xthousand, xhundred, xten, xunits, key, rthousand, rhundred, rten, runits);

	cout << "������ 4�ڸ� ������ �Է��Ͻÿ� : "; // prompt
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
	cout << "��ȣȭ�� ������ : ";
	make.setEncrypt();
	cout << " �Դϴ�.";

	// ������ ��ȣȭ ����
	// �Ʒ����� �ص� ����

	cout << endl << endl;
	cout << "�ص��� 4�ڸ� ������ �Է��Ͻÿ� : ";
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
	cout << "�ص��� ������ : ";
	make.setSolution();
	cout << " �Դϴ�.";
}