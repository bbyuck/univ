// 삼각형의 세 변이 주어 졌을때 가장 큰 길이의 변이 나머지 두 변의 합보다 작아야 한다.

#include <iostream>


using namespace std;

class Triangle { // contest 클래스 선언

public:
	Triangle(double n, double l, double t) { // 생성자
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
	void setLargest(double l) { // 가장 큰 수 뽑는 setLargest 함수
		if (largest == 0) {
			largest = number;
		}
		else if (largest < number) {
			largest = number;
		}
		else largest = largest;
	}
	double getNumber() { // 값을 리턴시킬 get함수
		return number;
	}
	double getLargest() {
		return largest;
	}
	double getDetermine() {
		if (total - largest > largest) { //{알고리즘} 삼각형 세 변의 합(total) - 가장 긴 변의 길이(largest)를 뺀 길이 = [작은 두 변의 길이의 합] >가장 긴 변의 길이(largest)
			return 1; // 삼각형이 형성이 되면 1을 반환
		}
		else {
			return 0;
		}
	}

private:
	double number; // 멤버변수
	double largest;
	double total; // 삼각형 세 변의 합
};

int main() {
	double number = 0;
	double largest = 0;
	double total = 0;


	Triangle Determine(number, largest, total);
	int counter = 1;

	while (counter <= 3) { // while문을 통해 total, largest 값 계산
		cout << "Enter nonzero values : "; // prompt
		cin >> number;
		Determine.setNumber(number);
		Determine.setLargest(largest);
		Determine.setTotal(total);
		counter++;
	}
	if (Determine.getDetermine() == 1) { // 삼각형을 형성할 수 있으면
		cout << "These three values can form a triangle.";
	}
	else { // 없으면
		cout << "These three values can't form a triangle.";
	}
}