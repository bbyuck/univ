#include <iostream>
#include <cmath>


using namespace std;

double distance(double, double); // �Լ� ������Ÿ��

int main() {

	double x1 = 0;
	double y1 = 0;
	double x2 = 0;
	double y2 = 0; // �Է¹��� ���� x1,y1,x2,y2 ���� �� �ʱ�ȭ

	cout << "x1 �Է� : ";
	cin >> x1;

	cout << "y1 �Է� : ";
	cin >> y1;

	cout << "x2 �Է� : ";
	cin >> x2;

	cout << "y2 �Է� : ";
	cin >> y2; // �� �Է� prompt

	cout << "\n�� �� (x1, y1)�� (x2, y2) ������ �Ÿ� : " << distance(x2 - x1, y2 - y1); // �Լ� ȣ�� �� ������� �Լ� �����۵����� Ȯ��

	return 0;
}

double distance(double dx, double dy) { // �� �� ������ �Ÿ� dx, dy �μ�
	double distance; // ����� �Ÿ��� �����ϰ� ��ȯ�� ����

	distance = sqrt(pow(dx, 2) + pow(dy, 2)); // distance ����

	return distance;
}