#include <iostream>
#include <iomanip>
using namespace std;

class Sphere {

public:
	Sphere(double r, double c, double a, double v) { //������
		radius = r;
		circumference = c;
		area = a;
		volume = v;
	}
	void setRadius(double r) { // ���� ������ִ� void�� set �Լ���
		radius = r;
	}
	void setCircumference(double c, double r) {
		c = 2 * r * 3.14159;
		circumference = c;
	}
	void setArea(double a, double r) {
		a = r * r * 3.14159;
		area = a;
	}
	void setVolume(double v, double r) {
		v = 4 / 3 * r * r * r * 3.14159;
		volume = v;
	}

	double getRadius() {
		return radius;
	}
	double getCircumference() {
		return circumference;
	}
	double getArea() {
		return area;
	}
	double getVolume() {
		return volume;
	}

private:
	double radius; //������  // �������
	double circumference; // ����
	double area; // ����
	double volume; // ���� ����
};

int main() {
	double radius = 0;
	double circumference = 0;
	double area = 0;
	double volume = 0;

	Sphere calculate(radius, circumference, area, volume);

	cout << "Enter radius : "; // prompt
	cin >> radius; // �������Է�
	calculate.setRadius(radius);
	calculate.setCircumference(circumference, radius);
	calculate.setArea(area, radius);
	calculate.setVolume(volume, radius);
	cout << "Circumference : " << fixed << setprecision(5) << calculate.getCircumference() << endl;
	cout << "Area : " << fixed << setprecision(5) << calculate.getArea() << endl;
	cout << "Volume : " << fixed << setprecision(5) << calculate.getVolume() << endl;
}