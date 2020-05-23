#include <iostream>

using namespace std;

class contest { // contest 클래스 선언

public:
	contest(int n, int l, int c) { // 생성자
		number = n;
		largest = l;
		counter = c;
	}

	void setNumber(int n) {
		number = n;
	}
	void setLargest(int l) { // 가장 큰 수 뽑는 setLargest 함수
		if (counter == 1) {
			largest = number;
		}
		else if (largest < number) {
			largest = number;
		}
		else largest = largest;
	}
	void setCounter(int c) {
		counter = c;
	}

	int getNumber() { // 값을 리턴시킬 get함수
		return number;
	}
	int getLargest() {
		return largest;
	}

private:
	int number; // 멤버변수
	int largest;
	int counter;
};

int main() {
	int counter = 1; // 반복문에서 카운터로 사용
	int number = 0;
	int largest = 0;

	contest input(number, largest, counter);

	while (counter <= 10) { // while 문 통해서 counter 변수가 1 ~ 10 까지 반복할 수 있도록 조건 선언
		if (counter == 1) {
			cout << "Enter 1st number : "; // 첫번째 수 입력할 수 있는 prompt에 1st UI 
		}
		else if (counter == 2) { // 두번째 수 입력할 수 있는 prompt에 2nd UI
			cout << "Enter 2nd number : ";
		}
		else if (counter == 3) { // 세번째 수 입력할 수 있는 prompt에 3rd UI
			cout << "Enter 3rd number : ";
		}
		else { // 4이상의 수 뒤에는 th 붙임.
			cout << "Enter " << counter << "th number : ";
		}
		cin >> number;
		input.setNumber(number);
		input.setLargest(largest);
		counter++;
		input.setCounter(counter); // class 로 counter의 증감을 보내주어 첫 번째로 입력받은 수가 음수여도 largest 변수에 음수 들어갈 수 있도록 도와줌. because largest를 0으로 초기화했기 때문에 getLargest 함수의 else if문을 바로 읽으면 음수일때 가장 큰수가 0으로 출력되는 논리적 오류가 나옴.
	}

	cout << endl;
	cout << "The largest of 10 numbers input : " << input.getLargest() << endl;

	return 0;
}