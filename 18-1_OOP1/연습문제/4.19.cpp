#include <iostream>

using namespace std;

class contest { // contest 클래스 선언

public:
	contest(int s, int n, int l, int c) { // 생성자
		number = n;
		largest = l;
		counter = c;
		second = s;
	}
	void setCounter(int c) { // 값을 저장할 set함수
		counter = c;
	}
	void setNumber(int n) {
		number = n;
	}
	void setSecond(int s) {
	}
	void setLargest(int l) { // 가장 큰 수 뽑는 setLargest 함수
		if (counter == 1) { // counter가 1일때 default값 설정
			largest = number;
		}
		if (counter != 1) { // counter값이 1이 아닐때
			if (largest < number) { // 입력받은 값이 저장해둔 최댓값보다 크면
				second = largest; // 두번째로 큰 수를 저장할 변수 second에 기존의 최댓값을 넣어줌
				largest = number; // 최댓값변수 largest에 새로 입력받은 수를 넣음
			}
			else { // 입력받은 값이 저장해둔 최댓값보다 작거나 같을 때
				if (second <= number) { // 기존에 두번째로 큰 수가 입력받은 수보다 작거나 같으면
					second = number; // 입력받은 값을 두번째로 큰 수를 저장할 변수 second에 넣어줌
				}
				largest = largest; // 입력받은 값이 저장해둔 최댓값보다 작거나 같으므로 기존의 최댓값이 그대로 최댓값.
			}
		}
	}



	int getNumber() { // 값을 리턴시킬 get함수
		return number;
	}
	int getLargest() {
		return largest;
	}
	int getSecond() {
		return second;
	}

private:
	int second; // 멤버변수
	int number;
	int largest;
	int counter;

};

int main() {
	int second = 0;
	int counter = 1; // 반복문에서 카운터로 사용
	int number = 0;
	int largest = 0;


	contest input(second, number, largest, counter);

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
		input.setSecond(second);
		counter++;
		input.setCounter(counter); // class 로 counter의 증감을 보내주어 첫 번째로 입력받은 수가 음수여도 largest 변수에 음수 들어갈 수 있도록 도와줌. because largest를 0으로 초기화했기 때문에 getLargest 함수의 else if문을 바로 읽으면 음수일때 가장 큰수가 0으로 출력되는 논리적 오류가 나옴.
	}

	cout << endl;
	cout << "The largest of 10 numbers input : " << input.getLargest() << endl;
	cout << "Second largest of 10 numbers input : " << input.getSecond() << endl;

	return 0;
}