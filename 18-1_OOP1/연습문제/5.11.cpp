#include <iostream>

using namespace std;

class Smallest {

public:
	Smallest(int x, int s, int c) { // 생성자
		num = x;
		smallest = s;
		counter = c;
	} // Smallest 대괄호 끝

	void setNum(int x) {
		num = x;
	}
	void setCounter(int c) {
		counter = c;
	}
	void setSmallest(int x, int s, int c) {
		if (c == 1) {
			smallest = num;
		}
		else if (smallest <= num) {
			smallest = smallest;
		}
		else {
			smallest = num;
		}
	}	// 값을 저장할 set함수들 리턴할 값이 필요 없으므로 데이터 타입은 void형

	int getSmallest() {
		return smallest;
	}


private:
	int num; // 멤버변수 입력받을 수, 가장 작은 정수 저장할 변수
	int smallest;
	int counter;
};

int main() {
	int num = 0;
	int smallest = 0;
	int ncounter = 0; // 입력받을 정수의 개수
	int counter = 1;
	cout << "입력할 정수의 갯수를 입력하세요" << endl; // prompt
	cin >> ncounter; //

	Smallest integer(num, smallest, counter);

	while (counter <= ncounter) {
		cout << "정수를 입력하세요 ";
		cin >> num;
		integer.setNum(num);
		integer.setSmallest(num, smallest, counter);
		++counter;
		integer.setCounter(counter);
	}
	cout << "가장 작은 정수는 " << integer.getSmallest() << "입니다.";

	return 0;
}